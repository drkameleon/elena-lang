//---------------------------------------------------------------------------
//		E L E N A   P r o j e c t:  ELENA RT Engine
//
//                                              (C)2009-2020, by Alexei Rakov
//---------------------------------------------------------------------------

#include "elena.h"
// --------------------------------------------------------------------------
#include "elenartmachine.h"
#include "rtman.h"
#include "config.h"
#include "bytecode.h"

#define LIBRARY_PATH                "configuration/library/path"

using namespace _ELENA_;

// --- Instance ---

void ELENARTMachine :: startSTA(ProgramHeader* frameHeader, SystemEnv* env, void* programEntry)
{
   // setting up system
   __routineProvider.InitSTA((SystemEnv*)env, frameHeader);

   _Entry entry;
   entry.address = env->Invoker;

   // executing the program
   int retVal = entry.evaluate2(0, programEntry);

   // winding down system
   Exit(0);
}

void ELENARTMachine :: startMTA(ProgramHeader* frameHeader, SystemEnv* env, void* programEntry)
{
   // setting up system
   __routineProvider.InitMTA((SystemEnv*)env, frameHeader);

   _Entry entry;
   entry.address = env->Invoker;

   // executing the program
   int retVal = entry.evaluate3(0, programEntry, nullptr);

   // winding down system
   Exit(0);
}

void ELENARTMachine :: startThread(ProgramHeader* frameHeader, SystemEnv* env, void* threadEntry, int index)
{
   __routineProvider.NewThread(env, frameHeader);

   _Entry entry;
   entry.address = env->Invoker;

   entry.evaluate3(0, threadEntry, &index);

   __routineProvider.ExitThread(env, 0, false);
}

void ELENARTMachine :: Exit(int exitCode)
{
   __routineProvider.Exit(exitCode);
}

void ELENARTMachine :: ExitThread(SystemEnv* env, int exitCode)
{
   __routineProvider.ExitThread(env, exitCode, true);
}

// --- Instance::ImageSection ---

void* ELENARTMachine :: ImageSection :: get(pos_t position) const
{
   return (unsigned char*)_section + position;
}

bool ELENARTMachine :: ImageSection :: read(pos_t position, void* s, pos_t length)
{
   if (position < _length && _length >= position + length) {
      memcpy(s, (unsigned char*)_section + position, length);

      return true;
   }
   else return false;
}

ELENARTMachine :: ELENARTMachine(path_t rootPath, path_t execFileName)
   : _rootPath(rootPath)
{
   _messageSection = nullptr;
   _mattributesSection = nullptr;

   _debugFilePath.copy(execFileName);
   _debugFilePath.changeExtension("dn");
}

bool ELENARTMachine :: loadDebugSection()
{
   if (_debugFilePath.isEmpty())
      return false;

   FileReader reader(_debugFilePath.c_str(), feRaw, false);
   if (!reader.isOpened()) {
      // clear the path to indicate an absence of debug data
      _debugFilePath.clear();

      return false;
   }
   else {
      char header[5];
      reader.read(header, 5);
      if (!ident_t(DEBUG_MODULE_SIGNATURE).compare(header, 0, 5)) {
         // clear the path to indicate invalid debug data
         _debugFilePath.clear();

         return false;
      }

      size_t len = reader.getDWord();
      MemoryWriter writer(&_debugSection);
      writer.read(&reader, len);

      return len != 0;
   }
}

bool ELENARTMachine :: loadConfig(path_t configFile)
{
   Path configPath((path_t)_rootPath);
   configPath.combine(configFile);

   XmlConfigFile config;
   if (!config.load(configPath.c_str(), feUTF8)) {
      return false;
   }

   Path path(_rootPath.c_str(), config.getSetting(LIBRARY_PATH));

   if (!emptystr(path)) {
      _loader.setRootPath(path.c_str());
   }

   return true;
}

void ELENARTMachine :: init(void* messageTable, void* mattributeTable, path_t configPath)
{
   _messageSection = messageTable;
   _mattributesSection = mattributeTable;

   loadConfig(configPath);
}

int ELENARTMachine :: readCallStack(size_t framePosition, size_t currentAddress, size_t startLevel, int* buffer, size_t maxLength)
{
   RTManager manager;

   ImageSection image;
   MemoryReader reader(&image);

   return manager.readCallStack(reader, framePosition, currentAddress, startLevel, buffer, maxLength);
}

int ELENARTMachine :: loadAddressInfo(size_t retPoint, char* buffer, size_t maxLength)
{
   // lazy load of debug data
   if (_debugSection.Length() == 0 && !loadDebugSection())
      return 0;

   RTManager manager;
   MemoryReader reader(&_debugSection);

   // skip a debugger entry pointer
   reader.getDWord();

   // set the root namespace
   _loader.setNamespace(reader.getLiteral(DEFAULT_STR));

   return manager.readAddressInfo(reader, retPoint, &_loader, buffer, maxLength);
}

int ELENARTMachine :: loadClassName(size_t classAddress, char* buffer, size_t length)
{
   int packagePtr = *(int*)(classAddress - 24);
   int namePtr = *(int*)(classAddress - 20);

   char* name = (char*)namePtr;
   char* ns = ((char**)packagePtr)[0];

   size_t ns_len = length;
   if (!ident_t(ns).copyTo(buffer, ns_len))
      return 0;

   length -= ns_len;
   if (!ident_t(name).copyTo(buffer + ns_len, length))
      return 0;

   return length + ns_len;
}

int ELENARTMachine :: loadSubjectName(size_t subjectRef, char* buffer, size_t length)
{
   ImageSection messageSection;
   messageSection.init(_messageSection, 0x1000000); // !! dummy size

   ref_t actionPtr = messageSection[subjectRef * 8];

   if (actionPtr == 0) {
      size_t used = length;
      pos_t namePtr = messageSection[subjectRef * 8 + 4];

      MemoryReader reader(&messageSection);
      reader.seek(namePtr);

      IdentifierString messageName;
      reader.readString(messageName);

      Convertor::copy(buffer, messageName.c_str(), messageName.Length(), used);

      return used;
   }
   else return loadSubjectName(actionPtr, buffer, length);
}

int ELENARTMachine :: loadMessageName(size_t messageRef, char* buffer, size_t length)
{
   int prefixLen = 0;
   int paramCount = 0;
   ref_t actionRef, flags;
   decodeMessage(messageRef, actionRef, paramCount, flags);
   if (test(flags, VARIADIC_MESSAGE)) {
      size_t len = 7;
      Convertor::copy(buffer, "params#", 7, len);

      buffer += len;
      length -= len;
      prefixLen += len;
   }

   int used = loadSubjectName(actionRef, buffer, length);
   if (used > 0) {
      size_t dummy = 10;
      String<char, 10>temp;
      temp.appendInt(paramCount);

      buffer[used++] = '[';
      Convertor::copy(buffer + used, temp, getlength(temp), dummy);
      used += dummy;
      buffer[used++] = ']';
   }

   return prefixLen + used;
}

void* ELENARTMachine :: loadMetaAttribute(ident_t name, int category)
{
   ImageSection mattrSection;
   mattrSection.init(_mattributesSection, 0x10000); // !! dummy size
   MemoryReader reader(&mattrSection);

   size_t len = reader.getDWord();

   RTManager manager;

   return manager.loadMetaAttribute(reader, name, category, len);
}

//inline void printInfo(char n)
//{
//   putchar(n);
//   fflush(stdout);
//}

void* ELENARTMachine :: loadSubject(ident_t name)
{
   ImageSection messageSection;
   messageSection.init(_messageSection, 0x1000000); // !! dummy size
   MemoryReader reader(&messageSection);

   for (ref_t subjectRef = 1; true; subjectRef++) {
      if (messageSection[subjectRef * 8] == 0) {
         pos_t namePtr = messageSection[subjectRef * 8 + 4];
         if (!namePtr)
            break;

         reader.seek(namePtr);

         IdentifierString messageName;
         reader.readString(messageName);

         if (messageName.compare(name)) {
            return (void*)subjectRef;
         }
      }
   }

   return nullptr;
}

void* ELENARTMachine :: loadMessage(ident_t message)
{
   IdentifierString messageName;
   int paramCount = -1;
   ref_t flags = 0;

   if (SystemRoutineProvider::parseMessageLiteral(message, messageName, paramCount, flags)) {
      ref_t actionRef = (ref_t)loadSubject(messageName.ident());
      if (!actionRef)
         return nullptr;

      return (void*)(encodeMessage(actionRef, paramCount, flags));
   }
   else return nullptr;
}

ref_t ELENARTMachine :: loadDispatcherOverloadlist(ident_t referenceName)
{
   return (ref_t)loadMetaAttribute(referenceName, caExtOverloadlist);
}

int ELENARTMachine :: loadExtensionDispatcher(const char* moduleList, ref_t message, void* output)
{
   // load message name
   char messageName[IDENTIFIER_LEN];
   int mssgLen = loadMessageName(message, messageName, IDENTIFIER_LEN);
   messageName[mssgLen] = 0;

   int len = 0;

   // search message dispatcher
   IdentifierString messageRef;
   int listLen = getlength(moduleList);
   int i = 0;
   while (moduleList[i]) {
      ident_t ns = moduleList + i;

      messageRef.copy(ns);
      messageRef.append('\'');
      messageRef.append(messageName);

      ref_t listRef = loadDispatcherOverloadlist(messageRef.c_str());
      if (listRef) {
         ((int*)output)[len] = listRef;
         len++;
      }

      i += getlength(ns) + 1;
   }

   return len;
}
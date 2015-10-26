//---------------------------------------------------------------------------
//		E L E N A   P r o j e c t:  ELENA Compiler
//               
//		This file contains ELENA Engine Syntax Tree classes
//
//                                              (C)2005-2015, by Alexei Rakov
//---------------------------------------------------------------------------

#ifndef syntaxTreeH
#define syntaxTreeH 1

namespace _ELENA_
{

// --- SyntaxType ---

enum LexicalType
{
   lxObjectMask      = 0x100,
   lxCallMask        = 0x200,

   lxNone            = 0x000,

   lxCodeBlock       = 0x001,

   lxExpression      = 0x101,
   lxSymbol          = 0x102,
   lxConstantSymbol  = 0x103,
   lxField           = 0x104,
   lxFieldAddress    = 0x105,
   lxLocal           = 0x106,
   lxConstantString  = 0x107,
   lxConstantChar    = 0x108,
   lxConstantInt     = 0x109,
   lxConstantLong    = 0x10A,
   lxConstantReal    = 0x10B,
   lxConstantClass   = 0x10C,
   lxNil             = 0x10D,
   lxCurrent         = 0x10E,
   lxResult          = 0x10F,

   lxSemiDirectCall  = 0x201,
   lxDirectCall      = 0x203,
   lxCall            = 0x204,
   lxTypecast        = 0x205,
   lxExternalCall    = 0x206,

   lxAlternative     = 0x401,
   lxCatch           = 0x402,
   lxAssigning       = 0x403,    // if argument == 0 -> assign field, otherwise copy the memory block with specified size
   lxReturning       = 0x404,
   lxBoxing          = 0x405,
   lxCondBoxing      = 0x406,    // the same like boxing except checking if the reference is stack allocated

   lxTarget          = 0x801,
   lxType            = 0x802,

   lxBreakpoint      = 0x1001,
   lxCol             = 0x1002,
   lxRow             = 0x1003,
   lxLength          = 0x1004,
};

// --- SyntaxWriter ---

class SyntaxWriter
{
   MemoryWriter _writer;

public:
   void clear()
   {
      _writer.seek(0);
   }

   void newNode(LexicalType type, ref_t argument);
   void newNode(LexicalType type)
   {
      newNode(type, 0);
   }
   void appendNode(LexicalType type, ref_t argument)
   {
      newNode(type, argument);
      closeNode();
   }
   void appendNode(LexicalType type)
   {
      newNode(type);
      closeNode();
   }

   void closeNode();

   SyntaxWriter(_Memory* dump)
      : _writer(dump)
   {
   }
};

// --- SyntaxReader ---

class SyntaxReader
{
public:
   // --- Node ---
   class Node
   {
      friend class SyntaxReader;

      SyntaxReader* reader;
      size_t        position;

      Node(SyntaxReader* reader, size_t position, LexicalType type, ref_t argument);

   public:
      LexicalType   type;
      ref_t         argument;

      bool operator == (LexicalType type)
      {
         return this->type == type;
      }
      bool operator != (LexicalType type)
      {
         return this->type != type;
      }

      void operator = (LexicalType type)
      {
         this->type = type;

         int prevPos = reader->_reader.Position();

         reader->_reader.seek(position - 8);
         *(int*)(reader->_reader.Address()) = (int)type;
         reader->_reader.seek(prevPos);
      }

      Node firstChild() const
      {
         return reader->readFirstNode(position);
      }

      Node nextNode() const
      {
         return reader->readNextNode(position);
      }

      Node prevNode() const
      {
         return reader->readPreviousNode(position);
      }

      Node()
      {
         type = lxNone;
         argument = 0;

         reader = NULL;
      }
   };

private:
   MemoryReader _reader;

   Node read();

public:
   static Node findChild(Node node, LexicalType type)
   {
      Node current = node.firstChild();

      while (current != lxNone && current != type) {
         current = current.nextNode();
      }

      return current;
   }

   static Node findChild(Node node, LexicalType type1, LexicalType type2)
   {
      Node current = node.firstChild();

      while (current != lxNone && current != type1) {
         if (current == type2)
            return current;

         current = current.nextNode();
      }

      return current;
   }

   Node readRoot();
   Node readFirstNode(size_t position);
   Node readNextNode(size_t position);
   Node readPreviousNode(size_t position);

   SyntaxReader(_Memory* dump)
      : _reader(dump)
   {      
   }
};

} // _ELENA_

#endif // syntaxTreeH

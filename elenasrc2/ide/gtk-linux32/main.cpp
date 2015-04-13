//---------------------------------------------------------------------------
//		E L E N A   P r o j e c t:  ELENA IDE
//      Linux-GTK+ program entry
//                                              (C)2005-2015, by Alexei Rakov
//---------------------------------------------------------------------------

//#include "gtk-linux32/gtkcommon.h"
////#include "gtk-linux32/gtksdi.h"
////#include "gtk-linux32/gtkmenu.h"
////#include "gtk-linux32/gtktoolbar.h"
////#include "gtk-linux32/gtkstatusbar.h"
////#include "gtkeditframe.h"

#include "gtkide.h"
////#include "gtkideconst.h"
#include "../appwindow.h"
#include "../settings.h"

using namespace _GUI_;

//#pragma GCC diagnostic ignored "-Wwrite-strings"

// --- command line arguments ---
#define CMD_CONFIG_PATH    _T("-c")

class GTKIDEView : public _View, public _DebugListener
{
public:
   MainWindow appWindow;

   virtual void start(bool maximized)
   {
      appWindow.show();

      if (maximized)
         appWindow.maximize();
   }

   virtual void exit()
   {
      appWindow.exit();
   }

   virtual void refresh(bool onlyFrame)
   {
//      if (onlyFrame) {
//         appWindow.refreshDocument();
//      }
//      else appWindow.refresh();
   }

   virtual bool saveProject(Model* model, _ELENA_::Path& path)
   {
//      FileDialog dialog(&appWindow, FileDialog::ProjectFilter, SAVEAS_PROJECT_CAPTION, model->project.path);
//
//      return dialog.saveFile(_T("prj"), path);
//
//
      return false; // !!
   }

   virtual bool saveFile(Model* model, _ELENA_::Path& newPath)
   {
//      FileDialog dialog(&appWindow, FileDialog::SourceFilter, SAVEAS_FILE_CAPTION, model->project.path);
//
//      return dialog.saveFile(_T("l"), newPath);
//

      return false; // !!
   }

   virtual bool selectFiles(Model* model, _ELENA_::List<text_c*>& selected)
   {
//      FileDialog dialog(&appWindow, FileDialog::SourceFilter, OPEN_FILE_CAPTION, model->paths.lastPath);
//
//      return dialog.openFiles(selected);
//
      return false; // !!
   }

   virtual bool selectProject(Model* model, _ELENA_::Path& path)
   {
//      FileDialog dialog(&appWindow, FileDialog::ProjectFilter, OPEN_PROJECT_CAPTION, model->paths.lastPath);
//
//      path.copy(dialog.openFile());
//
//      return !path.isEmpty();
//
      return false; // !!
   }

   virtual void error(text_t message)
   {
      //MsgBox::showError(appWindow.getHandle(), message, NULL);
   }

   virtual void error(text_t message, text_t param)
   {
      //MsgBox::showError(appWindow.getHandle(), message, param);
   }

   virtual bool confirm(text_t message, text_t param1, text_t param2)
   {
//      int result = MsgBox::showQuestion(appWindow.getHandle(), message, param1, param2);
//
//      return MsgBox::isYes(result);
//
      return false; // !!
   }

   virtual bool confirm(text_t message)
   {
//      int result = MsgBox::showQuestion(appWindow.getHandle(), message);
//
//      return MsgBox::isYes(result);

      return false; // !!
   }

   virtual _View::Answer question(text_t message)
   {
//      int result = MsgBox::showQuestion(appWindow.getHandle(), message);
//
//      if (MsgBox::isYes(result)) {
//         return Answer::Yes;
//      }
//      else if (MsgBox::isCancel(result)) {
//         return Answer::Cancel;
//      }
      /*else */return _View::No;
   }

   virtual Answer question(text_t message, text_t param)
   {
//      int result = MsgBox::showQuestion(appWindow.getHandle(), message, param);
//
//      if (MsgBox::isYes(result)) {
//         return Answer::Yes;
//      }
//      else if (MsgBox::isCancel(result)) {
//         return Answer::Cancel;
//      }
      /*else */return _View::No;
   }

   virtual int newDocument(text_t name, Document* doc)
   {
      return appWindow.newDocument(name, doc);
   }

   virtual int getCurrentDocumentIndex()
   {
     // return appWindow.getCurrentDocumentIndex();
   }

   virtual void selectDocument(int docIndex)
   {
     // appWindow.selectDocument(docIndex);
   }

   virtual void closeDocument(int index)
   {
     // appWindow.closeDocument(index);
   }

   virtual void renameDocument(int index, text_t name)
   {
     // appWindow.renameDocument(index, name);
   }

   virtual void showFrame()
   {
     // appWindow.showFrame();
   }

   virtual void activateFrame()
   {
     // appWindow.activateFrame();
   }

   virtual void hideFrame()
   {
    //  appWindow.hideFrame();
   }

   virtual void showStatus(int index, text_t message)
   {
     // appWindow.setStatusBarText(index, message);
   }

   virtual void setCaption(text_t caption)
   {
      //appWindow.setCaption(caption);
   }

   virtual void enableMenuItemById(int id, bool doEnable, bool toolBarItemAvailable)
   {
//      appWindow.getMenu()->enableItemById(id, doEnable);
//      if (toolBarItemAvailable)
//         appWindow.getToolBar()->enableItemById(id, doEnable);
   }

   virtual void checkMenuItemById(int id, bool doEnable)
   {
      //appWindow.getMenu()->checkItemById(id, doEnable);
   }

   virtual void markDocumentTitle(int docIndex, bool changed)
   {
      //appWindow.markDocumentTitle(docIndex, changed);
   }

   virtual void addToWindowList(text_t path)
   {
      //appWindow.addToWindowList(path);
   }

   virtual void removeFromWindowList(text_t path)
   {
      //appWindow.removeFromWindowList(path);
   }

   virtual void addToRecentFileList(text_t path)
   {
    //  appWindow.addToRecentFileList(path);
   }

   virtual void addToRecentProjectList(text_t path)
   {
   //   appWindow.addToRecentProjectList(path);
   }

   virtual bool configProject(_ProjectManager* project)
   {
//      ProjectSettingsDialog dlg(&appWindow, project);
//
//      return dlg.showModal() != 0;
//
      return false; // !!
   }

   virtual bool configEditor(Model* model)
   {
//      EditorSettings dlg(&appWindow, model);
//
//      return dlg.showModal() != 0;
//
      return false; // !!
   }

   virtual bool configDebugger(Model* model)
   {
//      DebuggerSettings dlg(&appWindow, model);
//
//      return dlg.showModal() != 0;

      return false; // !!
   }

   virtual bool configurateForwards(_ProjectManager* project)
   {
//      ProjectForwardsDialog dlg(&appWindow, project);
//
//      return dlg.showModal() != 0;

      return false; // !!
   }

   virtual bool about(Model* model)
   {
//      AboutDialog dlg(&appWindow);
//
//      return dlg.showModal() != 0;

      return false; // !!
   }

   virtual bool copyToClipboard(Document* doc)
   {
      //return appWindow.copyToClipboard(doc);
   }

   virtual void pasteFromClipboard(Document* doc)
   {
      //appWindow.pasteFrameClipboard(doc);
   }

   virtual bool find(Model* model, SearchOption* option, SearchHistory* searchHistory)
   {
//      FindDialog dialog(&appWindow, false, option, searchHistory, NULL);
//
//      return dialog.showModal();

      return false; // !!
   }

   virtual bool replace(Model* model, SearchOption* option, SearchHistory* searchHistory, SearchHistory* replaceHistory)
   {
//      FindDialog dialog(&appWindow, true, option, searchHistory, replaceHistory);
//
//      return dialog.showModal();

      return false; // !!
   }

   virtual bool gotoLine(int& row)
   {
//      GoToLineDialog dlg(&appWindow, row);
//      if (dlg.showModal()) {
//         row = dlg.getLineNumber();
//
//         return true;
//      }
      /*else */return false;
   }

   virtual bool selectWindow(Model* model, _Controller* controller)
   {
//      IDEWindowsDialog dialog(&appWindow, controller, model);
//
//      if (dialog.showModal() == -2) {
//         return true;
//      }
/*      else */return false;
   }

   virtual void reloadSettings()
   {
      //appWindow.reloadSettings();
   }

   virtual void removeFile(const char* name)
   {
      remove(name);
   }

   virtual void switchToOutput()
   {
      //appWindow.switchToOutput();
   }

   virtual void openOutput()
   {
      //appWindow.openOutput();
   }

   virtual void closeOutput()
   {
      //appWindow.closeOutput();
   }

   virtual void openMessageList()
   {
      //appWindow.openMessageList();
   }

   virtual void closeMessageList()
   {
      //appWindow.closeMessageList();
   }

   virtual void openDebugWatch()
   {
      //appWindow.openDebugWatch();
   }

   virtual void closeDebugWatch()
   {
      //appWindow.closeDebugWatch();
   }

   virtual void openCallList()
   {
      //appWindow.openCallList();
   }

   virtual void closeCallList()
   {
      //appWindow.closeCallList();
   }

   virtual void clearMessageList()
   {
      //appWindow.clearMessageList();
   }

   virtual bool compileProject(_ProjectManager* project, int postponedAction)
   {
      //return appWindow.compileProject(project, postponedAction);
   }

   virtual void resetDebugWindows()
   {
      //appWindow.resetDebugWindows();
   }

   virtual void refreshDebugWindows(_ELENA_::_DebugController* debugController)
   {
      //appWindow.refreshDebugWindows(debugController);
   }

   virtual void browseWatch(_ELENA_::_DebugController* debugController, void* watchNode)
   {
      //appWindow.browseWatch(debugController, watchNode);
   }

   virtual void browseWatch(_ELENA_::_DebugController* debugController)
   {
      //appWindow.browseWatch(debugController);
   }

   virtual void onStop(bool failed)
   {
      //appWindow._notify(failed ? IDE_DEBUGGER_BREAK : IDE_DEBUGGER_STOP);
   }

   void onCheckPoint(const char* message)
   {
      //appWindow._notify(IDE_DEBUGGER_CHECKPOINT, message);
   }

   void onNotification(const char* message, size_t address, int code)
   {
      //appWindow._notify(IDM_DEBUGGER_EXCEPTION, message, address, code);
   }

   virtual void onStep(_ELENA_::ident_t ns, _ELENA_::ident_t source, int row, int disp, int length)
   {
      //appWindow._notify(IDE_DEBUGGER_STEP, TextString(ns), TextString(source), HighlightInfo(row, disp, length));
   }

   virtual void onDebuggerHook()
   {
      //appWindow._notify(IDE_DEBUGGER_HOOK);
   }

   virtual void onStart()
   {
      //appWindow._notify(IDE_DEBUGGER_START);
   }

   GTKIDEView(_Controller* controller, Model* model)
      : appWindow("IDE", controller, model)
   {

   }
};

//// --- getBasePath --
//
//void getBasePath(_path_t* path)
//{
//   pid_t pid = getpid();
//
//   _ELENA_::String<char, 50> link;
//
//   link.copy("/proc/");
//   link.appendInt(pid);
//   link.append("/exe");
//
//   char proc[512];
//   int ch = readlink(link, proc, 512);
//   if (ch != -1) {
//      proc[ch] = 0;
//      int index = _ELENA_::StringHelper::findLast(proc, '/');
//      _ELENA_::StringHelper::copy(path, proc, index);
//      path[index] = 0;
//   }
//   else path[0] = 0;
//}

// --- loadCommandLine ---

inline void setOption(Model* model, const char* parameter)
{
   if (parameter[0]!='-') {
      if (_ELENA_::Path::checkExtension(parameter, "l")) {
         model->defaultFiles.add(_ELENA_::StringHelper::clone(parameter));
      }
      else if (_ELENA_::Path::checkExtension(parameter, "prj")) {
         model->defaultProject.copy(parameter);
      }
   }
}

void loadCommandLine(Model* model, int argc, char *argv[], _ELENA_::Path& configPath)
{
   for (int i = 1 ; i < argc ; i++) {
      if (_ELENA_::StringHelper::compare(argv[i], CMD_CONFIG_PATH, _ELENA_::getlength(CMD_CONFIG_PATH))) {
         configPath.copy(argv[i] + _ELENA_::getlength(CMD_CONFIG_PATH));
      }
      else setOption(model, argv[i]);
   }
}

// --- loadSettings ---

//void loadSettings(const _path_t* path, IDE& appWindow)
void loadSettings(_ELENA_::path_t path, Model* model, GTKIDEView* view)
{
   _ELENA_::IniConfigFile file;

   if (file.load(path, _ELENA_::feUTF8)) {
      Settings::load(model, file);

      // !! temporal
      //view->appWindow.loadHistory(file, RECENTFILES_SECTION, RECENTRPOJECTS_SECTION);

      //view->appWindow.reloadSettings();
   }
}

// --- saveSettings ---

void saveSettings(_ELENA_::path_t path, Model* model, GTKIDEView* view)
{
   _ELENA_::IniConfigFile file;

   Settings::save(model, file);

   // !! temporal
   //view->appWindow.saveHistory(file, RECENTFILES_SECTION, RECENTRPOJECTS_SECTION);

   file.save(path, _ELENA_::feUTF8);
}

// --- main ---

int main( int argc, char *argv[])
{
   Model         model;

//   // get app path
//   _path_t appPath[FILENAME_MAX];
//   getBasePath(appPath);
//
//   // get default path
//   _path_t defPath[FILENAME_MAX];
//   getcwd(defPath, FILENAME_MAX);

   Gtk::Main kit(argc, argv);

   // init paths & settings
//   Paths::init(&model, appPath, defPath);
   Settings::init(&model, "/usr/share/elena/src30/", "/usr/lib/elena/lib30");

   _ELENA_::Path configPath("/etc/elena");
   configPath.combine(_T("ide.config"));

   // load command line argiments
   loadCommandLine(&model, argc, argv, configPath);

   IDEController ide;
   GTKIDEView  view(&ide, &model);

   // init IDE settings
   loadSettings(configPath, &model, &view);

//   controller.assign(ide.getAppWindow());

   // start IDE
   ide.start(&view, &view, &model);

   Gtk::Main::run(view.appWindow);

   saveSettings(configPath, &model, &view);
//   Font::releaseFontCache();

   return 0;
}

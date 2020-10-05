#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>

class SpreadSheet;
class QToolBar;
class QLabel;
class FindDialog;

class MainWindow :
	public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(void);
	~MainWindow(void);

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void find();
	void goToCell();
	void sort();
	void about();

	void openRecentFile();
	void updateStatusBar();
	void spreadsheetModified();

private:
	void readSettings();
	void writeSettings();
	bool okToContinue();
	void updateRecentFileActions();
	QString strippedName(const QString &fullFileName);

	void setCurrentFile(const QString &fileName);

	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);

private:
	// 创建主菜单
	void createMenus();

	// 创建子菜单
	void createActions();

	// 创建右键菜单
	void createContextMenu();

	// 创建工具栏
	void createToolBars();

	// 创建状态栏
	void createStatusBar();

private:
	SpreadSheet *spreadsheet;
	FindDialog *findDialog;

	QStringList recentFiles;
	QString curFile;

	// 状态栏
	QLabel *locationLabel;
	QLabel *formulaLabel;

	// 工具栏
	QToolBar* fileToolBar;
	QToolBar* editToolBar;

	// 文件菜单
	QMenu* fileMenu;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAction;

	enum { MaxRecentFiles = 5 }; // 最近文档
	QAction *recentFileActions[MaxRecentFiles];
	QAction *separatorAction;

	QAction *exitAction;

	// 编辑菜单
	QMenu *editMenu;
	QAction *cutAction;
	QAction *copyAction;
	QAction *pasteAction;
	QAction *deleteAction;

	QMenu *selectSubMenu;
	QAction *selectRowAction;
	QAction *selectColumnAction;
	QAction *selectAllAction;

	QAction *findAction;
	QAction *goToCellAction;

	// 工具菜单
	QMenu *toolsMenu;
	QAction *recalculateAction;
	QAction *sortAction;

	// 选项菜单
	QMenu *optionsMenu;
	QAction *showGridAction;
	QAction *autoRecalcAction;

	// 帮助菜单
	QMenu *helpMenu;
	QAction *aboutAction;
	QAction *aboutQtAction;

};

#endif
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
	// �������˵�
	void createMenus();

	// �����Ӳ˵�
	void createActions();

	// �����Ҽ��˵�
	void createContextMenu();

	// ����������
	void createToolBars();

	// ����״̬��
	void createStatusBar();

private:
	SpreadSheet *spreadsheet;
	FindDialog *findDialog;

	QStringList recentFiles;
	QString curFile;

	// ״̬��
	QLabel *locationLabel;
	QLabel *formulaLabel;

	// ������
	QToolBar* fileToolBar;
	QToolBar* editToolBar;

	// �ļ��˵�
	QMenu* fileMenu;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAction;

	enum { MaxRecentFiles = 5 }; // ����ĵ�
	QAction *recentFileActions[MaxRecentFiles];
	QAction *separatorAction;

	QAction *exitAction;

	// �༭�˵�
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

	// ���߲˵�
	QMenu *toolsMenu;
	QAction *recalculateAction;
	QAction *sortAction;

	// ѡ��˵�
	QMenu *optionsMenu;
	QAction *showGridAction;
	QAction *autoRecalcAction;

	// �����˵�
	QMenu *helpMenu;
	QAction *aboutAction;
	QAction *aboutQtAction;

};

#endif
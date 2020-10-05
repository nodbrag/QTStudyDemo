#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow mainWin;
	mainWin.show();
	return a.exec();
}

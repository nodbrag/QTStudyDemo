#include "sortdialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SortDialog w;
	w.show();
	return a.exec();
}

#include "player.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	player w;
	w.show();
	return a.exec();
}

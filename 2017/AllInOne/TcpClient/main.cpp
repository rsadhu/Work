#include "tcpclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TcpClient w;
	w.show();
	return a.exec();
}

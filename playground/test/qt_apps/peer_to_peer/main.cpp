#include "peer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc != 4)
    {
        qDebug()<<" insufficient args, exiting the apps \n";
        return -1;
    }

    PeerWidget w(std::stoi(argv[1]), std::stoi(argv[2]));
    w.setGeometry(300,200,300, 400);
    w.setWindowTitle(argv[3]);
    w.show();

    return a.exec();
}

#include <QApplication>
#include "graphicsview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyGraphicsView view;
    view.show();

    return a.exec();
}

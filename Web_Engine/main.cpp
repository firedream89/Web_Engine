#include "web_engine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Web_Engine *w = new Web_Engine;

    //TEST
    w->Test();

    return a.exec();
}

#include "web_engine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //TEST
    Web_Engine *w = new Web_Engine;
    w->Show();
    qDebug() << w->Load("http://google.fr");
    qDebug() << w->Get_PlainText();
    qDebug() << w->Get_Html();
    qDebug() << w->Last_Error();
    w->deleteLater();

    return a.exec();
}

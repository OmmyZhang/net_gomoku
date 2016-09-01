#include "begin.h"
#include "mainbody.h"
#include <QApplication>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Begin begin;
    begin.show();

    MainBody mainbody;
    QObject::connect(&begin ,SIGNAL(start_game(bool,QTcpSocket*)),
                     &mainbody,SLOT(game_start(bool,QTcpSocket*)));


    return a.exec();
}

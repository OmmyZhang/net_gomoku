#include "mainbody.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <ctime>

MainBody::MainBody(QWidget *parent) : QWidget(parent)
{
    int w,h;
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    w=screenRect.width();
    h=screenRect.height();
    len = w < h ? w : h;
    len = len * 5 / 6;
    l_cell = len / 16;
    setFixedSize(len,len);
    move((w-len)/2 , (h-len)/2);
}

void MainBody::recv()
{
    socket->read(data,2);
    qDebug()<<"get:"<<(int)data[0]<< (int)data[1] << endl;
    
    if(my_turn)
    {
    }
    else
    {
        is_black = (int)data[0] ^ 1;
        pre();
    }
}

void MainBody::game_start(bool isServer ,QTcpSocket* _socket)
{
    show();
    socket = _socket;
    is_server = isServer;
    connect(socket,SIGNAL(readyRead()),this,SLOT(recv()));
    setWindowTitle(QString("Gomoku, you're ")+QString(is_server?"Server":"Client"));
    my_turn=0;
    QMessageBox::information(this,"Gomoku","Game is going to begin,are you ready?",QMessageBox::Yes);
    if(isServer)
    {
        srand(clock());
        is_black = rand() % 2;
        data[0] = (char)is_black;
        socket->write(data,2);
        pre();
    }
}
void MainBody::pre()
{
    setWindowTitle(QString( is_black?"Black, ":"White, ") + QString(is_server?"Server":"Client"));
    my_turn = 2 - is_black;
}

void MainBody::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::gray);
    for(int i=1;i<=14;++i)
        for(int j=1;j<=14;++j)
            p.drawRect(l_cell*i+1,l_cell*j+1,l_cell,l_cell);
    p.setBrush(Qt::black);
    p.drawChord(l_cell*4 - l_cell/6 +1,l_cell*4 - l_cell/6 +1,l_cell/3,l_cell/3,0,16*360);
    p.drawChord(l_cell*12 - l_cell/6 +1,l_cell*4 - l_cell/6 +1,l_cell/3,l_cell/3,0,16*360);
    p.drawChord(l_cell*4 - l_cell/6 +1,l_cell*12 - l_cell/6 +1,l_cell/3,l_cell/3,0,16*360);
    p.drawChord(l_cell*12 - l_cell/6 +1,l_cell*12 - l_cell/6 +1,l_cell/3,l_cell/3,0,16*360);
    p.drawChord(l_cell*8 - l_cell/6 +1,l_cell*8 - l_cell/6 +1,l_cell/3,l_cell/3,0,16*360);

    for(int i=1;i<=15;++i)
        for(int j=1;j<=15;++j)
            if(status[i][j])
            {
                p.setPen
            }


}


void MainBody::mouseReleaseEvent(QMouseEvent *event)
{
    if(my_turn==1)
    {   int x,y,i,j;
        x = event->pos().x();
        y = event->pos().y();
        i = (x + l_cell/2) / l_cell ;
        j = (y + l_cell/2) / l_cell;
        if(abs(i * l_cell - x) < l_cell/4  && abs(j * -l_cell - y) < l_cell/4)
            if(status[i][j] == 0)
            {
                status[i][j] = 2 - is_black;
                data[0] = (char)i;data[1]=(char)j;
                my_turn=2;
                socket->write(data,2);
            }
    }
    else
        QMessageBox::about(this,"please wait a moment","Not now!.");
}

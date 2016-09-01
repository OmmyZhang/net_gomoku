#include "mainbody.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>

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

void MainBody::game_start(bool isServer ,QTcpSocket* socket)
{
    show();
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


}

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

    go_i[0]=-1;go_j[0]=-1;
    go_i[1]=-1;go_j[1]=0;
    go_i[2]=-1;go_j[2]=1;
    go_i[3]=0; go_j[3]=1; 
    go_i[4]=1; go_j[4]=1;
    go_i[5]=1; go_j[5]=0;
    go_i[6]=1; go_j[6]=-1;
    go_i[7]=0; go_j[7]=-1;
}

void MainBody::recv()
{
    socket->read(data,2);
    qDebug()<<"get:"<<(int)data[0]<< (int)data[1] << endl;
    
    if(my_turn)
    {
        int i = (int)data[0];
        int j = (int)data[1];
        status[i][j] = 1 + is_black;
        update();
        check(i,j);
        my_turn = 1;

        danger=false; 
        for(int i=1;i<=15;++i)
            for(int j=1;j<=15;++j)
                if(status[i][j] == 0)
                    danger |= (is_danger[i][j] = test(i,j,is_black+1));
                else
                    is_danger[i][j]=false;
        update();
        if(danger)
            QMessageBox::warning(this,"Dangerous!","Look at the red circles!");
                    
    }
    else
    {
        is_black = (int)data[0] ^ 1;
        pre();
    }
}
void MainBody::dic()
{
    qDebug() << "befor_dis" << endl;
    QMessageBox::warning(this,"!!","Disconnected!");
    qDebug() << "dis" <<endl;
    hide();
    emit game_over();

}
void MainBody::game_start(bool isServer ,QTcpSocket* _socket)
{
    for(int i=1;i<=15;++i)
        for(int j=1;j<=15;++j)
            status[i][j]=is_danger[i][j]=0;
    show();
    socket = _socket;
    is_server = isServer;
    connect(socket,SIGNAL(readyRead()),this,SLOT(recv()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(dic()));
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
    update();
}

void MainBody::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(QColor(80,80,80));
    p.setFont(QFont("Comic Sans MS",26,2));
    QString words;
    switch( my_turn)
    {
        case 0:words="Someone is not ready";break;
        case 1:words="your turn";break;
        case 2:words="your opponent's turn";
    }
    p.drawText(l_cell,l_cell-10,words);

    p.setPen(Qt::black);
    p.setBrush(Qt::lightGray);
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
                QPixmap pic(status[i][j]==1?"pic/black.png":"pic/white3.png");
                p.drawPixmap(l_cell*i - l_cell*5/12 +1,l_cell*j - l_cell*5/12 +1,l_cell*5/6,l_cell*5/6,pic,0,0,0,0);
            }
            else
                if(is_danger[i][j])
                {
                    p.setPen(Qt::red);
                    p.setBrush(Qt::red);
                    p.drawArc(l_cell*i - l_cell*5/12 +1,l_cell*j - l_cell*5/12 +1,l_cell*5/6,l_cell*5/6,0,360*16);
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
        qDebug() << x << y << i <<j  <<endl;
        if(abs(i * l_cell - x) < l_cell/4  && abs(j * l_cell - y) < l_cell/4)
            if(status[i][j] == 0)
            {
                qDebug() << i << j <<endl;
                status[i][j] = 2 - is_black;
                data[0] = (char)i;data[1]=(char)j;
                socket->write(data,2);
                update();
                check(i,j);
                my_turn=2;
            }
    }
    else
        QMessageBox::about(this,"please wait","___Not now!___");
}


void MainBody::check(int i,int j)
{
    int col = status[i][j];
    qDebug() << i << j << ":" << col << endl;

    int l[8];
    for(int d=0;d<8;++d)
        l[d] = go_ahead(i,j,go_i[d],go_j[d],col);
    for(int d=0;d<4;++d)
        if(l[d] + l[d+4] >= 60)
            win_or_lost(col == 2-is_black);

}

bool MainBody::test(int i,int j,int col)
{
    int l[8],ds=0;
    for(int d=0;d<8;++d)
        l[d] = go_ahead(i+go_i[d],j+go_j[d],go_i[d],go_j[d],col);
    for(int d=0;d<4;++d)
        if(l[d] + l[d+4] == 22 || l[d] + l[d+4] == 31)
            ++ds;
    return ds>1;
            
}

int MainBody::go_ahead(int i,int j,int go_ii,int go_jj,int col)
{
    if(i == 0 || j == 0 || i>15 || j>15) return 0;
    if(status[i][j] == 0) return 1;
    if(status[i][j] == col)
        return 10 + go_ahead(i+go_ii,j+go_jj,go_ii,go_jj,col);
    else
        return 0;
}

void MainBody::win_or_lost(bool win)
{
    disconnect(socket,SIGNAL(disconnected()),this,SLOT(dic()));
    if(win)
        QMessageBox::about(this,"Congratulations","_____You win!_______");
    else
        QMessageBox::about(this,"Sad story","_____You lose!_______");
    hide();
    emit game_over();
}

#ifndef MAINBODY_H
#define MAINBODY_H

#include <QWidget>
#include <QTcpSocket>

class MainBody : public QWidget
{
    Q_OBJECT
public:
    explicit MainBody(QWidget *parent = 0);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    int len;
    int l_cell;
    int status[16][16]; // 1:black,2:white
    bool is_black,is_server;
    int my_turn; //0:not ready,1:my,2:other's
    QTcpSocket *socket;
    char data[2];

    void pre();

signals:
    void game_over(bool isServer);

public slots:
    void game_start(bool isServer ,QTcpSocket* socket);
    void recv();
};

#endif // MAINBODY_H

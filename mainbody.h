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
    int go_i[8],go_j[8];
    bool is_black,is_server,danger,is_danger[16][16];
    int my_turn; //0:not ready,1:my,2:other's
    QTcpSocket *socket;
    char data[2];

    void pre();
    void check(int i,int j);
    bool test(int i,int j,int col);
    int go_ahead(int i,int j,int go_ii,int go_jj,int col);

signals:
    void game_over();

public slots:
    void game_start(bool isServer ,QTcpSocket* socket);
private slots:
    void dic();
    void win_or_lost(bool win); 
    void recv();
};

#endif // MAINBODY_H

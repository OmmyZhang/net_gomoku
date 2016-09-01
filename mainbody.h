#ifndef MAINBODY_H
#define MAINBODY_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>

class MainBody : public QWidget
{
    Q_OBJECT
public:
    explicit MainBody(QWidget *parent = 0);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    int len;
    int l_cell;
    int status[16][16];

signals:
    void game_over();

public slots:
    void game_start(bool isServer ,QTcpSocket* socket);
};

#endif // MAINBODY_H

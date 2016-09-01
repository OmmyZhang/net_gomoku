#ifndef BEGIN_H
#define BEGIN_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Begin;
}

class Begin : public QDialog
{
    Q_OBJECT

public:
    explicit Begin(QWidget *parent = 0);
    ~Begin();

private slots:
    void on_sw_toggled(bool);
    void on_send_clicked();
    void socket_ready();
    void server_ready();

signals:
    void start_game(bool isSever,QTcpSocket* socket);

private:
    Ui::Begin *ui;
    void status_init(bool);

    QTcpSocket* socket;
    QTcpServer* server;

};

#endif // BEGIN_H

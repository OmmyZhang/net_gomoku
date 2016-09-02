#include <QNetworkInterface>
#include "begin.h"
#include "ui_begin.h"
#include <QMessageBox>

Begin::Begin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Begin)
{
    ui->setupUi(this);
    ui->sw->setDisabledColor(Qt::red);
    
    socket = new QTcpSocket;
    server = new QTcpServer;

    status_init(0);
}

void Begin::status_init(bool last_time_is_server)
{
    qDebug() << " Is server?" << last_time_is_server <<endl;
/*    
    if(last_time_is_server)
        server->close();
    else
        socket->disconnectFromHost();
*/

    delete socket;
    delete server;
    socket = new QTcpSocket;
    server = new QTcpServer;

    connect(server,SIGNAL(newConnection()),this,SLOT(server_ready()));
    connect(socket,SIGNAL(connected()),this,SLOT(socket_ready()));
    
    show();
    ui->sw->setToggle(false);
    on_sw_toggled(false);

    ui->local_ip->setText(QString("Local IP : \n     IPv4: ") + QNetworkInterface::allAddresses()[2].toString()
            +QString("\n     IPV6: ") + QNetworkInterface::allAddresses()[3].toString());
}

Begin::~Begin()
{
    delete socket;
    delete server;
    delete ui;
}

void Begin::on_sw_toggled(bool server_mod)
{
    if(server_mod)
    {
        ui->send->hide();
        ui->ip->hide();
        ui->lineEdit->hide();
        ui->for_server->show();
        socket->disconnectFromHost();
        server->listen(QHostAddress::Any,9876);
    }
    else
    {
        ui->send->show();
        ui->ip->show();
        ui->lineEdit->show();
        ui->for_server->hide();
        server->close();
    }
}

void Begin::on_send_clicked()
{   
    socket->connectToHost(QHostAddress(ui->lineEdit->text()),9876);
}

void Begin::socket_ready()
{
    qDebug() << "Socket ready" <<endl;
    hide();
    emit start_game(0,socket);
}

void Begin::server_ready()
{
    qDebug() << "Server ready" <<endl;
    hide();

    QTcpSocket *tmp = server->nextPendingConnection();
    server->close();
    emit start_game(1,tmp);
}

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
    status_init(0);
}

void Begin::status_init(bool last_time_is_server)
{
    if(last_time_is_server)
        delete server;
    else
        delete socket;

    show();
    ui->sw->setToggle(false);
    server = new QTcpServer;
    on_sw_toggled(false);

    ui->local_ip->setText(QString("Local IP : \n     IPv4: ") + QNetworkInterface::allAddresses()[2].toString()
            +QString("\n     IPV6: ") + QNetworkInterface::allAddresses()[3].toString());
}

Begin::~Begin()
{
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
        delete socket;
        server = new QTcpServer;
        server->listen(QHostAddress::Any,9876);
        connect(socket,SIGNAL(newConnection()),this,SLOT(server_ready()));
    }
    else
    {
        ui->send->show();
        ui->ip->show();
        ui->lineEdit->show();
        ui->for_server->hide();
        delete server;
        socket = new QTcpSocket;
        connect(socket,SIGNAL(connected()),this,SLOT(socket_ready()));
    }
}

void Begin::on_send_clicked()
{   
    socket->connectToHost(QHostAddress(ui->lineEdit->text()),9876);
}

void Begin::socket_ready()
{
    hide();
    emit start_game(0,socket);
}

void Begin::server_ready()
{
    hide();
    emit start_game(1,server->nextPendingConnection());
}

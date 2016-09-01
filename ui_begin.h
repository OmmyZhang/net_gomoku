/********************************************************************************
** Form generated from reading UI file 'begin.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEGIN_H
#define UI_BEGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <switchcontrol.h>

QT_BEGIN_NAMESPACE

class Ui_Begin
{
public:
    QLineEdit *lineEdit;
    QLabel *ip;
    SwitchControl *sw;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *for_server;
    QLabel *waiting;
    QLabel *local_ip;
    QPushButton *send;

    void setupUi(QDialog *Begin)
    {
        if (Begin->objectName().isEmpty())
            Begin->setObjectName(QStringLiteral("Begin"));
        Begin->resize(270, 140);
        Begin->setMinimumSize(QSize(270, 140));
        Begin->setMaximumSize(QSize(270, 140));
        lineEdit = new QLineEdit(Begin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(100, 50, 91, 21));
        ip = new QLabel(Begin);
        ip->setObjectName(QStringLiteral("ip"));
        ip->setGeometry(QRect(30, 50, 71, 21));
        ip->setTextFormat(Qt::AutoText);
        sw = new SwitchControl(Begin);
        sw->setObjectName(QStringLiteral("sw"));
        sw->setGeometry(QRect(92, 11, 40, 16));
        label_2 = new QLabel(Begin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(135, 10, 81, 18));
        label_3 = new QLabel(Begin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(23, 10, 71, 18));
        for_server = new QGroupBox(Begin);
        for_server->setObjectName(QStringLiteral("for_server"));
        for_server->setGeometry(QRect(10, 10, 261, 121));
        waiting = new QLabel(for_server);
        waiting->setObjectName(QStringLiteral("waiting"));
        waiting->setEnabled(true);
        waiting->setGeometry(QRect(14, 68, 201, 71));
        waiting->setIndent(5);
        local_ip = new QLabel(for_server);
        local_ip->setObjectName(QStringLiteral("local_ip"));
        local_ip->setGeometry(QRect(10, 30, 231, 51));
        send = new QPushButton(Begin);
        send->setObjectName(QStringLiteral("send"));
        send->setGeometry(QRect(90, 90, 90, 26));
        for_server->raise();
        lineEdit->raise();
        ip->raise();
        label_2->raise();
        label_3->raise();
        sw->raise();
        send->raise();

        retranslateUi(Begin);

        QMetaObject::connectSlotsByName(Begin);
    } // setupUi

    void retranslateUi(QDialog *Begin)
    {
        Begin->setWindowTitle(QApplication::translate("Begin", "Start Game", 0));
        lineEdit->setText(QApplication::translate("Begin", "127.0.0.1", 0));
        ip->setText(QApplication::translate("Begin", "Server host:", 0));
        label_2->setText(QApplication::translate("Begin", "Server mod", 0));
        label_3->setText(QApplication::translate("Begin", "Socket mod", 0));
        for_server->setTitle(QString());
        waiting->setText(QApplication::translate("Begin", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600; color:#009688;\">Waiting...</span></p></body></html>", 0));
        local_ip->setText(QApplication::translate("Begin", "Local IP:", 0));
        send->setText(QApplication::translate("Begin", "Send request", 0));
    } // retranslateUi

};

namespace Ui {
    class Begin: public Ui_Begin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEGIN_H

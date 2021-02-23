/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mycombobox.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *MQTT;
    QGroupBox *groupBox_2;
    QPushButton *SubButton;
    QLineEdit *SubEdit;
    QPushButton *UnSubButton;
    QGroupBox *groupBox_14;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_6;
    QLineEdit *ServerIP;
    QGroupBox *groupBox_15;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_7;
    QLineEdit *port;
    QGroupBox *groupBox_16;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_8;
    QLineEdit *username;
    QGroupBox *groupBox_17;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_9;
    QLineEdit *password;
    QGroupBox *groupBox_18;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_10;
    QLineEdit *keeplive;
    QPushButton *MQTTSava;
    QWidget *MODBUS;
    QGroupBox *groupBox_9;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *BoundComBox_3;
    QLabel *label_11;
    QGroupBox *groupBox_10;
    QHBoxLayout *horizontalLayout_8;
    QComboBox *dataComBox_6;
    QLabel *label_12;
    QGroupBox *groupBox_11;
    QHBoxLayout *horizontalLayout_9;
    QComboBox *CheckComBox_5;
    QLabel *label_13;
    QGroupBox *groupBox_12;
    QHBoxLayout *horizontalLayout_10;
    QComboBox *StopComBox_4;
    QLabel *label_14;
    QPushButton *ModbusSave;
    QWidget *Serial;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    MyComboBox *PortComBox;
    QLabel *label;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QComboBox *BoundComBox_2;
    QLabel *label_2;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *dataComBox_5;
    QLabel *label_5;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *CheckComBox_4;
    QLabel *label_4;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *StopComBox_3;
    QLabel *label_3;
    QGroupBox *groupBox_13;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton;
    QPushButton *cleanbutton;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *SerialButton;
    QPushButton *MQTTButton;
    QPushButton *ModbusButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(678, 636);
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 70, 661, 611));
        MQTT = new QWidget();
        MQTT->setObjectName(QString::fromUtf8("MQTT"));
        groupBox_2 = new QGroupBox(MQTT);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(40, 380, 591, 81));
        SubButton = new QPushButton(groupBox_2);
        SubButton->setObjectName(QString::fromUtf8("SubButton"));
        SubButton->setGeometry(QRect(390, 30, 75, 23));
        SubEdit = new QLineEdit(groupBox_2);
        SubEdit->setObjectName(QString::fromUtf8("SubEdit"));
        SubEdit->setGeometry(QRect(10, 30, 341, 31));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SubEdit->sizePolicy().hasHeightForWidth());
        SubEdit->setSizePolicy(sizePolicy);
        UnSubButton = new QPushButton(groupBox_2);
        UnSubButton->setObjectName(QString::fromUtf8("UnSubButton"));
        UnSubButton->setGeometry(QRect(480, 30, 75, 23));
        groupBox_14 = new QGroupBox(MQTT);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        groupBox_14->setGeometry(QRect(60, 10, 451, 61));
        horizontalLayout_12 = new QHBoxLayout(groupBox_14);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_6 = new QLabel(groupBox_14);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_12->addWidget(label_6);

        ServerIP = new QLineEdit(groupBox_14);
        ServerIP->setObjectName(QString::fromUtf8("ServerIP"));
        sizePolicy.setHeightForWidth(ServerIP->sizePolicy().hasHeightForWidth());
        ServerIP->setSizePolicy(sizePolicy);
        ServerIP->setSizeIncrement(QSize(0, 0));

        horizontalLayout_12->addWidget(ServerIP);

        groupBox_15 = new QGroupBox(MQTT);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        groupBox_15->setGeometry(QRect(60, 70, 451, 61));
        horizontalLayout_13 = new QHBoxLayout(groupBox_15);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_7 = new QLabel(groupBox_15);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_13->addWidget(label_7);

        port = new QLineEdit(groupBox_15);
        port->setObjectName(QString::fromUtf8("port"));
        sizePolicy.setHeightForWidth(port->sizePolicy().hasHeightForWidth());
        port->setSizePolicy(sizePolicy);

        horizontalLayout_13->addWidget(port);

        groupBox_16 = new QGroupBox(MQTT);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        groupBox_16->setGeometry(QRect(60, 140, 451, 61));
        horizontalLayout_14 = new QHBoxLayout(groupBox_16);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_8 = new QLabel(groupBox_16);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_14->addWidget(label_8);

        username = new QLineEdit(groupBox_16);
        username->setObjectName(QString::fromUtf8("username"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(username->sizePolicy().hasHeightForWidth());
        username->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(username);

        groupBox_17 = new QGroupBox(MQTT);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        groupBox_17->setGeometry(QRect(60, 210, 451, 61));
        horizontalLayout_15 = new QHBoxLayout(groupBox_17);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_9 = new QLabel(groupBox_17);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_15->addWidget(label_9);

        password = new QLineEdit(groupBox_17);
        password->setObjectName(QString::fromUtf8("password"));
        sizePolicy.setHeightForWidth(password->sizePolicy().hasHeightForWidth());
        password->setSizePolicy(sizePolicy);

        horizontalLayout_15->addWidget(password);

        groupBox_18 = new QGroupBox(MQTT);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        groupBox_18->setGeometry(QRect(60, 280, 451, 61));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_18->sizePolicy().hasHeightForWidth());
        groupBox_18->setSizePolicy(sizePolicy2);
        horizontalLayout_16 = new QHBoxLayout(groupBox_18);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_10 = new QLabel(groupBox_18);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_16->addWidget(label_10);

        keeplive = new QLineEdit(groupBox_18);
        keeplive->setObjectName(QString::fromUtf8("keeplive"));
        sizePolicy.setHeightForWidth(keeplive->sizePolicy().hasHeightForWidth());
        keeplive->setSizePolicy(sizePolicy);

        horizontalLayout_16->addWidget(keeplive);

        MQTTSava = new QPushButton(MQTT);
        MQTTSava->setObjectName(QString::fromUtf8("MQTTSava"));
        MQTTSava->setGeometry(QRect(520, 160, 131, 41));
        stackedWidget->addWidget(MQTT);
        MODBUS = new QWidget();
        MODBUS->setObjectName(QString::fromUtf8("MODBUS"));
        groupBox_9 = new QGroupBox(MODBUS);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(60, 50, 261, 85));
        horizontalLayout_7 = new QHBoxLayout(groupBox_9);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        BoundComBox_3 = new QComboBox(groupBox_9);
        BoundComBox_3->addItem(QString());
        BoundComBox_3->addItem(QString());
        BoundComBox_3->addItem(QString());
        BoundComBox_3->setObjectName(QString::fromUtf8("BoundComBox_3"));

        horizontalLayout_7->addWidget(BoundComBox_3);

        label_11 = new QLabel(groupBox_9);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_7->addWidget(label_11);

        groupBox_10 = new QGroupBox(MODBUS);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(60, 160, 261, 85));
        horizontalLayout_8 = new QHBoxLayout(groupBox_10);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        dataComBox_6 = new QComboBox(groupBox_10);
        dataComBox_6->addItem(QString());
        dataComBox_6->addItem(QString());
        dataComBox_6->addItem(QString());
        dataComBox_6->addItem(QString());
        dataComBox_6->setObjectName(QString::fromUtf8("dataComBox_6"));

        horizontalLayout_8->addWidget(dataComBox_6);

        label_12 = new QLabel(groupBox_10);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_8->addWidget(label_12);

        groupBox_11 = new QGroupBox(MODBUS);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(60, 270, 261, 85));
        horizontalLayout_9 = new QHBoxLayout(groupBox_11);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        CheckComBox_5 = new QComboBox(groupBox_11);
        CheckComBox_5->addItem(QString());
        CheckComBox_5->addItem(QString());
        CheckComBox_5->addItem(QString());
        CheckComBox_5->setObjectName(QString::fromUtf8("CheckComBox_5"));

        horizontalLayout_9->addWidget(CheckComBox_5);

        label_13 = new QLabel(groupBox_11);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_9->addWidget(label_13);

        groupBox_12 = new QGroupBox(MODBUS);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setGeometry(QRect(60, 380, 261, 85));
        horizontalLayout_10 = new QHBoxLayout(groupBox_12);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        StopComBox_4 = new QComboBox(groupBox_12);
        StopComBox_4->addItem(QString());
        StopComBox_4->addItem(QString());
        StopComBox_4->addItem(QString());
        StopComBox_4->setObjectName(QString::fromUtf8("StopComBox_4"));

        horizontalLayout_10->addWidget(StopComBox_4);

        label_14 = new QLabel(groupBox_12);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_10->addWidget(label_14);

        ModbusSave = new QPushButton(MODBUS);
        ModbusSave->setObjectName(QString::fromUtf8("ModbusSave"));
        ModbusSave->setGeometry(QRect(400, 190, 111, 51));
        stackedWidget->addWidget(MODBUS);
        Serial = new QWidget();
        Serial->setObjectName(QString::fromUtf8("Serial"));
        textBrowser = new QTextBrowser(Serial);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(210, 20, 441, 531));
        groupBox_7 = new QGroupBox(Serial);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(0, 10, 201, 481));
        verticalLayout = new QVBoxLayout(groupBox_7);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(groupBox_7);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        PortComBox = new MyComboBox(groupBox);
        PortComBox->setObjectName(QString::fromUtf8("PortComBox"));

        horizontalLayout_2->addWidget(PortComBox);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setTextFormat(Qt::RichText);

        horizontalLayout_2->addWidget(label);


        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(groupBox_7);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BoundComBox_2 = new QComboBox(groupBox_3);
        BoundComBox_2->addItem(QString());
        BoundComBox_2->addItem(QString());
        BoundComBox_2->addItem(QString());
        BoundComBox_2->setObjectName(QString::fromUtf8("BoundComBox_2"));

        horizontalLayout->addWidget(BoundComBox_2);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);


        verticalLayout->addWidget(groupBox_3);

        groupBox_6 = new QGroupBox(groupBox_7);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_6);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        dataComBox_5 = new QComboBox(groupBox_6);
        dataComBox_5->addItem(QString());
        dataComBox_5->addItem(QString());
        dataComBox_5->addItem(QString());
        dataComBox_5->addItem(QString());
        dataComBox_5->setObjectName(QString::fromUtf8("dataComBox_5"));

        horizontalLayout_5->addWidget(dataComBox_5);

        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);


        verticalLayout->addWidget(groupBox_6);

        groupBox_5 = new QGroupBox(groupBox_7);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        CheckComBox_4 = new QComboBox(groupBox_5);
        CheckComBox_4->addItem(QString());
        CheckComBox_4->addItem(QString());
        CheckComBox_4->addItem(QString());
        CheckComBox_4->setObjectName(QString::fromUtf8("CheckComBox_4"));

        horizontalLayout_4->addWidget(CheckComBox_4);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);


        verticalLayout->addWidget(groupBox_5);

        groupBox_4 = new QGroupBox(groupBox_7);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        StopComBox_3 = new QComboBox(groupBox_4);
        StopComBox_3->addItem(QString());
        StopComBox_3->addItem(QString());
        StopComBox_3->addItem(QString());
        StopComBox_3->setObjectName(QString::fromUtf8("StopComBox_3"));

        horizontalLayout_3->addWidget(StopComBox_3);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);


        verticalLayout->addWidget(groupBox_4);

        groupBox_13 = new QGroupBox(Serial);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        groupBox_13->setGeometry(QRect(10, 490, 191, 61));
        horizontalLayout_11 = new QHBoxLayout(groupBox_13);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        pushButton = new QPushButton(groupBox_13);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_11->addWidget(pushButton);

        cleanbutton = new QPushButton(groupBox_13);
        cleanbutton->setObjectName(QString::fromUtf8("cleanbutton"));

        horizontalLayout_11->addWidget(cleanbutton);

        stackedWidget->addWidget(Serial);
        groupBox_8 = new QGroupBox(Widget);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(0, 0, 681, 71));
        horizontalLayout_6 = new QHBoxLayout(groupBox_8);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        SerialButton = new QPushButton(groupBox_8);
        SerialButton->setObjectName(QString::fromUtf8("SerialButton"));

        horizontalLayout_6->addWidget(SerialButton);

        MQTTButton = new QPushButton(groupBox_8);
        MQTTButton->setObjectName(QString::fromUtf8("MQTTButton"));

        horizontalLayout_6->addWidget(MQTTButton);

        ModbusButton = new QPushButton(groupBox_8);
        ModbusButton->setObjectName(QString::fromUtf8("ModbusButton"));

        horizontalLayout_6->addWidget(ModbusButton);


        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(2);
        SerialButton->setDefault(false);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        groupBox_2->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        SubButton->setText(QApplication::translate("Widget", "\350\256\242\351\230\205\344\270\273\351\242\230", nullptr));
        UnSubButton->setText(QApplication::translate("Widget", "\345\217\226\346\266\210\350\256\242\351\230\205", nullptr));
        groupBox_14->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        label_6->setText(QApplication::translate("Widget", "\345\234\260\345\235\200", nullptr));
        groupBox_15->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        label_7->setText(QApplication::translate("Widget", "\347\253\257\345\217\243", nullptr));
        groupBox_16->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        label_8->setText(QApplication::translate("Widget", "\347\224\250\346\210\267", nullptr));
        groupBox_17->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        label_9->setText(QApplication::translate("Widget", "\345\257\206\347\240\201", nullptr));
        groupBox_18->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        label_10->setText(QApplication::translate("Widget", "\345\277\203\350\267\263\351\227\264\351\232\224", nullptr));
        MQTTSava->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
        groupBox_9->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        BoundComBox_3->setItemText(0, QApplication::translate("Widget", "115200", nullptr));
        BoundComBox_3->setItemText(1, QApplication::translate("Widget", "9600", nullptr));
        BoundComBox_3->setItemText(2, QApplication::translate("Widget", "4800", nullptr));

        label_11->setText(QApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207", nullptr));
        groupBox_10->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        dataComBox_6->setItemText(0, QApplication::translate("Widget", "8", nullptr));
        dataComBox_6->setItemText(1, QApplication::translate("Widget", "7", nullptr));
        dataComBox_6->setItemText(2, QApplication::translate("Widget", "6", nullptr));
        dataComBox_6->setItemText(3, QApplication::translate("Widget", "5", nullptr));

        label_12->setText(QApplication::translate("Widget", "\346\225\260\346\215\256\344\275\215", nullptr));
        groupBox_11->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        CheckComBox_5->setItemText(0, QApplication::translate("Widget", "\346\227\240", nullptr));
        CheckComBox_5->setItemText(1, QApplication::translate("Widget", "\345\245\207\346\240\241\351\252\214", nullptr));
        CheckComBox_5->setItemText(2, QApplication::translate("Widget", "\345\201\266\346\240\241\351\252\214", nullptr));

        label_13->setText(QApplication::translate("Widget", "\346\240\241\351\252\214\344\275\215", nullptr));
        groupBox_12->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        StopComBox_4->setItemText(0, QApplication::translate("Widget", "1", nullptr));
        StopComBox_4->setItemText(1, QApplication::translate("Widget", "1.5", nullptr));
        StopComBox_4->setItemText(2, QApplication::translate("Widget", "2", nullptr));

        label_14->setText(QApplication::translate("Widget", "\345\201\234\346\255\242\344\275\215", nullptr));
        ModbusSave->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
        groupBox_7->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        groupBox->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        label->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267", nullptr));
        groupBox_3->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        BoundComBox_2->setItemText(0, QApplication::translate("Widget", "115200", nullptr));
        BoundComBox_2->setItemText(1, QApplication::translate("Widget", "9600", nullptr));
        BoundComBox_2->setItemText(2, QApplication::translate("Widget", "4800", nullptr));

        label_2->setText(QApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207", nullptr));
        groupBox_6->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        dataComBox_5->setItemText(0, QApplication::translate("Widget", "8", nullptr));
        dataComBox_5->setItemText(1, QApplication::translate("Widget", "7", nullptr));
        dataComBox_5->setItemText(2, QApplication::translate("Widget", "6", nullptr));
        dataComBox_5->setItemText(3, QApplication::translate("Widget", "5", nullptr));

        label_5->setText(QApplication::translate("Widget", "\346\225\260\346\215\256\344\275\215", nullptr));
        groupBox_5->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        CheckComBox_4->setItemText(0, QApplication::translate("Widget", "\346\227\240", nullptr));
        CheckComBox_4->setItemText(1, QApplication::translate("Widget", "\345\245\207\346\240\241\351\252\214", nullptr));
        CheckComBox_4->setItemText(2, QApplication::translate("Widget", "\345\201\266\346\240\241\351\252\214", nullptr));

        label_4->setText(QApplication::translate("Widget", "\346\240\241\351\252\214\344\275\215", nullptr));
        groupBox_4->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        StopComBox_3->setItemText(0, QApplication::translate("Widget", "1", nullptr));
        StopComBox_3->setItemText(1, QApplication::translate("Widget", "1.5", nullptr));
        StopComBox_3->setItemText(2, QApplication::translate("Widget", "2", nullptr));

        label_3->setText(QApplication::translate("Widget", "\345\201\234\346\255\242\344\275\215", nullptr));
        groupBox_13->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        pushButton->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        cleanbutton->setText(QApplication::translate("Widget", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        groupBox_8->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        SerialButton->setText(QApplication::translate("Widget", "\344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        MQTTButton->setText(QApplication::translate("Widget", "MQTT\351\205\215\347\275\256", nullptr));
        ModbusButton->setText(QApplication::translate("Widget", "ModBus\351\205\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

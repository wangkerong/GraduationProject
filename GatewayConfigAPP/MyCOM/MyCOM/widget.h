#ifndef WIDGET_H
#define WIDGET_H

#include "mycombobox.h"
#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QStringList>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QMouseEvent>



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void ReadCom();
    void Subscribe();
    void UnSubscribe();
    void on_pushButton_clicked();
    void MQTTConfig();
    void ModBusConfig();

private:
    Ui::Widget *ui;
    QSerialPort *serial;
    int GetSerailPort(QStringList &list);
    void UpdateAvailablePort(QComboBox *combo_box);
    void SerailPortInit(void);
    void UI_Init(void);
    bool button = true;
};


#endif // WIDGET_H

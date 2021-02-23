#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    UI_Init();

    serial = new QSerialPort;
    connect(serial,&QSerialPort::readyRead,this, &Widget::ReadCom);
    connect(ui->cleanbutton, &QPushButton::clicked ,[=](){ui->textBrowser->clear();});
    connect(ui->UnSubButton, &QPushButton::clicked, this, &Widget::UnSubscribe);
    connect(ui->SubButton,&QPushButton::clicked,this, &Widget::Subscribe);
    connect(ui->PortComBox, &MyComboBox::clicked, [=](){UpdateAvailablePort(ui->PortComBox);});

    //页面切换
    connect(ui->SerialButton,&QPushButton::clicked,[=](){ui->stackedWidget->setCurrentIndex(2);});
    connect(ui->MQTTButton,&QPushButton::clicked,[=](){ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->ModbusButton,&QPushButton::clicked,[=](){ui->stackedWidget->setCurrentIndex(1);});

    //保存配置
    connect(ui->MQTTSava,&QPushButton::clicked,this, &Widget::MQTTConfig);
    connect(ui->ModbusSave,&QPushButton::clicked,this, &Widget::ModBusConfig);
}

void Widget::MQTTConfig()
{
    if(ui->ServerIP->text()==""||ui->port->text()==""||ui->username->text()==""||ui->password->text()==""||ui->keeplive->text()=="")
    {
        QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("错误"), QMessageBox::Yes | QMessageBox::No);
    }
    else {
        QString MQTTConfig;
        MQTTConfig = "MQTTConfig";
        MQTTConfig.append(',');
        MQTTConfig.append(ui->ServerIP->text());
        MQTTConfig.append(',');
        MQTTConfig.append(ui->port->text());
        MQTTConfig.append(',');
        MQTTConfig.append(ui->username->text());
        MQTTConfig.append(',');
        MQTTConfig.append(ui->password->text());
        MQTTConfig.append(',');
        MQTTConfig.append(ui->keeplive->text());
        serial->write(MQTTConfig.toLocal8Bit());
    }


}
void Widget::ModBusConfig()
{
    QString ModBusConfig;
    ModBusConfig = "ModBusConfig";
    ModBusConfig.append(',');
    ModBusConfig.append(ui->BoundComBox_3->currentText());
    ModBusConfig.append(',');
    ModBusConfig.append(ui->dataComBox_6->currentText());
    ModBusConfig.append(',');
    ModBusConfig.append(ui->CheckComBox_5->currentText());
    ModBusConfig.append(',');
    ModBusConfig.append(ui->StopComBox_4->currentText());
    serial->write(ModBusConfig.toLocal8Bit());


}

void Widget::UnSubscribe()
{
    if(ui->SubEdit->text()=="")
    {
        QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("订阅主题为空"), QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        QString sub;
        sub = "UN:";
        sub.insert(3,ui->SubEdit->text());
        sub.append('\0');
        serial->write(sub.toLocal8Bit());
    }

}
void Widget::Subscribe()
{
    if(ui->SubEdit->text()=="")
    {
        QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("主题为空"), QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        QString sub;
        sub = "SUB:";
        sub.insert(4,ui->SubEdit->text());
        sub.append('\0');
        serial->write(sub.toLocal8Bit());
    }
}

void Widget::ReadCom(void)
{
   QByteArray buf;
   buf = serial->readAll();
   if (!buf.isEmpty())
   {
        QString myStrTemp = QString::fromLocal8Bit(buf); //支持中文显示
        QString str = ui->textBrowser->toPlainText();
        str +=myStrTemp;
        ui->textBrowser->clear();
        ui->textBrowser->append(str);
   }
   buf.clear();
}


int Widget::GetSerailPort(QStringList &list)
{
    QSerialPort SerialPort;
    list.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())  //遍历这个链表
    {
        SerialPort.setPort(info);
        list.append(SerialPort.portName());  //将获取的端口号追加在链表后
    }
    return list.size();
}

void Widget::UpdateAvailablePort(QComboBox *combo_box)
{
    QStringList available_port;                                       //链表
    int available_port_num ;    //available_port返回可用端口的链表
     available_port_num =  GetSerailPort(available_port);                                                               //available_port_num端口的数量
    //当串口数量超过2时，将获取所有可用串口，并对其进行从小到大重新排序
    if (available_port_num >= 2)
    {
        int port_value[10];
        for (int i = 0; i < available_port_num; i++)
        {  //获取串口号的number
            QString port_name = available_port.at(i);  //返回字符串中给定索引位置的字符
            port_value[i] = port_name.replace("COM", "").toInt();
        }

        for (int i = 0; i < available_port_num - 1; i++)
        {  //选择排序
            int min_index = i;
            for (int j = i + 1; j <= available_port_num - 1; j++)
            {
                if (port_value[j] < port_value[min_index])
                {
                    min_index = j;
                }
            }
            int temp = port_value[i];
            port_value[i] = port_value[min_index];
            port_value[min_index] = temp;
        }

        for (int i = 0; i < available_port_num; i++)
        {  //排序后的串口号重新加入链表中
            available_port.replace(i, QString("COM%1").arg(port_value[i]));
        }
    }
    //将当前全部串口号加入下拉框中
    combo_box->clear();
    combo_box->addItems(available_port);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_pushButton_clicked()//打开串口槽函数
{
    if(button)
    {
        //COM
        serial->setPortName(ui->PortComBox->currentText());

        //Bound
        serial->setBaudRate(ui->BoundComBox_2->currentText().toInt());

        //Data bit
        switch(ui->dataComBox_5->currentText().toInt())
        {
            case 5: serial->setDataBits(QSerialPort::Data5);  break;
            case 6: serial->setDataBits(QSerialPort::Data6);  break;
            case 7: serial->setDataBits(QSerialPort::Data7);  break;
            case 8: serial->setDataBits(QSerialPort::Data8);  break;
            default :                                        break;
        }

        //Check bit
        if(ui->CheckComBox_4->currentText() == "无")
        {
            serial->setParity(QSerialPort::NoParity);
        }
        else if(ui->CheckComBox_4->currentText() == "奇校验")
        {
            serial->setParity(QSerialPort::OddParity);
        }
        else if(ui->CheckComBox_4->currentText() == "偶校验")
        {
            serial->setParity(QSerialPort::EvenParity);
        }

        //Stop bit
        if(ui->StopComBox_3->currentText() == "1")
        {
            serial->setStopBits(QSerialPort::OneStop);
        }
        else if(ui->StopComBox_3->currentText() == "2")
        {
            serial->setStopBits(QSerialPort::TwoStop);
        }
        else if(ui->StopComBox_3->currentText() == "1.5")
        {
            serial->setStopBits(QSerialPort::OneAndHalfStop);
        }

        //无硬件流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->close();
        bool open = serial->open(QIODevice::ReadWrite);
        if(!open) //以读写的方式打开串口
        {
            QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("串口打开错误"), QMessageBox::Yes | QMessageBox::No);
        }
        else {
            button = false;
            ui->pushButton->setText(QString::fromLocal8Bit("关闭串口"));
            ui->MQTTSava->setEnabled(true);
            ui->ModbusSave->setEnabled(true);
        }
    }
    else {
        button = true;
        ui->pushButton->setText(QString::fromLocal8Bit("打开串口"));
        serial->close();
        }
}

void Widget::UI_Init(void)
{
    QFont font("微软雅黑", 15, 50);
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);
    ui->label_8->setFont(font);
    ui->label_9->setFont(font);
    ui->label_10->setFont(font);
    ui->label_11->setFont(font);
    ui->label_12->setFont(font);
    ui->label_13->setFont(font);
    ui->label_14->setFont(font);
    ui->ServerIP->setFont(font);
    ui->port->setFont(font);
    ui->username->setFont(font);
    ui->password->setFont(font);
    ui->keeplive->setFont(font);
    ui->SubEdit->setFont(font);

    ui->SerialButton->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:25px;color:rgb(0,0,0,255);}QPushButton{background-color:rgb(227,226,228)}QPushButton:hover{background-color:rgb(221, 234, 223)}");
    ui->MQTTButton->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:25px;color:rgb(0,0,0,255);}QPushButton{background-color:rgb(227,226,228)}QPushButton:hover{background-color:rgb(221, 234, 223)}");
    ui->ModbusButton->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:25px;color:rgb(0,0,0,255);}QPushButton{background-color:rgb(227,226,228)}QPushButton:hover{background-color:rgb(221, 234, 223)}");
    ui->pushButton->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:15px;color:rgb(0,0,0,255);}QPushButton{background-color:rgb(227,226,228)}QPushButton:hover{background-color:rgb(221, 234, 223)}");
    ui->cleanbutton->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:15px;color:rgb(0,0,0,255);}QPushButton{background-color:rgb(227,226,228)}QPushButton:hover{background-color:rgb(221, 234, 223)}");
    ui->MQTTSava->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QPushButton{background-color:rgb(227,226,228)}QPushButton:hover{background-color:rgb(221, 234, 223)}");
    ui->ModbusSave->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QPushButton{background-color:rgb(227,226,228)}QPushButton:hover{background-color:rgb(221, 234, 223)}");


    ui->PortComBox->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");
    ui->BoundComBox_2->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");
    ui->StopComBox_3->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");
    ui->dataComBox_5->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");
    ui->CheckComBox_4->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");

    ui->BoundComBox_3->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");
    ui->dataComBox_6->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");
    ui->CheckComBox_5->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");
    ui->StopComBox_4->setStyleSheet("QComboBox{font-family:'微软雅黑';font-size:20px;color:rgb(0,0,0,255);}QComboBox{background-color:rgb(227,226,228)}");


    //ui->ServerIP->setFont(QFont("微软雅黑" , 13 ,  QFont::Normal));
    ui->port->setText("1883");
    setFixedSize(this->width(),this->height());//禁止拉伸窗体


    ui->BoundComBox_3->setCurrentIndex(1);
    ui->keeplive->setText("60");
    ui->MQTTSava->setEnabled(false);
    ui->ModbusSave->setEnabled(false);
}


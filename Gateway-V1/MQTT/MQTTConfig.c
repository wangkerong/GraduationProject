#include "mqttconfig.h"
#include "string.h"
extern USARTEnum UARTEnum; 
extern unsigned char WIFIRecBuf[500];
extern int WIFIRxCont;
bool connectflag = false;
unsigned short PACKDID = 1;
/*****************CONNECT CONFIG*************************/
#define CLEANSESSION    1                           //����Ự��־
#define WILLFLAG        0                           //������־
/*****************SubTheam CONFIG*************************/
#define SUB_QOS         0                           
#define SUB_DUP         '0'
/*****************PUBLISHMESSAGE CONFIG*************************/
#define THEAM_ID        "$baidu/iot/shadow/ESP8266/update"
//#define THEAM_ID        "SW_LED"
#define PUB_QOS         0
#define PUB_DUP         0



void PublishMessage(short int *Temp, short int *Hum)
{
    int messagelen = 0, len = 0;
    unsigned char sendbuf[200];
    unsigned char messagebuf[200];
    unsigned char dup = PUB_DUP;
    int Qos = PUB_QOS;
    unsigned char retained;
    MQTTString topicString;
    unsigned short packetid = PACKDID++;
    topicString.cstring = THEAM_ID;//������ⷢ����Ϣ
    
    sprintf(messagebuf, "{\"desired\":{},\"reported\":{\"Temperature\":%d,\"Humidity\":%d}}", *Temp, *Hum);//JSON��ʽ
    messagelen = strlen(messagebuf);
    len = MQTTSerialize_publish(sendbuf, sizeof(sendbuf), dup, Qos, retained, packetid, topicString, messagebuf, messagelen);
    if(len < 0||len ==0)
    {
        printf("MQTT Publish message error \r\n");
    }
    else
    {
        USART3_Write(sendbuf, len);
    }
    
}



void SubscribeTheam(char *topic)//��������
{
    unsigned char buf[200] = {'\0'};
    int len = 0;
    //������������
    int Qos = SUB_QOS;                    //QOS:��Ϣ�����ȼ�
    unsigned char dup = SUB_DUP;        //dup:�ظ��ַ���־
    unsigned short packetid = PACKDID++;    //id :MQTT����־��
    MQTTString topicString;
	topicString.lenstring.data = topic;   //������������
    topicString.cstring = topic;
    topicString.lenstring.len = MQTTstrlen(topicString);

	len = MQTTSerialize_subscribe((unsigned char *)buf, (int)sizeof(buf), dup, packetid, 1, &topicString, &Qos);

    if(len == 0)
    {
        printf("MQTT subscribe message error \r\n");
    }
    else
    {
        USART3_Write(buf, len);
    }

}

void UnsubscribeThem(char *topic)
{
    int len=0;
    unsigned char sendbuf[200] = {'\0'};
    unsigned char dup = SUB_DUP;
    unsigned short packetid = PACKDID++;
    MQTTString topicString;
    topicString.lenstring.data = topic;   //�˶���������
    topicString.cstring = topic;
    topicString.lenstring.len = MQTTstrlen(topicString);

    len = MQTTSerialize_unsubscribe(sendbuf,sizeof(sendbuf), dup, packetid, 1, &topicString);
    if(len == 0)
    {
        printf("MQTT Unsubscribe message error \r\n");
    }
    else
    {
        USART3_Write(sendbuf, len);
    }
}

void ConnectToServer(char *n, char *p, unsigned short k)
{
    unsigned char sendbuf[500]={'\0'};
    int rec = 0;
    MQTTPacket_connectData client;
    UARTEnum =  MQTTConnect;
    client.struct_id[0] = 'M';
    client.struct_id[1] = 'Q';
    client.struct_id[2] = 'T';
    client.struct_id[3] = 'C';
	client.struct_version = 0;
	client.MQTTVersion = 4;                     //MQTT Version is 3.1.1
	client.clientID.cstring = "STM32";
	client.keepAliveInterval = k;             //�������
	client.cleansession = CLEANSESSION;                    //����Ự
	client.willFlag = WILLFLAG;                        //������־
	client.username.cstring = n;
	client.password.cstring = p;
    rec = MQTTSerialize_connect(sendbuf, 500, &client);   //����
    if(rec == 0){
        printf("MQTT Connect message error \r\n");
    }
    else{
        USART3_Write(sendbuf, rec);
    }
    rec = 0;
    while(!connectflag)
    {
        delay_ms(10);
        rec++;
        if(rec == 700)
        {
            printf("connect mqtt server error\r\n");
            break;
        }
    }
}


//void MQTTInit(void)
//{
//    ConnectToServer();
//    UARTEnum =  Other;
//    SubscribeTheam("$baidu/iot/shadow/ESP8266/update/accepted");
//    delay_ms(100);
    // SubscribeTheam("Temp");
    // delay_ms(100);
    // SubscribeTheam("Beep");
    // delay_ms(100);
    
//}
void KeepLive(void)
{
    unsigned char sendbuf[10];
    int len = 0;
    len = MQTTSerialize_pingreq(sendbuf, strlen(sendbuf));
    USART3_Write(sendbuf, len);
}

void Receive_Connect_Data(void)
{
    unsigned char sessionPresentp[50];
    unsigned char connack_rc[1];
    int rec = 0;
    rec = MQTTDeserialize_connack(sessionPresentp, connack_rc, WIFIRecBuf, 500);
    if(connack_rc[0]==0x00)
    {
        connectflag = true; 
        memset(WIFIRecBuf, 0, sizeof(WIFIRecBuf));
        WIFIRxCont = 0;
        printf("connect mqtt server success\r\n");
    }
    else
    {
        connectflag = false;
        memset(WIFIRecBuf, 0, sizeof(WIFIRecBuf));
        WIFIRxCont = 0;
        printf("connect mqtt server error\r\n");
        printf("error code��%d\r\n",connack_rc[0]);
    }
    

}

void PublishMessageAnalysis(void)
{
    unsigned char *data;
    unsigned char dup, retained;
    int qos, payloadlen, rec;
    unsigned short packetid;
    MyMQTTString topicName;
    memset(topicName.lenstring.data, 0, sizeof(topicName.lenstring.data));
    rec = MQTTDeserialize_publish(&dup, &qos, &retained, &packetid, &topicName,(unsigned char **)&data, &payloadlen, WIFIRecBuf, sizeof(WIFIRecBuf));
    if(rec)
    {
        printf("Topic��%s\r\n",topicName.lenstring.data);
        printf("Message��%s\r\n\r\n",data);
    }
    else
    {
        printf("�������ݳ���");
    }
    
}
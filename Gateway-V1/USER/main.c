#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "wifi.h"
#include "mqttconfig.h"
#include "rs485.h"

extern bool DataReady;
extern u8 flag;
extern unsigned char SUBBUF[100];
extern unsigned char DataBuf[9];
int main(void)
{
    short int temp=0,hum=0;
    u8 change = 0;
	delay_init(168);    
	LED_Init();	   
	USART1_Init(115200);
	USART3_Init(115200);
	while(1)
	{
        
        if(flag ==0x03)//modbusͨ������
        {
            flag = 0;
            ModBusConfig();
            memset(SUBBUF ,0, sizeof(SUBBUF));
            change++;
            
        }
        if(flag ==0x04)//MQTT�ͻ�������
        {
            flag = 0;
            MQTTClientConfig();
            memset(SUBBUF ,0, sizeof(SUBBUF));
            change++;
            
        }
        //�������
        if(change ==0x02)
        {
            WriteData(0x01, 0x03, 0x0000, 0x0002);//��ȡModbusЭ���ʽ����ʪ������
            
            if(flag == 0x01)//��������
            {
                flag = 0;
                SubscribeTheam(SUBBUF+4);
                memset(SUBBUF ,0, sizeof(SUBBUF));
            }
            if(flag ==0x02)//�˶�����
            {
                flag = 0;
                UnsubscribeThem(SUBBUF+3);
                memset(SUBBUF ,0, sizeof(SUBBUF));
            }
            
            if(DataReady)//������Ϣ
            {
                if(GetHumAndTemp(DataBuf, &temp, &hum))
                {
                    //printf("ʪ��:%dRH, �¶�:%d��\r\n", hum, temp);
                    memset(DataBuf ,0 ,sizeof(DataBuf));
                    DataReady = false;
                    PublishMessage(&temp,&hum);
               
                }
            }
            
        }
		delay_ms(1000);
    
		//KeepLive();//��������
        LED0 = !LED0;
	}
}


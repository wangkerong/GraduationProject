#include "WIFI.h"
bool ATRecState = false;
extern USARTEnum UARTEnum;
extern char WIFIRecBuf[500];
extern unsigned char SUBBUF[150];
extern int WIFIRxCont;

void USART3_Write(unsigned char *cmd, int len)
{
    int i;
	USART_ClearFlag(USART3,USART_FLAG_TC);    //发送之前清空发送标志  
	for(i=0;i<len;i++)
	{
        USART_SendData(USART3,*cmd);   //发送当前数据
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
        cmd++;      //指针自加 准备发送下一个数据	   
	}
 
}


int WIFISendAT(unsigned char *at, unsigned char *ack)
{
	int timeout = 0;
    memset(WIFIRecBuf, 0, sizeof(WIFIRecBuf));
	WIFIRxCont = 0;
	ATRecState = false;
	USART3_Write(at, strlen(at));
	while(1)
	{
		while(!ATRecState)
		{
			timeout++;
			delay_ms(1);
			if(timeout>=7000)
			{
				memset(WIFIRecBuf, 0, sizeof(WIFIRecBuf));
				printf("%s error\r\n",at);
				return 1;
			}
		}
		timeout=0;
		if(strstr((const char *)WIFIRecBuf, (const char *)ack) != NULL)
		{
			memset(WIFIRecBuf, 0, sizeof(WIFIRecBuf));
			return 0;
		}
	}    
}

void WIFIInit(unsigned char *p)
{
    int rec = 0;
    UARTEnum = AT_START;
	USART3_Write((unsigned char *)"+++", 3);  //退出透传
	delay_ms(100);
    rec |= WIFISendAT((unsigned char *)"AT+RST\r\n", (unsigned char *)"OK");
	delay_ms(500);
    rec |= WIFISendAT((unsigned char *)"AT+CWMODE=1\r\n", (unsigned char *)"OK");
    rec |= WIFISendAT((unsigned char *)"AT+CWJAP=\"MI6\",\"w2585651242\"\r\n", (unsigned char *)"OK");
    rec |= WIFISendAT(p, (unsigned char *)"OK");
    rec |= WIFISendAT((unsigned char *)"AT+CIPMODE=1\r\n", (unsigned char *)"OK");
    rec |= WIFISendAT((unsigned char *)"AT+CIPSEND\r\n", (unsigned char *)"OK");  //透传
    if(rec){
        printf("WIFI 初始化错误\r\n");
    }
    else{
        printf("WIFI 初始化完成\r\n");
    }
}

void MQTTClientConfig(void)
{
    unsigned char buf[100]={0};
    char *p = NULL,*n = NULL;
    unsigned short KeepLive=0;
    p = strtok((char *)SUBBUF,",");
    strcat(buf,"AT+CIPSTART=\"TCP\",\"");
    strcat(buf,strtok(NULL,","));
    strcat(buf,"\",");
    strcat(buf,strtok(NULL,","));
    strcat(buf,"\r\n");
    WIFIInit(buf);
    n = strtok(NULL,",");//用户名
    p = strtok(NULL,",");//密码
    KeepLive = (unsigned  short)atoi(strtok(NULL,","));
    ConnectToServer(n, p ,KeepLive);
    UARTEnum =  Other;
}


void Receive_AT_Data(void)
{
	ATRecState = true;
	WIFIRxCont=0;     			
}
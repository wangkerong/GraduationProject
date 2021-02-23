#include "rs485.h"
unsigned char DataBuf[9]={0};
char cnt =0;
bool DataReady = false;
extern unsigned char SUBBUF[150];
void ModBusConfig(void)
{
    int bound,data,stop;
    char *p=NULL;
    p = strtok((char *)SUBBUF,",");
    bound = atoi((const char *)strtok(NULL,","));
    data  = atoi((const char *)strtok(NULL,","));
    p     = strtok(NULL,",");
    stop  = atoi((const char *)strtok(NULL,","));
    RS485_Init(bound, data, stop, p);
}
void RS485_Init(int bound, int data, int stop, char *p)
{  	 
	
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);  //ʹ��GPIOGʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
  //����2���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//USART2    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3
	
	//PG8���������485ģʽ����  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //GPIOG8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOG,&GPIO_InitStructure); //��ʼ��PG8
	

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
    switch(data)
    {
        case 9 :USART_InitStructure.USART_WordLength = USART_WordLength_9b;break;
        case 8 :USART_InitStructure.USART_WordLength = USART_WordLength_8b;break;
        default:USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    }
    switch(stop)
    {
        case 1 :USART_InitStructure.USART_StopBits = USART_StopBits_1;break;
        case 2 :USART_InitStructure.USART_StopBits = USART_StopBits_2;break;
        default:USART_InitStructure.USART_StopBits = USART_StopBits_1;
    }
    if(strcmp(p,"��")==0)
    {
        USART_InitStructure.USART_Parity = USART_Parity_No; 
    }
    if(strcmp(p,"��У��")==0)
    {
        USART_InitStructure.USART_Parity = USART_Parity_Odd;        
    }
    if(strcmp(p,"żУ��")==0)
    {
        USART_InitStructure.USART_Parity = USART_Parity_Even;
    }    
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
    USART_Cmd(USART2, ENABLE);  //ʹ�ܴ��� 2
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
	
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//���������ж�
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//�����ж�ʹ��

	//Usart2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
	RS485_TX_EN=0;				//Ĭ��Ϊ����ģʽ
    printf("RS485 Config Finish\r\n");
}


void USART2_IRQHandler(void)
{
    u8 rec=0;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        USART_ClearFlag(USART2,USART_IT_RXNE);
        rec = USART_ReceiveData(USART2);
        DataBuf[cnt++]= rec;
    }
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        char temp;
        temp = USART2->SR; 
        temp = USART2->DR;
        DataReady = true;
        cnt = 0;
    }
    
}
void WriteData(u8 addr, u8  ControlCode, u16 registeraddr, u16 data)
{
	u8 buf[8]={0};
	u32 i =0;
	unsigned short crc=0;
    unsigned short siRet = 0;
	buf[0] = addr;
	buf[1] = ControlCode;
	buf[2] = (u8)((registeraddr&0XFF00)>>8);
	buf[3] = (u8)(registeraddr&0X00FF);
	buf[4] = (u8)((data&0XFF00)>>8);
	buf[5] = (u8)(data&0X00FF);
	crc = CheckCRC(buf, 6);
	buf[6] = (u8)((crc&0XFF00)>>8);
	buf[7] = (u8)(crc&0X00FF);
    RS485_TX_EN = 1;                //����Ϊ����ģʽ
	USART_ClearFlag(USART2,USART_FLAG_TC);    //����֮ǰ��շ��ͱ�־  
	for(i=0;i<sizeof(buf);i++)
	{
        USART_SendData(USART2,buf[i]); 
        while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //�ȴ����ͽ���     
	}
    RS485_TX_EN = 0;				//����Ϊ����ģʽ
}

unsigned short CheckCRC(unsigned char *pData,unsigned int siLen)
{
    int i =0, j = 0;
    unsigned short u16CRC = 0xFFFF;
    unsigned short siRet = 0;
	if (siLen <= 0)
	{
		return 0;
	}
	for (i = 0; i < siLen; i++)
	{
		u16CRC ^= (unsigned short)(pData[i]);
		for(j = 0; j <= 7; j++)
		{
			if (u16CRC & 0x0001)
			{
				u16CRC = (u16CRC >> 1) ^ 0xA001;
			}
			else
			{
				u16CRC = u16CRC >> 1;  
			}
		}
	}
	siRet = (u16CRC & 0x00FF) << 8; 
	siRet |= u16CRC >> 8;	
	return siRet;
}

int GetHumAndTemp(unsigned char *buf, short int *temp, short int *hum)
{
	u8 addr,ControlCode;
	unsigned short crc = 0,num = 0;
	crc = CheckCRC(buf, 7);
	if((*(buf+7) != ((crc&0xFF00)>>8))||(*(buf+8) != (crc&0xFF)))
	{
		return 0;	//����֡����
	}
	addr = *buf;
	ControlCode = *(buf+1);
	num = *(buf+2);

	*hum = ((short int)((*(buf+3)<<8)+*(buf+4)))/10.0;
	*temp = ((*(buf+5)<<8)+*(buf+6))/10.0;
	return 1;
}



int isspace(int x)
{
 if(x==' '||x=='\t'||x=='\n'||x=='\f'||x=='\b'||x=='\r')
  return 1;
 else 
  return 0;
}
int isdigit(int x)
{
 if(x<='9'&&x>='0')        
  return 1;
 else
  return 0;

}
int atoi(const char *nptr)
{
        int c;              /* current char */
        int total;         /* current total */
        int sign;           /* if '-', then negative, otherwise positive */

        /* skip whitespace */
        while ( isspace((int)(unsigned char)*nptr) )
            ++nptr;

        c = (int)(unsigned char)*nptr++;
        sign = c;           /* save sign indication */
        if (c == '-' || c == '+')
            c = (int)(unsigned char)*nptr++;    /* skip sign */

        total = 0;

        while (isdigit(c)) {
            total = 10 * total + (c - '0');     /* accumulate digit */
            c = (int)(unsigned char)*nptr++;    /* get next char */
        }

        if (sign == '-')
            return -total;
        else
            return total;   /* return result, negated if necessary */
}
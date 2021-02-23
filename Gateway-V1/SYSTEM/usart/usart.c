#include "sys.h"
#include "usart.h"
#include "mqttconfig.h"

unsigned char SUBBUF[150];      //������λ�����ݻ�����
unsigned char WIFIRecBuf[500];   //wifi���ܻ�����
int WIFIRxCont=0;        //wifi�������ݼ���
u16 SUBCont = 0;		//������λ�����ݼ���
USARTEnum UARTEnum;
u8 flag = 0;

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 

void USART1_Init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
	 
	//����1��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
		
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10
    //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
		
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�����ж�ʹ��
	

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}


void USART3_Init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
	
	//����3��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	
    //USART3�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOA10��GPIOA11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PB10��PB11
	
		
	//USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ 
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
    
    USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3 
    USART_ClearFlag(USART3, USART_FLAG_TC);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
	/*********************************************************************************************************************************************************************/
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//�����ж�ʹ��
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���	

}

void USART1_IRQHandler(void)            
{
	u8 rec,temp;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{   
        rec = USART_ReceiveData(USART1);
		SUBBUF[SUBCont] = rec;
		SUBCont++;
		if(SUBCont>150)
		{
			printf("error:Message length too long\r\n");
			SUBCont =0;
		}
        USART_ClearFlag(USART1,USART_IT_RXNE);
	}
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)//�����ж�
    {

        temp = USART1->SR; 
        temp = USART1->DR;
		if(strstr((char *)SUBBUF,"SUB:")!=NULL)
		{
			flag = 0x01;
            SUBCont = 0;
		}
		else if(strstr((char *)SUBBUF,"UN:")!=NULL)
		{
			flag = 0x02;
			SUBCont =0;
		}
        else if(strstr((char *)SUBBUF,"ModBusConfig")!=NULL)
		{
            flag = 0x03;
            SUBCont =0;
            printf("ModBusConfig\r\n");
			
		}
        else if(strstr((char *)SUBBUF,"MQTTConfig")!=NULL)
		{
            flag = 0x04;
            SUBCont =0;
            printf("MQTTConfig\r\n");
			
		}
		else
		{
			SUBCont =0;
			memset(SUBBUF,0,sizeof(SUBBUF));
		}
		
		
		
	}
		
}

void USART3_IRQHandler(void)
{
    u8 res;
	u8 temp;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		//printf("%c", USART_ReceiveData(USART3));
        res = USART_ReceiveData(USART3);
        WIFIRecBuf[WIFIRxCont] = res;
		WIFIRxCont++;
		if(WIFIRxCont > 999)
		{
			WIFIRxCont = 0;
		}
        USART_ClearFlag(USART3,USART_IT_RXNE);
	}
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)//���������ݺ��������ж�
    {

        temp = USART3->SR; //�ȶ�SR,�ٶ�DR�������idle�жϵ����㣬�����һֱ�����жϡ�
        temp = USART3->DR;
		  /*ATָ���µĴ������ݴ���*/
        if(UARTEnum == AT_START)
        Receive_AT_Data();
        /*connect���ӱ������ݵĴ���*/
        if(UARTEnum == MQTTConnect)
		Receive_Connect_Data();
		if(UARTEnum == Other)
		{
			if(WIFIRecBuf[0] == 0XD0)//���������Ӧ
			{
				memset(WIFIRecBuf,0,sizeof(WIFIRecBuf));
            	WIFIRxCont = 0;
				//printf("����������Ӧ\r\n");
			}
			if(WIFIRecBuf[0] == 0x90)//��������ɹ���Ӧ
			{
				printf("���ⶩ��ȷ��\r\n\r\n");
				memset(WIFIRecBuf,0,sizeof(WIFIRecBuf));
            	WIFIRxCont = 0;   
			}
			if((WIFIRecBuf[0]&0XF0) == 0X30)//�յ�������Ϣ
			{
				PublishMessageAnalysis();
                memset(WIFIRecBuf,0,sizeof(WIFIRecBuf));
            	WIFIRxCont = 0; 
			}
			if(WIFIRecBuf[0] == 0xB0)//�����˶��ɹ�
			{
				printf("�����˶��ɹ�\r\n\r\n");
				memset(WIFIRecBuf,0,sizeof(WIFIRecBuf));
            	WIFIRxCont = 0;
			}
            

		}

    }
	
}


 




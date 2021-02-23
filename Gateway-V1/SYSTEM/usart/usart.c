#include "sys.h"
#include "usart.h"
#include "mqttconfig.h"

unsigned char SUBBUF[150];      //接收上位机数据缓冲区
unsigned char WIFIRecBuf[500];   //wifi接受缓冲区
int WIFIRxCont=0;        //wifi接受数据计数
u16 SUBCont = 0;		//接收上位机数据计数
USARTEnum UARTEnum;
u8 flag = 0;

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 

void USART1_Init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
	 
	//串口1对应引脚复用映射
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
		
	//USART1端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10
    //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
		
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//空闲中断使能
	

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
}


void USART3_Init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
	
	//串口3对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
	
    //USART3端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOA10与GPIOA11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PB10，PB11
	
		
	//USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式 
	USART_Init(USART3, &USART_InitStructure); //初始化串口3
    
    USART_Cmd(USART3, ENABLE);  //使能串口3 
    USART_ClearFlag(USART3, USART_FLAG_TC);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
	/*********************************************************************************************************************************************************************/
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//空闲中断使能
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器	

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
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)//空闲中断
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
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)//接收完数据后进入空闲中断
    {

        temp = USART3->SR; //先读SR,再读DR才能完成idle中断的清零，否则会一直进入中断。
        temp = USART3->DR;
		  /*AT指令下的串口数据处理*/
        if(UARTEnum == AT_START)
        Receive_AT_Data();
        /*connect连接报文数据的处理*/
        if(UARTEnum == MQTTConnect)
		Receive_Connect_Data();
		if(UARTEnum == Other)
		{
			if(WIFIRecBuf[0] == 0XD0)//心跳请求回应
			{
				memset(WIFIRecBuf,0,sizeof(WIFIRecBuf));
            	WIFIRxCont = 0;
				//printf("心跳请求响应\r\n");
			}
			if(WIFIRecBuf[0] == 0x90)//订阅主题成功回应
			{
				printf("主题订阅确认\r\n\r\n");
				memset(WIFIRecBuf,0,sizeof(WIFIRecBuf));
            	WIFIRxCont = 0;   
			}
			if((WIFIRecBuf[0]&0XF0) == 0X30)//收到主题消息
			{
				PublishMessageAnalysis();
                memset(WIFIRecBuf,0,sizeof(WIFIRecBuf));
            	WIFIRxCont = 0; 
			}
			if(WIFIRecBuf[0] == 0xB0)//主题退订成功
			{
				printf("主题退订成功\r\n\r\n");
				memset(WIFIRecBuf,0,sizeof(WIFIRecBuf));
            	WIFIRxCont = 0;
			}
            

		}

    }
	
}


 




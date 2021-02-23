#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h"
#include "wifi.h"

typedef enum{
    AT_START,
    MQTTConnect,
    Other
}USARTEnum;

void USART1_Init(u32 bound);
void USART3_Init(u32 bound);

#endif



#ifndef _WIFI_H_
#define _WIFI_H_


#include "usart.h"
#include "delay.h"
#include <string.h>
#include "rs485.h"
#include "mqttconfig.h"

void WIFIInit(unsigned char *p);
void Receive_AT_Data(void);
void USART3_Write(unsigned char *cmd, int len);
void MQTTClientConfig(void);

#endif




#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"
#include "delay.h"
#include "string.h"

//模式控制
#define RS485_TX_EN		PGout(8)	//485模式控制.0,接收;1,发送.

#define NULL 0
														 
void RS485_Init(int bound, int data, int stop, char *p);
unsigned short CheckCRC(unsigned char *pData,unsigned int siLen);
void WriteData(u8 addr, u8  ControlCode, u16 registeraddr, u16 data);
int GetHumAndTemp(unsigned char *buf, short int *temp, short int *hum);
int atoi(const char *nptr);
void ModBusConfig(void);
int atoi(const char *nptr);


#endif	
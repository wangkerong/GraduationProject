#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"
#include "delay.h"
#include "string.h"

//ģʽ����
#define RS485_TX_EN		PGout(8)	//485ģʽ����.0,����;1,����.

#define NULL 0
														 
void RS485_Init(int bound, int data, int stop, char *p);
unsigned short CheckCRC(unsigned char *pData,unsigned int siLen);
void WriteData(u8 addr, u8  ControlCode, u16 registeraddr, u16 data);
int GetHumAndTemp(unsigned char *buf, short int *temp, short int *hum);
int atoi(const char *nptr);
void ModBusConfig(void);
int atoi(const char *nptr);


#endif	
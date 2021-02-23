#ifndef _MQTTCONFIG_H
#define _MQTTCONFIG_H
#include "MQTTConnect.h"
#include "MQTTSubscribe.h"
#include "MQTTPublish.h"
#include "wifi.h"

void Receive_Connect_Data(void);
void PublishMessage(short int *Temp, short int *Hum);
void KeepLive(void);
void SubscribeTheam(char *topic);
void UnsubscribeThem(char *topic);
void PublishMessageAnalysis(void);
void ConnectToServer(char *n, char *p, unsigned short k);


#endif 
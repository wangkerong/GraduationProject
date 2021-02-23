#ifndef MQTTSUBSCRIBE_H_
#define MQTTSUBSCRIBE_H_

#include "MQTTPacket.h"
#include <stdlib.h>



//订阅主题
int MQTTSerialize_subscribe(unsigned char* buf, int buflen, unsigned char dup, unsigned short packetid, int count, MQTTString topicFilters[], int requestedQoSs[]);
//订阅主题返回
int MQTTDeserialize_suback(unsigned short* packetid, int maxcount, int* count, int grantedQoSs[], unsigned char* buf, int buflen);
//退订主题
int MQTTSerialize_subscribe(unsigned char* buf, int buflen, unsigned char dup, unsigned short packetid, int count, MQTTString topicFilters[], int requestedQoSs[]);










#endif

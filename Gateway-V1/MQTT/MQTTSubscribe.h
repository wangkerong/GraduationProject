#ifndef MQTTSUBSCRIBE_H_
#define MQTTSUBSCRIBE_H_

#include "MQTTPacket.h"
#include <stdlib.h>



//��������
int MQTTSerialize_subscribe(unsigned char* buf, int buflen, unsigned char dup, unsigned short packetid, int count, MQTTString topicFilters[], int requestedQoSs[]);
//�������ⷵ��
int MQTTDeserialize_suback(unsigned short* packetid, int maxcount, int* count, int grantedQoSs[], unsigned char* buf, int buflen);
//�˶�����
int MQTTSerialize_subscribe(unsigned char* buf, int buflen, unsigned char dup, unsigned short packetid, int count, MQTTString topicFilters[], int requestedQoSs[]);










#endif

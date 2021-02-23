#ifndef MQTTPUBLISH_H_
#define MQTTPUBLISH_H_

#include "MQTTPacket.h"
#include <string.h>



//������Ϣ
int MQTTSerialize_publish(unsigned char* buf, int buflen, unsigned char dup, int qos, unsigned char retained, unsigned short packetid,
	MQTTString topicName, unsigned char* payload, int payloadlen);
//�յ�����Ϣ���н���
int MQTTDeserialize_publish(unsigned char* dup, int* qos, unsigned char* retained, unsigned short* packetid, MyMQTTString* topicName,
	unsigned char** payload, int* payloadlen, unsigned char* buf, int buflen);



#endif

#ifndef MQTTPUBLISH_H_
#define MQTTPUBLISH_H_

#include "MQTTPacket.h"
#include <string.h>



//发布消息
int MQTTSerialize_publish(unsigned char* buf, int buflen, unsigned char dup, int qos, unsigned char retained, unsigned short packetid,
	MQTTString topicName, unsigned char* payload, int payloadlen);
//收到的消息进行解析
int MQTTDeserialize_publish(unsigned char* dup, int* qos, unsigned char* retained, unsigned short* packetid, MyMQTTString* topicName,
	unsigned char** payload, int* payloadlen, unsigned char* buf, int buflen);



#endif

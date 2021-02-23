#include "MQTTPublish.h"



/**
*确定使用提供的参数将产生的MQTT发布数据包的长度
* @param qos发布的MQTT QoS（对于QoS 0，省略了数据包标识）
* @param topicName要在发布中使用的主题名称
* @param payloadlen要发送的有效载荷的长度
* @return包含数据包的序列化版本所需的缓冲区的长度
*/

int MQTTSerialize_publishLength(int qos, MQTTString topicName, int payloadlen)
{
	int len = 0;

	len += 2 + MQTTstrlen(topicName) + payloadlen;
	if (qos > 0)
		len += 2; /* packetid */
	return len;
}

/**
*将提供的发布数据序列化到提供的缓冲区中，准备发送
* @param buf将数据包序列化到的缓冲区
* @param buflen提供的缓冲区的字节长度
* @param dup整数 - MQTT dup标志
* @param qos整数 - MQTT QoS值
* @param retained整数 - MQTT保留标志
* @param packetid整数 - MQTT数据包标识符
* @param topicName MQTTString - 发布中的MQTT主题
* @param 有效负载字节缓冲区 - MQTT发布有效负载
* @param payloadlen整数 - MQTT有效载荷的长度
* @返回序列化数据的长度。 <= 0表示错误
*/
int MQTTSerialize_publish(unsigned char* buf, int buflen, unsigned char dup, int qos, unsigned char retained, unsigned short packetid,
	MQTTString topicName, unsigned char* payload, int payloadlen)
{
	unsigned char* ptr = buf;
	MQTTHeader header = { 0 };
	int rem_len = 0;
	int rc = 0;
	if (MQTTPacket_len(rem_len = MQTTSerialize_publishLength(qos, topicName, payloadlen)) > buflen)
	{
		return MQTTPACKET_BUFFER_TOO_SHORT;
	}
	header.bits.type = PUBLISH;
	header.bits.dup = dup;
	header.bits.qos = qos;
	header.bits.retain = retained;
	writeChar(&ptr, header.byte); /* write header */
	ptr += MQTTPacket_encode(ptr, rem_len); /* write remaining length */;
	writeMQTTString(&ptr, topicName);
	if (qos > 0)
		writeInt(&ptr, packetid);
	memcpy(ptr, payload, payloadlen);
	ptr += payloadlen;
	rc = ptr - buf;
	return rc;
}
/**
*将提供的缓冲区反序列化为发布的数据
* @param dup返回整数 - MQTT dup标志
* @param qos返回整数 - MQTT QoS值
* @param保留返回的整数 - MQTT保留标志
* @param packetid返回整数 - MQTT数据包标识符
* @param topicName返回了MQTTString - 发布中的MQTT主题
* @param有效负载返回的字节缓冲区 - MQTT发布有效负载
* @param payloadlen返回的整数 - MQTT有效载荷的长度
* @param buf原始缓冲区数据，其正确长度由剩余长度字段确定
* @param buflen提供的缓冲区中数据的字节长度
* @返回错误代码。 1就是成功
*/
int MQTTDeserialize_publish(unsigned char* dup, int* qos, unsigned char* retained, unsigned short* packetid, MyMQTTString* topicName,
	unsigned char** payload, int* payloadlen, unsigned char* buf, int buflen)
{
	MQTTHeader header = { 0 };
	unsigned char* curdata = buf;
	unsigned char* enddata = NULL;
	int rc = 0;
	int mylen = 0;
	//curdata指向原始缓冲区
	header.byte = readChar(&curdata);
	if (header.bits.type != PUBLISH)
		goto exit;
	*dup = header.bits.dup;
	*qos = header.bits.qos;
	*retained = header.bits.retain;
	//RC:剩余长度占两个字节=2
	curdata += (rc = MQTTPacket_decodeBuf(curdata, &mylen)); /* 读剩余长度 */
	//curdata指向Msg Len后面第一个字节就Topic Length
	//mylen：剩余长度272
	enddata = curdata + mylen;
	//enddata：指向缓存区的尾部

	if (!readMQTTLenString(topicName, &curdata, enddata) ||
		enddata - curdata < 0) /* do we have enough data to read the protocol version byte? 我们是否有足够的数据来读取协议版本字节？*/
		goto exit;

	if (*qos > 0)
		*packetid = readInt(&curdata);

	*payloadlen = enddata - curdata;
	*payload = curdata;
	rc = 1;
exit:
	return rc;
}

#include "MQTTSubscribe.h"


/*
*确定使用提供的参数将产生的MQTT订阅数据包的长度
* @param计算topicFilters中主题过滤器字符串的数量
* @param topicFilters用于在发布中使用的主题过滤器字符串数组
* @return包含数据包的序列化版本所需的缓冲区的长度
*/
int MQTTSerialize_subscribeLength(int count, MQTTString topicFilters[])
{
	int i;
	int len = 2; /* packetid */

	for (i = 0; i < count; ++i)
		len += 2 + MQTTstrlen(topicFilters[i]) + 1; /* length + topic + req_qos */
	return len;
}

int MQTTSerialize_unsubscribeLength(int count, MQTTString topicFilters[])
{
	int i;
	int len = 2; /* packetid */

	for (i = 0; i < count; ++i)
		len += 2 + MQTTstrlen(topicFilters[i]); /* length + topic*/
	return len;
}
/*
*将提供的订阅数据序列化到提供的缓冲区中，准备发送
* @param buf将数据包序列化到的缓冲区
* @param buflen提供的缓冲区的长度（以字节为单位）
* @param dup整数 - MQTT dup标志                     //对于QOS=0的消息，DUP标志必须为0
* @param packetid整数 - MQTT数据包标识符
* @param count - topicFilters和reqQos数组中的成员数
* @param topicFilters - 主题过滤器名称的数组
* @param requestedQoSs - 请求的QoS数组
* @返回序列化数据的长度。 <= 0表示错误
*/
int MQTTSerialize_subscribe(unsigned char* buf, int buflen, unsigned char dup, unsigned short packetid, int count,
	MQTTString topicFilters[], int requestedQoSs[])
{
	unsigned char* ptr = buf;
	MQTTHeader header = { 0 };
	int rem_len = 0;
	int rc = 0;
	int i = 0;

	if (MQTTPacket_len(rem_len = MQTTSerialize_subscribeLength(count, topicFilters)) > buflen)
	{
		rc = MQTTPACKET_BUFFER_TOO_SHORT;
		goto exit;
	}

	header.byte = 0;
	header.bits.type = SUBSCRIBE;
	header.bits.dup = dup;
	header.bits.qos = 1;
	writeChar(&ptr, header.byte); /* write header */

	ptr += MQTTPacket_encode(ptr, rem_len); /* write remaining length */;

	writeInt(&ptr, packetid);

	for (i = 0; i < count; ++i)
	{
		writeMQTTString(&ptr, topicFilters[i]);
		writeChar(&ptr, requestedQoSs[i]);
	}

	rc = ptr - buf;
exit:
	return rc;
}
/*
?? *将提供的取消订阅数据序列化到提供的缓冲区中，准备发送
?? * @param buf原始缓冲区数据，其正确长度由剩余长度字段确定
?? * @param buflen提供的缓冲区中数据的字节长度
?? * @param dup整数-MQTT dup标志
?? * @param packetid整数-MQTT数据包标识符
?? * @param count-topicFilters数组中的成员数
?? * @param topicFilters-主题过滤器名称的数组
?? * @返回序列化数据的长度。 <= 0表示错误
*/
int MQTTSerialize_unsubscribe(unsigned char* buf, int buflen, unsigned char dup, unsigned short packetid,
		int count, MQTTString topicFilters[])
{
	unsigned char *ptr = buf;
	MQTTHeader header = {0};
	int rem_len = 0;
	int rc = -1;
	int i = 0;
	if (MQTTPacket_len(rem_len = MQTTSerialize_unsubscribeLength(count, topicFilters)) > buflen)
	{
		rc = MQTTPACKET_BUFFER_TOO_SHORT;
		goto exit;
	}

	header.byte = 0;
	header.bits.type = UNSUBSCRIBE;
	header.bits.dup = dup;
	header.bits.qos = 1;
	writeChar(&ptr, header.byte); /* write header */

	ptr += MQTTPacket_encode(ptr, rem_len); /* write remaining length */;

	writeInt(&ptr, packetid);

	for (i = 0; i < count; ++i)
		writeMQTTString(&ptr, topicFilters[i]);

	rc = ptr - buf;
exit:
	return rc;
}
/**
*将提供的（有线）缓冲区反序列化为suback数据
* @param packetid返回整数 - MQTT数据包标识符
* @param maxcount - 在grantQoSs数组中允许的最大成员数
* @param count返回的整数 - grantQoSs数组中的成员数
* @param grantQoSs返回整数数组 - 授予的服务质量
* @param buf原始缓冲区数据，其正确长度由剩余长度字段确定
* @param buflen提供的缓冲区中数据的字节长度
* @返回错误代码。 1是成功，0是失败
*/
int MQTTDeserialize_suback(unsigned short* packetid, int maxcount, int* count, int grantedQoSs[], unsigned char* buf, int buflen)
{
	MQTTHeader header = { 0 };
	unsigned char* curdata = buf;
	unsigned char* enddata = NULL;
	int rc = 0;
	int mylen;

	header.byte = readChar(&curdata);
	if (header.bits.type != SUBACK)
		goto exit;

	curdata += (rc = MQTTPacket_decodeBuf(curdata, &mylen)); /* read remaining length */
	enddata = curdata + mylen;
	if (enddata - curdata < 2)
		goto exit;

	*packetid = readInt(&curdata);
	*count = 0;
	while (curdata < enddata)
	{
		if (*count > maxcount)
		{
			rc = -1;
			goto exit;
		}
		grantedQoSs[(*count)++] = readChar(&curdata);
	}

	rc = 1;
exit:
	return rc;
}



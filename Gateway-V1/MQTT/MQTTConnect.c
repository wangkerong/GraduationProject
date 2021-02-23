#include "MQTTConnect.h"

//计算剩余长度
int MQTTSerialize_connectLength(MQTTPacket_connectData* options)
{
	int len = 0;
	if (options->MQTTVersion == 3)
		len = 12; /* variable depending on MQTT or MQIsdp */
	else if (options->MQTTVersion == 4)
		len = 10;

	len += MQTTstrlen(options->clientID) + 2;
	if (options->willFlag)
		len += MQTTstrlen(options->will.topicName) + 2 + MQTTstrlen(options->will.message) + 2;
	if (options->username.cstring || options->username.lenstring.data)
		len += MQTTstrlen(options->username) + 2;
	if (options->password.cstring || options->password.lenstring.data)
		len += MQTTstrlen(options->password) + 2;
	return len;
}
/**
  * 将连接选项序列化到缓冲区中。
  * @param buf :数据转化后的缓存区
  * @param len :缓冲区的长度
  * @param options ：数据包选项结构体
  * @return 序列长度，如果是0，则返回错误
  */
int MQTTSerialize_connect(unsigned char* buf, int buflen, MQTTPacket_connectData* options)
{
	unsigned char* ptr = buf;
	MQTTHeader header = { 0 };
	MQTTConnectFlags flags = { 0 };
	int len = 0;
	int rc = -1;
	if (MQTTPacket_len(len = MQTTSerialize_connectLength(options)) > buflen)
	{
		return MQTTPACKET_BUFFER_TOO_SHORT;	
	}
	header.byte = 0;
	header.bits.type = CONNECT;
	writeChar(&ptr, header.byte); /* write header */

	ptr += MQTTPacket_encode(ptr, len); /* write remaining length */

	if (options->MQTTVersion == 4)
	{
		writeCString(&ptr, "MQTT");
		writeChar(&ptr, (char)4);
	}
	else
	{
		writeCString(&ptr, "MQIsdp");
		writeChar(&ptr, (char)3);
	}
	flags.all = 0;
	flags.bits.cleansession = options->cleansession;
	flags.bits.will = (options->willFlag) ? 1 : 0;
	if (flags.bits.will)
	{
		flags.bits.willQoS = options->will.qos;
		flags.bits.willRetain = options->will.retained;
	}
	if (options->username.cstring || options->username.lenstring.data)
		flags.bits.username = 1;
	if (options->password.cstring || options->password.lenstring.data)
		flags.bits.password = 1;
	writeChar(&ptr, flags.all);
	writeInt(&ptr, options->keepAliveInterval);
	writeMQTTString(&ptr, options->clientID);
	if (options->willFlag)
	{
		writeMQTTString(&ptr, options->will.topicName);
		writeMQTTString(&ptr, options->will.message);
	}
	if (flags.bits.username)
		writeMQTTString(&ptr, options->username);
	if (flags.bits.password)
		writeMQTTString(&ptr, options->password);
	rc = ptr - buf;
	return rc;
}
/**
* 将提供的（有线）缓冲区反序列化为connack数据 - 返回码
* @param sessionPresent返回返回的会话存在标志（仅适用于MQTT 3.1.1）
* @param connack_rc返回了connack返回码的整数值
* @param buf原始缓冲区数据，其正确长度由剩余长度字段确定
* @param len提供的缓冲区中数据的字节长度
* @返回错误代码。 1是成功，0是失败
*/
int MQTTDeserialize_connack(unsigned char* sessionPresent, unsigned char* connack_rc, unsigned char* buf, int buflen)
{
	MQTTHeader header = { 0 };
	unsigned char* curdata = buf;
	unsigned char* enddata = NULL;
	int rc = 0;
	int mylen;
	MQTTConnackFlags flags = { 0 };
	header.byte = readChar(&curdata);
	if (header.bits.type != CONNACK)
		goto exit;
	curdata += (rc = MQTTPacket_decodeBuf(curdata, &mylen)); /* read remaining length */
	enddata = curdata + mylen;
	if (enddata - curdata < 2)
		goto exit;
	flags.all = readChar(&curdata);
	*sessionPresent = flags.bits.sessionpresent;
	*connack_rc = readChar(&curdata);
	rc = 1;
exit:
	return rc;
}
/*
* @param buf将数据包序列化到的缓冲区
* @param buflen提供的缓冲区的长度（以字节为单位），以避免溢出
* @param packettype消息类型
* @返回序列化长度，如果为0，则返回错误
*/

int MQTTSerialize_zero(unsigned char* buf, int buflen, unsigned char packettype)
{
	MQTTHeader header = { 0 };
	int rc = -1;
	unsigned char* ptr = buf;
	if (buflen < 2){
		return MQTTPACKET_BUFFER_TOO_SHORT;
	}
	header.byte = 0;
	header.bits.type = packettype;
	writeChar(&ptr, header.byte); /* write header */
	ptr += MQTTPacket_encode(ptr, 0); /* write remaining length */
	rc = ptr - buf;
	return rc;
}
/*
*将断开连接的数据包序列化到提供的缓冲区中，以准备写入套接字
* @param buf将数据包序列化到的缓冲区
* @param buflen提供的缓冲区的长度（以字节为单位），以避免溢出
* @返回序列化长度，如果为0，则返回错误
*/
int MQTTSerialize_disconnect(unsigned char* buf, int buflen)
{
	return MQTTSerialize_zero(buf, buflen, DISCONNECT);
}

int MQTTSerialize_pingreq(unsigned char* buf, int buflen)
{
	return MQTTSerialize_zero(buf, buflen, PINGREQ);
}


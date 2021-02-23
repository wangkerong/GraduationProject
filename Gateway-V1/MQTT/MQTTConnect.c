#include "MQTTConnect.h"

//����ʣ�೤��
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
  * ������ѡ�����л����������С�
  * @param buf :����ת����Ļ�����
  * @param len :�������ĳ���
  * @param options �����ݰ�ѡ��ṹ��
  * @return ���г��ȣ������0���򷵻ش���
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
* ���ṩ�ģ����ߣ������������л�Ϊconnack���� - ������
* @param sessionPresent���ط��صĻỰ���ڱ�־����������MQTT 3.1.1��
* @param connack_rc������connack�����������ֵ
* @param bufԭʼ���������ݣ�����ȷ������ʣ�೤���ֶ�ȷ��
* @param len�ṩ�Ļ����������ݵ��ֽڳ���
* @���ش�����롣 1�ǳɹ���0��ʧ��
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
* @param buf�����ݰ����л����Ļ�����
* @param buflen�ṩ�Ļ������ĳ��ȣ����ֽ�Ϊ��λ�����Ա������
* @param packettype��Ϣ����
* @�������л����ȣ����Ϊ0���򷵻ش���
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
*���Ͽ����ӵ����ݰ����л����ṩ�Ļ������У���׼��д���׽���
* @param buf�����ݰ����л����Ļ�����
* @param buflen�ṩ�Ļ������ĳ��ȣ����ֽ�Ϊ��λ�����Ա������
* @�������л����ȣ����Ϊ0���򷵻ش���
*/
int MQTTSerialize_disconnect(unsigned char* buf, int buflen)
{
	return MQTTSerialize_zero(buf, buflen, DISCONNECT);
}

int MQTTSerialize_pingreq(unsigned char* buf, int buflen)
{
	return MQTTSerialize_zero(buf, buflen, PINGREQ);
}


#include "MQTTSubscribe.h"


/*
*ȷ��ʹ���ṩ�Ĳ�����������MQTT�������ݰ��ĳ���
* @param����topicFilters������������ַ���������
* @param topicFilters�����ڷ�����ʹ�õ�����������ַ�������
* @return�������ݰ������л��汾����Ļ������ĳ���
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
*���ṩ�Ķ����������л����ṩ�Ļ������У�׼������
* @param buf�����ݰ����л����Ļ�����
* @param buflen�ṩ�Ļ������ĳ��ȣ����ֽ�Ϊ��λ��
* @param dup���� - MQTT dup��־                     //����QOS=0����Ϣ��DUP��־����Ϊ0
* @param packetid���� - MQTT���ݰ���ʶ��
* @param count - topicFilters��reqQos�����еĳ�Ա��
* @param topicFilters - ������������Ƶ�����
* @param requestedQoSs - �����QoS����
* @�������л����ݵĳ��ȡ� <= 0��ʾ����
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
?? *���ṩ��ȡ�������������л����ṩ�Ļ������У�׼������
?? * @param bufԭʼ���������ݣ�����ȷ������ʣ�೤���ֶ�ȷ��
?? * @param buflen�ṩ�Ļ����������ݵ��ֽڳ���
?? * @param dup����-MQTT dup��־
?? * @param packetid����-MQTT���ݰ���ʶ��
?? * @param count-topicFilters�����еĳ�Ա��
?? * @param topicFilters-������������Ƶ�����
?? * @�������л����ݵĳ��ȡ� <= 0��ʾ����
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
*���ṩ�ģ����ߣ������������л�Ϊsuback����
* @param packetid�������� - MQTT���ݰ���ʶ��
* @param maxcount - ��grantQoSs���������������Ա��
* @param count���ص����� - grantQoSs�����еĳ�Ա��
* @param grantQoSs������������ - ����ķ�������
* @param bufԭʼ���������ݣ�����ȷ������ʣ�೤���ֶ�ȷ��
* @param buflen�ṩ�Ļ����������ݵ��ֽڳ���
* @���ش�����롣 1�ǳɹ���0��ʧ��
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



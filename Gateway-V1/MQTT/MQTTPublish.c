#include "MQTTPublish.h"



/**
*ȷ��ʹ���ṩ�Ĳ�����������MQTT�������ݰ��ĳ���
* @param qos������MQTT QoS������QoS 0��ʡ�������ݰ���ʶ��
* @param topicNameҪ�ڷ�����ʹ�õ���������
* @param payloadlenҪ���͵���Ч�غɵĳ���
* @return�������ݰ������л��汾����Ļ������ĳ���
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
*���ṩ�ķ����������л����ṩ�Ļ������У�׼������
* @param buf�����ݰ����л����Ļ�����
* @param buflen�ṩ�Ļ��������ֽڳ���
* @param dup���� - MQTT dup��־
* @param qos���� - MQTT QoSֵ
* @param retained���� - MQTT������־
* @param packetid���� - MQTT���ݰ���ʶ��
* @param topicName MQTTString - �����е�MQTT����
* @param ��Ч�����ֽڻ����� - MQTT������Ч����
* @param payloadlen���� - MQTT��Ч�غɵĳ���
* @�������л����ݵĳ��ȡ� <= 0��ʾ����
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
*���ṩ�Ļ����������л�Ϊ����������
* @param dup�������� - MQTT dup��־
* @param qos�������� - MQTT QoSֵ
* @param�������ص����� - MQTT������־
* @param packetid�������� - MQTT���ݰ���ʶ��
* @param topicName������MQTTString - �����е�MQTT����
* @param��Ч���ط��ص��ֽڻ����� - MQTT������Ч����
* @param payloadlen���ص����� - MQTT��Ч�غɵĳ���
* @param bufԭʼ���������ݣ�����ȷ������ʣ�೤���ֶ�ȷ��
* @param buflen�ṩ�Ļ����������ݵ��ֽڳ���
* @���ش�����롣 1���ǳɹ�
*/
int MQTTDeserialize_publish(unsigned char* dup, int* qos, unsigned char* retained, unsigned short* packetid, MyMQTTString* topicName,
	unsigned char** payload, int* payloadlen, unsigned char* buf, int buflen)
{
	MQTTHeader header = { 0 };
	unsigned char* curdata = buf;
	unsigned char* enddata = NULL;
	int rc = 0;
	int mylen = 0;
	//curdataָ��ԭʼ������
	header.byte = readChar(&curdata);
	if (header.bits.type != PUBLISH)
		goto exit;
	*dup = header.bits.dup;
	*qos = header.bits.qos;
	*retained = header.bits.retain;
	//RC:ʣ�೤��ռ�����ֽ�=2
	curdata += (rc = MQTTPacket_decodeBuf(curdata, &mylen)); /* ��ʣ�೤�� */
	//curdataָ��Msg Len�����һ���ֽھ�Topic Length
	//mylen��ʣ�೤��272
	enddata = curdata + mylen;
	//enddata��ָ�򻺴�����β��

	if (!readMQTTLenString(topicName, &curdata, enddata) ||
		enddata - curdata < 0) /* do we have enough data to read the protocol version byte? �����Ƿ����㹻����������ȡЭ��汾�ֽڣ�*/
		goto exit;

	if (*qos > 0)
		*packetid = readInt(&curdata);

	*payloadlen = enddata - curdata;
	*payload = curdata;
	rc = 1;
exit:
	return rc;
}

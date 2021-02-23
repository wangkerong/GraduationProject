#include "MQTTPacket.h"
#include <string.h>


int MQTTstrlen(MQTTString mqttstring)
{
	int rc = 0;
	if (mqttstring.cstring)
		rc = strlen(mqttstring.cstring);
	else
		rc = mqttstring.lenstring.len;
	return rc;
}


int MQTTPacket_len(int rem_len)
{
	rem_len += 1; /* header byte */
	/* now remaining_length field */
	if (rem_len < 128)
		rem_len += 1;
	else if (rem_len < 16384)
		rem_len += 2;
	else if (rem_len < 2097151)
		rem_len += 3;
	else
		rem_len += 4;
	return rem_len;
}

void writeChar(unsigned char** pptr, char c)   //���ַ�д�뻺����
{
	**pptr = c;
	(*pptr)++;
}
char readChar(unsigned char** pptr)			   //�ӻ��������ַ�
{
	char c = **pptr;
	(*pptr)++;
	return c;
}
/*
*����MQTT�㷨����Ϣ���Ƚ��б���
* @param buf����������д�����еĻ�����
* @param lengthҪ����ĳ���
* @����д�뻺�������ֽ���
*/
int MQTTPacket_encode(unsigned char* buf, int length)
{
	int rc = 0;
	do
	{
		char d = length % 128;
		length /= 128;
		/* if there are more digits to encode, set the top bit of this digit */
		if (length > 0)
			d |= 0x80;
		buf[rc++] = d;
	} while (length > 0);
	return rc;
}
/**
*��2�ֽڵ�����д�������������
* @param pptrָ�������������ָ�� - ����ʹ�õ��ֽ���������
* @param anIntҪд�������
*/
void writeInt(unsigned char** pptr, int anInt)
{
	**pptr = (unsigned char)(anInt / 256);
	(*pptr)++;
	**pptr = (unsigned char)(anInt % 256);
	(*pptr)++;
}
/**
* ���ݴ����뻺������ȡ�������ֽڼ���һ������
* @param pptrָ�����뻺������ָ�� - ����ʹ�õ��ֽ���������
* @���ؼ����������ֵ
*/
int readInt(unsigned char** pptr)
{
	unsigned char* ptr = *pptr;
	int len = 256 * (*ptr) + (*(ptr + 1));
	*pptr += 2;
	return len;
}
/**
*���� UTF���ַ���д������������� ��C�ַ���ת��Ϊ���ȷָ����ַ�����
* @param pptrָ�������������ָ�� - ����ʹ�õ��ֽ���������
* @param stringҪ��д��C�ַ���
*/
void writeCString(unsigned char** pptr, const char* string)
{
	int len = strlen(string);
	writeInt(pptr, len);
	memcpy(*pptr, string, len);
	*pptr += len;
}

void writeMQTTString(unsigned char** pptr, MQTTString mqttstring)
{
	if (mqttstring.lenstring.len > 0)
	{
		writeInt(pptr, mqttstring.lenstring.len);
		memcpy(*pptr, mqttstring.lenstring.data, mqttstring.lenstring.len);
		*pptr += mqttstring.lenstring.len;
	}
	else if (mqttstring.cstring)
		writeCString(pptr, mqttstring.cstring);
	else
		writeInt(pptr, 0);
}


static unsigned char* bufptr;
int bufchar(unsigned char* c, int count)
{
	int i;

	for (i = 0; i < count; ++i)
		*c = *bufptr++;
	return count;
}

/**
*����MQTT�㷨������Ϣ����
*@param getcharfnָ�룬���ڴ�����Դ��ȡ��һ���ַ�
*@paramֵ���صĽ��볤��
*@���ش��׽��ֶ�ȡ���ֽ���
*/

int MQTTPacket_decode(int (*getcharfn)(unsigned char*, int), int* value)
{
	unsigned char c;
	int multiplier = 1;
	int len = 0;
#define MAX_NO_OF_REMAINING_LENGTH_BYTES 4
	*value = 0;
	do
	{
		int rc = MQTTPACKET_READ_ERROR;

		if (++len > MAX_NO_OF_REMAINING_LENGTH_BYTES)
		{
			rc = MQTTPACKET_READ_ERROR;	/* bad data */
			goto exit;
		}
		rc = (*getcharfn)(&c, 1);
		if (rc != 1)
			goto exit;
		*value += (c & 127) * multiplier;
		multiplier *= 128;
	} while ((c & 128) != 0);
exit:
	return len;
}

int MQTTPacket_decodeBuf(unsigned char* buf, int* value)
{
	bufptr = buf;
	return MQTTPacket_decode(bufchar, value);
}


/**
*@param mqttstringҪ�����ж�ȡ���ݵ�MQTTString�ṹ
*@param pptrָ�������������ָ�� - ����ʹ�õ��ֽ���������
*@param enddataָ�����ݽ�β��ָ�룺��Ҫ����
*@����ɹ��򷵻�1�����򷵻�0
*/
int readMQTTLenString(MyMQTTString* mqttstring, unsigned char** pptr, unsigned char* enddata)
{
	int rc = 0;
	/* ǰ�����ֽ�������ĳ���
	enddata��ָ�򻺳�����β��
	pptr��ָ��topic len*/
	if (enddata - (*pptr) > 1) /* enough length to read the integer? */
	{
		mqttstring->lenstring.len = readInt(pptr); /* ���ⳤ��0x29 pptr��ָ��topic*/
		if (&(*pptr)[mqttstring->lenstring.len] <= enddata)
		{
			//mqttstring->lenstring.data = (char*)*pptr;//��dataָ��topic�ַ�����ͷ
			memcpy((char *)mqttstring->lenstring.data ,(char*)*pptr, mqttstring->lenstring.len);
			*pptr += mqttstring->lenstring.len;
			rc = 1;
			//pptrָ��message
		}
	}
	mqttstring->cstring = NULL;
	return rc;
}

// int MQTTPacket_read(unsigned char* buf, int buflen, int (*getfn)(unsigned char*, int))
// {
// 	int rc = -1;
// 	MQTTHeader header = {0};
// 	int len = 0;
// 	int rem_len = 0;

// 	/* 1. read the header byte.  This has the packet type in it */
// 	if ((*getfn)(buf, 1) != 1)
// 		goto exit;

// 	len = 1;
// 	/* 2. read the remaining length.  This is variable in itself */
// 	MQTTPacket_decode(getfn, &rem_len);
// 	len += MQTTPacket_encode(buf + 1, rem_len); /* put the original remaining length back into the buffer */

// 	/* 3. read the rest of the buffer using a callback to supply the rest of the data */
// 	if((rem_len + len) > buflen)
// 		goto exit;
// 	if (rem_len && ((*getfn)(buf + len, rem_len) != rem_len))
// 		goto exit;

// 	header.byte = buf[0];
// 	rc = header.bits.type;
// exit:
// 	return rc;
// }


// int GetInfo(unsigned char *buf, int len)
// {

// }
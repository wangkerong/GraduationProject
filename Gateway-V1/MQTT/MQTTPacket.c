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

void writeChar(unsigned char** pptr, char c)   //将字符写入缓冲区
{
	**pptr = c;
	(*pptr)++;
}
char readChar(unsigned char** pptr)			   //从缓冲区读字符
{
	char c = **pptr;
	(*pptr)++;
	return c;
}
/*
*根据MQTT算法对消息长度进行编码
* @param buf将编码数据写入其中的缓冲区
* @param length要编码的长度
* @返回写入缓冲区的字节数
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
*将2字节的整数写入输出缓冲区。
* @param pptr指向输出缓冲区的指针 - 增加使用的字节数并返回
* @param anInt要写入的整数
*/
void writeInt(unsigned char** pptr, int anInt)
{
	**pptr = (unsigned char)(anInt / 256);
	(*pptr)++;
	**pptr = (unsigned char)(anInt % 256);
	(*pptr)++;
}
/**
* 根据从输入缓冲区读取的两个字节计算一个整数
* @param pptr指向输入缓冲区的指针 - 增加使用的字节数并返回
* @返回计算出的整数值
*/
int readInt(unsigned char** pptr)
{
	unsigned char* ptr = *pptr;
	int len = 256 * (*ptr) + (*(ptr + 1));
	*pptr += 2;
	return len;
}
/**
*将“ UTF”字符串写入输出缓冲区。 将C字符串转换为长度分隔的字符串。
* @param pptr指向输出缓冲区的指针 - 增加使用的字节数并返回
* @param string要编写的C字符串
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
*根据MQTT算法解码消息长度
*@param getcharfn指针，用于从数据源读取下一个字符
*@param值返回的解码长度
*@返回从套接字读取的字节数
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
*@param mqttstring要在其中读取数据的MQTTString结构
*@param pptr指向输出缓冲区的指针 - 增加使用的字节数并返回
*@param enddata指向数据结尾的指针：不要超出
*@如果成功则返回1，否则返回0
*/
int readMQTTLenString(MyMQTTString* mqttstring, unsigned char** pptr, unsigned char* enddata)
{
	int rc = 0;
	/* 前两个字节是主题的长度
	enddata：指向缓冲区的尾巴
	pptr：指向topic len*/
	if (enddata - (*pptr) > 1) /* enough length to read the integer? */
	{
		mqttstring->lenstring.len = readInt(pptr); /* 主题长度0x29 pptr：指向topic*/
		if (&(*pptr)[mqttstring->lenstring.len] <= enddata)
		{
			//mqttstring->lenstring.data = (char*)*pptr;//将data指向topic字符串开头
			memcpy((char *)mqttstring->lenstring.data ,(char*)*pptr, mqttstring->lenstring.len);
			*pptr += mqttstring->lenstring.len;
			rc = 1;
			//pptr指向message
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
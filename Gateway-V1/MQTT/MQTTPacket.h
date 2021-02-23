#ifndef MQTTPACKET_H_
#define MQTTPACKET_H_


typedef struct
{
	int len;
	char* data;
} MQTTLenString;

typedef struct
{
	char* cstring;
	MQTTLenString lenstring;
} MQTTString;

typedef struct
{
	int len;
	char data[100];
} MyMQTTLenString;
typedef struct
{
	char* cstring;
	MyMQTTLenString lenstring;
} MyMQTTString;
typedef union
{
	unsigned char byte;	                /**< the whole byte */
	struct
	{
		unsigned int retain : 1;		/**< retained flag bit */
		unsigned int qos : 2;				/**< QoS value, 0, 1 or 2 */
		unsigned int dup : 1;				/**< DUP flag bit */
		unsigned int type : 4;			/**< message type nibble */
	} bits;
} MQTTHeader;

enum errors
{
	MQTTPACKET_BUFFER_TOO_SHORT = -2,
	MQTTPACKET_READ_ERROR = -1,
	MQTTPACKET_READ_COMPLETE
};

enum msgTypes
{
	CONNECT = 1, CONNACK, PUBLISH, PUBACK, PUBREC, PUBREL,
	PUBCOMP, SUBSCRIBE, SUBACK, UNSUBSCRIBE, UNSUBACK,
	PINGREQ, PINGRESP, DISCONNECT
};


//º¯ÊýÉùÃ÷
int MQTTstrlen(MQTTString mqttstring);
int MQTTPacket_len(int rem_len);
void writeChar(unsigned char** pptr, char c);
char readChar(unsigned char** pptr);
int MQTTPacket_encode(unsigned char* buf, int length);
void writeInt(unsigned char** pptr, int anInt);
int readInt(unsigned char** pptr);
void writeCString(unsigned char** pptr, const char* string);
void writeMQTTString(unsigned char** pptr, MQTTString mqttstring);
void writeChar(unsigned char** pptr, char c);
int MQTTPacket_decodeBuf(unsigned char* buf, int* value);
int readMQTTLenString(MyMQTTString* mqttstring, unsigned char** pptr, unsigned char* enddata);


#endif


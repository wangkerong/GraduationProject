#ifndef MQTTCONNECT_H_
#define MQTTCONNECT_H_

#include "MQTTPacket.h"
#include <stdlib.h>


typedef struct
{
	char struct_id[4];
	int struct_version;
	MQTTString topicName;
	MQTTString message;
	unsigned char retained;
	char qos;
} MQTTPacket_willOptions;   //遗嘱结构体


typedef struct
{
	/**This structure. must be MQTC. */
	char struct_id[4];
	/** The version number of this structure.  Must be 0 */
	int struct_version;
	/** Version of MQTT to be used.  3 = 3.1 4 = 3.1.1 */
	unsigned char MQTTVersion;
	MQTTString clientID;
	/** Keep connect timeout */
	unsigned short keepAliveInterval;
	unsigned char cleansession;
	unsigned char willFlag;
	MQTTPacket_willOptions will;
	MQTTString username;
	MQTTString password;
} MQTTPacket_connectData;


typedef union
{
	unsigned char all;	/**< all connect flags */
	struct
	{
		unsigned int : 1;	     					/**< unused */
		unsigned int cleansession : 1;	  /**< cleansession flag */
		unsigned int will : 1;			    /**< will flag */
		unsigned int willQoS : 2;				/**< will QoS value */
		unsigned int willRetain : 1;		/**< will retain setting */
		unsigned int password : 1; 			/**< 3.1 password */
		unsigned int username : 1;			/**< 3.1 user name */
	} bits;

} MQTTConnectFlags;	/**< connect flags byte */

typedef union
{
	unsigned char all;	/**< all connack flags */
	struct
	{
		unsigned int sessionpresent : 1;    /**< session present flag */
		unsigned int reserved : 7;	     			/**< unused */
	} bits;

} MQTTConnackFlags;	/**< connack flags byte */


int MQTTSerialize_connect(unsigned char* buf, int buflen, MQTTPacket_connectData* options);   //连接
int MQTTSerialize_disconnect(unsigned char* buf, int buflen);								  //断开连接
int MQTTSerialize_pingreq(unsigned char* buf, int buflen);									  //心跳请求
int MQTTDeserialize_connack(unsigned char* sessionPresent, unsigned char* connack_rc, unsigned char* buf, int buflen);  //连接返回信息的确认





#endif



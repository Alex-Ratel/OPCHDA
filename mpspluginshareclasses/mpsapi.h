#ifndef mps_api_h
#define mps_api_h
#include <windows.h>
#include "usstr.h"
#define OpcMP_True  1
#define OpcMP_False 0
#define OpcMP_Null  0
#define PLUGIN_NODETYPE_PROGRAM	1
#define PLUGIN_NODETYPE_COM	2
#define PLUGIN_NODETYPE_TCP	3
#define PLUGIN_VERSION "1.0"
#define OPCMP_PLUGINIS_PROGRAM		1
#define OPCMP_PLUGINIS_COMPORT		2
#define OPCMP_PLUGINIS_TCPIP		4
#define OPCMP_PLUGINIS_UDP			8
#define OPCMP_PLUGINIS_IMPORTTAGS  	16
#define OPCMP_PLUGINIS_COMPORTSLAVE	32
#define OPCMP_PLUGINIS_TCPIPSLAVE	64
#define OPCMP_PLUGINIS_UDPSLAVE		128
#define OPCMP_PLUGINIS_WRITETOHDA  	256
#define OPCMP_PLUGINIS_LICTAGS		512
#define OPCMP_PLUGINIS_LICDEVICES	1024
#define OPCMP_PLUGINIS_LICSUBDEVICES1   4096
#define OPCMP_PLUGINIS_LICSUBDEVICES2   8192

#define OPCMP_SUCCESS    0

//
#define OPCMP_QUALITY_BAD				0x00
#define OPCMP_QUALITY_UNCERTAIN			0x40
#define OPCMP_QUALITY_GOOD				0xC0
#define OPCMP_QUALITY_COMM_FAILURE		0x18
#define OPCMP_QUALITY_OUT_OF_SERVICE	0x1C
#define OPCMP_QUALITY_DEVICE_FAILURE	0x0C
#define OPCMP_QUALITY_SENSOR_FAILURE	0x10
#define OPCMP_QUALITY_SENSOR_CAL		0x50
#define OPCMP_QUALITY_LAST_KNOWN		0x14
// HDA
#define OPCMP_HDAMODEAUTOMATIC    true
#define OPCMP_HDAMODEMANUAL       false
#define OPCMP_HDARECORDEVERYCYCLE false
#define OPCMP_HDARECORDBYCHANGE   true
// PROPERTIES TYPE
#define OPCMP_PT_SHOW		1
#define OPCMP_PT_HIDE		2
#define OPCMP_PT_SHOW_R		3
#define OPCMP_PT_HIDE_R		4
#define OPCMP_PT_SHOW_AR	8
#define OPCMP_PT_HIDE_AR	16

// ACCESS TAG TYPE
#define OPCMP_AT_READWRITE 1
#define OPCMP_AT_READONLY  2 
#define OPCMP_AT_WRITEONLY 4 
#define OPCMP_AT_ALL    OPCMP_AT_READWRITE|OPCMP_AT_READONLY|OPCMP_AT_WRITEONLY
// TAG EDITABLE
#define OPCMP_EN_NONE	0
#define OPCMP_EN_DEL	1
#define OPCMP_EN_COPY	2
#define OPCMP_EN_REN	4
#define OPCMP_EN_MOVE	8
#define OPCMP_EN_ALL OPCMP_EN_DEL|OPCMP_EN_COPY|OPCMP_EN_REN|OPCMP_EN_MOVE
// DATA TAG TYPE
#define OPCMP_DT_BOOL	1
#define OPCMP_DT_INT	2
#define OPCMP_DT_UINT	4
#define OPCMP_DT_FLOAT	8
#define OPCMP_DT_DOUBLE	16
#define OPCMP_DT_STRING	32
#define OPCMP_DT_INT64	128
#define OPCMP_DT_UINT64	256
#define OPCMP_DT_BYTE	512
#define OPCMP_DT_SBYTE	1024
#define OPCMP_DT_DATETIME   2048
#define OPCMP_DT_BYTESTRING 4096
#define OPCMP_DT_ALL OPCMP_DT_BOOL|OPCMP_DT_INT|OPCMP_DT_UINT|OPCMP_DT_FLOAT|OPCMP_DT_DOUBLE|OPCMP_DT_STRING|OPCMP_DT_INT64|OPCMP_DT_UINT64|OPCMP_DT_BYTE|OPCMP_DT_SBYTE|OPCMP_DT_DATETIME|OPCMP_DT_BYTESTRING
typedef enum _OpcMP_BuiltInType
{
	OpcMPType_Null = 0,
	OpcMPType_Boolean = 1,
	OpcMPType_SByte = 2,
	OpcMPType_Byte = 3,
	OpcMPType_Int16 = 4,
	OpcMPType_UInt16 = 5,
	OpcMPType_Int32 = 6,
	OpcMPType_UInt32 = 7,
	OpcMPType_Int64 = 8,
	OpcMPType_UInt64 = 9,
	OpcMPType_Float = 10,
	OpcMPType_Double = 11,
	OpcMPType_String = 12,
	OpcMPType_DateTime = 13,
	OpcMPType_ByteString = 15,
	OpcUaType_XmlElement = 16,
	OpcUaType_NodeId = 17,
	OpcUaType_ExpandedNodeId = 18,
	OpcUaType_StatusCode = 19,
	OpcUaType_QualifiedName = 20,
	OpcUaType_LocalizedText = 21,
	OpcUaType_ExtensionObject = 22,
	OpcUaType_DataValue = 23,
	OpcUaType_Variant = 24,
	OpcUaType_DiagnosticInfo = 25

}OpcMP_BuiltInType;
typedef enum _OpcMP_AccessType
{
	OpcMPAccessType_Null = 0,
	OpcMPAccessType_ReadOnly=1,
	OpcMPAccessType_WriteOnly=2,
	OpcMPAccessType_ReadWrite=3
}OpcMP_AccessType;
//
typedef int                 OpcMP_Int;
typedef unsigned int        OpcMP_UInt;
typedef void                OpcMP_Void;
typedef void*               OpcMP_Handle;
typedef bool			    OpcMP_Boolean;
typedef char                OpcMP_SByte;
typedef unsigned char       OpcMP_Byte;
typedef short               OpcMP_Int16;
typedef unsigned short      OpcMP_UInt16;
typedef int                 OpcMP_Int32;
typedef unsigned int        OpcMP_UInt32;
typedef float               OpcMP_Float;
typedef double              OpcMP_Double;
typedef char                OpcMP_CharA;
typedef char  *             OpcMP_String;
typedef unsigned char       OpcMP_UCharA;
typedef unsigned short      OpcMP_Char;
typedef __int64				OpcMP_Int64;
typedef unsigned __int64	OpcMP_UInt64;
//
 typedef struct mps_State  mps_State;
 typedef struct mps_Object mps_Object;
 typedef int (*mps_CFunction) (mps_State *L);
 typedef struct OpcMP_subdevice_t OpcMP_subdevice_t;
 typedef struct OpcMP_plugin_t OpcMP_plugin_t;
 typedef struct OpcMP_plugin_info_t OpcMP_plugin_info_t;
 typedef struct OpcMP_plugin_config_t OpcMP_plugin_config_t;
 typedef int    (* mps_dataready_t)(OpcMP_plugin_t * Plugin, unsigned int TimeOut);
 typedef bool   (* mps_sleep_t)(OpcMP_plugin_t *Plugin, unsigned int TimeOut);
 typedef int	(* mps_sendandreceive_t)(OpcMP_plugin_t *Plugin,unsigned char *SrcBuf,int SrcLen,unsigned char *DstBuf,int DstLen);
 typedef int	(* mps_sendtobuffer_t)(OpcMP_plugin_t *Plugin,unsigned char *SrcBuf,int SrcLen);
 typedef int	(* mps_recvfrombuffer_t)(OpcMP_plugin_t *Plugin,unsigned char *DstBuf,int MaxLen);
 typedef struct OpcMP_tag_t OpcMP_tag_t;
 typedef bool	(* mps_writetohda_t)(OpcMP_plugin_t *Plugin,OpcMP_tag_t *Tag);
 typedef struct OpcMP_plugin_timestamp_t {
	 DWORD dwLowDateTime;
	 DWORD dwHighDateTime;
 }OpcMP_plugin_timestamp_t;
#ifdef __cplusplus
extern "C" {
#endif
#if defined(MPS_BUILD_AS_DLL)	/* { */

#if defined(MPS_LIB)	/* { */
#define MPS_API __declspec(dllexport)
#else						/* }{ */
#define MPS_API __declspec(dllimport)
#endif						/* } */
#else				/* }{ */
#define MPS_API		extern
#endif				/* } */

typedef int OpcMP_status_t; 
#define OPCMP_SUCCESS    0
#define OPCMP_BAD       -1
#define OPCMP_PLUGIN_EXPORT    __declspec(dllexport)

typedef struct mps_DataTag
 {
	int Type;
    bool			bVal; //0
	int				iVal; //1
	unsigned int	uiVal;//2
	float			fVal;
	double			dVal;
	USString		sVal;
	int				Qwality;
	unsigned long	timestamp;
	USString		Name;
	USString		FullName;
	int				Access;
 }mps_TagData;
 #define TT_BOOL   0  
 #define TT_INT    1   
 #define TT_UINT   2    
 #define TT_FLOAT  3 
 #define TT_DOUBLE 4 
 #define TT_STRING 5 
 #define NOTUSEVALUE 25252525.525 
 //
typedef OPCMP_PLUGIN_EXPORT void * (*OpcMP_plugin_create_t)(void *);
typedef OPCMP_PLUGIN_EXPORT OpcMP_status_t  (*OpcMP_plugin_init_t)(OpcMP_plugin_t*);
typedef OPCMP_PLUGIN_EXPORT OpcMP_status_t  (*OpcMP_plugin_run_t)(OpcMP_plugin_t*);
typedef OPCMP_PLUGIN_EXPORT OpcMP_status_t  (*OpcMP_plugin_read_t)(OpcMP_plugin_t*);
typedef OPCMP_PLUGIN_EXPORT OpcMP_status_t  (*OpcMP_plugin_write_t)(OpcMP_plugin_t*);
typedef OPCMP_PLUGIN_EXPORT OpcMP_status_t  (*OpcMP_plugin_close_t)(OpcMP_plugin_t*);
typedef OPCMP_PLUGIN_EXPORT OpcMP_status_t  (*OpcMP_plugin_slaveprocessing_t)(OpcMP_plugin_t*);
 //
 MPS_API bool (mps_isTagWriteOnly)(OpcMP_tag_t *);
 MPS_API bool (mps_isTagReadOnly)(OpcMP_tag_t *);
 MPS_API bool (mps_isTagReadWrite)(OpcMP_tag_t *);
 MPS_API void (mps_setTagQwality)(OpcMP_tag_t *,int QWALITY);
 MPS_API int  (mps_getTagQwality)(OpcMP_tag_t *);
 MPS_API bool (mps_setTagTimeStamp)(OpcMP_tag_t *tag,OpcMP_plugin_timestamp_t *);
 MPS_API bool (mps_getTagTimeStamp)(OpcMP_tag_t *tag,OpcMP_plugin_timestamp_t *);
 MPS_API void *(mps_getPluginData)(OpcMP_plugin_t *);
 MPS_API void  (mps_setPluginData)(OpcMP_plugin_t *,void *Data);
 MPS_API void *(mps_getPluginConfig)(OpcMP_plugin_t *);
 MPS_API int (mps_getNumberDeviceProperties)(OpcMP_plugin_t *);
 MPS_API void *(mps_getTagData)(OpcMP_tag_t *);
 MPS_API void (mps_setTagData)(OpcMP_tag_t *,void *Data);
 //
 MPS_API mps_Object	*(mps_getDeviceProperties)(OpcMP_plugin_t *);
 MPS_API int (mps_getNumberTagsProperties)(OpcMP_plugin_t *);
 //
 //MPS_API mps_Object *(mps_addDevice)(mps_Object *Devices,char *Name,char *Description);
 MPS_API mps_Object *(mps_addGroups)(mps_Object *);
 MPS_API mps_Object *(mps_addTags)(mps_Object *);
 MPS_API mps_Object *(mps_addSingleTags)( mps_Object * node);
 MPS_API mps_Object * (mps_addAnyTag)( mps_Object * node,const char *name,unsigned int editable,
		unsigned int type,
		unsigned int access,
		char *description);
 MPS_API mps_Object *(mps_addProperties)(mps_Object *Device);
 MPS_API mps_Object *(mps_createDeviceProperties)(void);
 //propeties
 
 MPS_API mps_Object *(mps_setHDAProperty)( mps_Object * node,bool Manual,bool Changed,int CountRecords);
 MPS_API mps_Object *(mps_addBooleanProperty)( mps_Object * node,unsigned int access,const char * name,	char * description,
	bool inival
	);

 MPS_API mps_Object *(mps_addIntegerProperty)( mps_Object * node,unsigned int access,const char * name,	char * description,
	int inival,
	int minval,
	int maxval
	);
 MPS_API mps_Object *(mps_addUIntegerProperty)( mps_Object * node,unsigned int access,const char * name,	char * description,
	int inival,
	int minval,
	int maxval
	);

 MPS_API mps_Object *(mps_addFloatProperty)( mps_Object * node,unsigned int access,const char * name,char * description,
	float inival,
	float minval,
	float maxval
	);
 MPS_API mps_Object *(mps_addDoubleProperty)( mps_Object * node,unsigned int access,const char * name,char * description,
	double inival,
	double minval,
	double maxval
	);
 MPS_API mps_Object *(mps_addStringProperty)( mps_Object * node,unsigned int access,const char * name,char * description,
	char *inival
	);
 MPS_API mps_Object *(mps_addBase64Property)( mps_Object * node,unsigned int access,const char * name, char * description,
	char *inival
	);

 MPS_API mps_Object *(mps_addComboProperty)( mps_Object * node,unsigned int access, const char * name, char * description,
	const char * inival,
	const char * casval
	);
 MPS_API mps_Object *(mps_addTagHDA)( mps_Object * node,bool mode,bool typerecord,int CountRecords);
 //
 MPS_API mps_Object * (mps_addGroup)(mps_Object * node,unsigned int editable,const char *name,const char *comment="");
 MPS_API mps_Object * (mps_addTag)( mps_Object * node, const char * region,const char * type = "int32",const char *accsess = "ReadWrite",const char *comment = " ");
 
 //
 MPS_API mps_sendandreceive_t  (mps_getSendAndReceive)(OpcMP_plugin_t *Plugin);
 MPS_API mps_writetohda_t  (mps_getWriteToHda)(OpcMP_plugin_t *Plugin);
 MPS_API mps_Object * (mps_createDeviceProperties)(void);
 MPS_API mps_Object * (mps_addTagWithCase)(mps_Object * node, const char * name,const char *type,const char *casetype,const char *access,const char *caseaccess,const char *comment = " ");
 MPS_API mps_Object * (mps_addProperties)( mps_Object * node);
 MPS_API mps_Object * (mps_addDevices)(mps_Object * node);
 MPS_API mps_Object * (mps_addSubDevices)(mps_Object * node);
 MPS_API mps_Object * (mps_addDevice)( mps_Object * node, const char * region,const char *comment = " ");
 MPS_API mps_Object * (mps_addSubDevice)( mps_Object * node, const char * region,const char *comment = " ");
 MPS_API mps_Object * (mps_addProperty)( mps_Object * node, const char * name,const char * description,
 const char * type,
 const char * inival,
 const char * minval="0",
 const char * maxval="0"
 );
 MPS_API OpcMP_plugin_info_t *(mps_plugin_info_create)(void *);
 MPS_API OpcMP_plugin_info_t *(mps_plugin_info_create_develop)(void *);
//
 MPS_API bool (mps_mutex_lock)(OpcMP_plugin_t *);
 MPS_API bool (mps_mutex_unlock)(OpcMP_plugin_t *);
 MPS_API void (mps_DebugMessage)(OpcMP_plugin_t *,char *);
 MPS_API bool (mps_isEnabledDebugMessages)(OpcMP_plugin_t *);
 MPS_API bool (mps_Sleep)(OpcMP_plugin_t   * plugin,unsigned long TimeOut);
 MPS_API void (mps_Message)(const OpcMP_plugin_t * plugin,char *Message);

// Properties
 MPS_API int (mps_getPluginNumberTags)(OpcMP_plugin_t *);
 MPS_API OpcMP_tag_t *(mps_getPluginTag)(OpcMP_plugin_t *,int Number);
 MPS_API mps_Object *(mps_getTagProperties)(OpcMP_plugin_t *,int Number);
 MPS_API bool (mps_property_as_bool)(mps_Object * JObject ,const char * NameProp,bool valinit);
 MPS_API int  (mps_property_as_int)(mps_Object * JObject ,const char * NameProp,int valinit);
 MPS_API unsigned int (mps_property_as_uint)(mps_Object * JObject ,const char * NameProp,unsigned int valinit);
 MPS_API float (mps_property_as_float)(mps_Object * JObject ,const char * NameProp,float valinit);
 MPS_API double (mps_property_as_double)(mps_Object * JObject ,const char * NameProp,double valinit);
 MPS_API char * (mps_property_as_string)(mps_Object * JObject ,const char * NameProp,const char * dflt);
//
 MPS_API mps_Object * (mps_addBooleanTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");
 MPS_API mps_Object * (mps_addIntegerTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");
 MPS_API mps_Object * (mps_addUIntegerTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");	
 MPS_API mps_Object * (mps_addFloatTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");	
 MPS_API mps_Object * (mps_addDoubleTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");	
 MPS_API mps_Object * (mps_addStringTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");		
 MPS_API mps_Object * (mps_addInt64Tag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");	
 MPS_API mps_Object * (mps_addUInt64Tag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");	
 MPS_API mps_Object * (mps_addByteTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");	
 MPS_API mps_Object * (mps_addSByteTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");	
 MPS_API mps_Object * (mps_addDateTimeTag)( mps_Object * node,const char *name,unsigned int editable=0,
		unsigned int access=OPCMP_AT_READWRITE,const char *description = " ");	

 MPS_API mps_Object * (OpcMP_addAnyTag)( mps_Object * node,const char *name,unsigned int editable=OPCMP_EN_ALL,
		unsigned int type =OPCMP_DT_BOOL|OPCMP_DT_INT|OPCMP_DT_UINT|OPCMP_DT_FLOAT|OPCMP_DT_DOUBLE|OPCMP_DT_STRING,
		unsigned int access=OPCMP_AT_READWRITE|OPCMP_AT_READONLY|OPCMP_AT_WRITEONLY,
		char *description = " ");			
 //
 MPS_API mps_Object * (mps_getDevicesProperties)(OpcMP_plugin_info_t *);
 MPS_API int (mps_getPluginIs)(OpcMP_plugin_info_t *);
 MPS_API OpcMP_plugin_read_t (mps_getPluginMethodRead)(OpcMP_plugin_t *);
 MPS_API OpcMP_plugin_slaveprocessing_t (mps_getPluginMethodSlaveProcessing)(OpcMP_plugin_t *);
 MPS_API OpcMP_plugin_write_t (mps_getPluginMethodWrite)(OpcMP_plugin_t *);
 MPS_API OpcMP_plugin_close_t (mps_getPluginMethodClose)(OpcMP_plugin_t *);

 MPS_API void (mps_setPluginMethodRead)(OpcMP_plugin_t *,OpcMP_plugin_read_t);
 MPS_API void (mps_setPluginMethodSlaveProcessing)(OpcMP_plugin_t *,OpcMP_plugin_slaveprocessing_t);
 MPS_API void (mps_setPluginMethodWrite)(OpcMP_plugin_t *,OpcMP_plugin_write_t);
 MPS_API void (mps_setPluginMethodClose)(OpcMP_plugin_t *,OpcMP_plugin_close_t);
 MPS_API void (mps_setPluginMethodSlaveProcessing)(OpcMP_plugin_t *,OpcMP_plugin_slaveprocessing_t);
 MPS_API char * (mps_getPluginDllName)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_setPluginDllName)(OpcMP_plugin_t *plugin,char *Name);
 // Objects
 MPS_API mps_Object * (mps_getObjectItem)(mps_Object *,char *);
 MPS_API mps_Object * (mps_getArrayItem)(mps_Object *,int);
 MPS_API int (mps_getArraySize)(mps_Object *);
 MPS_API char * (mps_getNameItem)(mps_Object *Object);
 MPS_API char * (mps_getValueItem)(mps_Object *Object);
 MPS_API bool (mps_ItemIsObject)(mps_Object *Object);
 MPS_API char *(mps_getShortDescription)(OpcMP_plugin_info_t *);
 MPS_API char *(mps_getLongDescription)(OpcMP_plugin_info_t *);
 MPS_API char *(mps_getProtocolName)(OpcMP_plugin_info_t *);
 MPS_API bool (mps_setProtocolName)(OpcMP_plugin_info_t *,char *ProtocolName);
 MPS_API void *(mps_getPluginDevice)(OpcMP_plugin_t *);
 MPS_API void (mps_setPluginDevice)(OpcMP_plugin_t *,void *);
 MPS_API void (mps_setPluginSubDevice)(OpcMP_plugin_t *plugin, void *PluginSubDevice);
 //
 MPS_API void (mps_addTagProperties)(OpcMP_plugin_t *,mps_Object *);
 MPS_API bool (mps_initPluginTags)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_tag_t * (mps_addPluginTag)(OpcMP_plugin_t *plugin,OpcMP_tag_t *tag);
 MPS_API void  (mps_setPluginMutex)(OpcMP_plugin_t *plugin,void *mutex); 
 MPS_API void (mps_setPluginAnswerTimeOut)(OpcMP_plugin_t *plugin,int ato);
 MPS_API void (mps_setPluginRepeatCount)(OpcMP_plugin_t *plugin,int rc);
 MPS_API int  (mps_getPluginRepeatCount)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_setPluginRepeatCountForWrite)(OpcMP_plugin_t *plugin,int rc);
 MPS_API int  (mps_getPluginRepeatCountForWrite)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_setTagMaxRepeatCount)(OpcMP_tag_t *Tag,int rc);
 MPS_API int  (mps_getTagMaxRepeatCount)(OpcMP_tag_t *Tag);
 MPS_API void (mps_setTagRepeatCount)(OpcMP_tag_t *Tag,int rc);
 MPS_API int  (mps_getTagRepeatCount)(OpcMP_tag_t *Tag);
 MPS_API void (mps_setTagRepeatCountForWrite)(OpcMP_tag_t *tag,int rc);
 MPS_API int (mps_getTagRepeatCountForWrite)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagMaxRepeatCountForWrite)(OpcMP_tag_t *tag,int rc);
 MPS_API int (mps_getTagMaxRepeatCountForWrite)(OpcMP_tag_t *tag);

 
 MPS_API void (mps_setPluginRepeatConnection)(OpcMP_plugin_t *plugin,int rcon);
 MPS_API void (mps_setPluginReinitNode)(OpcMP_plugin_t *plugin,bool reinit);
 MPS_API void (mps_setPluginEnableDebugMessages)(OpcMP_plugin_t *plugin,bool edm);
 MPS_API void (mps_setTagName)(OpcMP_tag_t *tag,char *Name);
 MPS_API char * (mps_getTagFullName)(OpcMP_tag_t *tag);
 MPS_API char * (mps_getTagName)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagFullName)(OpcMP_tag_t *tag,char *Name);
 MPS_API char * (mps_getTagFullName)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagVariantValue)(OpcMP_tag_t *tag,void *usv);
 MPS_API void *(mps_getTagVariantValue)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagInternalNumber)(OpcMP_tag_t *tag,size_t Number);
 MPS_API size_t  (mps_getTagInternalNumber)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagAccessReadWrite)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagAccessReadOnly)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagAccessWriteOnly)(OpcMP_tag_t *tag);
 MPS_API void (mps_setPluginMethodSleep)(OpcMP_plugin_t *plugin,void *plugin_sleep);
 MPS_API void (mps_setPluginMethodSendAndReceive)(OpcMP_plugin_t *plugin,void *plugin_sendandreceive);
 MPS_API void (mps_setPluginMethodMessage)(OpcMP_plugin_t *plugin,void *plugin_message);
 MPS_API void (mps_setPluginMethodIsTerminated)(OpcMP_plugin_t *plugin,void *plugin_isterminated);
 MPS_API void (mps_setPluginMethodWriteToHda)(OpcMP_plugin_t *plugin,void *plugin_writetohda);
 
 MPS_API void  (mps_setPluginMethodSendToBuffer)(OpcMP_plugin_t *plugin,void *plugin_sendtobuffer);
 MPS_API void *(mps_getPluginMethodSendToBuffer)(OpcMP_plugin_t *plugin);
 MPS_API void  (mps_setPluginMethodGetFromBuffer)(OpcMP_plugin_t *plugin,void *plugin_getfrombuffer);
 MPS_API void *(mps_getPluginMethodGetFromBuffer)(OpcMP_plugin_t *plugin);
 
 MPS_API void (mps_delPluginDeviceProperties)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_delPluginTagsProperties)(OpcMP_plugin_t *plugin); 
 MPS_API void (mps_freePluginData)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_plugin_t * (mps_initPluginData)(void);
 MPS_API mps_Object *(mps_CreateObject)();
 MPS_API mps_Object *(mps_ParseObject)(char *StringObject); 
 MPS_API mps_Object *(mps_ParseObject)(char *StringObject);
 MPS_API void (mps_DeleteObject)(mps_Object *Object);
 MPS_API void (mps_AddItemToObject)(mps_Object *Object,char *Name,mps_Object *AddObject1);
 MPS_API mps_Object * (mps_CreateStringObject)(char *string);
 //MPS_API void (mps_initPluginDeviceProperties)(OpcMP_plugin_t *plugin);
 //MPS_API void (mps_initPluginTagsProperties)(OpcMP_plugin_t *plugin);
 //
 MPS_API void (mps_addPluginDeviceProperty)(OpcMP_plugin_t *plugin,char *NameProperty,char *IniVal);
 MPS_API void (mps_initPluginReadTags)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_addPluginReadTag)(OpcMP_plugin_t *plugin,OpcMP_tag_t *tag);
 MPS_API int (mps_getPluginNumberReadTags)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_tag_t * (mps_getPluginReadTag)(OpcMP_plugin_t *plugin,int Number);
 
 MPS_API void (mps_initPluginWriteTags)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_addPluginWriteTag)(OpcMP_plugin_t *plugin,OpcMP_tag_t *tag);
 MPS_API int (mps_getPluginNumberWriteTags)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_tag_t * (mps_getPluginWriteTag)(OpcMP_plugin_t *plugin,int Number);

 // read-write tag
 MPS_API bool (mps_isTagDirty)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagDirty)(OpcMP_tag_t *tag,bool Dirty);
 MPS_API bool (mps_isTagHBW)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagHBW)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagIBW)(OpcMP_tag_t *tag);
 
 MPS_API void (mps_setTagAsDouble)(OpcMP_tag_t *tag,double Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsFloat)(OpcMP_tag_t *tag,float Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsInt)(OpcMP_tag_t *tag,int Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsUInt)(OpcMP_tag_t *tag,unsigned int Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsBoolean)(OpcMP_tag_t *tag,bool Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsString)(OpcMP_tag_t *tag,char *Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_getTag)(OpcMP_tag_t *,mps_TagData *);

 MPS_API double (mps_getTagAsDouble)(OpcMP_tag_t *tag);
 MPS_API float  (mps_getTagAsFloat)(OpcMP_tag_t *tag);
 MPS_API int    (mps_getTagAsInt)(OpcMP_tag_t *tag);
 MPS_API unsigned int (mps_getTagAsUInt)(OpcMP_tag_t *tag);
 MPS_API bool   (mps_getTagAsBoolean)(OpcMP_tag_t *tag);
 MPS_API char * (mps_getTagAsString)(OpcMP_tag_t *tag);
 MPS_API OpcMP_Boolean(mps_getTagAsStringToBuffer)(OpcMP_tag_t *tag, OpcMP_String Buffer, OpcMP_UInt32 BufferLen, OpcMP_UInt32 *Qwality = NULL, OpcMP_plugin_timestamp_t *SystemTime = NULL);
  //
 MPS_API bool (mps_isTagTypeBoolean)(OpcMP_tag_t *tag);
 MPS_API bool (mps_isTagTypeInt)(OpcMP_tag_t *tag);
 MPS_API bool (mps_isTagTypeUInt)(OpcMP_tag_t *tag);
 MPS_API bool (mps_isTagTypeFloat)(OpcMP_tag_t *tag);
 MPS_API bool (mps_isTagTypeDouble)(OpcMP_tag_t *tag);
 MPS_API bool (mps_isTagTypeString)(OpcMP_tag_t *tag);
 MPS_API OpcMP_BuiltInType (mps_getTagDataType)(OpcMP_tag_t *tag);
 MPS_API OpcMP_AccessType (mps_getTagAccessType)(OpcMP_tag_t *tag);
 MPS_API void (mps_free)(OpcMP_plugin_t *plugin,void *data);
 MPS_API void *(mps_malloc)(OpcMP_plugin_t *plugin,int size);
 MPS_API void *(mps_realloc)(OpcMP_plugin_t *plugin,void *ptr, int size);

 MPS_API int (mps_getPluginAnswerTimeOut)(OpcMP_plugin_t *plugin);
 MPS_API int (mps_getPluginRepeatCount)(OpcMP_plugin_t *plugin);
 MPS_API int (mps_getPluginRepeatCountForWrite)(OpcMP_plugin_t *plugin);
 MPS_API int (mps_getPluginRepeatConnection)(OpcMP_plugin_t *plugin);
 MPS_API bool (mps_getPluginReinitNode)(OpcMP_plugin_t *plugin);
 MPS_API void *(mps_getPluginSubDevice)(OpcMP_plugin_t *plugin);
 MPS_API void *(mps_getPluginMethodDataReady)(OpcMP_plugin_t *plugin);
 MPS_API void *(mps_setPluginMethodDataReady)(OpcMP_plugin_t *plugin,void *);
 MPS_API bool (mps_isTerminated)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_plugin_timestamp_t *(mps_getTimeStamp)(OpcMP_plugin_timestamp_t *);
 MPS_API  unsigned int  (mps_getSizeOfTimeStamp)(void);
 MPS_API  OpcMP_plugin_timestamp_t * (mps_addMSecond)(OpcMP_plugin_timestamp_t *timestamp, int count);
 MPS_API  OpcMP_plugin_timestamp_t * (mps_addSecond)(OpcMP_plugin_timestamp_t *timestamp, int count);
 MPS_API  OpcMP_plugin_timestamp_t * (mps_addMunute)(OpcMP_plugin_timestamp_t *timestamp, int count);
 MPS_API  OpcMP_plugin_timestamp_t * (mps_addHour)(OpcMP_plugin_timestamp_t *timestamp, int count);
 MPS_API  OpcMP_plugin_timestamp_t * (mps_addDay)(OpcMP_plugin_timestamp_t *timestamp, int count);
 MPS_API  bool  (mps_setDataReady)(OpcMP_plugin_t * plugin, unsigned int count);
 MPS_API  bool  (mps_WriteTagToHDA)(OpcMP_plugin_t *Plugin, OpcMP_tag_t *Tag);
 MPS_API  OpcMP_Boolean (mps_setTagHDA)(OpcMP_tag_t *tag, OpcMP_Boolean IsHDA, OpcMP_Boolean HDAMode, OpcMP_Boolean HDATypeRecord, OpcMP_UInt32 HDACountRecords);
 MPS_API  OpcMP_Boolean (mps_getTagHDA)(OpcMP_tag_t *tag,OpcMP_Boolean *HDAMode, OpcMP_Boolean *HDATypeRecord, OpcMP_UInt32 *HDACountRecords);
 MPS_API OpcMP_Boolean(mps_setPluginNodeType)(OpcMP_plugin_t *plugin,OpcMP_UInt32 NodeType);
 MPS_API OpcMP_UInt32(mps_getPluginNodeType)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_setPluginMethodSetPortOptions)(OpcMP_plugin_t *plugin,void *setportoptions);
 MPS_API void (mps_setPluginMethodGetPortOptions)(OpcMP_plugin_t *plugin, void *getportoptions);
 MPS_API void (mps_setPluginPortOptions)(OpcMP_plugin_t *plugin, OpcMP_UInt32 Speed, OpcMP_UInt32 Paritet, OpcMP_UInt32 Bit, OpcMP_UInt32 Stop);
 MPS_API void (mps_getPluginPortOptions)(OpcMP_plugin_t *plugin, OpcMP_UInt32 *Speed, OpcMP_UInt32 *Paritet, OpcMP_UInt32 *Bit, OpcMP_UInt32 *Stop);
// NOW
 MPS_API OpcMP_tag_t *(mps_getPluginTagByNumber)(OpcMP_plugin_t *plugin, int Number); 
 MPS_API OpcMP_tag_t * (mps_addPluginAllTag)(OpcMP_plugin_t *plugin,OpcMP_tag_t *tag);
 MPS_API OpcMP_tag_t * (mps_addSubDeviceAllTag)(OpcMP_subdevice_t *SubDevice, OpcMP_tag_t *tag);
 MPS_API OpcMP_tag_t * (mps_addSubDeviceTag)(OpcMP_subdevice_t *SubDevice, OpcMP_tag_t *tag);
 MPS_API int (mps_getPluginTagsNumber)(OpcMP_plugin_t *);
 MPS_API int (mps_getPluginAllTagsNumber)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_tag_t *(mps_getPluginAllTagByNumber)(OpcMP_plugin_t *plugin, int Number);
 MPS_API OpcMP_tag_t *(mps_getPluginTagByNumber)(OpcMP_plugin_t *plugin, int Number);
 MPS_API int (mps_getSubDeviceNumberAllTags)(OpcMP_plugin_t *SubDevice);
 MPS_API int (mps_getSubDeviceNumberTags)(OpcMP_plugin_t *SubDevice);
 MPS_API OpcMP_tag_t *(mps_getSubDeviceAllTag)(OpcMP_subdevice_t *SubDevice, int Number);
 MPS_API OpcMP_tag_t *(mps_getSubDeviceTag)(OpcMP_plugin_t *SubDevice, int Number);
 MPS_API OpcMP_tag_t * (mps_createPluginTag)(OpcMP_plugin_t *plugin, int Access, int DataType);
 MPS_API OpcMP_tag_t * (mps_createPluginTagNew)(OpcMP_plugin_t *plugin,int Access,int DataType,
						size_t InternalNumber,
						int Qwality,
						char *FullName,
						char *Name,
						char *DeviceID,
						char *SubDeviceID,
						char *GroupID,
						char *TagID,
						OpcMP_Boolean ReadAfterWrite,
						OpcMP_UInt32 MaxRepeatCountForWrite,
						OpcMP_UInt32 RepeatCountForWrite,
						OpcMP_Boolean IsHDA,
						OpcMP_Boolean HDASaveAutomatic,
						OpcMP_Boolean HDASaveIfChange,
						OpcMP_UInt32 HDACountRecords
 );
 MPS_API OpcMP_Boolean(mps_addPluginSubDevice)(OpcMP_plugin_t *plugin, OpcMP_plugin_t *SubDevice);
 MPS_API OpcMP_Boolean(mps_delPluginSubDevice)(OpcMP_plugin_t *plugin, OpcMP_plugin_t *SubDevice);
 MPS_API OpcMP_UInt32(mps_getPluginSubDevicesNumber)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_plugin_t *(mps_getPluginSubDeviceByNumber)(OpcMP_plugin_t *plugin, OpcMP_UInt32 Number);
 MPS_API OpcMP_plugin_t *(mps_getPluginSubDeviceByID)(OpcMP_plugin_t *plugin, OpcMP_String ID);
 MPS_API OpcMP_UInt32 (mps_getPluginPropertiesNumber)(OpcMP_plugin_t *plugin);
 MPS_API mps_Object	*(mps_getPluginProperties)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_Void (mps_setPluginNeedScan)(OpcMP_plugin_t *plugin, OpcMP_Boolean NeedScan);
 MPS_API OpcMP_Boolean (mps_getPluginNeedScan)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_Void(mps_setTagNeedScan)(OpcMP_tag_t *tag, OpcMP_Boolean NeedScan);
 MPS_API OpcMP_Boolean (mps_getTagNeedScan)(OpcMP_tag_t *tag);
 MPS_API OpcMP_Void (mps_setPluginNeedWrite)(OpcMP_plugin_t *plugin, OpcMP_Boolean NeedWrite);
 MPS_API OpcMP_Boolean (mps_getPluginNeedWrite)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_UInt32(mps_getPluginSamplingInterval)(OpcMP_plugin_t *plugin);
 MPS_API OpcMP_Boolean(mps_setPluginSamplingInterval)(OpcMP_plugin_t *plugin, OpcMP_UInt32 SamplingInterval);
 MPS_API OpcMP_Boolean (mps_setTagReadAfterWrite)(OpcMP_tag_t *tag, OpcMP_Boolean ReadAfterWrite);
 MPS_API OpcMP_Boolean (mps_getTagReadAfterWrite)(OpcMP_tag_t *tag);
 
//
 MPS_API void (mps_setTagAsInt16)(OpcMP_tag_t *tag,OpcMP_Int16 Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsUInt16)(OpcMP_tag_t *tag,OpcMP_UInt16 Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsInt64)(OpcMP_tag_t *tag,OpcMP_Int64 Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsUInt64)(OpcMP_tag_t *tag,OpcMP_UInt64 Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsByte)(OpcMP_tag_t *tag,OpcMP_Byte Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API void (mps_setTagAsSByte)(OpcMP_tag_t *tag,OpcMP_SByte Val,int Qwality=192,OpcMP_plugin_timestamp_t *SystemTime=0);
 MPS_API OpcMP_Boolean (mps_setTagAsDateTime)(OpcMP_tag_t *tag, OpcMP_plugin_timestamp_t *DateTime, int Qwality = 192, OpcMP_plugin_timestamp_t           *SystemTime = 0);
 MPS_API OpcMP_Boolean (mps_setTagAsByteString)(OpcMP_tag_t *tag, OpcMP_String ByteStringBuf, OpcMP_Int32 Len, int Qwality = 192, OpcMP_plugin_timestamp_t *SystemTime = 0);
 
 MPS_API OpcMP_Int16    (mps_getTagAsInt16)(OpcMP_tag_t *tag);
 MPS_API OpcMP_UInt16   (mps_getTagAsUInt16)(OpcMP_tag_t *tag);
 MPS_API OpcMP_Int64    (mps_getTagAsInt64)(OpcMP_tag_t *tag);
 MPS_API OpcMP_UInt64   (mps_getTagAsUInt64)(OpcMP_tag_t *tag);
 MPS_API OpcMP_Byte    (mps_getTagAsByte)(OpcMP_tag_t *tag);
 MPS_API OpcMP_SByte   (mps_getTagAsSByte)(OpcMP_tag_t *tag);
 MPS_API OpcMP_Boolean (mps_getTagAsDateTime)(OpcMP_tag_t *tag, OpcMP_plugin_timestamp_t *DateTime,OpcMP_UInt32 *Qwality = NULL, OpcMP_plugin_timestamp_t *SystemTime = NULL);
 MPS_API OpcMP_Boolean mps_getTagAsByteString(OpcMP_tag_t *tag, OpcMP_String ByteStringBuf, OpcMP_Int32 *Len);

 MPS_API char * (mps_getTagGroupID)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagGroupID)(OpcMP_tag_t *tag,char *GroupID);
 MPS_API char * (mps_getTagDeviceID)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagDeviceID)(OpcMP_tag_t *tag,char *DeviceID);
 MPS_API char * (mps_getTagSubDeviceID)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagSubDeviceID)(OpcMP_tag_t *tag,char *SubDeviceID);
 MPS_API char * (mps_getTagID)(OpcMP_tag_t *tag);
 MPS_API void (mps_setTagID)(OpcMP_tag_t *tag,char *TagID);
 MPS_API char * (mps_getPluginID)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_setPluginID)(OpcMP_plugin_t *plugin,char *DeviceID);
 MPS_API OpcMP_tag_t * (mps_getPluginTagByID)(OpcMP_plugin_t *plugin, char *TagID);
 MPS_API OpcMP_plugin_t * (mps_getPluginDevicePlugin)(OpcMP_plugin_t *plugin);
 MPS_API void (mps_setPluginDevicePlugin)(OpcMP_plugin_t *plugin, void *deviceplugin);

 MPS_API void (mps_setPluginMethodSyncDriverData)(OpcMP_plugin_t *plugin,void *plugin_syncdriverdata);
 MPS_API bool (mps_SyncDriverData)(OpcMP_plugin_t *plugin,void **tags,OpcMP_UInt32 len);
#ifdef __cplusplus
}
#endif
#endif
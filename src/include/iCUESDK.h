#pragma once

#include "iCUESDKGlobal.h"

#ifdef __cplusplus
extern "C"
{
#endif

const unsigned int CORSAIR_STRING_SIZE_S = 64;        // small string length
const unsigned int CORSAIR_STRING_SIZE_M = 128;       // medium string length
const unsigned int CORSAIR_LAYER_PRIORITY_MAX = 255;  // maximum level of layer’s priority that can be used in CorsairSetLayerPriority
const unsigned int CORSAIR_DEVICE_COUNT_MAX = 64;     // maximum number of devices to be discovered
const unsigned int CORSAIR_DEVICE_LEDCOUNT_MAX = 512; // maximum number of LEDs controlled by device

// defines a character array of length CORSAIR_DEVICE_ID_MAX to store device identifier string
typedef char CorsairDeviceId[CORSAIR_STRING_SIZE_M];

// defines a type that specifies a LED identifier that is guaranteed to be unique for a specific device
typedef unsigned int CorsairLedLuid;

enum CorsairError // contains shared list of all errors which could happen during calling of Corsair* functions
{
	CE_Success = 0,               // if previously called function completed successfully
	CE_NotConnected = 1,          // if iCUE is not running or was shut down or third-party control is disabled in iCUE settings (runtime error), or if developer did not call CorsairConnect after calling CorsairDisconnect or on app start (developer error)
	CE_NoControl = 2,             // if some other client has or took over exclusive control (runtime error)
	CE_IncompatibleProtocol = 3,  // if developer is calling the function that is not supported by the server (either because protocol has broken by server or client or because the function is new and server is too old. Check CorsairSessionDetails for details) (developer error)
	CE_InvalidArguments = 4,      // if developer supplied invalid arguments to the function (for specifics look at function descriptions) (developer error)
	CE_InvalidOperation = 5,      // if developer is calling the function that is not allowed due to current state (reading improper properties from device, or setting callback when it has already been set) (developer error)
	CE_DeviceNotFound = 6,        // if invalid device id has been supplied as an argument to the function (when device id refers to disconnected device) (runtime error)
	CE_NotAllowed = 7             // if specific functionality (key interception) is disabled in iCUE settings (runtime error)
};

enum CorsairSessionState // contains a list of all possible session states
{
	CSS_Invalid = 0,              // dummy value
	CSS_Closed = 1,               // client not initialized or client closed connection (initial state)
	CSS_Connecting = 2,           // client initiated connection but not connected yet
	CSS_Timeout = 3,              // server did not respond, sdk will try again
	CSS_ConnectionRefused = 4,    // server did not allow connection
	CSS_ConnectionLost = 5,       // server closed connection
	CSS_Connected = 6             // successfully connected
};

enum CorsairDeviceType // contains list of available device types
{
	CDT_Unknown = 0x0000,           // for unknown/invalid devices
	CDT_Keyboard = 0x0001,          // for keyboards
	CDT_Mouse = 0x0002,             // for mice
	CDT_Mousemat = 0x0004,          // for mousemats
	CDT_Headset = 0x0008,           // for headsets
	CDT_HeadsetStand = 0x0010,      // for headset stands
	CDT_FanLedController = 0x0020,  // for DIY-devices like Commander PRO
	CDT_LedController = 0x0040,     // for DIY-devices like Lighting Node PRO
	CDT_MemoryModule = 0x0080,      // for memory modules
	CDT_Cooler = 0x0100,            // for coolers
	CDT_Motherboard = 0x0200,       // for motherboards
	CDT_GraphicsCard = 0x0400,      // for graphics cards
	CDT_Touchbar = 0x0800,          // for touchbars
	CDT_GameController = 0x1000,    // for game controllers
	CDT_All = 0xFFFFFFFF            // for all devices
};

enum CorsairEventId // contains list of event identifiers
{
	CEI_Invalid = 0, // dummy value,
	CEI_DeviceConnectionStatusChangedEvent = 1,
	CEI_KeyEvent = 2
};

enum CorsairMacroKeyId // contains a shared list of G, M and S keys (not all available keys!)
{
	CMKI_Invalid = 0,
	CMKI_1 = 1,
	CMKI_2 = 2,
	CMKI_3 = 3,
	CMKI_4 = 4,
	CMKI_5 = 5,
	CMKI_6 = 6,
	CMKI_7 = 7,
	CMKI_8 = 8,
	CMKI_9 = 9,
	CMKI_10 = 10,
	CMKI_11 = 11,
	CMKI_12 = 12,
	CMKI_13 = 13,
	CMKI_14 = 14,
	CMKI_15 = 15,
	CMKI_16 = 16,
	CMKI_17 = 17,
	CMKI_18 = 18,
	CMKI_19 = 19,
	CMKI_20 = 20
};

enum CorsairDevicePropertyId // contains list of properties identifiers which can be read from device
{
	CDPI_Invalid = 0,                     // dummy value
	CDPI_PropertyArray = 1,               // array of CorsairDevicePropertyId members supported by device
	CDPI_MicEnabled = 2,                  // indicates Mic state (On or Off); used for headset, headset stand
	CDPI_SurroundSoundEnabled = 3,        // indicates Surround Sound state (On or Off); used for headset, headset stand
	CDPI_SidetoneEnabled = 4,             // indicates Sidetone state (On or Off); used for headset (where applicable)
	CDPI_EqualizerPreset = 5,             // the number of active equalizer preset (integer, 1 - 5); used for headset, headset stand
	CDPI_PhysicalLayout = 6,              // keyboard physical layout (see CorsairPhysicalLayout for valid values); used for keyboard
	CDPI_LogicalLayout = 7,               // keyboard logical layout (see CorsairLogicalLayout for valid values); used for keyboard
	CDPI_MacroKeyArray = 8,               // array of programmable G, M or S keys on device
	CDPI_BatteryLevel = 9,                // battery level (0 - 100); used for wireless devices
	CDPI_ChannelLedCount = 10,            // total number of LEDs connected to the channel
	CDPI_ChannelDeviceCount = 11,         // number of LED-devices (fans, strips, etc.) connected to the channel which is controlled by the DIY device
	CDPI_ChannelDeviceLedCountArray = 12, // array of integers, each element describes the number of LEDs controlled by the channel device
	CDPI_ChannelDeviceTypeArray = 13      // array of CorsairChannelDeviceType members, each element describes the type of the channel device
};

enum CorsairDataType // contains list of available property types
{
	CT_Boolean = 0,          // for property of type Boolean
	CT_Int32 = 1,            // for property of type Int32 or Enumeration
	CT_Float64 = 2,          // for property of type Float64
	CT_String = 3,           // for property of type String
	CT_Boolean_Array = 16,   // for array of Boolean
	CT_Int32_Array = 17,     // for array of Int32
	CT_Float64_Array = 18,   // for array of Float64
	CT_String_Array = 19     // for array of String
};

enum CorsairPropertyFlag // contains list of operations that can be applied to the property
{
	CPF_None = 0x00,
	CPF_CanRead = 0x01,     // describes readable property
	CPF_CanWrite = 0x02,    // describes writable property
	CPF_Indexed = 0x04      // if flag is set, then index should be used to read/write multiple properties that share the same property identifier
};

enum CorsairPhysicalLayout // contains list of available physical layouts for keyboards
{
	CPL_Invalid = 0,
	CPL_US = 1,
	CPL_UK = 2,
	CPL_JP = 3,
	CPL_KR = 4,
	CPL_BR = 5
};

enum CorsairLogicalLayout // contains list of available logical layouts for keyboards
{
	CLL_Invalid = 0,
	CLL_US_Int = 1,
	CLL_NA = 2,
	CLL_EU = 3,
	CLL_UK = 4,
	CLL_BE = 5,
	CLL_BR = 6,
	CLL_CH = 7,
	CLL_CN = 8,
	CLL_DE = 9,
	CLL_ES = 10,
	CLL_FR = 11,
	CLL_IT = 12,
	CLL_ND = 13,
	CLL_RU = 14,
	CLL_JP = 15,
	CLL_KR = 16,
	CLL_TW = 17,
	CLL_MEX = 18
};

enum CorsairChannelDeviceType // contains list of the LED-devices which can be connected to the DIY-device, memory module or cooler
{
	CCDT_Invalid = 0,
	CCDT_HD_Fan = 1,
	CCDT_SP_Fan = 2,
	CCDT_LL_Fan = 3,
	CCDT_ML_Fan = 4,
	CCDT_QL_Fan = 5,
	CCDT_8LedSeriesFan = 6,
	CCDT_Strip = 7,
	CCDT_DAP = 8,
	CCDT_Pump = 9,
	CCDT_DRAM = 10,
	CCDT_WaterBlock = 11,
	CCDT_QX_Fan = 12,
};

enum CorsairAccessLevel // contains list of available SDK access levels
{
	CAL_Shared = 0,                                         // shared mode (default)
	CAL_ExclusiveLightingControl = 1,                       // exclusive lightings, but shared events
	CAL_ExclusiveKeyEventsListening = 2,                    // exclusive key events, but shared lightings
	CAL_ExclusiveLightingControlAndKeyEventsListening = 3   // exclusive mode
};

struct CorsairVersion // contains information about version that consists of three components
{
	int major;
	int minor;
	int patch;
};

struct CorsairSessionDetails // contains information about SDK and iCUE versions
{
	CorsairVersion clientVersion;       // version of SDK client (like {4,0,1}). Always contains valid value even if there was no iCUE found. Must comply with the semantic versioning rules.
	CorsairVersion serverVersion;       // version of SDK server (like {4,0,1}) or empty struct ({0,0,0}) if the iCUE was not found. Must comply with the semantic versioning rules.
	CorsairVersion serverHostVersion;   // version of iCUE (like {3,33,100}) or empty struct ({0,0,0}) if the iCUE was not found.
};

struct CorsairSessionStateChanged // contains information about session state and client/server versions
{
	CorsairSessionState state;       // new session state which SDK client has been transitioned to
	CorsairSessionDetails details;   // information about client/server versions
};

struct CorsairDeviceInfo // contains information about device
{
	CorsairDeviceType type;                // enum describing device type
	CorsairDeviceId id;                    // null terminated Unicode string that contains unique device identifier
	char serial[CORSAIR_STRING_SIZE_M];    // null terminated Unicode string that contains device serial number. Can be empty, if serial number is not available for the device
	char model[CORSAIR_STRING_SIZE_M];     // null terminated Unicode string that contains device model (like “K95RGB”)
	int ledCount;                          // number of controllable LEDs on the device
	int channelCount;                      // number of channels controlled by the device
};

struct CorsairLedPosition // contains led id and position of led
{
	CorsairLedLuid id;    // unique identifier of led
	double cx;            /* for keyboards, mice, mousemats, headset stands and memory modules values are */
	double cy;            /* in mm, for DIY-devices, headsets and coolers values are in logical units     */
};

struct CorsairDeviceFilter // contains device search filter
{
	int deviceTypeMask;  // mask that describes device types, formed as logical “or” of CorsairDeviceType enum values
};

struct CorsairDeviceConnectionStatusChangedEvent // contains information about device that was connected or disconnected
{
	CorsairDeviceId deviceId; // null terminated Unicode string that contains unique device identifier
	bool isConnected;         // true if connected, false if disconnected
};

struct CorsairKeyEvent // contains information about device where G, M or S key was pressed/released and the key itself
{
	CorsairDeviceId deviceId; // null terminated Unicode string that contains unique device identifier
	CorsairMacroKeyId keyId;  // G, M or S key that was pressed/released
	bool isPressed;           // true if pressed, false if released
};

struct CorsairEvent // contains information about event id and event data
{
	CorsairEventId id; // event identifier
	union
	{
		const CorsairDeviceConnectionStatusChangedEvent *deviceConnectionStatusChangedEvent; // when id == CEI_DeviceConnectionStatusChangedEvent contains valid pointer to structure with information about connected or disconnected device
		const CorsairKeyEvent *keyEvent; // when id == CEI_KeyEvent contains valid pointer to structure with information about pressed or released G, M or S button and device where this event happened
	};
};

struct CorsairDataType_BooleanArray // represents an array of boolean values
{
	bool *items;          // an array of boolean values
	unsigned int count;   // number of items array elements
};

struct CorsairDataType_Int32Array // represents an array of integer values
{
	int *items;           // an array of integer values
	unsigned int count;   // number of items array elements
};

struct CorsairDataType_Float64Array // represents an array of double values
{
	double *items;        // an array of double values
	unsigned int count;   // number of items array elements
};

struct CorsairDataType_StringArray // represents an array of pointers to null terminated strings
{
	char **items;         // an array of pointers to null terminated strings
	unsigned int count;   // number of items array elements
};

union CorsairDataValue // a union of all property data types
{
	bool boolean;                                // actual property value if it’s type is CPDT_Boolean
	int int32;                                   // actual property value if it’s type is CPDT_Int32
	double float64;                              // actual property value if it’s type is CPDT_Float64
	char* string;                                // actual property value if it’s type is CPDT_String
	CorsairDataType_BooleanArray boolean_array;  // actual property value if it’s type is CPDT_Boolean_Array
	CorsairDataType_Int32Array int32_array;      // actual property value if it’s type is CPDT_Int32_Array
	CorsairDataType_Float64Array float64_array;  // actual property value if it’s type is CPDT_Float64_Array
	CorsairDataType_StringArray string_array;    // actual property value if it’s type is CPDT_String_Array
};

struct CorsairProperty // contains information about device property type and value
{
	CorsairDataType type;    // type of property
	CorsairDataValue value;  // property value
};

struct CorsairLedColor // contains information about LED and its color
{
	CorsairLedLuid id;   // unique identifier of led
	unsigned char r;     // red brightness [0..255]
	unsigned char g;     // green brightness [0..255]
	unsigned char b;     // blue brightness [0..255]
	unsigned char a;     // alpha channel [0..255]. The opacity of the color from 0 for completely translucent to 255 for opaque
};

struct CorsairKeyEventConfiguration // contains information about key event configuration
{
	CorsairMacroKeyId keyId;  // G, M or S key
	bool isIntercepted;       // flag that defines how key event should behave. If true then iCUE will pass the event to an active exclusive SDK client and stop passing it to the rest SDK clients. If false then iCUE will resume sending it to all SDK clients
};

// callback that is called by SDK when session state changed
typedef void(*CorsairSessionStateChangedHandler)(void *context, const CorsairSessionStateChanged *eventData);

// callback that is called by SDK when colors are set
typedef void(*CorsairAsyncCallback)(void *context, CorsairError error);

// callback that is called by SDK when some event happened
typedef void(*CorsairEventHandler)(void *context, const CorsairEvent *event);

// sets handler for session state changes, checks versions of SDK client, server and host (iCUE) to understand which of SDK functions can be used with this version of iCUE
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairConnect(CorsairSessionStateChangedHandler onStateChanged, void *context);

// checks versions of SDK client, server and host (iCUE) to understand which of SDK functions can be used with this version of iCUE. If there is no active session or client is not connected to the server, then only client version will be filled
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairGetSessionDetails(CorsairSessionDetails *details);

// removes handler for session state changes previously set by CorsairConnect
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairDisconnect();

// populates the buffer with filtered collection of devices
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairGetDevices(const CorsairDeviceFilter *filter, int sizeMax, CorsairDeviceInfo *devices, int *size);

// gets information about device specified by deviceId
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairGetDeviceInfo(const CorsairDeviceId deviceId, CorsairDeviceInfo *deviceInfo);

// provides a list of supported device LEDs by its id with their positions. Position could be either physical (only device-dependent) or logical (depend on device as well as iCUE settings)
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairGetLedPositions(const CorsairDeviceId deviceId, int sizeMax, CorsairLedPosition *ledPositions, int *size);

// registers a callback that will be called by SDK when some event happened. If client is already subscribed but calls this function again SDK should use only last callback registered for sending notifications
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairSubscribeForEvents(CorsairEventHandler onEvent, void *context);

// unregisters callback previously registered by CorsairSubscribeForEvents call
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairUnsubscribeFromEvents();

// this function gives possibility for a client with ExclusiveKeyEventsListening or ExclusiveLightingControlAndKeyEventsListening access level to control selected set of macro keys only and let iCUE to pass some key events to other shared clients
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairConfigureKeyEvent(const CorsairDeviceId deviceId, const CorsairKeyEventConfiguration *config);

// gets information about device property for the device specified by deviceId
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairGetDevicePropertyInfo(const CorsairDeviceId deviceId, CorsairDevicePropertyId propertyId, unsigned int index, CorsairDataType *dataType, unsigned int *flags);

// gets the data of device property by device identifier, property identifier and property index
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairReadDeviceProperty(const CorsairDeviceId deviceId, CorsairDevicePropertyId propertyId, unsigned int index, CorsairProperty *property);

// sets the data of device property by device identifier, property identifier and property index. Can be called only with writable properties
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairWriteDeviceProperty(const CorsairDeviceId deviceId, CorsairDevicePropertyId propertyId, unsigned int index, const CorsairProperty *property);

// frees memory occupied by CorsairProperty instance
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairFreeProperty(CorsairProperty *property);

// sets specified LEDs to some colors. The color is retained until changed by successive calls. This function does not take logical layout into account. This function executes synchronously, if you are concerned about delays consider using CorsairSetLedColorsBuffer together with CorsairSetLedColorsFlushBufferAsync
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairSetLedColors(const CorsairDeviceId deviceId, int size, const CorsairLedColor *ledColors);

// sets specified LEDs to some colors. This function sets LEDs colors in the buffer which is written to the devices via CorsairSetLedColorsFlushBufferAsync. Typical usecase is next: CorsairSetLedColorsFlushBufferAsync is called to write LEDs colors to the device and follows after one or more calls of CorsairSetLedColorsBuffer to set the LEDs buffer. This function does not take logical layout into account
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairSetLedColorsBuffer(const CorsairDeviceId deviceId, int size, const CorsairLedColor *ledColors);

// writes to the devices LEDs colors buffer which is previously filled by the CorsairSetLedColorsBuffer function. This function executes asynchronously and returns control to the caller immediately
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairSetLedColorsFlushBufferAsync(CorsairAsyncCallback callback, void *context);

// get current color for the list of requested LEDs of supported device. The color should represent the actual state of the hardware LED, which could be a combination of SDK and/or iCUE input
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairGetLedColors(const CorsairDeviceId deviceId, int size, CorsairLedColor *ledColors);

// set layer priority for this shared client. By default iCUE has priority of 127 and all shared clients have priority of 128 if they don’t call this function. Layers with higher priority value are shown on top of layers with lower priority
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairSetLayerPriority(unsigned int priority);

// retrieves LED luid for key name taking logical layout into account. So on AZERTY keyboards if user calls CorsairGetLedLuidForKeyName(‘A’, &luid) he gets luid with CLK_Q code. This luid can be used in CorsairSetLedColors or CorsairSetLedColorsBuffer function
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairGetLedLuidForKeyName(const CorsairDeviceId deviceId, char keyName, CorsairLedLuid *ledId);

// requests control using specified access level. By default client has shared control over lighting and events so there is no need to call CorsairRequestControl() unless client requires exclusive control
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairRequestControl(const CorsairDeviceId deviceId, CorsairAccessLevel accessLevel);

// releases previously requested control for specified device. This action resets access level to default (shared)
CORSAIR_ICUE_SDK_EXPORT CorsairError CorsairReleaseControl(const CorsairDeviceId deviceId);

#ifdef __cplusplus
} //exten "C"
#endif

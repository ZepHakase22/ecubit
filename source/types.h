#if ( !defined(TYPES_H) || defined(GENERATE_ENUM_STRINGS) )

#if (!defined(GENERATE_ENUM_STRINGS))
	#define TYPES_H
#endif

#include <string>
#include "ftd2xx.h"
#include "EnumToString.h"

#if (!defined(GENERATE_ENUM_STRINGS))
#define LOG_LEVEL(mode) LOGCFG.headers = false; \
                        LOGCFG.level = mode; 

typedef struct _parser {
    _parser() {
        isListing=false;
        isSerialNumber=true;
        isMultiThread=false;
        port=0;
        numBytes=0;
        capacity=0;
    }
    bool isListing;
    bool isSerialNumber;
    bool isMultiThread;
    std::string value;
    DWORD numBytes;
    WORD capacity;
    std::string address;
    uint port;
} parser;

parser parse(int argc,char *argv[]);

template<typename ... Args>
std::string stringFormat(std::string fmt, Args&& ... args);

typedef enum tagOpenMode {
    SERIAL_NUMBER,
    DESCRIPTION
} openMode;

#endif //GENERATE_ENUM_STRINGS

BEGIN_ENUM(DEVICE) 
{
	DECL_ENUM(FTBM),
	DECL_ENUM(FTAM),
	DECL_ENUM(FT100AX),
	DECL_ENUM(FTUNKNOWN),
	DECL_ENUM(FT2232C),
	DECL_ENUM(FT232R),
	DECL_ENUM(FT2232H),
	DECL_ENUM(FT4232H),
	DECL_ENUM(FT232H),
	DECL_ENUM(FTXSERIES),
	DECL_ENUM(FT4222H0),
	DECL_ENUM(FT4222H12),
	DECL_ENUM(FT4222H3),
    DECL_ENUM(FT4222PROG),
} 
END_ENUM(DEVICE);

BEGIN_ENUM(DEVICE_VERSION)
{
    DECL_ENUM_ELEMENT(V_FT232B,Rev4 (FT232B) extensions),
    DECL_ENUM_ELEMENT(V_FT2232,Rev 5 (FT2232) extensions),
    DECL_ENUM_ELEMENT(V_FT232R,Rev 6 (FT232R) extensions),
    DECL_ENUM_ELEMENT(V_FT2232H,Rev 7 (FT2232H) Extensions),
    DECL_ENUM_ELEMENT(V_FT4232H,Rev 8 (FT4232H) Extensions),
    DECL_ENUM_ELEMENT(V_FT232H,Rev 9 (FT232H) Extensions)
}
END_ENUM(DEVICE_VERSION);

#endif
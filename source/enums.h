#if ( !defined(ENUMS_H) || defined(GENERATE_ENUM_STRINGS) )

#if (!defined(GENERATE_ENUM_STRINGS))
	#define ENUMS_H
#endif

#include "EnumToString.h"

#include "ftd2xx.h"

BEGIN_ENUM(ftdErrors) 
{
    DECL_ENUM_ELEMENT(FT_OK,OK),
    DECL_ENUM_ELEMENT(FT_INVALID_HANDLE,Invalid handle),
    DECL_ENUM_ELEMENT(FT_DEVICE_NOT_FOUND,Device not found),
    DECL_ENUM_ELEMENT(FT_DEVICE_NOT_OPENED,Device not opened),
    DECL_ENUM_ELEMENT(FT_IO_ERROR,Device I/O error),
    DECL_ENUM_ELEMENT(FT_INSUFFICIENT_RESOURCES,Insufficient resources),
    DECL_ENUM_ELEMENT(FT_INVALID_PARAMETER,Invalid parameter),
    DECL_ENUM_ELEMENT(FT_INVALID_BAUD_RATE,Invalid baud rate),
    DECL_ENUM_ELEMENT(FT_DEVICE_NOT_OPENED_FOR_ERASE,Device not opened for erase),
    DECL_ENUM_ELEMENT(FT_DEVICE_NOT_OPENED_FOR_WRITE,Device not opened for write),
    DECL_ENUM_ELEMENT(FT_FAILED_TO_WRITE_DEVICE,Failed to write to device),
    DECL_ENUM_ELEMENT(FT_EEPROM_READ_FAILED,EEPROM read failed),
    DECL_ENUM_ELEMENT(FT_EEPROM_WRITE_FAILED,EEPROM write failed),
    DECL_ENUM_ELEMENT(FT_EEPROM_ERASE_FAILED,EEPROM erase failed),
    DECL_ENUM_ELEMENT(FT_EEPROM_NOT_PRESENT,EEPROM not present),
    DECL_ENUM_ELEMENT(FT_EEPROM_NOT_PROGRAMMED,EEPROM not programmed),
    DECL_ENUM_ELEMENT(FT_INVALID_ARGS,Invalid args),
    DECL_ENUM_ELEMENT(FT_NOT_SUPPORTED,Not supported),
    DECL_ENUM_ELEMENT(FT_OTHER_ERROR,Other error),
    DECL_ENUM_ELEMENT(FT_DEVICE_LIST_NOT_READY,Device list not ready),
}
END_ENUM(ftdErrors)

#endif
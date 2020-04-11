#if ( !defined(ENUMS_H) || defined(GENERATE_ENUM_STRINGS) )

#if (!defined(GENERATE_ENUM_STRINGS))
	#define ENUMS_H
#endif

#include "EnumToString.h"

#include "ftd2xx.h"

BEGIN_ENUM(ftdErrors) 
{
    DECL_ENUM_ELEMENT(OK,OK),
    DECL_ENUM_ELEMENT(INVALID_HANDLE1,Invalid handle),
    DECL_ENUM_ELEMENT(DEVICE_NOT_FOUND,Device not found),
    DECL_ENUM_ELEMENT(DEVICE_NOT_OPENED,Device not opened),
    DECL_ENUM_ELEMENT(IO_ERROR,Device I/O error),
    DECL_ENUM_ELEMENT(INSUFFICIENT_RESOURCES,Insufficient resources),
    DECL_ENUM_ELEMENT(INVALID_PARAMETER,Invalid parameter),
    DECL_ENUM_ELEMENT(INVALID_BAUD_RATE,Invalid baud rate),
    DECL_ENUM_ELEMENT(DEVICE_NOT_OPENED_FOR_ERASE,Device not opened for erase),
    DECL_ENUM_ELEMENT(DEVICE_NOT_OPENED_FOR_WRITE,Device not opened for write),
    DECL_ENUM_ELEMENT(FAILED_TO_WRITE_DEVICE,Failed to write to device),
    DECL_ENUM_ELEMENT(EEPROM_READ_FAILED,EEPROM read failed),
    DECL_ENUM_ELEMENT(EEPROM_WRITE_FAILED,EEPROM write failed),
    DECL_ENUM_ELEMENT(EEPROM_ERASE_FAILED,EEPROM erase failed),
    DECL_ENUM_ELEMENT(EEPROM_NOT_PRESENT,EEPROM not present),
    DECL_ENUM_ELEMENT(EEPROM_NOT_PROGRAMMED,EEPROM not programmed),
    DECL_ENUM_ELEMENT(INVALID_ARGS,Invalid args),
    DECL_ENUM_ELEMENT(NOT_SUPPORTED,Not supported),
    DECL_ENUM_ELEMENT(OTHER_ERROR,Other error),
    DECL_ENUM_ELEMENT(DEVICE_LIST_NOT_READY,Device list not ready),
    DECL_ENUM_ELEMENT(DEVICE_DISCONNECTED,Device not connected to the USB),
    DECL_ENUM_ELEMENT(PERMISSION_DENIED,Permission denied),
    DECL_ENUM_ELEMENT(DEVICE_OPENED,Device already opened by other),
    DECL_ENUM_ELEMENT(NO_D2XX_245FIFO_SUPPORT,Device was not configured for D2XX and 245FIFO)
}
END_ENUM(ftdErrors)

#endif
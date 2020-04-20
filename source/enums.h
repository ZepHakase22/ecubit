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
    DECL_ENUM_ELEMENT(NO_SUPPORTED_DEVICE,Device not supported or not configured for D2XX and 245FIFO use),
    DECL_ENUM_ELEMENT(BAD_BLOCK, Data Allocation failure: bad_block),
    DECL_ENUM_ELEMENT(DEVICE_NOT_POWERED, Device not powered)
}
END_ENUM(ftdErrors)


BEGIN_ENUM(socketErrors) 
{
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EBADF,9,Bad file number),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EINTR,4,Interrupted system call),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EIO,5,Input/output error),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_ENOSPC,28,No space left on device),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EDQUOT,122,Quota exceeded),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EACCES,13,Permission denied),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EAGAIN,11,Try again),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EFAULT,14,Bad address),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EALREADY,37,Operation already in progress),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_ECONNRESET,54,Connection reset by peer),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EDESTADDRREQ,39,Destination address required),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EINVAL,22,Invalid argument),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EISCONN,56,Socket is already connected),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EMSGSIZE,40,Message too long),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_ENOBUFS,55,No buffer space available),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_ENOMEM,12,Cannot allocate memory),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_ENOTCONN,57,Socket is not connected),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_ENOTSOCK,57,Socket operation on non-socket),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EOPNOTSUPP,57,Operation not supported on socket),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EPIPE,32,Broken pipe),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EAFNOSUPPORT,97,Address family not supported by protocol),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EMFILE,24,Too many open files),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_ENFILE,23,File table overflow),
    DECL_ENUM_CASUAL_ELEMENT(SOCK_EPROTONOSUPPORT,93,Protocol not supported),
}
END_ENUM(socketErrors)

BEGIN_ENUM(addrinfoErrors)
{
    DECL_ENUM_ELEMENT(E_ADDRFAMILY,Address family for host not supported),
    DECL_ENUM_ELEMENT(E_AGAIN,Temporary failure in name resolution),
    DECL_ENUM_ELEMENT(E_BADFLAGS,Invalid value for ai_flags),
    DECL_ENUM_ELEMENT(E_FAIL,Non-recoverable failure in name resolution),
    DECL_ENUM_ELEMENT(E_FAMILY,Ai_family not supported),
    DECL_ENUM_ELEMENT(E_MEMORY,Memory allocation failure),
    DECL_ENUM_ELEMENT(E_NODATA,No address associated with host),
    DECL_ENUM_ELEMENT(E_NONAME,Host nor service provided or not known),
    DECL_ENUM_ELEMENT(E_SERVICE,Service not supported for ai_socktype),
    DECL_ENUM_ELEMENT(E_SOCKTYPE,Ai_socktype not supported),
    DECL_ENUM_ELEMENT(E_SYSTEM,System error returned in errno)
}
END_ENUM(addrinfoErrors)
#endif
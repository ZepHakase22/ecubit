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

#if !defined(_WIN32)
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
    DECL_ENUM_ELEMENT(E_FAILURE,Non-recoverable failure in name resolution),
    DECL_ENUM_ELEMENT(E_FAMILY,Ai_family not supported),
    DECL_ENUM_ELEMENT(E_MEMORY,Memory allocation failure),
    DECL_ENUM_ELEMENT(E_NODATA,No address associated with host),
    DECL_ENUM_ELEMENT(E_NONAME,Host nor service provided or not known),
    DECL_ENUM_ELEMENT(E_SERVICE,Service not supported for ai_socktype),
    DECL_ENUM_ELEMENT(E_SOCKTYPE,Ai_socktype not supported),
    DECL_ENUM_ELEMENT(E_SYSTEM,System error returned in errno)
}
END_ENUM(addrinfoErrors)
#else
BEGIN_ENUM(addrinfoErrors)
{
    DECL_ENUM_CASUAL_ELEMENT(SYSNOTREADY, 10091,Network subsystem is unavailable),
    DECL_ENUM_CASUAL_ELEMENT(VERNOTSUPPORTED, 10092,Winsock.dll version out of range),
    DECL_ENUM_CASUAL_ELEMENT(EINPROGRESS2, 10036,Operation now in progress),
    DECL_ENUM_CASUAL_ELEMENT(EPROCLIM, 10067,Too many processes),
    DECL_ENUM_CASUAL_ELEMENT(EFAULT2, 10014,Bad address)
}
END_ENUM(addrinfoErrors)

BEGIN_ENUM(socketErrors)
{
    DECL_ENUM_CASUAL_ELEMENT(NOTINITIALISED, 10093,A successful WSAStartup call must occur before using this function),
        DECL_ENUM_CASUAL_ELEMENT(EAFNOSUPPORT2, 10047,The specified address family is not supported),
        DECL_ENUM_CASUAL_ELEMENT(EINPROGRESS3, 10036,A blocking Windows Sockets call is in progress or the service provider is still processing a callback function),
        DECL_ENUM_CASUAL_ELEMENT(EMFILE2, 10024,No more socket descriptors are available),
        DECL_ENUM_CASUAL_ELEMENT(EINVAL2, 10022,An invalid argument was supplied),
        DECL_ENUM_CASUAL_ELEMENT(EINVALIDPROVIDER,10105,The service provider returned a version other than 2.2),
        DECL_ENUM_CASUAL_ELEMENT(EINVALIDPROCTABLE,10104,The service provider returned an invalid or incomplete procedure table to the WSPStartup),
        DECL_ENUM_CASUAL_ELEMENT(ENOBUFS2, 10055,No buffer space is available),
        DECL_ENUM_CASUAL_ELEMENT(EPROTONOSUPPORT2,10043,The specified protocol is not supported),
        DECL_ENUM_CASUAL_ELEMENT(EPROTOTYPE2, 10041,The specified protocol is the wrong type for this socket),
        DECL_ENUM_CASUAL_ELEMENT(EPROVIDERFAILEDINIT, 10106,The service provider failed to initialize),
        DECL_ENUM_CASUAL_ELEMENT(ESOCKTNOSUPPORT, 10044,The specified socket type is not supported in this address family),
        DECL_ENUM_CASUAL_ELEMENT(EACCES2, 10013,An attempt was made to access a socket in a way forbidden by its access permissions),
        DECL_ENUM_CASUAL_ELEMENT(EADDRINUSE2, 10048,Address already in use),
        DECL_ENUM_CASUAL_ELEMENT(EFAULT3, 10014,Bad address),
        DECL_ENUM_CASUAL_ELEMENT(ENOTSOCK2, 10038,Socket operation on nonsocket),
        DECL_ENUM_CASUAL_ELEMENT(ENETDOWN2, 10050,Network is down),
        DECL_ENUM_CASUAL_ELEMENT(EINTR2, 10004,A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall),
        DECL_ENUM_CASUAL_ELEMENT(ENETRESET2, 10004, The connection has been broken due to keep - alive activity detecting a failure while the operation was in progress),
        DECL_ENUM_CASUAL_ELEMENT(ENOTCONN2, 10057, Socket is not connected),
        DECL_ENUM_CASUAL_ELEMENT(EOPNOTSUPP2, 10045, Operation not supported),
        DECL_ENUM_CASUAL_ELEMENT(ESHUTDOWN, 1058, Cannot send after socket shutdown),
        DECL_ENUM_CASUAL_ELEMENT(EWOULDBLOCK2, 10035, Resource temporarily unavailable),
        DECL_ENUM_CASUAL_ELEMENT(EMSGSIZE2, 10040, Message too long),
        DECL_ENUM_CASUAL_ELEMENT(EHOSTUNREACH2, 10065, No route to host),
        DECL_ENUM_CASUAL_ELEMENT(ECONNABORTED2, 10053, Software caused connection abort),
        DECL_ENUM_CASUAL_ELEMENT(ECONNRESET2, 10054, Connection reset by peer),
        DECL_ENUM_CASUAL_ELEMENT(EADDRNOTAVAIL2, 10049, Cannot assign requested address),
        DECL_ENUM_CASUAL_ELEMENT(EDESTADDRREQ2, 10039, Destination address required),
        DECL_ENUM_CASUAL_ELEMENT(ENETUNREACH2, 10051, Network is unreachable),
        DECL_ENUM_CASUAL_ELEMENT(ETIMEDOUT2, 10060, Connection timed out)
}
END_ENUM(socketErrors)
#endif
#endif
#if ( !defined(FTD_DEVICE_H))
#define FTD_DEVICE_H

#include <string>
#include "ftd2xx.h"

using namespace std;
class ftdDevice {
    private:

    bool isHighSpeed;
    FT_DEVICE ftDeviceType;
    ULONG id;
    string serialNumber;
    string description;
    FT_HANDLE handle;

    ftdDevice();
    
    protected:

    public:

    ftdDevice(bool isHighSpeed, FT_DEVICE ftDeviceType, ULONG id,
                         string serialNumber, string description, FT_HANDLE hable);
};

#endif // FTD_DEVICE_H
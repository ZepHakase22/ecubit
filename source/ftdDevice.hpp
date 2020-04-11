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

    bool get_isHighSpeed() const { return isHighSpeed; }
    FT_DEVICE get_ftDeviceType() const { return ftDeviceType; }
    ULONG get_id() const { return id; }
    const string get_serialNumber() const { return serialNumber; }
    const string get_description() const { return description; }
};

#endif // FTD_DEVICE_H
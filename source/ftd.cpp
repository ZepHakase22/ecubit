#include <memory>

#include "ftd2xx.h"
#include "ftdException.hpp"
#include "ftd.hpp"

using namespace std;
using namespace FTDI;

ftd::ftd() {
    FT_STATUS ftStatus;
    DWORD dwDevicesNumber;
    using deviceInfo = shared_ptr<FT_DEVICE_LIST_INFO_NODE[]>;

    ftStatus=FT_CreateDeviceInfoList(&dwDevicesNumber);
    if(ftStatus != FT_OK) {
        ftdThrow(ftStatus);
    } else {
        if(!dwDevicesNumber) {
          ftdThrow(DEVICE_DISCONNECTED);
        }
    }
    auto buf = deviceInfo(new FT_DEVICE_LIST_INFO_NODE[dwDevicesNumber]);
    ftStatus = FT_GetDeviceInfoList(buf.get(),&dwDevicesNumber);
    if(ftStatus != FT_OK) {
        ftdThrow(ftStatus);
    }
    for(uint i=0; i < dwDevicesNumber; i++ ) {
        if(buf[i].Flags & FT_FLAGS_OPENED) {
            if(buf[i].Type == FT_DEVICE_UNKNOWN) {
                ftdThrowInfo(PERMISSION_DENIED, "You must be root to run this program: \
                run as superuser or join your user to root group");
            }
            continue;
        }
        ftdDevice device((buf[i].Flags & FT_FLAGS_HISPEED)?true:false,buf[i].Type,buf[i].ID,
            string(buf[i].SerialNumber),string(buf[i].Description),buf[i].ftHandle);
        devices.push_back(device);
    }
    if(devices.size()==0) {
        ftdThrow(DEVICE_OPENED);
    }
}
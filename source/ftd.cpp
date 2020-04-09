#include <memory>

#include "ftd2xx.h"
#include "ftdException.hpp"
#include "ftd.hpp"

using namespace std;
using namespace FTDI;

ftd::ftd() {
    using deviceInfo = shared_ptr<FT_DEVICE_LIST_INFO_NODE>;
    FT_STATUS ftStatus;
    DWORD dwDevicesNumbers;

    ftStatus=FT_CreateDeviceInfoList(&dwDevicesNumbers);
    if(ftStatus != FT_OK) {
        ftdThrow(ftStatus);
    }
    auto buf = deviceInfo(new FT_DEVICE_LIST_INFO_NODE[dwDevicesNumbers]);
    ftStatus = FT_GetDeviceInfoList(buf.get(),&dwDevicesNumbers);


}
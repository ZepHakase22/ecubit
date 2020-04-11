#include <memory>
#include <string>

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
bool ftd::icompare(const string & str1,const string &str2)
{
    return ( (str1.size() == str2.size() ) &&
            std::equal(str1.begin(), str1.end(), str2.begin(),[this] (const char & c1,const  char &c2){
                return (c1==c2 || toupper(c1)==toupper(c2));
            }));
}

void ftd::openBySerialNumber(const string &serialNumber) {
    for (vector<ftdDevice>::iterator it = devices.begin(); it!= devices.end(); ++it) {
        if(!icompare(serialNumber,it->get_serialNumber())) {
            selectedDevice->open(SERIAL_NUMBER);
            if(it->evaluateSpecification()) {
                selectedDevice = make_shared<ftdDevice>(*it);
                mode = SERIAL_NUMBER;
                break;
            } else {
                ftdThrow(NO_D2XX_245FIFO_SUPPORT);
            }
        }
    }
}
void ftd::openByDescription(const string &description) {
    for (vector<ftdDevice>::iterator it = devices.begin(); it!= devices.end(); ++it) {
        if(!icompare(description,it->get_description())) {
            selectedDevice->open(DESCRIPTION);
            if(it->evaluateSpecification()) {
                selectedDevice = make_shared<ftdDevice>(*it);
                mode = DESCRIPTION;
                break;
            } else {
                ftdThrow(NO_D2XX_245FIFO_SUPPORT);
            }
        }
    }
}

#include "ftdException.hpp"
#include "ftdDevice.hpp"

using namespace FTDI;

ftdDevice::ftdDevice(bool isHighSpeed_, FT_DEVICE ftDeviceType_, ULONG id_,
                         string serialNumber_, string description_, FT_HANDLE handle_) {

    isHighSpeed = isHighSpeed_;
    ftDeviceType = ftDeviceType_;
    id =id_;
    serialNumber = serialNumber_;
    description = description_;
    handle = handle_;
}

bool ftdDevice::evaluateSpecification() {
    FT_PROGRAM_DATA Data;
    FT_STATUS ftStatus;

    Data.Signature1 = 0x00000000;
    Data.Signature2 = 0xffffffff;
    Data.Manufacturer = new char[256];
    Data.ManufacturerId = new char[256];
    Data.Description = new char[256]; 
    Data.SerialNumber = new char[256];
    
    if (Data.Manufacturer == NULL || Data.ManufacturerId == NULL || Data.Description == NULL ||
        Data.SerialNumber == NULL)
    {

    }

    ftStatus = FT_EE_Read(handle, &Data);
    if(ftStatus != FT_OK) {
        ftdThrow(ftStatus);
    }
    return true;
}
void ftdDevice::open(const openMode &mode) {
    FT_STATUS ftStatus;

    if(mode==SERIAL_NUMBER) {
        ftStatus = FT_OpenEx((PVOID)serialNumber.c_str(),FT_OPEN_BY_SERIAL_NUMBER,&handle);
    } else {
        ftStatus = FT_OpenEx((PVOID)description.c_str(),FT_OPEN_BY_SERIAL_NUMBER,&handle);
    }
    if(ftStatus != FT_OK)
        ftdThrow(ftStatus);
}



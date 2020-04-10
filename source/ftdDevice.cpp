#include "ftdDevice.hpp"

ftdDevice::ftdDevice(bool isHighSpeed_, FT_DEVICE ftDeviceType_, ULONG id_,
                         string serialNumber_, string description_, FT_HANDLE handle_) {

    isHighSpeed = isHighSpeed_;
    ftDeviceType = ftDeviceType_;
    id =id_;
    serialNumber = serialNumber_;
    description = description_;
    handle = handle_;
}
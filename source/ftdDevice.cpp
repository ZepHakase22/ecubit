#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include "ftdException.hpp"
#include "ftdDevice.hpp"

using namespace std;
using namespace FTDI;

ftdDevice::ftdDevice(bool isHighSpeed_, FT_DEVICE ftDeviceType_, ULONG id_,
                         string serialNumber_, string description_, FT_HANDLE handle_) {

    isHighSpeed = isHighSpeed_;
    ftDeviceType = (DEVICE)ftDeviceType_;
    id =id_;
    serialNumber = serialNumber_;
    description = description_;
    handle = handle_;
}

void ftdDevice::evaluateSpecification() {
    FT_PROGRAM_DATA Data;
    FT_STATUS ftStatus;

    Data.Signature1 = 0x00000000;
    Data.Signature2 = 0xffffffff;
    Data.Version = 0xffffffff;
    std::shared_ptr<char> ptr(new char[256], std::default_delete<char[]>());
    Data.Manufacturer = Data.ManufacturerId = Data.Description = Data.SerialNumber =NULL;

    Data.Manufacturer = new char[256];
    Data.ManufacturerId = new char[256];
    Data.Description =  new char[256];
    Data.SerialNumber = new char[256];
 
    if((Data.Manufacturer == NULL) || (Data.ManufacturerId == NULL) ||
        (Data.SerialNumber == NULL) || (Data.Description == NULL)) {
        delete [] Data.ManufacturerId;
        delete [] Data.Manufacturer;
        delete [] Data.Description;
        delete [] Data.SerialNumber;
        ftdThrow(BAD_BLOCK);
    }

    ftStatus = FT_EE_Read(handle, &Data);
    if(ftStatus != FT_OK) {
        ftdThrow(ftStatus);
    }
    if(Data.Version != 0xffffffff)
        ftDeviceVersion = (DEVICE_VERSION)Data.Version;
    else {
        switch (ftDeviceType) {
        case FTBM:
            ftDeviceVersion = V_FT232B;
            break;

        case FT2232C:
            ftDeviceVersion = V_FT2232;
            break;

        case FT232R:
            ftDeviceVersion = V_FT232R;
            break;

        case FT2232H:
            ftDeviceVersion = V_FT2232H;
            break;

        case FT4232H:
            ftDeviceVersion = V_FT4232H;
            break;

        case FT232H:
            ftDeviceVersion = V_FT232H;
            break;

        default:
            ftDeviceVersion = V_FTUNKNOWN;
        }
    }
    vendorId = Data.VendorId;
    productId = Data.ProductId;
    manufacturer = string(Data.Manufacturer);
    manufacturerId = string(Data.ManufacturerId);
    maxPower = Data.MaxPower;
    isPnp = Data.PnP==1;
    isSelfPowered = Data.SelfPowered==1;
    isRemoteWakeUp = Data.RemoteWakeup==1;
    char port = serialNumber[serialNumber.length()-1];
    isFifo245 = ((ftDeviceVersion == V_FT2232)  && ((port == 'A' && Data.IFAIsFifo == 1) || (port == 'B' && Data.IFBIsFifo == 1))) ||
                ((ftDeviceVersion == V_FT2232H) && ((port == 'A' && Data.IFAIsFifo7 == 1) || (port == 'B' && Data.IFBIsFifo7 == 1))) ||
                (ftDeviceVersion == V_FT232H && Data.IsFifoH == 1);
    isD2XX =    (ftDeviceVersion == V_FT232B) || 
                ((ftDeviceVersion == V_FT2232) && ((port == 'A' && Data.AIsVCP == 0) || (port == 'B' && Data.BIsVCP == 0))) ||
                ((ftDeviceVersion == V_FT232R) && (Data.RIsD2XX == 1)) ||
                ((ftDeviceVersion == V_FT2232H)  && ((port == 'A' && Data.AIsVCP7) == 0 || (port == 'B' && Data.BIsVCP7 == 0))) ||
                ((ftDeviceVersion == V_FT4232H ) && ((port == 'A' && Data.AIsVCP8) == 0 || (port == 'B' && Data.BIsVCP8 == 0) || 
                                                    (port == 'C' && Data.CIsVCP8 == 0) || (port == 'D' && Data.DIsVCP8 == 0))) ||
                (ftDeviceVersion == V_FT232H && Data.IsVCPH == 0);
    
    if((productId != 0x6010) || (vendorId != 0x0403) || !isFifo245 || !isD2XX ) {
        ftdThrowInfo(NO_SUPPORTED_DEVICE,  (string("Fifo 245: ") + (get_isFifo245()? "true" : "false") 
                        + string(" D2XX: ") + (get_isD2XX()? "true" : "false")).c_str());
    }
    delete [] Data.ManufacturerId;
    delete [] Data.Manufacturer;
    delete [] Data.Description;
    delete [] Data.SerialNumber;
}
void ftdDevice::open(const openMode &mode_) {
    FT_STATUS ftStatus;

    if(mode_==SERIAL_NUMBER) {
        ftStatus = FT_OpenEx((PVOID)serialNumber.c_str(),FT_OPEN_BY_SERIAL_NUMBER,&handle);
    } else {
        ftStatus = FT_OpenEx((PVOID)description.c_str(),FT_OPEN_BY_DESCRIPTION,&handle);
    }
    if(ftStatus != FT_OK)
        ftdThrow(ftStatus);
    mode=mode_;
}
void ftdDevice::close() {
    FT_STATUS ftStatus;

    ftStatus = FT_Close(handle);
    if(ftStatus != FT_OK)
        ftdThrow(ftStatus);

}
uint ftdDevice::read(shared_ptr<unsigned char[]> &output) {

	DWORD dwRxSize = 0;
    DWORD dwBytesRead = 0;
    FT_STATUS ftStatus;
    using readBuffer = shared_ptr<unsigned char[]>;
    uint nReset = 0;
    bool isOn = true;

    ftStatus = FT_Purge(handle, FT_PURGE_RX);
    if(ftStatus != FT_OK) 
        ftdThrow(ftStatus);
    DWORD prevDwRxSize = 0;
   do
	{
        if(!isOn) {
            close();
            this_thread::sleep_for(chrono::milliseconds(1));
            open(mode);
            LOG(WARN) << "****************************************"" Number of reset " 
                <<  ++nReset << endl;
            this_thread::sleep_for(chrono::milliseconds(10));
        }

        for(register uint i=0; i<1000; i++) {
            prevDwRxSize = dwRxSize;
            ftStatus = FT_GetQueueStatus(handle, &dwRxSize);
            if (ftStatus != FT_OK) {
                ftdThrow(ftStatus); 
            }
            if(dwRxSize==0 || prevDwRxSize == dwRxSize) {
                isOn = false;
                this_thread::sleep_for(chrono::milliseconds(1));
            } else {
                isOn = true;
                break;
            } 
        }
        TRACE   << "Read: " <<  dwRxSize << endl;
	} while(dwRxSize <= bufferSize);

     if(dwRxSize == 0) {
        ftdThrow(DEVICE_NOT_POWERED);
    } 
	auto buf = readBuffer(new unsigned char[dwRxSize]);
    ftStatus = FT_Read(handle, buf.get(), dwRxSize, &dwBytesRead);
    if (ftStatus != FT_OK) 
        ftdThrow(ftStatus);
    
    TRACE   << "Read: " << dwBytesRead << " of " << dwRxSize << " required:" << endl;
    
    output=buf;
    return dwBytesRead;

}
void ftdDevice::prepareToRead(const DWORD &capacity) {
    queue = make_shared<blocking_queue<readBuffer>>(capacity);
    thContinousRead = new thread([=] {continousRead();});
}
void ftdDevice::continousRead() {
    while(true) {
        shared_ptr<unsigned char[]> buff;
    
        readBuffer buffer;
        uint n=read(buff);
        buffer.size=n;
        buffer.buff=buff;
        queue->push(buffer);
    }
}

uint ftdDevice::readAsync(shared_ptr<unsigned char[]> &output)  {
    readBuffer buffer = queue->front();
    output = buffer.buff;
    queue->pop();
    return buffer.size;
}
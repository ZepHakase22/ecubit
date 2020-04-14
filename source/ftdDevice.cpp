#include <memory>
#include <string>
#include <sys/time.h>
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
    std::shared_ptr<char> ptr(new char[256], std::default_delete<char[]>());
    Data.Manufacturer = Data.ManufacturerId = Data.Description = Data.SerialNumber =NULL;

    Data.Manufacturer = new char[256];
    Data.ManufacturerId = new char[256];
    Data.Description =  new char[256];
    Data.SerialNumber = new char[256];
 
    if((Data.ManufacturerId == NULL) || (Data.ManufacturerId == NULL) ||
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
    ftDeviceVersion = (DEVICE_VERSION)Data.Version;
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
void ftdDevice::read(const DWORD &numberOfBytesToRead, string &output) {

    struct timeval  startTime;
	DWORD dwRxSize = 0;
    DWORD dwBytesRead = 0;
    long int timeout = 60; // seconds
    FT_STATUS ftStatus;
    using readBuffer = shared_ptr<char[]>;

	gettimeofday(&startTime, NULL);
	for (int queueChecks = 0; dwRxSize < numberOfBytesToRead; queueChecks++)
	{
		// Periodically check for time-out 
		if (queueChecks % 128 == 0) {
			struct timeval now;
			struct timeval elapsed;
			
			gettimeofday(&now, NULL);
			timersub(&now, &startTime, &elapsed);

			if (elapsed.tv_sec > timeout) 
				break;

            TRACE << ((queueChecks == 0)? "Number of bytes in D2XX receive-queue: " : ", ") << (int)dwRxSize << endl; 

    		ftStatus = FT_GetQueueStatus(handle, &dwRxSize);
    		if (ftStatus != FT_OK)
    			ftdThrow(ftStatus);
        }
	}

    TRACE << "Got" << dwRxSize << "(of " << numberOfBytesToRead << ")" << endl;

	auto buf = readBuffer(new char[dwRxSize]);
    ftStatus = FT_Read(handle, buf.get(), dwRxSize, &dwBytesRead);
    if (ftStatus != FT_OK) 
        ftdThrow(ftStatus);
    
    TRACE   << "Read: " << dwBytesRead << " of " << dwRxSize << " required:" << endl
            << buf << endl;

    output= buf.get();
}
void ftdDevice::continousRead(const DWORD &numberOfBytesToRead, shared_ptr<blocking_queue<string>> queue) {
   struct timeval  startTime;
	DWORD dwRxSize = 0;
    DWORD dwBytesRead = 0;
    long int timeout = 60; // seconds
    FT_STATUS ftStatus;
    using readBuffer = shared_ptr<char[]>;

    while(true) {
        gettimeofday(&startTime, NULL);
        for (int queueChecks = 0; dwRxSize < numberOfBytesToRead; queueChecks++)
        {
            // Periodically check for time-out 
            if (queueChecks % 128 == 0) {
                struct timeval now;
                struct timeval elapsed;
                
                gettimeofday(&now, NULL);
                timersub(&now, &startTime, &elapsed);

                if (elapsed.tv_sec > timeout) 
                    break;

                TRACE << ((queueChecks == 0)? "Number of bytes in D2XX receive-queue: " : ", ") << (int)dwRxSize << endl; 

                ftStatus = FT_GetQueueStatus(handle, &dwRxSize);
                if (ftStatus != FT_OK)
                    ftdThrow(ftStatus);
            }
        }
        TRACE << "Got" << dwRxSize << "(of " << numberOfBytesToRead << ")" << endl;

        auto buf = readBuffer(new char[dwRxSize]);
        ftStatus = FT_Read(handle, buf.get(), dwRxSize, &dwBytesRead);
        if (ftStatus != FT_OK) 
            ftdThrow(ftStatus);
        
        TRACE   << "Read: " << dwBytesRead << " of " << dwRxSize << " required:" << endl
                << buf << endl;

        queue->push(string(buf.get()));
    }
}
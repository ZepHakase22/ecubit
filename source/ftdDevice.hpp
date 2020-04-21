#if ( !defined(FTD_DEVICE_H))
#define FTD_DEVICE_H

#include <string>
#include <utility>
#include "ftd2xx.h"
#include "types.h"
#include "blocking_queue.hpp"


using namespace std;
namespace FTDI {
    class ftdDevice {
        private:

        bool isHighSpeed;
        DEVICE ftDeviceType;
        ULONG id;
        string serialNumber;
        string description;
        FT_HANDLE handle;
        DEVICE_VERSION ftDeviceVersion;
        WORD vendorId;
        WORD productId;
        string manufacturer;
        string manufacturerId;
        WORD maxPower;
        bool isPnp;
        bool isSelfPowered;
        bool isRemoteWakeUp;
        bool isFifo245;
        bool isD2XX;
        openMode mode;
        ulong bufferSize;
        shared_ptr<blocking_queue<readBuffer>> queue;
        thread *thContinousRead;

        protected:

        public:
        ftdDevice() { handle=0; }
        ~ftdDevice(){ FT_Close(handle); handle=0; }

        ftdDevice(bool isHighSpeed, FT_DEVICE ftDeviceType, ULONG id,
                            string serialNumber, string description, FT_HANDLE hable);

        bool get_isHighSpeed() const { return isHighSpeed; }
        DEVICE get_ftDeviceType() const { return ftDeviceType; }
        const string get_ftStringDeviceType() const { return GetStringDEVICE(ftDeviceType);}
        ULONG get_id() const { return id; }
        const string get_serialNumber() const { return serialNumber; }
        const string get_description() const { return description; }
        DEVICE_VERSION get_ftDeviceVersion() const {return ftDeviceVersion; };
        const string get_ftStringDeviceVersion() const { return GetStringDEVICE_VERSION(ftDeviceVersion); }
        WORD get_VendorId() const { return vendorId; }
        WORD get_ProductId() const { return productId; }
        const string get_manufacturer() const { return manufacturer; } 
        const string get_manufacturerId() const { return manufacturerId; }
        WORD get_maxPower() const { return maxPower; }
        bool get_isPnp() const { return isPnp; }
        bool get_isSelfPowered() const { return isSelfPowered; };
        bool get_isRemoteWakeUp() const { return isRemoteWakeUp; };
        bool get_isFifo245() const { return isFifo245; };
        bool get_isD2XX() const { return isD2XX; };

        void evaluateSpecification();
        void open(const openMode &mode);
        uint read(shared_ptr<unsigned char[]> &output);
        void close();
        void set_fifoBuffer(const ulong &bufferSize_) {
            bufferSize = bufferSize_;
        }
        void prepareToRead(const DWORD &capacity);
        void continousRead();
        uint readAsync(shared_ptr<unsigned char[]> &output);
    };
}
#endif // FTD_DEVICE_H
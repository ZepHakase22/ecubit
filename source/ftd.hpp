#if ( !defined(FTD_H))
#define FTD_H

#include <vector>
#include "ftd2xx.h"
#include "types.h"
#include "ftdDevice.hpp"

using namespace std;


namespace FTDI {
    class ftd {
        private:
        vector<ftdDevice> devices;
        shared_ptr<ftdDevice> selectedDevice;
        openMode mode;
        DWORD capacity;

        bool icompare(const string & str1,const string &str2);
        void open(const openMode &mode, const string &deviceIdentificator);

        protected:

        public:
        ftd();
        ~ftd() {}

        void openBySerialNumber(const string &serialNumber);
        void openByDescription(const string &description);

        vector<ftdDevice> get_devices() const  { return devices; }
        const shared_ptr<ftdDevice> get_selectedDevice() const { return selectedDevice; }

        void startRead(const DWORD &capacity_);
        void setFifoBuffer(const ulong &fifoBuffer);
        uint readAsync(shared_ptr<unsigned char[]> &output);
        uint read(shared_ptr<unsigned char[]> &output);
    };
}

#endif // FTD_H
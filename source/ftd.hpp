#if ( !defined(FTD_H))
#define FTD_H

#include <vector>
#include "types.h"
#include "ftdDevice.hpp"
using namespace std;

namespace FTDI {
    class ftd {
        private:
        vector<ftdDevice> devices;
        shared_ptr<ftdDevice> selectedDevice;
        openMode mode;

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
    };
}

#endif // FTD_H
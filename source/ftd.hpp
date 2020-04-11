#if ( !defined(FTD_H))
#define FTD_H

#include <vector>
#include "ftdDevice.hpp"
using namespace std;

namespace FTDI {
    class ftd {
        private:
        
        vector<ftdDevice> devices;

        protected:

        public:
        ftd();
        ~ftd() {}

        vector<ftdDevice> get_devices() const  { return devices; }
    };
}

#endif // FTD_H
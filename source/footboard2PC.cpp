#include <iostream>

#include "Log.hpp"
#include "ftd.hpp"
#include "ftdException.hpp"

using namespace std;
using namespace FTDI;
structlog LOGCFG = {};

int main() {
    LOGCFG.headers = false; 
    LOGCFG.level = DEBUG;
    int retCode = 0;

    LOG(INFO) << "START"; 
    
    ftd *footboard = NULL;

    try {
        footboard = new ftd;
    } catch(ftdException &ex) {
        printException(ex);
        retCode = -1;
        goto end;
    }
    // OpenDevice
    // Read 
    // Write to pc
end:
    delete footboard;
    return retCode;
}
#include <iostream>
#include <memory>
#include "ftd.hpp"
#include "ftdException.hpp"
#include "types.h"

using namespace std;
using namespace FTDI;

int main(int argc, char *argv[]) {
    int retCode = 0;
    parser params;

    params = parse(argc,argv);

    TRACE << "==================================== START ====================================="; 
   
    using _footboard = unique_ptr<ftd>;

    try {
        auto footboard = _footboard(new ftd);
        
        BEGIN_LOG(INFO)
            vector<ftdDevice> v = footboard->get_devices();
            for (vector<ftdDevice>::iterator it = v.begin(); it!=v.end(); ++it) {
            TRACE << "Is High Speed: " << it->get_isHighSpeed() 
                << " Device Type: " << it->get_ftDeviceType()
                << " ID: " <<  it->get_id()
                << " Serial Number: " << it->get_serialNumber()
                << " Description: " << it->get_description(); 
            }
        END_LOG

        if(params.isListing)
            goto end;
        // footboard->open()

    } catch(ftdException &ex) {
        EXCEPT(ex,ERROR);
        retCode = -1;
        goto end;
    }
    // Read 
    // Write to pc
end:
    TRACE << "==================================== END =====================================";
    return retCode;
}
#include <iostream>
#include <memory>
#include <iomanip>

#include "ftd.hpp"
#include "ftdException.hpp"
#include "types.h"
#include "udpClient.hpp"

using namespace std;
using namespace FTDI;
using namespace udp;

int main(int argc, char *argv[]) {
    int retCode = 0;
    parser params;

    params = parse(argc,argv);

    TRACE << "========================================================= START ==========================================================";
   
    using _footboard = unique_ptr<ftd>;

    try {
        auto footboard = _footboard(new ftd);
        
        BEGIN_LOG(INFO)
            vector<ftdDevice> v = footboard->get_devices();
            for (vector<ftdDevice>::iterator it = v.begin(); it!=v.end(); ++it) {
            TRACE << "Is High Speed: " << setiosflags(ios::boolalpha) << it->get_isHighSpeed() 
                    << resetiosflags(ios::boolalpha)
                << " Device Type: " << it->get_ftStringDeviceType() 
                << ":(" << it->get_ftDeviceType() << ")"
                << " ID: " <<  it->get_id()
                << " Serial Number: " << it->get_serialNumber()
                << " Description: " << it->get_description(); 
            }
        END_LOG

        if(params.isListing)
            goto end;
        if(params.isSerialNumber) {
            footboard->openBySerialNumber(params.value);
        } else {
            footboard->openByDescription(params.value);
        }
        shared_ptr<ftdDevice> selectedDevice = footboard->get_selectedDevice();

        TRACE   << "Device: " << selectedDevice->get_ftStringDeviceType() 
                << " opened, with:" << endl 
                << "Serial Number: " << selectedDevice->get_serialNumber()
                << ", Description: " << selectedDevice->get_description() 
                << ", Device version: " << selectedDevice->get_ftStringDeviceVersion() 
                << ", " << endl
                << "Vendor ID: " << hex << setiosflags (ios::showbase | ios::uppercase) 
                        << selectedDevice->get_VendorId() << resetiosflags(ios::uppercase)
                << ", Product ID: " << setiosflags(ios::uppercase) << selectedDevice->get_ProductId() 
                        << resetiosflags(ios::showbase | ios::uppercase) << dec
                << ", Manufacturer: " << selectedDevice->get_manufacturer()
                << ", Manufacturer ID: " << selectedDevice->get_manufacturerId()
                << ", Max power: " << selectedDevice->get_maxPower()
                << ", PnP: " << setiosflags(ios::boolalpha) << selectedDevice->get_isPnp()
                << ", " << endl
                << "Self powered: " << selectedDevice->get_isSelfPowered()
                << ", Remote wake up: " << selectedDevice->get_isRemoteWakeUp()
                << ", FIFO 245: " << selectedDevice->get_isFifo245()
                << ", D2XX: " << selectedDevice->get_isD2XX();
        
        string chunk;
        udp_client client(params.address,params.port);
        if(params.isMultiThread) {
            footboard->startRead(params.numBytes, params.capacity);
            while(true) {
                footboard->getData(chunk);
                client.send(chunk);
            }
        } else {
            while(true) {
                selectedDevice->read(params.numBytes,chunk);
                client.send(chunk);
            } 
        }
    } catch(ftdException &ex) {
        EXCEPT(ex,ERROR);
        retCode = -1;
        goto end;
    } 
end:
    TRACE << "========================================================== END ===========================================================" << endl;
    return retCode;
}
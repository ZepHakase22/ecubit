#include <iostream>
#include <memory>
#include <iomanip>
#include <cstring>

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

    TRACE << "========================================================= START ==========================================================" << endl;
   
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
                << " Description: " << it->get_description()
                << endl; 
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
                << ", D2XX: " << selectedDevice->get_isD2XX() << endl;
        
        footboard->setFifoBuffer(params.fifo_buffer);

        udp_client client(params.address,params.port);
        shared_ptr<unsigned char[]> buff;
        unsigned char *bufToSend = (unsigned char *)calloc(params.udp_buffer,1);
        uint size = 0;

        if(params.isMultiThread)
            footboard->startRead(params.queue_capacity);

        while(true) {
            uint tmpsize = 0;
            uint n0;
            if(params.isMultiThread) {
                n0 = footboard->readAsync(buff);
            } else {
                n0 = footboard->read(buff);
            }
            BEGIN_LOG(DEBUG)
                TRACE  << "RECEIVED BUFFER: " << endl;
                dumpBuffer(buff.get(),n0);
            END_LOG
            uint n = n0;
            while (n +size >= params.udp_buffer) {
                memcpy(bufToSend + size ,buff.get() + tmpsize, params.udp_buffer -size);
                BEGIN_LOG(DEBUG)
                    TRACE  << "BUFFER TO TRANSMIT: " << endl;
                    dumpBuffer(bufToSend,params.udp_buffer);
                END_LOG
                client.send(bufToSend,params.udp_buffer);
                memset(bufToSend,0,params.udp_buffer);
                tmpsize += params.udp_buffer - size;
                n -= params.udp_buffer -size;
                size = 0;
            }
            memcpy(bufToSend+size,buff.get() + tmpsize, n);
            size += n;
            BEGIN_LOG(DEBUG)
                TRACE  << "PREPAIRED BUFFER: " << endl;
                dumpBuffer(bufToSend,size);
            END_LOG
        } 
    } catch(ftdException &ex) {
        EXCEPT(ex,ERROR) << endl;
        retCode = -1;
        goto end;
    } catch(exception &e) {
        int a=0;
    }
end:
    TRACE << "========================================================== END ===========================================================" << endl;
    return retCode;
}
#include <iostream>


#include "types.h"
#include "Log.hpp"
#include "cppopt.hpp"

parser parse(int argc,char *argv[]) {

parser params;

try
{

    cxxopts::Options options(argv[0], "footboard2PC - Send data from footboard to PC via UDP");
    options
        .custom_help("OPTIONS: [GENERAL][DEVICE][WI-FI] ")
        .positional_help("ip-address [ DEBUG|INFO|WARN|ERROR ]")
        .allow_unrecognised_options()
        .show_positional_help();

    options.add_options("GENERAL")
        ("h,help", "This help print message")
        ("l,list", "List the exsisting devices")
        ("m,usethread", "If present, use threads (default false) ")
        ("c,capacity", "In multithread mode is the queue capacity", cxxopts::value<ulong>());

    options.add_options("DEVICE")
        ("s,serialnumber", "The device serial number", cxxopts::value<std::string>())
        ("d,description" , "The device description", cxxopts::value<std::string>())
        ("f,FIFO-buffer","Number of bytes read from device",cxxopts::value<ulong>());

    options.add_options("WI-FI")
        ("u,UDP-buffer","Set the transmission buffer size",cxxopts::value<ulong>())
        ("p,port", "The number of the socket port to communicate",cxxopts::value<uint>());

    options.add_options("POSITIONAL") 
        ("ip-address","The Server Ip Address",cxxopts::value<std::string>())
        ("level-log", "Required level log",cxxopts::value<std::string>());
 
    options.parse_positional({"ip-address","level-log","positional"});



    auto result = options.parse(argc, argv);

    if (result.count("h"))
    {
        std::cout << options.help({"GENERAL", "DEVICE", "WI-FI","POSITIONAL"}) << std::endl;
        exit(0);
    }

    if (result.count("l"))
    {
        params.isListing = true;
        LOG_LEVEL(INFO);
        return params;
    }

    if (result.count("m")) {
        params.isMultiThread = true;
        if(result.count("c")) {
            params.queue_capacity=result["capacity"].as<ulong>();
        }
    }
    if(result.count("f")) {
        params.fifo_buffer = result["FIFO-buffer"].as<ulong>();
         if(params.fifo_buffer >= 65537) {
            std::cout << "The requested buffer size exceeds the \
             maximum FIFO 245 buffer size of 65536" << endl;
            exit(1);
        }       
    }    
    if(result.count("u")) {
        params.udp_buffer = result["UDP-buffer"].as<ulong>();
        if(params.udp_buffer >= 65508) {
            std::cout << "The requested buffer size exceeds the \
             maximum UDP buffer size of 65507" << endl;
            exit(1);
        }
    }    

    if(result.count("ip-address")) {
        params.address = result["ip-address"].as<std::string>();
    }
    if(result.count("port")) {
        params.port = result["port"].as<uint>();
    }

    if(result.count("level-log")) {
        string debugLevel = result["level-log"].as<std::string>();
        if((debugLevel == "DEBUG" || debugLevel == "debug")) {
            LOG_LEVEL(DEBUG);
        } else if(debugLevel == "INFO" || debugLevel == "info") {
            LOG_LEVEL(INFO);
        } else if(debugLevel == "WARN" || debugLevel == "warn") {
            LOG_LEVEL(WARN);
        } else if(debugLevel == "ERROR" || debugLevel == "error") {
            LOG_LEVEL(FAILURE);
        }
    }
    if (result.count("serialnumber")) {
        params.value = result["serialnumber"].as<std::string>();
        if (result.count("description")) {
            std::cout << "Inconsistent parameters: you cannot pass serial number " 
                << params.value << " and description " 
                << result["description"].as<std::string>()
                << std::endl;
            exit(1);
        }
    }
    if (result.count("description")) {
        params.isSerialNumber = false;
        params.value = result["description"].as<std::string>();
    }
 
    if(params.value.empty()) {
        std::cout << "Missing device Serial Number or Description" << std::endl;
        exit(1);
    } else if(params.address.empty()) {
        std::cout << "Missing Server IP ADDRESS" << std::endl;
        exit(1);
    } 
  }
  catch (const cxxopts::OptionException& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
  return params;
}

#include <iostream>

#include "cppopt.hpp"
#include "types.h"
#include "Log.hpp"

parser parse(int argc,char *argv[]) {

parser params;

try
{

    cxxopts::Options options(argv[0], "footboard2PC - Send data from footboard to PC via UDP");
    options
        .custom_help("[-h | --help] [-l | --list] [-s | --serialnumber[=]<serial number> | -d | --description[=]<description>] [--log-level]")
        .positional_help("[DEBUG|INFO|WARN|ERROR]")
        .allow_unrecognised_options()
        .show_positional_help();

    options.add_options()
        ("h,help", "This help print message")
        ("l,list", "List the exsisting devices")
        ("log-level", "The log level", cxxopts::value<std::string>());

    options.add_options("Device")
        ("s,serialnumber", "The device serial number", cxxopts::value<std::string>())
        ("d,description" , "The device description", cxxopts::value<std::string>());

    options.parse_positional({"log-level"});

    auto result = options.parse(argc, argv);

    if (result.count("h"))
    {
        std::cout << options.help({"", "Device"}) << std::endl;
        exit(0);
    }

    if (result.count("l"))
    {
        params.isListing = true;
        LOG_LEVEL(INFO);
        return params;
    }

    if (result.count("log-level"))
    {
        string debugLevel = result["log-level"].as<std::string>();
        if((debugLevel == "DEBUG" || debugLevel == "debug")) {
            LOG_LEVEL(DEBUG);
        } else if(debugLevel == "INFO" || debugLevel == "info") {
            LOG_LEVEL(INFO);
        } else if(debugLevel == "WARN" || debugLevel == "warn") {
            LOG_LEVEL(WARN);
        } else if(debugLevel == "ERROR" || debugLevel == "error") {
            LOG_LEVEL(ERROR);
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
    }
  }
  catch (const cxxopts::OptionException& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
  return params;
}

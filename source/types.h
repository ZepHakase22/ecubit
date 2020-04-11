#if ( !defined(TYPES_H) )
#define TYPES_H
#include <string>

#define LOG_LEVEL(mode) LOGCFG.headers = false; \
                        LOGCFG.level = mode; 

typedef struct _parser {
    _parser() {
        isListing=false;
        isSerialNumber=true;
    }
    bool isListing;
    bool isSerialNumber;
    std::string value;
} parser;

parser parse(int argc,char *argv[]);

#endif
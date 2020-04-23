/* 
 * File:   Log.hpp
 * Author: ZepHakase <ZepHakase22@gmail.com>
 *
 * Created on April 9, 2020, 2:00 AM
 */

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

enum typelog {
    DEBUG,
    INFO,
    WARN,
    FAILURE
};

struct structlog {
    bool headers = false;
    typelog level = INFO;
};

extern structlog LOGCFG;
 
class LOG : public ostream{
    class LOGStreamBuf : public stringbuf {
        ostream &output;
        typelog msglevel = DEBUG;
        inline string getLabel(typelog type) {
            string label;
            switch(type) {
                case DEBUG: label = "DEBUG"; break;
                case INFO:  label = "INFO "; break;
                case WARN:  label = "WARN "; break;
                case FAILURE: label = "ERROR"; break;
            }
            return label;
        }


        public:
        LOGStreamBuf(typelog typel, ostream &str) 
            :output(str)
        {
            msglevel=typel;
        }

        ~LOGStreamBuf() {
            if(pbase()!=pptr()) {
                if(msglevel >= LOGCFG.level) {
                    putOutput(); 
                } else {
                    str().clear();
                }
            }
        }

        virtual int sync() {
            if(msglevel >= LOGCFG.level) {
                putOutput(); 
            } else {
                str().clear();
            }

            return 0;
        }

        void putOutput() {
            if(LOGCFG.headers) {
                output << setiosflags(std::ios::boolalpha) << "["+getLabel(msglevel)+"]" 
                        << resetiosflags(std::ios::boolalpha) << str();
            } else {
                output << str();
            }
            str("");
            output.flush();
        }
    };
    LOGStreamBuf buffer;
public:
    LOG(typelog type,ostream &str=cout) 
        :ostream(&buffer),
        buffer(type,str) {
    }
    ~LOG() override {
    }
private:
};

#endif  /* LOG_H */
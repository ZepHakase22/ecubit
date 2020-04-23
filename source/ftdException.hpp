#ifndef FTD_EXCEPTION_HPP
#define FTD_EXCEPTION_HPP

#include <exception>
#include "Log.hpp"

#include "enums.h"
#include "ftd2xx.h"


#define ftdThrow( status ) throw ftdException((ftdErrors)status,__FILE__,__LINE__,__func__)
#define socketThrow( status ) throw socketException((socketErrors)status,__FILE__,__LINE__,__func__)
#define socketThrowInfo( status, info ) throw socketException((socketErrors)status,__FILE__,__LINE__,__func__,info)
#define addrinfoThrow( status ) throw addrinfoException((addrinfoErrors)status,__FILE__,__LINE__,__func__)
#define ftdThrowInfo( status , info ) throw ftdException((ftdErrors)status,__FILE__,__LINE__,__func__,info)
#define ftdThrowMsg( message ) throw ftdException(message,__FILE__,__LINE__,__func__)
#define ftdThrowMsgInfo( message , info ) throw ftdException(message,__FILE__,__LINE__,__func__,info)
#define TRACE  LOG(INFO)


#define BEGIN_LOG(mode) if(LOGCFG.level <= mode) {
#define END_LOG }
namespace FTDI {
    class ftdException : public std::exception {
        private:
        ftdErrors status;
        const char *msg;
        const char *file;
        int line;
        const char *func;
        const char *info;

        public:
        
            ftdException(const char *msg_, const char* file_, int line_, const char* func_, const char* info_ = "No Info") : std::exception(    ),
                msg(msg_),
                file (file_),
                line (line_),
                func (func_),
                info (info_)
            {
            }
            ftdException(ftdErrors status_, const char* file_, int line_, const char* func_, const char* info_ = "No Info") : std::exception(    ),
                status(status_),
                file (file_),
                line (line_),
                func (func_),
                info (info_)
            {
                msg = GetStringftdErrors(status);
            }
            virtual UINT get_status() const { return status; }
            const char* get_file() const { return file; }
            int get_line() const { return line; }
            const char* get_func() const { return func; }
            const char* get_info() const { return info; }
        
            const char *what() const throw() override {
                return msg;
            }
    };
    class socketException : public ftdException {
        private:
         socketErrors status;

        public:
            socketException(const char *msg_, const char* file_, int line_, const char* func_, const char* info_ = "No Info") : 
                ftdException(msg_, file_,line_,func_,info_)
            {
            }
            socketException(socketErrors status_, const char* file_, int line_, const char* func_, const char* info_ = "No Info") : 
                ftdException(GetStringsocketErrors(status_), file_,line_,func_,info_),
                status(status_)
            {
            }
            UINT get_status() const { return status; }
     };
     class addrinfoException : public ftdException {
        private:
        addrinfoErrors status;

        public:
        addrinfoException(const char *msg_, const char* file_, int line_, const char* func_, const char* info_ = "No Info") : 
            ftdException(msg_, file_,line_,func_,info_)
        {
        }
        addrinfoException(addrinfoErrors status_, const char* file_, int line_, const char* func_, const char* info_ = "No Info") : 
            ftdException(GetStringaddrinfoErrors(status_), file_,line_,func_,info_),
            status(status_)
        {
        }
        UINT get_status() const { return status; }
     };
#if defined(_WIN32)
     inline void EXCEPT(FTDI::ftdException& ex, const typelog& mode) {
         LOG(mode, cout) << endl << mode << ": " << ex.get_status() \
             << " ( " << ex.what() << " FILE: " \
             << ex.get_file() << " FUNC: " << ex.get_file() \
             << " LINE: " << ex.get_line() << " INFO: " \
             << ex.get_info() <<endl;
     }
#else
#define EXCEPT(ex, mode) LOG(mode)  << endl << #mode            << ": "             << ex.get_status() \
                                    << " ( " << "\e[01m"      << ex.what()        << "\e[0m ) FILE: " \
                                    << ex.get_file()    << " FUNC: "        << ex.get_file() \
                                    << " LINE: "        << ex.get_line()    << " INFO: " \
                                    << ex.get_info() << endl
#endif


}
#endif 
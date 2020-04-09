#ifndef FTD_EXCEPTION_HPP
#define EXCEPTION
#include <exception>

#include "enums.h"
#include "ftd2xx.h"

#define ftdThrow( status ) throw new ftdException((ftdErrors)##status,__FILE__,__LINE__,__func__)
#define ftdThrowInfo( status , info ) throw new ftdException((ftdErrors)##status,__FILE__,__LINE__,__func__,##info)
#define ftdThrowMsg( message ) throw new ftdException(##message,__FILE__,__LINE__,__func__)
#define ftdThrowMsgInfo( message , info ) throw new ftdException(##message,__FILE__,__LINE__,__func__,##info)

namespace FTDI {
    class ftdException : public std::exception {
        private:
        const char *file;
        int line;
        const char *func;
        const char *info;
        const char *msg;

        public:
        
            ftdException(const char *msg_, const char* file_, int line_, const char* func_, const char* info_ = "") : std::exception(    ),
                msg(msg_),
                file (file_),
                line (line_),
                func (func_),
                info (info_)
            {
            }
            ftdException(ftdErrors status_, const char* file_, int line_, const char* func_, const char* info_ = "") : std::exception(    ),
                msg(GetStringftdErrors(status_)),
                file (file_),
                line (line_),
                func (func_),
                info (info_)
            {
            }
            const char* get_file() const { return file; }
            int get_line() const { return line; }
            const char* get_func() const { return func; }
            const char* get_info() const { return info; }
        
            const char *what() const throw() override {
                return msg;
            }
    };
}
#endif // FTD_EXCEPTION_HPP
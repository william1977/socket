#ifndef _ERROR_WRAPPER_H_
#define _ERROR_WRAPPER_H_

#include <string>

struct Error {
    int errnum;
    std::string strerror;
};

#endif //_ERROR_WRAPPER_H_
#include "EdgeDetectorException.h"


EdgeDetectorException::EdgeDetectorException(const char *msg) {

    message_ = msg;

}


const char* EdgeDetectorException::what() noexcept { 

    return message_.c_str();
    
}

#include "../server.h"

using namespace server;
using namespace std;

// Constructor

ServiceException::ServiceException (HttpStatus status, string msg) 
    : httpStatus(status), msg(msg) {    
}

// Functions

HttpStatus ServiceException::status () const {
    return httpStatus;
}

const char* ServiceException::what () const  {
    return msg.c_str();
}
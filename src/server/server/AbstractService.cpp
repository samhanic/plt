#include "../server.h"
#include <iostream>
using namespace server;
using namespace std;

// Constructor

AbstractService::AbstractService (const std::string& pattern) {
    setPattern(pattern);
}

// Functions

const string& AbstractService::getPattern () const {
    return pattern;
}

void AbstractService::setPattern (const std::string& pattern) {
    this->pattern = pattern;
}

HttpStatus AbstractService::get (Json::Value& out, int id) const {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not implemented");
}

HttpStatus AbstractService::post (const Json::Value& in, int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not implemented");
}

HttpStatus AbstractService::put (Json::Value& out, const Json::Value& in) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not implemented");
}

HttpStatus AbstractService::remove (int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
}

// Destructor

AbstractService::~AbstractService() {
    
}
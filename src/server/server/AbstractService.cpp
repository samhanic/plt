#include "AbstractService.h"

server::AbstractService::AbstractService(const std::string &pattern) :pattern(pattern) {

}

const std::string &server::AbstractService::getPattern() const {
    return this->pattern;
}

void server::AbstractService::setPattern(const std::string &pattern) {
    this->pattern = pattern;
}

server::AbstractService::~AbstractService() {

}

server::HttpStatus server::AbstractService::get(Json::Value &out, int id) const {
    return OUT_OF_RESOURCES;
}

server::HttpStatus server::AbstractService::post(const Json::Value &in, int id) {
    return OUT_OF_RESOURCES;
}

server::HttpStatus server::AbstractService::put(Json::Value &out, const Json::Value &in) {
    return OUT_OF_RESOURCES;
}

server::HttpStatus server::AbstractService::remove(int id) {
    return OUT_OF_RESOURCES;
}

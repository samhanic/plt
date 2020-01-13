#include "GameService.h"

server::GameService::GameService(Game &game) : AbstractService("game"), game(game){

}

server::HttpStatus server::GameService::get(Json::Value &out, int id) const {
    return AbstractService::get(out, id);
}

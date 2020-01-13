#include "PlayerService.h"

server::PlayerService::PlayerService(Game &game)
        : AbstractService("player"), game(game) {
}

server::HttpStatus server::PlayerService::get(Json::Value &out, uint id) const {
    if(game.getPlayers().size() != 0 && id < game.getPlayers().size()){
        out["name"] = game.player(id).name;
        return OK;
    }
    else{
        return NOT_FOUND;
    }
}

server::HttpStatus server::PlayerService::post(const Json::Value &in, uint id) {
    std::vector<Player> players = game.getPlayers();
    Player player;
    bool isset = false;
    if(id < players.size()){
        isset = true;
        players[id].name = in["name"].asString();
        game.setPlayers(players);
    }
    if(isset){
        return NO_CONTENT;
    }
    else{
        return NOT_FOUND;
    }
}

server::HttpStatus server::PlayerService::put(Json::Value &out, const Json::Value &in) {
    std::vector<Player> players = game.getPlayers();
    Player player;
    player.name = in["name"].asString();
    players.push_back(player);
    game.setPlayers(players);
    out["id"] = players.size()-1;
    return CREATED;
}

server::HttpStatus server::PlayerService::remove(uint id) {
    std::vector<Player> players = game.getPlayers();
    Player player;
    bool isset = false;
    if(id < players.size()){
        isset = true;
        players.erase(players.begin() + id);
        game.setPlayers(players);
    }
    if(isset){
        return NO_CONTENT;
    }
    else{
        return NOT_FOUND;
    }
}

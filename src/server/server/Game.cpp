#include "Game.h"

server::Game::Game() {

}

server::Player &server::Game::player(int i) {
    return players[i];
}

const std::vector<server::Player> &server::Game::getPlayers() const {
    return this->players;
}

void server::Game::setPlayers(const std::vector<Player> &players) {
    this->players = players;
}

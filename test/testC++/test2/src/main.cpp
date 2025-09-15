#include "header.h"
using namespace std;

struct Player{
    int id;
    char padding[0x300];
    int health;
};

struct PlayerManager{
    char padding[0x20];
    std::vector<std::unique_ptr<Player>> players;
};

int main() {
    auto player_manager=std::make_unique<PlayerManager>();
    for(size_t i=0;i<10;i++){
        auto player=std::make_unique<Player>();
        player->id=i;
        player->health=100;
        player_manager->players.emplace_back(std::move(player));
    }
    int id=-1;
    std::cin>>id;
    while(true){
        std::cin.get();
        player_manager->players[id]->health-=4;
        std::cout<<"Player "<<id<<" health: "<<player_manager->players[id]->health<<"\n";
    }
}
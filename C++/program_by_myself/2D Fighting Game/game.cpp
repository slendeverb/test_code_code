#include <iostream>
#include <functional>
#include <SDL2/SDL.h>
using namespace std;

class Character
{
private:
    int health;
    int attack;
    int defense;

public:
    Character()
    {
        health = 100;
        attack = 10;
        defense = 5;
    }

    void attackEnemy(function<void()> callback)
    {
        if (callback)
        {
            callback();
        }
    }
};

void playAttackAnimation()
{
}

int main(int args, char *argv[])
{
    
    return 0;
}
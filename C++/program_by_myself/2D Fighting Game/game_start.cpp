#include <iostream>
#include <functional>
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

int main()
{

    return 0;
}
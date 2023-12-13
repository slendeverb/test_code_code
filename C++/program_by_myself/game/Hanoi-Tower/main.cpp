#include "HanoiTower.h"

int main()
{
    HanoiTower hanoiTower;
    int userKey;
    do
    {
        system("cls");
        hanoiTower.showMenu();
        std::cout << "请选择: ";
        std::cin >> userKey;
        HanoiTower::Key key{static_cast<HanoiTower::Key>(userKey)};
        using enum HanoiTower::Key;
        switch (key)
        {
        case START:
            hanoiTower.startGame();
            break;
        case RECORD:
            hanoiTower.showRecord();
            break;
        case INSTRUCTION:
            hanoiTower.showInstruction();
            break;
        case EXIT:
            std::cout << "退出游戏!\n"
                      << std::endl;
            break;
        default:
            std::cout << "输入无效!\n"
                      << std::endl;
            system("pause");
            break;
        }
    } while (userKey != 0);

    system("pause");
    return 0;
}
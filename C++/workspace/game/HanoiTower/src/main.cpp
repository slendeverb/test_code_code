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
        using Key = HanoiTower::Key;
        switch (key)
        {
        case Key::START:
            hanoiTower.startGame();
            break;
        case Key::RECORD:
            hanoiTower.showRecord();
            break;
        case Key::INSTRUCTION:
            hanoiTower.showInstruction();
            break;
        case Key::EXIT:
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
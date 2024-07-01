#include "HanoiTower.h"

HanoiTower::HanoiTower()
{
    readRecord();
    showInstruction();
}

void HanoiTower::showMenu()
{
    std::cout << "汉诺塔游戏: \n";
    std::cout << "-------------------------------\n";
    std::cout << "-------> 1. 开始游戏 <---------\n";
    std::cout << "-------> 2. 游戏记录 <---------\n";
    std::cout << "-------> 3. 游戏介绍 <---------\n";
    std::cout << "-------> 0. 退出游戏 <---------\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

void HanoiTower::readRecord()
{
    std::ifstream in{"./record.txt"};
    if (!in.is_open())
    {
        return;
    }
    std::string s;
    Record record;
    while (std::getline(in, s))
    {
        std::istringstream inString{s};
        inString >> record;
        m_records.emplace_back(record);
    }
    std::sort(m_records.begin(), m_records.end());
    in.close();
}

void HanoiTower::showRecord()
{
    system("cls");
    std::cout << "游戏记录: \n";
    for (int i = 0; i < m_records.size(); i++)
    {
        std::cout << i + 1 << ". " << m_records[i] << "\n";
    }
    std::cout << std::endl;
    system("pause");
}

void HanoiTower::showInstruction()
{
    system("cls");
    std::cout << "欢迎游玩汉诺塔游戏!\n"
              << "游戏介绍:\n"
              << "    法国数学家爱德华·卢卡斯曾编写过一个印度的古老传说: "
              << "在世界中心贝拿勒斯（在印度北部）的圣庙里,一块黄铜板上插着三根宝石针。"
              << "印度教的主神梵天在创造世界的时候,在其中一根针上从下到上地穿好了由大到小的64片金片,这就是所谓的汉诺塔。"
              << "不论白天黑夜,总有一个僧侣在按照下面的法则移动这些金片: "
              << "一次只移动一片,不管在哪根针上,小片必须在大片上面。"
              << "僧侣们预言,当所有的金片都从梵天穿好的那根针上移到另外一根针上时,"
              << "世界就将在一声霹雳中消灭,而梵塔、庙宇和众生也都将同归于尽。\n\n";

    std::cout << "下面是汉诺塔游戏的教学: \n"
              << "    简单的游戏规则: 有三根杆子A,B,C。A杆上有 N 个 (N>1) 穿孔圆盘，盘的尺寸由下到上依次变小。"
              << "要求按下列规则将所有圆盘移至 C 杆：\n"
              << "        1.每次只能移动一个圆盘；\n"
              << "        2.大盘不能叠在小盘上面。\n"
              << "    提示：可将圆盘临时置于 B 杆，也可将从 A 杆移出的圆盘重新移回 A 杆，但都必须遵循上述两条规则。\n"
              << std::endl;
    system("pause");
}

void HanoiTower::showBreakRecord(const Record &record)
{
    std::cout << "恭喜玩家打破纪录!\n";
    std::cout << record << "\n"
              << std::endl;
}

void HanoiTower::showGameOver()
{
    std::cout << "游戏结束!\n\n";
    system("pause");
}

void HanoiTower::setRecord(const Record &record)
{
    int index{-1};
    bool findRecord{false};
    for (int i = 0; i < m_records.size(); i++)
    {
        if (m_records[i].plateNumber == record.plateNumber)
        {
            index = i;
            findRecord = true;
            break;
        }
    }
    if (findRecord)
    {
        if ((m_records[index].turnNumber > record.turnNumber) || (m_records[index].turnNumber == record.turnNumber && m_records[index].calSecond() > record.calSecond()))
        {
            showBreakRecord(record);
            m_records[index] = record;
        }
    }
    else
    {
        showBreakRecord(record);
        m_records.emplace_back(record);
        std::sort(m_records.begin(), m_records.end());
    }

    std::ofstream out{"./record.txt"};
    if (!out.is_open())
    {
        return;
    }
    for (int i = 0; i < m_records.size(); i++)
    {
        out << i + 1 << ". " << m_records[i] << "\n";
    }
    out.close();
}

void HanoiTower::startGame()
{
    system("cls");
    std::cout << "请问是否需要观看示例? (Y or n): ";
    std::cin.ignore();
    char yesOrNot = std::cin.get();
    if (yesOrNot == 'n' || yesOrNot == 'N')
    {
        play();
    }
    else
    {
        showExample();
        play();
    }
}

void HanoiTower::init()
{
    m_towers.clear();
    m_towers.resize(3);
    for (int i = m_plateNumber; i >= 1; --i)
    {
        m_towers[0].push_back(i);
    }
    m_turnNumber = 0;
    MinTurnNumber = (1ULL << m_plateNumber) - 1;
}

void HanoiTower::hanoi(int n, char a, char b, char c)
{
    if (n == 1)
    {
        moveExample(1, a, c);
    }
    else
    {
        hanoi(n - 1, a, c, b);
        moveExample(n, a, c);
        hanoi(n - 1, b, a, c);
    }
}

void HanoiTower::moveExample(int disks, char from, char to)
{
    int plate{m_towers[from - 'A'].back()};
    m_towers[from - 'A'].pop_back();
    m_towers[to - 'A'].push_back(plate);
    print();
    std::cout << "将圆盘 " << disks << " 从 " << from << " 移动到 " << to << "\n";
    system("pause");
}

void HanoiTower::showExample()
{
    system("cls");
    std::cout << "请输入想要观看的圆盘片数: ";
    std::cin >> m_plateNumber;
    init();
    print();
    system("pause");
    hanoi(m_plateNumber, 'A', 'B', 'C');
}

bool HanoiTower::movePlayer(char from, char to)
{
    int fromIndex{from - 'A'};
    int toIndex{to - 'A'};
    if (m_towers[fromIndex].empty())
    {
        std::cout << from << " 为空!\n";
        return false;
    }
    int plate{m_towers[fromIndex].back()};
    m_towers[fromIndex].pop_back();
    if (!m_towers[toIndex].empty() && plate > m_towers[toIndex].back())
    {
        std::cout << "不允许将大圆盘放在小圆盘上面!\n"
                  << std::endl;
        return false;
    }
    m_towers[toIndex].push_back(plate);
    print();
    std::cout << "将圆盘 " << plate << " 从 " << from << " 移动到 " << to << "\n";
    std::cout << "总步数: " << (++m_turnNumber) << "\n";
    return true;
}

void HanoiTower::play()
{
    system("cls");
    std::cout << "请输入想要游玩的圆盘片数: ";
    std::cin >> m_plateNumber;
    system("cls");
    init();
    print();
    int moveMethodFrom, moveMethodTo;
    bool success{true};
    clock_t timeStart{clock()};
    do
    {
        success = true;
        std::cout << "请输入指令移动圆盘(如:1 3,代表把圆盘从A的顶部移动到C的顶部): ";
        std::cin >> moveMethodFrom;
        if (moveMethodFrom == 0)
        {
            showGameOver();
            return;
        }
        std::cin >> moveMethodTo;
        if (moveMethodTo == 0)
        {
            showGameOver();
            return;
        }
        system("cls");
        bool moveTry{movePlayer(moveMethodFrom + 'A' - 1, moveMethodTo + 'A' - 1)};
        if (!moveTry)
        {
            showGameOver();
            return;
        }
        for (long long i = m_towers['C' - 'A'].size() - 1; i >= 0; i--)
        {
            if (m_towers['C' - 'A'][i] != m_plateNumber - i)
            {
                success = false;
                break;
            }
        }
    } while (m_towers['C' - 'A'].size() != m_plateNumber || !success);
    clock_t timeEnd{clock()};
    std::cout << "恭喜玩家成功通关!\n"
              << std::endl;
    setRecord(Record(m_plateNumber, m_turnNumber, (timeEnd - timeStart) / 1000));
    system("pause");
}

void HanoiTower::print()
{
    for (int i = m_plateNumber; i > 0; i--)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (i > m_towers[j].size())
            {
                for (int k = 0; k < m_plateNumber; k++)
                {
                    std::cout << " ";
                }
                std::cout << "||";
                for (int k = 0; k < m_plateNumber; k++)
                {
                    std::cout << " ";
                }
                std::cout << " ";
                if (j == 2)
                {
                    std::cout << std::endl;
                }
            }
            else
            {
                for (int k = 0; k < m_plateNumber - m_towers[j][i - 1]; k++)
                {
                    std::cout << " ";
                }
                for (int k = 0; k < m_towers[j][i - 1]; k++)
                {
                    std::cout << "=";
                }
                std::cout << "||";
                for (int k = 0; k < m_towers[j][i - 1]; k++)
                {
                    std::cout << "=";
                }
                for (int k = 0; k < m_plateNumber - m_towers[j][i - 1]; k++)
                {
                    std::cout << " ";
                }
                std::cout << " ";
                if (j == 2)
                {
                    std::cout << std::endl;
                }
            }
        }
    }
}
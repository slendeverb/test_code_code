#pragma once
#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

class HanoiTower
{
public:
    HanoiTower();
    ~HanoiTower() = default;
    void showMenu();
    void startGame();
    void showRecord();
    void showInstruction();

    enum class Key
    {
        START = 1,
        RECORD = 2,
        INSTRUCTION = 3,
        EXIT = 0
    };

private:
    int m_plateNumber{0};
    std::vector<std::vector<int>> m_towers;
    size_t m_turnNumber{0};
    size_t MinTurnNumber;

    struct Record
    {
        size_t hour;
        size_t minute;
        size_t second;
        size_t turnNumber;
        size_t plateNumber;

        Record() = default;

        Record(size_t plateNumber, size_t turnNumber, size_t second)
            : plateNumber{plateNumber}, turnNumber{turnNumber}, hour{second / 3600}, minute{(second % 3600) / 60}, second{(second % 3600) % 60} {}

        Record(size_t plateNumber, size_t turnNumber, size_t hour, size_t minute, size_t second)
            : plateNumber{plateNumber}, turnNumber{turnNumber}, hour{hour}, minute{minute}, second{second} {}

        size_t calSecond() const
        {
            return hour * 60 * 60 + minute * 60 + second;
        }

        friend std::istream &operator>>(std::istream &in, Record &record)
        {
            std::string s;
            in >> s >> s >> record.plateNumber >> s >> record.turnNumber >> s >> record.hour >> s >> record.minute >> s >> record.second;
            return in;
        }

        friend std::ostream &operator<<(std::ostream &out, const Record &record)
        {
            out << "难度: " << record.plateNumber << " 回合数: " << record.turnNumber
                << " 用时: " << record.hour << " h " << record.minute << " m " << record.second << " s";
            return out;
        }

        bool operator<(const Record &b) const
        {
            if (plateNumber == b.plateNumber)
            {
                if (turnNumber == b.turnNumber)
                {
                    return this->calSecond() < b.calSecond();
                }
                return turnNumber < b.turnNumber;
            }
            return plateNumber > b.plateNumber;
        }
    };

    void init();
    void hanoi(int n, char a, char b, char c);
    void moveExample(int disks, char from, char to);
    void showExample();
    bool movePlayer(char from, char to);
    void play();
    void print();
    void readRecord();
    void setRecord(const Record &record);
    void showBreakRecord(const Record &record);
    void showGameOver();

    std::vector<Record> m_records;
};
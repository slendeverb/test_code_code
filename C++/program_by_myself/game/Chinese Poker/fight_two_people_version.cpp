#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

enum identity
{
    landlord,
    farmer
};

enum GameResult
{
    NotFinished = -2,
    Initial = -1,
    LandlordWon,
    FarmerWon
};

enum Suit
{
    SUIT_SPADE,  // 黑桃
    SUIT_HEART,  // 红桃
    SUIT_CLUB,   // 梅花
    SUIT_DIAMOND // 方块
};

enum Rank
{
    RANK_3 = 3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10 = 'A' - '0',
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    RANK_2,
    RANK_SMALL_JOKER,
    RANK_BIG_JOKER
};

enum CardType
{
    Invalid = -1,
    SINGLE = 1,           // 单张
    PAIR,                 // 对子
    TRIPLE,               // 三张
    TRIPLE_WITH_ONE,      // 三带一
    TRIPLE_WITH_TWO,      // 三带二
    QUADRUPLE_WITH_TWO,   // 四带二
    QUADRUPLE_WITH_FOUR,  // 四带四
    STRAIGHT,             // 顺子
    STRAIGHT_PAIR,        // 连对
    PLANE,                // 飞机（三顺）
    PLANE_WITH_WINGS_ONE, // 飞机带单牌
    PLANE_WITH_WINGS_TWO, // 飞机带对子
    BOMB,                 // 炸弹
    KING_BOMB             // 王炸（大小王）
};

// 比较两张牌的大小
// 返回值大于0表示card1大于card2，小于0表示card1小于card2，等于0表示相等
bool compareCards(const char &card1, const char &card2)
{
    return card1 < card2;
}

// 判断牌是否为炸弹
bool isBomb(const std::vector<int> &cards)
{
    if (cards.size() != 4)
    {
        return false;
    }
    return cards[0] == cards[1] &&
           cards[1] == cards[2] &&
           cards[2] == cards[3];
}

// 判断牌是否为王炸
bool isKingBomb(const std::vector<int> &cards)
{
    if (cards.size() != 2)
    {
        return false;
    }
    return cards[0] == RANK_SMALL_JOKER && cards[1] == RANK_BIG_JOKER;
}

CardType calCardType(std::vector<int> &card)
{
    sort(card.begin(), card.end());
    if (card.size() == 1)
    {
        return CardType::SINGLE;
    }
    if (card.size() == 2)
    {
        if (isKingBomb(card))
        {
            return CardType::KING_BOMB;
        }
        if (card[0] == card[1])
        {
            return CardType::PAIR;
        }
    }
    if (card.size() == 3)
    {
        if (card[0] == card[1] && card[1] == card[2])
        {
            return CardType::TRIPLE;
        }
    }
    if (card.size() == 4)
    {
        if (isBomb(card))
        {
            return CardType::BOMB;
        }
        if (card[0] == card[1] && card[1] == card[2] || card[1] == card[2] && card[2] == card[3])
        {
            return CardType::TRIPLE_WITH_ONE;
        }
    }
    bool have = false;
    if (card.size() >= 5)
    {
        std::map<int, int> m;
        int cnt = 1;
        int maxx3 = -1, minn3 = 100;
        for (int i = 1; i < card.size(); i++)
        {
            if (card[i] == RANK_2 || card[i] == RANK_SMALL_JOKER && card[i] == RANK_BIG_JOKER)
            {
                have = true;
            }
            if (card[i] == card[i - 1])
            {
                cnt++;
            }
            else
            {
                if (cnt == 3)
                {
                    maxx3 = std::max(maxx3, card[i]);
                    minn3 = std::min(minn3, card[i]);
                }
                m[cnt]++;
                cnt = 1;
            }
        }
        if (card[0] != card[1])
        {
            m[1]++;
        }
        m[cnt]++;
        cnt = 1;
        if (card.size() == 5)
        {
            if (m[3] == 1 && m[2] == 1)
            {
                return CardType::TRIPLE_WITH_TWO;
            }
        }
        if (card.size() == 6)
        {
            if (m[4] == 1)
            {
                return CardType::QUADRUPLE_WITH_TWO;
            }
        }
        if (card.size() == 8)
        {
            if (m[4] == 1 && m[2] == 2)
            {
                return CardType::QUADRUPLE_WITH_FOUR;
            }
        }
        if (m[1] == card.size() && card[card.size() - 1] >= RANK_10 && card[0] <= RANK_9 ? card[card.size() - 1] - RANK_10 + RANK_9 - card[0] == card.size() - 2 : card[card.size() - 1] - card[0] == card.size() - 1)
        {
            return CardType::STRAIGHT;
        }
        if (card.size() / 2 >= 3 && card.size() % 2 == 0 && m[2] == card.size() / 2 && card[card.size() - 1] >= RANK_10 && card[0] <= RANK_9 ? card[card.size() - 1] - RANK_10 + RANK_9 - card[0] == card.size() / 2 - 2 : card[card.size() - 1] - card[0] == (card.size() / 2 - 1))
        {
            return CardType::STRAIGHT_PAIR;
        }
        if (m[3] == card.size() / 3 && card.size() % 3 == 0 && card[card.size() - 1] >= RANK_10 && card[0] <= RANK_9 ? card[card.size() - 1] - RANK_10 + RANK_9 - card[0] == card.size() / 3 - 2 : card[card.size() - 1] - card[0] == (card.size() / 3 - 1))
        {
            return CardType::PLANE;
        }
        if (m[3] >= 2 && m[3] == card.size() / 4 && maxx3 >= RANK_10 && minn3 <= RANK_9 ? maxx3 - RANK_10 + RANK_9 - minn3 == card.size() / 4 - 2 : maxx3 - minn3 == card.size() / 4 - 1)
        {
            return CardType::PLANE_WITH_WINGS_ONE;
        }
        if (m[3] >= 2 && m[3] == card.size() / 5 && maxx3 >= RANK_10 && minn3 <= RANK_9 ? maxx3 - RANK_10 + RANK_9 - minn3 == card.size() / 5 - 2 : maxx3 - minn3 == card.size() / 5 - 1)
        {
            return CardType::PLANE_WITH_WINGS_TWO;
        }
    }
    return CardType::Invalid;
}

bool calCardValue(std::vector<int> &previous, std::vector<int> &current)
{
    CardType type = calCardType(current);
    if (type == CardType::SINGLE || type == CardType::PAIR || type == CardType::TRIPLE)
    {
        if (current[0] > previous[0])
        {
            return true;
        }
    }
    if (type == CardType::STRAIGHT || type == CardType::STRAIGHT_PAIR || type == CardType::PLANE)
    {
        if (current[current.size() - 1] > previous[previous.size() - 1])
        {
            return true;
        }
    }

    std::map<int, int> mCurrent, mPrevious;
    int cntCurrent = 1, cntPrevious = 1;
    int maxxPrev = -1, maxxCurrent = -1;
    int maxxPrevCnt = -1, maxxCurrentCnt = -1;
    for (int i = 1; i < current.size(); i++)
    {
        if (current[i] == current[i - 1])
        {
            cntCurrent++;
        }
        else
        {
            mCurrent[cntCurrent]++;
            maxxCurrentCnt = std::max(maxxCurrentCnt, cntCurrent);
            cntCurrent = 1;
        }

        if (previous[i] == previous[i - 1])
        {
            cntPrevious++;
        }
        else
        {
            mPrevious[cntPrevious]++;
            maxxPrevCnt = std::max(maxxPrevCnt, cntPrevious);
            cntPrevious = 1;
        }
    }

    if (current[0] != current[1])
    {
        mCurrent[1]++;
    }
    mCurrent[cntCurrent]++;
    maxxCurrentCnt = std::max(maxxCurrentCnt, cntCurrent);
    cntCurrent = 1;

    if (previous[0] != previous[1])
    {
        mPrevious[1]++;
    }
    mPrevious[cntPrevious]++;
    maxxPrevCnt = std::max(maxxPrevCnt, cntPrevious);
    cntPrevious = 1;

    for (auto ele : mCurrent)
    {
        if (ele.second == maxxCurrentCnt)
        {
            maxxCurrent = std::max(maxxCurrent, ele.first);
        }
    }
    for (auto ele : mPrevious)
    {
        if (ele.second == maxxPrevCnt)
        {
            maxxPrev = std::max(maxxPrev, ele.first);
        }
    }
    if (type == CardType::TRIPLE_WITH_ONE || type == CardType::TRIPLE_WITH_TWO || type == CardType::QUADRUPLE_WITH_TWO || type == CardType::QUADRUPLE_WITH_FOUR || type == CardType::PLANE_WITH_WINGS_ONE || type == CardType::PLANE_WITH_WINGS_TWO)
    {
        if (maxxCurrent > maxxPrev)
        {
            return true;
        }
    }

    return false;
}

string toString(const char &ch)
{
    string res;
    res.push_back(ch);
    return res;
}

string handcard;
map<string, int> m[15];

void removeCardFromHand(const char &card)
{
    auto it = std::find(handcard.begin(), handcard.end(), card);
    if (it != handcard.end())
    {
        handcard.erase(it);
    }
}
void sortHand()
{
    std::stable_sort(handcard.begin(), handcard.end(), compareCards);
}

void separateCard()
{
    for (int i = SINGLE; i <= KING_BOMB; i++)
    {
        m[i].clear();
    }

    for (int i = 0; i < handcard.size(); i++)
    {
        m[SINGLE][toString(handcard[i])]++;
    }

    if (m[SINGLE].count(toString(RANK_SMALL_JOKER + '0')) && m[SINGLE].count(toString(RANK_BIG_JOKER + '0')))
    {
        m[KING_BOMB][toString(RANK_SMALL_JOKER + '0') + toString(RANK_BIG_JOKER + '0')]++;
    }

    int cnt = 1;
    for (int i = 1; i < handcard.size(); i++)
    {
        if (handcard[i] == handcard[i - 1])
        {
            cnt++;
        }
        else
        {
            cnt = 1;
        }
        if (cnt == 2)
        {
            m[PAIR][toString(handcard[i - 1]) + toString(handcard[i])]++;
            cnt = 1;
        }
    }

    cnt = 1;
    for (int i = 1; i < handcard.size(); i++)
    {
        if (handcard[i] == handcard[i - 1])
        {
            cnt++;
        }
        else
        {
            cnt = 1;
        }
        if (cnt == 3)
        {
            m[TRIPLE][toString(handcard[i - 2]) + toString(handcard[i - 1]) + toString(handcard[i])]++;
            cnt = 1;
        }
    }

    for (auto i = m[TRIPLE].begin(); i != m[TRIPLE].end(); i++)
    {
        for (auto j = m[SINGLE].begin(); j != m[SINGLE].end(); j++)
        {
            if (j->first[0] == i->first[0])
            {
                continue;
            }
            m[TRIPLE_WITH_ONE][i->first + j->first]++;
        }
    }

    for (auto i = m[TRIPLE].begin(); i != m[TRIPLE].end(); i++)
    {
        for (auto j = m[PAIR].begin(); j != m[PAIR].end(); j++)
        {
            if (j->first[0] == i->first[0])
            {
                continue;
            }
            m[TRIPLE_WITH_TWO][i->first + j->first]++;
        }
    }

    cnt = 1;
    for (int i = 1; i < handcard.size(); i++)
    {
        if (handcard[i] == handcard[i - 1])
        {
            cnt++;
        }
        else
        {
            cnt = 1;
        }
        if (cnt == 4)
        {
            m[BOMB][toString(handcard[i - 3]) + toString(handcard[i - 2]) + toString(handcard[i - 1]) + toString(handcard[i])]++;
            cnt = 1;
        }
    }

    for (auto i = m[BOMB].begin(); i != m[BOMB].end(); i++)
    {
        for (auto j = m[SINGLE].begin(); j != m[SINGLE].end();)
        {
            auto tj1 = j++;
            auto tj2 = j++;
            if (tj1 == m[SINGLE].end() || tj2 == m[SINGLE].end())
            {
                break;
            }
            if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0])
            {
                continue;
            }
            m[QUADRUPLE_WITH_TWO][i->first + tj1->first + tj2->first]++;
        }
    }

    for (auto i = m[BOMB].begin(); i != m[BOMB].end(); i++)
    {
        for (auto j = m[PAIR].begin(); j != m[PAIR].end();)
        {
            auto tj1 = j++;
            auto tj2 = j++;
            if (tj1 == m[PAIR].end() || tj2 == m[PAIR].end())
            {
                break;
            }
            if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0])
            {
                continue;
            }
            m[QUADRUPLE_WITH_FOUR][i->first + tj1->first + tj2->first]++;
        }
    }

    string s = "";
    for (auto i = m[SINGLE].begin(); i != m[SINGLE].end(); i++)
    {
        if (i->first[0] <= RANK_ACE + '0' && i->first[0] == RANK_10 + '0' ? i->first[0] == s[s.size() - 1] + RANK_10 - RANK_9 : i->first[0] == s[s.size() - 1] + 1)
        {
            s += i->first;
        }
        else
        {
            if (s.size() >= 5)
            {
                m[STRAIGHT][s]++;
            }
        }
    }

    s.clear();
    for (auto i = m[PAIR].begin(); i != m[PAIR].end(); i++)
    {
        if (i->first[0] <= RANK_ACE + '0' && i->first[0] == RANK_10 + '0' ? i->first[0] == s[s.size() - 1] + RANK_10 - RANK_9 : i->first[0] == s[s.size() - 1] + 1)
        {
            s += i->first;
        }
        else
        {
            if (s.size() / 2 >= 3)
            {
                m[STRAIGHT_PAIR][s]++;
            }
        }
    }

    s.clear();
    for (auto i = m[TRIPLE].begin(); i != m[TRIPLE].end(); i++)
    {
        if (i->first[0] <= RANK_ACE + '0' && i->first[0] == RANK_10 + '0' ? i->first[0] == s[s.size() - 1] + RANK_10 - RANK_9 : i->first[0] == s[s.size() - 1] + 1)
        {
            s += i->first;
        }
        else
        {
            if (s.size() / 3 >= 2)
            {
                m[PLANE][s]++;
            }
        }
    }

    for (auto i = m[PLANE].begin(); i != m[PLANE].end(); i++)
    {
        int sz = i->first.size() / 3;
        if (sz == 2 && m[SINGLE].size() >= 2)
        {
            for (auto j = m[SINGLE].begin(); j != m[SINGLE].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                if (tj1 == m[SINGLE].end() || tj2 == m[SINGLE].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_ONE][i->first + tj1->first + tj2->first]++;
            }
        }
        else if (sz == 3 && m[SINGLE].size() >= 3)
        {
            for (auto j = m[SINGLE].begin(); j != m[SINGLE].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                auto tj3 = j++;
                if (tj1 == m[SINGLE].end() || tj2 == m[SINGLE].end() || tj3 == m[SINGLE].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0] || tj3->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_ONE][i->first + tj1->first + tj2->first + tj3->first]++;
            }
        }
        else if (sz == 4 && m[SINGLE].size() >= 4)
        {
            for (auto j = m[SINGLE].begin(); j != m[SINGLE].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                auto tj3 = j++;
                auto tj4 = j++;
                if (tj1 == m[SINGLE].end() || tj2 == m[SINGLE].end() || tj3 == m[SINGLE].end() || tj4 == m[SINGLE].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0] || tj3->first[0] == i->first[0] || tj4->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_ONE][i->first + tj1->first + tj2->first + tj3->first + tj4->first]++;
            }
        }
        else if (sz == 5 && m[SINGLE].size() >= 5)
        {
            for (auto j = m[SINGLE].begin(); j != m[SINGLE].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                auto tj3 = j++;
                auto tj4 = j++;
                auto tj5 = j++;
                if (tj1 == m[SINGLE].end() || tj2 == m[SINGLE].end() || tj3 == m[SINGLE].end() || tj4 == m[SINGLE].end() || tj5 == m[SINGLE].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0] || tj3->first[0] == i->first[0] || tj4->first[0] == i->first[0] || tj5->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_ONE][i->first + tj1->first + tj2->first + tj3->first + tj4->first + tj5->first]++;
            }
        }
        else if (sz == 6 && m[SINGLE].size() >= 6)
        {
            for (auto j = m[SINGLE].begin(); j != m[SINGLE].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                auto tj3 = j++;
                auto tj4 = j++;
                auto tj5 = j++;
                auto tj6 = j++;
                if (tj1 == m[SINGLE].end() || tj2 == m[SINGLE].end() || tj3 == m[SINGLE].end() || tj4 == m[SINGLE].end() || tj5 == m[SINGLE].end() || tj6 == m[SINGLE].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0] || tj3->first[0] == i->first[0] || tj4->first[0] == i->first[0] || tj5->first[0] == i->first[0] || tj6->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_ONE][i->first + tj1->first + tj2->first + tj3->first + tj4->first + tj5->first + tj6->first]++;
            }
        }
        else if (sz == 7 && m[SINGLE].size() >= 7)
        {
            for (auto j = m[SINGLE].begin(); j != m[SINGLE].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                auto tj3 = j++;
                auto tj4 = j++;
                auto tj5 = j++;
                auto tj6 = j++;
                auto tj7 = j++;
                if (tj1 == m[SINGLE].end() || tj2 == m[SINGLE].end() || tj3 == m[SINGLE].end() || tj4 == m[SINGLE].end() || tj5 == m[SINGLE].end() || tj6 == m[SINGLE].end() || tj7 == m[SINGLE].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0] || tj3->first[0] == i->first[0] || tj4->first[0] == i->first[0] || tj5->first[0] == i->first[0] || tj6->first[0] == i->first[0] || tj7->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_ONE][i->first + tj1->first + tj2->first + tj3->first + tj4->first + tj5->first + tj6->first + tj7->first]++;
            }
        }
    }

    for (auto i = m[PLANE].begin(); i != m[PLANE].end(); i++)
    {
        int sz = i->first.size() / 3;
        if (sz == 2 && m[PAIR].size() >= 2)
        {
            for (auto j = m[PAIR].begin(); j != m[PAIR].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                if (tj1 == m[PAIR].end() || tj2 == m[PAIR].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_TWO][i->first + tj1->first + tj2->first]++;
            }
        }
        else if (sz == 3 && m[PAIR].size() >= 3)
        {
            for (auto j = m[PAIR].begin(); j != m[PAIR].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                auto tj3 = j++;
                if (tj1 == m[PAIR].end() || tj2 == m[PAIR].end() || tj3 == m[PAIR].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0] || tj3->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_TWO][i->first + tj1->first + tj2->first + tj3->first]++;
            }
        }
        else if (sz == 4 && m[PAIR].size() >= 4)
        {
            for (auto j = m[PAIR].begin(); j != m[PAIR].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                auto tj3 = j++;
                auto tj4 = j++;
                if (tj1 == m[PAIR].end() || tj2 == m[PAIR].end() || tj3 == m[PAIR].end() || tj4 == m[PAIR].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0] || tj3->first[0] == i->first[0] || tj4->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_TWO][i->first + tj1->first + tj2->first + tj3->first + tj4->first]++;
            }
        }
        else if (sz == 5 && m[PAIR].size() >= 5)
        {
            for (auto j = m[PAIR].begin(); j != m[PAIR].end();)
            {
                auto tj1 = j++;
                auto tj2 = j++;
                auto tj3 = j++;
                auto tj4 = j++;
                auto tj5 = j++;
                if (tj1 == m[PAIR].end() || tj2 == m[PAIR].end() || tj3 == m[PAIR].end() || tj4 == m[PAIR].end() || tj5 == m[PAIR].end())
                {
                    break;
                }
                if (tj1->first[0] == i->first[0] || tj2->first[0] == i->first[0] || tj3->first[0] == i->first[0] || tj4->first[0] == i->first[0] || tj5->first[0] == i->first[0])
                {
                    continue;
                }
                m[PLANE_WITH_WINGS_TWO][i->first + tj1->first + tj2->first + tj3->first + tj4->first + tj5->first]++;
            }
        }
    }
}

string attack()
{
    string ret = "none";

    if (handcard.size() == 8 && !m[QUADRUPLE_WITH_FOUR].empty())
    {
        return m[QUADRUPLE_WITH_FOUR].begin()->first;
    }
    if (handcard.size() == 6 && !m[QUADRUPLE_WITH_TWO].empty())
    {
        return m[QUADRUPLE_WITH_TWO].begin()->first;
    }
    if (!m[PLANE_WITH_WINGS_TWO].empty())
    {
        for (auto ele : m[PLANE_WITH_WINGS_TWO])
        {
            if (ele.first.size() > ret.size())
            {
                ret = ele.first;
            }
        }
        return ret;
    }
    else if (!m[PLANE_WITH_WINGS_ONE].empty())
    {
        for (auto ele : m[PLANE_WITH_WINGS_ONE])
        {
            if (ele.first.size() > ret.size())
            {
                ret = ele.first;
            }
        }
        return ret;
    }
    else if (!m[PLANE].empty())
    {
        for (auto ele : m[PLANE])
        {
            if (ele.first.size() > ret.size())
            {
                ret = ele.first;
            }
        }
        return ret;
    }
    else if (!m[STRAIGHT_PAIR].empty())
    {
        for (auto ele : m[STRAIGHT_PAIR])
        {
            if (ele.first.size() > ret.size())
            {
                ret = ele.first;
            }
        }
        return ret;
    }
    else if (!m[STRAIGHT].empty())
    {
        for (auto ele : m[STRAIGHT])
        {
            if (ele.first.size() > ret.size())
            {
                ret = ele.first;
            }
        }
        return ret;
    }
    else if (!m[TRIPLE_WITH_TWO].empty())
    {
        return m[TRIPLE_WITH_TWO].begin()->first;
    }
    else if (!m[TRIPLE_WITH_ONE].empty())
    {
        return m[TRIPLE_WITH_ONE].begin()->first;
    }
    else if (!m[TRIPLE].empty())
    {
        return m[TRIPLE].begin()->first;
    }
    else if (!m[PAIR].empty())
    {
        return m[PAIR].begin()->first;
    }
    else if (!m[SINGLE].empty())
    {
        return m[SINGLE].begin()->first;
    }
    else if (!m[BOMB].empty())
    {
        return m[BOMB].begin()->first;
    }
    else if (!m[KING_BOMB].empty())
    {
        return m[KING_BOMB].begin()->first;
    }
    return ret;
}
string defend(const string &s)
{
    vector<int> prev;
    bool ok = false;
    for (int i = 0; i < s.size(); i++)
    {
        prev.push_back(s[i] - '0');
    }
    CardType type = calCardType(prev);
    if (type == KING_BOMB)
    {
        return "none";
    }
    if (type == BOMB)
    {
        goto CHECK_BOMB;
    }
    if (!m[type].empty())
    {
        for (auto ele : m[type])
        {
            vector<int> pos;
            for (int i = 0; i < ele.first.size(); i++)
            {
                pos.push_back(ele.first[i] - '0');
            }
            ok = calCardValue(prev, pos);
            if (ok)
            {
                return ele.first;
            }
            else
            {
                continue;
            }
        }
        if (!ok)
        {
            goto CHECK_BOMB;
        }
    }
    else
    {
    CHECK_BOMB:
        if (type == BOMB)
        {
            if (!m[BOMB].empty())
            {
                for (auto ele : m[BOMB])
                {
                    vector<int> pos;
                    for (int i = 0; i < ele.first.size(); i++)
                    {
                        pos.push_back(ele.first[i]);
                    }
                    ok = calCardValue(prev, pos);
                    if (ok)
                    {
                        return ele.first;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            if (!m[KING_BOMB].empty())
            {
                return m[KING_BOMB].begin()->first;
            }
        }
        else
        {
            if (!m[BOMB].empty())
            {
                return m[BOMB].begin()->first;
            }
            if (!m[KING_BOMB].empty())
            {
                return m[KING_BOMB].begin()->first;
            }
        }
    }
    return "none";
}

int main()
{
    cin >> handcard;
    std::cout << "received" << endl;
    sortHand();
    string my_prev;
    string play;
    separateCard();
    while (true)
    {
        string s;
        cin >> s;
        if (s == "start")
        {
            play = attack();
            std::cout << play << endl;
            for (int i = 0; i < play.size(); i++)
            {
                removeCardFromHand(play[i]);
            }
            separateCard();
        }
        else
        {
            if (s == my_prev)
            {
                play = attack();
            }
            else
            {
                play = defend(s);
            }
            std::cout << play << endl;
            if (play != "none")
            {
                for (int i = 0; i < play.size(); i++)
                {
                    removeCardFromHand(play[i]);
                }
                separateCard();
            }
        }
        my_prev = play;
    }
    return 0;
}
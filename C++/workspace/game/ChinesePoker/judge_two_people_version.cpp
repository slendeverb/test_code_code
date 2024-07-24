#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int currentTurn = 0, previousTurn = 0;

const int playernum = 2;

namespace ChinesePoker
{
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

    void Knuth_Shuffle(std::vector<int> &card)
    {
        for (int i = card.size() - 1; i >= 0; i--)
        {
            std::swap(card[i], card[rand() % (i + 1)]);
        }
    }

    class Player
    {
    public:
        Player(const std::string &name) : name(name) {}

        void addCardToHand(const int &card)
        {
            hand.push_back(card);
        }

        void removeCardFromHand(const int &card)
        {
            auto it = std::find(hand.begin(), hand.end(), card);
            if (it != hand.end())
            {
                hand.erase(it);
            }
        }

        const std::vector<int> &getHand() const
        {
            return hand;
        }

        void sortHand()
        {
            std::sort(hand.begin(), hand.end(), compareCards);
        }

    private:
        std::string name;
        std::vector<int> hand;
    };

    class Game
    {
    public:
        std::vector<Player> players;
        std::string previousPlay = "none";

        Game() : players{Player("player1"), Player("player2")} {}

        void initialize()
        {
            dealCards();
        }

        void bidLandlord()
        {
            for (int i = 0; i < landlordCards.size(); i++)
            {
                players[0].addCardToHand(landlordCards[i]);
            }
        }

        bool isValidPlay(std::vector<int> &previousPlay, std::vector<int> &currentPlay)
        {
            CardType currentType = calCardType(currentPlay), previousType = calCardType(previousPlay);
            if (currentType == CardType::Invalid)
            {
                return false;
            }
            if (previousTurn == currentTurn)
            {
                return true;
            }
            else
            {
                if (currentType == CardType::KING_BOMB || (currentType == CardType::BOMB && previousType != CardType::BOMB) || (currentType == CardType::BOMB && previousType == CardType::BOMB && currentPlay[0] > previousPlay[0]))
                {
                    return true;
                }
                if (previousType != currentType)
                {
                    return false;
                }
                else
                {
                    return calCardValue(previousPlay, currentPlay);
                }
            }
            return false;
        }

        int isGameOver()
        {
            for (int id = 0; id < playernum; id++)
            {
                if (players[id].getHand().size() == 0)
                {
                    return id;
                }
            }
            return NotFinished;
        }

    private:
        std::vector<int> landlordCards;
        std::vector<int> allCards;

        void dealCards()
        {
            for (int suit = 0; suit < 4; suit++)
            {
                for (int rank = RANK_3; rank <= RANK_9; rank++)
                {
                    allCards.push_back(rank);
                }
                for (int rank = RANK_10; rank <= RANK_2; rank++)
                {
                    allCards.push_back(rank);
                }
            }
            allCards.push_back(RANK_SMALL_JOKER);
            allCards.push_back(RANK_BIG_JOKER);

            Knuth_Shuffle(allCards);

            for (int i = 0; i < 51; i += playernum)
            {
                for (int j = 0; j < playernum && (i + j) < 51; j++)
                {
                    players[j].addCardToHand(allCards[i + j]);
                }
            }

            for (int i = 51; i < 54; i++)
            {
                landlordCards.push_back(allCards[i]);
            }
        }
    };
};

// 此游戏为双人斗地主，默认第一个bot是地主

// 游戏规则:
// (1) 单张：前面提到过，大小顺序从3(最小)到大怪(最大)；
// (2) 一对：两张大小相同的牌，从3(最小)到2(最大)；
// (3) 三张：三张大小相同的牌；
// (4) 三张带一张：三张并带上任意一张牌，例如6-6-6-8，根据三张的大小来比较，例如9-9-9-3盖过8-8-8-A；
// (5) 三张带一对：三张并带上一对，类似扑克中的副路(Full House)，根据三张的大小来比较，例如Q-Q-Q-6-6盖过10-10-10-K-K；
// (6) 顺子：至少5张连续大小(从3到A，2和怪不能用)的牌，例如8-9-10-J-Q；
// (7) 连对：至少3个连续大小(从3到A，2和怪不能用)的对子，例如10-10-J-J-Q-Q-K-K；
// (8) 三张的顺子：至少2个连续大小(从3到A)的三张，例如4-4-4-5-5-5；
// (9) 三张带一张的顺子：每个三张都带上额外的一个单张，例如7-7-7-8-8-8-3-6，尽管三张2不能用，但能够带上单张2和怪；
// (10) 三张带一对的顺子：每个三张都带上额外的一对，只需要三张是连续的就行，例如8-8-8-9-9-9-4-4-J-J，尽管三张2不能用，但能够带上一对2【不能带一对怪，因为两张怪的大小不一样】，这里要注意，三张带上的单张和一对不能是混合的，例如3-3-3-4-4-4-6-7-7就是不合法的；
// (11) 炸弹：四张大小相同的牌，炸弹能盖过除火箭外的其他牌型，大的炸弹能盖过小的炸弹；
// (12) 火箭：一对怪，这是最大的组合，能够盖过包括炸弹在内的任何牌型；
// (13) 四张套路(四带二)：有两种牌型，一个四张带上两个单张，例如6-6-6-6-8-9，或一个四张带上两对，例如J-J-J-J-9-9-Q-Q，四带二只根据四张的大小来比较，只能盖过比自己小的同样牌型的四带二【四张带二张和四张带二对属于不同的牌型，不能彼此盖过】，不能盖过其他牌型，四带二能被比自己小的炸弹盖过

// 输入格式:
// 游戏开始时，会先发给每个bot一次初始手牌，接收后输出一个任意的字符串如"received"(无引号")作为与裁判机的惯例交互
// 之后裁判机输出给第一个bot一次"start"(无引号)作为游戏开始的标志,此时可以从第一个bot开始轮流出牌
// 在bot开始出牌后,裁判机输出的字符串会变为上一个有效输出的字符串
// 请对比该字符串与每个bot上一次输出的结果,如果一致,则该回合可以任意出牌

// 输出格式:
// 以字符串形式输出,打出的牌请在手牌中自行删去,如果手牌中的牌型大小比不过,则输出字符串"none"
// 如果输出不合规的出牌,则会直接判负
// 3-9和'3'-'9'代表牌3-9,17-24和'A'-'H'代表牌10-JOKER
// 输出时每张牌的数值+'0'后放入字符串中

int main()
{
    srand(time(NULL));
    json output;
    int result = ChinesePoker::NotFinished;
    ChinesePoker::Game game;
    game.initialize();
    game.bidLandlord();
    const std::string player_id[] = {"0", "1"};

    for (int id = 0; id < playernum; id++)
    {
        output = json();
        output["command"] = "request";
        game.players[id].sortHand();
        std::string s;
        for (int i = 0; i < game.players[id].getHand().size(); i++)
        {
            s.push_back((game.players[id].getHand())[i] + '0');
        }
        output["content"][player_id[id]] = s;
        s.clear();
        for (int i = 0; i < game.players[id].getHand().size(); i++)
        {
            for (int rank = ChinesePoker::RANK_3; rank <= ChinesePoker::RANK_9; rank++)
            {
                if (game.players[id].getHand()[i] == rank)
                {
                    s.push_back(rank + '0');
                    s.push_back(',');
                    break;
                }
            }
            int rank = game.players[id].getHand()[i];
            if (rank == ChinesePoker::RANK_10)
            {
                s += "10,";
            }
            else if (rank == ChinesePoker::RANK_JACK)
            {
                s += "J,";
            }
            else if (rank == ChinesePoker::RANK_QUEEN)
            {
                s += "Q,";
            }
            else if (rank == ChinesePoker::RANK_KING)
            {
                s += "K,";
            }
            else if (rank == ChinesePoker::RANK_ACE)
            {
                s += "A,";
            }
            else if (rank == ChinesePoker::RANK_2)
            {
                s += "2,";
            }
            else if (rank == ChinesePoker::RANK_SMALL_JOKER)
            {
                s += "Small Joker,";
            }
            else if (rank == ChinesePoker::RANK_BIG_JOKER)
            {
                s += "Big Joker,";
            }
        }
        if (!s.empty())
        {
            s.pop_back();
        }
        output["display"][player_id[id]] = s;
        output["display"] = output["display"].dump();
        std::cout << output << std::endl;
        json to_judge;
        std::cin >> to_judge;
    }

    output = json();
    output["command"] = "request";
    output["content"]["0"] = "start";
    output["display"]["0"] = "start";
    output["display"] = output["display"].dump();
    std::cout << output << std::endl;

    auto setWinner = [&](int to)
    {
        if (to == ChinesePoker::LandlordWon)
        {
            output["content"]["0"] = 3;
            output["content"]["1"] = 0;
        }
        else if (to == ChinesePoker::FarmerWon)
        {
            output["content"]["0"] = 0;
            output["content"]["1"] = 3;
        }
    };

    int cnt_turn = 0;
    bool ok = true;
    while (true)
    {
        cnt_turn++;
        output = json();
        output["command"] = "request";
        json to_judge;
        std::cin >> to_judge;
        std::string raw = to_judge[player_id[currentTurn]]["raw"].get<std::string>();

        if (raw != "none")
        {
            std::vector<int> pos;
            for (int i = 0; i < raw.size(); i++)
            {
                pos.push_back(raw[i] - '0');
            }
            if (game.previousPlay != "none")
            {
                std::vector<int> prev;
                for (int i = 0; i < game.previousPlay.size(); i++)
                {
                    prev.push_back(game.previousPlay[i] - '0');
                }
                ok = game.isValidPlay(prev, pos);
                if (!ok)
                {
                    if (currentTurn == ChinesePoker::landlord)
                    {
                        result = ChinesePoker::FarmerWon;
                    }
                    else
                    {
                        result = ChinesePoker::LandlordWon;
                    }
                    goto Ed;
                }
                else
                {
                    for (int i = 0; i < pos.size(); i++)
                    {
                        game.players[currentTurn].removeCardFromHand(pos[i]);
                    }
                }
            }
            else if (game.previousPlay == "none")
            {
                ChinesePoker::CardType type = ChinesePoker::calCardType(pos);
                if (type == ChinesePoker::Invalid)
                {
                    if (currentTurn == ChinesePoker::landlord)
                    {
                        result = ChinesePoker::FarmerWon;
                    }
                    else
                    {
                        result = ChinesePoker::LandlordWon;
                    }
                    goto Ed;
                }
            }
            if (cnt_turn == 1)
            {
                for (int i = 0; i < pos.size(); i++)
                {
                    game.players[currentTurn].removeCardFromHand(pos[i]);
                }
            }
            game.previousPlay = raw;
            previousTurn = currentTurn;
            result = game.isGameOver();
            if (result != ChinesePoker::NotFinished)
            {
                goto Ed;
            }
        }
        currentTurn = (currentTurn + 1) % playernum;
        output["content"][std::to_string(currentTurn)] = game.previousPlay;
        for (int id = 0; id < playernum; id++)
        {
            std::string s;
            for (int i = 0; i < game.players[id].getHand().size(); i++)
            {
                for (int rank = ChinesePoker::RANK_3; rank <= ChinesePoker::RANK_9; rank++)
                {
                    if (game.players[id].getHand()[i] == rank)
                    {
                        s.push_back(rank + '0');
                        s.push_back(',');
                        break;
                    }
                }
                int rank = game.players[id].getHand()[i];
                if (rank == ChinesePoker::RANK_10)
                {
                    s += "10,";
                }
                else if (rank == ChinesePoker::RANK_JACK)
                {
                    s += "J,";
                }
                else if (rank == ChinesePoker::RANK_QUEEN)
                {
                    s += "Q,";
                }
                else if (rank == ChinesePoker::RANK_KING)
                {
                    s += "K,";
                }
                else if (rank == ChinesePoker::RANK_ACE)
                {
                    s += "A,";
                }
                else if (rank == ChinesePoker::RANK_2)
                {
                    s += "2,";
                }
                else if (rank == ChinesePoker::RANK_SMALL_JOKER)
                {
                    s += "Small Joker,";
                }
                else if (rank == ChinesePoker::RANK_BIG_JOKER)
                {
                    s += "Big Joker,";
                }
            }
            if (!s.empty())
            {
                s.pop_back();
            }
            output["display"][player_id[id]] = s;
        }
        output["display"] = output["display"].dump();
        std::cout << output << std::endl;
    }

Ed:
    output = json();
    setWinner(result);
    output["command"] = "finish";
    output["display"]["Winner"] = result;
    if (ok)
    {
        output["display"]["reason"] = "出完了所有手牌";
    }
    else
    {
        output["display"]["reason"] = "对手违反出牌规则";
    }
    for (int id = 0; id < playernum; id++)
    {
        std::string s;
        for (int i = 0; i < game.players[id].getHand().size(); i++)
        {
            for (int rank = ChinesePoker::RANK_3; rank <= ChinesePoker::RANK_9; rank++)
            {
                if (game.players[id].getHand()[i] == rank)
                {
                    s.push_back(rank + '0');
                    s.push_back(',');
                    break;
                }
            }
            int rank = game.players[id].getHand()[i];
            if (rank == ChinesePoker::RANK_10)
            {
                s += "10,";
            }
            else if (rank == ChinesePoker::RANK_JACK)
            {
                s += "J,";
            }
            else if (rank == ChinesePoker::RANK_QUEEN)
            {
                s += "Q,";
            }
            else if (rank == ChinesePoker::RANK_KING)
            {
                s += "K,";
            }
            else if (rank == ChinesePoker::RANK_ACE)
            {
                s += "A,";
            }
            else if (rank == ChinesePoker::RANK_2)
            {
                s += "2,";
            }
            else if (rank == ChinesePoker::RANK_SMALL_JOKER)
            {
                s += "Small Joker,";
            }
            else if (rank == ChinesePoker::RANK_BIG_JOKER)
            {
                s += "Big Joker,";
            }
        }
        if (!s.empty())
        {
            s.pop_back();
        }
        output["display"][player_id[id]] = s;
    }
    output["display"] = output["display"].dump();
    std::cout << output << std::endl;
    return 0;
}
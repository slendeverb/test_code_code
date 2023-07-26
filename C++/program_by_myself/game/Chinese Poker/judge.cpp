#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int currentTurn = 0, previousTurn = 0;

const int playernum = 3;

namespace ChinesePoker
{
    enum identity
    {
        landlord,
        farmer1,
        farmer2
    };

    enum GameResult
    {
        NotFinished = -2,
        Initial = -1,
        LandlordWon,
        Farmer1Won,
        Farmer2Won

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
        RANK_10,
        RANK_JACK,
        RANK_QUEEN,
        RANK_KING,
        RANK_ACE,
        RANK_2,
        RANK_SMALL_JOKER,
        RANK_BIG_JOKER
    };

    enum class CardType
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

    struct Card
    {
        int value; // 牌的点数，3-15表示3到A，16表示小王，17表示大王
        CardType type;
    };

    // 比较两张牌的大小
    // 返回值大于0表示card1大于card2，小于0表示card1小于card2，等于0表示相等
    int compareCards(const Card &card1, const Card &card2)
    {
        if (card1.type != card2.type)
        {
            return static_cast<int>(card1.type) - static_cast<int>(card2.type);
        }
        return card1.value - card2.value;
    }

    // 判断牌是否为炸弹
    bool isBomb(const std::vector<Card> &cards)
    {
        if (cards.size() != 4)
        {
            return false;
        }
        return cards[0].value == cards[1].value &&
               cards[1].value == cards[2].value &&
               cards[2].value == cards[3].value;
    }

    // 判断牌是否为王炸
    bool isKingBomb(const std::vector<Card> &cards)
    {
        if (cards.size() != 2)
        {
            return false;
        }
        return cards[0].value == 16 && cards[1].value == 17;
    }

    CardType calCardType(const std::vector<Card> &card)
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
            if (card[0].value == card[1].value)
            {
                return CardType::PAIR;
            }
        }
        if (card.size() == 3)
        {
            if (card[0].value == card[1].value == card[2].value)
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
            if (card[0].value == card[1].value && card[1].value == card[2].value || card[1].value == card[2].value && card[2].value == card[3].value)
            {
                return CardType::TRIPLE_WITH_ONE;
            }
        }
        if (card.size() >= 5)
        {
            std::map<int, int> m;
            int cnt = 1;
            int maxx3 = -1, minn3 = 100;
            for (int i = 1; i < card.size(); i++)
            {
                if (card[i].value == RANK_2 || card[i].value == RANK_SMALL_JOKER && card[i].value == RANK_BIG_JOKER)
                {
                    return CardType::Invalid;
                }
                if (card[i].value == card[i - 1].value)
                {
                    cnt++;
                }
                else
                {
                    if (cnt == 3)
                    {
                        maxx3 = std::max(maxx3, card[i].value);
                        minn3 = std::min(minn3, card[i].value);
                    }
                    m[cnt]++;
                    cnt = 1;
                }
            }
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
            if (m[1] == card.size() && card[card.size() - 1].value - card[0].value == card.size() - 1)
            {
                return CardType::STRAIGHT;
            }
            if (card.size() / 2 >= 3 && card.size() % 2 == 0 && m[2] == card.size() / 2 && card[card.size() - 1].value - card[0].value == (card.size() / 2 - 1))
            {
                return CardType::STRAIGHT_PAIR;
            }
            if (m[3] == card.size() / 3 && card.size() % 3 == 0 && card[card.size() - 1].value - card[0].value == (card.size() / 3 - 1))
            {
                return CardType::PLANE;
            }
            if (m[3] >= 2 && m[3] == card.size() / 4 && maxx3 - minn3 == card.size() / 4 - 1)
            {
                return CardType::PLANE_WITH_WINGS_ONE;
            }
            if (m[3] >= 2 && m[3] == card.size() / 5 && maxx3 - minn3 == card.size() / 5 - 1)
            {
                return CardType::PLANE_WITH_WINGS_TWO;
            }
        }
        return CardType::Invalid;
    }

    bool calCardValue(const std::vector<Card> &previous, const std::vector<Card> &current)
    {
        CardType type = calCardType(current);
        if (type == CardType::SINGLE || type == CardType::PAIR || type == CardType::TRIPLE)
        {
            if (current[0].value > previous[0].value)
            {
                return true;
            }
        }
        if (type == CardType::STRAIGHT || type == CardType::STRAIGHT_PAIR || type == CardType::PLANE)
        {
            if (current[current.size() - 1].value > previous[previous.size() - 1].value)
            {
                return true;
            }
        }

        std::map<int, int> mCurrent, mPrevious;
        int cntCurrent = 1, cntPrevious;
        int maxxPrev = -1, maxxCurrent = -1;
        int maxxPrevCnt = -1, maxxCurrentCnt = -1;
        for (int i = 1; i < current.size(); i++)
        {
            if (current[i].value == current[i - 1].value)
            {
                cntCurrent++;
            }
            else
            {
                mCurrent[cntCurrent]++;
                maxxCurrentCnt = std::max(maxxCurrentCnt, cntCurrent);
                cntCurrent = 1;
            }

            if (previous[i].value == previous[i - 1].value)
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

    class Deck
    {
    public:
        Deck()
        {
            for (int suit = SUIT_SPADE; suit <= SUIT_DIAMOND; suit++)
            {
                for (int rank = RANK_3; rank <= RANK_2; rank++)
                {
                    cards.push_back({rank, CardType::SINGLE});
                }
            }
            cards.push_back({RANK_SMALL_JOKER, CardType::SINGLE});
            cards.push_back({RANK_BIG_JOKER, CardType::SINGLE});
        }

        void shuffle()
        {
            std::random_shuffle(cards.begin(), cards.end());
        }

        std::vector<Card> dealCards(int numCards)
        {
            std::vector<Card> dealtCards;
            if (numCards <= static_cast<int>(cards.size()))
            {
                dealtCards.assign(cards.begin(), cards.begin() + numCards);
                cards.erase(cards.begin(), cards.begin() + numCards);
            }
            return dealtCards;
        }

    private:
        std::vector<Card> cards;
    };

    class Player
    {
    public:
        Player(const std::string &name) : name(name) {}

        void addCardToHand(const Card &card)
        {
            hand.push_back(card);
        }

        void removeCardFromHand(const Card &card)
        {
            auto it = std::find(hand.begin(), hand.end(), card);
            if (it != hand.end())
            {
                hand.erase(it);
            }
        }

        const std::vector<Card> &getHand() const
        {
            return hand;
        }

        void sortHand()
        {
            std::sort(hand.begin(), hand.end(), compareCards);
        }

    private:
        std::string name;
        std::vector<Card> hand;
    };

    class Game
    {
    public:
        std::vector<Player> players;
        std::string previousPlay;
        std::vector<int> cardNum = {20, 17, 17};

        void initialize()
        {
            deck.shuffle();
            dealCards();
        }

        void bidLandlord()
        {
            // 默认player1是地主
            for (int i = 0; i < landlordCards.size(); i++)
            {
                players[0].addCardToHand(landlordCards[i]);
            }
        }

        bool isValidPlay(const std::vector<Card> &previousPlay, const std::vector<Card> &currentPlay)
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
                if (currentType == CardType::KING_BOMB || (currentType == CardType::BOMB && previousType != CardType::BOMB) || (currentType == CardType::BOMB && previousType == CardType::BOMB && currentPlay[0].value > previousPlay[0].value))
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

        int isGameOver(const std::vector<int> &cardNum)
        {
            for (int id = 0; id < playernum; id++)
            {
                if (cardNum[id] == 0)
                {
                    return id;
                }
            }
            return NotFinished;
        }

    private:
        Deck deck;
        std::vector<Card> landlordCards;

        void dealCards()
        {
            std::vector<Card> allCards = deck.dealCards(54);
            for (int i = 0; i < 51; i += playernum)
            {
                for (int j = 0; j < playernum; j++)
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

// 此游戏为三人斗地主，默认第一个bot是地主

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
// 游戏开始时，会先发给每个bot一次初始手牌，接收后输出一个任意的字符串作为与裁判机的惯例交互
// 之后裁判机输出给第一个bot一次"start"(无引号)作为游戏开始的标志,此时可以从第一个bot开始轮流出牌
// 在bot开始出牌后,裁判机输出的字符串会变为上一个有效输出的字符串
// 请对比该字符串与每个bot上一次输出的结果,如果一致,则该回合可以任意出牌

// 输出格式:
// 以字符串形式输出(请按大小升序排列),如果手牌中的牌型大小比不过,则输出空字符串.

int main()
{
    json output;
    int result = ChinesePoker::NotFinished;
    ChinesePoker::Game game;
    game.initialize();
    game.bidLandlord();
    const std::string player_id[] = {"0", "1", "2"};

    for (int id = 0; id < playernum; id++)
    {
        output = json();
        output["command"] = "request";
        game.players[0].sortHand();
        std::string s;
        for (int i = 0; i < game.players[0].getHand().size(); i++)
        {
            s.push_back(game.players[0].getHand()[i].value + '0');
        }
        output["content"]["0"] = s;
        std::cout << output << std::endl;
        json to_judger;
        std::cin >> to_judger;
    }

    output = json();
    output["command"] = "request";
    output["content"]["0"] = "start";
    std::cout << output << std::endl;

    auto setWinner = [&](int to)
    {
        if (to == ChinesePoker::LandlordWon)
        {
            output["content"]["0"] = 1;
            output["content"]["1"] = 0;
            output["content"]["2"] = 0;
        }
        else
        {
            output["content"]["0"] = 0;
            output["content"]["1"] = 1;
            output["content"]["2"] = 1;
        }
    };

    while (true)
    {
        output = json();
        output["command"] = "request";
        json to_judger;
        std::cin >> to_judger;
        std::string raw = to_judger["raw"].get<std::string>();

        if (!raw.empty())
        {
            game.previousPlay = raw;
            previousTurn = currentTurn;
            game.cardNum[previousTurn] -= raw.size();
            result = game.isGameOver(game.cardNum);
            if (result != ChinesePoker::NotFinished)
            {
                goto Ed;
            }
        }
        currentTurn = (currentTurn + 1) % playernum;
        output["content"][std::to_string(currentTurn)] = game.previousPlay;
        std::cout << output << std::endl;
    }

Ed:
    output = json();
    setWinner(result);
    output["command"] = "finish";
    std::cout << output << std::endl;
    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ChinesePoker
{
    const int playernum = 3;

    enum identity
    {
        landlord,
        farmer1,
        farmer2
    };

    enum GameResult
    {
        NotFinished = -1,
        Initial = 0,
        Farmer1Won = 1,
        Farmer2Won = 2,
        LandlordWon = 3
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
        SINGLE = 1,       // 单张
        PAIR,             // 对子
        TRIPLE,           // 三张
        TRIPLE_WITH_ONE,  // 三带一
        TRIPLE_WITH_TWO,  // 三带二
        STRAIGHT,         // 顺子
        STRAIGHT_PAIR,    // 连对
        PLANE,            // 飞机（三顺）
        PLANE_WITH_WINGS, // 飞机带翅膀
        BOMB,             // 炸弹
        KING_BOMB         // 王炸（大小王）
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

    CardType calCardType(const std::vector<Card> &card)
    {
    }

    int calCardValue(const std::vector<Card> &card)
    {
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

        const std::vector<Card> &playCard() const
        {
        }

    private:
        std::string name;
        std::vector<Card> hand;
    };

    class Game
    {
    public:
        Game() : currentPlayerIndex(Initial), previousPlayerIndex(Initial), gameWon(Initial) {}

        std::vector<Player> players;
        std::vector<int> id;
        std::vector<std::string> playername = {"Player1", "Player2", "Player3"};
        std::vector<Card> previousPlay;

        void initialize()
        {
            deck.shuffle();
            players.clear();
            previousPlay.clear();
            for (int i = 0; i < playernum; i++)
            {
                players.push_back(Player(playername[i]));
            }
            id.clear();
            id.assign(playernum, 0);
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
            if (calCardType(currentPlay) == CardType::Invalid)
            {
                return false;
            }
            if (previousPlayerIndex == currentPlayerIndex)
            {
                return true;
            }
            else
            {
                if (calCardType(currentPlay) == CardType::KING_BOMB)
                {
                    return true;
                }
                if (calCardType(previousPlay) != calCardType(currentPlay))
                {
                    return false;
                }
                else
                {
                    int prevPoint = calCardValue(previousPlay);
                    int currentPoint = calCardValue(currentPlay);
                    if (currentPoint > prevPoint)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return false;
        }

        int isGameOver(const std::vector<Player> &players)
        {
            for (int winner = landlord; winner <= farmer2; winner++)
            {
                const std::vector<Card> &tmp = players[winner].getHand();
                if (tmp.size() == 0)
                {
                    return winner;
                }
            }
            return NotFinished;
        }

        void play()
        {
        }

    private:
        Deck deck;
        std::vector<Card> landlordCards;
        int currentPlayerIndex, previousPlayerIndex;
        int gameWon;

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

int main()
{
    ChinesePoker::Game game;
    game.play();
    return 0;
}
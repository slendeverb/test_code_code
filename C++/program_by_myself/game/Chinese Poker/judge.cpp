#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ChinesePoker
{
    const int playernum = 3;

    enum players
    {
        farmer1 = 1,
        farmer2,
        landlord
    };

    enum GameResult
    {
        NotFinished = -2,
        Draw = -1,
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

    class Deck
    {
    public:
        Deck()
        {
            for (int suit = 0; suit < 4; suit++)
            {
                for (int rank = 3; rank <= 15; rank++)
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
        Game() : currentPlayerIndex(0), gameWon(0) {}

        void initialize()
        {
            deck.shuffle();
            players.clear();
            players.push_back(Player("Player1"));
            players.push_back(Player("Player2"));
            players.push_back(Player("Player3"));
            dealCards();
        }

        void play();

    private:
        Deck deck;
        std::vector<Player> players;
        std::vector<Card> landlordCards;
        int currentPlayerIndex;
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

    void Game::play()
    {

    }
};

int main()
{
    ChinesePoker::Game game;
    game.play();
    return 0;
}
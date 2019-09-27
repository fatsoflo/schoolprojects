/******************************************************************************
FFongMyShipSails.cpp
Created on: May 25, 2018
    Author: Florence Fong
*******************************************************************************/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
using namespace std;

class Card{
public:
    string suit;
    string face;
    Card() {}
    Card(string _suit, string _face) : suit(_suit), face(_face) {}

    string outputAsString() {
        return suit + face;
    }

    void output(bool withNewLine = false) {
        cout << outputAsString();
        if (withNewLine) {
            cout << endl;
        }
    }
};
const int SIZE = 52;
const int PLAYER_DECK_SIZE = 7;
const string faces[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const string suits[] = {"D", "C", "H", "S"};
const char validCmds[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', '?'};

class DeckOfCards {
public:
    vector <Card> hand;

    DeckOfCards() {
        for(int i = 0; i < SIZE; i++) {
            Card card = Card(suits[i / 13], faces[i % 13]);
            hand.push_back(card);
        }
    };

    void shuffle() {
        vector <Card> deckShuffled;
        vector <int> picked;
        vector <int>::iterator search;

        while(true) {
            int cardIndex = rand() % SIZE;
            search = find(begin(picked), end(picked), cardIndex);

            if (search == std::end(picked)) {
                picked.push_back(cardIndex);
                deckShuffled.push_back(hand[cardIndex]);
            }
            if (deckShuffled.size() == SIZE) {
                break;
            }
        }
        hand = deckShuffled;
    };

    Card pick() {
        Card card = hand.back();
        hand.pop_back();
        return card;
    }
    void output(){
        cout << "Deck: " << endl;
        for (int i = 0; i < hand.size(); i++) {
            Card& c = hand[i];
            cout << c.suit << c.face << " ";
        }
        cout <<endl;
    };
};

class Player {
public:
    int selfIndex;
    Player* next;
    vector <Card> hand;
    int discardIndex;
    Card discard;
    Card receivedCard;

    Player() {}

    Player(int _name, DeckOfCards& _deck): selfIndex(_name) {
        // deal 7 cards to the player
        for (int i = 0; i < PLAYER_DECK_SIZE; i++) {
            Card card = _deck.pick();
            hand.push_back(card);
        }
    };

    void output() {
        cout << selfIndex << ":" << "\t";
        for (int i = 0; i < PLAYER_DECK_SIZE; i++) {
            Card& card = hand[i];
            card.output();
            cout << "\t";
        }
        cout << endl;
    }

    bool hasWon() {
        string suit = hand[0].suit;
        string discardedSuit = discard.suit;

        for (auto& card : hand) {
            if (card.suit != suit) {
                return false;
            }
        }
        return true;
    }
    
    virtual void chooseDiscard(int slot) {
        discardIndex = slot;
        discard = hand[discardIndex];

        next->receive(discard);

        cout << "\t\t" << "Player " << selfIndex << " gave "
            << next->selfIndex << " " << discard.outputAsString() << endl;
    }

    void receive(Card card) {
        receivedCard = card;
    }

    void replenish() {
        hand[discardIndex] = receivedCard;
    }

};

class HumanPlayer : public Player {
public:
    HumanPlayer(int selfIndex, DeckOfCards& hand) : Player(selfIndex, hand) {}

    void chooseDiscard(int _discardedSlot) {
        Player::chooseDiscard(_discardedSlot);
    }
};

class AutoPlayer : public Player {
public:
    AutoPlayer(int selfIndex, DeckOfCards& hand) : Player(selfIndex, hand) {}

    void chooseDiscard(int a) {
        // Count how many cards are there for each suit
        map<string, int> count;
        map <string, int> :: iterator itr;

        count["D"] = 0;
        count["C"] = 0;
        count["H"] = 0;
        count["S"] = 0;

        for (auto& card : hand) {
            count[card.suit]++;
        }

        // Determine the least common suit
        string minimumSuit;
        int minimumCount = 10; // start off with a larger number than 7


        for (itr = count.begin(); itr != count.end(); itr++)
        {
            int suitCount = itr->second;
            if (suitCount < minimumCount && suitCount != 0) {
                minimumSuit = itr->first;
                minimumCount = suitCount;
            }
        }

        // Discard the first card of least common suit
        int slot = 0;
        for (auto& card : hand) {
            if (card.suit == minimumSuit) {
                Player::chooseDiscard(slot);
                return;
            }
            slot++;
        }
    }
};




class Game {
public:
    DeckOfCards hand;
    Player * p0;
    Player * p1;
    Player * p2;
    Player * p3;
    Player * p4;
    vector <Player *> players;

    Game() {
        hand.shuffle();
        p0 = new HumanPlayer(0, hand);
        p1 = new AutoPlayer(1, hand);
        p2 = new AutoPlayer(2, hand);
        p3 = new AutoPlayer(3, hand);
        p4 = new AutoPlayer(4, hand);
        p0->next = p1;
        p1->next = p2;
        p2->next = p3;
        p3->next = p4;
        p4->next = p0;

        players.push_back(p0);
        players.push_back(p1);
        players.push_back(p2);
        players.push_back(p3);
        players.push_back(p4);
    }

    void outputPlayers() {
        for(auto p : players) {
            p->output();
        }
    }

    void outputP0Hand() {
        cout << "Your hand:\n";
        p0->output();
        cout << "\ta\tb\tc\td\te\tf\tg\n";
    }

    char getCommand() {
        while(true) {
            cout << "cmd: ";
            char in;
            cin >> in;

            for (auto& cmd : validCmds) {
                if (cmd == in) {
                    return cmd;
                }
            }
            cout << "Invalid choice" << endl;
        }
    }

    void play() {
        outputP0Hand();
        while (true) {
            char cmd = getCommand();
            if (cmd == '?') {
                outputPlayers();
            } else {
                int discardIndex = (int)cmd - 97;
                p0->chooseDiscard(discardIndex);
                p1->chooseDiscard(-1);
                p2->chooseDiscard(-1);
                p3->chooseDiscard(-1);
                p4->chooseDiscard(-1);

                for(auto p : players) {
                    p->replenish();
                }

                bool someoneWon = false;
                for(auto p : players) {
                    if (p->hasWon()) {
                        someoneWon = true;
                        cout << "Player " << p->selfIndex << " is a winner!\n";
                    }
                }
                if (someoneWon) {
                    cout << "At the end of the game the players had:\n";
                    outputPlayers();
                    return;
                }

                // game still not over. show p0's hand
                outputP0Hand();
            }
        }
    }
};

int main(){
    srand(time(NULL));
    Game game;
    game.play();
    return 0;
}

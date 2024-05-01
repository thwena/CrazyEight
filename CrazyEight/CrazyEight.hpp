#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "player.hpp"
#include "deck.hpp"

class CrazyEight{
    public:
        CrazyEight();
        int playerTurn(vector<player> &players, int curPlayer, deck &cards, bool &skip, bool &specialSuit, string &suitSpecial, bool &reverseDir);
        void numPlayer();
        void twoPlayer();
        void threePlayer();
        void fourPlayer();
        void fivePlayer();
        void sixPlayer();
        bool endGame(player person);
        int specialCard(int card, bool &skip);
        string eight();
        void ace(player &person, deck &cards);
        string joker(player &person, deck &cards);
        void queen(bool &reverseDir);
        void noDrawPile(deck &cards);
    private:

};
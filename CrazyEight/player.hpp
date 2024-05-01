#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std; 

class player {
    public:
        player();
        void playerName();
        void drawCard(int cardNum);
        void playingField(vector<int> cards, bool specialSuit, string suitSpecial);
        int playCard(vector<int> cards, bool &specialSuit, string suitSpecial);
        bool availablePlay(vector<int> cards, bool specialSuit, string suitSpecial);
        string cardSuit(int card);
        string cardMem(int card);
        bool legalPlay(int cardNum, vector<int> discardPile, bool specialSuit, string suitSpecial);
        void numWins();
        void playerInfo();
        vector<int> playerCards();
        void dealtCards(vector<int> cards);
        string namePlayer();
        
        void save();

    private:
        string name;
        vector<int> hand;
        int numWin;



};
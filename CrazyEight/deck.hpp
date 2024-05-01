#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <ctime>

using namespace std;

class deck{
    public:
        deck(vector<int> &player1, vector<int> &player2);
        deck(vector<int> &player1, vector<int> &player2, vector<int> &player3);
        deck(vector<int> &player1, vector<int> &player2, vector<int> &player3, vector<int> &player4);
        deck(vector<int> &player1, vector<int> &player2, vector<int> &player3, vector<int> &player4, vector<int> &player5);
        deck(vector<int> &player1, vector<int> &player2, vector<int> &player3, vector<int> &player4, vector<int> &player5, vector<int> &player6);
        void deckSetup2P();
        void deckSetup3P();
        void deckSetup5P();
        
        void shuffle();
        void noDrawCards();
        void discard(int card);
        int draw();
        void play(int card);
        void save();
        string cardSuit(int cardNum);
        string cardMem(int cardNum);
        string cardType(int card);
        vector<int> drawCards();
        vector<int> discardCards();



    private:
        vector<int> drawPile;
        vector<int> discardPile;
};
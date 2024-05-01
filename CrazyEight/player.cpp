#include "player.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

//calls player Name sets wins to 0, and clears hand
player::player(){
    numWin = 0;
    playerName();
    cout << endl;
    hand.clear();

}

//take user name confirms their name and saves it
void player::playerName(){
    int ans = 2;
    do{
        cout << "Please Type your first name\n>> ";
        cin >> name;
        cout << endl;
        cout << "Name: " << name << endl;
        cout << "If you're name is correct please type '1' if not type '2'" << endl;
        cin >> ans; 
    }while(ans != 1);
}

//give card to player hand when drawing card
void player::drawCard(int cardNum){
    hand.push_back(cardNum);
    sort(hand.begin(), hand.end());
}

//Prints players card and top card of discard pile or suit that is expected
void player::playingField(vector<int> cards, bool specialSuit, string suitSpecial){
    int count = 0;
    if(specialSuit){                                    //checks if last card played was a wild card, then prints given suit
        cout << "Card is: " << suitSpecial << endl;
    } else {
        cout << "Card is: " << cardMem(cards[0]) << " of " << cardSuit(cards[0]) << endl;
    }
    for(int i = 0; i < hand.size(); i++){
        cout << i << ": " << cardMem(hand[i]) << " of " << cardSuit(hand[i]) << "; ";
        if(count == 4){
            cout << endl;
            count = 0;
        }
        count++;
    }
}

//asks the user which card they would like to play, deletes card from hand and returns the card to be played.
int player::playCard(vector<int> cards, bool &specialSuit, string suitSpecial){
    int cardIndex, card, count = 0;
    bool flag = false, play = false;
    if(specialSuit){                                    //checks if last card played was a wild card, then prints given suit
        cout << "Card is: " << suitSpecial << endl;
        
    } else {
        cout << "Card is: " << cardMem(cards[0]) << " of " << cardSuit(cards[0]) << endl;
    }
    for(int i = 0; i < hand.size(); i++){
        cout << i << ": " << cardMem(hand[i]) << " of " << cardSuit(hand[i]) << "; ";
        if(count == 4){
            cout << endl;
            count = 0;
        }
        count++;
    }
    do{
        do{
            if(flag){
                cout << "Error: Incorrect value entered!" << endl;
            }
            cout << endl << "What is the index of the card you would like to play: ";
            cin >> cardIndex;
            flag = true;
        }while(cardIndex < -1 || cardIndex > hand.size()+1);
        if(cardIndex == -1){
            play == true;
        } else if(legalPlay(hand[cardIndex], cards, specialSuit, suitSpecial)){
            play = true;
        }
    } while(!play);
    specialSuit = false;                        //sets special suit to false,
    if(cardIndex == -1){
        return cardIndex;
    } else{
        card = hand[cardIndex];
        hand.erase(hand.begin()+cardIndex);     //erases played card from hand
        return card;
    }
    
}

//returns true if player has available play, false if player does not have available play
bool player::availablePlay(vector<int> cards, bool specialSuit, string suitSpecial){
    for(int i = 0; i < hand.size(); i++){
        if(legalPlay(hand[i], cards, specialSuit, suitSpecial)){
            return true;
        }
    }
    return false;
}

//returns card suit
string player::cardSuit(int card){
    string suit = "";
    if(0 <= card && card <= 12){
        suit = "Spade";
    } else if(13 <= card && card <= 25){
        suit = "Hearts";
    } else if(26 <= card && card <= 38){
        suit = "Club";
    } else if(39 <= card && card <= 51){
        suit = "Diamond";
    }
    return suit;
}

//returns card name eg Ace, King 6
string player::cardMem(int card){
    int card1 = 0, card2 = 13, card3 = 26, card4 = 39;
    string type = "";
    if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "Ace";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "2";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "3";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "4";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "5";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "6";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "7";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "8";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "9";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "10";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "Jack";
    } else if(card == card1++ || card == card2++ || card == card3++ || card == card4++){
        type = "Queen";
    } else if(card == card1 || card == card2 || card == card3 || card == card4){
        type = "King";
    } else if(card == 52 || card == 53){
        type = "Joker";
    }
    return type;
}

//returns true if the play is legal, false if it is not a legal play
bool player::legalPlay(int cardNum, vector<int> discardPile, bool specialSuit, string suitSpecial){
    if(specialSuit){
        if(cardSuit(cardNum) == suitSpecial){
            return true;
        } else if(cardNum == 7 || cardNum == 20 || cardNum == 33 || cardNum == 46 || cardNum == 52 || cardNum == 53){
            return true;
        } else {
            return false;
        }
    } else if(cardNum == 7 || cardNum == 20 || cardNum == 33 || cardNum == 46 || cardNum == 52 || cardNum == 53){
        return true;
    } else {
        if(cardSuit(cardNum) == cardSuit(discardPile[0])){
            return true;
        } else if(cardMem(cardNum) == cardMem(discardPile[0])){
            return true;
        } else {
            return false;
        }
    }
}

//adds to numWins. Not used future implementation
void player::numWins(){
    numWin++;
}

//return user info, not used future implementation
void player::playerInfo(){
    cout << name << endl;
    for(int i = 0; i < hand.size(); i++){
        cout << hand[i] << " ";
    }
    cout << endl << "Number of wins: " << numWin << endl;
}

//returns players hand
vector<int> player::playerCards(){
    return hand;
}

//deals cards to players hand
void player::dealtCards(vector<int> cards){
    hand.clear();
    hand = cards;
}

//returns player name
string player::namePlayer(){
    return name;
}

//saves player info
void player::save(){
    string cardHand = "";                       //Sets string to nothing
    string winCount = cardHand;                 //^^
    cardHand += name;                           //Adds name to string 
    winCount += name;                           //^^
    cardHand += ".txt";                         //Adds extension to name so that it can open the correct file
    winCount += "W.txt";                        //^^
    ofstream playerFile;                        //Creates object of type ofstream to write to file
    playerFile.open(cardHand.c_str());          //Opens file
    if(playerFile.is_open()){                   
        for(int i = 0; i < hand.size(); i++){   //Write hand to save file
            playerFile << hand[i] << endl;
        }
    }
    ofstream wins;                              //creates ofstream to record number of wind
    wins.open(winCount.c_str());                //opens file
    if(wins.is_open()){
        wins << numWin << endl;                 //writes to file
    }
}
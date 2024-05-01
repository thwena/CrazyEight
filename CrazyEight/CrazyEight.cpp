//Crazy Eigts
//Card game
//8: wild
//Aces: Draw 2
//Joker: Wild Draw 6
//Queen: reverse
//King: Skip
#include "CrazyEight.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;

CrazyEight::CrazyEight(){               //Contructor, setting up the game,  prints rules, and call a function.
    int ans = 1;
    bool error = false;
    do{
        cout << "This game is called CrazyEights" << endl
             << "You can only play a card if either the suit or the number matches" << endl
             << "8's and Jokers are wild cards, They allow you to change the suit" << endl
             << "Jokers are wild draw 6, You can choose to play with Jokers" << endl
             << "If you choose to play with Jokers there are only 2 of them in play" << endl
             << "Aces are draw 2. They cannot be stacked" << endl
             << "Queens reverse direction of play" << endl
             << "Kings skip the next player" << endl
             << "Please follow on screen prompts" << endl;
        numPlayer();
        do{
            if(error){
                cout << "ERROR: Incorrect value entered." << endl;
            }
            cout << "If you would like to play again type '1' if not type '2'\n>> ";
            cin >> ans;
        } while (ans != 1 || ans != 2);
    }while (ans == 1);
}

//Player turn is the set of instruction for what to do for each players turn.
int CrazyEight::playerTurn(vector<player> &players, int curPlayer, deck &cards, bool &skip, bool &specialSuit, string &suitSpecial, bool &reverseDir){
    noDrawPile(cards);                      //Makes sure there are cards in the draw pile. If not it reshuffles all but the top card of the discard.
    int specialCardNum;
    int card;
    char check;
    bool played = false;
    cout << players[curPlayer].namePlayer() << " turn." << endl;
    cout << "Type anything then press enter to Continue:" << endl;
    cin >> check;
    
    if(skip){ //Checks if players turn has been skipped
        cout << "You have been skipped." << endl;
        cout << "Type anything then press enter to Continue:" << endl;
        cin >> check;
        skip = false;
    } else {
    if(players[curPlayer].availablePlay(cards.discardCards(), specialSuit, suitSpecial)){ // checks if user has available play to make.
        card = players[curPlayer].playCard(cards.discardCards(), specialSuit, suitSpecial);
        if(card == -1){
            players[curPlayer].drawCard(cards.draw());
        } else {
            cards.play(card);
            if(card != -1){
                specialCardNum = specialCard(card, skip); // checks if player played a special card and does acoordingly
                if(specialCardNum == 1){
                    int nextPlayer = curPlayer;
                    if(reverseDir){
                        nextPlayer -= 1;
                        if(nextPlayer == -1){
                            nextPlayer = players.size()-1;
                        }
                    } else {
                        nextPlayer += 1;
                        if(nextPlayer == players.size()){
                            nextPlayer = 0;
                        }
                    }
                    ace(players[nextPlayer], cards);
                } else if(specialCardNum == 2){
                    queen(reverseDir);
                } else if(specialCardNum == 3){
                    skip = true;
                } else if(specialCardNum == 4){
                    specialSuit = true;
                    suitSpecial = eight();
                } else if(specialCardNum == 5){
                    int nextPlayer = curPlayer;
                    if(reverseDir){
                        nextPlayer -= 1;
                        if(nextPlayer == -1){
                            nextPlayer = players.size()-1;
                        }
                    } else {
                        nextPlayer += 1;
                        if(nextPlayer == players.size()){
                            nextPlayer = 0;
                        }
                    }
                    specialSuit = true;
                    suitSpecial = joker(players[nextPlayer], cards);
                }
            }
            played = true;
        }
    } else{ //If user doesn't have available play it makes them draw and lets them know
        players[curPlayer].playingField(cards.discardCards(), specialSuit, suitSpecial);
        cout << endl << endl << "No available play. Drew card." << endl;
        players[curPlayer].drawCard(cards.draw());
        cout << "Type anything then press enter to Continue:" << endl;
        cin >> check;

        }
    }
    players[curPlayer].save(); //saves the players hand and some other things. Not needed for this game.
    cards.save();               // ^^
    noDrawPile(cards);          //checks to make sure there is card to be drawn
    if(played){
        return card;
    } else {
        return -1;
    }
}

void CrazyEight::numPlayer(){      //Lets the user input how many players 2-6. and calls the correct function accordingly
    int numPlayers = 0;
    bool error = false;
    do{
        if(error){
            cout << "Error: Number outside excepted values" << endl;
        }
        cout << "How many players are there? (2-6 players)\n>> ";
        cin >> numPlayers;
    } while(numPlayers < 2 || numPlayers > 6);
    if(numPlayers == 2){
        twoPlayer();
    } else if(numPlayers == 3){
        threePlayer();
    } else if(numPlayers == 4){
        fourPlayer();
    } else if(numPlayers == 5){
        fivePlayer();
    } else {
        sixPlayer();
    }
}

void CrazyEight::twoPlayer(){   //Game code for 2 player
    bool gameOver = false, skip = false, used = true;   //Basic setup. gameover is used to signal end ofgame. skip is used in conjuection with special cards
    bool specialSuit = false, reverseDir = false;       //special suit is used in conjunction with wild cards, reverse direction tells the program which way to run
    string suitSpecial = "";                            //records what suit is chosen by wild card
    player player1, player2;                            //setups the players
    vector<int> player1Cards, player2Cards;             //Creates the storage lcoation for the cards of the user.
    deck cards(player1Cards,player2Cards);              //deals the cards
    vector<player> players;                             //vector to store the users and cycle through player turns
    players.push_back(player1);                         //adds players to the vector of player
    players.push_back(player2);
    players[0].dealtCards(player1Cards);                //gives player the dealt cards
    players[1].dealtCards(player2Cards);
    cards.save();
    players[0].save(), players[1].save();
    int i = 0;
    do{
        int card;
        card = playerTurn(players, i, cards, skip, specialSuit, suitSpecial, reverseDir); //takes the card the player selects to play
        gameOver = endGame(players[i]);                 //checks if user player their last card
        if(gameOver){
            break;
        }
        if(reverseDir){                                 //checks if player turn is in normal rotation of reversed rotation
            i--;                                        //and cycles through the players accordingly
            if(i == -1){
                i = players.size() -1;
            }
        } else {
            i++;
            if(i == players.size()){
                i = 0;
            }
        }
        cout << flush;                                  //flushes the cout
        system("CLS");                                  //clears the screen so other users can't see previous players hand
    } while(!gameOver);

}

//same thing as two player with added players
void CrazyEight::threePlayer(){
    bool gameOver = false, skip = false, used = true;
    bool specialSuit = false, reverseDir = false;
    string suitSpecial = "";
    player player1, player2, player3;
    vector<int> player1Cards, player2Cards, player3Cards;
    deck cards(player1Cards,player2Cards, player3Cards);
    vector<player> players;
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players[0].dealtCards(player1Cards);
    players[1].dealtCards(player2Cards);
    players[2].dealtCards(player3Cards);
    cards.save();
    players[0].save(), players[1].save(), players[2].save();
    int i = 0;
    do{
        int card;
        card = playerTurn(players, i, cards, skip, specialSuit, suitSpecial, reverseDir);
        gameOver = endGame(players[i]);
        if(gameOver){
            break;
        }
        if(reverseDir){
            i--;
            if(i == -1){
                i = players.size() -1;
            }
        } else {
            i++;
            if(i == players.size()){
                i = 0;
            }
        }
        cout << flush;
        system("CLS");
    } while(!gameOver);

}

//same thing as two player with added players
void CrazyEight::fourPlayer(){
    bool gameOver = false, skip = false, used = true;
    bool specialSuit = false, reverseDir = false;
    string suitSpecial = "";
    player player1, player2, player3, player4;
    vector<int> player1Cards, player2Cards, player3Cards, player4Cards;
    deck cards(player1Cards,player2Cards, player3Cards, player4Cards);
    vector<player> players;
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);
    players[0].dealtCards(player1Cards);
    players[1].dealtCards(player2Cards);
    players[2].dealtCards(player3Cards);
    players[3].dealtCards(player4Cards);
    cards.save();
    players[0].save(), players[1].save(), players[2].save(), players[3].save();
    int i = 0;
    do{
        int card;
        card = playerTurn(players, i, cards, skip, specialSuit, suitSpecial, reverseDir);
        gameOver = endGame(players[i]);
        if(gameOver){
            break;
        }
        if(reverseDir){
            i--;
            if(i == -1){
                i = players.size() -1;
            }
        } else {
            i++;
            if(i == players.size()){
                i = 0;
            }
        }
        cout << flush;
        system("CLS");
    } while(!gameOver);
}

//same thing as two player with added players
void CrazyEight::fivePlayer(){
    bool gameOver = false, skip = false, used = true;
    bool specialSuit = false, reverseDir = false;
    string suitSpecial = "";
    player player1, player2, player3, player4, player5;
    vector<int> player1Cards, player2Cards, player3Cards, player4Cards, player5Cards;
    deck cards(player1Cards,player2Cards, player3Cards, player4Cards, player5Cards);
    vector<player> players;
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);
    players.push_back(player5);
    players[0].dealtCards(player1Cards);
    players[1].dealtCards(player2Cards);
    players[2].dealtCards(player3Cards);
    players[3].dealtCards(player4Cards);
    players[4].dealtCards(player5Cards);
    cards.save();
    players[0].save(), players[1].save(), players[2].save(), players[3].save();
    players[4].save();
    int i = 0;
    do{
        int card;
        card = playerTurn(players, i, cards, skip, specialSuit, suitSpecial, reverseDir);
        gameOver = endGame(players[i]);
        if(gameOver){
            break;
        }
        if(reverseDir){
            i--;
            if(i == -1){
                i = players.size() -1;
            }
        } else {
            i++;
            if(i == players.size()){
                i = 0;
            }
        }
        cout << flush;
        system("CLS");
    } while(!gameOver);
}

//same thing as two player with added players
void CrazyEight::sixPlayer(){
    bool gameOver = false, skip = false, used = true;
    bool specialSuit = false, reverseDir = false;
    string suitSpecial = "";
    player player1, player2, player3, player4, player5, player6;
    vector<int> player1Cards, player2Cards, player3Cards, player4Cards, player5Cards, player6Cards;
    deck cards(player1Cards,player2Cards, player3Cards, player4Cards, player5Cards, player6Cards);
    vector<player> players;
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);
    players.push_back(player5);
    players.push_back(player6);
    players[0].dealtCards(player1Cards);
    players[1].dealtCards(player2Cards);
    players[2].dealtCards(player3Cards);
    players[3].dealtCards(player4Cards);
    players[4].dealtCards(player5Cards);
    players[5].dealtCards(player6Cards);
    cards.save();
    players[0].save(), players[1].save(), players[2].save(), players[3].save();
    players[4].save(), players[5].save();
    int i = 0;
    do{
        int card;
        card = playerTurn(players, i, cards, skip, specialSuit, suitSpecial, reverseDir);
        gameOver = endGame(players[i]);
        if(gameOver){
            break;
        }
        if(reverseDir){
            i--;
            if(i == -1){
                i = players.size() -1;
            }
        } else {
            i++;
            if(i == players.size()){
                i = 0;
            }
        }
        cout << flush;
        system("CLS");
    } while(!gameOver);
    
}

//checks if user played last card, If so prints who won and returns true
bool CrazyEight::endGame(player person){
    if(person.playerCards().size() == 0){
        cout << person.namePlayer() << " WINS!!" << endl;
        return true;
    } else {
        return false;
    }
}

//checks which special card was played and returns and number that corresponds the special card played
int CrazyEight::specialCard(int card, bool &skip){
    if(card == 0 || card == 13 || card == 26 || card == 39){
        skip = true;
        return 1;       //Ace
    } else if(card == 11 || card == 24 || card == 37 || card == 50){
        return 2;       //Queen
    } else if(card == 12 || card == 25 || card == 38 || card == 51){
        skip = true;
        return 3;       //King
    } else if(card == 7 || card == 20 || card == 33 || card == 46){
        return 4;       //8's
    } else if(card == 52 || card == 53){
        skip = true;
        return 5;       //Joker
    } else {
        return 0;       //No speacial Card
    }
}

//If user played and eight(wild card) asks user what suit they would like and returns the suit selected
string CrazyEight::eight(){
    int ans1 = 2, ans2 = 0;
    string suit;
    do{
        do{
        cout << "Please Type the number corresponding to the suit you would like" << endl
             << "Spade  : 1" << endl
             << "Hearts : 2" << endl
             << "Club   : 3" << endl
             << "Diamond: 4" << endl;
            cin >> ans2;
        } while(ans2 < 1 || ans2 > 4);
        if(ans2 == 1){
            suit = "Spade";
        } else if(ans2 == 2){
            suit = "Hearts";
        } else if(ans2 == 3){
            suit = "Club";
        } else {
            suit = "Diamond";
        }
        cout << endl;
        cout << "Suit: " << suit << endl;
        cout << "If the suit is correct please type '1' if not type '2'" << endl;
        cin >> ans1; 
    }while(ans1 != 1);
    return suit;
}

//makes the next player draw two cards
void CrazyEight::ace(player &person, deck &cards){
    for(int i = 0; i < 2; i++){
        noDrawPile(cards);      //checks to make sure there are cards to be drawn
        person.drawCard(cards.draw());
    }
    person.save();
    cards.save();
    cout << "You must draw 2 cards\nDue to drawing cards you will be skipped" << endl;
}

//same thing as eight but adds 6 cards to the next player
string CrazyEight::joker(player &person, deck &cards){
    int ans1 = 2, ans2 = 0;
    string suit;
    for(int i = 0; i < 6; i++){
        noDrawPile(cards);
        person.drawCard(cards.draw());
    }
    
    do{
        do{
        cout << "Please Type the number corresponding to the suit you would like" << endl
             << "Spade  : 1" << endl
             << "Hearts : 2" << endl
             << "Club   : 3" << endl
             << "Diamond: 4" << endl;
            cin >> ans2;
        } while(ans2 < 1 || ans2 > 4);
        if(ans2 == 1){
            suit = "Spade";
        } else if(ans2 == 2){
            suit = "Hearts";
        } else if(ans2 == 3){
            suit = "Club";
        } else {
            suit = "Diamond";
        }
        cout << endl;
        cout << "Suit: " << suit << endl;
        cout << "If the suit is correct please type '1' if not type '2'" << endl;
        cin >> ans1; 
    }while(ans1 != 1);
    return suit;
    person.save();
    cards.save();
}

//returns true if direction of play is not reversed of initial direction of play
//causing the direction to be reversed. Returns false if direction is reversed of initial direction of play
//causing it to reverse current direction of play
void CrazyEight::queen(bool &reverseDir){
    if(reverseDir){
        reverseDir = false;
    } else {
        reverseDir = true;
    }
}

//checks if there are no more cards in draw pile
//if there are no cards in draw pile calls function oc cards
void CrazyEight::noDrawPile(deck &cards){
    if(cards.drawCards().size() == 0){
        cards.noDrawCards();
    }
}
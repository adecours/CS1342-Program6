/* File: main.cpp
Author: Abby DeCoursin
Date: 12/9/2019
Description: This program simulates a blackjack game where a user has the ability
to hit with cards or a dice. The player has a balance which is read in from a file
and the balance is updated after every game. In order to win, the player must have 21,
score higher than the dealer, or have the dealer go over 21. The cards are spun up for each hand
and stored in a queue and shuffled. The game history is stored in a stack and is outputted
to the console once the user decides to end the game. The new balance is then stored 
in the balance.txt file.
*/
#include "gamepiece.h"
#include <deque>
#include <queue>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include <iomanip>

using namespace std;

/** Function used to randomize cards, param is an int and so is the return.
 */ 
int myrand(int i) {
    return rand() % i;
}

/** Runs the actual game.
 */ 
int main() {
    stack <string> gameHistory;
    string gameResult;
    double playerBalance = 0;
    int handNumber = 1;
    string userInput;
    ifstream inFile;
    ofstream outFile;

    // opens the balance file, returns an error if fails
    inFile.open("balance.txt");
    if(!inFile.is_open()) {
        cout << "balance.txt could not be opened." << endl;
        return 1;
    }
    inFile >> playerBalance; // reads in balance
    outFile.open("balance.txt");

    cout << "Welcome to Super Blackjack" << endl;
    cout << "Bank Balance: " << playerBalance << endl;
    cout << endl;

    srand(time(0));
    
    // all cards values
    vector<string> allValues;
    allValues.push_back("A");
    allValues.push_back("2");
    allValues.push_back("3");
    allValues.push_back("4");
    allValues.push_back("5");
    allValues.push_back("6");
    allValues.push_back("7");
    allValues.push_back("8");
    allValues.push_back("9");
    allValues.push_back("10");
    allValues.push_back("J");
    allValues.push_back("Q");
    allValues.push_back("K");

    // all card suits
    vector<string> allSuits;
    allSuits.push_back("Hearts");
    allSuits.push_back("Diamonds");
    allSuits.push_back("Spades");
    allSuits.push_back("Clubs"); 

    // loop runs until player decides to quit game
    do {
        int playerScore = 0;
        int dealerScore = 0;
        double betAmount;
        bool playerWon = false;

        vector <Gamepiece*> cards;

        // creates all 52 cards each hand
        for(int i = 0; i < 4; i++) {
            string currSuit = allSuits.at(i);
            for (int k = 0; k < 13; k++) {
                string currValue = allValues.at(k);
                Gamepiece * currCard = new Card(currSuit, currValue);
                cards.push_back(currCard);
            }
        }

        random_shuffle(cards.begin(), cards.end(), myrand); // shuffles cards

        // stores cards in a queue
        queue<Gamepiece*> allCards;
        for (int i = 0; i < cards.size(); i++) {
            allCards.push(cards.at(i));
        }

        cout << "-- HAND " << handNumber << " --" << endl;
        cout << "You have $" << playerBalance << "." << endl;
        cout << endl;
        cout << "How many dollars do you want to bet?" << endl;
        cin >> betAmount;
        cin.clear(); // ignores invalid inputs
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if ((playerBalance - betAmount) < 0) {
            cout << "Invalid bet amount, try again." << endl;
            cin >> betAmount;
        }

        cout << "Dealing cards..." << endl;
        cout << endl;

        // deal two cards for dealer, display one

        Gamepiece * currentCard = allCards.front();
        cout << "Dealer shows: " << endl;
        currentCard->display();
        int cardValue = currentCard->getValue();
        dealerScore += cardValue;
        allCards.pop();

        currentCard = allCards.front();
        cardValue = currentCard->getValue();
        dealerScore += cardValue;
        allCards.pop();
        cout << endl;


        // dealing player two cards
        cout << endl << "Player shows: " << endl;
        currentCard = allCards.front();
        currentCard->display();
        cardValue = currentCard->getValue();
        playerScore += cardValue;
        allCards.pop();
        
        cout << endl;

        currentCard = allCards.front();
        currentCard->display();
        cardValue = currentCard->getValue();
        playerScore += cardValue;
        allCards.pop();
        cout << "Player hand value: " << playerScore << endl;
        cout << endl;

        // handles scenario of blackjack on deal
        if (playerScore == 21 && dealerScore == 21) {
            cout << "Dealer and player have blackjack. Tie." << endl;
            cout << endl;
            
            gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Tie");
            gameHistory.push(gameResult);
            betAmount = 0;
        }
        else if (playerScore == 21) {
            cout << "Player has blackjack." << endl;
            cout << endl;
            playerWon = true;

            gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Player won. Blackjack on deal.");
            gameHistory.push(gameResult);
        }
        else if (dealerScore == 21) {
            cout << "Dealer has blackjack." << endl;
            cout << endl;
            playerWon = false;

            gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Player lost. Blackjack on deal.");
            gameHistory.push(gameResult);
        }

        else {
            string userPlay;
            do { // loop runs while player doesn't want to stay and is under 21
                cout << "Player's turn." << endl;
                cout << "Enter 's' to stay, 'h' to hit, or 'd' to roll dice." << endl;
                cin >> userPlay;

                 if (userPlay != "s") { // error checking
                     if (userPlay != "h") {
                        if (userPlay != "d") {
                            cout << "Invalid input, try again." << endl;
                            cin >> userPlay;
                        }
                     }
                }

                if (userPlay == "h") {
                    cout << "Player chose to hit." << endl;
                    currentCard = allCards.front();
                    currentCard->display();
                    cardValue = currentCard->getValue();
                    playerScore += cardValue;
                    allCards.pop();
                    cout << endl;
                }
                else if (userPlay == "d") {
                    cout << "Player chose to hit with dice." << endl;
                    int diceValue = (rand() % 6 + 1);
                    string newDiceValue = to_string(diceValue);
                    Gamepiece * currDice = new Dice(newDiceValue);
                    diceValue = currDice->getValue();
                    currDice->display();
                    playerScore += diceValue;
                    cout << endl;
                }

            } while (playerScore < 21 && userPlay != "s");

            if (userPlay == "s") {
                cout << "Player chose to stay." << endl;
            }
        }
        
        if (playerScore > 21) { // handles player bust
                    cout << "Player busts." << endl;
                    playerWon = false;
                    cout << endl;
                    gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                        + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Player lost. Player bust.");
                    gameHistory.push(gameResult);
                }
        else { // dealers turn, dealer keeps hitting until over 17
            if (dealerScore < 17) {
                cout << "Dealer's turn." << endl;
            }
            while (dealerScore < 17) {
                currentCard = allCards.front();
                cout << "Dealer draws new card." << endl;
                currentCard->display();
                cardValue = currentCard->getValue();
                dealerScore += cardValue;
                allCards.pop();
                cout << "Dealer score: " << dealerScore << endl;
                cout << endl;
            }
        }

        if (dealerScore == 21) { // dealer blackjack
            cout << "Dealer has blackjack." << endl;
            playerWon = false;
            cout << endl;

            gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Player lost. Dealer has blackjack.");
            gameHistory.push(gameResult);
        }
        else if (dealerScore > 21) { // dealer bust
            cout << "Dealer busts." << endl;
            playerWon = true;
            cout << endl;

            gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Player won. Dealer bust.");
            gameHistory.push(gameResult);
        }
        else {
            if (playerScore == dealerScore) { // tie
                betAmount = 0;
                cout << "Player and dealer tied." << endl;
                cout << endl;
                gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                    + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Tie.");
                gameHistory.push(gameResult);
            }
            else if (playerScore > dealerScore && playerScore < 22) { // player has higher score and didn't bust
                playerWon = true;
                cout << "Player wins. Player score was higher than dealer score." << endl;
                cout << endl;
                gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                    + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Player won. Score above dealer.");
                gameHistory.push(gameResult);
            }
            else if (playerScore < dealerScore) { // dealer has higher score
                playerWon = false;
                cout << "Dealer wins. Player score was less than dealer score." << endl;
                cout << endl;
                gameResult = string("Hand: ") + to_string(handNumber) + string(" Player: ") + to_string(playerScore)
                    + string(" Dealer: ") + to_string(dealerScore) + string(" Result: Player lost. Score below dealer.");
                gameHistory.push(gameResult);
            }
        }

        if (playerWon == false) { // determines loss or gain of money
            playerBalance -= betAmount;
        }
        else if (playerWon == true) {
            playerBalance += betAmount;
        }
        
        cout << "Enter 'c' to continue playing or 'q' to quit: ";
        cin >> userInput;

         if (userInput != "c") { // error checking
            if (userInput != "q") {
            cout << "Invalid input, try again." << endl;
            cin >> userInput;
            }
        } 
        cout << endl;
        handNumber++;

        for (int i = 0; i < 52; i++) { // deallocates memory for vector of cards
            delete cards.at(i);
        }

    } while (userInput == "c"); 

    outFile << playerBalance; // updates player balance in file

    for (int i = 0; i < handNumber - 1; i++) { // displays stack of game history in console
        string currentGame = gameHistory.top();
        cout << currentGame << endl;
        gameHistory.pop();
    } 

    inFile.close(); // close input file
    outFile.close(); // close output file
}
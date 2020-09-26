/* File: gamepiece.cpp
Author: Abby DeCoursin
Date: 12/9/2019
Description: The gamepiece class uses inheritance to create cards and dice. These
 pieces are used within the game to add points to the score of the dealer or of
 the player. The display of the classes is formatted nicely to appear clear. The 
 display function is overloaded in the dice and card class since the pieces appear
 differently.
*/
#include <queue>
#include <string>
#include <iostream>
#include "gamepiece.h"

using namespace std;

/** Displays value of gamepiece, no return.
 */
void Gamepiece::display() {
    cout << "Value: " << value << endl;
}

/** Sets value of gamepiece to newValue, no return.
 */ 
void Gamepiece::setValue(string newValue) {
    value = newValue;
}

/** Returns the integer value of the gamepiece. No param. Converts face cards to ints.
 */ 
int Gamepiece::getValue() {
    int val;
    if (value == "J" || value == "Q" || value == "K") {
        val = 10;
    }
    else if (value == "A") {
        val = 11;
    }
    else {
        val = stoi(value);
    }
    return val;
}

/** Returns the integer value of a card. Converts face cards to ints. No param. 
 */ 
int Card::getValue() {
    int cardVal;
    if (value == "J" || value == "Q" || value == "K") {
        cardVal = 10;
    }
    else if (value == "A") {
        cardVal = 1;
    }
    else {
        cardVal = stoi(value);
    }
    return cardVal;
}

/** Sets the type of the card to newType. No return.
 */ 
void Card::setType(string newType) {
    type = newType;
}

/** Returns a string of the type of card. No param
 */ 
string Card::getType() {
    return type;
}

/** Displays the card value and suit in an organized way. Prints to console, no return.
 * If card type is not valid, an error message is outputted.
 */ 
void Card::display() {
    cout << "+------------+" << endl;
    cout << "| ";
    cout << value;
    if (value != "10") {
        cout << " ";
    }
    cout << "         |" << endl;
    if (type == "Hearts") {
        cout << "|   **  **   |" << endl;
        cout << "|   ******   |" << endl;
        cout << "|   ******   |" << endl;
        cout << "|    ****    |" << endl;
        cout << "|     **     |" << endl;
    }
    else if (type == "Diamonds") {
        cout << "|     **     |" << endl;
        cout << "|    ****    |" << endl;
        cout << "|   ******   |" << endl;
        cout << "|    ****    |" << endl;
        cout << "|     **     |" << endl;
    }
    else if (type == "Spades") {
        cout << "|  ** ** **  |" << endl;
        cout << "|   ******   |" << endl;
        cout << "|    ****    |" << endl;
        cout << "|     **     |" << endl;
        cout << "|    ****    |" << endl;
    }
    else if (type == "Clubs") {
        cout << "|     **     |" << endl;
        cout << "|   ******   |" << endl;
        cout << "|   ******   |" << endl;
        cout << "|     **     |" << endl;
        cout << "|   ******   |" << endl;
    }
    else {
        cout << "BAD SUIT.";
    }

    cout << "|         ";
    if (value != "10") {cout << " "; }
    cout << value;
    cout << " |" << endl;
    cout << "+------------+";
    cout << endl;
}

/** Displays the value of the dice. If value is not valid, an error message is outputted.
 */ 
void Dice::display() {
    cout << "D" << value << endl;

    cout << "+------------+" << endl;
    if (value == "1") {
        cout << "|            |" << endl;
        cout << "|            |" << endl;
        cout << "|     *      |" << endl;
        cout << "|            |" << endl;
        cout << "|            |" << endl;
    }
    else if (value == "2") {
        cout << "|  *         |" << endl;
        cout << "|            |" << endl;
        cout << "|            |" << endl;
        cout << "|            |" << endl;
        cout << "|         *  |" << endl;
    }
    else if (value == "3") {
        cout << "|          * |" << endl;
        cout << "|            |" << endl;
        cout << "|     *      |" << endl;
        cout << "|            |" << endl;
        cout << "| *          |" << endl;
    }
    else if (value == "4") {
        cout << "| *        * |" << endl;
        cout << "|            |" << endl;
        cout << "|            |" << endl;
        cout << "|            |" << endl;
        cout << "| *        * |" << endl;
    }
    else if (value == "5") {
        cout << "| *        * |" << endl;
        cout << "|            |" << endl;
        cout << "|     *      |" << endl;
        cout << "|            |" << endl;
        cout << "| *        * |" << endl;
    }
    else if (value == "6") {
        cout << "| *    *   * |" << endl;
        cout << "|            |" << endl;
        cout << "|            |" << endl;
        cout << "|            |" << endl;
        cout << "| *    *   * |" << endl;
    }
    else {
        cout << "BAD DIE.";
    }
    cout << "+------------+";
    cout << endl;
}

/** Returns the int value of the dice. 
 */ 
int Dice::getValue() {
    int diceValue = stoi(value);
    return diceValue;
}
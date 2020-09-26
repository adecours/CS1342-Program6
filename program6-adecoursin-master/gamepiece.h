/* File: gamepiece.h
Author: Abby DeCoursin
Date: 12/9/2019
Description: The gamepiece class is the base class in which the card and dice classes
 are derived from. They each have getters and setters and use a display function to
 output the value. The display function is virtual since the implementation is different
 for each class, utilizing polymorphism.
*/
#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include <string>
#include <iostream>

using namespace std;

class Gamepiece {
    public:
        Gamepiece(string myValue) {value = myValue;}
        void setValue(string newValue);
        int getValue();
        virtual void display();
    protected:
        string value;

};

class Card : public Gamepiece {
    public:
        Card(string myType, string myValue) : Gamepiece(myValue) {type = myType;}
        void setType(string newType);
        string getType();
        int getValue();
        void display();
    private:
        string type;
};

class Dice : public Gamepiece {
    public:
        Dice(string myValue) : Gamepiece(myValue) {}
        void display();
        int getValue();
};

#endif
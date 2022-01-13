//
// Created by EA on 15.11.2020.
//

#ifndef UNTITLED2_ARRAYCLASS_H
#define UNTITLED2_ARRAYCLASS_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ArrayClass {
public:
    ArrayClass();
    static string deck[13][25];
    static int openCards[13][25];
    static void win();
    static void exitFunction();
    static void firstOpenCard();
    static void movePile(int a, int b, int c);
    static void openStock();
    static void openCardPile(int row);
    static void moveToFoundationPile(int n);
    static void moveWaste(int row);
    static void moveToFoundationWaste();
    static void moveFoundation(int a , int b);
    static int getNullCard(int n);
    static int pileException(string a, string b);
    static void foundation(string s);
    static int findWaste();
    static int foundationException(string s);
    static int stock_row;
    static int yeth;
    static int foundation_one;
    static int foundation_two;
    static int foundation_three;
    static int foundation_four;
    static string message;
    static int empt;


};
#endif


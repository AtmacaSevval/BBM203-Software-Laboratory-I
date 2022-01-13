//
// Created by EA on 9.11.2020.
//

#ifndef UNTITLED2_READINGCLASS_H
#define UNTITLED2_READINGCLASS_H
#include <string>
using namespace std;

class ReadingClass {
public:
    static char deck[50];
    static char commands[50];
    static char output[50];

    void readDeck();
    void readCommands();
    void callMethods(string command[],int y);
};


#endif //UNTITLED2_CLASS2_H



//
// Created by EA on 30.11.2020.
//

#ifndef NEWASSIGNMENT2_COMMANDREADING_H
#define NEWASSIGNMENT2_COMMANDREADING_H

#include <string>

using namespace std;
class CommandReading {
public:
    static char commands[50];
    void reading();
    void callMethods(string commandarr[],int lenght);
    void print(string prev, string s);
    string printMethod(string com);
};


#endif //NEWASSIGNMENT2_COMMANDREADING_H

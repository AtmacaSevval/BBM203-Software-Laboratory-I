
#ifndef ASSIGNMENT4_READING_H
#define ASSIGNMENT4_READING_H

#include <string>
#include "Tree.h"

using namespace std;


class Reading {
public:

    Tree treeObj;

    string read(string file,string fileName);// to read a file and save a string

    void callEncode(string filename);
    void callCharacter(string ch);
    void callDecode(string filename);
};


#endif

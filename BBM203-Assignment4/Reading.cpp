
#include "Reading.h"

#include <string>
#include<bits/stdc++.h>

using namespace std;


string Reading::read(string file,string fileName){
    string myText;
    string line;
    ifstream myfile;
    myfile.open(fileName.c_str());

    if (!myfile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while (getline(myfile, line)) {
        file += line;
    }
    return file;//to save a file to a string
}


void Reading::callEncode(string filename){//to "-i input_1.txt -encode"
    string file;
    file = read(file, filename);
    transform(file.begin(), file.end(), file.begin(), ::tolower);
    treeObj.initialFreq(file);
    treeObj.encodeString(file);
}

void Reading::callCharacter(string character) {//to "-s character"

    treeObj.character(character);
}


void Reading::callDecode(string filename) {//to "-i decode_input_1.txt -decode"

    string fileDecode;
    fileDecode = read(fileDecode, filename);
    transform(fileDecode.begin(), fileDecode.end(), fileDecode.begin(), ::tolower);
    treeObj.decode(fileDecode);
}



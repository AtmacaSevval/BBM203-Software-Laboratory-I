//
// Created by EA on 9.11.2020.
//
#include <iostream>
#include <string>
#include "ReadingClass.h"
#include "ArrayClass.h"
#include "OutputFile.h"

#include <cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include <sstream>

using namespace std;

char ReadingClass::deck[50];//first argument
char ReadingClass::commands[50];//second argument
char ReadingClass::output[50];//third argument

void ReadingClass::readDeck() {
    string deckold[52];
    string x;

    ifstream inFile;
    int cnt= 0;
    inFile.open(ReadingClass::deck);
    if (!inFile) {

    }
    while (inFile >> x) {//save deckold[] to txt
        deckold[cnt] = x;
        cnt++;
    }

    for (int i = 24; i < 38; i++) {
        string asd = deckold[i];
        deckold[i] = deckold[75 - i];
        deckold[75 - i] = asd;
    }
    for(int i = 0;i < 13; i++) {
        for (int j = 0; j < 25; j++) {
            ArrayClass::deck[i][j] = "null";
        }
    }
    //I converted 2D array.
    int z = 24;
    int d = 1;
    for(int i = 0;i < 13; i++){
        if(i == 0) {
            for (int j = 0; j < 25; j++) {

                if(j < 24){
                    ArrayClass::deck[i][j] = deckold[j];
                }
                else{
                    ArrayClass::deck[i][j] = "null";
                }
            }

        }
        else if(i>0 && i<6){
            for (int j = 0; j < 25; j++) {
                ArrayClass::deck[i][j] = "null";
            }
        }


        else{
            int inx = 1;
            int x = 1;
            int u = 6;
            ArrayClass::deck[i][0] = deckold[z];
            int o = z;
            z++;
            while (d > x) {
                ArrayClass::deck[i][inx] = deckold[o + u];
                o+=u;
                u--;
                x++;
                inx++;
            }
            d++;
        }
    }

}


void ReadingClass::readCommands(){
    int i2 = 0;
    string myText2;
    string line2;
    ifstream myfile2;
    myfile2.open(ReadingClass::commands);

    if(!myfile2.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while(getline(myfile2, line2)) {
        i2++;
    }

    string command[i2];
    int i3=0;

    string myText3;
    string line3;
    ifstream myfile3;
    myfile3.open(ReadingClass::commands);

    if(!myfile3.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while(getline(myfile3, line3)) {
        command[i3]=line3;//command array
        i3++;
    }
    callMethods(command , i3);
}



void ReadingClass::callMethods(string command[], int y){
    std::ofstream outfile;
    outfile.open(ReadingClass::output, std::ios_base::app);

    ArrayClass::firstOpenCard();
    OutputFile ou;
    ou.createFile();
    ou.first();//I printed the first version of the array
    string com;

    for(int i = 0; i<y; i++){//call methods
        com = command[i];


        ArrayClass::win();
        outfile<<com<<endl<<endl;

        if(com.find("open from stock") != std::string::npos){
            ArrayClass::openStock();
            ou.print();


        }
        else if(com.find("move to foundation waste") == 0) {
            ArrayClass::moveToFoundationWaste();
            ou.print();

        }
        else if(com.find("open") != std::string::npos) {
            string suba = com.substr( 5);
            int value_a = atoi(suba.c_str());//pile num
            ArrayClass::openCardPile(value_a);
            ou.print();

        }
        else if(com.find("move waste") == 0) {
            string suba = com.substr( 11);
            int value_a = atoi(suba.c_str());//waste num
            ArrayClass::moveWaste(value_a);
            ou.print();

        }
        else if(com.find("move to foundation pile") != std::string::npos) {
            string suba = com.substr( 24);
            int value_a = atoi(suba.c_str());//pile num
            ArrayClass::moveToFoundationPile(value_a);

            ou.print();

        }
        else if(com.find("move pile") != std::string::npos) {
            std::istringstream iss(com);

            std::string s,s1;
            int a, b, c;//old row,num,new row

            iss >> s >>s1 >> a >> b >> c;

            ArrayClass::movePile(a , b, c);
            ou.print();
        }

        else if(com.find("move foundation") != std::string::npos){
            char sr1 = com[16];
            char sr2 = com[18];

            int ia = sr1 - '0';//num1
            int ib = sr2 - '0';//num2
            ArrayClass::moveFoundation(ia, ib);
            ou.print();
        }

        else if(com.find("exit") != std::string::npos){// to break program
            ArrayClass::exitFunction();

        }

    }
    ArrayClass::win();
}


















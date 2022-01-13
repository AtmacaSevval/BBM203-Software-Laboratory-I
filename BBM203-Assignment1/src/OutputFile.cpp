//
// Created by EA on 12.11.2020.
//
#include "OutputFile.h"
#include "ArrayClass.h"
#include "ReadingClass.h"

#include <iostream>
#include <string>
using namespace std;


int OutputFile::column() {//take the which maximum element in the index to To understand how many lines I should printed
    int arr[7];
    int zero = ArrayClass::getNullCard(0);
    int one = ArrayClass::getNullCard(1);
    int two = ArrayClass::getNullCard(2);
    int three = ArrayClass::getNullCard(3);
    int four = ArrayClass::getNullCard(4);
    int five = ArrayClass::getNullCard(5);
    int six = ArrayClass::getNullCard(6);;
    arr[0] = zero; arr[1] = one; arr[2] = two; arr[3] = three; arr[4]=four;arr[5] = five, arr[6] = six;

    int max = arr[0];

    for (int i = 1; i < 7; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}


void OutputFile::first(){//first print before commands
    std::ofstream outfile;
    outfile.open(ReadingClass::output, std::ios_base::app);
    outfile<<endl;
    outfile<< "@@@ ___ ___ ___         ___ ___ ___ ___"<<endl<<endl;

    for(int i = 0;i < sizeof (ArrayClass::deck) / sizeof (ArrayClass::deck[0]); i++){
        int x = 6;
        while(x < 13) {
            if (ArrayClass::deck[x][i] == "null") {
                outfile<< "      ";
            }
            else {
                if(ArrayClass::openCards[x][i] == 1){
                    outfile << ArrayClass::deck[x][i];
                    outfile<< "   ";
                }
                else if(ArrayClass::openCards[x][i] == 0){
                    outfile<< "@@@   ";
                }
            }
            x++;
        }
        outfile <<endl;
    }

}
void OutputFile::createFile() {//crate output txt
    ofstream MyFile(ReadingClass::output);
    MyFile.close();
}


void OutputFile::print() {
    std::ofstream outfile;
    outfile.open(ReadingClass::output, std::ios_base::app); // append instead of overwrite

    outfile << ArrayClass::message;//print error message
    if(ArrayClass::message != ""){
        outfile<<endl<<endl;
    }
    ArrayClass::message = "";
    string star = "****************************************";
    outfile<<star<<endl<<endl;


    if(ArrayClass::stock_row == 25 ){//if there is no card
        outfile <<"@@@ ___ ___ ___";
    }
    else {
        if(ArrayClass::stock_row == 24 || ArrayClass::stock_row == -1 || ArrayClass::empt == 101){
            outfile << "___";
        }
        else if(ArrayClass::empt == 102){
            outfile << "@@@";

        }
        else {
            outfile << "@@@";
        }

        for (int i = 0; 3 > i; i++) {//print waste
            if (ArrayClass::deck[1][i] != "null") {
                outfile<< " " + ArrayClass::deck[1][i];
            } else {
                outfile<< " ___";
            }


        }
    }
    outfile<< "         ";

    if(ArrayClass::openCards[2][ArrayClass::foundation_one - 1] == 1){//the last card in the foundation
        outfile << ArrayClass::deck[2][ArrayClass::foundation_one - 1] + " ";
    }
    else{
        outfile<<"___ ";


    }

    if(ArrayClass::openCards[3][ArrayClass::foundation_two - 1] == 1){
        outfile << ArrayClass::deck[3][ArrayClass::foundation_two - 1] ;
        outfile<<" ";

    }
    else{
        outfile<<"___ ";

    }
    if(ArrayClass::openCards[4][ArrayClass::foundation_three - 1] == 1){
        outfile << ArrayClass::deck[4][ArrayClass::foundation_three - 1] + " ";

    }
    else{
        outfile<<"___ ";

    }
    if(ArrayClass::openCards[5][ArrayClass::foundation_four - 1] == 1){
        outfile << ArrayClass::deck[5][ArrayClass::foundation_four - 1] + " ";

    }
    else{
        outfile<<"___ ";
    }

    outfile<<endl<<endl;
    int col = column();

    for(int i = 0;i < col+2; i++){
        int x = 6;
        while(x < 13) {
            if (ArrayClass::deck[x][i] == "null") {//if it is null dont write
                outfile<< "      ";
            }
            else {
                if(ArrayClass::openCards[x][i] == 1){//if it is card is open the show the card name
                    outfile << ArrayClass::deck[x][i];
                    outfile<< "   ";
                }
                else if(ArrayClass::openCards[x][i] == 0){// else dont show the name
                    outfile<< "@@@   ";
                }
            }
            x++;
        }
        outfile <<endl;
    }

    outfile.close();

}

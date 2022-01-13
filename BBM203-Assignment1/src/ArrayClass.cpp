//
// Created by EA on 8.11.2020.
//

#include "ArrayClass.h"
#include "ReadingClass.h"
using namespace std;

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>


string ArrayClass::deck[13][25];
int ArrayClass::openCards[13][25];
int ArrayClass::stock_row = 23;
int ArrayClass::yeth = 23;
int ArrayClass::foundation_one = 0;
int ArrayClass::foundation_two = 0;
int ArrayClass::foundation_three = 0;
int ArrayClass::foundation_four = 0;
string ArrayClass::message;
int ArrayClass::empt = 100;


ArrayClass::ArrayClass() {

}


int ArrayClass::findWaste(){//find in the waste, index of last card
    int index = 25;
    for(int i = 24; i > -1 ;i--){
        index--;
        if(deck[1][i] != "null"){
            break;
        }
    }
    return index;
};

void ArrayClass::openStock(){
    int index = 0;
    for(int i = 24; i > -1 ;i--){
        if(deck[1][i] != "null"){
            index++;
        }
    }

    if(index != 0) {// if index is not zero there is cards in waste which in still , so I have to these cards take stock

        int i = 0;
        int a = yeth;
        while (index > i) {
            deck[0][a] = deck[1][i];
            deck[1][i] = "null";
            a--;
            i++;
        }

    }
    int how = 0;
    for(int a = stock_row; a > -1;a--){
        if(deck[0][a] != "null"){
            how++;
        }
    }
    if(how == 0){// if it is zero there is no card to open then I have to update index s0,I get the beginning
        int index = 25;
        for(int i = 24; i > -1 ;i--){
            index--;
            if(deck[0][i] != "null"){
                break;
            }

        }
        stock_row = index;
        empt = 102;
        return;
    }

    yeth = stock_row;


    int x = 0;
    int d = 0;
    for(int i = stock_row; i > -1; i--){//take most 3 cards in stock index

        string s =  deck[0][i];
        if (deck[0][i] != "null") {
            d++;
            deck[0][i] = "null";
            deck[1][x] = s;
            x++;
        }
        if(x==3){
            break;
        }
    }
    stock_row -= d ;

    empt = 100;
    for(int a = stock_row; a > -1;a--){
        if(deck[0][a] != "null"){
            empt++;
        }
    }
    empt++;

}




void ArrayClass::foundation(string s) {//to put a new card foundation
    int a;
    if (s.rfind("H", 0) == 0) {
        a = 2;
        deck[2][foundation_one] = s;
        openCards[2][foundation_one] = 1;
        foundation_one++;// I updated for new null card index
    } else if (s.rfind("D", 0) == 0) {
        a = 3;
        deck[3][foundation_two] = s;
        openCards[3][foundation_two] = 1;
        foundation_two++;
    } else if (s.rfind("S", 0) == 0) {
        a = 4;
        deck[4][foundation_three] = s;
        openCards[4][foundation_three] = 1;
        foundation_three++;
    } else if (s.rfind("C", 0) == 0) {
        a = 5;
        deck[5][foundation_four] = s;
        openCards[5][foundation_four] = 1;
        foundation_four++;
    }
}


int ArrayClass::foundationException(string s){//exception
    string suba = s.substr( 1);
    string subb = s.substr(0,1);

    if(subb == "H"){
        if(foundation_one == 0 && s == "H01")//if foundations are null it have to start "01"
            return 1;
    }
    if(subb == "D"){
        if(foundation_two == 0 && s == "D01")
            return 1;
    }
    if(subb == "S"){
        if(foundation_three == 0 && s == "S01")
            return 1;
    }
    if(subb == "C"){
        if(foundation_four == 0 && s == "C01")
            return 1;
    }
    int value_a = atoi(suba.c_str());
    value_a--;


    ostringstream str1;
    str1 << value_a;
    string str = str1.str();
    if(str.size() == 1){
        str = "0" + str;
    }
    subb += str;//new card must be 1 greater than the previous card like if new card end like"02" previous card must be"01"
    if(subb == deck[2][foundation_one - 1]){
        return 1;
    }
    else if(subb==deck[3][foundation_two - 1]){
        return 1;
    }
    else if(subb == deck[4][foundation_three - 1]){
        return 1;
    }
    else if(subb == deck[5][foundation_four - 1]){
        return 1;
    }
    else{
        return 0;
    }
}
void ArrayClass::moveToFoundationPile(int n){
    int lastcard = getNullCard(n);
    lastcard -= 1;
    string s = deck[n+6][lastcard];//the last opened card in the pile
    if(foundationException(s) == 0){
        message = "Invalid Move!";
        return;
    }

    deck[n+6][lastcard] = "null";//I gave "null" because I put somewhere different
    openCards[n+6][lastcard] = 0;
    foundation(s);
}



void ArrayClass::moveToFoundationWaste() {
    int in = findWaste();//take last card in waste
    string s = deck[1][in];
    if(foundationException(s) == 0){//if is zero invalid
        message = "Invalid Move!";
        return;
    }
    deck[1][in] = "null";//I gave "null" because I put somewhere different
    foundation(s);
}




int ArrayClass::pileException(string a , string b){//pileexception : cards which to put in the pile
    string suba = a.substr(1);
    string subb = b.substr(1);
    int value_a = atoi(suba.c_str());// new card must be same type previous card and there is 1 missing than previous like "01" and "02"
    int value_b = atoi(subb.c_str());

    string kind1 = a.substr(0, 1);
    string kind2 = b.substr(0, 1);

    int re;//if there is not true you cannot put here
    if( (value_a + 1 == value_b)&& ((kind1 == "H" ||kind1 == "D") && (kind2 == "S" || kind2 =="C")) || ((kind2 == "H" ||kind2 == "D") && (kind1 == "S" || kind1 == "C"))){
        re = 1;
    }
    else{
        re = 0;
    }
    return re;
}

void ArrayClass::moveWaste(int row) {

    int changingcard = findWaste();
    string newCard = deck[1][changingcard];// the last card in the waste

    int nullIndex = getNullCard(row);
    string a = deck[row + 6][nullIndex - 1];// the last card in the row

    string suba = newCard.substr( 1);
    int value_a = atoi(suba.c_str());

    int re = pileException(newCard,a);

    if(nullIndex == 0 && value_a != 13){
        message = "Invalid move!";
        return;

    }
    else if(nullIndex == 0 && value_a == 13){// if pile is empty you can use the card like ending "13"

    }
    else if(re == 0){
        message = "Invalid move!";
        return;

    }
    deck[1][changingcard] = "null";// I change as a "null" because ı put them somewhere different
    deck[1][changingcard] = "null";
    deck[row + 6][nullIndex] = newCard;//I added new card to pile
    openCards[row + 6][nullIndex] = 1;// the card is open
}

void ArrayClass::moveFoundation(int a, int b){
    int index;
    if(a == 0){// take null index in foundations
        index = foundation_one;
    }
    else if(a == 1){
        index = foundation_two;
    }
    else if(a == 2){
        index = foundation_three;
    }
    else{
        index = foundation_four;
    }

    string s = deck[a+2][index - 1];// take the card in the foundation
    int t = getNullCard(b);
    string c =  deck[b+6][t - 1];
    int re = pileException(c,s);
    if(re == 0){
        message = "Invalid Move!";
        return;
    }
    deck[b+6][t] = s;// I put new card
    openCards[b+6][t] = 1;
    openCards[a + 2][index - 1] = 0;//I remove the card
    deck[a + 2][index - 1] = "null";
}

void ArrayClass::openCardPile(int row){
    int lastcard = getNullCard(row);
    lastcard -= 1;// the index of last card in the pile
    if(openCards[row+6][lastcard] == 1){// if it is olready opened is error
        message = "Invalid Move!";
        return;
    }
    else {
        openCards[row + 6][lastcard] = 1;//else i opened the card
    }
}

void ArrayClass::movePile(int oldrow, int z, int newrow) {
    int nullindexofold = getNullCard(oldrow);
    int nullindexofnew = getNullCard(newrow);

    nullindexofold -= 1;
    nullindexofnew -= 1;

    string a = deck[oldrow + 6][nullindexofold - z];
    string b = deck[newrow + 6][nullindexofnew];



    int re = pileException(a,b);

    string suba = a.substr(1);
    int value_a = atoi(suba.c_str());
    if(b=="null" && value_a == 13){//if the pile is empty and the card is ending with"13" you can put here.

    }    else if(re == 0 || (openCards[oldrow + 6][nullindexofold - z]==0) || (openCards[newrow + 6][nullindexofnew]==0) ){
        message = "Invalid Move!";
        return;
    }

    int newad = 1;
    for(int i = z ; i > -1; i--){// I added cards and remove other cards I make them visible
        string str = deck[oldrow+6][nullindexofold - i] ;
        deck[oldrow+6][nullindexofold - i] = "null";
        openCards[oldrow+6][nullindexofold - i] = 0;
        deck[newrow+6][nullindexofnew + newad] = str;
        openCards[newrow+6][nullindexofnew + newad] = 1;
        newad++;
    }
}


int ArrayClass::getNullCard(int row){
    int a;//get null card index of the pile
    int index = 0;
    for(int i = 0;i <sizeof (deck[0]) / sizeof (string); i++){
        string str = deck[row+6][i];
        if(str.compare("null") == 0){
            break;
        }
        index++;
    }
    a = index;
    return a;// return index
}


void ArrayClass::firstOpenCard(){// first version about the card is visible or not
    for(int i = 0;i < sizeof (deck) / sizeof (deck[0]); i++){
        if(i < 6){
            for (int j = 0; j < sizeof (deck[0]) / sizeof (string); j++) {
                openCards[i][j] = 0;
            }
        }

        else if(i >= 6){
            for (int j = 0; j < sizeof (deck[0]) / sizeof (string); j++) {
                if(j == getNullCard(i - 6) - 1)
                    openCards[i][j] = 1;
                else
                    openCards[i][j] = 0;
            }
        }
    }
}

void ArrayClass::win() {// if foundations have 13 cards then win
    if(foundation_one == 13 && foundation_two == 13 && foundation_three == 13 && foundation_four== 13){
        std::ofstream outfile;
        outfile.open(ReadingClass::output, std::ios_base::app); // append instead of overwrite

        outfile<<"****************************************"<<endl<<endl<<"You Win!"<<endl<<endl<<"Game Over!";
        outfile<<endl;
        outfile.close();
        exit(0);
    }
}

void ArrayClass::exitFunction(){//exit the program
    std::ofstream outfile;
    outfile.open(ReadingClass::output, std::ios_base::app);
    outfile<<"****************************************"<<endl<<endl<<"Game Over!";
    outfile<<" ";
    outfile.close();
    exit(20);

}






#ifndef NEWASSIGNMENT3_READING_H
#define NEWASSIGNMENT3_READING_H
#include "Truck.h"
#include <string>
#include <vector>

using namespace std;

class Reading {
public:
    Truck obj1;
    static char desks[50];//desk.txt
    static char packages[50];//packages.txt
    static char trucks[50];//trucks.txt
    static char missions[50];//missions.txt
    static char results[50];//output.txt

    //find the line number of a file
    int FindLineCount(string fileName);

    //read one file
    void readAFile(string fileName, string arrFile[]);

    //I read all txts in this method
    void ReadAllFile();

    //calling methods in Truck or Package class
    void calling(string arrMission[], int sizeMission, string arrDesk[] , int sizeDesk );

    // Split a string by its token(',' , '-' etc.)
    vector<string> split(char token, string s);

    //Convert a string vector to int vector
    vector<int> convert(vector<string> vect);
};


#endif //NEWASSIGNMENT3_READING_H

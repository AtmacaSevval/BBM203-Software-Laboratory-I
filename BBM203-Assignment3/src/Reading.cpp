


#include "Reading.h"
#include <cstdlib>
#include <stdio.h>

using namespace std;
char Reading::desks[50];
char Reading::packages[50];
char Reading::trucks[50];
char Reading::missions[50];
char Reading::results[50];
Truck obj1;//Truck obj

int Reading::FindLineCount(string fileName){//line number of txt
    int linecount = 0;

    string myText;
    string line;
    ifstream myfile;
    myfile.open(fileName);

    if (!myfile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while (getline(myfile, line)) {
        linecount++;
    }
    return linecount;
}

// Save a file into an array
void Reading::readAFile(string fileName, string arrFile[]){
    string myText2;
    string line2;
    ifstream myfile2;
    myfile2.open(fileName);

    if (!myfile2.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (getline(myfile2, line2)) {
        arrFile[i] = line2;//command array
        i++;
    }
}

//Find line number of all input files and save information in arrays
void Reading::ReadAllFile(){
    int lineDesk = FindLineCount(desks);
    string deskArr[lineDesk];
    readAFile(desks,deskArr);

    int linePackage = FindLineCount(packages);
    string PackagesArr[linePackage];
    readAFile(packages,PackagesArr);

    int lineTruck = FindLineCount(trucks);
    string TruckArr[lineTruck];
    readAFile(trucks,TruckArr);

    int lineMissions = FindLineCount(missions);
    string MissionsArr[lineMissions];
    readAFile(missions,MissionsArr);

    obj1.initialPackages(deskArr , lineDesk, PackagesArr, linePackage);//Take initial packages in station in Package class
    obj1.initialTruck(deskArr, lineDesk, TruckArr, lineTruck);//Take initial trucks in station in Truck class
    calling(MissionsArr, lineMissions,deskArr, lineDesk);
}

//Call methods in Truck or Packages according to missions
void Reading::calling(string arrMission[], int sizeMission, string arrDesk[] , int sizeDesk ) {

    string com;
        for (int z = 0; z < sizeMission; z++) {
            com = arrMission[z];

            vector<string> v1;// I seperated word by word with using vector
            v1 = split('-', com);// A-B-C-x-y

            string ar = v1[5];
            vector<string> v2;// I seperated word by word with using vector
            v2 =split(',',ar);// v2 vector is for z's  //z1,z2


            for (int k = 0; k < sizeDesk; k++) {//first station

                if (v1[0] == arrDesk[k]) {//find index of first station in the desk
                    stringstream out(v1[3]);
                    int count = 0;
                    out >> count;

                    obj1.takeTruckFromFirstStation(k);//take a truck in the station
                    obj1.deletePackageFromStation(k, count);//take packages by ordered number packages
                }
            }

            for (int k1 = 0; k1 < sizeDesk; k1++) {//middle station
                if (v1[1] == arrDesk[k1]) {

                    stringstream out(v1[4]);
                    int count1 = 0;
                    out >> count1;
                    obj1.deletePackageFromStation(k1, count1);//take packages by ordered number packages

                    vector<int> output;//save index of packages in vector v2
                    output = convert(v2);//convert index to int
                    obj1.addPackagesMiddleStation(output, k1);
                    /*take packages in the trucks by ordered index
                     add in the middle station */
                }
            }


            for (int k = 0; k < sizeDesk; k++) {//last station
                if (v1[2] == arrDesk[k]) {
                    obj1.leaveTruckToLastStation(k);//add truck in last station
                    obj1.addAllPackageToLastStation(k);
                }
            }

            v2.clear();
            v1.clear();
        }

    for (int k = 0; k < sizeDesk; k++) {
        obj1.output(arrDesk[k], k);
    }
}

vector<string> Reading::split(char token, string s) {
    vector<string>result;
    string temp = "";

    for (int i = 0; i < s.length(); ++i) {

        if (s[i] == token) {//to not save tab character as a vector element
            result.push_back(temp);
            temp = "";
        } else {
            temp.push_back(s[i]);
        }

    }
    result.push_back(temp);
    return result;//return new vector
}

//convert string vector to int
vector<int> Reading::convert(vector<string> vect) {
    vector<int> output;
    for (auto &s : vect) {
        std::stringstream parser(s);
        int x = 0;

        parser >> x;

        output.push_back(x);
    }
    return output;
}
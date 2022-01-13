//
// Created by EA on 9.12.2020.
//

#ifndef NEWASSIGNMENT3_PACKAGES_H
#define NEWASSIGNMENT3_PACKAGES_H

#include "Stack.h"
#include "Queue.h"

#include <vector>
#include <array>
#include <sstream>
#include <iostream>

using namespace std;

class Packages {
public:
    int stackSize;//stack object for each station ordered by desk file
    Stack<string> *s;


    //adding initial packages in their stations
    void initialPackages(string arrDesk[] , int sizeDesk, string arrPackage[] , int sizePackage);

    // add items in double linked list
    void addItemToTruck(const string &newItem);

    //deleting packages in the station by ordered number
    void deletePackageFromStation(int index, int count);

    //to add packages in the middle station
    void addPackagesMiddleStation(vector<int> vect, int k);

    //find items in double linked list by their index
    string findByIndex(const int &index);

    //delete an item by their data(package name)
    void popByName(const string &name);

    //add all packages in the truck to last station
    void addAllPackageToLastStation(int index);


    struct Node {
        string data;
        struct Node* next; // Pointer to next node in DLL
        struct Node* prev; // Pointer to previous node in DLL
    };
    Node *_headDouble = NULL;
    Node *_tailDouble = NULL;
    int doubleSize;

};


#endif //NEWASSIGNMENT3_PACKAGES_H


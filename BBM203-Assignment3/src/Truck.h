
#ifndef NEWASSIGNMENT3_TRUCK_H
#define NEWASSIGNMENT3_TRUCK_H

#include "Packages.h"
#include <iostream>
using namespace std;

class Truck : public Packages{
public:
    //Queue size
    int queueSize;
    Queue<string> *q;//Queue objects for each station

    //Adding initial trucks in their stations
    void initialTruck(string arr[] , int size, string arr1[] , int size1);

    //Take a truck in station
    void takeTruckFromFirstStation(int index);

    //add truck in the last station
    void leaveTruckToLastStation(int index);

    //to write in txt as an output
    void output(string city, int index);
};



#endif //NEWASSIGNMENT3_TRUCK_H
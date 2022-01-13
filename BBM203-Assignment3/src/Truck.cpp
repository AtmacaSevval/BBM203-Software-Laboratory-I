

#include "Truck.h"
#include "Reading.h"
#include <fstream>


void Truck::initialTruck(string arrDesk[] , int sizeDesk, string arrTruck[] , int sizeTruck){
    queueSize = sizeDesk;
    q = new Queue<string>[sizeDesk];//create queue object by desk size for each city

    string com;
    string com1;

    for(int z = 0; z<sizeDesk; z++){//save all trucks in their stations
        com = arrDesk[z];
        for(int i = 0; i<sizeTruck; i++){
            com1 = arrTruck[i];

            std::istringstream iss(com1);
            std::string truck,city,power;
            iss >>truck >> city >> power;//split

            if(city == com){
                q[z].enqueue(truck + " " + power);//add trucks

            }
        }
    }
}


void Truck::takeTruckFromFirstStation(int index){
    string top;
    q[index].getFront(top);//take top truck
    addItemToTruck(top);//add the truck in double linked list
    q[index].dequeue();//and delete truck in the first station
}



void Truck::leaveTruckToLastStation(int index) {

    struct Node* temp;
    temp=_headDouble;//truck was in head
    q[index].enqueue(_headDouble->data);//add truck in the last station
    _headDouble=_headDouble->next;//change the head
    _headDouble->prev=NULL;
    free(temp);//delete truck in DLL

}

//OUTput
void Truck::output(string city, int index){
    string ou;
    std::ofstream outputFile;
    outputFile.open(Reading::results, std::ios_base::app);

    outputFile<<city<<endl;
    outputFile<<"Packages:"<<endl;
    ou = s[index].display();
    outputFile<<ou;
    outputFile<<"Trucks:"<<endl;
    ou = q[index].display();
    outputFile<<ou;
    outputFile<<"-------------"<<endl;

    outputFile.close();
}
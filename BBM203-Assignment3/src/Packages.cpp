#include "Packages.h"

void Packages::initialPackages(string arrDesk[] , int sizeDesk, string arrPackage[] , int sizePackage){
    s = new Stack<string>[sizeDesk];//create stack object by desk size for each city
    stackSize = sizeDesk;
    
    string com;
    string com1;

    for(int z = 0; z<sizeDesk; z++){//save all packages in their stations
        com = arrDesk[z];

        for(int i = 0; i<sizePackage; i++){
            com1 = arrPackage[i];

            std::istringstream iss(com1);
            std::string package,city;
            iss >>package >> city;//split string

            if(city == com){
                s[z].push(package);//add packages
            }
        }
    }
}

// add items in double linked list
void Packages::addItemToTruck(const string &newItem){
    Node* ptr = new Node();
    ptr->data=newItem;

    if(_headDouble==NULL)
    {
        _headDouble=ptr;
        ptr->prev=NULL;
        ptr->next=NULL;
        _tailDouble=ptr;
    }
    else
    {
        ptr->prev=_tailDouble;
        _tailDouble->next=ptr;
        ptr->next=NULL;
        _tailDouble=ptr;
    }

    doubleSize++;
}


void Packages::deletePackageFromStation(int index, int count){

    string top;
    while(count!= 0){
        s[index].getTop(top);//take top package and save in top
        s[index].pop();
        addItemToTruck(top);//and add in the truck
        count--;
    }
}



void Packages::addAllPackageToLastStation(int index) {
    struct Node* temp;

    while(_headDouble != NULL) {//begin the head add all packages in station and delete in the DLL
        temp = _headDouble;
        string dt = temp->data;
        s[index].push(dt);
        _headDouble = _headDouble->next;
        free(temp);
    }

}

//delete pacckages by their data
void Packages::popByName(const string &name){
    doubleSize--;

    struct Node* temp;
    temp=_headDouble;

    if(_headDouble == _tailDouble)
    {
        if(_headDouble->data!=name)
        {
            cout<<"could not delete"<<endl;
            return;
        }
        _headDouble=NULL;
        _tailDouble=NULL;
        free(temp);
        return;
    }

    if(_headDouble->data==name)
    {
        _headDouble=_headDouble->next;
        _headDouble->prev=NULL;
        free(temp);
        return;
    }

    else if(_tailDouble->data==name)
    {
        temp=_tailDouble;
        _tailDouble=_tailDouble->prev;
        _tailDouble->next=NULL;
        free(temp);
        return;
    }

    while(temp->data!=name)
    {
        temp=temp->next;
        if(temp==NULL)
        {
            cout<<"element not found"<<endl;
            return;
        }
    }
    temp->next->prev=temp->prev;
    temp->prev->next=temp->next;
    free(temp);

}

//find items by their index return their data
string Packages::findByIndex(const int &index) {
    int in = index;
    Node* src = _headDouble;

    // Traverse node till pos
    while (in != -1) {
        src = src->next;
        in--;
    }

    string item = src->data;
    return item;
}

void Packages::addPackagesMiddleStation(vector<int> vect,int k) {
    vector<string> output;//to save elements which deletes in truck
    int in;
    string z;
    for (int i = 0; i < vect.size(); i++){// find elements in trucks by their index and save them in vector
        in = vect.at(i);
        z = findByIndex(in);
        output.push_back(z);
    }

    for (int i = 0; i < output.size(); i++){
        s[k].push(output.at(i));//add this packages in middle station
        popByName(output.at(i));// and delete in the truck
    }
}


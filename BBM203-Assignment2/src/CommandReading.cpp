
#include "CommandReading.h"
#include "LibrarySystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include<vector>
#include <cstdlib>
#include <stdio.h>
using namespace std;

char CommandReading::commands[50];

void CommandReading::reading() {
    int count = 0;//to save size of array

    string myText2;
    string line2;
    ifstream myfile2;
    myfile2.open(commands);

    if(!myfile2.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while(getline(myfile2, line2)) {
        count++;
    }

    string command[count];
    int i3=0;

    string myText3;
    string line3;
    ifstream myfile3;
    myfile3.open(commands);

    if(!myfile3.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while(getline(myfile3, line3)) {
        command[i3]=line3;//command array
        i3++;
    }
    callMethods(command , i3);//to call methods
}

void CommandReading::print(string prev , string current) {
    if(prev == "empty"){//if first command print it
        outputFile<<"\n"<<current<<"\n";
    }
    else if(prev != current){//if prev and current are different, print
        outputFile<<"\n"<<current<<"\n";
    }
}

string CommandReading::printMethod(string com){
    string re;
    if (com.find("addUser")!= std::string::npos){
        re = "===addUser() method test===";
    }
    else if(com.find("deleteUser")!= std::string::npos){
        re = "===deleteUser() method test===";
    }
    else if(com.find("addMovie")!= std::string::npos){
        re = "===addMovie() method test===";
    }
    else if(com.find("checkoutMovie") != std::string::npos){
        re = "===checkoutMovie() method test===";
    }
    else if(com.find("deleteMovie")!= std::string::npos){
        re = "===deleteMovie() method test===";
    }
    else if(com.find("showAllMovie")!= std::string::npos){
        re = "===showAllMovie() method test===\nMovie id - Movie name - Year - Status";
    }
    else if(com.find("showMovie")!= std::string::npos){
        re = "===showMovie() method test===";
    }
    else if(com.find("showUser")!= std::string::npos){
        re = "===showUser() method test===";
    }
    else if(com.find("returnMovie")!= std::string::npos){
        re = "===returnMovie() method test===";
    }
    return re;

}
void CommandReading::callMethods(string commandArr[],int length) {
    string com;
    LibrarySystem obj;
    string prev = "empty";//to save prev command
    string current;

    outputFile<<"===Movie Library System===\n";
    for(int i = 0; i<length; i++) {//call methods
        com = commandArr[i];
        current = printMethod(com);//I determine what I print
        print(prev, current);
        prev = current;

        if (com.find("addUser") != std::string::npos) {
            std::istringstream iss(com);
            std::string s,userName,userName2;
            int userId;

            iss >> s>> userId >> userName >>userName2;
            userName += " " + userName2;

            obj.addUser(userId,userName);

        }
        else if(com.find("deleteUser") != std::string::npos){
            std::istringstream iss(com);
            std::string s;
            int userId;

            iss >> s>> userId;
            obj.deleteUser(userId);
        }
        else if(com.find("addMovie") != std::string::npos){
            vector<string> v;// I seperated word by word with using vector
            string temp = "";
            for(int i=0;i<com.length();++i){

                if(com[i]=='\t'){//to not save tab character as a vector element
                    v.push_back(temp);
                    temp = "";
                }
                else{
                    temp.push_back(com[i]);
                }

            }
            v.push_back(temp);


            stringstream out(v[1]);// I convert string to int for movieid and year
            int movieId = 0;
            out >> movieId;

            stringstream out1(v[3]);
            int year = 0;
            out1 >> year;

            obj.addMovie(movieId,v[2],year);
        }
        else if(com.find("checkoutMovie") != std::string::npos){
            std::istringstream iss(com);
            std::string s;
            int movieId, userId;

            iss >> s>> movieId>> userId;
            obj.checkoutMovie(movieId,userId);
        }
        else if(com.find("deleteMovie") != std::string::npos){
            std::istringstream iss(com);
            std::string s;
            int movieId;

            iss >> s>> movieId;
            obj.deleteMovie(movieId);
        }
        else if(com.find("showAllMovie") != std::string::npos){
            obj.showAllMovies();
        }

        else if(com.find("showMovie") != std::string::npos){
            std::istringstream iss(com);
            std::string s;
            int movieId;

            iss >> s>> movieId;
            obj.showMovie(movieId);
        }
        else if(com.find("showUser") != std::string::npos){
            std::istringstream iss(com);
            std::string s;
            int userId;

            iss >> s>> userId;
            obj.showUser(userId);
        }

        else if(com.find("returnMovie") != std::string::npos){
            std::istringstream iss(com);
            std::string s;
            int movieId;

            iss >> s>> movieId;
            obj.returnMovie(movieId);
        }
    }

}


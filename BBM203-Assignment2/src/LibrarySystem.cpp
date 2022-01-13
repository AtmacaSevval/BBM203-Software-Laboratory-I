//
// Created by EA on 30.11.2020.
//

#include "LibrarySystem.h"
#include "CommandReading.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct UserNode{//user node
    int userId;
    string userName;
    UserNode* next;
    UserNode* prev;
}*head;

struct NodeChecked{//checked movies node
    int CheckedMovieID;
    string CheckedMovieTitle;
    int CheckedYear;
    int CheckedUser;
    NodeChecked* next;
};
struct NodeChecked* headChecked = NULL;


struct NodeNotChecked{//notchecked movies node
    int NotCheckedMovieID;
    string NotCheckedMovieTitle;
    int NotCheckedYear;
    NodeNotChecked* next;
};
struct NodeNotChecked* headNotChecked = NULL;


LibrarySystem::LibrarySystem() {

}

LibrarySystem::~LibrarySystem(){

}


int LibrarySystem::UserException(const int newuserId) {
    if(head == NULL) {//if head is null there is no node
        return 0;
    }

    UserNode* current = new UserNode;
    current = head;

    while(current->next != head) {
        if(current->userId == newuserId) {//if exists return 1
            return 1;
        }
        current = current->next;
    }

    if(current->userId == newuserId) {//if it is the last element return 1
        return 1;
    }
    return 0;
}

void LibrarySystem::addUser(const int newUserId, const string newUserName){
    int ch = UserException(newUserId);//check if user exists or not
    if(ch == 1){
        outputFile<<"User "<<newUserId<<" already exists\n";
        return;
    }
    UserNode* new_node = new UserNode;

    if (head == NULL)//add as a first node
    {
        new_node->userId = newUserId;
        new_node->userName= newUserName;
        new_node->next = new_node->prev = new_node;
        head = new_node;//change the head

    }

    else{// if it is not null
        UserNode *last = head->prev;//find the last node

        new_node->userId = newUserId;
        new_node->userName = newUserName;
        new_node->next = head;//connect last and head
        head->prev = new_node;

        new_node->prev = last;//connect to last
        last->next = new_node;
    }
    outputFile<<"User "<<newUserId<<" has been added\n";
}

void LibrarySystem::deleteUser(const int newUserId){
    int exc = UserException(newUserId);
    if(exc == 0){//there is no user with this id
        outputFile<<"User "<<newUserId<<" does not exist\n";
        return;
    }

    UserNode* temp = head;// find the user
    while (temp->userId != newUserId){
        temp = temp->next;
    }

    UserNode* last = head;// find the last node
    while (last->next != head){
        last = last->next;
    }
    if(temp == head && head->next == head){//if there is only one node and equal to head
        head = NULL;
        outputFile<<"User "<<newUserId<<" has been deleted\n";
        deleteMovieUser(newUserId);// delete movies in that user
        return;
    }
    else if(temp == head){//if there is not only one node and equal to head
        head = head->next;// change the head
        last->next = head;
        head->prev = last;
        free(temp);// free head

        deleteMovieUser(newUserId);// delete movies in that user
        outputFile<<"User "<<newUserId<<" has been deleted\n";
        return;
    }

    UserNode* before = temp->prev;
    UserNode* after = temp->next;
    if(temp == last){//if it is equal tothe last node
        before->next = head;// to make before to last
        head->prev = before;//change the last node
        free(temp);
    }

    else{//if it is in the middle
        before->next = after;
        after->prev = before;
        free(temp);

    }

    outputFile<<"User "<<newUserId<<" has been deleted\n";
    deleteMovieUser(newUserId);


}
void LibrarySystem::deleteMovieUser(const int userId){// to delete user's movie
    NodeChecked* del = headChecked;
    int movie;
    if(headChecked == NULL){
        return;
    }
    if(headChecked->next == headChecked){//if there is only one node
        if(del->CheckedUser == userId){
            movie = del->CheckedMovieID;
            deleteChecked(movie);
        }
    }
    else {
        while (del->next != headChecked) {
            if (del->CheckedUser == userId) {
                deleteChecked(movie);
            }
            del = del->next;
        }
        if (del->CheckedUser == userId) {
            deleteChecked(movie);
        }
    }
}

int LibrarySystem::movieException(const int movieId){
    if(headNotChecked == NULL) {//if it is null then there is no movie
        return 0;
    }
    NodeNotChecked* current = new NodeNotChecked;
    current = headNotChecked;

    while(current->next != headNotChecked) {
        if(current->NotCheckedMovieID == movieId) {//if there is a movie then return 1
            return 1;
        }
        current = current->next;
    }

    if(current->NotCheckedMovieID == movieId) {//if it equal to last node
        return 1;
    }
    return 0;
}

void LibrarySystem::addMovie(const int movieId, const string movieTitle, const int year) {
    int x = movieException(movieId);
    if(x == 1){
        outputFile<<"Movie "<<movieId<<" has already exits\n";
        return;
    }
    addNotChecked(movieId, movieTitle, year);//add movie to checked list
    outputFile<<"Movie "<<movieId<<" has been added\n";


}
void LibrarySystem::addNotChecked(const int movieId, const string movieTitle, const int year) {
    NodeNotChecked* newNode = new NodeNotChecked();

    //to assign data elements
    newNode->NotCheckedMovieID = movieId;
    newNode->NotCheckedMovieTitle = movieTitle;
    newNode->NotCheckedYear = year;

    //assign head to the next of new node
    newNode->next = headNotChecked;

    /* If linked list is not NULL then set the
    next of last node */
    if (headNotChecked != NULL)
    {
        NodeNotChecked* temp = headNotChecked;
        while (temp->next != headNotChecked)
            temp = temp->next;
        temp->next = newNode;
    }
    else{
        newNode->next = newNode;
        headNotChecked = newNode;//For the first node
    }
}

void LibrarySystem::checkoutMovie(const int movieId, const int userId){
    int y = UserException(userId);
    if(y != 1){
        outputFile<<"User "<<userId<<" does not exist for checkout\n";
        return;
    }

    int x = movieException(movieId);
    if(x!=1){
        outputFile<<"Movie "<<movieId<<" does no exist for checkout\n";
        return;
    }
    string newCheckedMovieTitle;
    int newCheckedYear;

    if(headNotChecked->NotCheckedMovieID==movieId && headNotChecked->next==headNotChecked)//if there is only one node and equal to head
    {
        newCheckedMovieTitle = headNotChecked->NotCheckedMovieTitle;
        newCheckedYear = headNotChecked->NotCheckedYear;
        free(headNotChecked);
        headNotChecked=NULL;
    }

    NodeNotChecked* last=headNotChecked;
    NodeNotChecked* d = new NodeNotChecked();

    if(headNotChecked->NotCheckedMovieID==movieId)// if it is equal to head but there is not just one node in list
    {
        newCheckedMovieTitle = headNotChecked->NotCheckedMovieTitle;
        newCheckedYear = headNotChecked->NotCheckedYear;
        while(last->next!= headNotChecked)
            last=last->next;

        last->next=headNotChecked->next;
        free(headNotChecked);
        headNotChecked=last->next;
    }
    while(last->next!=headNotChecked && last->next->NotCheckedMovieID!=movieId)//find the node
    {
        last=last->next;
    }

    // If node to be deleted was found
    if(last->next->NotCheckedMovieID==movieId)
    {
        d = last->next;
        newCheckedMovieTitle = last->next->NotCheckedMovieTitle;
        newCheckedYear = last->next->NotCheckedYear;
        last->next=d->next;
        free(d);
    }

    /*I deleted from "not checked node" then I add "checked node"*/
    NodeChecked* ptr1 = new NodeChecked();
    ptr1->CheckedUser = userId;
    ptr1->CheckedMovieID = movieId;
    ptr1->CheckedMovieTitle = newCheckedMovieTitle;
    ptr1->CheckedYear = newCheckedYear;
    ptr1->next = headChecked;

    /* If linked list is not NULL then set the
    next of last node */
    if (headChecked != NULL)
    {
        NodeChecked* temp = headChecked;
        while (temp->next != headChecked)
            temp = temp->next;
        temp->next = ptr1;
    }
    else {
        ptr1->next = ptr1;
        headChecked = ptr1; /*For the first node */
    }

    outputFile<<"Movie "<<movieId<<" has been checked out by User "<<userId<<"\n";


}
void LibrarySystem::deleteChecked(const int movieId) {// to delete movies in the checked list.
    if (headChecked->CheckedMovieID == movieId && headChecked->next == headChecked) {// if there is only one node and equal to head
        free(headChecked);
        headChecked = NULL;
    }

    NodeChecked *last1 = headChecked;
    NodeChecked *d1 = new NodeChecked();

    if (headChecked->CheckedMovieID == movieId) {// if there is not only one node and equal to head
        while (last1->next != headChecked)
            last1 = last1->next;

        last1->next = headChecked->next;// change the head
        free(headChecked);
        headChecked = last1->next;
    }
    while (last1->next != headChecked && last1->next->CheckedMovieID != movieId) {//find the node to delete
        last1 = last1->next;
    }

    if (last1->next->CheckedMovieID == movieId) {// If node to be deleted was found
        d1 = last1->next;
        last1->next = d1->next;
        free(d1);
    }
}

void LibrarySystem::deleteMovie(const int movieId){

    int ch = checkedMovieException(movieId);
    int nch = movieException(movieId);
    if(nch == 0 && ch == 0){

        outputFile<<"Movie "<<movieId<<" does not exist\n";
        return;
    }

    else if(nch == 1){// if it is in "not checked node"

        if(headNotChecked->NotCheckedMovieID==movieId && headNotChecked->next==headNotChecked)//delete from head and single node
        {
            free(headNotChecked);
            headNotChecked=NULL;
            outputFile<<"Movie "<<movieId<<" has not been checked out\n";
            outputFile<<"Movie "<<movieId<<" has been deleted\n";
            return;
        }

        NodeNotChecked* last=headNotChecked;
        NodeNotChecked* d = new NodeNotChecked();

        if(headNotChecked->NotCheckedMovieID==movieId)//delete from head
        {
            while(last->next!= headNotChecked)
                last=last->next;

            last->next=headNotChecked->next;
            free(headNotChecked);
            headNotChecked=last->next;
        }
        while(last->next!=headNotChecked && last->next->NotCheckedMovieID!=movieId)//find the node
        {
            last=last->next;
        }

        // If node to be deleted was found
        if(last->next->NotCheckedMovieID==movieId)
        {
            d = last->next;
            last->next=d->next;
            free(d);
        }
        outputFile<<"Movie "<<movieId<<" has not been checked out\n";
        outputFile<<"Movie "<<movieId<<" has been deleted\n";

    }

    else if(ch == 1) {// if it is in "checked node"
        deleteChecked(movieId);
        outputFile<<"Movie "<<movieId<<" has been checked out\n";
        outputFile<<"Movie "<<movieId<<" has been deleted\n";
    }
}

void LibrarySystem::showAllMovies(){
    NodeNotChecked* temp = headNotChecked;// print "not checked list"
    if (headNotChecked != NULL) {
        do {
            outputFile<< temp->NotCheckedMovieID << " "<<temp->NotCheckedMovieTitle<<" "<<temp->NotCheckedYear<<" Not checked out\n";
            temp = temp->next;
        } while (temp != headNotChecked);
    }


    NodeChecked* temp1 = headChecked;//print "checked list"
    if (headChecked != NULL) {
        do {
            outputFile << temp1->CheckedMovieID << " "<<temp1->CheckedMovieTitle<<" "<<temp1->CheckedYear<<" Checked out by User "<<temp1->CheckedUser<<"\n";
            temp1 = temp1->next;
        } while (temp1 != headChecked);
    }


}
void LibrarySystem::showMovie(const int movieId){
    int ch = checkedMovieException(movieId);
    int nch = movieException(movieId);

    if(nch == 0 && ch == 0){
        outputFile<<"Movie with the id "<<movieId<<" does not exist\n";
        return;
    }

    else if(nch == 1){// if the movie in "not checked list"
        NodeNotChecked* temp1 = headNotChecked;
        if (headNotChecked != NULL) {
            do {
                if(temp1->NotCheckedMovieID == movieId){//find the node and then print its data
                    break;
                }
                temp1 = temp1->next;
            } while (temp1 != headNotChecked);
        }
        outputFile<< temp1->NotCheckedMovieID << " "<< temp1->NotCheckedMovieTitle<<" "<<temp1->NotCheckedYear<<" Not checked out\n";
    }

    else if(ch == 1){// if the movie in " checked list"
        NodeChecked* temp = headChecked;
        if (headChecked != NULL) {
            do {
                if(temp->CheckedMovieID == movieId){//find the node and then print its data
                    break;
                }
                temp = temp->next;
            } while (temp != headChecked);
        }
        outputFile << temp->CheckedMovieID << " "<< temp->CheckedMovieTitle<<" "<<temp->CheckedYear<<" Checked out by User "<<temp->CheckedUser<<"\n";

    }
}

int LibrarySystem::checkedMovieException(const int movieId){
    if(headChecked == NULL) {//if it is null there is no movie then true
        return 0;
    }
    NodeChecked* current = new NodeChecked;
    current = headChecked;

    while(current->next != headChecked) {
        if(current->CheckedMovieID == movieId) {// if there is a movie with this movieid
            return 1;
        }
        current = current->next;
    }

    if(current->CheckedMovieID == movieId) {
        return 1;
    }
    return 0;

}
void LibrarySystem::returnMovie(const int movieId){
    int ch = checkedMovieException(movieId);
    int nch = movieException(movieId);
    if(nch == 0 && ch == 0){
        outputFile<<"Movie "<<movieId<<" not exist in the library\n";
        return;
    }
    else if(nch == 1){//if it is in "not checked node"
        outputFile<<"Movie "<<movieId<<" has not been checked out\n";

    }
    else if(ch == 1){//if it is in "checked node"
        int movieid;
        string movietitle;
        int year;
        NodeChecked *temp = headChecked;//find the node
        if (headChecked != NULL) {
            do {
                if (temp->CheckedMovieID == movieId) {
                    movieid = temp->CheckedMovieID; movietitle= temp->CheckedMovieTitle; year= temp->CheckedYear;
                    break;
                }
                temp = temp->next;
            } while (temp != headChecked);
        }
        deleteChecked(movieId);// then delete from "checked list"
        addNotChecked(movieid, movietitle,year);//then add "not checked list"
        outputFile<<"Movie "<<movieId<<" has been returned\n";

    }
}
void LibrarySystem::showUser(const int userId){
    int y = UserException(userId);
    if(y != 1){
        outputFile<<"User "<<userId<<" does not exist for checkout\n";
        return;
    }
    else {
        UserNode* temp3 = head;// find user and their data and print
        if (head != NULL) {
            do {
                if(temp3->userId == userId){
                    outputFile<<"User id: "<<userId<<" User name: "<<temp3->userName<<"\n";
                    outputFile<<"User "<<userId<<" checked out the following Movies:\n";
                }
                temp3 = temp3->next;
            } while (temp3 != head);
        }

        NodeChecked *temp = headChecked;//then print their movies until head
        if (headChecked != NULL) {
            do {
                if (temp->CheckedUser == userId) {
                    outputFile << temp->CheckedMovieID << " " << temp->CheckedMovieTitle << " " << temp->CheckedYear << " \n";
                }
                temp = temp->next;
            } while (temp != headChecked);
        }
    }

}

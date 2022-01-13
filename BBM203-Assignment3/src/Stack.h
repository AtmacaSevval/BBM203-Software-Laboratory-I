//
// Created by EA on 9.12.2020.
//

#ifndef NEWASSIGNMENT3_STACK_H
#define NEWASSIGNMENT3_STACK_H

/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);

*/

#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class Stack {
public:
    Stack();

    ~Stack();

    bool isEmpty() const;

    int size() const;

    //Push: Place item on top of the stack
    void push(const T &newItem);

    //Top: Take a look at the topmost item without removing it
    void getTop(T &stackTop) const;

    //Pop: Remove item from the top of the stack
    void pop();

    string display();

private:
    struct ListNode {
        T item;
        ListNode *next;
    };
    ListNode *_head;
    int _size;
};

#endif //NEWASSIGNMENT3_STACK_H


template <typename T>
Stack<T>::Stack(){
    _size = 0;
    _head = NULL;
}

template <typename T>
Stack<T>::~Stack(){}

template <typename T>
bool Stack<T>::isEmpty() const{
    return _size == 0;
}

template <typename T>
int Stack<T>::size() const{
    return _size;
}

template <typename T>
void Stack<T>::push(const T &newItem){
    struct ListNode* temp;
    temp = new ListNode();


    struct ListNode* temp1 = _head;
    if (temp1 == NULL)
    {
        temp->item = newItem;

        temp->next = NULL;
        // Make temp as top of Stack
        _head = temp;
        _size++;
    }

    else {// Initialize data into temp data field
        temp->item = newItem;

        temp->next = _head;
        // Make temp as top of Stack
        _head = temp;
        _size++;
    }
}

template <typename T>
void Stack<T>::getTop(T &stackTop) const{
    if (isEmpty())
        throw string("Stack is empty");
    else
        stackTop = _head->item;
}

template <typename T>
void Stack<T>::pop() {
    struct ListNode* temp;

    if (_head == NULL)
    {

    }
    else
    {
        // Top assign into temp
        temp = _head;

        // Assign second node to top
        _head = _head->next;

        // Destroy connection between first and second
        temp->next = NULL;

        // delete node
        free(temp);
    }

    _size--;
}

//output
template <typename T>
string Stack<T>::display(){
    string ou;
    ListNode* curPtr = _head;
    while (curPtr != NULL)
    {
        ou += curPtr->item + "\n";
        curPtr = curPtr->next;
    }

    return ou;
}



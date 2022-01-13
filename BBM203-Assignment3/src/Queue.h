//
// Created by EA on 9.12.2020.
//

#ifndef NEWASSIGNMENT3_QUEUE_H
#define NEWASSIGNMENT3_QUEUE_H


/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/

#include <iostream>
#include <sstream>

using namespace std;


template<typename T>
class Queue {
public:
    Queue();

    ~Queue();

    bool isEmpty() const;

    int size() const;

    //Enqueue: Items are added to the back of the queue
    void enqueue(const T &newItem);

    //Dequeue: Items are removed from the front of the queue
    void dequeue();

    //Get Front: Take a look at the first item
    void getFront(T &queueTop) const;

    //for txt
    string display();

private:
    struct QueueNode {
        T item;
        QueueNode *next;
    };
    int _size;
    /* to avoid the traversal to the last node,
     an additional pointer to the last node is defined*/
    QueueNode *_front;
    QueueNode *_lastNode;
};


#endif //NEWASSIGNMENT3_QUEUE_H
template<typename T>
Queue<T>::Queue(){
    _size = 0;
    _front = NULL;
}

template <typename T>
Queue<T>::~Queue(){}

template <typename T>
bool Queue<T>::isEmpty() const{
    return _size == 0;
}

template <typename T>
int Queue<T>::size() const{
    return _size;
}

template <typename T>
void Queue<T>::enqueue(const T &newItem){
    QueueNode* temp = new QueueNode;

    temp->item = newItem;
    temp->next = NULL;
    // If queue is empty, then new node is front and rear both
    if (_front == NULL) {
        _front = _lastNode = temp;
        _size++;
        return;
    }
    // Add the new node at the end of queue and change rear
    _lastNode->next = temp;
    _lastNode = temp;
    _size++;
}


template<typename T>
void Queue<T>::dequeue(){
    if (_front == NULL)
        return;

    // Store previous front and move front one node ahead
    QueueNode* temp = _front;
    _front = _front->next;

    // If front becomes NULL, then there is just one item then change rear also as NULL
    if (_front == NULL)
        _lastNode = NULL;

    temp->next=NULL;
    free (temp);
    _size--;

}

template<typename T>
void Queue<T>::getFront(T &queueTop) const{
    if (isEmpty())
        throw string("Queue is empty");
    else
        queueTop = _front->item;
}

template <typename T>
string Queue<T>::display(){//to output
    string ou;
    QueueNode* curPtr = _front;
    while (curPtr != NULL)
    {
        std::istringstream iss(curPtr->item);
        std::string truck,power;
        iss >> truck >>power;
        ou += truck + "\n";
        curPtr = curPtr->next;
    }
    return ou;
}

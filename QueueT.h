#pragma once
#include <iostream>
#include <stdexcept>
using std::cout;
using std::endl;
using std::runtime_error;

// Template class for the nodes to create a singly linked list
// to implement a queue.
template <class T>
class NodeT
{
    public:
    T data;
    NodeT<T>* next;
    // Constructor that initializes the value of the node.
    NodeT(T val) : data(val), next(nullptr) { ; };
    // Constructor that initializes the value of the node and 
    // the next node.
    NodeT(T val, NodeT<T>* nd) : data(val), next(nd) { ; };
};

// Template class for the queue.
template <class T>
class QueueT
{
public:
    // Constructor that creates an empty queue.
    QueueT();
    
    // Copy constructor that creates deep copy of its 
    // constant QueueT reference parameter
    QueueT(const QueueT<T> & qu);
    
    // Destructor that deallocates the dynamic memory allocated
    // by the queue.
    ~QueueT();

    // Overload operator that deep copies its constant QueueT 
    // reference parameter
    QueueT<T> & operator=(const QueueT<T> & qu);

    // Enqueue function that inserts its template type parameter at the
    // back of queue.
    void enqueue(T val);
    
    // Dequeue function that removes and returns the value at the front of
    // the queue.
    T dequeue();

    // Prints the contents of the queue, from front to back.
    void print();

    // Empty function that returns true if the queue is empty or false
    // if otherwise.
    bool empty();

    // Size function that returns the number of items in the queue.
    int size();

    // Concatenate function that concatenates the first n values of its 
    // QueueT parameter to the end of the calling object.
    void concatenate(QueueT<T> & qu, int n);

    // Merges the contents of the calling object and its constant QueueT 
    // reference parameter in an alternating order between them.
    QueueT<T> merge(const QueueT<T> & qu);

    // getFront function that returns a pointer to the node at the front of
    // the queue.
    NodeT<T>* getFront();

private:
    // A helper function that copies the queue.
    void copyQueue(const QueueT<T> & qu);
    
    // A helper function that copies each node in the singly linked list
    // recursively.
    void copyNode(NodeT<T>* original, NodeT<T>* copy);

    // A helper function that deallocates the dynamic memory allocated by the 
    // queue.
    void removeAll();

    // A pointer to a NodeT that represents the front of the queue.
    NodeT<T>* front;

    // A pointer to a NodeT that represents the back of the queue.
    NodeT<T>* back;

    // An int that records the current size of the queue.
    int sz;
};

// QUEUE PUBLIC METHODS IMPLEMENTATION

// Constructor that creates an empty queue.
template <class T>
QueueT<T>::QueueT()
{
    front = nullptr;
    back = nullptr;
    sz = 0;
}

// Copy constructor that creates a deep copy of its constant QueueT
// reference parameter.
template <class T>
QueueT<T>::QueueT(const QueueT & qu)
{
    // Calls a helper function to copy the queue.
    copyQueue(qu);
}

// A helper function that creates a deep copy of its constant QueueT
// reference parameter.
template <class T>
void QueueT<T>::copyQueue(const QueueT & qu)
{
    if (qu.front!=nullptr){
        NodeT<T>* original = qu.front;
        // Creating a new node for a deep copy.
        front = new NodeT<T>(original->data);
        back = front;
        sz = qu.sz;
        if (front != nullptr){
            // Calls a helper function to copy each node of the queue.
            copyNode(original->next, front);
        }
    }
}

// A helper function that deep copies each node of the queue recursively.
template <class T>
void QueueT<T>::copyNode(NodeT<T>* original, NodeT<T>* copy)
{
    if (original != nullptr){  
        // Creating a new node for a deep copy.
        copy->next = new NodeT<T>(original->data); 
        back = copy->next;
        copyNode(original->next, copy->next);
    }
}

// A destructor that deallocates dynamic memory allocated by the queue.
template <class T>
QueueT<T>::~QueueT()
{
    // Calls a helper function that deallocates dynamic memory of a queue.
    removeAll();
}

// A helper function that deallocates dynamic memory allocated by a queue.
template <class T>
void QueueT<T>::removeAll()
{
    NodeT<T>* temp = front;
    while (front != nullptr){
        front = temp->next;
        delete temp;
        temp = front;
    }
    sz = 0;
    front = nullptr;
    back = nullptr;
}

// Overload operator that deep copies its constant QueueT reference parameter
// into the calling object after deallocating any dynamic memory associated with
// the original contents of the calling object.
template <class T>
QueueT<T> & QueueT<T>::operator=(const QueueT & qu)
{
    if (this != &qu){
        // Calls a helper function to deallocate the dynamic memory.
        removeAll();
        // Calls a helper function to deep copy to the calling object.
        copyQueue(qu);
    }
    return *this;
}

// Enqueue function that inserts its template type parameter at the back of the
// queue.
template <class T>
void QueueT<T>::enqueue(T val)
{
    NodeT<T>* temp = new NodeT<T>(val);
    // Checks if the queue is empty by calling the empty function.
    if (this->empty()){
        front = temp;
        back = front;
    }
    else {
        back->next = temp;
        back = temp;
    }
    sz++;
}

// Dequeue function that removes and returns the value at the front of the queue.
template <class T>
T QueueT<T>::dequeue()
{
    // Checks if the queue is empty by calling the empty function.
    if (this->empty()){
        throw runtime_error("dequeue failed - empty");
    }
    T result = front->data;
    NodeT<T>* temp = front; 
    front = front->next;
    // If there was only one node before removing and the queue is empty after 
    // removing.
    if (front == nullptr){
        back = nullptr;
    }
    sz--;
    delete temp;
    return result;
}

// Print function that prints the contents of the queue, one value per line, from
// front to back.
template <class T>
void QueueT<T>::print()
{
    NodeT<T>* temp = front; 
    while(temp!=nullptr){
        cout << temp->data << endl;
        temp = temp->next;
    }
}

// A function that checks if the queue is empty or not.
template <class T>
bool QueueT<T>::empty()
{
    return sz == 0;
}

// A function that returns the current size of the queue.
template <class T>
int QueueT<T>::size()
{
    return sz;
}

// A function that concatentates the first n value of its QueueT reference parameter
// to the end of the calling object.
template <class T>
void QueueT<T>::concatenate(QueueT<T> & qu, int n)
{
    // Checks if the number of values to be concatenated is greater than the size of the
    // parameter.
    if (n>qu.sz){
        throw runtime_error("concatenate failed - n is greater");
    }
    T temp;
    for (int i=0; i<n; i++){
        temp = qu.dequeue();
        this->enqueue(temp);
    }
}

// A function that merges the constant QueueT reference parameter with the calling object
// in an alternating order.
template <class T>
QueueT<T> QueueT<T>::merge(const QueueT<T> & qu)
{
    QueueT<T> tempQ;
    NodeT<T>* temp1 = this->front;
    NodeT<T>* temp2 = qu.front;
    // Continues to enqueue values, alternating order, until both queues have been fully added.
    while (temp1!=nullptr||temp2!=nullptr){
        // Adds the calling object's content until the whole queue has been added.
        if (temp1!=nullptr){
            tempQ.enqueue(temp1->data);
            temp1 = temp1->next;
        }
        // Adds the parameter's content until the whole queue has been added.
        if (temp2!=nullptr){
            tempQ.enqueue(temp2->data);
            temp2 = temp2->next;
        }
    }
    return tempQ;
}

// A function that returns a pointer to the node at the front of the queue.
template <class T>
NodeT<T>* QueueT<T>::getFront()
{
    return this->front;
}
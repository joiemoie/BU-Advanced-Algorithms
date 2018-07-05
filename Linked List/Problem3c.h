//  Copyright 2017 Joseph Liba
//  LinkedList.h
//
//  Copyright © 2017 Tali Moreshet. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>

using namespace std;

template <class T = int>
class Node {
public:
    Node();                                         // default constructor
    Node(const T& data, Node<T>* next = nullptr);   // donstructor
    T data;                                         // node data
    Node<T>* next;                                  // node next pointer
};

template <class T = int>
class LinkedList {
public:
    LinkedList();                                   // constructor
    ~LinkedList();                                  // destructor
    T deleteFromHead() throw (runtime_error);       // removes and returns content of head
    T deleteFromTail() throw (runtime_error);       // removes and returns content of tail
    void deleteNode(T data) throw (runtime_error);  // removes node with specified data
    void InsertToHead(T data);                      // insert node with data at the head
    void InsertToTail(T data);                      // insert node with data at the tail
    int getSize();                                  // returns size of linked list
    void print();                                   // prints linked list
private:
    Node<T>* head;                                  // head of linked list
};

template <class T = int>
class StackFromList {
public:
    StackFromList();                                // constructor
    ~StackFromList();                               // destructor
    T pop();                                        // removes data from the top of the stack
    void push(T data);                              // adds data to the top of the stack
    bool isEmpty();                                 // checks if the stack is empty
private:
    LinkedList<T> * list;                           // linked list
};

template <class T = int>
class QueueFromList {
public:
    QueueFromList();                                // constructor
    ~QueueFromList();                               // destructor
    T dequeue();                                        // removes data from the top of the stack
    void enqueue(T data);                              // adds data to the top of the stack
    bool isEmpty();                                 // checks if the stack is empty
private:
    LinkedList<T> * list;                           // linked list
};

/******* From here down is the content of the LinkedList.cpp file: ***********************/

 /* Implementation of Node */

 // default constructor
 template<class T>
 Node<T>::Node()
 {
 }
 
 // constructor
 template<class T>
 Node<T>::Node(const T& data, Node<T>* next)
 {
     this->data = data;
     this->next = next;
 }
 
 /* Implementation of linked list */

 // constructor
 template <class T>
 LinkedList<T>::LinkedList()
 {
     head = nullptr;
 }

 // destructor
 template <class T>
 LinkedList<T>::~LinkedList()
 {
    delete head;
 }

 template <class T>
 T LinkedList<T>::deleteFromHead() throw (std::runtime_error)
 {

    //Sets the head to the next node in the linked list
    Node<T> *oldHead = head;
    if (head != nullptr) {
      oldHead = head;
      head = head->next;
    }

    //Throws an exception if the Linked List is empty.
    try { return oldHead->data; }
    catch (std::runtime_error e) { std::cout << "List is empty."; throw e;}
 }

 
 template <class T>
 T LinkedList<T>::deleteFromTail() throw (std::runtime_error)
 {
    
    //Finds the last node in the linked list and removes its link to the previous node
    Node<T> * lastNode = nullptr;
    Node<T> * tail = head;
    while (tail->next != nullptr) {
      lastNode = tail;
      tail = tail->next;
    }

    //Throws an exception if the linked list is empty.
    try { 
     if (lastNode!=nullptr) {
       lastNode->next = nullptr;
       return tail->data;
     }
     else {
       head = nullptr;
       return tail->data;
     }
    }
    catch (std::runtime_error e) { throw e;}   
 }
 

 template <class T>
 void LinkedList<T>::deleteNode(T data) throw (std::runtime_error)
 {
    //Finds the node containing a certain value and sets the links the previous node to the following node
    Node<T> * lastNode = nullptr;
    Node<T> * currentNode = head;
    
    //Throws an exception if the linked list is empty.
    try {
      while (currentNode != nullptr && currentNode->data != data) {
        lastNode = currentNode;
        currentNode = currentNode->next;
      }
      if (lastNode == nullptr) {
        head = head->next;
      }
      else {
        lastNode->next = currentNode->next;
      }
    }
    catch (std::runtime_error e) { throw e;}
 }
 

 template <class T>
 void LinkedList<T>::InsertToHead(T data)
 {
     Node<T> * newNode = new Node<T>(data, nullptr);
     
     if (head == nullptr)
         head = newNode;
     else
     {
         newNode->next = head;
         head = newNode;
     }
 }


 template <class T>
 void LinkedList<T>::InsertToTail(T data)
 {
   Node<T> * newNode = new Node<T>(data, nullptr);
   Node<T> * currentNode = head;
   if (currentNode != nullptr) {
     while (currentNode->next != nullptr) currentNode = currentNode->next;
     currentNode->next = newNode;
   }
   else head = newNode;
 }


 template <class T>
 int LinkedList<T>::getSize()
 {
   int length = 0;
   Node<T> * currentNode = head;
   if (currentNode!=nullptr) {
     while (currentNode!=nullptr) {
       length++;
       currentNode = currentNode->next;
     }
   }
   return length;
 }


 template <class T>
 void LinkedList<T>::print()
 {
     if (head == nullptr)
     {
         cout << "Linked list is empty" << endl;;
         return;
     }
     
     cout << head->data << " ";
     
     if (head->next == nullptr)
     {
         cout << endl;
         return;
     }
 
     Node<T>* currNode = head->next;
     Node<T>* prevNode = head;
 
     
     while (currNode->next != nullptr)
     {
         cout << currNode->data << " ";
         prevNode = currNode;
         currNode = currNode->next;
     }
 
     cout << currNode->data << endl;
     return;
 }

  /* Implementation of stack */

 // constructor
 template <class T>
 StackFromList<T>::StackFromList()
 {
     list = new LinkedList<T>();
 }

 // destructor
 template <class T>
 StackFromList<T>::~StackFromList()
 {
    delete list;
 }

 template <class T>
 T StackFromList<T>::pop()
 {
   return list->deleteFromTail();
 }

 template <class T>
 void StackFromList<T>::push(T data)
 {
   list->InsertToTail(data);
 }

 template <class T>
 bool StackFromList<T>::isEmpty()
 {
   return (list->getSize() == 0) ? true : false;
 }

  /* Implementation of queue */

 // constructor
 template <class T>
 QueueFromList<T>::QueueFromList()
 {
     list = new LinkedList<T>();
 }

 // destructor
 template <class T>
 QueueFromList<T>::~QueueFromList()
 {
    delete list;
 }

 template <class T>
 T QueueFromList<T>::dequeue()
 {
   return list->deleteFromHead();
 }

 template <class T>
 void QueueFromList<T>::enqueue(T data)
 {
   list->InsertToTail(data);
 }

 template <class T>
 bool QueueFromList<T>::isEmpty()
 {
   return (list->getSize() == 0) ? true : false;
 }
     
#endif /* LinkedList_h */

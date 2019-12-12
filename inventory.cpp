//
//  inventory.cpp
//  Lab4
//
//  Created by Daniela Castro on 5/25/19.
//  Copyright © 2019 Daniela Castro. All rights reserved

//CSC 2430 Spring 2019 LAB 4 – Inventory Manager (Linked List)
//Dr. Taiwoo Park
//

#include <iostream>
#include <string>
#include <iomanip>
#include "inventory.h"

using namespace std;


//given pointers
Node::Node(Item* item) {
    
    _item = item;
    _next = nullptr;
}

Node::~Node() {
    delete _item;
}

Node* Node::getNext() const {
    return _next;
}

Item* Node::getItem() const {
    return _item;
}

void Node::setNext(Node* nextPtr) {
    _next = nextPtr;
}

void Node::setItem(Item* item) {
    _item = item;
}

//Initializes _head to nullptr.
Inventory::Inventory() {
    _head = nullptr;
}

//Free up (i.e., delete) all nodes in the list. Tilda indicates calling destructor.
Inventory::~Inventory() {
    
    while(_head != nullptr)
        pop_front();
}

//Allocate a new Node with the parameter item, then insert it at the front of the list. Update _head to the new Node pointer.
void Inventory::push_front(Item* newItem) {
    
    Node *newNode = new Node(newItem);
    newNode->setNext(_head);
    _head = newNode;
}

//Returns the first item of the list (i.e., _head’s item). If there is no Node, return nullptr.
Item* Inventory::front() const {
    
    if (_head != nullptr)
        return _head->getItem();
    
    return nullptr;
}


//Deletes the first node. Return true if the delete was successful, false otherwise (i.e., no node).
bool Inventory::pop_front() {
    
    Node* erase;
    erase = _head;
    
    if(!isEmpty())
    {
        _head = _head->getNext();
        delete erase;
        return true;
    }
    
    return false;
}


//Traverse the nodes in the list and return if there is a node containing an item having the same name to the string parameter.   if found, nullptr otherwise.
Node* Inventory::findNodeByName(const string &givenName) const {
    
    for (Node* i = _head; i != nullptr; i= i->getNext())
        if(i->getItem()->getName() == givenName)
            return i;
    
    return nullptr;
}

//Traverse the nodes in the list and return if there is a node containing an item having the same ID to the integer parameter.   if found, nullptr otherwise.
Node* Inventory::findNodeByID(const int id) const {
    
    for (Node* i = _head; i != nullptr; i= i->getNext())
        
        if(i->getItem()->getID() == id)
            return i;
    
    return nullptr;
}

//Traverse the nodes in the list and return if there is a node containing an item having the same name to the string parameter. Return an item pointer if found, nullptr otherwise.
Item* Inventory::findItemByName(const string &productName) const {
    
    for (Node* i = _head; i != nullptr; i= i->getNext())
        if(i->getItem()->getName() == productName)
            return i->getItem();
    
    return nullptr;
}

//Traverse the nodes in the list and return if there is a node containing an item having the same ID to the integer parameter. Return an item pointer if found, nullptr otherwise.
Item* Inventory::findItemByID(const int identification) const {
    
    Node* found = findNodeByID(identification);
    if (found == nullptr)
        return nullptr;
    
    return found->getItem();
}

//Find an item with the given id (first parameter), then increase its quantity by the given value (second parameter). Return the updated quantity. If there is no item with the given id, return -1.
int Inventory::stockIn(const int id, const int quantity) {
    
    Item* found = findItemByID(id);
    if (found == nullptr)
        return -1;
    
    
    int totalQuantity = found->getQuantity();
    totalQuantity += quantity;
    found->setQuantity(totalQuantity);
    
    return totalQuantity;
}


//Find an item with the given id (first parameter), then decrease its quantity by the given value (second parameter). If the given value is greater than the current quantity in stock, update the quantity as zero. Return how many items are withdrawn.
int Inventory::stockOut(const int id, const int quantity) {
    
    
    Item* found = findItemByID(id);
    if (found == nullptr)
        return -1;
    
    if (quantity > found->getQuantity()) {
        
        int ret = found->getQuantity();
        found->setQuantity(0);
        
        return ret;
    }
    
    found->setQuantity(found->getQuantity() - quantity);
    
    return quantity;
}

//Add a new item to the inventory, if there is no item with the same ID. Return true if the addition was successful. False otherwise, that is, there is already an item with the same ID.
bool Inventory::addNewItem(Item* id) {
    
    Node* the_node = _head;
    if (_head == nullptr)
    {
        _head = new Node(id);
        return true;
        
    }
    
    while (the_node->getNext() != nullptr) {
        
        if (the_node->getItem()->getID() == id->getID()) {
            
            return false;
            
        }
        the_node = the_node->getNext();
        
        
    }
    
    push_front(id);
    return true;
}


//Find an item with the given ID, then delete it, (1) Find the node with the item with the given ID (say A) (2) Switch A’s item and head’s item (3) Delete head (using pop_head)
bool Inventory::deleteItem(const int id) {
    
    for (Node* i = _head; i != nullptr; i= i->getNext()) {
        
    if (i->getItem()->getID() == id) {
            //using item pointer
            Item* myItem;
                myItem = i->getItem();
                i->setItem(_head->getItem());
                _head->setItem(myItem);
                pop_front();
    return true;
        }
    }
    
    return false;
    
}

//Returns true if there are no nodes in the list, false otherwise.
bool Inventory::isEmpty() const {
    return _head == nullptr;
}


//Reads records from an istream, and insert them to the inventory. Each line has the four fields for one item record. Per record, an Item object is allocated and added to the inventory. Returns the number of records read.
int Inventory::load(istream& fin) {
    int id;
    int quantity;
    string name;
    double price;
    int counter = 0;

    
    while (!fin.eof())
    {
        fin>>id>>name>>price>>quantity;
        if (!fin.fail())
            
        {
            Item* z = new Item(id,name,price,quantity);
            if (addNewItem(z))
            {
                counter++;
            }
        }
    }
    
    return counter;
    
}

//From the head to the tail, print all records in a formatted way to ostream. It should format the output in the following way per record
void Inventory::formattedPrint(ostream& out) {
    
    Node* myptr = _head;
    
    while (myptr != nullptr)
    {
        out << left << fixed << setprecision(2);
        out << setw(6) << myptr->getItem()->getID();
        out << setw(12) << myptr->getItem()->getName();
        out << setw(8) << myptr->getItem()->getPrice();
        out << setw(4) <<  myptr->getItem()->getQuantity() << endl;
        myptr = myptr->getNext();
    }
    
    
}


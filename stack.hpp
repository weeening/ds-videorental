#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <stdexcept> // for exception
#include <string>
#include <cstddef> // for NULL
#include <new> // for bad_alloc
#include <regex>
#include "record.hpp"
//--------------------------------------------------------STACK-----------------------------------------------------------------------
using namespace std;

class StackException : public logic_error
{
    public:
    StackException(const string& message = "")
    :  logic_error(message.c_str())
    {}
};

class Stack : public record
{
private:

    struct StackNode
    {
    int qty;
    string cat;
    string title;
    double price;
    StackNode *next;
    };

    StackNode *topPtr;
    int size;


public:

    Stack() : topPtr(NULL),size(0){}

    Stack(const Stack& aStack)
    {
        if (aStack.topPtr == NULL)
            topPtr = NULL; // original list is empty
        else
    {
    // copy first node
        topPtr = new StackNode;
        topPtr->cat = aStack.topPtr->cat;
        topPtr->title = aStack.topPtr->title;
        topPtr->price = aStack.topPtr->price;
        topPtr->qty = aStack.topPtr->qty;

    // copy rest of list
        StackNode *newPtr = topPtr; // new node pointer

        for (StackNode *origPtr = aStack.topPtr->next;
        origPtr != NULL; origPtr = origPtr->next)
        {
            newPtr->next = new StackNode;
            newPtr = newPtr->next;
            newPtr->cat = origPtr->cat;
            newPtr->title = origPtr->title;
            newPtr->price = origPtr->price;
            newPtr->qty = origPtr->qty;
        }
        newPtr->next = NULL; //tail
        }
    }
    ~Stack()
        {
        // pop until stack is empty
        while (!isEmpty())
        pop();
        // Assertion: topPtr == NULL
        }

    bool isEmpty() const
        {
        return topPtr == NULL;
        }

    int getLength() const
        {
        return size;
        }
    void push(int index, string &cat,string &title, double &price,int &qty,string filename) throw(StackException)
        {
        // create a new node
        try
        {
            record::load(filename);
            record::retrieve(index,cat,title,price,qty);

            StackNode *newPtr = new StackNode;
                // set data portion of new node
            newPtr->price = price;
            newPtr->cat=cat;
            newPtr->title=title;
            newPtr->qty=qty;

                // insert the new node
            newPtr->next = topPtr; //newPtr->next pointer points to topPtr
            topPtr = newPtr;
            size++;
        }
        catch (bad_alloc e)
        {
            throw StackException(
                "StackException: push cannot allocate memory.");
        }
        }
    void pop() throw(StackException)
    {
        if (isEmpty())
            throw StackException("StackException: stack empty on pop");
        else
    {
        // stack is not empty; delete top
        StackNode *temp = topPtr;
        topPtr = topPtr->next;
        // return deleted node to system
        temp->next = NULL; // safeguard, don't point anything, points to nothing
        delete temp;
        temp = NULL;
        size--;
        }
    }

    double getTop() const throw(StackException)
    {
        double price;
        if (isEmpty())
            throw StackException("StackException: stack empty on getTop");
        else
        // stack is not empty; retrieve top

            price = topPtr->price;
            return price;
    }
};

#endif // STACK_HPP

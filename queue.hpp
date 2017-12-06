#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>    // Only for displaying copy constructor
#include <iomanip>
#include <fstream>     // for file I/O
#include <sstream>
#include <cstddef>     // for NULL
#include <string>
#include <new>         // for bad_alloc
#include <regex>
#include "recordException.h"
#include "recordIndexOutOfRangeException.h"
#include "record.hpp"
//-----------------------------------------------------------QUEUE---------------------------------------------------------------------
using namespace std;

class Queue : public record
{
private:
    struct qnode
    {
        int qty;
        string cat,title;
        double price;
        qnode *next;
    };
    qnode *frontPtr;
    qnode *backPtr;
    record Record;
    int qSize;

public:
    Queue():qSize(0){};
    Queue(const Queue &aQueue):qSize(aQueue.qSize)
{
    if ( aQueue.frontPtr == NULL )
   {
      frontPtr = NULL;  // original list is empty
   }
   else
   {
      // copy first node
      frontPtr = new qnode;
      frontPtr->cat = aQueue.frontPtr->cat;
      frontPtr->title = aQueue.frontPtr->title;
      frontPtr->qty = aQueue.frontPtr->qty;
      frontPtr->price = aQueue.frontPtr->price;


      // copy rest of list
      qnode *newPtr = frontPtr;
      // new list pointer
      // newPtr points to last node in new list
      // origPtr points to nodes in original list
      for (qnode *origPtr = aQueue.frontPtr->next;
	       origPtr != NULL;
           origPtr = origPtr->next)
      {
         newPtr->next = new qnode;
         newPtr = newPtr->next;
         newPtr->cat = origPtr->cat;
         newPtr->title = origPtr->title;
         newPtr->price = origPtr->price;
         newPtr->qty = origPtr->qty;
      }

      newPtr->next = NULL;
   }
}
    ~Queue()
    {
        while(!qEmpty())
        {
            dequeue();
        }
    }

    bool qEmpty()
    {
        return bool(backPtr == NULL);
    }

    int qLength()
    {
        return qSize;
    }

    void showList(string filename,string cat,string title,double price, int qty)
    {
        record::load(filename);
        record::displayAll(cat,title,price,qty);

    }

    void enqueue(string &cat,string &title, double &price, int &qty)
    {
     if(qEmpty())
    {
        frontPtr = new qnode;
        frontPtr -> cat = cat;
        frontPtr -> title = title;
        frontPtr -> qty = qty;
        frontPtr -> price = price;
        frontPtr -> next = NULL;
        backPtr = frontPtr;
    }
    else
    {
        qnode* newPtr = new qnode;
        newPtr -> cat = cat;
        newPtr -> title = title;
        newPtr -> qty = qty;
        newPtr -> price = price;
        newPtr -> next = NULL;
        backPtr -> next = newPtr;
        backPtr = newPtr;
    }
    qSize++;
    }

    void addToQueue(int index, string &cat, string &title,double &price, int &qty)
    {
        if(record::getQty(index)>0)
            {
                record::retrieve(index,cat,title,price,qty);
                enqueue(cat,title,price,qty);
                record::decreaseQty(index,cat,title,price,qty);
            }
        else
        {
            cout<<"Sorry, out of stock!"<<endl;
        }

    }

    void getFront()
    {
        string cat;
        string title;
        double price;
        if(qEmpty())
        {
            cout<<"Queue is empty!"<<endl;
        }
        else
        {
            cat = frontPtr->cat;
            title = frontPtr->title;
            price = frontPtr->price;
        }
        cout<<cat<<"\t"<<title<<"\t\t\t"<<price<<" ";
    }

    void dequeue()
    {
        if(qEmpty())
        {
            cout<<"No Items To Display"<<endl;
        }
        else
        {
            qnode *tempPtr = frontPtr;
            if(frontPtr == backPtr)
            {
                frontPtr = NULL;
                backPtr = NULL;
            }
            else
            {
                frontPtr = frontPtr -> next;
                tempPtr -> next = NULL;
                delete tempPtr;
            }
            qSize--;
        }
    }

    void displayQueue()
    {
        int i=1;
        cout<<"Item"<<" "<<"Category"<<"\t"<<"Title"<<"\t\t\t"<<"Sales Price(RM)"<<"\t"<< endl;
        cout<<"--------------------------------------------------------------------"<<endl;
        while(qLength() > 0)
        {
            cout<<i<<"\t";
            getFront();
            cout<<endl;
            dequeue();
            i++;
        }
    }
};

#endif // QUEUE_HPP

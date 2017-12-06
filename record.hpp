#ifndef RECORD_HPP
#define RECORD_HPP

#include <iostream>    // Only for displaying copy constructor
#include <iomanip>
#include <fstream>     // for file I/O
#include <sstream>
#include <cstddef>     // for NULL
#include <cstdlib>
#include <string>
#include <new>         // for bad_alloc
#include <regex>
#include "recordException.h"
#include "recordIndexOutOfRangeException.h"

using namespace std;
//-----------------------------------------------------------LINKED LIST--------------------------------------------------------------
class record
{
private:
     struct node
    {
        int qty;
        string cat;
        string title;
        double price;
        node *next;
    };
    int size;
    node *head;

public:

record() : size( 0 ), head( NULL )
{
}

~record()
{
   while (!isEmpty())
      remove(1);
}

record(const record &aRecord):size(aRecord.size)
{
    if ( aRecord.head == NULL )
   {
      head = NULL;  // original list is empty
   }
   else
   {
      // copy first node
      head = new node;
      head->cat = aRecord.head->cat;
      head->title = aRecord.head->title;
      head->qty = aRecord.head->qty;
      head->price = aRecord.head->price;


      // copy rest of list
      node *newPtr = head;
      // new list pointer
      // newPtr points to last node in new list
      // origPtr points to nodes in original list
      for (node *origPtr = aRecord.head->next;
	       origPtr != NULL;
           origPtr = origPtr->next)
      {
         newPtr->next = new node;
         newPtr = newPtr->next;
         newPtr->cat = origPtr->cat;
         newPtr->title = origPtr->title;
         newPtr->price = origPtr->price;
         newPtr->qty = origPtr->qty;
      }

      newPtr->next = NULL;
   }
}


bool isEmpty() const
{
   return size==0 ;
}

int getLength() const
{
   return size;
}

//input index, return node
//helper function
node *find(int k) const
{
   if ( (k < 1) || (k > getLength()) )
      return NULL;

   else  // count from the beginning of the list.
   {
      node *cur = head;
      for (int skip = 1; skip < k; ++skip)
         cur = cur -> next;
      return cur;
   }  // end if
}  // end find

void retrieve(int index, string &cat, string &title,double &price, int &qty) const
   throw(recordIndexOutOfRangeException, recordException)
{
   if ( (index < 1) || (index > getLength()) )
      throw recordIndexOutOfRangeException(
	    "recordIndexOutOfRangeException: retrieve record out of range");
   else
   {  // get pointer to node, then data in node
      node *cur = find(index);
       cat = cur->cat;
       title = cur->title;
       price = cur->price;
       qty = cur->qty;
   }  // end if
}  // end retrieve

void insert(int index, string &cat, string &title,double &price, int &qty)
   throw(recordIndexOutOfRangeException, recordException)
{
   int newLength = getLength() + 1;

   if ( (index < 1) || (index > newLength) )
      throw recordIndexOutOfRangeException("recordIndexOutOfRangeException: insert record out of range");
   else
   {
      // try to create new node and place newItem in it
      try
      {
         node *newPtr = new node;
         newPtr->cat= cat;
         newPtr->title=title;
         newPtr->price=price;
         newPtr->qty= qty;
         size = newLength;

         // attach new node to list
         if (index == 1)
         {  // insert new node at beginning of list
            newPtr->next = head ;
            head = newPtr;
         }
         else
         {  node *prev = find(index-1);
            // insert new node after node
            // to which prev points
            newPtr->next = prev->next;
            prev->next = newPtr;
         }  // end if
      }  // end try
      catch (bad_alloc e)
      {
	    throw recordException(
	      "recordException: memory allocation failed on insert");
      }  // end catch
   }  // end if
}  // end insert

void remove(int index)
    throw(recordIndexOutOfRangeException, recordException)
{
   node *cur;

   if ( (index < 1) || (index > getLength()) )
      throw recordIndexOutOfRangeException(
	   "recordIndexOutOfRangeException: remove record out of range");
   else
   {
      --size;
      if (index == 1)
      {  // delete the first node from the list
         cur = head;  // save pointer to node
         head = head->next ;
      }

      else
      {  node *prev = find(index - 1);
         // delete the node after the node to which prev points
         cur = prev->next;  // save pointer to node
	     if((index+1)>getLength())
         {
             prev->next = NULL;
         }
         else
         {
            prev->next = find(index+1);;
         }

      }  // end if

    // return node to system
    cur->next = NULL;
    delete cur;
    cur = NULL;
    //cout<<"Record "<<index<<" successfully removed!"<<endl;
    for(int i=(index+1);i<getLength();i++)
    {
        index=index-1;
    }
   }  // end if
}  // end remove


void save( string fileName )
{
   ofstream outFile( fileName.c_str() );

   // traverse the list to the end, writing each item
   for (node *cur = head; cur != NULL; cur = cur->next)
   {
      outFile << cur->cat <<"\t"<<cur->title<<"\t\t"<<cur->price<<"\t"<<cur->qty<<endl;
   }
   cout<<"\n File successfully saved!\n\n"<<endl;
   outFile.close();
}

void load( string fileName ) throw( recordException )
{
    string line;
    string c;
    string t;
    double p;
    int q;

    ifstream inFile( fileName.c_str() );
    if (!inFile.is_open())
    {
        return;
    }

    while (!isEmpty())
    {
        remove(1);
    }

    size = 0;

    try
    {
    while(getline(inFile,line))
    {
        regex re("\\s*(\\S+)\\s+(\\S.*\\S)\\s+(\\d+)\\s+(\\d+)");
        smatch match;

            if (regex_match(line, match, re))
            //assign the values gotten from the string to the variables
            c=match[1].str();
            t=match[2].str();
            stringstream convertp(match[3].str());
            convertp>>p;
            stringstream convertq(match[4].str());
            convertq>>q;

            insert(1,c,t,p,q);

    }
    }
    catch (const bad_alloc &e)
    {
        throw recordException(
            "recordException: restore cannot allocate memory.");
    }


    inFile.close();
}


const void displayAll(string &cat, string &title,double &price, int &qty)
{
    cout<<"Index"<<" "<<"Category"<<"\t"<<"Title"<<"\t\t\t"<<"RM"<<"\t"<<"Qty" << endl;
         cout<<"--------------------------------------------------------------------------"<<endl;
         for( int i = 1; i <= getLength(); i++ )
         {
            retrieve( i, cat, title, price, qty );
            cout<<i<<"\t"<<cat<<"\t"<<title<<"\t\t"<<price<<"\t"<<qty<<endl;
         }
         cout<<endl;
}

void bubbleSort(string &cat,string &title,double &price, int &qty)
{
    node* tempC = new node;
    node* tempT = new node;
    node* tempP = new node;
    node* tempQ = new node;
    node* p1 = new node;
    node* p2 = new node;

//------------------------------------------------------BUBBLE SORT--------------------------------------------------------------------

    for(int i=0;i<=getLength();i++)
    {
        for(p1=head;p1->next != NULL;p1=p1->next)
        {
            p2=p1->next;
            if(p1->cat.substr() > p2->cat.substr())
            {
                tempT->title = p1->title;
                p1->title = p2->title;
                p2->title = tempT->title;

                tempP->price = p1->price;
                p1->price = p2->price;
                p2->price = tempP->price;

                tempQ->qty = p1->qty;
                p1->qty = p2->qty;
                p2->qty = tempQ->qty;

                tempC->cat = p1->cat;
                p1->cat = p2->cat;
                p2->cat = tempC->cat;
            }

            else if(p1->cat.substr() == p2->cat.substr() && p1->title.substr()>p2->title.substr())
            {
                tempT->title = p1->title;
                p1->title = p2->title;
                p2->title = tempT->title;

                tempP->price = p1->price;
                p1->price = p2->price;
                p2->price = tempP->price;

                tempQ->qty = p1->qty;
                p1->qty = p2->qty;
                p2->qty = tempQ->qty;
            }
        }
    }
}

    int getQty(int index)
    {
        string cat;
        string title;
        double price;
        int qty;

        retrieve(index,cat,title,price,qty);
        return qty;
    }
    void decreaseQty(int index, string &cat, string &title,double &price, int &qty)
    {
        retrieve(index,cat,title,price,qty);

        if(isEmpty())
        {
            return;
        }
        else
        {
            qty = qty - 1;
            remove(index);
            insert(index,cat,title,price,qty);
        }
    }
};
#endif

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
//---------------------------------------------------SELECTION SORT-----------------------------------------------------------------
using namespace std;

class CustomerLogin{
    private:
    string pass;
    char ch;
    int n_items = 6;

public:
    int getSize() const
    {
        return n_items;
    }

    void swap( string& x, string& y)
    {
        string temp = x;
        x = y;
        y = temp;
    }

    void displayArray( const string theArray[],int size)
    {
        for ( int i = 0; i < size; ++i )
        cout<<"\n "<<theArray[ i ] << " ";
    }

    int indexOfLargest( const string theArray[],int size)
    {
        int indLargest = 0;
        for(int curr = 1; curr < size+1; curr++)//take index 1 compare with index 0
        {
            if(theArray[curr]>theArray[indLargest])
            {
                indLargest = curr;
            }

        }
        return indLargest;
    }

    void selectionSort( string theArray[], int n )
    {
        for(int last = n-1;last>=1;last--)
        {
            int indLargest = indexOfLargest(theArray,last);
            swap(theArray[indLargest],theArray[last]);
        }
    }

    //void CustomerLogin();

};

#endif // CUSTOMER_HPP

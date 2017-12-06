#include "interface.hpp"
#include "record.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "customer.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <regex>
#include <ctime>

using namespace std;

record d;
Queue q;
Stack s;
CustomerLogin t;
int index,qty;
string cat,title;
double price;

string filename = "hello.dat";
string user;
string pass;
string a[ ]= { "Lilian","Weening","Bob","Jane","Justine","Qian"};

void Interface::welcome()
{
    cout<<"\t\t\t----------------------------------------------------------\n\n";
    cout<<"\t\t\t     Welcome to BlockBuster Video Rental Store!!!\n\n";
    cout<<"\t\t\t----------------------------------------------------------\n\n";
}

void Interface::mainMenu()
{
    cout<<"\n\n\n ------------Main Menu----------\n\n\n";

    cout<<" What would you like to do today?"<<endl
        <<" 1. Buy an item"<<endl
        <<" 2. Rent an item"<<endl
        <<" 3. Administrator Login"<<endl
        <<" 4. Exit"<<endl<<endl
        <<" Please indicate your choice:  ";
}

void Interface::adminMenu()
{
    system("cls");
    string filename;
    string password;
    string pass = "admin";
    char achoice;
    cout << "\n\tPlease key in the password: ";
    cin >> password;

    if(password == pass)
    {
        system("cls");
        do
        {
        cout<<"\n -----------Administrator Menu----------\n\n\n"
            <<" 1. Load and display the database from a file\n"
            <<" 2. Add a record to the main database\n"
            <<" 3. Remove a record from the main database\n"
            <<" 4. Display all subscribed customers\n"
            <<" 5. Back to main menu\n\n"
            <<" What would you like to do? Choice: ";
        cin>>achoice;
        cout<<endl;

        switch(achoice)
        {
            case '1':
            {
                cout<<"Type in filename.extension: ";
                cin>>filename;
                cout<<endl;
                d.load(filename);
                d.bubbleSort(cat,title,price,qty);
                d.displayAll(cat,title,price,qty);
                d.save(filename);

                break;
            }
            case '2':
            {
                cout<<"Type in filename.extension: ";
                cin>>filename;
                d.load(filename);
                cout<<endl;
                d.displayAll(cat,title,price,qty);

                cout<<"\n ---Add a new record to this file---\n\n"<<endl;
                cin.ignore();
                cout<<" Category: ";
                getline(cin,cat);
                cout<<" Title: ";
                getline(cin,title);
                cout<<" Price: ";
                cin>>price;
                cout<<" Quantity of records: ";
                cin>>qty;

                d.insert( d.getLength() + 1, cat,title,price,qty);
                cout<<endl;
                d.displayAll(cat,title,price,qty);
                d.save(filename);

                break;
            }
            case '3':
            {
                cout<<" Type in filename.extension: ";
                cin>>filename;
                d.load(filename);
                cout<<endl;
                d.displayAll(cat,title,price,qty);
                cout<<"\n ---Delete a record from this file---\n\n"<<endl;
                cout<<" Which record would you like to remove? Choice: ";
                cin>>index;
                d.remove(index);
                cout<<endl;
                d.displayAll(cat,title,price,qty);
                d.save(filename);

                break;
            }
//---------------------------------------------------SELECTION SORT-----------------------------------------------------------------
            case '4':
            {
                //display all customers
                int asize = t.getSize();
                t.selectionSort( a, asize );
                cout << "List of Subscribed Customers : ";
                t.displayArray( a, asize );
                cout <<endl;
                break;
            }

            case '5':
            {
                system("cls");
                return;
            }
        }
        }
        while (achoice != '5');
    }
    else
    {
        cout << "Wrong password! Unauthorized access!" << endl;
        return;
    }
}

void Interface::quit()
{
    system("cls");
    cout<<"\n\n\t\t\t--------------------------------------------------------------------\n\n";
    cout<<"\t\t\t Thank you and have a nice day! From the folks at Blockbuster & Co.\n\n";
    cout<<"\t\t\t--------------------------------------------------------------------\n\n";
}

void Interface::buyMenu()
{
    int boption;
    char bchoice = 'Y';
    cout.precision(2);
    double sum = 0;

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d/%m/%Y  %H:%M:%S%p",timeinfo);
    string show_time(buffer);

    system("cls");
    cout<<"\n ----------Sales Menu----------\n\n\n";
    q.showList(filename,cat,title,price,qty);
    cout<<endl<<endl;
    do
    {
    cout<<"\nWhich item would you like to buy? Choice: ";
    cin>>boption;
    q.addToQueue(boption,cat,title,price,qty);
    s.push(boption,cat,title,price,qty,filename);

    cout<<"\nWould you like to buy another item?(Y/N) :";
    cin>>bchoice;
    }
    while(bchoice == 'Y'|| bchoice == 'y');
    q.save(filename);
    while(s.getLength() != 0)
    {
    sum = sum + s.getTop();
    s.pop();
    }
    system("cls");
    cout<<"\n\n\n";
        cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout<<"\n\n Sales Receipt for "<<show_time;
    cout<<"\n\n--------------------------------------------------------------------\n\n";

    q.displayQueue();
    q.save(filename);
    cout<<"\n Total price is: RM "<<fixed<<sum*1.06<<" including 6% GST";
    cout<<"\n\n\n\n";
    cout<<" *****Thank you and please come again!*****";
    cout<<"\n\n\n";
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    return;
}

void Interface::rentMenu()
{
    int roption;
    char rchoice = 'Y';
    int rCount = 0;
    int rNo = 0;
    cout.precision(2);

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%d/%m/%Y  %H:%M:%S%p",timeinfo);
    string show_time(buffer);


    system("cls");
    cout<<"\n ----------Rent Menu----------\n\n\n";
    q.showList(filename,cat,title,price,qty);
    cout<<endl<<endl;
    do
    {
    cout<<"\nWhich item would you like to rent? Choice: ";
    cin>>roption;

    q.addToQueue(roption,cat,title,price,qty);

    cout<<"\nWould you like to rent another item?(Y/N) :";
    cin>>rchoice;
    rCount++;
    rNo++;
    }
    while((rchoice == 'Y' && rCount < 3 )|| (rchoice == 'y' && rCount < 3));

    cout<<"\n\n\n";
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout<<"\n\n Rent Receipt for "<<show_time;
    cout<<"\n--------------------------------------------------------------------\n\n";

    q.displayQueue();
    q.save(filename);
    cout<<"\n Total price is: RM ";
    cout<<fixed<<(rNo * 5)*1.06<<" including 6% GST";
    cout<<"\n\n\n\n";
    cout<<" The due date is 14 days from "<<show_time<<endl;
    cout<<" *****Thank you and please come again!*****";
    cout<<"\n\n\n";
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";

    return;
}

void Interface::login()
{
    char ch;

    cout<<"\t\t\t----------------------------------------------------------"<<endl;
    cout<<"\t\t\t                       CUSTOMER LOGIN"<<endl;
    cout<<"\t\t\t----------------------------------------------------------"<<endl<<endl;
    cout<<"\t\t\tPlease Enter Login ID: ";
    cin>>user;
    cout<<endl<<"\t\t\tPlease Enter Password: ";
    while((ch=_getch()) != 13)
    {//character 13 is enter
    if (ch == 8)
		{
			if (pass.length() > 0)
			{
				pass.erase(pass.length()-1);
				cout << "\b \b"; // backspace and clear
			}
		}
		else
		{
            pass.push_back(ch);
            cout << '*';
        }
      }

    if((user=="Lilian" )&& (pass=="lilianpass"))
    {
        system("cls");
        cout<<"\n\n\n\t\t\t\t\t\t-----Login Successfully!!-----"<<endl;
        rentMenu();
    }
    else if ((user=="Weening" )&& (pass=="weeningpass"))
    {
        system("cls");
        cout<<"\n\n\n\t\t\t\t\t\t-----Login Successfully!!-----"<<endl;
        rentMenu();
    }
    else if((user=="Bob" )&& (pass=="bobpass"))
    {
        system("cls");
        cout<<"\n\n\n\t\t\t\t\t\t-----Login Successfully!!-----"<<endl;
        rentMenu();
    }
    else if((user=="Jane" )&& (pass=="janepass"))
    {
        system("cls");
        cout<<"\n\n\n\t\t\t\t\t\t-----Login Successfully!!-----"<<endl;
        rentMenu();
    }
    else if((user=="Justine" )&& (pass=="justinepass"))
    {
        system("cls");
        cout<<"\n\n\n\t\t\t\t\t\t-----Login Successfully!!-----"<<endl;
        rentMenu();
    }
    else if((user=="Qian")&& (pass=="qianpass"))
    {
        system("cls");
        cout<<"\n\n\n\t\t\t\t\t\t-----Login Successfully!!-----"<<endl;
        rentMenu();
    }

    else
    {
        cout<<"\n\n\n\t\t\t\t\t\t-----Please Try Again!-----"<<endl;
        system("cls");
        mainMenu();
    }
}

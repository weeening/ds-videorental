#include<iostream>
#include<cstdlib>
#include "record.hpp"
#include "interface.hpp"
//#include "sales.hpp"
//#include "rent.hpp"
#include "customer.hpp"
#include<regex>

using namespace std;

int main()
{

    Interface int1;
    char choice;
    bool done = false;

    int1.welcome();


    do
    {
        int1.mainMenu();
        cin >> choice;
        system("cls");

        switch(choice)
        {
            case '1' :
                    {
                        int1.buyMenu();
                        break;
                    }

            case '2' :
                    {
                        int1.login();
                        break;
                    }

            case '3' :
                    {
                        int1.adminMenu();
                        break;
                    }

            case '4' :
                    {
                        int1.quit();
                        done = true;
                        break;
                    }
            default :
                    {
                        cout << "Please input your choice (1-4): " << endl << endl;
                        system("pause");
                        break;
                    }

        }
    }while(!done);

    return 0;
}

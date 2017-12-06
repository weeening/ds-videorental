#ifndef interface_HPP
#define interface_HPP

#include "record.hpp"
#include "customer.hpp"
#include<string>

class Interface : public record
{
public:
    void mainMenu();
    void adminMenu();
    void welcome();
    void quit();
    void buyMenu();
    void rentMenu();
    void login();

};

#endif





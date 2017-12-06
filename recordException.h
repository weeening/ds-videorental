#ifndef RECORDEXCEPTION_H
#define RECORDEXCEPTION_H


#include <stdexcept>
#include <string>

using namespace std;

class recordException : public logic_error
{
public:
   recordException(const string & message = "")
      : logic_error(message.c_str())
   { }  // end constructor
}; // end ListException

#endif

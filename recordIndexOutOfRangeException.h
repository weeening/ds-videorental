#ifndef RECORDINDEXOUTOFRANGEEXCEPTION_H
#define RECORDINDEXOUTOFRANGEEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class recordIndexOutOfRangeException : public out_of_range
{
public:
   recordIndexOutOfRangeException(const string & message = "")
      : out_of_range(message.c_str())
   { }  // end constructor
}; // end ListIndexOutOfRangeException

#endif

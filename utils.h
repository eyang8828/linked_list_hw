#ifndef utila_h
#define utila_h

#include <stdbool.h>

const char* yesorno(bool condition) {
  static char yes[] = "YES";
  static char no[]  = "NO";

  return condition ? yes : no;
}


#endif /* utila_h */

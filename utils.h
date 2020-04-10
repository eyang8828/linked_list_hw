//
//  utila.h
//  linked_list
//
//  Created by William McCarthy on 094//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef utila_h
#define utila_h

#include <stdbool.h>

const char* yesorno(bool condition) {
  static char yes[] = "YES";
  static char no[]  = "NO";

  return condition ? yes : no;
}


#endif /* utila_h */

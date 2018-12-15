#ifndef STATE_H
#define STATE_H

#include <time.h>

struct State ; /* Forward declaration */

typedef struct State
{
  time_t timeStamp;
  int intervalInSeconds;
  int counter;
} State ;

#endif

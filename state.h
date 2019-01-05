#ifndef STATE_H
#define STATE_H

#include <time.h>

struct State ; /* Forward declaration */

typedef struct State
{
  time_t timeStamp;
  double intervalInSeconds;
  int counter;
} State ;

#endif

#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include "state.h"

void clearMemory();

void saveState(int address, State* state);

bool readState(int* nextAddress, State* state);

#endif

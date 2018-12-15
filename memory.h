#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include "state.h"

void saveState(int address, State* state);

bool readState(int* address, State* state);

#endif

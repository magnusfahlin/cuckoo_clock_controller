
#include "memory.h"
#include <EEPROM.h>

void clearMemory()
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    if(EEPROM.read(i) != 0)                     //skip already "empty" addresses
    {
      EEPROM.write(i, 0);                       //write 0 to address i
    }
  }
}

void saveState(int address, State* state) {
  if (address + sizeof(State) > EEPROM.length())
  {
    clearMemory();
  }
  
  EEPROM.begin(512);
  EEPROM.put(address, &state);
  address = address + sizeof(State);
  EEPROM.commit();
  EEPROM.end();
}

bool readState(int* address, State* state) {
  *address = 0;
  bool result = false;
  EEPROM.begin(512);
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    State readState;
    EEPROM.get(i, readState);
    if (readState.counter != 0) {
      memcpy((void*)&readState, (void*)&state, sizeof(State));
      *address = i;
      result = true;
      break;
    }
    i = i + sizeof(State);
    if (i > EEPROM.length())
      break;
   }
   
  EEPROM.end();
  return result;
}

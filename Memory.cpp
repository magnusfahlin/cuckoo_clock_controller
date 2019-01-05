
#include <SoftwareSerial.h>
#include "memory.h"
#include "logger.h"
#include <EEPROM.h>
#include <time.h>

void clearMemory()
{
  EEPROM.begin(512);
  logger("Clear memory");
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    if(EEPROM.read(i) != 0)                     //skip already "empty" addresses
    {
      EEPROM.write(i, 0);                       //write 0 to address i
    }
  }
  EEPROM.commit();
  EEPROM.end();
  logger("Memory cleared");
}

void saveState(int address, State* state) {
  char str[120];
  sprintf(str, "Save address = %i counter = %i, interval = %lf, time= %s", address, state->counter, state->intervalInSeconds, ctime(&(state->timeStamp)));
  logger(str);

  EEPROM.begin(512);
  if (address + sizeof(State) > EEPROM.length())
  {
    clearMemory();
    return;
  }
  
  EEPROM.put(address, *state);
  address = address + sizeof(State);
  EEPROM.commit();
  EEPROM.end();
}

bool readState(int* nextAddress, State* state) {

  *nextAddress = 0;
  bool result = false;
  EEPROM.begin(512);

  int i = 0;
  while(i < EEPROM.length())
  {
    State readState;
    EEPROM.get(i, readState);
    if (readState.counter != 0) {
      memcpy((void*)state, (void*)&readState, sizeof(State));
      *nextAddress = i + sizeof(State);
      result = true;
    }
    i = i + sizeof(State);
    
    if (i > EEPROM.length())
      break;
  }

   
  EEPROM.end();

  char str[120];
  sprintf(str, "Read nextAddress = %i counter = %i, interval = %lf, time= %s", *nextAddress, state->counter, state->intervalInSeconds, ctime(&(state->timeStamp)));
  logger(str);
  return result;
}

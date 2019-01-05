#include "logger.h"
#include "logger.h"
#include <ESP8266WiFi.h>
#include <time.h>

bool tryGetCurrentTime(time_t* currentTime)
{
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  for(int i=0; i<5; i++)
  {
    *currentTime = time(nullptr);

    char str[120];
    sprintf(str, "tryGetCurrentTime %i time= %s year = %i", i, ctime(currentTime), gmtime(currentTime)->tm_year);
    logger(str);
  
    if (gmtime(currentTime)->tm_year == 70) // The year is 1970, not likley...
    {
       logger("Failed to get time try once more");
    } 
    else
    {
      return true;
    }
  }
  return false;
}

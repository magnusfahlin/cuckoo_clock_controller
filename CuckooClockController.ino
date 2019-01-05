#include <ESP8266WiFi.h>
#include <time.h>
#include "currenttime.h"
#include "state.h"
#include "memory.h"
#include "logger.h"

const char* ssid = "***";
const char* password = "***";

int timezone = 3;
int dst = 0;


void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(2000);
  } 
  Serial.println("");
  clearMemory();
}

void loop() {
  time_t now;
  double intervalInSeconds = -1;
  State previousState = {now, intervalInSeconds, 0};
  int address = 0;
  logger("Trying to read previous state");
  
  if(readState(&address, &previousState))
  {
    if (previousState.counter == 1)
    {
      time_t newTime;
      if (!tryGetCurrentTime(&newTime))
      {
        clearMemory();
        return;
      }
      intervalInSeconds = difftime(newTime, previousState.timeStamp);
    }
    if (previousState.counter > 1)
    {
      intervalInSeconds = previousState.intervalInSeconds;
    }
    now = previousState.timeStamp + intervalInSeconds;
  } else {
      logger("failed to read previous state read");
      if (!tryGetCurrentTime(&now))
      {
        delay(2000);
        return;
      }
  }
  
  State state = {now, intervalInSeconds, previousState.counter + 1} ;
  saveState(address, &state);
  
  Serial.println("Klockan är UTC:");
  Serial.println(ctime(&now));
  Serial.println("Nu väntar vi");
  delay(2000);
}

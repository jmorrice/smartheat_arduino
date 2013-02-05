#include <WiFlyHQ.h>
#include <SoftwareSerial.h>

WiFly wifly;

/* For Debugging */
SoftwareSerial debug(10, 11);

/* FSM */
enum state {INIT, WAIT, CONNECT, SEND, EXIT};
state STATE = INIT;

void setup()
{
  wifi_init();
  
  //softwareserial for debugging
  debug.begin(9600);
}

void loop()
{
  //to debug server response
  while (wifly.available()) 
  {
    char c = wifly.read();
    debug.print(c);
  }
  
  switch(STATE)
  {
    case INIT:
      debug.println("State: Init");
      //next state
      STATE = CONNECT;
      break;
    
    case CONNECT:
      debug.println("State: Connect");
      wifly.setOUTPUT("0x20 0x70");
      if(wifi_connect())
        STATE = SEND;
      break;
      
    case SEND:
      debug.println("State: Send");
      wifly.setOUTPUT("0x30 0x70");
      if(wifi_send())
      {
        wifly.setOUTPUT("0x10 0x70");
        STATE = EXIT;
      }
      else
      {
        wifly.setOUTPUT("0x40 0x70");
        STATE = EXIT;
        debug.println("State: Exit");
      }
      break;
  }
}
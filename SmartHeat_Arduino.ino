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
  //wifi_init();
  zilog_init();
  //softwareserial for debugging
  debug.begin(9600);
  //temp_init();
}

void loop()
{
  //to debug server response
  //wifi_read();
  
  switch(STATE)
  {
    case INIT:
      //debug.println("State: Init");
      //next state
      if(zilog_detect_motion())
        digitalWrite(13, HIGH);
      else
        digitalWrite(13, LOW);
      delay(100);
      //debug.println(temp_read());
      //STATE = CONNECT;
      //STATE = EXIT;
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
        debug.println("State: Exit");
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

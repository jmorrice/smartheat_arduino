#include <WiFlyHQ.h>
#include <SoftwareSerial.h>
#include <Timer.h>

WiFly wifly;

/* For Debugging */
SoftwareSerial debug(10, 11);

/* FSM */
Timer t;
int timer_event_id;
enum state {INIT, WAIT, CONNECT, SEND, SLEEP, WAKE, EXIT};
state STATE = INIT;

/* Flags */
boolean SLEEP_FLAG = false;

/* Timeouts */
unsigned int ATTEMPTS = 0;
unsigned int MAX_ATTEMPTS = 3;

void setup()
{
  //softwareserial for debugging (not compatible with zmotion)
  debug.begin(9600);
  debug.println("setup");
  wifi_init();
  //zilog_init();
  temp_init();
  
  timer_event_id = t.every(120000, upload); //every 2 minutes
}

void loop()
{
  debug.println("loop");
  //to debug server response
  wifi_read();
  
  t.update();
  
  switch(STATE)
  {
    case INIT:
      debug.println("State: Init");
      //next state
      STATE = SLEEP;
      break;
    
    //TODO: add connect timeout
    case CONNECT:
      debug.println("State: Connect");
      wifly.setOUTPUT("0x20 0x70");
      if (!wifly.isAssociated())
      {
        if(wifi_connect())
          STATE = SEND;
      }
      else
        STATE = SEND;
      break;
      
    case SLEEP:
      debug.println("send to sleep...");
      if(!SLEEP_FLAG)
      {
        wifi_sleep();
        SLEEP_FLAG = true;
      }
      break;
      
    case WAKE:
      debug.println("waking up...");
      wifi_wake();
      STATE = SEND;
      break;
      
    case SEND:
      debug.println("State: Send");
      wifly.setOUTPUT("0x30 0x70");
      if(wifi_send(temp_read()))
      {
        wifly.setOUTPUT("0x10 0x70");
        ATTEMPTS = 0;
        STATE = SLEEP;
      }
      else
      {
        if(ATTEMPTS < MAX_ATTEMPTS)
          ATTEMPTS++;
        else
        {
          ATTEMPTS = 0;
          wifly.setOUTPUT("0x40 0x70");
          STATE = SLEEP;
        }
      }
      break;
      
    case EXIT:
      t.stop(timer_event_id);
      wifly.factoryRestore();
      break;
  }
}

void upload()
{
  debug.println("timerevent");
  SLEEP_FLAG = false;
  STATE = WAKE;
}

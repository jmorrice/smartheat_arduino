#include <WiFlyHQ.h>
#include <SoftwareSerial.h>
#include <Timer.h>

WiFly wifly;

/* Sensor values */
boolean presence_array [30];

/* Settings */ //be aware of also changing sample bufer size (below) and watchdog timer (in sleep file)
unsigned int t_transmit_min = 2;  //transimission period in minutes
unsigned int t_transmit = t_transmit_min * 60;  //in seconds
unsigned int t_motion = 4;    //motion sample period in seconds
unsigned int motion_thresh = 3;  //threshold for motion detection

/* Serial for ZMotion detection */
SoftwareSerial zilog(2, 3);

/* For Debugging */
//SoftwareSerial debug(10, 11);

/* FSM */
enum state {INIT, READ, CONNECT, SEND, SLEEP, WAKE, EXIT};
state STATE = INIT;
unsigned int sample_count = 0;

/* Flags */

/* Timeouts */
unsigned int ATTEMPTS = 0;
unsigned int MAX_ATTEMPTS = 3;

void setup()
{
  //softwareserial for debugging (not compatible with zmotion)
  //debug.begin(9600);
  //debug.println("setup");
}

void loop()
{
  //debug.println("loop");
  //to debug server response
  //wifi_read();
  
  switch(STATE)
  {
    case INIT:
      //debug.println("State: Init");
      wifi_init();
      temp_init();
      zilog_init();
      sample_count = 0;
      
      wifi_sleep();
      STATE = READ;
      break;
      
    case READ:
      presence_array[sample_count] = zilog_detect_motion();
      sample_count++;
      STATE = SLEEP;
      break;
    
    //TODO: add connect timeout
    case CONNECT:
      //debug.println("State: Connect");
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
      //debug.println("send to sleep...");
      avr_sleep();
      STATE = WAKE;
      break;
      
    case WAKE:
      if(sample_count * t_motion >= t_transmit)
      {
        //wifly.println(sample_count);
        //wifly.println(t_motion);
        //wifly.println(t_transmit);
        wifi_wake();
        STATE = SEND;
      }
      else  
        STATE = READ;
      break;
      
    case SEND:
      //debug.println("State: Send");
      wifly.setOUTPUT("0x30 0x70");
      if(wifi_send(temp_read(), zilog_process(&presence_array[0], motion_thresh)))
      //if(wifi_send(temp_read(), 1))
      {
        wifly.setOUTPUT("0x10 0x70");
        ATTEMPTS = 0;
        sample_count = 0;
        wifi_sleep();
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
          sample_count = 0;
          wifi_sleep();
          STATE = SLEEP;
        }
      }
      break;
      
    case EXIT:
      wifly.factoryRestore();
      break;
  }
}

void upload()
{
  //debug.println("timerevent");
  STATE = WAKE;
}

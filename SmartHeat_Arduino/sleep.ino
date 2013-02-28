#include <LowPower.h>

void avr_sleep()
{
  LowPower.powerDown(SLEEP_4S, //change according to motion sample period
                     ADC_OFF, 
                     BOD_OFF);
}

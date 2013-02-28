#include <avr/wdt.h>

void timeout_start()
{
  wdt_enable(WDTO_8S);
}

void timeout_stop()
{
  wdt_reset();
  wdt_disable();
}

/* LED Pin */
int led = 13;

void set_green_led(boolean status)
{
  if(status)
    //wifly.enableGreenLED();
    wifly.setOUTPUT("0x10 0x10");
  else
    wifly.setOUTPUT("0x00 0x10");
}

void set_yellow_led(boolean status)
{
  if(status)
    wifly.setOUTPUT("0x20 0x20");
  else
    wifly.setOUTPUT("0x00 0x20");
}

void set_red_led(boolean status)
{
  if(status)
    wifly.setOUTPUT("0x40 0x40");
  else
    wifly.setOUTPUT("0x00 0x40");
}

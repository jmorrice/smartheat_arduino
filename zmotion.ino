void zilog_init()
{
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  zilog.begin(9600);
}

void zilog_debug()
{
  if (zilog.available())
    Serial.print((char)zilog.read());
  if (Serial.available())
    zilog.print((char)Serial.read());
}

//TODO: add sleep functionality
//TODO: add error/warmup detection
boolean zilog_detect_motion()
{
  boolean output = false;
  
  zilog.print("a");
  delay(1);
  if(zilog.available())
  {
    if((char)zilog.read() == 'Y')
      output = true;
  }
  
  return output;
}

boolean zilog_process(boolean *values, unsigned int thresh)
{
  unsigned int sum = 0;
  for(int i = 0; i < (t_transmit/t_motion); i++)
    sum += values[i];
    
  if(sum >= thresh)
    return true;
  else
    return false;  
}

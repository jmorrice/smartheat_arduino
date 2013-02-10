/* Serial for ZMotion detection */
SoftwareSerial zilog(2, 3);

void zilog_init()
{
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  zilog.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
}

void zilog_debug()
{
  if (zilog.available())
    Serial.print((char)zilog.read());
  if (Serial.available())
    zilog.print((char)Serial.read());
}

boolean zilog_detect_motion()
{
  zilog.print("a");
  if(zilog.available())
  {
    char c = zilog.read();
    if(c == 'Y')
      return true;
    else
      return false; 
  }
  else
    return false;
}

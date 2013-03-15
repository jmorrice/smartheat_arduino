#include <Wire.h>

/* Device Adress */
int adr_temp = 31; //0x1F or 0b11111

void temp_init()
{
  Wire.begin();
}

double temp_read_old()
{
  Wire.beginTransmission(adr_temp);
  Wire.write(byte(0x05));  //request ambient temperature
  Wire.endTransmission();
  
  Wire.requestFrom(adr_temp, 2);
  if(Wire.available() >= 2)
  {
    byte upperByte, lowerByte;
    upperByte = Wire.read();
    lowerByte = Wire.read();
    //debug.println(upperByte);
    //debug.println(lowerByte);
    return temp_convert(upperByte, lowerByte);
  }
  else
  {
    Serial.println("error");
    return double(0); //error
  }
}

double temp_convert(byte upper, byte lower)
{
  double temp;
  //check flag bits
  if((upper & byte(0x80)) == byte(0x80))
  {
  }
  if((upper & byte(0x40)) == byte(0x40))
  {
  }
  if((upper & byte(0x20)) == byte(0x20))
  {
  }
  
  //clear flag bits
  upper = upper & byte(0x1F);
  
  if((upper & byte(0x10)) == byte(0x10))
  {
    upper = upper & byte(0x0F);  //clear sign
    temp = 256 - ((upper * 16.0) + (lower / 16.0));
  }
  else
    temp = (upper * 16.0) + (lower / 16.0);

  return temp;
}

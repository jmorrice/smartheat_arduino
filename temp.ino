#include <Wire.h>

/* Device Adress */
int adr = 31; //0x1F or 0b11111

void temp_init()
{
  Wire.begin();
}

int temp_read()
{
  Wire.beginTransmission(adr);
  Wire.write(byte(0x05));  //request ambient temperature
  Wire.endTransmission();
  
  Wire.requestFrom(adr, 2);
  if(Wire.available() >= 2)
  {
    byte upperByte, lowerByte;
    upperByte = Wire.read();
    lowerByte = Wire.read();
    debug.println(upperByte);
    debug.println(lowerByte);
    return temp_convert(upperByte, lowerByte);
  }
  else
    return int(0); //error
}

float temp_convert(byte upper, byte lower)
{
  float temp;
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
    temp = 256 - ((upper * 16) + (lower / 16));
  }
  else
    temp = (upper * 16) + (lower / 16);
    
  return temp;
}

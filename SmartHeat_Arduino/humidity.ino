#include <Wire.h>

/* Device Adress */
int adr_hum = 0x27; //0x1F or 0b11111

void temp_hum_init()
{
  Wire.begin();
}

double hum_read()
{ 
  Wire.beginTransmission(adr_hum);
  Wire.endTransmission(adr_hum);
  delay(40); //wait for measurements
  
  Wire.requestFrom(adr_hum, 4);
  if(Wire.available() >= 4)
  {
    byte HupperByte = Wire.read();
    byte HlowerByte = Wire.read();
    byte TupperByte = Wire.read();
    byte TlowerByte = Wire.read();

    int hum_count = (HupperByte & byte(0x3F)) << 8 | HlowerByte;
    return hum_count / 16382.0 * 100.0;
  }
  else
    return double(0); //error
}

double temp_read()
{ 
  Wire.beginTransmission(adr_hum);
  Wire.endTransmission(adr_hum);
  delay(40); //wait for measurements
  
  Wire.requestFrom(adr_hum, 4);
  if(Wire.available() >= 4)
  {
    byte HupperByte = Wire.read();
    byte HlowerByte = Wire.read();
    byte TupperByte = Wire.read();
    byte TlowerByte = Wire.read();
    
    int temp_count = TupperByte << 6 | TlowerByte >> 2;
    return temp_count * 165.0 / 16382.0 - 40.0;
  }
  else
    return double(0); //error
}

double ldr_read()
{
  int adc_out = analogRead(1);
  double lum = 100.0 * adc_out/1023.0;
  return 100 - lum;  //return in %
}

void ldr_debug()
{
  Serial.print("Brightness: ");
  Serial.println(ldr_read());
}

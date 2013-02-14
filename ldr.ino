double ldr_read()
{
  int adc_out = analogRead(1);
  return (double)5.0 * adc_out/1023.0;
}

void ldr_debug()
{
  Serial.println(ldr_read());
}

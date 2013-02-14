#define analogPin      0          // analog pin for measuring capacitor voltage
#define chargePin      6         // pin to charge the capacitor - connected to one end of the charging resistor
#define dischargePin   5         // pin to discharge the capacitor
#define resistorValue  6800000.0F   // change this to whatever resistor value you are using
                                  
float startTime;
float elapsedTime;
double picoFarads;                // floating point variable to preserve precision, make calculations
double nanoFarads;

void humidity_init()
{
  pinMode(chargePin, OUTPUT);     // set chargePin to output
  digitalWrite(chargePin, LOW);  
}

double get_capacitance()
{
  digitalWrite(chargePin, HIGH);  // set chargePin HIGH and capacitor charging
  startTime = micros();

  while(analogRead(analogPin) < 648);       // 647 is 63.2% of 1023, which corresponds to full-scale voltage 

  elapsedTime= micros() - startTime;
 // convert microseconds to seconds ( 10^-6 ) and Farads to picoFarads ( 10^12 ),  net 10^3 (1000)  
  picoFarads = ((double)elapsedTime / resistorValue) * 1000000;   

  /* dicharge the capacitor  */
  digitalWrite(chargePin, LOW);             // set charge pin to  LOW 
  pinMode(dischargePin, OUTPUT);            // set discharge pin to output 
  digitalWrite(dischargePin, LOW);          // set discharge pin LOW 
  while(analogRead(analogPin) > 0);         // wait until capacitor is completely discharged
  pinMode(dischargePin, INPUT);            // set discharge pin back to input
  
  return picoFarads;
}

int humidity_read()
{
  double cap = get_capacitance();
  if(cap > 390.0)
    return 100;
  else if(cap < 270.0)
    return 0;
  else
    return (int)((cap - 270.0)/ 120.0 * 100);
}

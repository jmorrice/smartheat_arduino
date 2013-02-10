/* Change these to match your WiFi network */
//const char mySSID[] = "Jonny_iPhone";
//const char myPassword[] = "mdv2posh4u";
const char mySSID[] = "virginmedia8629341";
const char myPassword[] = "pqclfnwp";

/* FE Server */
IPAddress server(152,78,189,14);

/* Test data to send */
//int h = 20;

boolean wifi_init()
{
  //init serial communication to wifi module
  Serial.begin(9600);
  if(!wifly.begin(&Serial, NULL))
  {
    //error handling
    return false;
  }
  else
  {
    //init leds
    wifly.setIOFUNC("0x70");
    wifly.setOUTPUT("0x00 0x70");
    
    //init wifi
    wifly.setAUTH("4");
    wifly.setSSID(mySSID);
    wifly.setPassphrase(myPassword);
    return true;
  }
}

boolean wifi_connect()
{
  debug.println("Joining network");
  if (wifly.join()) 
  {
     //connected
     debug.println("Joined wifi network");
     return true;
     //led_on();
  } 
  else 
  {
    //error handling
    debug.println("Failed to join wifi network");
    return false;
  }
}

boolean wifi_send(int temp)
{      
  if (wifly.open(server, 80))  
  {
    debug.print("Connected to ");
    debug.println(server);
    
    
    //Send the request
    wifly.println("POST //fe/rawinput/sensor/00-06-66-80-EC-76/temperature/data/ HTTP/1.1");
    //wifly.println("POST //fe/rawinput/sensor/90-A2-DA-00-ED-21/temperature/data/ HTTP/1.1");
    wifly.println("Host: hai.ecs.soton.ac.uk");
    wifly.println("Accept: */*");
    wifly.println("Content-Length: " + String(getLength(temp) + 28));
    wifly.println("Content-Type: application/x-www-form-urlencoded");
    wifly.println();
    String data = String("value=" + String(temp));
    //debug.println(data);
    wifly.println(data + String("&key=00-06-66-80-EC-76"));
    //wifly.println(data + String("&key=90-A2-DA-00-ED-21"));
    wifly.println();
    wifly.println();

    //read response
    delay(5000);
    wifi_read();
    return true;
  }
  else
  {
    //error
    debug.println("Failed to connect");
    return false;
  }
}

void wifi_read()
{
    while (wifly.available() > 0) 
    {
      //debug.println("reading byte...");
      char c = wifly.read();
      debug.print(c);
    }
}

int getLength(int someValue) 
{
  // there's at least one byte:
  int digits = 1;
  // continually divide the value by ten, 
  // adding one to the digit count for each
  // time you divide, until you're at 0:
  int dividend = someValue /10;
  while (dividend > 0) 
  {
    dividend = dividend /10;
    digits++;
  }
  // return the number of digits:
  return digits;
}

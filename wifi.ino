/* Change these to match your WiFi network */
const char mySSID[] = "Jonny_iPhone";
const char myPassword[] = "mdv2posh4u";

/* FE Server */
IPAddress server(152,78,189,14);      // numeric IP for api.pachube.com

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
  if (wifly.join()) 
  {
     //connected
     return true;
     //led_on();
  } 
  else 
  {
    //error handling
    return false;
  }
}

boolean wifi_send()
{      
  if (wifly.open(server, 80)) 
  {
    /* Send the request */
    wifly.print("POST //fe/rawinput/sensor/90-A2-DA-00-ED-21/temperature/data/");
    wifly.println(" HTTP/1.1");
    wifly.println("Host: 152,78,189,14:80");
    wifly.print("Content-Type: ");
    wifly.println("application/x-www-form-urlencoded");
    wifly.print("Content-Length: ");
    wifly.println(1); //data length
    wifly.println("Connection: close");
    wifly.println();
    wifly.print("value=");
    wifly.print(1); //data
    wifly.print("&key=");
    wifly.print("90-A2-DA-00-ED-21");
    return true;
  }
  else
  {
    //error
    return false;
  }
}

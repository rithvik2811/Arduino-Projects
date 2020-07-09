#include <SoftwareSerial.h>
#include<String.h>
#include<math.h>
#include "Arduino.h"
#include "thingspeak.h"

static SoftwareSerial sim800Module(9,10);
static void Send2thingspeak(String Y);
static void logSim800Data();

void thingsSpeakGsmSetup()
{

  // Set baud rate for communication with PC
  Serial.begin(9600);

  // Set baud rate for communication with sim800 module
  sim800Module.begin(9600);    
 
}

static String privateKey2Send;

void thingsSpeakSetPrivateSendKey(String privateKey_in)
{
  
  privateKey2Send = privateKey_in;
  Serial.print("PrivateKey Set: ");
  Serial.println(privateKey2Send);
  
}
  
void thingsSpeakSend(float* parFields_in,  unsigned char noOfParameters_in)
{
    Serial.print("thingsSpeakSend()");
    Serial.print("ParameterFields: ");
    for (int i=0; i<noOfParameters_in; i++)
    {
        Serial.print(parFields_in[i]);
        Serial.print(" ");
    }
    Serial.println(" ");

    String cmdString = String("GET /update?key=" + privateKey2Send);
    String parameterFields;
    for (int i=0; i<noOfParameters_in; i++)
    {
        parameterFields = parameterFields + "&field" + String(i+1) + "=" + String(parFields_in[i]);
        
    }
    String thinksSpeakString = String(cmdString + parameterFields);
    Serial.print("thingsSpeakSend(): Prepared string");
    Serial.println(thinksSpeakString);

    Send2thingspeak(thinksSpeakString);
}



static void Send2thingspeak(String parUploadCmdString_in)
{ 

      // Enable closing connection if needed
//   sim800Module.println("AT+CIPSHUT");
//   delay(1000);
//   logSim800Data();

   // Test with AT command
   sim800Module.println("AT");
   delay(1000);
   logSim800Data();
 
   // Attach GPRS  
   sim800Module.println("AT+CGATT=1");
   delay(1000);
   logSim800Data();
   
   // Read IP Connecion status
   sim800Module.println("AT+CIPMUX?");
   delay(1000); 
   logSim800Data();

   // Set up APN, User and Password
   sim800Module.println("AT+CSTT=\"internet\",\"\",\"\"");    
   delay(1000);
   logSim800Data();
   
   //Bring up wireless connection
   sim800Module.println("AT+CIICR");
   delay(1000);
   logSim800Data();
   
   sim800Module.println("AT+CIFSR");//get local IP adress
   delay(1000);
   logSim800Data();  

   //start up the connection,where 184.106.153.149 is IP address of ThingSpeak & port no 80
   sim800Module.println("AT+CIPSTART=\"TCP\",\"184.106.153.149\",\"80\""); 
   delay(2000);
   logSim800Data();
   
   // Let's begin to send data to remote server
   sim800Module.print("AT+CIPSEND=");
   // Command length will include the CR and NL
   int cmdLength = 2 + parUploadCmdString_in.length();
   sim800Module.println(cmdLength);
   delay(1000);
   logSim800Data();
   sim800Module.println(parUploadCmdString_in);
   delay(2500);
   logSim800Data();

   //close the connection
   sim800Module.println("AT+CIPSHUT");
   delay(5000);
   logSim800Data();
   delay(500);
}
static void logSim800Data()
{
  while(sim800Module.available()!=0)
    Serial.write(sim800Module.read());
}
 

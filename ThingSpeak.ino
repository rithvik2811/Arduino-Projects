#include "thingspeak.h"
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
// For periodic timer
//#include "TimerOne.h"

void setup() {
  // put your setup code here, to run once:
  thingsSpeakGsmSetup();
  thingsSpeakSetPrivateSendKey("FRQBN3Z7NERXVY6R");

  // For periodic timer 
  //Timer1.initialize(30000000);
  //Timer1.attachInterrupt(periodicLogFunc);

}
float temperature;
static unsigned short int dataUploadCount = 0;
void loop() {
  // put your main code here, to run repeatedly:
Serial.print("Temp=");

Serial.print(get_temperature());
 Serial.println("Â°C");
  float humidity=random(0,100);
  
  Serial.print("Humid=");
  Serial.println(humidity);
  delay(1000);

  float parameters[2] = { temperature, humidity};

  Serial.print("dataUploadCount: ");
  Serial.println(dataUploadCount);
  dataUploadCount++;
  thingsSpeakSend(parameters,  2);
  delay(30000);


}
void dht11setup()
{
 dht.begin();
 delay(1000);
}
float get_temperature()
{

temperature=dht.readTemperature();
return temperature;
}
/* For periodic timer
void periodicLogFunc()
{

    Serial.println("TestTimer");

}*/

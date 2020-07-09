#define trigPin 12
#define echoPin 13


void setup() {
pinMode(3,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);
pinMode(trigPin, OUTPUT);//Set I/o Mode
pinMode(echoPin, INPUT);
Serial.begin(9600);
}


long duration, distance;

void loop() {
int Left_IR=digitalRead(10);
int Right_IR=digitalRead(11);

digitalWrite(trigPin, LOW);
delayMicroseconds(2);//Delay 2micro sec
digitalWrite(trigPin, HIGH);
delayMicroseconds(2);//Delay 2micro sec
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.println(distance);


 if(Left_IR==HIGH&&Right_IR==HIGH)
 {if(distance>100)
{
  Serial.println(distance);
digitalWrite(3,LOW);
digitalWrite(6,LOW);
digitalWrite(5,HIGH);
digitalWrite(9,HIGH);
  }
else
{
digitalWrite(3,HIGH);
digitalWrite(6,HIGH);
digitalWrite(5,LOW);
digitalWrite(9,LOW);
  }
  }  
else if(Left_IR==LOW&& Right_IR==HIGH)
{
digitalWrite(3,LOW);
digitalWrite(5,LOW);
digitalWrite(6,HIGH);
digitalWrite(9,LOW);
}
else if(Left_IR==HIGH&&Right_IR==LOW)
{
  digitalWrite(3,HIGH);
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
digitalWrite(9,LOW);
}
else
{
digitalWrite(3,LOW);
digitalWrite(6,LOW);
digitalWrite(5,LOW);
digitalWrite(9,LOW);
}

}

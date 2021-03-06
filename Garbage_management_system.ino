#include<SoftwareSerial.h>
SoftwareSerial gsm(2,3);
const int trigpin =10;
const int echopin =9;

int r=13; //Red LED
int y=12; //Yellow LED
int g=11; //Green LED
long duration;
int distance;
int maxd=19;
int x;
int per;

// this function is for the blinking of light to indicate the changes
void blinks()
{
  for(int i=0;i<5;i++)
  {
// digitalWrite for light to glow(high) and off(low) is used   
 digitalWrite(r,HIGH);
    delay(50);
    digitalWrite(r,LOW);
//delay for time delay in millisecond  
    delay(50);
    digitalWrite(y,HIGH);
    delay(50);
    digitalWrite(y,LOW);
    delay(50);
    digitalWrite(g,HIGH);
    delay(50);
    digitalWrite(g,LOW);
    delay(50);  
  }
  }

//This function is used to initilize the pin and pin mode respectively 
void setup()
{
//pinMode is used to say whether pin is getting the data or giving the data through it respectively
  pinMode(r,OUTPUT);
  pinMode(y,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
//serial begin is used for display of value in serial monitor
  Serial.begin(9600);
  
} 

//this function is used for n iterations
void loop()
{
   blinks();
   digitalWrite(r,LOW);
   digitalWrite(y,LOW);
   digitalWrite(g,LOW);
   digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

//The code below is used to get the value from ultrasonic sensor to measure the depth
  duration = pulseIn(echopin, HIGH);
  distance= duration*0.034/2;
  x=maxd-distance;
  per=((x*100)/maxd)+20;
  if(per<=25)
  {
    /* Serial.print("Distance: ");
     Serial.println(distance);*/
    Serial.print("STATUS: ");
    Serial.println("Approx 0% to 25% is full"); 
    digitalWrite(g,HIGH);  
    delay(10000);   
  }

   else if(per<35)
  {
    /* Serial.print("Distance: ");
     Serial.println(distance);*/
    Serial.print("STATUS: ");
    Serial.println("Approx 25% to 35% is full"); 
    digitalWrite(g,HIGH);  
    delay(10000);   
  }
  else if(per<=45)
  {
    /* Serial.print("Distance: ");
     Serial.println(distance);
     */Serial.print("STATUS: ");
     Serial.println("Approx 35% to 45% is full"); 
     digitalWrite(g,HIGH); 
      delay(10000);
  }
 else if(per<=55)
  {
    /* Serial.print("Distance: ");
     Serial.println(distance);
     */Serial.print("STATUS: ");
     Serial.println("Approx 45% to 55% is full"); 
     digitalWrite(y,HIGH); 
      delay(10000);
  }
  else if(per<=65)
  {
     /* Serial.print("Distance: ");
     Serial.println(distance);*/
     Serial.print("STATUS: ");
     Serial.println("Approx 55% to 65% is full ");  
     digitalWrite(y,HIGH); 
      delay(10000);
  }
  else if(per<=75)
  {
     /* Serial.print("Distance: ");
     Serial.println(distance);*/
     Serial.print("STATUS: ");
     Serial.println("Approx 65% to 75% is full ");  
     digitalWrite(y,HIGH); 
      delay(10000);
  }
  else
  {
     /* Serial.print("Distance: ");
     Serial.println(distance);
     Serial.print("STATUS: ");
     Serial.println("Approx 75% to 85% is full");  
     Serial.println("Ready to remove waste");*/
      delay(10000);
       Serial.begin(9600);
      gsm.begin(9600);
//this command is used for GSM to make it active
     gsm.println("AT+CMGF=1");
     delay(1000);
// this command is used for GSM to add number to send message
     gsm.println("AT+CMGS=\"+91xxxxxxxxx\"\r"); //Enter the Mobile number after +91 replacing xxxxxxxxx
 //this is time delay
    delay(1000);
     gsm.println("FULL");
     delay(100);
    gsm.println((char)26);
    delay(1000); 
     digitalWrite(r,HIGH);
      delay(10000);
  }
 
}


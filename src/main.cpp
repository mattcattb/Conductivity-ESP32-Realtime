#include <Arduino.h>
//this uses gpio pins for 3.3v and gnd to not have a constant current be put through the water
#define bLED 23
#define gLED 19
#define rLED 16

#define ECprobe 34
#define ECpower 26
#define ECgnd 14

float Vin = 3.3;
float Vout;
float adc;

 
float R2 = 930;
const float Rpin = 25;//resistance of the powering pin i/o
float R1;

float Ec;
float EcTemp;

float k = 1.6;
float ppm = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //LED 
  pinMode(gLED,OUTPUT);
  pinMode(bLED,OUTPUT);
  pinMode(rLED,OUTPUT);
  pinMode(21, OUTPUT);
//gpio power and ground 
  pinMode(ECpower, OUTPUT);
  pinMode(ECgnd, OUTPUT);
//sets both to ground
  digitalWrite(ECgnd,LOW);
  digitalWrite(ECpower,HIGH);
  delay(100);
  R2 = R2 + Rpin;
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(500);
  
  digitalWrite(ECpower, HIGH);
  delay(2000);
  adc = analogRead(ECprobe);
  adc = analogRead(ECprobe);
  digitalWrite(ECpower, LOW);

  
  Serial.println(adc);
  Vout = adc * (Vin/4094);
  digitalWrite(ECpower, HIGH);
  
  R1 = ((Vout*R2)/(Vin-Vout)); //for when Rc is next to GND
  Ec = (1/(R1*k))*1000;
  digitalWrite(21, HIGH);
  float analogTest = analogRead(ECprobe);

  Serial.print("Vout is ");
  Serial.println(Vout);
  //Vout is the most important
  float exponent = exp(-3.94*Vout);
  ppm = 243774 * exponent;

  Serial.print("The ppm is ");
  Serial.println(ppm);

  if(ppm > 1000 && ppm <= 3600 ){ //blue on
    digitalWrite(bLED, HIGH);
    digitalWrite(gLED, LOW);
    digitalWrite(rLED,LOW); 
  }if(ppm > 3000 && ppm <= 6000){ //green on 
    digitalWrite(bLED, LOW);
    digitalWrite(gLED, HIGH);
    digitalWrite(rLED,LOW); 
  }
  if( ppm > 0 && ppm <= 1000 ) {//red on 
    digitalWrite(bLED, LOW);
    digitalWrite(gLED, LOW);
    digitalWrite(rLED,HIGH); 
  }

  //temperature conversions
  //need to tinker with K to get it to be the right value... hmmmmmmmm


}
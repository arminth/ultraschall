#include <Arduino.h>
#define settime 2 ;
#define on_off 3 ;
#define t60s 4 ;
#define t120s 5 ;
#define t180s 6 ;
#define SSR 7 ;

int timer[3] = {60,120,180}; 
int zeit = 0;

void setup() {
  pinMode(t60s, OUTPUT);
  pinMode(t120s, OUTPUT);
  pinMode(t180s, OUTPUT);
  pinMode(on_off, OUTPUT);
  pinMode(settime, INPUT);
  pinMode(on_off, INPUT);
  digitalWrite(SSR,LOW);
  digitalWrite(on_off,LOW);
  digitalWrite(t60s,HIGH);
  digitalWrite(t120s,LOW);
  digitalWrite(t180s,LOW);
  

}

void loop() {
  // put your main code here, to run repeatedly:
}
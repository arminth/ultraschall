// Controller software for Ultrasonic Cleaner on Arduino Nano
// Wiring: D4 - LED Green Anode - LED Kathode - GND
// Wiring: D5 - LED Yellow Anode - LED Kathode - GND
// Wiring: D6 - LED Red Anode - LED Kathode - GND
// Wiring: D7 - LED Bluen Anode - LED Kathode - GND and
// Wiring: D7 - SSR Control_in + 
// Wiring: SSR Control_-  GND
// Wiring: D2 - Button 1_in (Settime) - Button_1_out - GND
// Wiring: D3 - Button 2_in (ON/OFF) - Button_2_out - GND 

#define FASTLED_INTERNAL        // Suppress build banner
#include <Arduino.h>
#include <FastLED.h>

#define settime 2  //Input button 1
#define on_off 3  // Input button 2
#define t60s 4  // LED Green
#define t120s 5 // LED Yellow
#define t180s 6  // LED Red
#define SSR 7  //Output to control SSR and LED Blue

unsigned long time[3] = {60000,120000,180000}; // Timer-array, time in milliseconds
int zeit = 0;
int State_on_off = LOW;         // the current state of the output pin
int button_on_offState;             // the current reading from the input pin
int button_timerState;
int lastButton_on_off_State = HIGH;   // the previous reading from the input pin
int lastButton_timer_State = HIGH;   // the previous reading from the input pin
 int onoffbutton;
 int timerbutton;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime1 = 0;  // the last time the on_off pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the settime pin was toggled
unsigned long startTime = 0; //When did we push start
unsigned long debounceDelay = 30;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(t60s, OUTPUT);
  pinMode(t120s, OUTPUT);
  pinMode(t180s, OUTPUT);
  pinMode(SSR, OUTPUT);
  
  pinMode(settime, INPUT_PULLUP);
  pinMode(on_off, INPUT_PULLUP);
  digitalWrite(SSR,LOW);
  
  digitalWrite(t60s,HIGH);
  digitalWrite(t120s,LOW);
  digitalWrite(t180s,LOW);
   Serial.begin(115200); 
 onoffbutton = digitalRead(on_off);
 timerbutton = digitalRead(settime);
}

void loop() {
  lastButton_on_off_State = onoffbutton;
  lastButton_timer_State = timerbutton;
   onoffbutton = digitalRead(on_off);
  
 
  // check to see if you just pressed the ON/OFF button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (onoffbutton != lastButton_on_off_State) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
    
    delay (50);
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
     
    // if the onoffbutton state has changed from high to low:
    if ((onoffbutton != lastButton_on_off_State) && onoffbutton==LOW) {
      button_on_offState = onoffbutton;
      

      // only toggle the LED if the new button state is LOW
      if (button_on_offState == LOW) {
        State_on_off = !State_on_off;
        startTime = millis();
        Serial.print("Toggel change ON/OFF................................................... ");Serial.println(State_on_off);
      }
    }
  }



  if (State_on_off != HIGH){
   
     digitalWrite(SSR,LOW);
     timerbutton = digitalRead(settime);

  // check to see if you just pressed the settime-button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (timerbutton != lastButton_timer_State) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
    delay(50);
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the timerbutton state has changed:
    if ((timerbutton != lastButton_timer_State) && timerbutton==LOW){
      button_timerState = timerbutton;

      // only toggle the LED if the new button state is LOW
      if (button_timerState == LOW) {
        
        zeit ++;
        if (zeit == 3) {zeit = 0;};
        Serial.print("Toggel change Time................................................... ");Serial.println(time[zeit]);
      } 
        switch (zeit){
          case 0:
          digitalWrite(t60s,HIGH);
          digitalWrite(t120s,LOW);
          digitalWrite(t180s,LOW);
          break;

          case 1:
          digitalWrite(t60s,LOW);
          digitalWrite(t120s,HIGH);
          digitalWrite(t180s,LOW);
          break;

          case 2:
          digitalWrite(t60s,LOW);
          digitalWrite(t120s,LOW);
          digitalWrite(t180s,HIGH);
          break;

          default:
          digitalWrite(t60s,HIGH);
          digitalWrite(t120s,LOW);
          digitalWrite(t180s,LOW);
          zeit = 0;
        };

      }
    }
  } else {
    
    if ((millis() - startTime) <= time[zeit]) {EVERY_N_MILLISECONDS(10000) {Serial.print("S");}; digitalWrite(SSR,State_on_off);} else {Serial.println(""); 
    State_on_off = !State_on_off; digitalWrite(SSR,State_on_off);
    Serial.print("Toggel change ON/OFF................................................... ");Serial.println(State_on_off);
    };

  }





  }

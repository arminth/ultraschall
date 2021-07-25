#include <Arduino.h>
#define settime 2  //Input button 1
#define on_off 3  // Input button 2
#define t60s 4  // LED Blue
#define t120s 5 // LED Green
#define t180s 6  // LED Yellow
#define SSR 7  //Output to control SSR

unsigned long time[3] = {60000,120000,180000};
int timerstate = 0; 
int zeit = 0;
int State_on_off = LOW;         // the current state of the output pin
int button_on_offState;             // the current reading from the input pin
int button_timerState;
int lastButton_on_off_State = LOW;   // the previous reading from the input pin
int lastButton_timer_State = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime1 = 0;  // the last time the on_off pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the settime pin was toggled
unsigned long startTime = 0; //When did we push start
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

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

  int onoffbutton = digitalRead(on_off);

  // check to see if you just pressed the ON/OFF button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (onoffbutton != lastButton_on_off_State) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (onoffbutton != button_on_offState) {
      button_on_offState = onoffbutton;

      // only toggle the LED if the new button state is HIGH
      if (button_on_offState == HIGH) {
        State_on_off = !State_on_off;
        startTime = millis();
      }
    }
  }

  if (button_on_offState != HIGH){
     digitalWrite(SSR,LOW);
    int timerbutton = digitalRead(settime);

  // check to see if you just pressed the settime-button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (timerbutton != lastButton_timer_State) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (timerbutton != button_timerState) {
      button_timerState = timerbutton;

      // only toggle the LED if the new button state is HIGH
      if (button_timerState == HIGH) {
        zeit ++;
        if (zeit == 3) {zeit = 0;};
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
    
    if ((millis() - startTime) < time[zeit]) { digitalWrite(SSR,HIGH);} else {digitalWrite(SSR,LOW);};

  }





  }

#include <IRremote.h>
#include <IRremoteInt.h> 

int receiver = 2; //Signal Pin of IR receiver to Arduino Pin ?
int ButtonPin = 4; //Signal Pin of Button to Arduino Pin ?
int LedPin = 8; //output to pin

int LedState = LOW;
int ButtonState = LOW;
int previous = LOW;

long time = 0;
long debounce = 1000;

IRrecv irrecv(receiver);
decode_results results;
 
void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(ButtonPin, INPUT);
  pinMode(LedPin, OUTPUT);
  Serial.println("Visual Effects Online");
}
 
void loop(){
  if (irrecv.decode(&results)){ // have we received an IR signal?
    translateIR(); 
    irrecv.resume(); // receive the next value
    LedState = digitalRead(LedPin);
  }
  ButtonState = digitalRead(ButtonPin);  
  if (ButtonState == HIGH && previous == LOW && millis() - time > debounce) {
    if(LedState == HIGH){
      LedState = LOW;
      Serial.println(" Button Read  Led Off");
    } else {
       LedState = HIGH;
       Serial.println(" Button Read  Led On"); 
    }
    time = millis();
  }
  digitalWrite(LedPin, LedState);
}

void translateIR(){ // takes action based on IR code received
 switch(results.value){
  case 0xFF30CF: //Need to change to samsung power button code
 if(LedState == LOW){
          digitalWrite(LedPin, HIGH);
          Serial.println(" Controler '1' Read  Led On");
          digitalRead(LedState);
   } else if(LedState != LOW){
          digitalWrite(LedPin, LOW);
          Serial.println(" Controler '1' Read  Led Off");
  }
  break;
  case 0xFF18E7: //Need to change to cox power button code
 if(LedState == LOW){
          digitalWrite(LedPin, HIGH);
          Serial.println(" Controler '2' Read  Led On");
          digitalRead(LedState);
   } else if (LedState != LOW){
          digitalWrite(LedPin, LOW);
          Serial.println(" Controler '2' Read  Led Off");
  }
  default: Serial.println(" Imput not in use");

  }
  delay(1000); // Do not get immediate repeat
}

const float wheelCircumference = 0.2125;
volatile int pulseCounter = 0;
float distance = 0;

int buttonState1 = 0;
int lastButtonState1 = 0;

boolean lastCycling = false;
boolean cycling = false;

int totalPulses;

const byte interruptPin = 2;
volatile byte state = LOW;

int BUTTON1 = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(BUTTON1, INPUT);
  
}

void calculatePulses(){
  int pulse = digitalRead(interruptPin);
  if (pulse == LOW){
    pulseCounter = pulseCounter + 1; 
    //Serial.println("Pulses: " + String(pulseCounter));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState1 = digitalRead(BUTTON1);
  
  if(buttonState1 != lastButtonState1){
    if(buttonState1 == HIGH){
      cycling = !cycling;    
    }
    lastButtonState1 = buttonState1;
  }

  if(cycling != lastCycling){
    if(cycling == true){
      //pulseCounter = calculatePulses();
      Serial.println("BIKING");
      attachInterrupt(digitalPinToInterrupt(interruptPin), calculatePulses, CHANGE); 
      //Serial.println("Pulses: " + String(pulseCounter));
    }
    /*stopped biking and distance is travelled*/
    if (cycling == false && pulseCounter > 0){
      detachInterrupt(digitalPinToInterrupt(interruptPin));
      totalPulses = pulseCounter;
      Serial.println("STOPPED");
  
      distance = totalPulses * wheelCircumference;
      //Serial.println("Total distance travelled: " + String(distance));
      Serial.print(distance);

      delay(50);
      
      pulseCounter = 0;
      distance = 0;
    }
    else if(cycling == false){
      pulseCounter = 0;
      distance = 0;
    }
    lastCycling = cycling;
  }
  
  delay(50);
}

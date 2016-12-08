const float wheelCircumference = 0.135;
volatile int pulseCounter = 0;
float distance = 0;
//int buttonState = 0;

boolean lastCycling = false;
boolean cycling = false;

uint8_t _t = 0;
int totalPulses;

const byte interruptPin = 2;
volatile byte state = LOW;

//int BUTTON = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(interruptPin, INPUT_PULLUP);
  
  //pinMode(BUTTON, INPUT);

  Serial.println("Program Started");
}

void calculatePulses(){
  volatile int pulse = digitalRead(interruptPin);
  if (pulse == LOW){
    pulseCounter = pulseCounter + 1; 
    //Serial.println("Pulses: " + String(pulseCounter));
  }
}

void loop() {


  if(Serial.available() > 0){
    delay(50);
    uint8_t _t = (char)Serial.read();
    
    if(_t == 'A'){
      cycling = !cycling; 
    }
  }
  
  /*start biking*/
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

int distance = 0;

int redPin1 = 5;
int greenPin1 = 3;

int redPin2 = 9;
int greenPin2 = 10;

int redPin3 = 11;
int greenPin3 = 6;

int BUTTON1 = 13;
int BUTTON2 = 12;

int buttonState1 = 0;
int buttonState2 = 0;

int lastbuttonState2 = 0;

void setup() {
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(redPin3, OUTPUT);
  pinMode(greenPin3, OUTPUT);

//  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0){
    int input = Serial.parseFloat();
    distance = distance + input;
    if (distance < 5){
      analogWrite(redPin1, 255);
      analogWrite(redPin2, 255);
      analogWrite(redPin3, 255);
      Serial.println("Distance = " + String(distance) + " and input = " + String(input) ); 
    }
    else if (distance >= 5 && distance < 10){
      analogWrite(redPin1, 0);
      analogWrite(greenPin1, 255);
      analogWrite(redPin2, 255);
      analogWrite(redPin3, 255);
      Serial.println("Distance = " + String(distance) + " and input = " + String(input) ); 
    }
    else if (distance >= 10 && distance < 20){
      analogWrite(redPin2, 0);
      analogWrite(greenPin1, 255);
      analogWrite(greenPin2, 255);
      analogWrite(redPin3, 255);
      Serial.println("Distance = " + String(distance) + " and input = " + String(input) ); 
    }
    else if (distance >= 20 && distance < 11011){
      analogWrite(redPin3, 0);
      analogWrite(greenPin1, 255);
      analogWrite(greenPin2, 255);
      analogWrite(greenPin3, 255);
      Serial.println("Distance = " + String(distance) + " and input = " + String(input) ); 
    }
  }

  buttonState1 = digitalRead(BUTTON1);
  
  if (buttonState1 == HIGH){
    distance = 0;  
    analogWrite(redPin1, 0);
    analogWrite(redPin2, 0);
    analogWrite(redPin3, 0);
    analogWrite(greenPin1, 0);
    analogWrite(greenPin2, 0);
    analogWrite(greenPin3, 0);
  }

  buttonState2 = digitalRead(BUTTON2);
  if (buttonState2 != lastbuttonState2){
    if (buttonState2 == HIGH){
      Serial.print('A');  
  }  
    lastbuttonState2 = buttonState2;
  }
 
  delay(50);
}

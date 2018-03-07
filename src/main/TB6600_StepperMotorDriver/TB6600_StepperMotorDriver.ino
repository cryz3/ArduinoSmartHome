
int EnablePin = 5;    //define Enable Pin
int DirectionPin = 6; //define Direction pin
int PulsePin = 7;     //define Pulse pin

int ButtonPinFront = 2;
int ButtonPinBack = 3;

int ButtonStateFront = 0;
int ButtonStateBack = 0;

void setup() {
  pinMode (PulsePin, OUTPUT);
  pinMode (DirectionPin, OUTPUT);
  pinMode (EnablePin, OUTPUT);

  pinMode (ButtonPinFront, INPUT);
  pinMode (ButtonPinBack, INPUT);
}

void loop() {

  ButtonStateFront = digitalRead(ButtonPinFront);
  ButtonStateBack = digitalRead(ButtonPinBack);

  if (ButtonStateFront == HIGH) {
    for (int i = 0; i < 400; i++) {
      //Forward 5000 steps = 6400
      digitalWrite(DirectionPin, LOW);
      digitalWrite(EnablePin, HIGH);
      digitalWrite(PulsePin, HIGH);
      delayMicroseconds(400);
      digitalWrite(PulsePin, LOW);
      delayMicroseconds(400);
    }
  }

  if (ButtonStateBack == HIGH) {
    for (int i = 0; i < 400; i++) {
      //Backward 5000 steps = 6400
      digitalWrite(DirectionPin, HIGH);
      digitalWrite(EnablePin, HIGH);
      digitalWrite(PulsePin, HIGH);
      delayMicroseconds(400);
      digitalWrite(PulsePin, LOW);
      delayMicroseconds(400);
    }
  }
}

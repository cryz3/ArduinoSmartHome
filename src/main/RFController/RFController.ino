/*
 * RF Controller
 *
 * DESCRIPTION
 * BlaBlaBlub...Beschreibung...lalalallilalu...
 *
 * Developed by Daniel Sigl.
 *
 * REVISION HISTORY
 * Version 1.0 - March 07, 2018 - Release
*/

#define DATA_PIN 14       //Data pin for RF Transmitter (TX)
#define BUTTON_PIN_UP 7   //Read pin for UP button
#define BUTTON_PIN_DOWN 5 //Read pin for DOWN button
#define BUTTON_PIN_STOP 6 //Read pin for STOP button

int ButtonStateUp = 0;
int ButtonStateDown = 0;
int ButtonStateStop = 0;

#define ZERO_HIGH 345 //Delay for the high part of a 0 in microseconds
#define ZERO_LOW 755  //Delay for the low part of a 0 in microseconds
#define ONE_HIGH 690  //Delay for the high part of a 1 in microseconds
#define ONE_LOW 410   //Delay for the low part of a 1 in microseconds

// 40 bits to send
String data = "0000000000000000000000000000000000000000";

void setup() {
  //set output/input pins
  pinMode(DATA_PIN, OUTPUT);
  pinMode(BUTTON_PIN_UP, INPUT);
  pinMode(BUTTON_PIN_DOWN, INPUT);
  pinMode(BUTTON_PIN_STOP, INPUT);
}

void loop() {
  //read button state
  ButtonStateUp = digitalRead(BUTTON_PIN_UP);
  ButtonStateDown = digitalRead(BUTTON_PIN_DOWN);
  ButtonStateStop = digitalRead(BUTTON_PIN_STOP);

  //send stop motor signal blocks
  if (ButtonStateStop == HIGH) {
    Serial.println("Button STOP: ON");

    data = "1111101001000010100001111100000101010101";

    digitalWrite(DATA_PIN, HIGH); //start high
    delayMicroseconds(4800);
    digitalWrite(DATA_PIN, LOW);  //start low
    delayMicroseconds(1400);

    //Block 1/3
    sendBits(data);
    separatorDelay(true);
    //Block 2/3
    sendBits(data);
    separatorDelay(true);
    //Block 3/3
    sendBits(data);

    endDelay();
  }

  //send motor up signal blocks
  if (ButtonStateUp == HIGH) {
    Serial.println("Button UP: ON");

    data = "1111101001000010100001111100000100010001";

    digitalWrite(DATA_PIN, HIGH); //start high
    delayMicroseconds(4800);
    digitalWrite(DATA_PIN, LOW);  //start low
    delayMicroseconds(1400);

    //Block 1/3
    sendBits(data);
    separatorDelay(true);
    //Block 2/3
    sendBits(data);
    separatorDelay(true);
    //Block 3/3
    sendBits(data);

    Delay3to4();

    digitalWrite(DATA_PIN, HIGH); //start high
    delayMicroseconds(4800);
    digitalWrite(DATA_PIN, LOW);  //start low
    delayMicroseconds(1400);

    data = "1111101001000010100001111100000100011110";

    //Block 4/9
    sendBits(data);
    separatorDelay(true);
    //Block 5/9
    sendBits(data);
    separatorDelay(true);
    //Block 6/9
    sendBits(data);
    separatorDelay(true);
    //Block 7/9
    sendBits(data);
    separatorDelay(true);
    //Block 8/9
    sendBits(data);
    separatorDelay(true);
    //Block 9/9
    sendBits(data);

    endDelay();
  }

  //send motor down signal blocks
  if (ButtonStateDown == HIGH) {
    Serial.println("Button DOWN: ON");

    data = "1111101001000010100001111100000100110011";

    digitalWrite(DATA_PIN, HIGH); //start high
    delayMicroseconds(4800);
    digitalWrite(DATA_PIN, LOW);  //start low
    delayMicroseconds(1400);

    //Block 1/3
    sendBits(data);
    separatorDelay(true);
    //Block 2/3
    sendBits(data);
    separatorDelay(true);
    //Block 3/3
    sendBits(data);

    Delay3to4();

    digitalWrite(DATA_PIN, HIGH); //start high
    delayMicroseconds(4800);
    digitalWrite(DATA_PIN, LOW);  //start low
    delayMicroseconds(1400);

    data = "1111101001000010100001111100000100111100";

    //Block 4/9
    sendBits(data);
    separatorDelay(true);
    //Block 5/9
    sendBits(data);
    separatorDelay(true);
    //Block 6/9
    sendBits(data);
    separatorDelay(true);
    //Block 7/9
    sendBits(data);
    separatorDelay(true);
    //Block 8/9
    sendBits(data);
    separatorDelay(true);
    //Block 9/9
    sendBits(data);

    endDelay();
  }
}

/*
 * Send 40 bits = 1 block with different signal edge times.
 * ZERO_XXX = 0 & HIGH_XXX = 1
*/
void sendBits(String bits) {
  unsigned char j;
  int delayTime;

  for (j = 0; j < 40; j++) {
    int highTime;
    int lowTime;
    char charData = data.charAt(j);

    delayTime = charData - '0'; //check if char value is int 0/1

    if (delayTime == 1) {
      //set HIGH delay time
      highTime = ONE_HIGH;
      lowTime = ONE_LOW;
    }
    else {
      //set LOW delay time
      highTime = ZERO_HIGH;
      lowTime = ZERO_LOW;
    }
    //write square waves
    digitalWrite(DATA_PIN, HIGH);
    delayMicroseconds(highTime);
    digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(lowTime);
  }
}

/*
 * function for block separator delay
*/
void separatorDelay(boolean upDown) {
  if (upDown == true) {
    digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(8377);
  }
  digitalWrite(DATA_PIN, HIGH); //start high
  delayMicroseconds(4800);
  digitalWrite(DATA_PIN, LOW);  //start low
  delayMicroseconds(1400);
}

void Delay3to4() {
  digitalWrite(DATA_PIN, LOW);
  delayMicroseconds(51444);
}

/*
 * function for ending one block season
*/
void endDelay() {
  digitalWrite(DATA_PIN, LOW);
  delay(1000);
}

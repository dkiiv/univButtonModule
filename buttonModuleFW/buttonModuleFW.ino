#include <CAN.h>
int heartBeat = 1;
int button1 = 0;
int button2 = 0;
int button3 = 0;
int button4 = 0;
int buttonState = 0;

void setup() {
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);

  Serial.begin(9600);
  while (!Serial);
  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  button1 = digitalRead(21);
  button2 = digitalRead(22);
  button3 = digitalRead(23);
  button4 = digitalRead(24);
  if (button1) {
    buttonState = 1;
  }
  if (button2) {
    buttonState = 2;
  }
  if (button3) {
    buttonState = 3;
  }
  if (button4) {
    buttonState = 4;
  }
  else {
    buttonState = 0;
  }
  // send packet
  Serial.print("Sending packet ... ");

  CAN.beginPacket(0x210);
  CAN.write(heartBeat);
  CAN.write(buttonState);
  CAN.endPacket();

  Serial.println("done");

  delay(100);
}

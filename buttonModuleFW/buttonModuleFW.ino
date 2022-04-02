#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(9);
struct can_frame canMsg1;
int heartBeat = 0x1;
int buttonState = 0x0;

void setup() {
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("univButtonModule, khonsu / retropilot.org");
}

void loop() {
  int noButton = 0;
  if (digitalRead(21)) buttonState = 1; else noButton += 1;
  if (digitalRead(22)) buttonState = 2; else noButton += 1;
  if (digitalRead(23)) buttonState = 3; else noButton += 1;
  if (digitalRead(24)) buttonState = 4; else noButton += 1;
  if (noButton >= 4) buttonState = 0;
  canMsg1.can_id  = 0x210;
  canMsg1.can_dlc = 1;
  canMsg1.data[0] = heartBeat;
  canMsg1.data[1] = buttonState;

  mcp2515.sendMessage(&canMsg1);

  Serial.println("Messages sent");
  
  delay(100);
}

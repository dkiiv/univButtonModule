#include <mcp_can.h>
#include <SPI.h>
#define SPI_CS_PIN  9
#define CAN_500KBPS  16
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin
int heartBeat = 0x1;
int buttonState = 0x0;

void setup() {
    pinMode(21, INPUT);
    pinMode(22, INPUT);
    pinMode(23, INPUT);
    pinMode(24, INPUT);
    Serial.begin(115200);
    while(!Serial);
    
    // below code need for OBD-II GPS Dev Kit
    // pinMode(A3, OUTPUT);
    // digitalWrite(A3, HIGH);
    
    while (CAN_OK != CAN.begin(CAN_500KBPS))    // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS FAIL!");
        delay(100);
    }
    Serial.println("CAN BUS OK!");
    Serial.println("univButtonModule, khonsu / retropilot.org");
}

void loop() {
  unsigned char univACC[2] = {heartBeat, buttonState};
  int noButton = 0;
  if (digitalRead(21)) buttonState = 0x1; else noButton += 1;
  if (digitalRead(22)) buttonState = 0x2; else noButton += 1;
  if (digitalRead(23)) buttonState = 0x3; else noButton += 1;
  if (digitalRead(24)) buttonState = 0x4; else noButton += 1;
  if (noButton >= 4) buttonState = 0x0;

  CAN.sendMsgBuf(0x210, 0, 5, univACC);
  delay(100);                       // send data per 100ms
}

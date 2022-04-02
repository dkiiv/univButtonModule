#include <mcp_can.h>
#include <SPI.h>
unsigned char heartBeat = 1;
unsigned char buttonState = 0;
int button1 = 0;
int button2 = 0;
int button3 = 0;
int button4 = 0;

#define SPI_CS_PIN  9 

MCP_CAN CAN(SPI_CS_PIN); // Set CS pin

void setup()
{
    pinMode(21, INPUT);
    pinMode(22, INPUT);
    pinMode(23, INPUT);
    pinMode(24, INPUT);
    Serial.begin(115200);
    while(!Serial);
    
    while (CAN_OK != CAN.begin(CAN_500KBPS))    // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS FAIL!");
        delay(100);
    }
    Serial.println("CAN BUS OK!");
}

void loop()
{
    button1 = digitalRead(21);
    button2 = digitalRead(22);
    button3 = digitalRead(23);
    button4 = digitalRead(24);
    if (button1) {
      unsigned char buttonState = 1;
    }
    if (button2) {
      unsigned char buttonState = 2;
    }
    if (button3) {
      unsigned char buttonState = 3;
    }
    if (button4) {
      unsigned char buttonState = 4;
    }
    else {
      unsigned char buttonState = 0;
    }
    CAN.sendMsgBuf(0x210, 0, 1, heartBeat);
    CAN.sendMsgBuf(0x210, 1, 5, buttonState);
    delay(100); // send data per 100ms
}

// END FILE

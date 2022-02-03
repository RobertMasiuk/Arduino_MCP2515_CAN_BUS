#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);

int LED_PIN = 3;
void setup() {
  Serial.begin(115200);
  SPI.begin();
  pinMode(LED_PIN, OUTPUT);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
}

void loop() {

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {

    Serial.print(canMsg.can_id, HEX);
    Serial.print(" ");
    Serial.print(canMsg.can_dlc, HEX);
    Serial.print(" ");
    if (canMsg.data[0] == 0x00) {
      digitalWrite(LED_PIN, HIGH);
      Serial.print("YEET");
    }
    if (canMsg.data[0] == 0x01) {
      digitalWrite(LED_PIN, LOW);
      Serial.print("YOTE");
    }
    for (int i = 0; i < canMsg.can_dlc; i++)  {
      Serial.print(canMsg.data[i], HEX);
      Serial.print(" ");

    }

    Serial.println();
  }

}

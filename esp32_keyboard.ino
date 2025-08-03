v#include <BleKeyboard.h>
#include "BluetoothSerial.h"

BleKeyboard bleKeyboard("ESP32_Keyboard", "Espressif", 100);
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_CodeInput");
  bleKeyboard.begin();
  Serial.println("BLE Keyboard + Bluetooth Serial Ready");
}

void typeSlowly(String text) {
  for (int i = 0; i < text.length(); i++) {
    char c = text[i];

    // Handle tabs
    if (c == '\t') {
      for (int j = 0; j < 4; j++) {
        bleKeyboard.print(" ");
        delay(50);
      }
    }
    // Handle newline manually
    else if (c == '\n') {
      bleKeyboard.write(KEY_RETURN);
    }
    // Normal characters
    else {
      bleKeyboard.print(c);
    }

    delay(50);  // delay between each character
  }
}

void loop() {
  if (bleKeyboard.isConnected() && SerialBT.available()) {
    String input = SerialBT.readStringUntil('\0');  // Read full until end
    Serial.println("Typing received code...");
    typeSlowly(input);
    Serial.println("Done.");
  }
}

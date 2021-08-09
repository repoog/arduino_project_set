/*
 * It is a IR remote system with Arduino Keyboard firmware.
 * To make Arduino UNO work with keyboard like BadUSB, it needs to flush ATmega chip to Keyboard flash, see https://peirs.net/2021/08/02/226/ for details.
 * 
 * Features:
 *    Press button 1 to open Windows Explorer.
 *    Press button 2 to shift screen back to desktop.
 *    Press button 3 to open application in third place of task bar.
 *    Press button CH+ to shutdown Windows system.
*/

#include <HIDKeyboard.h>
#include <IRremote.h>

const int IR_PIN = 7;   // IR receiver INPUT.
IRrecv irrecv(IR_PIN);

HIDKeyboard keyboard;

void setup() {
  keyboard.begin();
  keyboard.pressSpecialKey(CTRL, SPACEBAR);   // Shift Chinese input to English to avoid exception.
  
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.begin(9600);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    switch (IrReceiver.decodedIRData.command) {
      case 0xC:  // Button 1, open Windows Explorer.
        keyboard.pressKey(GUI, 'e');
        keyboard.releaseKey();
        break;
      case 0x18:  // Button 2, shift back to desktop.
        keyboard.pressKey(GUI, 'd');
        keyboard.releaseKey();
        break;
      case 0x5E:  // Button 3, open application in third place of task bar, you can change it in your way.
        keyboard.pressKey((GUI | CTRL), '3');
        keyboard.releaseKey();
        break;
      case 0x47:  // Button CH+, shutdown system
        keyboard.pressKey(GUI, 'r');
        keyboard.releaseKey();
        delay(500);
        keyboard.pressSpecialKey(CTRL, SPACEBAR);   // Shift Chinese input to English to avoid exception.
        keyboard.println("shutdown /s");
        break;
    }
    irrecv.resume();
  }
  delay(3000);
}

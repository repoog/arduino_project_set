/*
 * It is a remote fan control by IR controler.
 * IR controls fan speed with range in 100, 180, 250, 250 is top speed of fan.
 * 
 * Features:
 *    Press button 1 to 100 speed.
 *    Press button 2 to 180 speed.
 *    Press button 3 to 250 speed.
*/

#include <IRremote.h>

const int MOTOR_IN = 9;   // Motor fan input
const int IR_PIN = 7;   // IR recevier input

IRrecv irrecv(IR_PIN);
decode_results sig;   // it's need in older version IRremote

void setup() {
  pinMode(MOTOR_IN, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  if (irrecv.decode(&sig)) {
    Serial.println(sig.value, HEX);
    switch (sig.value) {
      case 0xFF30CF:  // button 1
        run_fan(100);
        break;
      case 0xFF18E7:  // button 2
        run_fan(180);
        break;
      case 0xFF7A85:  // button 3
        run_fan(250);
        break;
    }
    irrecv.resume();
  }
  delay(500);
}

void run_fan(int speed) {
  analogWrite(MOTOR_IN, speed);
}

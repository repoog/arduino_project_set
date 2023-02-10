/**
* Copyright: repoog
*
* This is a automatic drug feeding equipment which help patient to feed drugs by themselves.
* The equipment is conducted by touch sensor button, servo motor and step motor.
*
* Author: repoog
* Date: 2022.12.31
*
**/

#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

static const uint8_t BASE_SERVO_INPUT = 8;
static const uint8_t POUR_SERVO_INPUT = 9;

static const uint8_t PIN_MP3_RX = 10;
static const uint8_t PIN_MP3_TX = 11;

Servo baseServoMotor, pourServoMotor;
SoftwareSerial mySoftwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini mp3Player;

void setup() {
  Serial.begin(115200);

  pinMode(2, INPUT);  // the input of button.
  pinMode(2, INPUT_PULLUP);

  baseServoMotor.attach(BASE_SERVO_INPUT);  // attach input of basement servo motor to 8.
  baseServoMotor.write(0);                  // initialize basement servo motor position to 0.

  pourServoMotor.attach(POUR_SERVO_INPUT);  // attach input of basement servo motor to 9.
  pourServoMotor.write(0);                  // initialize basement servo motor position to 0.

  mySoftwareSerial.begin(9600);

  if (!mp3Player.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }

  mp3Player.volume(15);
}

void loop() {
  // touch the sensor when patient's feeling is not good.
  if (isButtonPress()) {
    playNotice();
    pourMedicine();
    resetArms();
  }
}

bool isButtonPress() {
  bool buttonState = false;

  if (!digitalRead(2)) {
    delay(200);  // To avoid button jittering.

    if (!digitalRead(2)) {
      Serial.println(F("Button is pressed."));
      return true;
    }
  }

  return buttonState;
}

void playNotice() {
  Serial.println("Play notice sound.");
  mp3Player.play(1);
  delay(10000);
}

void pourMedicine() {
  Serial.println(F("Rotate arm to mouth position and pour medicine."));

  delay(2000);  // wait 2 seconds to rotate arm.
  for (int pos = 0; pos <= 90; pos += 1) {
    baseServoMotor.write(pos);
    delay(15);
  }

  delay(2000);
  // start to pour stuff.
  for (int pos = 0; pos <= 180; pos += 1) {
    pourServoMotor.write(pos);
    delay(15);
  }
}

void resetArms() {
  Serial.println("Reset arms.");

  delay(2000);  // wait 2 seconds to reset arm.
  // reset servo motor to start position.
  for (int pos = 90; pos >= 0; pos -= 1) {
    baseServoMotor.write(pos);
    delay(15);
  }

  delay(2000);
  // start to pour stuff.
  for (int pos = 180; pos >= 0; pos -= 1) {
    pourServoMotor.write(pos);
    delay(15);
  }
}

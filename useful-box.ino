/*
20240605: this is origial from 
https://github.com/balassy/useless-box.git

$ cat /etc/os-release 
PRETTY_NAME="Ubuntu 24.04 LTS"
NAME="Ubuntu"
VERSION_ID="24.04"
VERSION="24.04 LTS (Noble Numbat)"
VERSION_CODENAME=noble
ID=ubuntu
ID_LIKE=debian
HOME_URL="https://www.ubuntu.com/"
SUPPORT_URL="https://help.ubuntu.com/"
BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
UBUNTU_CODENAME=noble
LOGO=ubuntu-logo

$ arduino-cli version
arduino-cli  Version: 0.35.3 Commit: 95cfd654 Date: 2024-02-19T13:24:24Z

Used library Version Path
Servo        1.0.2   /home/qchen/.arduino15/packages/esp8266/hardware/esp8266/3.1.2/libraries/Servo                                                                     
Wire         1.0     /home/qchen/.arduino15/packages/esp8266/hardware/esp8266/3.1.2/libraries/Wire                                                                      

Used platform   Version Path
esp8266:esp8266 3.1.2   /home/qchen/.arduino15/packages/esp8266/hardware/esp8266/3.1.2                                                                                  
*/
// Platform libraries.
#include <Arduino.h>  // To add IntelliSense for platform constants.

// Third-party libraries.

// My classes.
#include "speed-servo.h"
#include "status-led.h"
#include "proximity-sensor.h"

#include "config.h"  // To store configuration and secrets.

SpeedServo lidServo;
SpeedServo switchServo;
StatusLed led;
ProximitySensor sensor;

int lastSwitchState = 0;
long playCount = 0;
bool isLidOpen = false;
bool monitorSensor = false;

void setup() {
  initSerial();
  initServos();
  initLed();
  initSensor();
  pinMode(PIN_SWITCH, INPUT);

  Serial.printf("Application version: %s\n", APP_VERSION);
  Serial.println("Setup completed.");
}

void initSerial() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Initializing serial connection DONE.");
}

void initServos() {
  lidServo.attach(PIN_LID_SERVO);
  lidServo.moveNowTo(LID_START_POSITION);

  switchServo.attach(PIN_SWITCH_SERVO);
  switchServo.moveNowTo(SWITCH_START_POSITION);
}

void initLed() {
  led.setPin(LED_BUILTIN);
  led.turnOff();
}

void initSensor() {
  sensor.attach(PIN_SENSOR_SDA, PIN_SENSOR_SCL, SENSOR_TRIGGER_THRESHOLD);
}

void loop() {
  int switchState = digitalRead(PIN_SWITCH);
  boolean isSwitchTurnedOn = (switchState == LOW);

  if (isSwitchTurnedOn) {
    led.turnOn();
    run();
    isLidOpen = false;
    led.turnOff();
  }

  // Check the proximity sensor even if the switch is not turned on.
  if (sensor.isInRange()) {
    if (!isLidOpen && monitorSensor) {
      openLidFast();
      isLidOpen = true;
    }
  } else {
    if (isLidOpen) {
      closeLidFast();
      isLidOpen = false;
    }
  }

  // Update last switch state for the next iteration.
  lastSwitchState = switchState;

  // Wait 250 ms before next reading (required for the sensor).
  delay(250);
}
void run() {
  static int runCounter = 0; // Counter to track the number of runs

  if (runCounter < 10) { // Follow pattern for the first 10 runs
    switch (runCounter % 10) { // Use runCounter to determine the pattern
      case 0:
      case 1:
        runSlow();
        break;
      case 2:
        runWaitThenFast();
        break;
      case 3:
        runFast();
        break;
      case 4:
        runFastThenClap();
        monitorSensor = true;
        break;
      case 5:
        runOpenCloseThenFast();
        monitorSensor = false;
        break;
      case 6:
        runPeekThenFast();
        break;
      case 7:
        runFastWithDelay();
        monitorSensor = true;
        break;
      case 8:
        runClap();
        monitorSensor = false;
        break;
      case 9:
        runHalf();
        break;
      default:
        break;
    }
  } else { // After 10 runs, switch to random selection
    int randomCase = random(10); // Generate a random number between 0 and 9

    switch (randomCase) {
      case 0:
        runSlow();
        break;
      case 1:
        runWaitThenFast();
        break;
      case 2:
        runFast();
        break;
      case 3:
        runFastThenClap();
        monitorSensor = true;
        break;
      case 4:
        runOpenCloseThenFast();
        monitorSensor = false;
        break;
      case 5:
        runPeekThenFast();
        break;
      case 6:
        runFastWithDelay();
        monitorSensor = true;
        break;
      case 7:
        runClap();
        monitorSensor = false;
        break;
      case 8:
        runHalf();
        break;
      case 9:
        // Add additional cases here as needed
        break;
      default:
        break;
    }
  }

  runCounter++; // Increment the run counter
  playCount++;
}

void runSlow() {
  openLidSlow();
  flipSwitchSlow();
  closeLidSlow();
}

void runWaitThenFast() {
  delay(5000);
  flipSwitchFast();
}

void runFast() {
  flipSwitchFast();
}

void runFastThenClap() {
  flipSwitchFast();
  clapLid();
}

void runOpenCloseThenFast() {
  openLidSlow();
  delay(2000);
  closeLidSlow();
  delay(2000);
  flipSwitchFast();
}

void runPeekThenFast() {
  switchServo.moveSlowTo(SWITCH_HALF_POSITION);
  delay(3000);
  switchServo.moveFastTo(SWITCH_START_POSITION);
  delay(3000);
  flipSwitchFast();
}

void runFastWithDelay() {
  openLidSlow();
  delay(4000);
  flipSwitchFast();
  closeLidFast();
}

void runClap() {
  clapLid();
  clapLid();
  clapLid();
  clapLid();
  openLidFast();
  flipSwitchFast();
  closeLidFast();
}

void runHalf() {
  switchServo.moveSlowTo(SWITCH_HALF_POSITION);
  delay(3000);
  switchServo.moveFastTo(SWITCH_END_POSITION);
  switchServo.moveFastTo(SWITCH_START_POSITION);
}

void openLidSlow() {
  lidServo.moveSlowTo(LID_END_POSITION);
}

void openLidFast() {
  lidServo.moveFastTo(LID_END_POSITION);
}

void closeLidSlow() {
  lidServo.moveSlowTo(LID_START_POSITION);
}

void closeLidFast() {
  lidServo.moveFastTo(LID_START_POSITION);
}

void clapLid() {
  openLidFast();
  closeLidFast();
}

void flipSwitchSlow() {
  switchServo.moveSlowTo(SWITCH_END_POSITION);
  switchServo.moveSlowTo(SWITCH_START_POSITION);
}

void flipSwitchFast() {
  switchServo.moveFastTo(SWITCH_END_POSITION);
  switchServo.moveFastTo(SWITCH_START_POSITION);
}

#include "proximity-sensor.h"

void ProximitySensor::attach(uint8_t sdaPin, uint8_t sclPin, uint8_t rangeThreshold) {
  Serial.println(F("ProximitySensor: Initializing..."));

  _sensor = SparkFun_APDS9960();

  Serial.println(F("ProximitySensor: Starting I2C..."));
  Wire.begin(sdaPin, sclPin);
  Serial.println(F("ProximitySensor: Starting I2C...DONE"));

  Serial.println(F("ProximitySensor: Configuring I2C and initial values..."));
  if (_sensor.init()) {
    Serial.println(F("ProximitySensor: Configuring I2C and initial values...DONE"));
  } else {
    Serial.println(F("ProximitySensor: Configuring I2C and initial values...FAILED!"));
  }

  Serial.println(F("ProximitySensor: Adjusting the sensor gain..."));
  if (_sensor.setProximityGain(PGAIN_2X)) {
    Serial.println(F("ProximitySensor: Adjusting the sensor gain...DONE"));
  } else {
    Serial.println(F("ProximitySensor: Adjusting the sensor gain...FAILED!"));
  }

  Serial.println(F("ProximitySensor: Starting the sensor..."));
  bool enableInterrupts = false;
  if (_sensor.enableProximitySensor(enableInterrupts)) {
    Serial.println(F("ProximitySensor: Starting the sensor...DONE"));
  } else {
    Serial.println(F("ProximitySensor: Starting the sensor...FAILED!"));
  }

  _rangeThreshold = rangeThreshold;

  Serial.println(F("ProximitySensor: Initializing...DONE"));
}

uint8_t ProximitySensor::getProximity() {
  if ( _sensor.readProximity(_lastProximityValue) ) {
    Serial.print(F("ProximitySensor: Proximity value: "));
    Serial.println(_lastProximityValue);
    return _lastProximityValue;
  } else {
    Serial.println(F("ProximitySensor: Reading proximity value FAILED!"));
    // 确保在所有情况下都有一个返回值
    return 0; // 或者返回一个适当的默认值
  }
}

bool ProximitySensor::isInRange() {
  uint8_t currentProximityValue = getProximity();
  return currentProximityValue > _rangeThreshold;
}

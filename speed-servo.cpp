#include "speed-servo.h"

const int SLOW_MOVE_STEPS = 1;
const int Fast_MOVE_STEPS = 5;

void SpeedServo::attach(uint8_t pin) {
_servo.attach(pin,544,2570);
}

// Valid position: 0-180.
void SpeedServo::moveNowTo(int newPosition) {
_lastPosition = newPosition;
_servo.write(newPosition);
}

// Valid position: 0-180.
void SpeedServo::moveFastTo(int newPosition) {
_moveTo(newPosition, Fast_MOVE_STEPS);
}

// Valid position: 0-180.
void SpeedServo::moveSlowTo(int newPosition) {
_moveTo(newPosition, SLOW_MOVE_STEPS);
}

// Valid position: 0-180.
void SpeedServo::_moveTo(int newPosition, unsigned long stepDelay) {
if(newPosition > _lastPosition) {
for (int pos = _lastPosition; pos <= newPosition; pos = pos + stepDelay) {
_servo.write(pos);
}
} else {
for (int pos = _lastPosition; pos >= newPosition; pos = pos - stepDelay) {
_servo.write(pos);
}
}

_lastPosition = newPosition;
}

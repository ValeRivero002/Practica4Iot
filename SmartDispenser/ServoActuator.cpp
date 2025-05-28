#include "ServoActuator.h"

ServoActuator::ServoActuator(int pin) : pin(pin) {}

void ServoActuator::begin() {
  servo.attach(pin);
  close();
}

void ServoActuator::open() {
  servo.write(170);
  opened = true;
}

void ServoActuator::close() {
  servo.write(0);
  opened = false;
}

bool ServoActuator::isOpen() const {
  return opened;
}

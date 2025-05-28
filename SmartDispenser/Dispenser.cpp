#include "Dispenser.h"

Dispenser::Dispenser(ServoActuator* actuator, WeightSensor* sensor)
  : actuator(actuator), sensor(sensor) {}

void Dispenser::begin() {
  actuator->begin();
  sensor->begin();
}

void Dispenser::applyState(const String& state) {
  dispenserState = state;
  if (state == "open") actuator->open();
  else actuator->close();
  delay(300);
}

float Dispenser::readWeight() {
  return sensor->getWeightGrams();
}

String Dispenser::classifyWeight(float g) {
  if (g <= thresholdEmpty) return "nothing";
  if (g <= thresholdLittle) return "little";
  if (g <= thresholdEnough) return "enough";
  return "overflowing";
}

String Dispenser::getCurrentState() {
  return dispenserState;
}

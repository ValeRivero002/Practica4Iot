#include "WeightSensor.h"

WeightSensor::WeightSensor(int doutPin, int sckPin, float calibration)
  : doutPin(doutPin), sckPin(sckPin), calibrationFactor(calibration) {}

void WeightSensor::begin() {
  scale.begin(doutPin, sckPin);
  scale.set_scale(calibrationFactor);
  scale.tare();
}

float WeightSensor::getWeightGrams() {
  float g = scale.get_units(30);
  return (g < 3.0f) ? 0.0f : g;
}

void WeightSensor::tare() {
  scale.tare();
}

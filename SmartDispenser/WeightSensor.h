#ifndef WEIGHTSENSOR_H
#define WEIGHTSENSOR_H

#include "HX711.h"

class WeightSensor {
  public:
    WeightSensor(int doutPin, int sckPin, float calibration = 470.95f);
    void begin();
    float getWeightGrams();
    void tare();

  private:
    HX711 scale;
    int doutPin;
    int sckPin;
    float calibrationFactor;
};

#endif

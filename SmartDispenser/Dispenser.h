#ifndef DISPENSER_H
#define DISPENSER_H

#include "WeightSensor.h"
#include "ServoActuator.h"

class Dispenser {
  public:
    Dispenser(ServoActuator* servo, WeightSensor* sensor);
    void begin();
    void applyState(const String& state);
    float readWeight();
    String classifyWeight(float g);
    String getCurrentState();

  private:
    ServoActuator* actuator;
    WeightSensor* sensor;
    float thresholdEmpty = 30.0f;
    float thresholdLittle = 60.0f;
    float thresholdEnough = 200.0f;
    String dispenserState = "closed";
};

#endif

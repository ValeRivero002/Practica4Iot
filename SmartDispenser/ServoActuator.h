#ifndef SERVOACTUATOR_H
#define SERVOACTUATOR_H

#include <ESP32Servo.h>

class ServoActuator {
  public:
    ServoActuator(int pin);
    void begin();
    void open();
    void close();
    bool isOpen() const;

  private:
    Servo servo;
    int pin;
    bool opened = false;
};

#endif

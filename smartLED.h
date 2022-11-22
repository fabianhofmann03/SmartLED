/******************************

  Mann Co.
  Progamm: smartLED.h
  Datum: 13.11.20
  Programmierer: Fabian Hofmann

******************************/

#include "Arduino.h"
#ifndef SMARTLED_H
#define SMARTLED_H

class SmartLED {
    bool ledState;
    int pin;
    int brightLow, brightHigh;
    long zaehlerOn, zaehlerOff;
    unsigned long startTime;
    unsigned long duration;
    unsigned long tOn, tOff;
    bool blink;
    bool fadeOn;
    bool once;
  public:
    SmartLED(int pin);
    void setOn(int);
    void setOff(int);
    void stop();
    void setBlink(unsigned long);
    void setBlink();
    void setPulse(unsigned long, unsigned long);
    void setPulse(float, float);
    void setPulse();
    void updateLED(int, int);
    void updateLED();
    float fade(float, float, float, float);
    void setPulseFade(unsigned long, unsigned long);
    void setPulseFade(float, float);
    void setPulseFade();
    void setFade(unsigned long, bool);
    void setFade(bool);
};

#endif

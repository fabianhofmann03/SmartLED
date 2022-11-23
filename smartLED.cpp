/******************************

  Mann Co.
  Progamm: smartLED.cpp
  Datum: 13.11.20
  Programmierer: Fabian Hofmann

******************************/

#include "smartLED.h"

SmartLED::SmartLED(int pin) {
  this->pin = pin;
  //(*this).pin = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  ledState = LOW;
  tOn = tOff = 500;
  startTime = 0;
}
void SmartLED::setOn(int brightLow) {
  outp = brightLow;
  analogWrite(pin, brightLow);
  ledState = HIGH;
}
void SmartLED::setOff(int brightHigh) {
  outp = brightHigh;
  analogWrite(pin, brightHigh);
  ledState = LOW;
}

void SmartLED::stop() {
  blink = false;
  fadeOn = false;
  once = false;
}

void SmartLED::setBlink(unsigned long duration) {
  (*this).stop();
  blink = true;
  startTime = millis();
  tOn = tOff = duration / 2;
  zaehlerOn = zaehlerOff = 0;
}
void SmartLED::setBlink() {
  (*this).stop();
  blink = true;
  startTime = millis();
  tOn = tOff = 500;
  zaehlerOn = zaehlerOff = 0;
}
void SmartLED::setPulse(unsigned long tOn, unsigned long tOff) {
  (*this).stop();
  blink = true;
  startTime = millis();
  (*this).tOn = tOn;
  (*this).tOff = tOff;
  zaehlerOn = zaehlerOff = 0;
}
void SmartLED::setPulse(float dutyCycle, float frequency) {
  (*this).stop();
  blink = true;
  startTime = millis();
  (*this).tOn = 1000 * dutyCycle / (frequency * (dutyCycle + 1));
  (*this).tOff = 1000 * (1 - dutyCycle)/ (frequency * (dutyCycle + 1));
  zaehlerOn = zaehlerOff = 0;
}

void SmartLED::setPulse() {
  (*this).stop();
  blink = true;
  startTime = millis();
  tOn = tOff = 500;
  zaehlerOn = zaehlerOff = 0;
}

//------------------------------------------------------------

void SmartLED::setPulseFade(unsigned long tOn, unsigned long tOff) {
  (*this).stop();
  blink = true;
  fadeOn = true;
  startTime = millis();
  (*this).tOn = tOn;
  (*this).tOff = tOff;
  zaehlerOn = zaehlerOff = 0;
}
void SmartLED::setPulseFade(float dutyCycle, float frequency) {
  (*this).stop();
  blink = true;
  fadeOn = true;
  startTime = millis();
  tOn = 1000 * dutyCycle / (frequency * (dutyCycle + 1));
  tOff = 1000 * (1 - dutyCycle) / (frequency * (dutyCycle + 1));
  zaehlerOn = zaehlerOff = 0;
}

void SmartLED::setPulseFade() {
  (*this).stop();
  blink = true;
  fadeOn = true;
  startTime = millis();
  tOn = tOff = 500;
  zaehlerOn = zaehlerOff = 0;
}

void SmartLED::setFade(unsigned long t, bool down) {
  (*this).stop();
  blink = true;
  once = true;
  fadeOn = true;
  startTime = millis();
  tOn = tOff = t;
  if(down) {
    setOff(0);
    zaehlerOn = 1;
    zaehlerOff = 0;
  }
  else {
    setOn(255);
    zaehlerOn = 0;
    zaehlerOff = 1;
  }
}

void SmartLED::setFade(bool down) {
  (*this).stop();
  blink = true;
  once = true;
  fadeOn = true;
  startTime = millis();
  tOn = tOff = 500;
  if(down) {
    setOff(0);
    zaehlerOn = 1;
    zaehlerOff = 0;
  }
  else {
    setOn(255);
    zaehlerOn = 0;
    zaehlerOff = 1;
  }
}

float SmartLED::fade(float start, float from, float to, float timeT) {
  return (millis() - start) * (to - from) / timeT + from;
}

//-------------------------------------------------------------

int SmartLED::updateLED(int brightHigh, int brightLow) {
  if (blink == true) {
    if (ledState) {
      if (fadeOn) {
        if (millis() < startTime + tOn * zaehlerOn + tOff * zaehlerOff) {
          setOn(fade(startTime + tOn * (zaehlerOn - 1) + tOff * zaehlerOff, brightHigh, brightLow, tOn));
        }
      }
      if (millis() > startTime + tOn * zaehlerOn + tOff * zaehlerOff) {
        if(once) stop();
        setOff(brightLow);
        zaehlerOff ++;
      }
    } else {
      if (fadeOn) {
        if (millis() < startTime + tOn * zaehlerOn + tOff * zaehlerOff) {
          setOff(fade(startTime + tOn * zaehlerOn + tOff * (zaehlerOff - 1), brightLow, brightHigh, tOff));
        }
      }
      if (millis() > startTime + tOn * zaehlerOn + tOff * zaehlerOff) {
        if(once) stop();
        setOn(brightHigh);
        zaehlerOn ++;
      }
    }
  }
  return outp;
}

int SmartLED::updateLED() {
  if (blink == true) {
    if (ledState) {
      if (fadeOn) {
        if (millis() < startTime + tOn * zaehlerOn + tOff * zaehlerOff) {
          setOn(fade(startTime + tOn * (zaehlerOn - 1) + tOff * zaehlerOff, 255, 0, tOn));
        }
      }
      if (millis() > startTime + tOn * zaehlerOn + tOff * zaehlerOff) {
        if(once) stop();
        setOff(0);
        zaehlerOff ++;
      }
    } else {
      if (fadeOn) {
        if (millis() < startTime + tOn * zaehlerOn + tOff * zaehlerOff) {
          setOff(fade(startTime + tOn * zaehlerOn + tOff * (zaehlerOff - 1), 0, 255, tOff));
        }
      }
      if (millis() > startTime + tOn * zaehlerOn + tOff * zaehlerOff) {
        if(once) stop();
        setOn(255);
        zaehlerOn ++;
      }
    }
  }
  return outp;
}

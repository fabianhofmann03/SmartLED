# SmartLED
SmartLED Library we had to build in school. 

## setBlink

Make the LED blink with a certain periode.

```
setBlink()
setBlink(unsigned long periode)             // periode ... duration of on/off periode in ms (default 500ms)
```

![grafik](https://user-images.githubusercontent.com/33757785/203544844-e239c08f-370d-4310-b8da-4367431d1479.png)

## <a name="setPulse"></a>setPulse

Make the LED blink with different periodes.

```
setPulse()
setPulse(unsigned long periodeOn, unsigned long periodeOff)             // periodeOn ... duration of on periode in ms (default 500ms)
                                                                        // periodeOff ... duration of off periode in ms (default 500ms)
setPulse(float dutyCycle, float frequency)                              // dutyCycle ... percentage of the time the signal is on (0 - 1)
                                                                        // frequecy ... frequency of the signal in Hz
```

![grafik](https://user-images.githubusercontent.com/33757785/203534443-e9937f03-3f2c-4008-b49a-8da940c94cc5.png)

## setFade

Fade one time from High to Low or Low to High

```
setFade(bool down)                                                      // down ... true = \, false = /
setFade(unsigned long t, bool down)                                     // t ... time it takes to fade in ms
```

![grafik](https://user-images.githubusercontent.com/33757785/203537102-f747e1c0-1edc-4ee9-a1e3-62433629ed8f.png)


## setPulseFade

Works like [setPulse](setPulse), but fades to Low, when in High state and fades to High when in Low State

```
setPulseFade()
setPulseFade(unsigned long periodeOn, unsigned long periodeOff)         // periodeOn ... duration of on periode in ms (default 500ms)
                                                                        // periodeOff ... duration of off periode in ms (default 500ms)
setPulseFade(float dutyCycle, float frequency)                          // dutyCycle ... percentage of the time the signal is on (0 - 1)
                                                                        // frequecy ... frequency of the signal in Hz
```

![grafik](https://user-images.githubusercontent.com/33757785/203525913-27419045-523b-4074-9f47-f9df51ed6955.png)

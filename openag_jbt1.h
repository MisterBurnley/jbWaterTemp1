/**
 *  \file jbt1.h
 *  \brief analog Sensor module for temperature.
 */

#ifndef OPENAG_JBT1_H
#define OPENAG_JBT1_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// 8 MHz(ish) AVR ---------------------------------------------------------
#if (F_CPU >= 7400000UL) && (F_CPU <= 9500000UL)
#define COUNT 3
// 16 MHz(ish) AVR --------------------------------------------------------
#elif (F_CPU >= 15400000UL) && (F_CPU <= 19000000L)
#define COUNT 6
#else
#error "CPU SPEED NOT SUPPORTED"
#endif

#include <math.h>
#include <openag_module.h>
#include <std_msgs/Float32.h>

/**
 *  \brief Sensor module for air temperature.
 */

class Jbt1 : public Module {
  public:
    // Public Functions
    Jbt1(int pin);
    void begin();
    void update();
    bool get_air_temperature(std_msgs::Float32 &msg);

  private:
    // Private Functions
    float getData();



    // Private Variables
    float valC;
    float Temp;
    int _pin;
    float _air_temperature;
    bool _send_air_temperature;
    uint32_t _time_of_last_reading;
    const uint32_t _min_update_interval = 2500;

};

#endif


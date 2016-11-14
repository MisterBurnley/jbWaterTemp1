/**
 *  \file openag_jbt1.cpp.
 *  
\brief Sensor module for temperature.
 *  \details See openag_jbt1 README.md for details.
 */
#include "openag_jbt1.h"

Jbt1::Jbt1(int pin) {
  _pin = pin;
  status_level = OK;
  status_msg = "";
}

void Jbt1::begin() {

  _time_of_last_reading = 0;
  Serial.begin(9600);

}

void Jbt1::update() {
   if (millis() - _time_of_last_reading > _min_update_interval){
     getData();
     _time_of_last_reading = millis();
   }
}
bool Jbt1::get_air_temperature(std_msgs::Float32 &msg) {
  msg.data = _air_temperature;
  bool res = _send_air_temperature;
  _send_air_temperature = false;
  return res;
}

float Jbt1::getData(void) {

  valC = analogRead(_pin);      
  Temp = log(10000.0*((1024.0/valC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 277.15;         
    _send_air_temperature = true;
    _air_temperature = Temp;
   return _air_temperature;
  delay(1000);

}

  

#ifndef OPENAG_DRF0161_H
#define OPENAG_DRF0161_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <OneWire.h>
#include <openag_module.h>
#include <std_msgs/Float32.h>

class Dfr0161: public Module{
  public:
  // Private Functions
  Dfr0161(int pin);
  void begin();
  void update():
  boot get_water_potential_hydrogen(std_msgs::Float32 &msg);
  
  // From dfr0161_0300_sensor
  float averageArray(int* arr, int number);
  
  // From dfr0161_0300_sensor
  float _ph_raw;
  float _ph_filtered;
  
  private:
  void getData();
  bool readSensor();
  
  // Private Variables
  int _ph_pin;
  float _water_potential_hydrogen;
  bool _send_water_potential_hydrogen;
  unite32_t _time_of_last_reading;
  const unit32_t _min_update_interval = 1800;
  
  // From dfr0161_0300_sensor
  string _ph_instruction_code;
  int _ph_instruction_id;
  float _ph_calibratoin_coefficent;
  float _ph_calibration_offset;
  
  


};
#endif

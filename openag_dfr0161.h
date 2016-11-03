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
#define ph_pin 1

class Dfr0161: public Module {
  public:
  // Private Functions
  Dfr0161(int _ph_pin);
  void begin();
  void update();
  bool get_water_potential_hydrogen(std_msgs::Float32 &msg);
  
  // From dfr0161_0300_sensor
  float averageArray(int* arr, int number);
  
  // From dfr0161_0300_sensor
  float _ph_raw;
  float _ph_filtered;
  
  private:
  float getData();
  bool readSensor();
  
  // Private Variables
  int _ph_pin = 1;
  float _water_potential_hydrogen;
  bool _send_water_potential_hydrogen;
  uint32_t _time_of_last_reading;
  const uint32_t _min_update_interval = 1800;
  
  // From dfr0161_0300_sensor
  String _ph_instruction_code;
  int _ph_instruction_id;
  float _ph_calibration_coefficient;
  float _ph_calibration_offset;
  
  


};

#endif

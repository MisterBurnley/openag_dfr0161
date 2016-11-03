
#include "openag_dfr0161.h"

 Dfr0161::Dfr0161(int pin){
   _ph_pin = pin;
   status_level = OK;
   status_msg = "";
}

 void Dfr0161::begin(){
   pinMode(_ph_pin, OUTPUT);
   digitalWrite(_ph_pin, LOW);
   _time_of_last_reading = 0;
   _ph_calibration_coefficient = 3.5;
   _ph_calibration_offset = -0.1;
 }
 
 void Dfr0161::update(){
   if (millis() - _time_of_last_reading > _min_update_interval){
     getData();
     _time_of_last_reading = millis();
   }
}
 
 bool Dfr0161::get_water_potential_hydrogen(std_msgs::Float32 &msg){
   msg.data = _water_potential_hydrogen;
   bool res = _send_water_potential_hydrogen;
   _send_water_potential_hydrogen = false;
   return res;
}

//.......................................Private.......................................//
 
 float Dfr0161::getData(void){
   int samples = 40;
  int voltage[samples];
  const int sample_time_delta = 20; // millisecond
  // Acquire Samples
  for (int i=0; i<samples; i++){
   voltage[i] = analogRead(_ph_pin);
  }
  
  // Remove Min & Max Samples, average, Convert to Voltage
  double volts = averageArray(voltage, samples) * 5.0/1024;
  
  // Conver Average Voltage to pH
  return _ph_calibration_coefficient*volts + _ph_calibration_offset;
}

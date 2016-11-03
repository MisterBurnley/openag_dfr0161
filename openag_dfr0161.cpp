
#include "openag_dfr0161.h"

 Dfr0161::Dfr0161(int pin){
   _pin = pin;
   status_level = OK;
   status_msg = "";
 }

 void Dfr0161::begin(){
   pinMode(_pin, INPUT);
   analogWrite(HIGH);
   _time_of_last_reading = 0; 
 }
 
 void Dfr0161::update(){
   if (millis() - _time_of_last_reading > _min_update_interval){
     getData();
     _time_of_last_reading = millis();
   }
 }
 
 bool Dfr0161::get_water_potential_hygrogen(std_msg::Float32 &msg){
   msg.data = _water_potential_hydrogen;
   bool res = _send_water_potential_hydrogen;
   _send_water_potential_hydrogen = false;
   return res;
 }
 
 

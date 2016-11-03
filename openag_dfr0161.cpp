
#include "openag_dfr0161.h"

 Dfr0161::Dfr0161(int pin){
   _ph_pin = pin;
   status_level = OK;
   status_msg = "";
}

 void Dfr0161::begin(){
   Serial2.println("Hi");
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
    Serial2.println("HiUpdate");
   }
}
 
 bool Dfr0161::get_water_potential_hydrogen(std_msgs::Float32 &msg){
   msg.data = _water_potential_hydrogen;
   bool res = _send_water_potential_hydrogen;
   _send_water_potential_hydrogen = false;
   Serial2.println("HiBool");
   return res;
}
 
 float Dfr0161::averageArray(int* arr, int number){
   Serial2.println("HiAverage");
   int i;
   int max,min;
   float avg;
   long amount=0;
   if (number<=0){ //if
     return 0;
   } //if(number<=0)
  
   if (number<5){ // less than 5, calculated directly statistics
     for(i=0;i<number;i++){ //if
       amount+=arr[i];
     } //for (i=0;i<number;i++)
      avg = amount/number;
      return avg;
   } //if (number<5)
  
   else {  //first_else
    
       if(arr[0]<arr[1]){// if(arr[0]<arr[1])
         min = arr[0];
         max = arr[1];
       } // if(arr[0]<arr[1])
    
       else{ // second_else
         min = arr[1];
         max = arr[0];
       } // second_else
    
       for (i=2; i<number; i++){//for (i=2; i<number; i++)
         if (arr[i]<min){ //if (arr[i]<min)
           amount+=min;
           min=arr[i];
         } //if (arr[i]<min)
         else 
         { // third_else
           if (arr[i]>max){ // if (arr[i]>max)
             amount+=max;
             max=arr[i];
           } //if (arr[i]>max)
          
           else
           { //fourth_else
             amount+=arr[i];
           } //fourth_else
         } //third_else
       } //for (i=2; i<number; i++)
       avg = (float) amount/(number-2);
     } // first_else 
  return avg;
} //end of function
//.......................................Private.......................................//
 
 float Dfr0161::getData(void){
   Serial2.println("HiData");
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
  Serial2.println(_ph_calibration_coefficient*volts + _ph_calibration_offset);
  return _ph_calibration_coefficient*volts + _ph_calibration_offset;
}

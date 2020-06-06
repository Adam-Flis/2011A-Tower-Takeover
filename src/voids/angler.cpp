#include "main.h"
#include "define.hpp"
#include "voids.hpp"

/**
 * Sets brake mode of the angler depending on its position
 */
void anglerBrakeMode(){
  if (anglerPot.get_value() > anglerStackVar/1.5){
    angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  else {
    angler.set_brake_mode(MOTOR_BRAKE_BRAKE);
  }
}

/**
 * Moves the angler to the position needed to stack cubes
 * endTime: Seconds
 */
void anglerStack(float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while(endT > millis() || anglerStackVar > anglerPot.get_value()){
    float error = anglerStackVar - anglerPot.get_value();
    float voltage = error * angler_Kp;
    if ((anglerHomeVar + anglerAdd) > anglerPot.get_value()){ //Sets voltage if below specific position
      voltage = 12000; //Max voltage
    }
    if (voltage > 12000){ //Max voltage
      voltage = 12000;
    }
    if (voltage < 5000){ //Min voltage
      voltage = 5000;
    }
    angler.move_voltage(voltage); //Sets angler voltage
    delay(10);
  }
  anglerBrakeMode(); //Sets brake mode of the angler depending on its position
  angler.move_velocity(0); //Stops angler
}

/**
 * Moves the angler back to the start position
 * endTime: Seconds
 */
void anglerHome(float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while (endT > millis() || anglerHomeVar < anglerPot.get_value()){
    angler.move_voltage(-10000);
    delay(10);
  }
  anglerBrakeMode(); //Sets brake mode of the angler depending on its position
  angler.move_velocity(0); //Stops angler
}

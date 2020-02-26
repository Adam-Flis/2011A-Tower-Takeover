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
  while(endT > millis()){
    float VoltageInterval = anglerHomeVar-anglerStackVar/angler_acc * 60;
		float AnglerVoltage = -(anglerHomeVar-anglerStackVar)/VoltageInterval;
    angler.move_voltage(AnglerVoltage); //Sets angler voltage
    delay(10);
  }
  anglerBrakeMode(); //Sets brake mode of the angler depending on its position
  angler.move_velocity(0);
}

/**
 * Moves the angler back to the start position
 * endTime: Seconds
 */
void anglerHome(float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while (endT > millis()){
    if (anglerHomeVar > anglerPot.get_value()){break;}
    angler.move_voltage(-10000);
    delay(10);
  }
  anglerBrakeMode(); //Sets brake mode of the angler depending on its position
  angler.move_velocity(0);
}

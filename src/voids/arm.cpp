#include "main.h"
#include "define.hpp"
#include "voids.hpp"

/**
 * Sets brake mode of the arm depending on its position
 */
void armBrakeMode(){
  if (armPot.get_value() > armHold){
    arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  else {
    arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
  }
}

/**
 * Moves arm up to specificed spot
 * position: Potiometer value
 * velocity: 0 to 200
 * endTime: Seconds
 */
void armUp(int position, int velocity, float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while (endT > millis()){
    arm.move_velocity(velocity);
    if (position < armPot.get_value()){break;} //Stops movement if arm gets to desired position
    delay(10);
  }
  armBrakeMode(); //Sets the brake mode of the arm depending on its position
  arm.move_velocity(0); //Stops arm
}

/**
 * Moves arm down to specificed spot
 * position: Potiometer value
 * velocity: 0 to 200
 * endTime: Seconds
 */
void armDown(int position, int velocity, float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while (endT > millis()){
    arm.move_velocity(-velocity);
    if (position > armPot.get_value()){break;} //Stops movement if arm gets to desired position
    delay(10);
  }
  armBrakeMode(); //Sets the brake mode of the arm depending on its position
  arm.move_velocity(0); //Stops arm
}

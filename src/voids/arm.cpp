#include "main.h"
#include "define.hpp"
#include "voids.hpp"

Two_Bar::Two_Bar(){}

/**
 * Sets brake mode of the arm depending on its position
 */
void Two_Bar::brakeMode(){
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
void Two_Bar::up(int position, int velocity, float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while (endT > millis()){
    arm.move_velocity(velocity);
    if (position < armPot.get_value()){break;}
    delay(10);
  }
  Arm.brakeMode();
  arm.move_velocity(0);
}

/**
 * Moves arm down to specificed spot
 * position: Potiometer value
 * velocity: 0 to 200
 * endTime: Seconds
 */
void Two_Bar::down(int position, int velocity, float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while (endT > millis()){
    arm.move_velocity(-velocity);
    if (position > armPot.get_value()){break;}
    delay(10);
  }
  Arm.brakeMode();
  arm.move_velocity(0);
}

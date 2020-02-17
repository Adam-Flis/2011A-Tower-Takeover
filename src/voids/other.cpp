#include "main.h"
#include "define.hpp"
#include "voids.hpp"

/**
 * Converts seconds to milliseconds
 */
int secondsToMillis(float input){
  float output = input * 1000;
  return output;
}

/**
 * Calculates the time needed to end a movement
 */
int timeOut(int input){
  int output = input + millis();
  return output;
}

/**
 * Unfolds tray
 */
void unfold(){
  arm.move_velocity(200);
  delay(1200);
  arm.move_velocity(0);
  delay(100);
  arm.move_velocity(-200);
  delay(1200);
  arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
  arm.move_velocity(0);
}

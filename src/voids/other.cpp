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
 * Unfolds tray and deploys anti-tips
 */
void unfold(){
  arm.move_velocity(200);
  angler.move_voltage(7000);
  delay(500);
  angler.move_voltage(-8500);
  delay(100);
  arm.move_velocity(-200);
  delay(600);
  angler.set_brake_mode(MOTOR_BRAKE_BRAKE);
  arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
  angler.move_voltage(0);
  arm.move_velocity(0);
}

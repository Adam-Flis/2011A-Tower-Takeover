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
  arm.move_voltage(12000);
  angler.move_voltage(12000);
  delay(400);
  angler.move_voltage(-12000);
  arm.move_voltage(-12000);
  delay(450);
  arm.move_velocity(0);
  angler.move_velocity(0);
}

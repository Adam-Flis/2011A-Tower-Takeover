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

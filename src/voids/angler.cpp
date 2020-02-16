#include "main.h"
#include "define.hpp"
#include "voids.hpp"

Tilter::Tilter(){}

/**
 * Sets brake mode of the angler depending on its position
 */
void Tilter::brakeMode(){
  if (anglerPot.get_value() > anglerStack/2){
    angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  else {
    angler.set_brake_mode(MOTOR_BRAKE_COAST);
  }
}

/**
 * Moves the angler to the position needed to stack cubes
 * endTime: Seconds
 */
void stack(float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while(endT > millis()){
    float error = anglerStack - anglerPot.get_value();
    float voltage = error * angler_kP;
    if (error < 5){break;}
    if (voltage > 12000){
      voltage = 12000;
    }
    if (voltage < 7000){
      voltage = 7000;
    }
    angler.move_voltage(voltage);
    delay(10);
  }
  Angler.brakeMode();
  angler.move_velocity(0);
}

/**
 * Moves the angler back to the start position
 * endTime: Seconds
 */
void home(float endTime){
  int endT = timeOut(secondsToMillis(endTime));
  while (endT > millis()){
    angler.move_voltage(-10000);
    delay(10);
  }
  Angler.brakeMode();
  angler.move_velocity(0);
}

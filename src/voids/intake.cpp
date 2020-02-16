#include "main.h"
#include "define.hpp"
#include "voids.hpp"

Cube_Intake::Cube_Intake(){}

/**
 * Sets brake mode of intake to brake
 */
void Cube_Intake::brake(){
  LI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets velocity of intake between -200 to 200
 */
void Cube_Intake::move(int velocity){
  LI.move_velocity(velocity);
  RI.move_velocity(velocity);
}

/**
 * Stops movement of intake
 */
void Cube_Intake::stop(){
  Intake.brake();
  Intake.move(0);
}

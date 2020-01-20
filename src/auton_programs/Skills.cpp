#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 8 cubes from the field and sets 2 cubes in challices
//Points scored: 24
void Skills(){

  //Unfolds tray and sets state
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);

  //Intakes line of cubes
  Chassis->setMaxVelocity(75);
  Chassis->driveToPoint({8_ft, 0_ft});
  Chassis->turnAngle(45_deg);
  Chassis->

}

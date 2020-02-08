#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//Collects 8 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 8
void BlueSmall(){


  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.moveVelocity(-10);

  //Intakes 1st line of cubes
  Intake.moveVelocity(200);
  pros::delay(200);
  Drive(43, 70, 1500);

  //Drive towards scoring zone
  Drive(-31, -70, 1500);
  Intake.moveVelocity(100);
  Chassis->setMaxVelocity(100);
  Chassis->turnAngle(-135_deg);

  //Score cubes
  Intake.moveVelocity(-35);
  Drive(4.5, 40, 1200);
  AnglerStack(3000);

  //Drive away from scoring zone
  Drive(-12, -200, 1000);

}

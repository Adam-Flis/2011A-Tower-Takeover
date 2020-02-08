#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void RedSmall(){

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
  Chassis->turnAngle(140_deg);

  //Score cubes
  Intake.moveVelocity(-40);
  Drive(4.5, 50, 1200);
  AnglerStack(3000);

  //Drive away from scoring zone
  Drive(-12, -200, 1000);


}

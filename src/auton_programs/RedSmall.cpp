#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void RedSmall(){

  DriveVel(-10);
  Unfold();
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  DriveVel(0);
  Intake.moveVelocity(200);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(60);
  Chassis->moveDistance(3.4_ft);
  Intake.moveVelocity(60);

  //Turn at scoring zone
  Chassis->setMaxVelocity(120);
  Chassis->turnAngle(185_deg);

  //Drive at scoring zone
  Chassis->moveDistanceAsync(2.5_ft);
  pros::delay(750);
  Intake.moveVelocity(-35);
  pros::delay(450);
  Chassis->setMaxVelocity(40);
  pros::delay(500);
  Chassis->stop();

  //Score cubes
  AnglerStack(3000);
  pros::delay(200);

  //Drive out of zone
  Chassis->moveDistance(-1_ft);


}

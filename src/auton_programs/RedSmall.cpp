#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void RedSmall(){

  //Unfolds tray
  //Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(100);

  //Drive to intake cubes 1-5
  Chassis->setMaxVelocity(85);
  Chassis->moveDistance(3.5_ft);

  //Grab 6th cube
  Chassis->setMaxVelocity(160);
  Chassis->moveDistance(-3_in);
  Chassis->setMaxVelocity(200);
  Chassis->turnAngle(-18_deg);
  Chassis->moveDistanceAsync(1_ft);
  pros::delay(800);
  Chassis->stop();

  //Drive away from 6th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistance(-1_ft);
  Intake.moveVelocity(0);

  //Turn and drive at scoring zone
  Chassis->setMaxVelocity(200);
  Chassis->turnAngle(172_deg);
  Chassis->moveDistanceAsync(2.1_ft);
  Angler.moveVoltage(6000);
  Intake.moveVelocity(-40);
  pros::delay(1300);
  Chassis->stop();

  //Score cubes
  AnglerStack(1100);
  Chassis->moveDistance(-6_in);

}

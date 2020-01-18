#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void RedSmall(){

  //Unfolds tray
  Unfold();
  Chassis->setState({0_in, 0_in, 0_deg});
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);

  //Drive to intake cubes 1-5
  Chassis->setMaxVelocity(80);
  Chassis->moveDistanceAsync(3.5_ft);
  pros::delay(2500);
  Chassis->stop();

  //Grab 6th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistance(-4_in);
  Chassis->setMaxVelocity(200);
  Chassis->turnAngle(-18_deg);
  Chassis->moveDistanceAsync(9_in);
  pros::delay(700);
  Chassis->stop();

  //Drive away from 6th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistanceAsync(-1_ft);
  pros::delay(600);
  Chassis->stop();

  //Turn at scoring zone
  Chassis->setMaxVelocity(200);
  Chassis->turnAngleAsync(-180_deg);
  pros::delay(500);
  Intake.moveVelocity(0);
  Chassis->waitUntilSettled();

  //Drive at scoring zone
  Chassis->moveDistanceAsync(2.1_ft);
  Angler.moveVoltage(6000);
  Intake.moveVelocity(-35);
  pros::delay(550);
  Chassis->setMaxVelocity(100);
  pros::delay(950);
  Chassis->stop();

  //Score cubes
  AnglerStack(1400);
  Chassis->moveDistance(-6_in);
  Arm.setBrakeMode(AbstractMotor::brakeMode::brake);

}

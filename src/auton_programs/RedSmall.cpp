#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void RedSmall(){

  //Unfolds tray
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);

  //Drive to intake cubes 1-5
  Chassis->setMaxVelocity(80);
  Chassis->moveDistanceAsync(3.5_ft);
  pros::delay(2600);
  Chassis->stop();
  Intake.moveVelocity(100);

  //Grab 6th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistance(-5.5_in);
  Chassis->setMaxVelocity(200);
  Chassis->turnAngle(-15_deg);
  Intake.moveVelocity(200);
  Chassis->moveDistanceAsync(1_ft);
  pros::delay(900);
  Chassis->stop();

  //Drive away from 6th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistanceAsync(-1_ft);
  pros::delay(800);
  Chassis->stop();

  //Turn at scoring zone
  Chassis->setMaxVelocity(200);
  Chassis->turnAngleAsync(-190_deg);
  pros::delay(200);
  Intake.moveVelocity(0);
  Chassis->waitUntilSettled();

  //Drive at scoring zone
  Chassis->moveDistanceAsync(2.1_ft);
  Angler.moveVoltage(6000);
  Intake.moveVelocity(-35);
  pros::delay(400);
  Chassis->setMaxVelocity(120);
  pros::delay(1100);
  Chassis->stop();

  //Score cubes
  AnglerStack(2000);
  Chassis->moveDistance(-6_in);
  Arm.setBrakeMode(AbstractMotor::brakeMode::brake);

}

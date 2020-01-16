#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 7-8 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 7-8
void BlueSmall(){

  //Unfolds tray and sets starting point
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.moveVelocity(-10);
  pros::delay(100);

  //Drive to intake cubes 1-5
  Chassis->setMaxVelocity(80);
  Chassis->moveDistanceAsync(2.8_ft);
  Chassis->waitUntilSettled();

  //Drive to 2nd line
  Intake.moveVelocity(0);
  Chassis->setMaxVelocity(200);
  ProfileController->loadPath("/usd/A.csv", "A");
  ProfileController->setTarget("A", true, false);
  ProfileController->waitUntilSettled();

  //Drive at cubes 6-8
  Chassis->setMaxVelocity(80);
  Chassis->moveDistanceAsync(2.25_ft);
  Intake.moveVelocity(200);
  Chassis->waitUntilSettled();

  //Move angler forward to avoid chalice
  Intake.moveVelocity(0);
  Angler.moveVoltage(12000);
  pros::delay(100);

  //Turn to scoring zone
  Chassis->setMaxVelocity(55);
  Chassis->turnAngleAsync(-112_deg);
  pros::delay(250);
  Angler.moveVelocity(0);
  Angler.setBrakeMode(AbstractMotor::brakeMode::hold);
  Chassis->waitUntilSettled();
  pros::delay(100);

  //Drive at scoring zone
  Chassis->setMaxVelocity(100);
  Chassis->moveDistanceAsync(2.82_ft);
  pros::delay(380);
  Intake.moveVelocity(-25);
  pros::delay(550);
  Angler.moveVoltage(8000);
  pros::delay(1200);
  Chassis->setMaxVelocity(50);
  Chassis->waitUntilSettled();
  Intake.moveVelocity(0);

  //Set down stack
  AnglerStack(1500);
  Angler.moveVoltage(0);
  Intake.moveVelocity(-160);

  //Drive out of scoring zone
  Chassis->setMaxVelocity(200);
  Chassis->moveDistance(-1_ft);

}

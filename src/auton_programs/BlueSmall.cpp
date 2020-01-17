#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 6 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 6
void BlueSmall(){

  //Unfolds tray
  Unfold();
  Chassis->setState({0_in, 0_in, 0_deg});
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);

  //Drive to intake cubes 1-5
  Chassis->setMaxVelocity(80);
  Chassis->driveToPoint({3.5_ft, 0_ft});

  //Grab 6th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistance(-4_in);
  Chassis->setMaxVelocity(200);
  Chassis->turnAngle(18_deg);
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
  Chassis->turnAngleAsync(180_deg);
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
/*
//Unfolds tray and sets starting point
Chassis->setState({0_in, 0_in, 0_deg});
//Unfold();
Intake.moveVelocity(200);
Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
pros::delay(100);

//Drive to intake cubes 1-5
Chassis->setMaxVelocity(90);
Chassis->moveDistanceAsync(3.5_ft);
Chassis->waitUntilSettled();

//Drive to 2nd line
Intake.moveVelocity(0);
Chassis->setMaxVelocity(200);
//ProfileController->loadPath("/usd/A.csv", "A");
//ProfileController->setTarget("A", true, true);
ProfileController->waitUntilSettled();

//Drive at cubes 6-8
Chassis->setMaxVelocity(100);
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
Chassis->moveDistance(-1_ft);*/

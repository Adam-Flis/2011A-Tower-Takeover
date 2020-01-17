#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 5 cubes from the field
//Places cubes into the big scoring zone close to the edge
//Points scored: 5
void RedBigClose(){

  //Unfolds tray
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Drive at cube tower and intake cubes
  Chassis->setMaxVelocity(150);
  Chassis->moveDistanceAsync(3.3_ft);
  pros::delay(1600);
  Chassis->stop();
  pros::delay(700);

  //Grab 5th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistance(-6_in);
  Chassis->setMaxVelocity(200);
  Chassis->turnAngle(-18_deg);
  Chassis->moveDistanceAsync(1_ft);
  pros::delay(800);
  Chassis->stop();

  //Drive away from 5th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistanceAsync(-1_ft);
  pros::delay(600);
  Chassis->stop();

  //Turn at the scoring zone
  Chassis->setMaxVelocity(200);
  Chassis->turnAngleAsync(-105_deg);
  pros::delay(400);
  Intake.moveVelocity(0);
  Chassis->waitUntilSettled();

  //Drive at scoring zone
  Chassis->setMaxVelocity(140);
  Intake.moveVelocity(200); //Suck up cube
  Chassis->moveDistanceAsync(3.0_ft);
  pros::delay(1250);
  Intake.moveVelocity(-35);
  Chassis->stop();

  //Score cubes
  AnglerStack(2500);
  Chassis->moveDistance(-6_in);
  Arm.setBrakeMode(AbstractMotor::brakeMode::brake);

}

//Collects 5 cubes from the field
//Places cubes into the corner of the big scoring zone
//Points scored: 5
void RedBigCorner(){

  //Unfolds tray and sets starting point
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);

  //Drive at cube tower and sucks up cubes
  Chassis->moveDistance(3.8_ft);
  pros::delay(800);

  //Turn and drive at the scoring zone
  Intake.moveVelocity(0);
  Chassis->moveDistance(-4_in);
  Chassis->turnAngle(-120_deg);
  Chassis->moveDistanceAsync(3.25_ft);
  pros::delay(250);
  Intake.moveVelocity(200); //Suck up cube
  pros::delay(1250);

  //Set down stack
  Intake.moveVelocity(-40);
  AnglerStack(3200);
  pros::delay(200);
  Chassis->waitUntilSettled();
  Intake.moveVelocity(-100);
  pros::delay(1000);

  //Drive out of scoring zone
  Chassis->moveDistance(-1_ft);

}

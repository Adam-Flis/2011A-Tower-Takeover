#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 5 cubes from the field
//Places cubes into the big scoring zone close to the edge
//Points scored: 5
void RedBig(){

  //Unfolds tray
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Drive at cube tower and intake cubes
  Chassis->setMaxVelocity(180);
  Chassis->moveDistanceAsync(3.4_ft);
  pros::delay(1500);
  Chassis->stop();
  pros::delay(600);

  //Grab 5th cube
  Chassis->setMaxVelocity(170);
  Intake.moveVelocity(100);
  Chassis->moveDistance(-6_in);
  Chassis->setMaxVelocity(200);
  Chassis->turnAngle(-20_deg);
  Intake.moveVelocity(200);
  Chassis->moveDistanceAsync(1.2_ft);
  pros::delay(1100);
  Chassis->stop();

  //Drive away from 5th cube
  Chassis->setMaxVelocity(170);
  Chassis->moveDistanceAsync(-1_ft);
  pros::delay(650);
  Chassis->stop();

  //Turn at the scoring zone
  pros::delay(500);
  Angler.moveVoltage(8000);
  pros::delay(500);
  Angler.moveVoltage(0);
  Chassis->setMaxVelocity(200);
  Chassis->turnAngleAsync(-95_deg);
  pros::delay(400);
  Intake.moveVelocity(0);
  Chassis->waitUntilSettled();

  //Drive at scoring zone
  Chassis->setMaxVelocity(100);
  Intake.moveVelocity(200); //Suck up cube
  Chassis->moveDistanceAsync(3.0_ft);
  pros::delay(1450);
  Intake.moveVelocity(-35);
  Chassis->stop();

  //Score cubes
  RightSide.moveVelocity(150);
  pros::delay(300);
  RightSide.moveVelocity(0);
  AnglerStack(2500);
  Chassis->moveDistance(-6_in);
  Arm.setBrakeMode(AbstractMotor::brakeMode::brake);

}

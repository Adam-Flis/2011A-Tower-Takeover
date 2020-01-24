#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 16 cubes from the field and sets 3 cubes in challices
//Points scored: 64
void Skills(){

  //Unfolds tray and sets state
  Chassis->setState({0_in, 0_in, 0_deg});
  Chassis->driveToPoint({0.05_ft, 0_ft});
  //Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(60);
  Chassis->driveToPoint({2.4_ft, 0_ft});

  //Turn at challice cube
  Chassis->turnAngle(-23_deg);

  //Grab 6th cube
  Chassis->moveDistance(4.45_in);
  Chassis->waitUntilSettled();
  pros::delay(300);
  Intake.moveVelocity(35);

  //Drive away from chalice
  Chassis->moveDistance(-8_in);
  pros::delay(300);
  Chassis->turnAngle({140_deg});

  //Drive to score
  Chassis->moveDistance(1.5_ft);
  RightSide.moveVelocity(100);
  Intake.moveVelocity(-40);
  pros::delay(550);
  RightSide.moveVelocity(0);
  AnglerStack(3000);

  //Drive away from zone
  Chassis->moveDistance(-1_ft);
  Intake.moveVelocity(0);
  Chassis->turnAngle({100_deg});
  AnglerHome(4000);


  //Drive at challice and grab cube
  Intake.moveVelocity(200);
  Chassis->moveDistance(2.5_ft);
  pros::delay(500);

  //Drive away from challice
  Intake.moveVelocity(50);
  Chassis->moveDistance(-6_in);
  Intake.moveVelocity(-200);
  pros::delay(400);
  Intake.moveVelocity(0);
  ArmMediumChalice(900);

  //Score in chalice
  Chassis->moveDistance(11_in);
  Intake.moveVelocity(-200);
  pros::delay(500);
  Intake.moveVelocity(0);
  Chassis->moveDistance(-5_in);
  ArmHome(1000);

  //Go at next line
  Chassis->turnAngle(65_deg);
  Intake.moveVelocity(200);
  Chassis->moveDistance(4_ft);


}

#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 16 cubes from the field and sets 3 cubes in challices
//Points scored: 64
void Skills(){

  //Unfolds tray and sets state
  Chassis->setState({0_in, 0_in, 0_deg});
  //Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(80);
  Chassis->driveToPoint({2.8_ft, 0_ft});

  //Turn at challice cube
  Chassis->setMaxVelocity(200);
  Chassis->turnToAngle(-25_deg);

  //Grab 6th cube
  Chassis->setMaxVelocity(150);
  Chassis->moveDistanceAsync(2_ft);
  pros::delay(500);
  Chassis->stop();
  pros::delay(400);
  Intake.moveVelocity(50);

  //Drive away from chalice
  Chassis->setMaxVelocity(200);
  Chassis->moveDistance(-1_ft);
  Chassis->turnToAngle({152_deg});

  //Drive to score
  Chassis->moveDistanceAsync(3_ft);
  pros::delay(300);
  Chassis->setMaxVelocity(170);
  Intake.moveVelocity(-35);
  pros::delay(350);
  Chassis->stop();
  AnglerStack(3000);

  //Drive away from zone
  Chassis->setMaxVelocity(200);
  Chassis->moveDistance(-0.8_ft);
  Intake.moveVelocity(0);
  Chassis->turnToAngle({-90_deg});
  AnglerHome(4000);

  //Drive at challice and grab cube
  Intake.moveVelocity(200);
  Chassis->driveToPoint({1.5_ft, -2.2_ft});
  pros::delay(300);

  //Drive away from challice
  Intake.moveVelocity(50);
  Chassis->moveDistanceAsync(-6_in);
  Intake.moveVelocity(-200);
  pros::delay(300);
  Intake.moveVelocity(0);
  ArmMediumChalice(3000);



}

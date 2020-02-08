#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//Collects 16 cubes from the field and sets 3 cubes in challices
//Points scored: 64
void Skills(){

  //Unfolds tray and sets state
  //DriveVel(-10);
  //Unfold();
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  DriveVel(0);
  Arm.moveVelocity(-10);
  Chassis->setMaxVelocity(100);
  pros::delay(200);

  //Intakes 1st line of cubes
  Intake.moveVelocity(200);
  Drive(110, 65, 6000);

  //Go to scoring zone
  Intake.moveVelocity(0);
  Drive(-10, -65, 1500);
  Intake.moveVelocity(100);
  pros::delay(100);
  Chassis->turnAngle(55_deg);
  pros::delay(100);
  Drive(14, 40, 1500);

  //Score cubes
  Intake.moveVelocity(-30);
  AnglerStack(3000);

  //Drive out of scoring zone
  Drive(-18, 100, 1300);
  pros::delay(100);
  Chassis->turnAngle(-55_deg);
  Intake.moveVelocity(0);
  AnglerHome(2000);

  //Line up on wall
  ArmUp(LowChalice, 2000);
  Drive(18, 120, 2300);

  //Drive away from wall
  Drive(-12, -80, 1000);
  pros::delay(100);
  ArmDown(ArmStart, 1500);

  //Go to challice
  Chassis->turnAngle(-110_deg);
  pros::delay(100);
  Intake.moveVelocity(200);
  Drive(30, 100, 2300);

  //Score cube
  Drive(-6, -60, 800);
  Intake.moveVelocity(-200);
  pros::delay(400);
  Intake.moveVelocity(0);
  ArmUp(LowChalice, 3000);
  Drive(8, 60, 800);
  Intake.moveVelocity(-200);




}

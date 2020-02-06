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
  Intake.moveVelocity(200);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(65);
  Chassis->moveDistanceAsync({9.8_ft});
  pros::delay(7000);
  Chassis->stop();
  Chassis->moveDistanceAsync(3.0_ft);
  pros::delay(2500);
  Chassis->stop();

  //Go to scoring zone
  Intake.moveVelocity(100);
  Chassis->setMaxVelocity(150);
  Chassis->moveDistance({-1_ft});
  Chassis->turnAngle(55_deg);
  Chassis->setMaxVelocity(65);
  Chassis->moveDistanceAsync(2.0_ft);
  pros::delay(900);
  Chassis->stop();

  //Score cubes
  Intake.moveVelocity(-30);
  AnglerStack(3000);

  //Drive out of scoring zone
  Chassis->setMaxVelocity(100);
  Chassis->moveDistance({-2_ft});
  Chassis->turnAngle(-55_deg);
  Intake.moveVelocity(0);
  AnglerHome(2000);

  //Line up on wall
  ArmUp(LowChalice, 2000);
  Chassis->moveDistanceAsync(3_ft);
  pros::delay(2500);
  Chassis->stop();

  //Drive away from wall
  Chassis->moveDistance(-1.3_ft);
  ArmDown(ArmStart, 1500);

  //Go to challice
  Chassis->setMaxVelocity(150);
  Chassis->turnAngle(-120_deg);
  Chassis->moveDistanceAsync(3_ft);
  pros::delay(2000);
  Intake.moveVelocity(200);
  Chassis->waitUntilSettled();

  //Score cube
  Chassis->moveDistance(-1_ft);
  Intake.moveVelocity(-200);
  pros::delay(400);
  Intake.moveVelocity(0);
  ArmUp(LowChalice, 3000);
  Chassis->moveDistance(8_in);
  Intake.moveVelocity(-200);
  



}

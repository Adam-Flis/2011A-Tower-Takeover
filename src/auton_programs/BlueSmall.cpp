#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//Collects 8 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 8
void BlueSmall(){

  DriveVel(-10);
  Unfold();
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  DriveVel(0);
  Intake.moveVelocity(200);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(60);
  Chassis->moveDistance(3.4_ft);
  Intake.moveVelocity(60);

  //Turn at scoring zone
  Chassis->setMaxVelocity(120);
  Chassis->turnAngle(-185_deg);

  //Drive at scoring zone
  Chassis->moveDistanceAsync(2.5_ft);
  pros::delay(750);
  Intake.moveVelocity(-35);
  pros::delay(450);
  Chassis->setMaxVelocity(40);
  pros::delay(500);
  Chassis->stop();

  //Score cubes
  AnglerStack(3000);
  pros::delay(200);

  //Drive out of zone
  Chassis->moveDistance(-1_ft);

}

/*
//Unfolds tray and sets state
Chassis->setState({0_in, 0_in, 0_deg});
Unfold();
Intake.moveVelocity(200);
Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
pros::delay(200);

//Intakes 1st line of cubes
Chassis->setMaxVelocity(75);
Chassis->driveToPoint({3_ft, 0_ft});
Intake.moveVelocity(100);

//Drive to 2nd line of cubes
Chassis->driveToPoint({0_ft, 2_ft});
Intake.moveVelocity(200);

//Intake 2nd line of cubes
Chassis->setMaxVelocity(75);
Chassis->driveToPoint({3_ft, 2_ft});
Intake.moveVelocity(100);

//Turn at scoring zone
Angler.moveVoltage(5000);
Chassis->turnToAngle(-135_deg);
Angler.moveVelocity(0);
Angler.setBrakeMode(AbstractMotor::brakeMode::hold);

//Drive to scoring zone
Chassis->driveToPoint({0.5_ft, 0_ft});
Intake.moveVelocity(-30);
Chassis->setMaxVelocity(100);
Chassis->moveDistanceAsync(2_ft);
pros::delay(1200);
Chassis->stop();

//Score cubes
AnglerStack(2000);
Chassis->moveDistance(-1_ft);*/

#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//Collects 8 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 8
void BlueSmall(){

  Chassis->setState({0_in, 0_in, 0_deg});
  Chassis->setMaxVelocity(40);
  Chassis->moveDistance(4_in);
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(60);
  Chassis->driveToPoint({3.4_ft, 0_ft});
  Intake.moveVelocity(100);

  //Turn at scoring zone
  Chassis->turnAngle(-150_deg);

  //Drive at scoring zone
  Chassis->setMaxVelocity(90);
  Chassis->moveDistanceAsync(3.0_ft);
  pros::delay(400);
  Intake.moveVelocity(-35);
  pros::delay(600);
  Chassis->setMaxVelocity(40);
  pros::delay(400);
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

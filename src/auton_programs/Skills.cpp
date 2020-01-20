#include "main.h"
#include "robot.hpp"
#include "define.hpp"

//Collects 16 cubes from the field and sets 3 cubes in challices
//Points scored: 64
void Skills(){

  //Unfolds tray and sets state
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Intake.moveVelocity(200);
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(75);
  Chassis->driveToPoint({8.5_ft, 0_ft});

  //Go to scoring zone and score
  Intake.moveVelocity(50);
  Chassis->setMaxVelocity(200);
  Chassis->turnToAngle(45_deg);
  Chassis->setMaxVelocity(100);
  Chassis->moveDistanceAsync(2_ft);
  pros::delay(1000);
  Intake.moveVoltage(-30);
  pros::delay(1000);
  Chassis->stop();
  AnglerStack(3000);

  //Drive away from zone and go to chalice
  Chassis->driveToPoint({7.5_ft, -1_ft});
  Chassis->turnToAngle(180_deg);
  Intake.moveVoltage(200);
  Chassis->driveToPoint({5_ft, -1_ft});

  //Score cube in 1st chalice
  Chassis->driveToPoint({5.5_ft, -1_ft});
  Intake.moveVelocity(-200);
  pros::delay(500);
  Intake.moveVelocity(0);
  ArmMediumChalice(3000);
  Chassis->driveToPoint({5_ft, -1_ft});
  Intake.moveVelocity(-200);
  pros::delay(1500);
  Intake.moveVelocity(0);

  //Drive away from chalice and turn at next one
  Chassis->driveToPoint({8.5_ft, -1_ft});
  ArmHome(2000);
  Chassis->turnToAngle(-90_deg);

  //Drive at 2nd challice and intake cube
  Intake.moveVelocity(200);
  Chassis->driveToPoint({8.5_ft, -3.5_ft});

  //Score cube in 2nd chalice
  Chassis->driveToPoint({8.5_ft, -3_ft});
  Intake.moveVelocity(-200);
  pros::delay(500);
  Intake.moveVelocity(0);
  ArmLowChalice(2000);
  Chassis->driveToPoint({8.5_ft, -4_ft});
  Arm.moveVelocity(-200);
  pros::delay(200);
  Intake.moveVelocity(-200);
  ArmLowChalice(2000);
  Intake.moveVelocity(0);

  //Drive away from chalice and go to 2nd cube line
  Chassis->driveToPoint({8.5_ft, -2_ft});
  ArmHome(3000);
  Chassis->turnToAngle(180_deg);

  //Drive and intake 2nd line of cubes
  Chassis->setMaxVelocity(75);
  Intake.moveVelocity(200);
  Chassis->driveToPoint({0.5_ft, -2_ft});

  //Go to scoring zone
  Chassis->setMaxVelocity(200);
  Chassis->turnToAngle(90_deg);
  Chassis->driveToPoint({0.5_ft,0_ft});

  //Score cubes
  Chassis->setMaxVelocity(100);
  Chassis->moveDistanceAsync(2_ft);
  pros::delay(1000);
  Intake.moveVoltage(-30);
  pros::delay(1000);
  Chassis->stop();
  AnglerStack(3000);

  //Drive away from zone and go to chalice
  Chassis->setMaxVelocity(200);
  Chassis->driveToPoint({0.5_ft, 0_ft});
  Chassis->turnToAngle({270_deg});
  Intake.moveVoltage(200);
  Chassis->driveToPoint({0.5_ft, -4.5_ft});
  pros::delay(500);

  //Score cube in 3rd chalice
  Intake.moveVoltage(0);
  Chassis->driveToPoint({0.5_ft, -4_ft});
  Intake.moveVelocity(-200);
  pros::delay(500);
  Intake.moveVelocity(0);
  ArmMediumChalice(3000);
  Chassis->driveToPoint({0.5_ft, -4.5_ft});
  Intake.moveVelocity(-200);
  pros::delay(1500);
  Intake.moveVelocity(0);
  Chassis->driveToPoint({0.5_ft, -4_ft});

}

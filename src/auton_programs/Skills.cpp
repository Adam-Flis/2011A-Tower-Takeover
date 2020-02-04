#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//Collects 16 cubes from the field and sets 3 cubes in challices
//Points scored: 64
void Skills(){

  //Unfolds tray and sets state
  DriveVel(-10);
  Chassis->setState({0_in, 0_in, 0_deg});
  Unfold();
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  DriveVel(0);
  Intake.moveVelocity(200);
  pros::delay(200);

  //Intakes 1st line of cubes
  Chassis->setMaxVelocity(60);
  Chassis->moveDistance({10_ft});

  //Go to scoring zone
  Chassis->moveDistance({-1_ft});
  Chassis->turnAngle(45_deg);
  Chassis->moveDistanceAsync(3_ft);
  pros::delay(1500);
  Chassis->stop();

  //Score cubes
  


}

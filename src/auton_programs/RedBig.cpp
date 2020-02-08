#include "main.h"
#include "setup/define.hpp"
#include "setup/robot.hpp"

//Collects 5 cubes from the field
//Places cubes into the big scoring zone close to the edge
//Points scored: 5
void RedBig(){


    //Unfold();
    Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
    Arm.moveVelocity(-10);
    DriveVel(0);

    //Intakes 1st cubes
    Intake.moveVelocity(200);
    pros::delay(400);
    Drive(11, 70, 1000);
    pros::delay(200);
    Intake.moveVelocity(0);

    //turn at 3 cube
    Chassis->setMaxVelocity(90);
    Chassis->turnAngle(100_deg);
    pros::delay(200);
    Intake.moveVelocity(200);

    //drive towards cubes
    Drive(7, 50, 800);
    pros::delay(200);
    Chassis->setMaxVelocity(90);
    Chassis->turnAngle(60_deg);
    Intake.moveVelocity(0);

    //drive backward
    Drive(-11, -60, 1000);
    Chassis->setMaxVelocity(100);
    Chassis->turnAngle(-250_deg);
    pros::delay(200);
    Intake.moveVelocity(200);

    //drive to 4 cubes
    Drive(11, 50, 1000);
    pros::delay(200);
    Chassis->setMaxVelocity(90);
    Chassis->turnAngle(-60_deg);
    Intake.moveVelocity(0);
    //drive to zone
    Intake.moveVelocity(50);
    Drive(9, 50, 1000);
    AnglerStack(3000);

    //Drive away from scoring zone
    Drive(-12, -200, 1000);


}

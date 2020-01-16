#include "main.h"
#include "robot.hpp"

//Code that runs when you start the program
void initialize(){
  pros::lcd::initialize();
  ProfileController->generatePath({{0_ft, 0_ft, 0_deg}, {2.45_ft, -1.3_ft, 0_deg}}, "A");
  ProfileController->storePath("/usd/A.csv", "A");

}

//Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled(){

}

//Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize(){

}

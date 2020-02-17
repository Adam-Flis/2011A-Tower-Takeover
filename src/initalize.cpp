#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Code that runs when you start the program
void initialize(){
  lcd::initialize();
  IMU.reset();
  while (IMU.is_calibrating()){
    lcd::set_text(1, "IMU Calibrating");
    delay(10);
  }
   rEnc.reset();
  lEnc.reset();
}

//Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled(){

}

//Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize(){

}

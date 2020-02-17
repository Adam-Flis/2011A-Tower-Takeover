#include "main.h"
#include "define.hpp"
#include "voids.hpp"

/**
 * Converts velocity to velocity
 */
int velocityToVelocity(int input){
  int output = input * 0.8;
  return output;
}

/**
 * Converts velocity to voltage
 */
float velocityToVoltage (float input){
  int output = (input * 60);
  return output;
}

/**
 * 360 degrees per rotation of wheel
 * 2.75 in diameter wheels
 */
int inchToTicks(float input){
  float output = (input * 360)/(2.75 * M_PI);
  return output;
}

int degreesToTicks(float input){
  int output = input * 100;
  return output;
}

/* ********** PID Constants ********** */

//Drive
float kP = 20;
float kD = 5;
float kI = 0.01;

//Turn
float kP_t = 6;
float kD_t = 30;
float kI_t = 0.01;

//Drift
float kP_d = 500;
float kD_d = 300;

float intergralActive = inchToTicks(3);
float intergralActive_t = degreesToTicks(5);

/**
 * Resets the sensors except the IMU on the drivetrain
 */
void driveReset(){
  LFD.tare_position();
  LBD.tare_position();
  RFD.tare_position();
  RBD.tare_position();
  rEnc.reset();
  lEnc.reset();
}

/**
 * Sets brake mode of drivetrain
 * mode: brake, hold, or coast
 */
void driveMode(string mode){
  if (mode == "brake"){
    LFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
    LBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
    RFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
    RBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  }
  if (mode == "hold"){
    LFD.set_brake_mode(MOTOR_BRAKE_HOLD);
    LBD.set_brake_mode(MOTOR_BRAKE_HOLD);
    RFD.set_brake_mode(MOTOR_BRAKE_HOLD);
    RBD.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  if (mode == "coast"){
    LFD.set_brake_mode(MOTOR_BRAKE_COAST);
    LBD.set_brake_mode(MOTOR_BRAKE_COAST);
    RFD.set_brake_mode(MOTOR_BRAKE_COAST);
    RBD.set_brake_mode(MOTOR_BRAKE_COAST);
  }
}

/**
 * Sets Velocity of drive train
 * side: right, left, both
 * velocity: -250 to 250
 */
void driveMove(string side, int velocity){
  if (side == "right"){
    LFD.move_velocity(velocityToVelocity(velocity));
    LBD.move_velocity(velocityToVelocity(velocity));
  }
  if (side == "left"){
    RFD.move_velocity(velocityToVelocity(velocity));
    RBD.move_velocity(velocityToVelocity(velocity));
  }
  if (side == "both"){
    LFD.move_velocity(velocityToVelocity(velocity));
    LBD.move_velocity(velocityToVelocity(velocity));
    RFD.move_velocity(velocityToVelocity(velocity));
    RBD.move_velocity(velocityToVelocity(velocity));
  }
}

void moveLeft(int voltage){
   LFD.move_voltage(voltage);
   LBD.move_voltage(voltage);
}

void moveRight(int voltage){
   RFD.move_voltage(voltage);
   RBD.move_voltage(voltage);
}

/**
 * Stops the drivetrain
 */
void driveStop(){
  driveMode("brake");
  driveMove("both", 0);
}

float IMURotation;

/**
 * Moves drivetrain in specificed direction
 * direction f, b, l, or r
 * target: inches or degrees
 * maxVelocity: 0 to 250
 * endTime: seconds
 */
 void drive(string direction, float target, int maxVelocity, float endTime) {
   driveReset();
   //Error var declarations//
   float error;
   float error_drift;
   float lastError;
   float lastError_d;
   float rotation;
   //Calc var declarations//
   float proportion;
   float proportion_drift;
   float intergral;
   float derivative;
   float derivative_d;
   ////////////////////////
   float intergralLimit = (maxVelocity / kI) / 50;
   float intergralLimit_t = (maxVelocity / kI_t) / 50;
   //Motor output var declarations//
   float targetVoltage;
   float finalVoltage;
   //Timeout var declarations
   int endT = timeOut(secondsToMillis(endTime));

   //Loop continues until time out is reached
   while (millis() < endT) {
     //PID calculation when the direction desired is forward/ backwards
     if (direction == "f" || direction == "b") {

       //Error reestablished at the start of the loop
       error = inchToTicks(target) - (fabs(rEnc.get_value() + lEnc.get_value()) / 2);
       //Proportion stores the error until it can be multiplied by the constant
       proportion = error;
       //Breaks loop when the robot gets close to target
       if (error < 5) {
         break;
       }
       //Intergral takes area under the error and is useful for major adjustment
       if (fabs(error) < intergralActive) {
         intergral = intergral + error;
       } else {
         intergral = 0;
       }
       //Set intergral output to limit
       if (intergral > intergralLimit) {
         intergral = intergralLimit;
       } else if (intergral < intergralLimit) {
         intergral = -intergralLimit;
       }

       //Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
       derivative = error - lastError;
       lastError = error;
       //Sets var equal to zero if no adjustment is needed
       if (error == 0) {
         derivative = 0;
       }

       //Convert target velocity to voltage
       targetVoltage = velocityToVoltage(velocityToVelocity(maxVelocity));

       //Final output of drive alg that applies constants to the PID factors
       finalVoltage = kP * proportion + kI * intergral + kD * derivative;

       if (finalVoltage > targetVoltage) {
         finalVoltage = targetVoltage;
       } else if (finalVoltage < -targetVoltage) {
         finalVoltage = -targetVoltage;
       }

       //Establishes the initial error simply as the value of the IMU since its supposed to be 0
       error_drift = IMU.get_rotation() - (IMURotation) / 100;
       //Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
       derivative = error_drift - lastError_d;
       lastError_d = IMU.get_rotation();

       proportion_drift = error_drift * kP_d;

       if (direction == "f") {
         moveRight(finalVoltage + proportion_drift);
         moveLeft(finalVoltage - proportion_drift);
       } else if (direction == "b") {
         moveRight(-finalVoltage - proportion_drift);
         moveLeft(-finalVoltage + proportion_drift);
       }
     }

     //PID Calculation when the direction desired is turn center
     else if (direction == "r" || direction == "l") {

       //Rotational Value around z-axis
       rotation = degreesToTicks(IMU.get_rotation()) - IMURotation;

       //Error reestablished at the start of the loop
       error = degreesToTicks(target) - fabs(rotation);
       //Proportion stores the error until it can be multiplied by the constant
       proportion = error;
       //Breaks loop when the robot gets close to target
       if (error < 5) {
         break;
       }
       //Intergral takes area under the error and is useful for major adjustment
       if (fabs(error) < intergralActive_t) {
         intergral = intergral + error;
       } else {
         intergral = 0;
       }
       //Set intergral output to limit
       if (intergral > intergralLimit_t) {
         intergral = intergralLimit_t;
       } else if (intergral < intergralLimit_t) {
         intergral = -intergralLimit_t;
       }

       //Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
       derivative = error - lastError;
       lastError = error;
       //Sets var equal to zero if no adjustment is needed
       if (error == 0) {
         derivative = 0;
       }

       //Convert target velocity to voltage
       targetVoltage = velocityToVoltage(velocityToVelocity(maxVelocity));

       //Final output of drive alg that applies constants to the PID factors
       finalVoltage = kP_t * proportion + kI_t * intergral + kD_t * derivative;

       if (finalVoltage > targetVoltage) {
         finalVoltage = targetVoltage;
       } else if (finalVoltage < -targetVoltage) {
         finalVoltage = -targetVoltage;
       }

       if (direction == "r") {
         moveRight(-finalVoltage);
         moveLeft(finalVoltage);
       } else if (direction == "l") {
         moveRight(finalVoltage);
         moveLeft(-finalVoltage);
       }
       delay(20);
     }
   }
   driveMode("brake");
   driveStop();
   driveReset();
   IMURotation = IMURotation + rotation;
 }

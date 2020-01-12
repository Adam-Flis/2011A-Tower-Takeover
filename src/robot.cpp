#include "main.h"
#include "define.hpp"

/* ********** Chassis Builder Parameters ********** */

#define Tracking_Length 7_in //Distance between tracking wheels
#define Tracking_Diameter 2.75_in //Wheel diameter of tracking wheel
#define Middle_Length 0.5_in //Distance of the middle tracking wheel to the center of turning

/* ********** Distance PID Parameters ********** */

#define Distance_kP 0.00083f
#define Distance_kI 0.00000f
#define Distance_kD 0.0000f

/* ********** Turn PID Parameters ********** */

#define Turn_kP 0.001f
#define Turn_kI 0.0000012f
#define Turn_kD 0.000042f

/* ********** Angle PID Parameters ********** */

#define Angle_kP 0.0f
#define Angle_kI 0.0f
#define Angle_kD 0.0f

/* ********** 2D Motion Profiling Parameters ********** */

#define Max_Linear_Velocity 2.0
#define Max_Linear_Acceleration 4.5
#define Max_Linear_Jerk 4.0

/* ********** Other Parameters ********** */

#define Arm_kP 14.0f

/* ********** Drivetrain ********** */

//Generates the chassis needed to use Okapi's built in PIDs, odometry, and 2D motion profiling
auto Chassis = ChassisControllerBuilder()
  .withMotors(LeftSide, RightSide)
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 12_in}, imev5GreenTPR})
  .withSensors(LeftEnc, RightEnc, MiddleEnc)
  .withOdometry( {{Tracking_Diameter,Tracking_Length,Middle_Length,Tracking_Diameter}, quadEncoderTPR})
  .buildOdometry();

//Establishes the controller used in Okapi's built in 2D motion profiling
auto ProfileController = AsyncMotionProfileControllerBuilder()
  .withLimits({Max_Linear_Velocity, Max_Linear_Acceleration, Max_Linear_Jerk})
  .withOutput(Chassis)
  .buildMotionProfileController();

/* ********** Other ********** */

//Adds TimeInput and current pros time
//Used to make time out statements
int Time(int TimeInput){
  int EndTime = pros::millis() + TimeInput;
  return EndTime;
}

//Unfolds the tray during the autonomous period
void Unfold(){
  Arm.moveVoltage(12000);
  pros::delay(100);
  Intake.moveVoltage(12000);
  pros::delay(500);
  Arm.moveVoltage(-12000);
  pros::delay(650);
  Arm.setBrakeMode(AbstractMotor::brakeMode::brake);
  Arm.moveVelocity(0);
}

/* ********** Arm Voids ********** */

//Moves the arm to the home/start position
//Time out in milliseconds
void ArmHome(int TimeOut){
  int EndTime = Time(TimeOut);
  while (EndTime != pros::millis()){
    int Error = ArmPot.get() - ArmStart;
    float Voltage = Error * Arm_kP;
    if (Error < 5){break;} //Breaks or ends loop if arm reaches position
    if (Voltage > 12000){
      Voltage = 12000; //Maximum arm voltage for down
    }
    else if (Voltage < 8000){
      Voltage = 8000; //Minimum arm voltage for down
    }
    Arm.moveVoltage(-Voltage); //Sets arm voltage
    pros::delay(10); //Loop speed, prevents overload
  }
  Arm.setBrakeMode(AbstractMotor::brakeMode::brake); //Set brake mode brake
  Arm.moveVelocity(0); //Stops arm
}

//Moves the arm to the low chalice position
//Time out in milliseconds
void ArmLowChalice(int TimeOut){
  int EndTime = Time(TimeOut);
  while (EndTime != pros::millis()){
    int Error = LowChalice - ArmPot.get();
    float Voltage = Error * Arm_kP;
    if (Error < 5){break;} //Breaks or ends loop if arm reaches position
    if (Voltage > 12000){
      Voltage = 12000; //Maximum arm voltage for going up
    }
    else if (Voltage < 9600){
      Voltage = 9600; //Minimum arm voltage for going up
    }
    Arm.moveVoltage(Voltage); //Sets arm voltage
    pros::delay(10); //Loop speed, prevents overload
  }
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold); //Set brake mode hold
  Arm.moveVelocity(0); //Stops arm
}

//Moves the arm to the medium chalice position
//Time out in milliseconds
void ArmMediumChalice(int TimeOut){
  int EndTime = Time(TimeOut);
  while (EndTime != pros::millis()){
    int Error = MediumChalice - ArmPot.get();
    float Voltage = Error * Arm_kP;
    if (Error < 5){break;} //Breaks or ends loop if arm reaches position
    if (Voltage > 12000){
      Voltage = 12000; //Maximum arm voltage for going up
    }
    else if (Voltage < 9600){
      Voltage = 9600; //Minimum arm voltage for going up
    }
    Arm.moveVoltage(Voltage); //Sets arm voltage
    pros::delay(10); //Loop speed, prevents overload
  }
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold); //Set brake mode hold
  Arm.moveVelocity(0); //Stops arm
}

/* ********** Angler Voids ********** */

//Moves the angler to the home or start position
//Time out in milliseconds
void AnglerHome(int TimeOut){
  int EndTime = Time(TimeOut);
  while (EndTime != pros::millis()){
    int Error = AnglerPot.get() - AnglerPotMin;
    float Voltage = Error * Angler_kP;
    if (Error < 10){break;} //Breaks or ends loop if angler reaches position
    if (Voltage > 12000){
      Voltage = 12000; //Maximum angler voltage for going down
    }
    else if (Voltage < 8000){
      Voltage = 8000; //Minimum angler voltage for going down
    }
    Angler.moveVoltage(-Voltage); //Sets angler voltage
    pros::delay(10); //Loop speed, prevents overload
  }
  Angler.setBrakeMode(AbstractMotor::brakeMode::brake); //Set brake mode brake
  Angler.moveVelocity(0); //Stops angler
}

//Moves the angler to the position needed to set down a cube stack
//Time out in milliseconds
void AnglerStack(int TimeOut){
  int EndTime = Time(TimeOut);
  while (EndTime != pros::millis()){
    int Error = AnglerPotMax - AnglerPot.get();
    float Voltage = Error * Angler_kP;
    if (Error < 10){break;} //Breaks or ends loop if angler reaches position
    if (Voltage > 12000){
      Voltage = 12000; //Maximum angler voltage for going up
    }
    else if (Voltage < 4000){
      Voltage = 4000; //Minimum angler voltage for going up
    }
    Angler.moveVoltage(Voltage); //Sets angler voltage
    pros::delay(10); //loop speed, prevents overload
  }
  Angler.setBrakeMode(AbstractMotor::brakeMode::hold); //Set brake mode hold
  Angler.moveVelocity(0); //Stops angler
}

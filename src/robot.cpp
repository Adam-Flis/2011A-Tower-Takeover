#include "main.h"
#include "define.hpp"

/* ********** Chassis Builder Parameters ********** */

#define Tracking_Length 13_in //Distance between tracking wheels
#define Tracking_Diameter 2.75_in //Wheel diameter of tracking wheel
#define Middle_Length 2.0_in //Distance of the middle tracking wheel to the center of turning

/* ********** Distance PID Parameters ********** */

#define Distance_kP 0.00124f
#define Distance_kI 0.0000005f
#define Distance_kD 0.0f

/* ********** Turn PID Parameters ********** */

#define Turn_kP 0.00113f
#define Turn_kI 0.0000001f
#define Turn_kD 0.0f

/* ********** Angle PID Parameters ********** */

#define Angle_kP 0.0f
#define Angle_kI 0.0f
#define Angle_kD 0.0f

/* ********** 2D Motion Profiling Parameters ********** */

#define Max_Linear_Velocity 1.0 //Maximum linear velocity of the chassis in m/s
#define Max_Linear_Acceleration 2.0 //Maximum linear acceleration of the chassis in m/s/s
#define Max_Linear_Jerk 3.0 //Maximum linear jerk of the chassis in m/s/s/s

/* ********** Other Parameters ********** */

#define Arm_kP 14.2f

/* ********** Drivetrain ********** */

//Generates the chassis needed to use Okapi's built in PIDs, odometry, and 2D motion profiling
auto Chassis = ChassisControllerBuilder()
  .withMotors(LeftSide, RightSide)
  .withGains({Distance_kP, Distance_kI, Distance_kD}, //Distance controller gains
             {Turn_kP, Turn_kI, Turn_kD}, //Turn controller gains
             {Angle_kP, Angle_kI, Angle_kD})  //Angle controller gains (helps drive straight)
  .withDerivativeFilters(
      std::make_unique<AverageFilter<3>>(), //Distance controller filter
      std::make_unique<AverageFilter<3>>(), //Turn controller filter
      std::make_unique<AverageFilter<3>>())  //Angle controller filter
  .withClosedLoopControllerTimeUtil(75, 5, 150_ms) //Min error, min error derivative and min time at error to be considered settled
  .withSensors(LeftEnc, RightEnc, MiddleEnc)
  .withDimensions(AbstractMotor::gearset::green, {{Tracking_Diameter,Tracking_Length,Middle_Length,Tracking_Diameter}, quadEncoderTPR})
  .withOdometry() //Use the same scales as the chassis (above)
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
  pros::delay(800);
  Arm.moveVoltage(-12000);
  pros::delay(950);
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
    double Voltage = Error * Arm_kP;
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
    double Voltage = Error * Arm_kP;
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
    double Voltage = Error * Arm_kP;
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
    double Voltage = Error * Angler_kP;
    if (Error < 5){break;} //Breaks or ends loop if angler reaches position
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
    double Voltage = Error * Angler_kP;
    if (Error < 5){break;} //Breaks or ends loop if angler reaches position
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

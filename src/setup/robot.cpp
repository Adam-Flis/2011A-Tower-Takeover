#include "main.h"
#include "setup/define.hpp"

/* ********** Chassis Builder Parameters ********** */

#define Wheel_Diameter 4_in //Wheel diameter of omni wheels
#define Wheel_Length 9_in //Distance between omni wheels
#define Tracking_Length 8.5_in //Distance between tracking wheels
#define Tracking_Diameter 2.75_in //Wheel diameter of tracking wheel
#define Middle_Length 2.0_in //Distance of the middle tracking wheel to the center of turning

/* ********** Distance PID Parameters ********** */

#define Distance_kP 0.0014f
#define Distance_kI 0.00004f
#define Distance_kD 0.000015f

/* ********** Turn PID Parameters ********** */

#define Turn_kP 0.0014f
#define Turn_kI 0.00004f
#define Turn_kD 0.000015f

/* ********** Angle PID Parameters ********** */

#define Angle_kP 0.0f
#define Angle_kI 0.0f
#define Angle_kD 0.0f

/* ********** 2D Motion Profiling Parameters ********** */

#define Max_Linear_Velocity 1.0 //Maximum linear velocity of the chassis in m/s
#define Max_Linear_Acceleration 2.0 //Maximum linear acceleration of the chassis in m/s/s
#define Max_Linear_Jerk 3.0 //Maximum linear jerk of the chassis in m/s/s/s

/* ********** Other Parameters ********** */

#define Arm_kP 0.1f

/* ********** Drivetrain ********** */

//Generates the chassis needed to use Okapi's built in PIDs, odometry, and 2D motion profiling
auto Chassis = ChassisControllerBuilder()
  .withMotors(LeftSide, RightSide)
  .withSensors(LeftEnc, RightEnc)
  .withGains(
      {Distance_kP, Distance_kI, Distance_kD}, //Distance controller gains
      {Turn_kP, Turn_kI, Turn_kD}, //Turn controller gains
      {Angle_kP, Angle_kI, Angle_kD})  //Angle controller gains (helps drive straight)
  .withDerivativeFilters(
      std::make_unique<AverageFilter<5>>(),//Distance controller filter
      std::make_unique<AverageFilter<5>>(), //Turn controller filter
      std::make_unique<AverageFilter<5>>()) //Angle controller filter
  .withClosedLoopControllerTimeUtil(50, __DBL_MAX__, 0_ms) //Min error, min error derivative and min time at error to be considered settled
  .withDimensions(AbstractMotor::gearset::green, {{Tracking_Diameter, Tracking_Length, Middle_Length, Tracking_Diameter}, quadEncoderTPR})
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
  Arm.moveVelocity(200);
  pros::delay(650);
  Arm.moveVelocity(-200);
  pros::delay(750);
  Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  Arm.moveVelocity(0);
}

//Sets velocity of drivetrain
void DriveVel(int Velocity){
  LeftSide.moveVelocity(Velocity);
  RightSide.moveVelocity(Velocity);
}

//360 degrees per rotation of wheel
//2.75 in diameter wheels
int inchToInch(float input){
  float inches = (input * 360)/(2.75 * M_PI);
  return inches;
}

//Moves robot
//Distance in inches (+in forward -in backward)
//Velocity -200 to 200
//Timeout in milliseconds
void Drive(float Distance, int Velocity, int TimeOut){
  int EndTime = Time(TimeOut);
  LeftEnc.reset();
  RightEnc.reset();
  while (abs((LeftEnc.get() + RightEnc.get()))/2 < abs(inchToInch(Distance))){
    DriveVel(Velocity);
    if (EndTime == TimeOut){break;}
  }
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
  DriveVel(0);
}

/* ********** Arm Voids ********** */

//Moves the arm up to set position
//Position in arm potentiometer counts
//Time out in milliseconds
void ArmUp(int Position, int TimeOut){
  int EndTime = Time(TimeOut);
  while (EndTime != pros::millis()){
    int Error = Position - ArmPot.get();
    double Velocity = Error * Arm_kP;
    if (Error < 5){break;} //Breaks or ends loop if angler reaches position
    if (Velocity > 200){
      Velocity = 200; //Maximum arm velocity
    }
    else if (Velocity < 120){
      Velocity = 120; //Minimum arm velocity
    }
    Arm.moveVelocity(Velocity); //Sets arm velocity
    pros::delay(10); //Loop speed, prevents overload
  }
  if (ArmPot.get() > ArmHold){ //Set brake mode hold if over certain value
    Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  }
  else { //Set brake mode if anything else
    Arm.setBrakeMode(AbstractMotor::brakeMode::brake);
  }
  Arm.moveVelocity(0); //Stops arm
}

//Moves the arm down to set position
//Position in arm potentiometer counts
//Time out in milliseconds
void ArmDown(int Position, int TimeOut){
  int EndTime = Time(TimeOut);
  while (EndTime != pros::millis()){
    int Error = abs(ArmPot.get() - Position);
    double Velocity = Error * Arm_kP;
    if (Error < 5){break;} //Breaks or ends loop if angler reaches position
    if (Velocity > 200){
      Velocity = 200; //Maximum arm velocity
    }
    else if (Velocity < 160){
      Velocity = 160; //Minimum arm velocity
    }
    Arm.moveVelocity(-Velocity); //Sets arm velocity
    pros::delay(10); //Loop speed, prevents overload
  }
  if (ArmPot.get() > ArmHold){ //Set brake mode hold if over certain value
    Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
  }
  else { //Set brake mode if anything else
    Arm.setBrakeMode(AbstractMotor::brakeMode::brake);
  }
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
  Angler.setBrakeMode(AbstractMotor::brakeMode::coast); //Set brake mode coast
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

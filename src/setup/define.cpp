#include "main.h"

/* ********** Define Motor Ports ********** */

#define LFD_Port 2
#define LBD_Port 3
#define RFD_Port 10
#define RBD_Port 9
#define Angler_Port 8
#define Arm_Port 11
#define Cube_Intake_Left_Port 14
#define Cube_Intake_Right_Port 12

/* ********** Define Sensor Ports ********** */

#define Left_Encoder_Top_Port 'a'
#define Left_Encoder_Bottom_Port 'b'
#define Right_Encoder_Top_Port 'c'
#define Right_Encoder_Bottom_Port 'd'
#define Angler_Potentiomenter_Port 'g'
#define Arm_Potentiometer_Port 'h'

/* ********** Creates Motors ********** */

Motor LFD(LFD_Port, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor LBD(LBD_Port, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor RFD(RFD_Port, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor RBD(RBD_Port, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor Arm(Arm_Port, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor CIL(Cube_Intake_Left_Port, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor CIR(Cube_Intake_Right_Port, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor Angler(Angler_Port, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

/* ********** Creates Motor Groups ********** */

MotorGroup LeftSide{LFD, LBD};
MotorGroup RightSide{RFD, RBD};
MotorGroup Intake{CIL, CIR};

/* ********** Creates Sensors ********** */

ADIEncoder LeftEnc(Left_Encoder_Top_Port, Left_Encoder_Bottom_Port, false);
ADIEncoder RightEnc(Right_Encoder_Top_Port, Right_Encoder_Bottom_Port, true);
Potentiometer ArmPot(Arm_Potentiometer_Port);
Potentiometer AnglerPot(Angler_Potentiomenter_Port);

/* ********** Creates Controller ********** */

Controller Main(ControllerId::master);

/* ********** Angler Variables ********** */

int AnglerPotMin = 1200;
int AnglerPotMax = 3000;
float Angler_kP = 9.2;

/* ********** Arm Variables ********** */

int ArmHold = 1100;
int LowChalice = 1695;
int MediumChalice = 2300;
int ArmStart = 650;

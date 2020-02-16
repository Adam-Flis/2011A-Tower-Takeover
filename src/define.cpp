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

#define IMU_Port 13
#define Left_Encoder_Top_Port 'a'
#define Left_Encoder_Bottom_Port 'b'
#define Right_Encoder_Top_Port 'c'
#define Right_Encoder_Bottom_Port 'd'
#define Angler_Potentiomenter_Port 'g'
#define Arm_Potentiometer_Port 'h'


/* ********** Creates Motors ********** */

Motor LFD (LFD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor LBD (LBD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor RFD (RFD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor RBD (RBD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor angler (Angler_Port,MOTOR_GEARSET_36,false,MOTOR_ENCODER_DEGREES);
Motor arm (Arm_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor LI (Cube_Intake_Left_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor RI (Cube_Intake_Right_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);

/* ********** Creates Sensors ********** */

Imu IMU (IMU_Port);
ADIAnalogIn anglerPot (Angler_Potentiomenter_Port);
ADIAnalogIn armPot (Arm_Potentiometer_Port);
ADIEncoder lEnc (Left_Encoder_Top_Port,Left_Encoder_Bottom_Port,false);
ADIEncoder rEnc (Right_Encoder_Top_Port,Right_Encoder_Bottom_Port,true);

/* ********** Creates Controller ********** */

Controller Main (CONTROLLER_MASTER);

/* ********** Arm Variables ********** */

int armHold = 1100;
int lowChalice = 1695;
int mediumChalice = 2300;
int armHome = 650;

/* ********** Angler Variables ********** */

int anglerHome = 1200;
int anglerStack = 3000;
float angler_kP = 9.2;
bool trayDown = false;

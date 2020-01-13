#include "main.h"
#include "define.hpp"
#include "robot.hpp"


void opcontrol(){

  /* ********** Declares Controller Buttons ********** */

  ControllerButton ButtonUp = Main[ControllerDigital::up];
  ControllerButton ButtonDown = Main[ControllerDigital::down];
  ControllerButton ButtonLeft = Main[ControllerDigital::left];
  ControllerButton ButtonRight = Main[ControllerDigital::right];
  ControllerButton ButtonL1 = Main[ControllerDigital::L1];
  ControllerButton ButtonL2 = Main[ControllerDigital::L2];
  ControllerButton ButtonR1 = Main[ControllerDigital::R1];
  ControllerButton ButtonR2 = Main[ControllerDigital::R2];
  ControllerButton ButtonX = Main[ControllerDigital::X];
  ControllerButton ButtonY = Main[ControllerDigital::Y];
  ControllerButton ButtonA = Main[ControllerDigital::A];
  ControllerButton ButtonB = Main[ControllerDigital::B];

  ProfileController->flipDisable(true); //Disables the profile controller, prevents it from trying to run during operator control
  Chassis->stop(); //Stops the drivetrain motors from running in the background
  Chassis->setMaxVelocity(200); //Makes sure to reset the velocity to the maximum on the drivetrain
  Chassis->getModel()->setMaxVoltage(12000); //Makes sure to reset the voltage to the maximum on the drivetrain
  Chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake); //Sets brake mode brake on drivetrain

  while(1){

    /* ********** Sensor Testing ********** */
    //Used to make sure sensors work by print their value to the lcd display

    /*pros::lcd::print(2, "Angler Pot: %lf", AnglerPot.get());
    pros::lcd::print(3, "Arm Pot: %lf", ArmPot.get());
    pros::lcd::print(4, "Encoder Left: %lf", LeftEnc.get());
    pros::lcd::print(5, "Encoder Right: %lf", RightEnc.get());
    pros::lcd::print(6, "Encoder Middle: %lf", MiddleEnc.get());*/

    /* ********** Drivetrain Control ********** */

    Chassis->getModel()->tank(Main.getAnalog(ControllerAnalog::leftY), //Left joystick moved, power left side of drivetrain
                              Main.getAnalog(ControllerAnalog::rightY)); //Right joystickt moved, power right side of drivetrain

    /* ********** Cube Intake Control ********** */

    if (ButtonL1.isPressed()){ //Button left 1 pressed, intake cubes
      Intake.moveVoltage(12000);
    }
    else if (ButtonL2.isPressed()){ //Button left 2 pressed, outtake cubes
      Intake.moveVoltage(-12000);
    }
    else { //Sets brake mode and stops cube intake when buttons L1 & L2 are not pressed
      Intake.setBrakeMode(AbstractMotor::brakeMode::brake); //Set brake mode brake
      Intake.moveVelocity(0); //Stops intake
    }

    /* ********** Arm Control ********** */

    if (ButtonR1.isPressed()){ //Button right 1 pressed, raise arm
      Arm.moveVoltage(12000);
    }
    else if (ButtonR2.isPressed() && ArmPot.get() > ArmStart){ //Button right 2 pressed, lower arm
      Arm.moveVoltage(-12000);
    }
    else { //Sets brake mode and stops arm when buttons R1 & R2 are not pressed
 			if (ArmPot.get() > ArmHold) { //Set brake mode hold if over certain value
 				Arm.setBrakeMode(AbstractMotor::brakeMode::hold);
 			}
 			else { //Set brake mode if anything else
 				Arm.setBrakeMode(AbstractMotor::brakeMode::brake);
 			}
 			Arm.moveVelocity(0); //Stops arm
 		}

    /* ********** Angler Control ********** */

    if (ButtonA.isPressed() && AnglerPot.get() < AnglerPotMax){ //Button A pressed, raise tray
      int Error = AnglerPotMax - AnglerPot.get();
      double Voltage = Error * Angler_kP;
      if (Voltage > 12000){
        Voltage = 12000; //Maximum angler voltage for going up
      }
      else if (Voltage < 4000){
        Voltage = 4000; //Minimum angler voltage for going up
      }
      pros::lcd::print(1, "Angler Voltage: %lf", Voltage); //Prints voltage value to lcd
      Angler.moveVoltage(Voltage); //Sets angler voltage
		}
    else if (ButtonB.isPressed() && AnglerPot.get() > AnglerPotMin){ //Button B pressed, lower tray
      int Error = AnglerPot.get() - AnglerPotMin;
      double Voltage = Error * Angler_kP;
      if (Voltage > 12000){
        Voltage = 12000; //Maximum angler voltage for going down
      }
      else if (Voltage < 8000){
        Voltage = 8000; //Minimum angler voltage for going down
      }
      pros::lcd::print(1, "Angler Voltage: %lf", Voltage); //Prints voltage value to lcd
      Angler.moveVoltage(-Voltage); //Sets angler voltage
		}
    else { //Sets brake mode and stops tray when buttons A & B are not pressed
      if(AnglerPot.get() > (AnglerPotMax/1.5)){ //Set brake mode hold if over certain value
        Angler.setBrakeMode(AbstractMotor::brakeMode::hold);
      }
      else { //Set brake mode brake if anything else
        Angler.setBrakeMode(AbstractMotor::brakeMode::brake);
      }
      pros::lcd::print(1, "Angler Voltage: 0"); //Resets lcd line to 0
      Angler.moveVelocity(0); //Stops angler
    }

    pros::delay(10); //Loop speed, prevent overload
  }
}

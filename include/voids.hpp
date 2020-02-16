#include "main.h"

#ifndef ROBOT_HPP
#define ROBOT_HPP

extern int secondsToMillis(float input);
extern int timeOut(int input);

/* ********** Cube Intake Class ********** */

class Cube_Intake
{
public:
  Cube_Intake();
  virtual void brake();
  virtual void move(int velocity);
  virtual void stop();
};

/* ********** Arm Class ********** */

class Two_Bar
{
public:
  Two_Bar();
  virtual void brakeMode();
  virtual void up(int position, int velocity, float endTime);
  virtual void down(int position, int velocity, float endTime);

};

/* ********** Angler Class ********** */

class Tilter
{
public:
  Tilter();
  virtual void brakeMode();
  virtual void stack(float endTime);
  virtual void home(float endTime);
};

/* ********** Chassis Class ********** */

class Chassis
{
public:
  Chassis();
  virtual void reset();
  virtual void brakeMode(string mode);
  virtual void move(string side, int velocity);
  virtual void stop();
  virtual void moveDistance(string direction, float target, int maxVelocity, float endTime);
  virtual void turn(string direction, float target, int maxVelocity, float endTime);
};


/* ********** Declare Classes ********** */

extern Cube_Intake Intake;
extern Two_Bar Arm;
extern Tilter Angler;
extern Chassis Drive;


#endif

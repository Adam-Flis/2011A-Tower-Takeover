#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Collects 8 cubes from the field
//Places cubes into the small scoring zone
//Points scored: 8
void BlueSmall(){
int Stack = timeOut(secondsToMillis(13.0));


if (Stack > millis()){
  anglerStack(2.3);
  drive("b", 12, 250, 2.0);
}
angler.move_velocity(0);
driveStop();
}

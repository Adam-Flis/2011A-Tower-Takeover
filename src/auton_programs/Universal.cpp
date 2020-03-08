#include "main.h"
#include "define.hpp"
#include "voids.hpp"

//Pushes preload into scoring zone
//Works on any side
//Points scored: 1
void Universal(){

  drive("f", 24, 200, 2.0);
  delay(200);
  drive("b", 12, 250, 2.0);
  unfold();

}

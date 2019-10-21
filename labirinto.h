#pragma once 

#include "motoress.h"

void gturn_esq(motores &dir) {
  float f;
  float i = x;
  if (x < -89.9) {
    f = 90 + abs(-180 - i);

    while (!(x>f-0.4 and x<f+0.4)) {
      gloop();
      dir.turn_esq();    }


  } else {
    f = i - 90;
    while (x > f) {
      gloop();
      dir.turn_esq();
    }
  
  }

dir.parar();
delay(10);

}


void gturn_dir(motores &dir) {
  float f;
  float i = x;
  if (x > 90) {
    f = -abs(180 - x) - 90;

    while (!(x>f-0.4 and x<f+0.4))
    {
      gloop();
      dir.turn_dir();
    }
  } else {
    f = 90 + x;
    while (x < f) {
      gloop();
      dir.turn_dir();
    }
  }
  dir.parar();
  delay(10);
}

#include <NewPing.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
#include "MPU6050.h"

#include "mpuu.h"
#include "gyro.h"
#include "motoress.h"
#include "labirinto.h"
//==========================================================================

struct tripla
{
  int a, b, c;
  tripla(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c)
  {}
} recstack[400];

bool vis[20][20];
int labdir[] = { -1, 0, 1, 0, -1};
int recstacksz = 0;

NewPing sonar[6] = {
  NewPing(49, 48, 200),
  NewPing(47, 46, 200),
  NewPing(51, 50, 200),
  NewPing(53, 52, 200),
  NewPing(23, 22, 200),
  NewPing(25, 24, 200)
};

mpu1 giro;
motores  dir;
//===========================================================================

int parede[10];
int parede_mtr[10];
int aux1 = 0;
void paredes() {
  int a, b;
  memset(parede, 0, sizeof(parede));

  for (int j = 0, i = 0; i < 6; i += 2) {
    a = sonar[i].ping_cm();
    b = sonar[i + 1].ping_cm();

    if (j == 2) {
      parede[2] = 1;//sempre afirma que temparede pq nao importa;
      j++;
    }

    if ( a < 15 and b < 15) {
      parede[j] = 1;
    }
    if (a > 15 and b > 15) {
      parede[j] = 0;
    }

    j++;
  }

  for (int i = 0; i < 4; i++) {

    int k = i - aux1;
    if (k > 3)k -= 4;
    if (k < 0)k += 4;
    parede_mtr[i] = parede[k];
  }

  for (int i = 0; i < 4; i++) {
    Serial.print("Parede ");
    Serial.print(i);
    Serial.print(" valor:");
    Serial.println(parede[i]);
  }
}

void corrige(motores &dir) {
  paredes();
  for (int i = 1; i < 3; i++) {

    if (parede[i + (i == 2)]) {

      Serial.print("parede ");
      Serial.println(i);

      int j = 2 * i, a;
      while (true) {

        a = sonar[j + 1].ping_cm() - sonar[j].ping_cm();
        Serial.println("to na funcao");
        Serial.println(a);

        // if(i==3)a=-a;
        if ( a < 0) {
          dir.turn_dir();
          delay(3);
          //dir.parar();

        }

        else if ( a > 0) {
          dir.turn_esq();
          delay(3);
          dir.parar();

        } else {
          dir.parar();
          delay(400);
          break;
        }
      }
    }
  }
  dir.parar();
  //  delay(500);

}

int ref = 0;


bool labwall(int d)
{
  if (parede_mtr[d] == 1) {
    return true;
  } else return false ;

  //tem que retornar se tiver uma parede nessa direção
  //0=norte; 1=leste(dir),2-sul,sa3-oeste(esq)
}



void walk(int d)
{ //ordem da matriz cima,direita,baixo,esquerda
  //referencial parede sentido horario de 0 a 3;
  corrige(dir);

  if (d == 1) {
    gturn_dir(dir), aux1 = 1;
  }

  else if (d == 2) {
    gturn_dir(dir);
    corrige(dir);//gira 180 pra retornar
    gturn_dir(dir);
    ref++, aux1 = 2;

    if (ref > 3)ref -= 4;
  }

  else if (d == 3) {
    gturn_esq(dir);
    ref--;
    if (ref < 0)ref += 4;
    aux1 = -1;
  }

  corrige(dir);
  dir.frente_temp(780);

  dir.parar();
  delay(10);
  //corrige(dir);

  //tem que andar na direcao do referancial
  //mesmo referencial

}

void printa() {
  if (Serial.read() == 'q') {

    for (int i = 0; i < 6; i++) {
      Serial.println(sonar[i].ping_cm());
    }
  }
}

//==========================================================================

void setup() {
  Serial.begin(115200);

  Serial.println("quer calibrar?");
  while (true) {
    if (Serial.read() == 's') {
      giro.setup1();
      delay(100);
      giro.calibration_loop();
      break;
    } else if (Serial.read() == 'n') {
      break;
    }
  }

  //  delay(100);
  gsetup(giro);
  dir.mtr_setup();

  vis[1][1] = true;
  recstack[recstacksz++] = tripla(10, 10, 0);
}

int comp = 0;
long long momento;
void loop() {



  gloop();
  Serial.println(x);
  if (Serial.read() == 'f') {

    gturn_dir(dir);
    comp = 1;
    momento = millis();
  }

  if (comp == 1 and millis() - momento  < 750) {
    dir.parar();
  }

  if (comp == 1 and millis() - momento >= 750 and millis() - momento < 900) {
    corrige(dir);
  }

  if (Serial.read() == 'k') {
    comp = 0;
  }

  if (Serial.read() == 'p') {
    dir.frente_temp(800);
    momento = millis();
  }


  if (millis() - momento < 200) {
    dir.parar();
  }
  printa();
  /*
    for (int i = 1; i < 4; i += 2) {
      int j = 2 * i;
      int a = sonar[j].ping_cm() - sonar[j - 1].ping_cm();
      Serial.print(i);
      Serial.print("  ");
      Serial.println(a);
    }
    Serial.println();*/
  int r, c, d;
  r = recstack[recstacksz - 1].a;
  c = recstack[recstacksz - 1].b;
  d = recstack[recstacksz - 1].c;
  if (labwall(d) || vis[r + labdir[d]][c + labdir[d + 1]])
  {
    recstacksz--;
    if (d != 3)
      recstack[recstacksz++] = tripla(r, c, d + 1);
    else
    {
      r = recstack[recstacksz - 1].a;
      c = recstack[recstacksz - 1].b;
      d = recstack[recstacksz - 1].c;
      walk((d + 2) % 4);
    }
  }
  else
  {
    vis[r + labdir[d]][c + labdir[d + 1]] = true;
    walk(d);
    recstack[recstacksz++] = tripla(r + labdir[d], c + labdir[d + 1], 0);
  }
}

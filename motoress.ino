#include "motoress.h"

int motor_f0 = 6;
int motor_at0 = 4;
int motor_pwm0 = 7;

int motor_f1 =  5;
int motor_at1 = 9;
int motor_pwm1 = 8;

void motores::mtr_setup()
{
    pinMode(motor_f0, OUTPUT);
    pinMode(motor_f1, OUTPUT);
    pinMode(motor_at0, OUTPUT);
    pinMode(motor_at1, OUTPUT);
    digitalWrite(motor_f0, HIGH);
    digitalWrite(motor_f1, HIGH);
    digitalWrite(motor_at0, HIGH);
    digitalWrite(motor_at1, HIGH);
}

void motores::frente() {
  digitalWrite(motor_f0, HIGH);
  digitalWrite(motor_f1, HIGH);
  digitalWrite(motor_at0, LOW);
  digitalWrite(motor_at1, LOW);
  digitalWrite(motor_pwm0, 10);
  digitalWrite(motor_pwm1, 10);
}

void motores::tras() {
  digitalWrite(motor_f0, LOW);
  digitalWrite(motor_f1, LOW);
  digitalWrite(motor_at0, HIGH);
  digitalWrite(motor_at1, HIGH);
  digitalWrite(motor_pwm0, 210);
  digitalWrite(motor_pwm1, 30);
}

void motores::turn_esq() {
  digitalWrite(motor_f0, LOW);
  digitalWrite(motor_f1, HIGH);
  digitalWrite(motor_at0, HIGH);
  digitalWrite(motor_at1, LOW);
  digitalWrite(motor_pwm0, 255);//215
  digitalWrite(motor_pwm1, 255);
}

void motores::turn_dir() {
  digitalWrite(motor_f0, HIGH);
  digitalWrite(motor_f1, LOW);
  digitalWrite(motor_at0, LOW);
  digitalWrite(motor_at1, HIGH);
  digitalWrite(motor_pwm0, 255);
  digitalWrite(motor_pwm1, 255);
}

void motores::parar() {
  //long long temp = millis();
  //while ((millis() - temp) <= 100) {
  digitalWrite(motor_f0, HIGH);
  digitalWrite(motor_f1, HIGH);
  digitalWrite(motor_at0, HIGH);
  digitalWrite(motor_at1, HIGH);
  // }
}

void motores::frente_temp(int a) {
  long long temp = millis();
  while ((millis() - temp) <= a) {
    frente();
  }
}

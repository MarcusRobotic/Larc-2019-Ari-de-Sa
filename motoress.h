#pragma once

class motores {
  public:
    int motor_f0 = 6;
    int motor_at0 = 4;
    int motor_pwm0 = 7;

    int motor_f1 =  5;
    int motor_at1 = 9;
    int motor_pwm1 = 8;

    void mtr_setup();

    void frente();

    void tras();

    void turn_esq();

    void turn_dir();

    void parar();

    void frente_temp(int a);
};

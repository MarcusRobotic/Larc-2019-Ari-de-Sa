#include <Wire.h>
#include "mlx15.h"

MLX90615 mlx = MLX90615();

void setup() {
  Serial.begin(9600);
  //Serial.println("Melexis MLX90615 infra-red temperature sensor test");
  mlx.begin();
  //Serial.print("Sensor ID number = ");
 // Serial.println(mlx.get_id(), HEX);
}

void loop() {


  if (Serial.read() == 'b') {
    //Serial.print("Ambient = ");
    //Serial.print(mlx.get_ambient_temp());
    //Serial.print(" s2 = ");
    int k = (int)mlx.get_object_temp();
    Serial.print(k);
    //Serial.println(" *C");

    Serial.println();
    delay(500);
  }


}

//874340
// VERMELHO - VERDE - COISO - AZUL

//87441B
// BRANCO - VERMELHO - CINZA - LARANJA

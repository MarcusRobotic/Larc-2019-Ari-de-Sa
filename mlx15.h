#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Wire.h"

// default MLX90615 I2C address
#define MLX90615_I2C_ADDR    0x5B
// ROM - ID number
#define MLX90615_REG_ID_LOW     0x1E
#define MLX90615_REG_ID_HIGH    0x1F
// RAM - ambient temperature register
#define MLX90615_REG_TEMP_AMBIENT 0x26
// RAM - object temperature register 
#define MLX90615_REG_TEMP_OBJECT  0x27

class MLX90615 {
 public:
  MLX90615(uint8_t i2c_addr = MLX90615_I2C_ADDR);
  void begin();
  uint32_t get_id();
  float get_object_temp();
  float get_ambient_temp();

 private:
  uint8_t i2c_addr_;
  uint16_t read_word16(uint8_t reg);
};
#ifndef MPU6050_h
#define MPU6050_h

#include <Wire.h>

/*
Datasheet:
https://datasheet.octopart.com/MPU-6050-InvenSense-datasheet-14421344.pdf

Register Map:
https://www.waveshare.com/w/upload/0/03/MPU6050-Register-Map-and-Descriptions.pdf
*/
union MPU6050_Meassureing{
  struct _data{
    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;
    int16_t temp;
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;
    int16_t errorCode;
    int16_t transmitted;
  } data; //struct
  uint8_t ucRaw[2];
}; // union MPU6050_Meassureing

union MPU6050_Debug{
  struct _data{
    uint8_t reg_self_test_x;
    uint8_t reg_self_test_y;
    uint8_t reg_self_test_z;
    uint8_t reg_self_test_a;
    
    uint8_t reg_smprt_div;
    uint8_t reg_config;
    uint8_t reg_gyro_config;
    uint8_t reg_user_ctrl;
    uint8_t reg_pwr_mgmt_1;
    uint8_t reg_pwr_mgmt_2;
    uint8_t reg_fifo_counth;
    uint8_t reg_fifo_countl;
    uint8_t transmitted;
  } data; //struct
  uint8_t ucRaw[2];
}; // union MPU6050_Meassureing

class MPU6050
{
  private:
  unsigned char address;
  TwoWire *twi;
  
  
  public:
  static const unsigned char ad0_low  = 0b1101000;
  static const unsigned char ad0_high = 0b1101001;

  static const unsigned char reg_self_test_x  = 0x0D;
  static const unsigned char reg_self_test_y  = 0x0E;
  static const unsigned char reg_self_test_z  = 0x0F;
  static const unsigned char reg_self_test_a  = 0x10;
  static const unsigned char reg_smprt_div    = 0x19;
  static const unsigned char reg_config       = 0x1A;
  static const unsigned char reg_gyro_config  = 0x1B;
  static const unsigned char reg_accel_config = 0x1C;
  static const unsigned char reg_who_am_i     = 0x75;

  static const unsigned char reg_accel_xout = 0x3B; // 0s3B = HighByte  0x3C = LowByte
  static const unsigned char reg_accel_yout = 0x3D; // 0s3D = HighByte  0x3E = LowByte
  static const unsigned char reg_accel_zout = 0x3F; // 0s3F = HighByte  0x40 = LowByte
  static const unsigned char reg_temp       = 0x41; // 0s41 = HighByte  0x42 = LowByte
  static const unsigned char reg_gyro_xout  = 0x43; // 0s43 = HighByte  0x44 = LowByte
  static const unsigned char reg_gyro_yout  = 0x45; // 0s45 = HighByte  0x46 = LowByte
  static const unsigned char reg_gyro_zout  = 0x47; // 0s47 = HighByte  0x48 = LowByte
  static const unsigned char reg_user_ctrl  = 0x6A;
  static const unsigned char reg_pwr_mgmt_1 = 0x6B;
  static const unsigned char reg_pwr_mgmt_2 = 0x6C;
  static const unsigned char reg_fifo_counth= 0x72;
  static const unsigned char reg_fifo_countl= 0x73;
  
  static const char selftest_response_gyro_min = -14; // % (See Datasheet 6.1 Gyroscope Specifications)
  static const char selftest_response_gyro_max =  14; // %
  static const char selftest_response_accell_min = -14; // % (See Datasheet 6.2 Accelerometer Specifications)
  static const char selftest_response_accell_max =  14; // %

  MPU6050(TwoWire *cTwi, int bAddress);
  ~MPU6050();
  int  begin(int selftest, int gyro_FullScale, int accel_FullScale, int dlpf_cfg);
  int  selftest();
  uint8_t  readuInt8(unsigned char ucReg);
  int16_t  readInt16(unsigned char ucReg);
  void readMeassureing(MPU6050_Meassureing *package,int iID);
  void readConfig(MPU6050_Debug *cfg);
}; // class MPU6050


#endif //MPU6050_h

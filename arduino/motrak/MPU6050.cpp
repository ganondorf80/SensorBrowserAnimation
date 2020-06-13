#include "MPU6050.h"
#define MPU6050_debug

#ifdef MPU6050_debug
#include <Arduino.h>
#endif // MPU6050_debug

MPU6050::MPU6050(TwoWire *cTwi,int bAddress){
  twi = cTwi;
  if (bAddress) address = MPU6050::ad0_high;
  else address = MPU6050::ad0_low;

}; // MPU6050::MPU6050

MPU6050::~MPU6050(){
}; // MPU6050::~MPU6050

/*
 * Returns 0 if Successfull
 * gyro-/accel_selftest   0= not / 1= perform selftest
 * gyro-/accel_FullScale:
 * Val./// Gyro /// Accel
 * 0_///_+/- 250°/sec._///_+/- 2g
 * 1_///_+/- 500°/sec._///_+/- 4g
 * 2_///_+/-1000°/sec._///_+/- 8g
 * 3_///_+/-2000°/sec._///_+/-16g
 * gyro-/accel_dlpf_cfg   Val.: / OutRate Accel,delay: / Gyro,delay:
 *                        0     /        260, 0__     / 256,_0.98
 *                        1     /        184, 2.0     / 188,_1.9 
 *                        2     /        _94, 3.0     / _98,_2.8 
 *                        3     /        _44, 4.9     / _42,_4.8 
 *                        4     /        _21, 8.5     / _20,_8.3 
 *                        5     /        _10,13.8     / _10,13.4 
 *                        6     /        __5,19.0     / __5,18.8 
 *                        7     /                reserved
 */
int MPU6050::begin(int selftest, int gyro_FullScale, int accel_FullScale, int dlpf_cfg)
{
  if (selftest != 0) {
    //Stub
  };// if (selftest != 0)
  unsigned char ucValue=0;
  twi->beginTransmission(address);
  twi->write(MPU6050::reg_pwr_mgmt_1);
  twi->write(0x00);                     // Dissable Sleep Mode
  twi->endTransmission();

  delay(30);

  twi->beginTransmission(address);
  twi->write(MPU6050::reg_smprt_div);

  twi->write(50);                             // Reg: Sample Rate Divider

  ucValue = ((dlpf_cfg & 0b111) << 0);        // Reg: Config
  //Serial.println("");
  //Serial.printf("Config dlpf_cfg=%2x\r\n",ucValue);
  twi->write(ucValue);

  ucValue = ((gyro_FullScale & 0b11) << 3);   // Reg: Gyro
  //Serial.printf("Gyro gyro_FullScale=%2x\r\n",ucValue);
  twi->write(ucValue);

  ucValue = ((accel_FullScale & 0b11) << 3);  // Reg: Accel
  //Serial.printf("Accel gyro_FullScale=%2x\r\n",ucValue);
  twi->write(ucValue);

  return twi->endTransmission(true);
}; // MPU6050::begin



int MPU6050::selftest()
{
  unsigned char ucValue=0;
  twi->beginTransmission(address);
  twi->write(MPU6050::reg_config);

  //ucValue = ((dlpf_cfg & 0b111) << 0);
  //twi->write(ucValue);
  twi->endTransmission(true);  
}; // MPU6050::selftest



uint8_t MPU6050::readuInt8(unsigned char ucReg)
{
  uint8_t result=0;
  twi->beginTransmission(address);
  twi->write(ucReg);
  twi->endTransmission(false);
  
  while (twi->available()){
    result =  twi->read();
  }; // while
  
  twi->requestFrom(address,1,true);
  result =  twi->read();

  return result;
}; // MPU6050::readuInt8



int16_t MPU6050::readInt16(unsigned char ucReg)
{
  int16_t result=0;
  twi->beginTransmission(address);
  twi->write(ucReg);
  twi->endTransmission(false);
  
  while (twi->available()){
    result = (uint8_t) twi->read();
  }; // while

  twi->requestFrom(address,2,true);
  result = (twi->read()<<8);
  result |= (twi->read()<<0);

  return result;
}; // MPU6050::readuInt8



void MPU6050::readMeassureing(MPU6050_Meassureing *package,int iID)
{
  int iDummy=0;
  for(iDummy=0; iDummy < sizeof(MPU6050_Meassureing); iDummy++){
    package->ucRaw[iDummy]=0xFF;
  };// for
  twi->beginTransmission(address);
  twi->write(MPU6050::reg_accel_xout);
  twi->endTransmission(false);

  // Flush
  while (twi->available()){
    iDummy =  twi->read();
  }; // while

  // https://github.com/espressif/arduino-esp32/blob/master/libraries/Wire/src/Wire.h
  // i2c_err_t readTransmission(uint16_t address, uint8_t* buff, uint16_t size, bool sendStop=true, uint32_t *readCount=NULL);
  uint32_t readCount=0;
  int errorCode=0;
  errorCode = (int) twi->readTransmission(address,package->ucRaw,sizeof(MPU6050_Meassureing),true,&readCount);
  package->data.errorCode=((errorCode>>8)&0xff) | ((errorCode<<8)&0xff00);
  package->data.transmitted=((readCount>>8)&0xff) | ((readCount<<8)&0xff00);
  
  //Serial.printf("\r\nerrorCode: %2i,   n=%2i.\r\n",(int)errorCode,(int)readCount);

  // Swap HiLo:
  for (int n=0; n<sizeof(MPU6050_Meassureing); n=n+2) {
    errorCode=package->ucRaw[n];
    package->ucRaw[n]=package->ucRaw[n+1];
    package->ucRaw[n+1]=(uint8_t)errorCode;
  }; // for
  return;
}; // MPU6050::readMeassureing


void MPU6050::readConfig(MPU6050_Debug *cfg)
{
  int iDummy=0;
  for(iDummy=0; iDummy < sizeof(MPU6050_Debug); iDummy++){
    cfg->ucRaw[iDummy]=0xFF;
  };// for

  cfg->data.reg_self_test_x = readuInt8(reg_self_test_x);
  cfg->data.reg_self_test_y = readuInt8(reg_self_test_y);
  cfg->data.reg_self_test_z = readuInt8(reg_self_test_z);
  cfg->data.reg_self_test_a = readuInt8(reg_self_test_a);
  cfg->data.reg_smprt_div = readuInt8(reg_smprt_div);
  cfg->data.reg_config = readuInt8(reg_config);
  cfg->data.reg_gyro_config = readuInt8(reg_gyro_config);
  cfg->data.reg_user_ctrl = readuInt8(reg_user_ctrl);
  cfg->data.reg_pwr_mgmt_1 = readuInt8(reg_pwr_mgmt_1);
  cfg->data.reg_pwr_mgmt_2 = readuInt8(reg_pwr_mgmt_2);
  cfg->data.reg_fifo_counth = readuInt8(reg_fifo_counth);
  cfg->data.reg_fifo_countl = readuInt8(reg_fifo_countl);
//  cfg->data. = readuInt8();

  
}; // MPU6050::readConfig

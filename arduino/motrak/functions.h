#include <WiFi.h>
#include "MPU6050.h"


void publishMovements(WiFiClient *client, char devName[], char cName[], MPU6050_Meassureing *mes, int iID, MPU6050_Debug *dbg=NULL){
  char cBuffer[300];
  char cBoneBuffer[150];
  cBuffer[0]=0;
  strcat(cBuffer,"{\r\n");
  
  cBoneBuffer[0]=0;
  sprintf(cBoneBuffer,"{\"name\":\"%s\", \"frame\":\"%i\", \"time\":\"%i\"}",devName,iID,millis());
  strcat (cBuffer,"\""); strcat (cBuffer,"Info"); strcat (cBuffer,"\":");
  strcat (cBuffer,cBoneBuffer);
  strcat (cBuffer,",\r\n");

  if (dbg!=NULL) {
    cBoneBuffer[0]=0;
    sprintf(cBoneBuffer,"{\"reg_self_test_xyza\":\"%X, %X, %X, %X, \", \"reg_smprt_div\":\"%x\", \"reg_config\":\"%x\", \"reg_gyro_config\":\"%x\", \"reg_user_ctrl\":\"%x\", ",
    dbg->data.reg_self_test_x, dbg->data.reg_self_test_y, dbg->data.reg_self_test_z, dbg->data.reg_self_test_a,
    dbg->data.reg_smprt_div, dbg->data.reg_config, dbg->data.reg_gyro_config, dbg->data.reg_user_ctrl);
    strcat (cBuffer,"\""); strcat (cBuffer,"debug"); strcat (cBuffer,"\":");
    strcat (cBuffer,cBoneBuffer);

    sprintf(cBoneBuffer,"\"reg_pwr_mgmt_1,2\":\"%X,%X\", \"reg_pwr_mgmt_2\":\"%x\", \"reg_fifo_counth,l\":\"%X,%X\"},\r\n",
    dbg->data.reg_pwr_mgmt_1, dbg->data.reg_pwr_mgmt_2, dbg->data.reg_fifo_counth, dbg->data.reg_fifo_countl );
    strcat (cBuffer,cBoneBuffer);
  }; // if *dbg

  cBoneBuffer[0]=0;
  sprintf(cBoneBuffer,"{\"aX\":\"%i\", \"aY\":\"%i\", \"aZ\":\"%i\", \"gX\":\"%i\", \"gY\":\"%i\", \"gZ\":\"%i\", \"t\":\"%i\", \"e\":\"%i\", \"n\":\"%i\" }",
  mes->data.accelX, mes->data.accelY, mes->data.accelZ, mes->data.gyroX, mes->data.gyroY, mes->data.gyroZ, mes->data.temp, mes->data.errorCode, mes->data.transmitted);
  strcat (cBuffer,"\""); strcat (cBuffer,cName); strcat (cBuffer,"\":");
  strcat (cBuffer,cBoneBuffer);
//  strcat (cBuffer,",\r\n");

  strcat (cBuffer,"\r\n}//---END---");
  client->write(cBuffer,strlen(cBuffer));
  client->println();
/*  

  unsigned long uiStart;
  unsigned long uiEnd;
  unsigned long uiDuration;
  uiStart = millis();
  client->flush();
  uiEnd = millis();
  uiDuration = uiEnd - uiStart;
  Serial.printf("flush duration=%i\r\n",uiDuration);
*/

};// publishMovements(...



int dataToJson(char *cBuffer, char cName[], MPU6050_Meassureing *mes, int iID, MPU6050_Debug *dbg=NULL){
  char cBoneBuffer[150];
  cBuffer[0]=0;
  strcat(cBuffer,"{");
  
  cBoneBuffer[0]=0;
  sprintf(cBoneBuffer,"{\r\n\"frame\":\"%i\", \"time\":\"%i\"},\r\n",iID,millis());
  strcat (cBuffer,"\""); strcat (cBuffer,"Info"); strcat (cBuffer,"\":");
  strcat (cBuffer,cBoneBuffer);

  if (dbg!=NULL) {
    cBoneBuffer[0]=0;
    sprintf(cBoneBuffer,"{\"reg_self_test_xyza\":\"%X, %X, %X, %X, \", \"reg_smprt_div\":\"%x\", \"reg_config\":\"%x\", \"reg_gyro_config\":\"%x\", \"reg_user_ctrl\":\"%x\", ",
    dbg->data.reg_self_test_x, dbg->data.reg_self_test_y, dbg->data.reg_self_test_z, dbg->data.reg_self_test_a,
    dbg->data.reg_smprt_div, dbg->data.reg_config, dbg->data.reg_gyro_config, dbg->data.reg_user_ctrl);
    strcat (cBuffer,"\""); strcat (cBuffer,"debug"); strcat (cBuffer,"\":");
    strcat (cBuffer,cBoneBuffer);

    sprintf(cBoneBuffer,"\"reg_pwr_mgmt_1,2\":\"%X,%X\", \"reg_pwr_mgmt_2\":\"%x\", \"reg_fifo_counth,l\":\"%X,%X\"},\r\n",
    dbg->data.reg_pwr_mgmt_1, dbg->data.reg_pwr_mgmt_2, dbg->data.reg_fifo_counth, dbg->data.reg_fifo_countl );
    strcat (cBuffer,cBoneBuffer);
  }; // if *dbg

  cBoneBuffer[0]=0;
  sprintf(cBoneBuffer,"{\"aX\":\"%i\", \"aY\":\"%i\", \"aZ\":\"%i\", \"gX\":\"%i\", \"gY\":\"%i\", \"gZ\":\"%i\", \"t\":\"%i\", \"e\":\"%i\", \"n\":\"%i\" }\r\n",
  mes->data.accelX, mes->data.accelY, mes->data.accelZ, mes->data.gyroX, mes->data.gyroY, mes->data.gyroZ, mes->data.temp, mes->data.errorCode, mes->data.transmitted);
  strcat (cBuffer,"\""); strcat (cBuffer,cName); strcat (cBuffer,"\":");
  strcat (cBuffer,cBoneBuffer);
  
}

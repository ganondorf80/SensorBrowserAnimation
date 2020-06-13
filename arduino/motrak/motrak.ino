#include <WiFi.h>
#include <Wire.h>
#include "MPU6050.h"
#include "functions.h"


#define iic0_scl 22
#define iic0_sda 21

#define iic1_scl -2
#define iic1_sda -2

//const char strIoTserver[]="47.52.119.195";
char strAPname[]="GlobeAtHome_Normann";
char strAPpwd[]="Wuerzburg_ist_d00f";
char strIoTserver[]="192.168.254.134";
char strDeviceName[]="Motrak_Hand";           // <<<< Change this for Other Devices
int  iIoTport=8889;
int  iServerPort=8888;

int  iFrameID;
unsigned long ulLastFrame;

WiFiServer server(iServerPort);
WiFiClient client;
WiFiClient clientIoT;
TwoWire iic0=TwoWire(0);
//TwoWire iic1=TwoWire(1);

MPU6050 sensor_0 = MPU6050(&iic0,0);
int iTotal;

void setup(){
  Serial.begin(115200);
  bool bResult=false;
  int  iResult=0;

  // Init IIC0:
  Serial.printf ("Init IIC Bus 0 : SDA=%2i SCL=%2i ...",iic0_sda,iic0_scl);
  bResult = iic0.begin(iic0_sda,iic0_scl);
  iic0.setClock(80000);
  if (bResult) Serial.println("success");
  else Serial.println("fail");

  // Init IIC1:
  bResult=false;
  Serial.printf ("Init IIC Bus 1 : SDA=%2i SCL=%2i ...",iic1_sda,iic1_scl);
  //bResult = iic1.begin(iic1_sda,iic1_scl);
  if (bResult) Serial.println("success");
  else Serial.println("fail");

//  iResult = sensor_0.begin(1,3,2,6);
  iResult = sensor_0.begin(1,2,2,3);
  delay(200);

  
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(strAPname, strAPpwd);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      //Serial.print(".");
    }; // while != WL_CONNECTED
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
    
  server.begin();
  iTotal=0;
  iFrameID=0;
  ulLastFrame=millis();
}; // void setup


MPU6050_Meassureing mes;
int16_t iValue;


void loop(){
  if (!client) {
    client = server.available();
  }
  sensor_0.readMeassureing(&mes, iFrameID);
  MPU6050_Debug conf;
  sensor_0.readConfig(&conf);

  if (client) {
    if (client.available()) {
      int n = client.available();
      int iResult = 0;
      uint8_t *uiBuffer = (uint8_t*) malloc(n+2);
      Serial.printf("\r\nuiBuffer address=0x%X.   recive. %4i byte", (unsigned long) uiBuffer,n);
      iResult = client.read(uiBuffer,n);
      uiBuffer[n]=0x00;
      Serial.printf(" iResult: %4i, n=%i.  Data:\r\n", iResult, n);
      Serial.write(uiBuffer,n);
      Serial.print("\r\n---\r\n");
      Serial.flush();

      if (strstr((char*)uiBuffer,"Upgrade: websocket")) {
        //client.write("HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\n");
        client.write("HTTP/1.1 101 Switching Protocols\r\n");
      }; // if websocket request.

      
      delay(100);
      free(uiBuffer);
    }; // if client.available()
    publishMovements(&client, strDeviceName, "Bone_00", &mes, iFrameID);//, &conf);
  }; // if client

  if (!clientIoT.connected()) clientIoT.connect(strIoTserver, iIoTport);
  if (clientIoT.connected()){
    publishMovements(&clientIoT, strDeviceName, "Bone_00", &mes, iFrameID);//, &conf);
  }; //if (clientIoT.connected()
  
  iFrameID++;
  unsigned long ulTime=millis();
  unsigned int uiDelay=(unsigned int)(unsigned long)((ulTime/100)*100+100) - ulTime;//100-abs(millis() - ulLastFrame);
  //Serial.printf("t=%i  uiDelay=%i\r\n",(millis() - ulLastFrame), uiDelay);
  delay(uiDelay);
  ulLastFrame=millis();
}; // void loop

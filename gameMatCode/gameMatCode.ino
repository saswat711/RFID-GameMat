#include "RfidMat.h"

#include <Arduino.h>

#include <BleKeyboard.h>

BleKeyboard bleGamepad;
// dEFINING BUTTON NO
// for Buttons
#define btnFwdLft 1
#define btnFwd 2
#define btnFwdRgt 3
#define btnLft 4
#define btnCenter 5
#define btnRgt 6
#define btnBckLft 7
#define btnBck 8
#define btnBckRgt 9


// for Buttons
bool fwdA = 0;
bool lftB = 0;
bool bckX = 0;
bool rgtY = 0;
bool fwdL = 0;
bool fwdR = 0;
bool center = 0;
bool bckL = 0;
bool bckR = 0;


void setup(){
   Serial.begin(19200);
   
   initialize();
      // The default bleGamepad.begin() above enables 16 buttons, all axes, one hat, start and select and no simulation controls
   bleGamepad.begin();
   Serial.println("Starting BLE work!");
}

void loop(){
     // put your main code here, to run repeatedly:
    // For forward
    if (bleGamepad.isConnected())
    {
        Serial.println("Ble is connected");
        readBtn();
        updateBtn();
        delay(500);
    }
   else
    {
        Serial.println("Ble is not connected!"); 
        delay(500);
    }
}


void readBtn(){
    fwdA = forForward();
    lftB = forBackward();
    bckX = forLeftward();
    rgtY = forRightward();
    center = forCenter();
    fwdL = forFwdLft();
    fwdR = forFwdRgt();
    bckL = forBckLft();
    bckR = forBckRgt();
  // To print serial values
  Serial.println((String)"1, 2, 3, 4, 5, 6, 7, 8, 9 : "+fwdL+" "+fwdA+" "+fwdR+" "+lftB+" "+center+" "+rgtY+" "+bckL+" "+bckX+" "+bckR);
}

void updateBtn(){
  if(fwdA){
    bleGamepad.write(btnFwd);
  }
    // For B button
  if(lftB){
        bleGamepad.write(btnLft);
  }
    // For X button
  if(bckX){
        bleGamepad.write(btnBck);
  }
    // For Y button
  if(rgtY){
        bleGamepad.write(btnRgt);
  }
  if(center){
   bleGamepad.write(btnCenter);
  }
  if(fwdL){
   bleGamepad.write(btnFwdLft);
  }
  if(fwdR){
   bleGamepad.write(btnFwdRgt);
  }
  if(bckL){
   bleGamepad.write(btnBckLft);
  }
  if(bckR){
   bleGamepad.write(btnBckRgt);
  }
  bleGamepad.releaseAll();
  rstBool();
}
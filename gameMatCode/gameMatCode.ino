#include "RfidMat.h"

#include <Arduino.h>
#include <Gamepad.h>

Gamepad bleGamepad;
// dEFINING BUTTON NO
// for Buttons
#define btnA BUTTON_1
#define btnB BUTTON_2
#define btnX BUTTON_3
#define btnY BUTTON_4
#define btnFwdLft BUTTON_5
#define btnFwdRgt BUTTON_6
#define btnCenter BUTTON_14
#define btnBckLft BUTTON_15
#define btnBckRgt BUTTON_16



// for Buttons
bool fwdA = 0;
bool  lftB = 0;
bool bckX = 0;
bool  rgtY = 0;
bool  fwdLft = 0;
bool  fwdRgt = 0;
bool  cntr = 0;
bool  bckLft = 0;
bool bckRgt = 0;

void setup(){
   Serial.begin(9600);
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
        delay(500);
    }
   else
    {
        Serial.println("Ble is not connected!"); 
                delay(500);
    }
}


void readBtn(){
    fwdA =  forForward();
    lftB = forBackward();
    bckX = forLeftward();
    rgtY = forRightward();
  // To print serial values
  Serial.println((String)"A, B, X, Y: "+fwdA+" "+lftB+" "+bckX+" "+rgtY);
}

void updateBtn(){
  if(fwdA){
    bleGamepad.press(btnA);
  }
  else{
    bleGamepad.release(btnA);
  }
    // For B button
  if(lftB){
        bleGamepad.press(btnB);
  }
  else{
      bleGamepad.release(btnB);
  }
    // For X button
  if(bckX){
        bleGamepad.press(btnX);
  }
  else{
      bleGamepad.release(btnX);
  }
    // For Y button
  if(rgtY){
        bleGamepad.press(btnY);
  }
  else{
      bleGamepad.release(btnY);
  }
}
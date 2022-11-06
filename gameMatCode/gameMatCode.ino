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
bool fwdLft = 0;
bool fwdRgt = 0;
bool cntr = 0;
bool bckLft = 0;
bool bckRgt = 0;

// Keypad



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
    bleGamepad.write(btnFwd);
  }
  else{
    bleGamepad.release(btnFwd);
  }
    // For B button
  if(lftB){
        bleGamepad.write(btnLft);
  }
  else{
      bleGamepad.release(btnLft);
  }
    // For X button
  if(bckX){
        bleGamepad.write(btnBck);
  }
  else{
      bleGamepad.release(btnBck);
  }
    // For Y button
  if(rgtY){
        bleGamepad.write(btnRgt);
  }
  else{
      bleGamepad.release(btnRgt);
  }
}
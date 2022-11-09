
#include <SPI.h>
#include <MFRC522.h>

#define SS_PINF 33
#define SS_PINB 0
#define SS_PINL 25
#define SS_PINR 27

#define RST_PIN 22
#define MOSI_PIN 23
#define MISO_PIN 19
#define SCK_PIN 18

MFRC522 rfidF(SS_PINF, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidB(SS_PINB, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidL(SS_PINL, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidR(SS_PINR, RST_PIN); // Create MFRC522 instance.

uint8_t total_RFID = 4;

void setSSzero()
{
  digitalWrite(SS_PINF, HIGH);
  digitalWrite(SS_PINB, HIGH);
  digitalWrite(SS_PINL, HIGH);
  digitalWrite(SS_PINR, HIGH);
  Serial.println("Set ALL select to zero ");
}
void rfidVer(){
    rfidF.PCD_DumpVersionToSerial();
    rfidB.PCD_DumpVersionToSerial();
    rfidL.PCD_DumpVersionToSerial();
    rfidR.PCD_DumpVersionToSerial();
}
void initialize()
{
  SPI.begin();// Initialize MFRCT22
  rfidF.PCD_Init();
  rfidB.PCD_Init();
  rfidL.PCD_Init();
  rfidR.PCD_Init();
  setSSzero();  
  Serial.println("CARD Initialize...");
  Serial.println();
  rfidVer();
  // // Configuring pin
  // pinMode(SS_PINF, INPUT);
  // pinMode(SS_PINL, INPUT);
  // pinMode(SS_PINR, INPUT);
  // pinMode(SS_PINB, INPUT);
  // BY default no RFID card selected
 
}

bool fwd = false;
bool bck = false;
bool lft = false;
bool rgt = false;
int repeat = 0;

void rstBool(){
  fwd = false;
  lft = false;
  bck = false;
  rgt = false;
}

bool forForward()
{
  rfidVer();
  repeat = 0;
  Serial.println("Forward");
  setSSzero();
  digitalWrite(SS_PINF,LOW);
  Serial.println("Forward write");
  Serial.println("Rfid");
  delay(500);
  while (!fwd && repeat < 5)
  {
    Serial.println("Searching for tag");
    // Look for new cards

    // Select one of the cards
  if (!rfidF.PICC_ReadCardSerial())
    {
          if (!rfidF.PICC_IsNewCardPresent())
    {
      Serial.println("No new Card");
      fwd = false;
    
    }
    else{
      Serial.println("CARD sERIAL CAN'T BE READ");
      fwd = false;
    }
    }
  else{// Show UID on serial monitor
    Serial.println("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < rfidF.uid.size; i++)
    {
      Serial.print(rfidF.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfidF.uid.uidByte[i], HEX);
      content.concat(String(rfidF.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfidF.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    fwd = true;
  }
    repeat++;
    delay(100);
  }
  // rfidF.PICC_HaltA();
  // rfidF.PCD_StopCrypto1();
  Serial.println("Reading fwd ");
  return fwd;
}
bool forBackward()
{
  repeat = 0;
  Serial.println("Backward");
  setSSzero();
  digitalWrite(SS_PINB,LOW);
  delay(500);
  while (!bck && repeat < 5)
  {
    Serial.println("Searching for tag");
    // Look for new cards

    // Select one of the cards
    if (!rfidB.PICC_ReadCardSerial())
    {
          if (!rfidB.PICC_IsNewCardPresent())
    {
      Serial.println("No new Card");
      bck = false;
   
    }
     else{
      Serial.println("CARD sERIAL CAN'T BE READ");
      bck = false;
     }
    }
    else{ // Show UID on serial monitor
    Serial.println("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < rfidB.uid.size; i++)
    {
      Serial.print(rfidB.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfidB.uid.uidByte[i], HEX);
      content.concat(String(rfidB.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfidB.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    bck = true;
  }
    repeat++;
    delay(100);
  }
//  rfidB.PICC_HaltA();
//   rfidB.PCD_StopCrypto1();
  Serial.println(" Reading back");
  return bck;
}
bool forLeftward()
{
  repeat = 0;
  Serial.println("LEFT");
  setSSzero();
  digitalWrite(SS_PINL,LOW);
  delay(500);
  while (!lft && repeat < 5)
  {
    Serial.println("Searching for tag");
    // Look for new cards

    // Select one of the cards
     if (!rfidL.PICC_ReadCardSerial())
    {
          if (!rfidL.PICC_IsNewCardPresent())
    {
      Serial.println("No new Card");
      lft = false;

    }
     else{ Serial.println("CARD sERIAL CAN'T BE READ");
      lft = false;
     }
    }
    // Show UID on serial monitor
    else{Serial.println("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < rfidL.uid.size; i++)
    {
      Serial.print(rfidL.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfidL.uid.uidByte[i], HEX);
      content.concat(String(rfidL.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfidL.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    lft = true;
    }
    repeat++;
    delay(100);
  }
//  rfidL.PICC_HaltA();
//   rfidL.PCD_StopCrypto1();
  Serial.println("Reading left");
  return lft;
}
bool forRightward()
{
  repeat = 0;
  Serial.println("Right");
  setSSzero();
   digitalWrite(SS_PINR,LOW);
  delay(500);
  while (!rgt && repeat < 5)
  {
    Serial.println("Searching for tag");
    // Look for new cards
  
    // Select one of the cards
    if (!rfidR.PICC_ReadCardSerial())
    {
        if (!rfidR.PICC_IsNewCardPresent())
    {
      Serial.println("No new Card");
      rgt = false;
     
    }
      else{ Serial.println("CARD sERIAL CAN'T BE READ");
      rgt = false;
      }
    }
    
    else{// Show UID on serial monitor
    Serial.println("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < rfidR.uid.size; i++)
    {
      Serial.print(rfidR.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfidR.uid.uidByte[i], HEX);
      content.concat(String(rfidR.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfidR.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    rgt = true;
  }
    repeat++;
    delay(100);
  }
  //  rfidR.PICC_HaltA();
  // rfidR.PCD_StopCrypto1();
  Serial.println("Readign right");
  return rgt;
}
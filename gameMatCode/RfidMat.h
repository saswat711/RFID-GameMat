
#include <SPI.h>
#include <MFRC522.h>
#define SS_PINF 33
#define SS_PINB 0
#define SS_PINL 25
#define SS_PINR 27
#define SS_PINC 26
#define SS_PINFL 32
#define SS_PINFR 23
#define SS_PINBL 4
#define SS_PINBR 2

#define RST_PIN 22  
#define MOSI_PIN 23
#define MISO_PIN 19
#define SCK_PIN 18


MFRC522 rfidF(SS_PINF, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidB(SS_PINB, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidL(SS_PINL, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidR(SS_PINR, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidC(SS_PINC, RST_PIN); // Create MFRC522 instance
MFRC522 rfidFL(SS_PINFL, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidFR(SS_PINFR, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidBL(SS_PINBL, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidBR(SS_PINBR, RST_PIN); // Create MFRC522 instance.

uint8_t total_RFID = 4;

void setSSzero()
{ 
  digitalWrite(SS_PINF, HIGH);
  digitalWrite(SS_PINB, HIGH);
  digitalWrite(SS_PINL, HIGH);
  digitalWrite(SS_PINR, HIGH);
  digitalWrite(SS_PINC, HIGH);
  digitalWrite(SS_PINFL,HIGH);
  digitalWrite(SS_PINFR,HIGH);
  digitalWrite(SS_PINBL,HIGH);
  digitalWrite(SS_PINBR,HIGH);
  Serial.println("Set ALL select to zero ");
}
void rfidVer(){
    rfidF.PCD_DumpVersionToSerial();
    rfidL.PCD_DumpVersionToSerial();
}
void initialize()
{
  SPI.begin();// Initialize MFRCT22
  rfidF.PCD_Init();
  rfidB.PCD_Init();
  rfidL.PCD_Init();
  rfidR.PCD_Init();
  rfidC.PCD_Init();
  rfidFL.PCD_Init();
  rfidFR.PCD_Init();
  rfidBL.PCD_Init();
  rfidBR.PCD_Init();
  setSSzero();  
  Serial.println("CARD Initialize...");
  Serial.println();
  rfidVer();
    
 
}

bool cardDetect = false;
int repeat = 0;

void rstBool(){
  cardDetect = false;
}

bool readRfid(MFRC522 rfid){
rfid.PCD_DumpVersionToSerial();
  bool temp = false;
   while (!temp && repeat < 5)
  {
    Serial.println("Searching for tag");
    // Look for new cards

    // Select one of the cards
  if (!rfid.PICC_ReadCardSerial())
    {
          if (!rfid.PICC_IsNewCardPresent())
    {
      Serial.println("No new Card");
      temp = false;
    
    }
    else{
      Serial.println("CARD sERIAL CAN'T BE READ");
      temp = false;
    }
    }
  else{// Show UID on serial monitor
    Serial.println("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < rfid.uid.size; i++)
    {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
      content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfid.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    temp = true;
    break;
  }
    repeat++;
  }
  delay(200);
  return temp;
}
bool forForward()
{
  repeat = 0;
  Serial.println("Forward");
  setSSzero();
  digitalWrite(SS_PINF,LOW);
  Serial.println("Forward write");
  Serial.println("Rfid");
   cardDetect=readRfid(rfidF);
  Serial.println("Already Read fwd ");
  return  cardDetect;
}
bool forBackward()
{
  repeat = 0;
  Serial.println("Backward");
  setSSzero();
  digitalWrite(SS_PINB,LOW);
   cardDetect=readRfid(rfidB);
  Serial.println("Already Read back");
  return  cardDetect;
}
bool forLeftward()
{
  repeat = 0;
  Serial.println("LEFT");
  setSSzero();
  digitalWrite(SS_PINL,LOW);
   cardDetect = readRfid(rfidL);
  Serial.println("Already Read left");
  return  cardDetect;
}
bool forRightward()
{
  repeat = 0;
  Serial.println("Right");
  setSSzero();
  digitalWrite(SS_PINR,LOW);
   cardDetect = readRfid(rfidR);
  Serial.println("ALready Read right");
  return  cardDetect;
}
bool forCenter()
{
  repeat = 0;
  Serial.println("Center");
  setSSzero();
  digitalWrite(SS_PINC,LOW);
   cardDetect = readRfid(rfidC);
  Serial.println("ALready Read center");
  return  cardDetect;
}
bool forFwdLft(){
  repeat = 0;
  Serial.println("Forward Left");
  setSSzero();
  digitalWrite(SS_PINFL,LOW);
   cardDetect = readRfid(rfidFL);
  Serial.println("Already Read forward left");
  return  cardDetect;
}
bool forFwdRgt(){
  repeat = 0;
  Serial.println("Forward Right");
  setSSzero();
  digitalWrite(SS_PINFR,LOW);
   cardDetect = readRfid(rfidFR);
  Serial.println("Already Read forward RIGHT");
  return  cardDetect;
}
bool forBckLft(){
  repeat = 0;
  Serial.println("Backward Left");
  setSSzero();
  digitalWrite(SS_PINBL,LOW);
   cardDetect = readRfid(rfidBL);
  Serial.println("Already Read backward left");
  return  cardDetect;
}
bool forBckRgt(){
  repeat = 0;
  Serial.println("Backward Right");
  setSSzero();
  digitalWrite(SS_PINBR,LOW);
   cardDetect = readRfid(rfidBR);
  Serial.println("Already Read backward RIGHT");
  return  cardDetect;
}

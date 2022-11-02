
#include <SPI.h>
#include <MFRC522.h>

#define SS_PINF 35
#define SS_PINB 32
#define SS_PINL 33
#define SS_PINR 25

#define RST_PIN 9
#define MOSI_PIN 23
#define MISO_PIN 19
#define SCK_PIN 18

#define RFIDsensorVDD 3.3 // VDD for 3.3V

MFRC522 rfidF(SS_PINF, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidB(SS_PINB, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidL(SS_PINL, RST_PIN); // Create MFRC522 instance.
MFRC522 rfidR(SS_PINR, RST_PIN); // Create MFRC522 instance.

int total_RFID = 4;

bool RFIDsearch(MFRC522 rfid)
{
    // Look for new cards
    if (!rfid.PICC_IsNewCardPresent())
    {
        return false;
    }
    // Select one of the cards
    if (!rfid.PICC_ReadCardSerial())
    {
        return false;
    }
    // Show UID on serial monitor
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
    return true;
}

void setSSzero()
{
    digitalWrite(SS_PINF, LOW);
    digitalWrite(SS_PINB, LOW);
    digitalWrite(SS_PINL, LOW);
    digitalWrite(SS_PINR, LOW);
      Serial.println("Set ALL select to zero ");
}
void initialize()
{
    // put your setup code here, to run once:
    SPI.begin();        // Initiate  SPI bus
    // Initialize MFRCT22
    rfidF.PCD_Init();
    rfidB.PCD_Init();
    rfidL.PCD_Init();
    rfidR.PCD_Init();

    Serial.println("CARD Initialize...");
    Serial.println();

    // Configuring pin
    pinMode(SS_PINF,OUTPUT);
    pinMode(SS_PINL,OUTPUT);
    pinMode(SS_PINR,OUTPUT);
    pinMode(SS_PINB,OUTPUT);
    // BY default no RFID card selected
    setSSzero();
}

bool fwd = false;
bool bck = false;
bool lft = false;
bool rgt = false;
int repeat = 0;

bool forForward()
{
    Serial.println("Forward");
    setSSzero();
    digitalWrite(SS_PINF, HIGH);
    Serial.println("Forward write");
    fwd = RFIDsearch(rfidF);
    Serial.println("Rfid");
      delay(500);
    while (!fwd && repeat < 5)
    {
        fwd = RFIDsearch(rfidF);
    }
      Serial.println("Reading fwd ");
    return fwd;
}
bool forBackward()
{
    Serial.println("Backward");
    setSSzero();
    digitalWrite(SS_PINB, HIGH);
    bck = RFIDsearch(rfidB);
      delay(500);
    while (!bck && repeat < 5)
    {
        bck = RFIDsearch(rfidB);
    }
    Serial.println(" Reading back");
    return bck;
}
bool forLeftward()
{
    Serial.println("LEFT");
    setSSzero();
    digitalWrite(SS_PINL, 1);
    lft = RFIDsearch(rfidL);
      delay(500);
    while (!lft && repeat < 5)
    {
        lft = RFIDsearch(rfidL);
    }
    Serial.println("Reading left");
    return lft;
}
bool forRightward()
{
    Serial.println("Right");
    setSSzero();
    digitalWrite(SS_PINR, 1);
    rgt = RFIDsearch(rfidR);
      delay(500);
    while (!rgt && repeat < 5)
    {
        rgt = RFIDsearch(rfidR);
    }
    Serial.println("Readign right");
    return rgt;
}
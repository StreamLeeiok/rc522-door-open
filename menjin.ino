/*
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          3             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/
#include<Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         3           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

byte myname1[18]="lee";
byte myname2[18]="qingy";
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
bool isyou=false;
Servo myservo;
//*****************************************************************************************//
void setup() {
   
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
     //shows in serial that it is ready to read
 
myservo.attach(9);
}

//*****************************************************************************************//
void loop() {

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }


  //-------------------------------------------

  //mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

 byte myname3[18];
 byte myname4[18];
  byte buffer1[18];

  block = 4;
  len = 18;

int jk=0;
  int ijk=0;
 
    //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
   
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
  
    return;
  }
 int j =0;
 
  //GET FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
     myname3[j]=buffer1[i];
    j++;
    }
  }


  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
   
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
 
    return;
  
  }
//*******************************
for (uint8_t i = 0,j=0; i < 16; i++)
  {
    if (buffer2[i] != 32)
    {
     myname4[j]=buffer2[i];
    j++;
    }
  }
for(ijk=0;ijk<3;ijk++)
  {
    if(myname1[ijk]!=myname3[ijk])
    {
    isyou=false;
   
    return;}
  
    }
//  for(jk=0;jk<5;jk++)
//  {if(myname2[jk]!=myname4[jk])
//  isyou = false;
//  return;}
  
  isyou=true;
  
  
  
  if(isyou){
 engine();
  }



  delay(500); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();




}
void engine()
{ int pos=0;
   for(pos = 0; pos < 180; pos += 1)
{
myservo.write(pos);
delay(15);
}
delay (1000);
for(pos = 180; pos>=1; pos-=1)
{
myservo.write(pos);
delay(15);
}
  }
  


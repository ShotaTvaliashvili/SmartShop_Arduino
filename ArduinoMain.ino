// /*
//    -------------------------------------------------------------------------------------
//    HX711_ADC
//    Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
//    Olav Kallhovd sept2017
//    -------------------------------------------------------------------------------------
// */

// /*
//    Settling time (number of samples) and data filtering can be adjusted in the config.h file
//    For calibration and storing the calibration value in eeprom, see example file "Calibration.ino"

//    The update() function checks for new data and starts the next conversion. In order to acheive maximum effective
//    sample rate, update() should be called at least as often as the HX711 sample rate; >10Hz@10SPS, >80Hz@80SPS.
//    If you have other time consuming code running (i.e. a graphical LCD), consider calling update() from an interrupt routine,
//    see example file "Read_1x_load_cell_interrupt_driven.ino".

//    This is an example sketch on how to use this library
// */

// #include <HX711_ADC.h>
// #if defined(ESP8266) || defined(ESP32) || defined(AVR)
// #include <EEPROM.h>
// #include <MFRC522.h>
// #include <SPI.h>

// #endif

// #define SS_PIN 10
// #define RST_PIN 9
// //pins:
// const int HX711_dout = 4;  //mcu > HX711 dout pin
// const int HX711_sck = 5;   //mcu > HX711 sck pin

// //HX711 constructor:
// HX711_ADC LoadCell(HX711_dout, HX711_sck);

// const int calVal_eepromAdress = 0;
// unsigned long t = 0;


// MFRC522 mfrc522(SS_PIN, RST_PIN);


// void setup() {

//   Serial.begin(115200);
//   SPI.begin();         // Initiate  SPI bus
//   mfrc522.PCD_Init();  // Initiate MFRC522
//   delay(10);
//   Serial.println();
//   Serial.println("Starting...");
//   Serial.println("Put your card to the reader...");
//   Serial.println();

//   LoadCell.begin();
//   //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
//   float calibrationValue;    // calibration value (see example file "Calibration.ino")
//   calibrationValue = 696.0;  // uncomment this if you want to set the calibration value in the sketch
// #if defined(ESP8266) || defined(ESP32)
//   //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
// #endif
//   EEPROM.get(calVal_eepromAdress, calibrationValue);  // uncomment this if you want to fetch the calibration value from eeprom

//   unsigned long stabilizingtime = 2000;  // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
//   boolean _tare = true;                  //set this to false if you don't want tare to be performed in the next step
//   LoadCell.start(stabilizingtime, _tare);
//   if (LoadCell.getTareTimeoutFlag()) {
//     Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
//     while (1)
//       ;
//   } else {
//     LoadCell.setCalFactor(calibrationValue);  // set calibration value (float)
//     Serial.println("Startup is complete");
//   }
// }

// static boolean newDataReady = 0;
// const int serialPrintInterval = 2000;  //increase value to slow down serial print activity
// float prevValue;

// void loop() {

//   float i;
//   //delay(2000);
//   // check for new data/start next conversion:
//   if (LoadCell.update()) newDataReady = true;

//   // get smoothed value from the dataset:
//   if (newDataReady) {
//     if (millis() > t + serialPrintInterval) {
//       i = LoadCell.getData();
//       prevValue = i;
//       //
//       newDataReady = 0;
//       t = millis();
//     }
//   } else {
//     i = prevValue;
//   }
//   Serial.print("Load_cell output val: ");
//   Serial.println(i);

//   // receive command from serial terminal, send 't' to initiate tare operation:
//   if (Serial.available() > 0) {
//     char inByte = Serial.read();
//     if (inByte == 't') LoadCell.tareNoDelay();
//   }

//   // check if last tare operation is complete:
//   if (LoadCell.getTareStatus() == true) {
//     Serial.println("Tare complete");
//   }


//   // Look for new cards
//   if (!mfrc522.PICC_IsNewCardPresent()) {
//     return;
//   }
//   // Select one of the cards
//   if (!mfrc522.PICC_ReadCardSerial()) {
//     return;
//   }
//   //Show UID on serial monitor
//   Serial.print("UID tag :");
//   String content = "";
//   byte letter;
//   for (byte i = 0; i < mfrc522.uid.size; i++) {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     content.concat(String(mfrc522.uid.uidByte[i], HEX));
//   }
//   Serial.println();
//   Serial.print("Message : ");
//   content.toUpperCase();
//   if (content.substring(1) == "63 CB 0B 0E")  //change here the UID of the card/cards that you want to give access
//   {
//     Serial.println("Authorized access");
//     Serial.println();
//     // myServo.write(180);
//     delay(5000);
//     // myServo.write(0);
//   }

//   else {
//     Serial.println("Access denied");
//     delay(1000);
//   }
// }




/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017
   -------------------------------------------------------------------------------------
*/

/*
   Settling time (number of samples) and data filtering can be adjusted in the config.h file
   For calibration and storing the calibration value in eeprom, see example file "Calibration.ino"

   The update() function checks for new data and starts the next conversion. In order to acheive maximum effective
   sample rate, update() should be called at least as often as the HX711 sample rate; >10Hz@10SPS, >80Hz@80SPS.
   If you have other time consuming code running (i.e. a graphical LCD), consider calling update() from an interrupt routine,
   see example file "Read_1x_load_cell_interrupt_driven.ino".

   This is an example sketch on how to use this library
*/

#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#include <MFRC522.h>
#include <SPI.h>

#endif

#define SS_PIN 10
#define RST_PIN 9
//pins:
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;


MFRC522 mfrc522(SS_PIN, RST_PIN); 


void setup() {

  Serial.begin(115200); 
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  delay(10);
  Serial.println();
  Serial.println("Starting...");
  Serial.println("Put your card to the reader...");
  Serial.println();

  LoadCell.begin();
  //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }
}

void loop() {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 500; //increase value to slow down serial print activity
  float i;
  //delay(2000);
  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      i = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.println(i);
      //
      newDataReady = 0;
      t = millis();
    }
  }

  // receive command from serial terminal, send 't' to initiate tare operation:
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay();
  }

  // check if last tare operation is complete:
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }


   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  print( content.substring(1))
  if (content.substring(1) == "63 CB 0B 0E" || content.substring(1) == "05 81 D0 84 AD C1 00") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    // myServo.write(180);
    delay(5000);
    // myServo.write(0);
  }
 
 else   {
    Serial.println("Access denied");
    delay(1000);
  }
}

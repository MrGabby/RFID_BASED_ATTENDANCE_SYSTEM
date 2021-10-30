/* terminal1 program
 
 ----------------------------------------------------------------------------- 
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               51                MOSI
 * SPI MISO   12               50                MISO
 * SPI SCK    13               52                SCK
 * voltage 3.3v 
 
 */

/*
l , m , n , o are the commands for student1 , student2 ... respectively. when the controller receives any of these commands 
a message will be sent to the parents of that student. 
 
a, b , c and d commands are used to let the students know that the 
teacher has arrived
 
*/
 
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
    SoftwareSerial SIM900(2, 4);
String textForSMS;
 
 
#define SS_PIN 10
#define RST_PIN 9
    MFRC522 mfrc522(SS_PIN, RST_PIN);
         // Create MFRC522 instance.
 
  void setup()
{
            Serial.begin(9600);
             // Initialize serial communications with the PC
        SIM900.begin(19200);
            SPI.begin();
                     // Init SPI bus
        mfrc522.PCD_Init();
             // Init MFRC522 card
         //Serial.println("Scan a MIFARE Classic PICC to demonstrate Value Blocks.");
        randomSeed(analogRead(0));
            delay(5000);
}
  void loop()
{
            
  if (Serial.available() == 0)
  
    {
                 // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        MFRC522::MIFARE_Key key;
                for (byte i = 0; i < 6; i++)
        {
                            key.keyByte[i] = 0xFF;
                    
        }
                 // Look for new cards
        if (!mfrc522.PICC_IsNewCardPresent())
        {
                            return;
                    
        }
         
         // Select one of the cards
        if (!mfrc522.PICC_ReadCardSerial())
        {
                            return;
                    
        }
                 // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
         // Dump UID
        Serial.print("Card UID:");
                for (byte i = 0; i < mfrc522.uid.size; i++)
        {
                         //   Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
             //   Serial.print(mfrc522.uid.uidByte[i], DEC);
        
        }
                Serial.println();
         
         // Dump PICC type
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
             //    Serial.print("PICC type: ");
            //Serial.println(mfrc522.PICC_GetTypeName(piccType));
        if (        piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K)
        {
                             //Serial.println("This sample only works with MIFARE Classic cards.");
                return;
                    
        }
                 // defining Cards here 
         // teacher
        if ((mfrc522.uid.uidByte[0] == 192) && (mfrc522.uid.uidByte[1] == 47) && (mfrc522.uid.uidByte[2] == 254) && (mfrc522.uid.uidByte[3] == 121)) // teacher card
        
        {
                    Serial.println("teacher");
                    delay(2000);
                
        
        }
                
                 // student1
        if ((mfrc522.uid.uidByte[0] == 189) && (mfrc522.uid.uidByte[1] == 54) && (mfrc522.uid.uidByte[2] == 235) && (mfrc522.uid.uidByte[3] == 213)) // student1 card
        
        {
                    Serial.println("stu1");
            Serial.println("1723200")  Serial.println("2nd Shift")
        delay(2000);
                    
        }
                
                         // student2
        if ((mfrc522.uid.uidByte[0] == 198) && (mfrc522.uid.uidByte[1] == 69) && (mfrc522.uid.uidByte[2] == 34) && (mfrc522.uid.uidByte[3] == 75)) // student2 card
        
        {
                    Serial.println("stu2");
            Serial.println("1723201")  Serial.println("2nd Shift")
        delay(2000);
                    
        }
                
                                 // student3
        if ((mfrc522.uid.uidByte[0] == 00) && (mfrc522.uid.uidByte[1] == 47) && (mfrc522.uid.uidByte[2] == 115) && (mfrc522.uid.uidByte[3] == 137)) // student3 card
        
        {
                    Serial.println("stu3");
            Serial.println("1723202")  Serial.println("2nd Shift")
        delay(2000);
                    
        }
         
        else         Serial.println("unregistered user");
                
    }
     
        // commands from graphical user interface application
 
  if (Serial.available() > 0)
  
    {

            char data = Serial.read();
          delay(1000);
             // messages to the students that the teacher has arrived

                   if (data == 'a') 
    
        {
                    textForSMS =  "\nFahad:Teacher has arrived";
              
  sendSMS5(textForSMS);
              Serial.println(textForSMS);
              Serial.println("message sent.");
               data = 'z'; // garbage value
            delay(5000);
              
    
        }
            
                       if (data == 'b') 
    
        {
                    textForSMS =  "\nRam:Teacher has arrived";
              
  sendSMS6(textForSMS);
              Serial.println(textForSMS);
              Serial.println("message sent.");
               data = 'z'; // garbage value
            delay(5000);
              
    
        }
            
        if (data == 'c') 
    
        {
                    textForSMS =  "\nJan sher:Teacher has arrived";
              
  sendSMS7(textForSMS);
              Serial.println(textForSMS);
              Serial.println("message sent.");
               data = 'z'; // garbage value
            delay(5000);
              
    
        }
            
       if (data == 'd') 
    
        {
                    textForSMS =  "\ndol:Teacher has arrived";
              
  sendSMS8(textForSMS);
              Serial.println(textForSMS);
              Serial.println("message sent.");
              data = 'z'; // garbage value
            delay(5000);
              
    
        }
            
     // messages to their parents to let them know their son/daughter is absent
    
        if (data == 'l') 
    
        {
                    textForSMS =  "\nFahad was absent today";
              
  sendSMS1(textForSMS);
              Serial.println(textForSMS);
              Serial.println("message sent.");
               data = 'z'; // garbage value
            delay(5000);
              
    
        }
            
      if (data == 'm') 
    
        {
                    textForSMS =  "\nRam was absent today";
              
  sendSMS2(textForSMS);
              Serial.println(textForSMS);
              Serial.println("message sent.");
               data = 'z'; // garbage value
            delay(5000);
              
    
        }
            
        if (data == 'n') 
    
        {
                    textForSMS =  "\nJoony was absent today";
              
  sendSMS3(textForSMS);
              Serial.println(textForSMS);
              Serial.println("message sent.");
               data = 'z'; // garbage value
            delay(5000);
              
    
        }
            
       if (data == '0') 
    
        {
                    textForSMS =  "\nWadood was absent today";
              
  sendSMS4(textForSMS);
              Serial.println(textForSMS);
              Serial.println("message sent.");
              data = 'z'; // garbage value
            delay(5000);
              
    
        }
            
  
    }
    Serial.println("PORT NOT AVALIABLE")
          
}
 
    // user defined functions for sending messages to students and parents
 
    // messages to students 
 
    // student1
    void
    sendSMS5(String message)
{
      SIM900.print("AT+CMGF=1\r");
                         // AT command to send SMS message
  delay(100);
    SIM900.println("AT + CMGS = \"+911111111111\"");
       // recipient's mobile number, in international format
 
  delay(100);
      SIM900.println(message);
                             // message to send
  delay(100);
      SIM900.println((char)26);
                             // End AT command with a ^Z, ASCII code 26  means end message
  delay(5000);
                                         // give module time to send SMS
}
 
    // student2
    void
    sendSMS6(String message)
{
      SIM900.print("AT+CMGF=1\r");
                         // AT command to send SMS message
  delay(100);
    SIM900.println("AT + CMGS = \"+912222222222\"");
       // recipient's mobile number, in international format
 
  delay(100);
      SIM900.println(message);
                             // message to send
  delay(100);
      SIM900.println((char)26);
                             // End AT command with a ^Z, ASCII code 26  means end message
  delay(5000);
                                         // give module time to send SMS
}
 
    // student3
    void
    sendSMS7(String message)
{
      SIM900.print("AT+CMGF=1\r");
                         // AT command to send SMS message
  delay(100);
    SIM900.println("AT + CMGS = \"+913333333333\"");
       // recipient's mobile number, in international format
 
  delay(100);
      SIM900.println(message);
                             // message to send
  delay(100);
      SIM900.println((char)26);
                             // End AT command with a ^Z, ASCII code 26 means end message
  delay(5000);
                                         // give module time to send SMS
}
// student4
void sendSMS8(String message)
{
      SIM900.print("AT+CMGF=1\r");
                         // AT command to send SMS message
  delay(100);
    SIM900.println("AT + CMGS = \"+914444444444\"");
       // recipient's mobile number, in international format
 
  delay(100);
      SIM900.println(message);
                             // message to send
  delay(100);
      SIM900.println((char)26);
                             // End AT command with a ^Z, ASCII code 26  means end message
  delay(5000);
                                         // give module time to send SMS
 
 
        // parents numbers
  void
    sendSMS1(String message)
    {
          SIM900.print("AT+CMGF=1\r");
                             // AT command to send SMS message
  delay(100);
        SIM900.println("AT + CMGS = \"+915555555555\"");
           // recipient's mobile number, in international format
 
  delay(100);
          SIM900.println(message);
                                 // message to send
  delay(100);
          SIM900.println((char)26);
                                 // End AT command with a ^Z, ASCII code 26  means end message
  delay(5000);
                                             // give module time to send SMS
    }
     
        // parents number2
        void
        sendSMS2(String message)
    {
          SIM900.print("AT+CMGF=1\r");
                             // AT command to send SMS message
  delay(100);
        SIM900.println("AT + CMGS = \"+916666666666\"");
           // recipient's mobile number, in international format
 
  delay(100);
          SIM900.println(message);
                                 // message to send
  delay(100);
          SIM900.println((char)26);
                                 // End AT command with a ^Z, ASCII code 26  means end message
  delay(5000);
                                             // give module time to send SMS
    }
     
        // parents number3
        void
        sendSMS3(String message)
    {
          SIM900.print("AT+CMGF=1\r");
                             // AT command to send SMS message
  delay(100);
        SIM900.println("AT + CMGS = \"+917777777777\"");
           // recipient's mobile number, in international format
 
  delay(100);
          SIM900.println(message);
                                 // message to send
  delay(100);
          SIM900.println((char)26);
                                 // End AT command with a ^Z, ASCII code 26  means end message
  delay(5000);
                                             // give module time to send SMS
    }
    // parents number4
    void sendSMS4(String message)
    {
          SIM900.print("AT+CMGF=1\r");
                             // AT command to send SMS message
  delay(100);
        SIM900.println("AT + CMGS = \"+918888888888\"");
           // recipient's mobile number, in international format
 
  delay(100);
          SIM900.println(message);
                                 // message to send
  delay(100);
          SIM900.println((char)26);
                                 // End AT command with a ^Z, ASCII code 26  means end message
  delay(5000);
                                             // give module time to send SMS                           
    }
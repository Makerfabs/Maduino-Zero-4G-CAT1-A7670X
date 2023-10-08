#include<stdio.h>
#include<string.h>
#include<string.h>

#define DEBUG true

//include the SD library:
#include <SPI.h>
#include <SD.h>

//www.makerfabs.com
//Test SD card
//Send AT Command via serial tool
//version:v1.1
//author:Charlin
//date:2023/10/08

#define LTE_RESET_PIN 6

#define LTE_PWRKEY_PIN 5


// change this to match your SD shield or module;
// Maduino zero 4G LTE: pin 4
const int PIN_SD_SELECT = 4;

#define UART_BAUD           115200

#define MODEM_RXD          0
#define MODEM_TXD          1


unsigned long currentTime;

void setup()
{

  SerialUSB.begin(115200);
  //while (!SerialUSB)
  {
    ; // wait for Arduino serial Monitor port to connect
  }
  Serial1.begin(115200);
  delay(1000);
  //Serial1.begin(UART_BAUD, SERIAL_8N1, MODEM_RXD, MODEM_TXD);

  pinMode(LTE_RESET_PIN, OUTPUT);
  digitalWrite(LTE_RESET_PIN, LOW);

  pinMode(LTE_PWRKEY_PIN, OUTPUT);
  digitalWrite(LTE_RESET_PIN, LOW);
  delay(100);
  digitalWrite(LTE_PWRKEY_PIN, HIGH);
  delay(3000);
  digitalWrite(LTE_PWRKEY_PIN, LOW);
    
  
  SerialUSB.println("Maduino Zero 4G LTE CAT1 Test Start!");

  SerialUSB.println("Wait a few minutes for 4G star");
  delay(3000);
  sendData("AT", 1000, DEBUG);
  sendData("AT+CICCID", 1000, DEBUG);
  sendData("AT+SIMCOMATI", 1000, DEBUG);
  sendData("AT+COPS?", 1000, DEBUG); 
  sendData("AT+GMR", 1000, DEBUG); 
  
  #if 0
  //Get GNSS location  //GPS test
  sendData("AT+CGNSSPWR=1", 1000, DEBUG);// turn the GPS on //must wait about 10s for GPS on
  delay(12000); //Go on after shows +CGNSSPWR: READY!
  
  sendData("AT+CGNSSIPR=9600", 1000, DEBUG);//
  sendData("AT+CGNSSTST=1", 1000, DEBUG);
  sendData("AT+CGNSSINFO", 1000, DEBUG);//get GPS infomation
  #endif

#if 1
//  delay(2000);
//  delay(2000);
  delay(1000);
  //sendData("AT", 1000, DEBUG);
  delay(1000);
  sendData("AT", 1000, DEBUG);
  delay(1000);
  sendData("AT+SIMCOMATI", 1000, DEBUG);
  delay(1000);
  sendData("AT+CICCID", 1000, DEBUG);
  sendData("AT+CNUM", 1000, DEBUG);
  sendData("AT+COPS?", 1000, DEBUG);    
  sendData("AT+CPSI?", 1000, DEBUG);
  sendData("AT+CNMP?", 1000, DEBUG);
  
  //Http test
  sendData("AT+HTTPINIT", 1000, DEBUG);
  sendData("AT+HTTPPARA=\"URL\",\"https://ss0.bdstatic.com/5aV1bjqh_Q23odCf/static/mancard/css/card_min_dee38e45.css\"", 1000, DEBUG);
  sendData("AT+HTTPACTION=0", 1000, DEBUG);
  sendData("AT+CSQ", 1000, DEBUG);
  sendData("AT+HTTPHEAD", 1000, DEBUG);
  sendData("AT+HTTPREAD=0,500", 1000, DEBUG);
  sendData("AT+HTTPTERM", 1000, DEBUG);
#endif

//Make a call
#if 0
  sendData("ATD10086;", 1000, DEBUG);
  sendData("AT+COUTGAIN=2", 1000, DEBUG);//from (0-7)
  sendData("AT+CHUP", 1000, DEBUG);//end the call
#endif
  sendData("AT+CICCID", 1000, DEBUG);
 
   currentTime = millis();
}

void loop()
{
  if(millis()-currentTime>50000)
  {
      currentTime = millis();//refresh
      //sendData("AT+CGNSSINFO", 1000, DEBUG);//get GPS infomation
     // sendData("AT+CHUP", 1000, DEBUG);//end the call
  }
  //SerialUSB.println("echo test!");
  while (Serial1.available() > 0) {
    SerialUSB.write(Serial1.read());
    yield();
  }
  while (SerialUSB.available() > 0) {
    Serial1.write(SerialUSB.read());
    yield();
  }
}


String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  Serial1.println(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      response += c;
    }
  }
  if (debug)
  {
    SerialUSB.print(response);
  }
  return response;
}

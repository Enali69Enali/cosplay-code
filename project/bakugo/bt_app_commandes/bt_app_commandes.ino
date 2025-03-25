#include<SoftwareSerial.h>
// The SoftwareSerial library enables serial communication on any digital pins of a microcontroller, simulating an additional serial port. 
// It is useful when the hardware has only one hardware serial port or when multiple serial devices need to be used simultaneously.

#define RX 11 
#define TX 10

SoftwareSerial BlueT(RX,TX);
char recvChar;
char consigne;


/* Constants for communication with the KT403A module */
const byte COMMAND_BYTE_START = 0x7E;
const byte COMMAND_BYTE_VERSION = 0xFF;
const byte COMMAND_BYTE_STOP = 0xEF;

/* Low level function to send a command to the KT403A module */
void send_kt_command(byte command, byte data_h, byte data_l, unsigned long cmd_delay) {
  Serial.write(COMMAND_BYTE_START);
  Serial.write(COMMAND_BYTE_VERSION);
  Serial.write((byte) 0x06);
  Serial.write(command);
  Serial.write((byte) 0x00);
  Serial.write(data_h);
  Serial.write(data_l);
  Serial.write(COMMAND_BYTE_STOP);
  // 16-bits checksum is optionnal
  delay(cmd_delay);
}


void setup(){
  Serial.begin(9600);
  delay(500);
  Serial.println("Bonjour - Pret pour les commandes AT");
  BlueT.begin(9600);
  delay(500);}

void loop(){
  while (BlueT.available()) {
    consigne=char(BlueT.read());
    Serial.println(consigne);
    switch (consigne){
      case '0':
        //send_kt_command(0x06, 0, 0, 10);
        //setVolume(0);
        break;
      case '1':
        //send_kt_command(0x06, 0, 3, 10);
        //setVolume(1);
        break;
      case '2':
        //send_kt_command(0x06, 0, 6, 10);
        //setVolume(2);
        break;
      case '3':
        //send_kt_command(0x06, 0, 9, 10);
        //setVolume(3);
        break;
      case '4':
        //send_kt_command(0x06, 0, 12, 10);
        //setVolume(4);
        break;
      case '5':
        //send_kt_command(0x06, 0, 15, 10);
        //setVolume(5);
        break;
      case '6':
        //send_kt_command(0x06, 0, 18, 10);
        //setVolume(6);
        break;
      case '7':
        //send_kt_command(0x06, 0, 21, 10);
        //setVolume(7);
        break;
      case '8':
        //send_kt_command(0x06, 0, 24, 10);
        //setVolume(8);
        break;
      case '9':
        //send_kt_command(0x06, 0, 27, 10);
        //setVolume(9);
        break;

      case 'A':
        Serial.println("Musique d'après");
       break;
      case 'B':
        Serial.println("Musique d'avant");
       break;
      case 'L':
        Serial.println("lecture mistro");
        //send_kt_command(0x0D, 0, 0, 20);
        break;
      case 'S':
        Serial.println("Stop music");
        //send_kt_command(0x16, 0, 0, 20);
        break;
    }    
    
    }  
}

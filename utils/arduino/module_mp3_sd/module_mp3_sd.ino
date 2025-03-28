#include <SoftwareSerial.h>;
// The SoftwareSerial library enables serial communication on any digital pins of a microcontroller, simulating an additional serial port. 
// It is useful when the hardware has only one hardware serial port or when multiple serial devices need to be used simultaneously.
// All the commands needed in the datasheet(http://geekmatic.in.ua/pdf/Catalex_MP3_board.pdf) 

#define RX 12
#define TX 13

SoftwareSerial mySerial(RX,TX);

////////////////////////////////////////////////////////////////////////////////////

static int8_t Send_buf[8] = {0} ;// The MP3 player undestands orders in a 8 int string 
                                 // 0X7E FF 06 command 00 00 00 EF;(if command =01 next song order)  

#define NEXT_SONG 0X01  
#define PREV_SONG 0X02  
#define CMD_PLAY_W_INDEX 0X03 //DATA IS REQUIRED (number of song) 
#define VOLUME_UP_ONE 0X04 
#define VOLUME_DOWN_ONE 0X05 
#define CMD_SET_VOLUME 0X06//DATA IS REQUIRED (number of volume from 0 up to 30(0x1E)) 
#define SET_DAC 0X17 
#define CMD_PLAY_WITHVOLUME 0X22 //data is needed  0x7E 06 22 00 xx yy EF;(xx volume)(yy number of song) 
#define CMD_SEL_DEV 0X09 //SELECT STORAGE DEVICE, DATA IS REQUIRED 
#define DEV_TF 0X02 //HELLO,IM THE DATA REQUIRED 
#define SLEEP_MODE_START 0X0A 
#define SLEEP_MODE_WAKEUP 0X0B 
#define CMD_RESET 0X0C//CHIP RESET 
#define CMD_PLAY 0X0D //RESUME PLAYBACK 
#define CMD_PAUSE 0X0E //PLAYBACK IS PAUSED 
#define CMD_PLAY_WITHFOLDER 0X0F//DATA IS NEEDED, 0x7E 06 0F 00 01 02 EF;(play the song with the directory \01\002xxxxxx.mp3 
#define STOP_PLAY 0X16 
#define PLAY_FOLDER 0X17// data is needed 0x7E 06 17 00 01 XX EF;(play the 01 folder)(value xx we dont care) 
#define SET_CYCLEPLAY 0X19//data is needed 00 start; 01 close 
#define SET_DAC 0X17//data is needed 00 start DAC OUTPUT;01 DAC no output 
#define SINGLE_PLAY 0X08//Single play(without folder)

////////////////////////////////////////////////////////////////////////////////////  

void sendCommand(int8_t command, int16_t dat) { 
  delay(20); 
  Send_buf[0] = 0x7e;             // Starting byte 
  Send_buf[1] = 0xff;             // Version 
  Send_buf[2] = 0x06;             // The number of bytes of the command without starting byte and ending byte 
  Send_buf[3] = command; 
  Send_buf[4] = 0x00;             // 0x00 = no feedback, 0x01 = feedback 
  Send_buf[5] = (int8_t)(dat >> 8); // datah 
  Send_buf[6] = (int8_t)(dat);    // datal 
  Send_buf[7] = 0xef;             // Ending byte 
  for(uint8_t i=0; i<8; i++){ 
    mySerial.write(Send_buf[i]) ; 
  } 
} 

void setup() {
  mySerial.begin(9600);           // Start our Serial coms for our serial monitor! 
  delay(500);                     // Wait chip initialization is complete 
  sendCommand(CMD_SEL_DEV, DEV_TF); // Select the TF card   
  delay(200);
}


void loop() {
  sendCommand(CMD_PLAY_WITHFOLDER, 0X0303); // 3e song in the folder
  delay(3000);
}

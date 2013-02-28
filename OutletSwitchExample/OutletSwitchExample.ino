/*
 Author: Harm Reck
 
 This sketch lets you switch Cheap RCOutlets via the Serialport.
 
 See http://h-reg.blogspot.de/2013/02/hain-schalten-und-walten.html for more details and explanations


 This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 Germany License. To view a copy of this license, 
 visit http://creativecommons.org/licenses/by-sa/3.0/de/ or send a letter to 
 Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include <RCSwitch.h>



#define ON 1
#define OFF 0


RCSwitch mySwitch = RCSwitch();



void setup() {

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(3);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0){
    char buffer[20];

    int numRead = Serial.readBytesUntil('\n',buffer,20);
    Serial.print("received: ");
    Serial.println(buffer);
    char * tok;
    tok = strtok(buffer, ":");
    Serial.print("Token is: ");
    Serial.println(tok);

    
    
    switch(tok[0]){
     case 'S':
      Serial.println("processing SwitchCommand");
      processSwitch(buffer); 
      
    }

    
  }

  

}


void processSwitch(char *cmdString){
 
      

      char houseCode[6] = "";
      for (int i = 2; i < 7; i++){
        houseCode[i-2] = cmdString[i];
      }
      houseCode[6] = '\0';
      Serial.print("Housecode: ");
      Serial.println(houseCode);

      int deviceNumber = cmdString[7]-48;  
      Serial.print("devicenumber");
      Serial.println(deviceNumber, DEC);
      int action = cmdString[8]-48; 
      switch(action){
      case ON:
        Serial.println("switching ON");
        mySwitch.switchOn(houseCode, deviceNumber);
        break;
      case OFF:
        Serial.println("switching OFF");
        mySwitch.switchOff(houseCode, deviceNumber);
        break;
      }
    
  
}





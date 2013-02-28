

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
    
    char * tok;

    
    
    switch(tok[0]){
     case 'S':
      processSwitch(buffer); 
      
    }

    
  }

  

}


void processSwitch(char *cmdString){
 if(strlen(cmdString) == 9){
      

      char houseCode[6] = "";
      for (int i = 2; i < 7; i++){
        houseCode[i-2] = cmdString[i];
      }
      houseCode[6] = '\0';

      int deviceNumber = cmdString[7]-48;  
      int action = cmdString[8]-48; 
      switch(action){
      case ON:
        mySwitch.switchOn(houseCode, deviceNumber);
        break;
      case OFF:
        mySwitch.switchOff(houseCode, deviceNumber);
        break;
      }
    } 
  
}





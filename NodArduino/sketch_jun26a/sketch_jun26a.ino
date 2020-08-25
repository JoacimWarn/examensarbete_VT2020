#include <Ethernet.h>

/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

  pinMode(4, OUTPUT);
  
}

void loop() {
  
  if (mySwitch.available()) {

    int recValue = mySwitch.getReceivedValue();
    unsigned int* recRaw = mySwitch.getReceivedRawdata();
    unsigned int* ptr;

    ptr = &recRaw[0];
    
    Serial.print("Mottaget ");
    Serial.println( recValue);
    //while(*ptr){
      //Serial.println(*ptr++);
    //}
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );

    if(recValue == 1364){

      Serial.println("Slå av");
      //stäng av
      digitalWrite(4, LOW);
      
    }
    else if(recValue == 1361){

      Serial.println("Slå på");
      //slå på
      digitalWrite(4, HIGH);
      
    }
    
    mySwitch.resetAvailable();
    
  }

}

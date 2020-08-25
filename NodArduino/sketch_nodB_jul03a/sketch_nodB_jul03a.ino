/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int pulseLength = 188;

void setup() {

  delay(5000);
  
  Serial.begin(9600);
  //mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  mySwitch.disableReceive();
  mySwitch.enableTransmit(8);

  //mySwitch.setPulseLength(350);

  //mySwitch.setPulseLength(pulseLength);
  
  mySwitch.setRepeatTransmit(10);
  
  //pinMode(8, OUTPUT);

  pinMode(4, OUTPUT);
  
}

void loop() {

  /*
  
  if (mySwitch.available()) {

    int recValue = mySwitch.getReceivedValue();
    
    Serial.print("Mottaget ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );

    if(recValue == 4436){

      Serial.println("Slå av");
      //stäng av
      digitalWrite(4, LOW);
      
    }
    else if(recValue == 4433){

      Serial.println("Slå på");
      //slå på
      digitalWrite(4, HIGH);
      
    }
    
    mySwitch.resetAvailable();
    
  }

  */
    //mySwitch.setProtocol(i++);

    
    mySwitch.switchOn(1);
    mySwitch.switchOn(1);
    //mySwitch.switchOn(1);

    //mySwitch.send("11111111");

    //mySwitch.setPulseLength(pulseLength);

    //Serial.println(pulseLength);

    //pulseLength = pulseLength + 10;
    
  //mySwitch.disableTransmit();

    //delay(2000);
  
    //mySwitch.setPulseLength(i);

    //i = i + 50;

    //Serial.println(i);
    
}

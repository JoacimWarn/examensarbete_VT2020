
/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>
#include <ipv4.h>

RCSwitch mySwitch = RCSwitch();
ipv4 ip = ipv4();

void setup() {
  Serial.begin(9600);
  //mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  mySwitch.enableTransmit(8);

  pinMode(8, OUTPUT);
  //Serial.println(ip.);
  
}

void loop() {

  int counter = 0;

  if(!ip.gotAdress){


    while(counter < 10){

      mySwitch.switchOn(counter, 8);

      counter++;
      
    }
    
    //mySwitch.switchOn(1, 8);

    //mySwitch.switchOn(500, 24);
    
    //int* ptrToAdress;
    //ptrToAdress = ip.getSourceAdress();
    
   //Serial.println("hey");

    //Serial.println(ip.ipHeader.source[2]);
    //Serial.println(*ptrToAdress);
    //Serial.println(ip.getSourceAdress());

    mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

    int ipAdressToAssign[4];
    int counter = 0;
    int recValue = 0;
    int recPrev = -1;
    //ask raspberry pi for an ip adress
    while(true){
      
      if(mySwitch.available()){

        if(counter < 4){

          recValue = mySwitch.getReceivedValue();
          //recValue[counter] = mySwitch.getReceivedValue();
          if(recValue != recPrev){

            ipAdressToAssign[counter] = recValue;
            Serial.println(recValue);
            counter++;
            
          }

          recPrev = recValue;
          
        }
        else{

          break;
          
        }
        //Serial.println(mySwitch.getReceivedValue());

      mySwitch.resetAvailable();
      
    }
    
    }

    ip.setSourceAdress(&ipAdressToAssign[0]);

    int* ptr;
    counter = 0;

    ptr = ip.getSourceAdress();

    Serial.println("The ip adress is:");
    while(*ptr && counter < 4){

      Serial.print(*ptr++);
      Serial.print(".");
      counter++;
      
    }

    delay(5000);
    
  }
  else{

    if(mySwitch.available()){

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

}

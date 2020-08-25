#include <RCSwitch.h>
#include <ipv4.h>

RCSwitch mySwitch = RCSwitch();
ipv4 ip = ipv4();

int valueToSend = 0;
int recValue = 0;
int adressToSet = -1;

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  //mySwitch.enableTransmit(8);

  //pinMode(8, OUTPUT);
  //Serial.println(ip.);
  
}

void loop() {

  while(!ip.gotAdress){
    
    //attempt to receive an ip adress from the raspberry pi
    //send request signal

    ip.csmaca(mySwitch.available());

    if(!ip.isTransmitting){

      //no one is sending, attempt to get an ip adress
      mySwitch.disableReceive();
      mySwitch.enableTransmit(8);
      valueToSend = 555;
      mySwitch.send(valueToSend, 24);
      mySwitch.disableTransmit();
      mySwitch.enableReceive(0);

      while(true){

        if(mySwitch.available()){

        recValue = mySwitch.getReceivedValue();
        
        if(ip.transmissionSync(recValue)){

          int timer = 0;
          recValue = 0;
          
          Serial.println("handshake success!");
          //succesful handshake, assign ip adress

          mySwitch.resetAvailable();
          
          while(timer < 50){

            recValue = 0;

            Serial.println("inside timer loop");
            
            if(mySwitch.available()){
  
              //Serial.println("inside timer loop");
  
              recValue = mySwitch.getReceivedValue();
              valueToSend = recValue;

              Serial.print("got a value:");
              Serial.println(recValue);
  
              mySwitch.disableReceive();
              mySwitch.enableTransmit(8);
  
              mySwitch.switchOn(valueToSend, 24);
  
              adressToSet = recValue;
  
              //if the adress was right, an okay value of 888 will be sent, otherwise 666
              mySwitch.disableTransmit();
              mySwitch.enableReceive(0);
  
                if(mySwitch.available()){
                  
                  recValue = mySwitch.getReceivedValue();
    
                  if(ip.adressAssignment(recValue)){
    
                    //assign the adress!
                    int adress[4];
                    adress[0] = 192;
                    adress[1] = 168;
                    adress[2] = 1;
                    adress[3] = adressToSet;
    
                    ip.setSourceAdress(adress);
    
                    Serial.println("ip adress succesfully assigned!");
    
                    break;
                    
                  }
                  
                  mySwitch.resetAvailable();
                  
                }

              mySwitch.resetAvailable();
                
            }
          
          timer++;
          
        }

        recValue = 0;
        
        }
        
          mySwitch.resetAvailable();
          recValue = 0;
          
        }

      }
      
    }
    
  }
  while(ip.gotAdress){

    ip.csmaca(mySwitch.available());

    recValue = mySwitch.getReceivedValue();

    Serial.println("data:" + recValue);

    if(!ip.isTransmitting){

      //no one is sending, send the data
      
    }
    
  }
  
}

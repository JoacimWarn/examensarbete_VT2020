#include <RCSwitch.h>
#include <ipv4.h>

RCSwitch mySwitch = RCSwitch();
ipv4 ip = ipv4();

int recValue = -1;
int valueToSend = 0;

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  //mySwitch.enableTransmit(8);

  //pinMode(8, OUTPUT);
  //Serial.println(ip.);

}

void loop() {
  // put your main code here, to run repeatedly:
  START:
  while(!ip.gotAdress){

    ip.csmaca(mySwitch.available());

    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);

    //while(true);

    if(!ip.isTransmitting){

        while(true){

      ip.csmaca(mySwitch.available());
        
       mySwitch.disableReceive();
       mySwitch.enableTransmit(8);
       valueToSend = 555;
       mySwitch.send(valueToSend, 24);
       mySwitch.disableTransmit();
       mySwitch.enableReceive(0);

        delay(500);
        //while(true){

        if(mySwitch.available()){
          
          
          recValue = mySwitch.getReceivedValue();
          if(ip.transmissionSync(recValue)){

            mySwitch.resetAvailable();
            Serial.println("handskakning mottagen från server");

            while(!ip.gotAdress){

              delay(1000);
              
              //loopa tills en adress har fåtts
              if(mySwitch.available()){

                recValue = mySwitch.getReceivedValue();
                ip.setSourceAdress(recValue);

                mySwitch.resetAvailable();
                Serial.println("adress är satt till:");
                int* ptr;
                ptr = ip.getSourceAdress();
                while(*ptr){
                  Serial.print(*ptr++);
                  Serial.print(".");
                }

                goto START;
                
              }
              
            }
            
          }
          
        }
        }
       //recValue = mySwitch.getReceivedValue();

       Serial.println(recValue);

      mySwitch.resetAvailable();
      
    }
    
  }
digitalWrite(7, LOW);
}

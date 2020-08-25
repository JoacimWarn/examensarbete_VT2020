/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "ipv4.h"
#include "433Anslutning.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    int transmitterPin = 23;
    int receiverPin = 2;
    
    if (wiringPiSetup () == -1) return 1;
	//printf("sending systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);
	RCSwitch mySwitch = RCSwitch();
    ipv4 ip = ipv4();
	//mySwitch.enableTransmit(transmitterPin);
    //mySwitch.disableTransmit();
    
    mySwitch.disableTransmit();
    //mySwitch.enableTransmit(transmitterPin);
    
    //mySwitch.disableTransmit();
    mySwitch.enableReceive(receiverPin);
    wiringPiISR(receiverPin, INT_EDGE_BOTH, mySwitch.handleInterrupt);
    
    //pinMode(23, INPUT);
    
    int recValue = 0;
    int valueToSend = 0;
    
    while(true){
        
        if(mySwitch.available()){
            
            system("gpio edge 27 none");
            
            recValue = mySwitch.getReceivedValue();
            //tog emot meddelande
            if(recValue == 555){
                
                printf("handskakning mottagen, nod vill bli tilldelad en adress\n");
                //nod vill göra handskakning
                //system("gpio edge 27 none");
                valueToSend = 777;
                
                mySwitch.enableTransmit(transmitterPin);
                mySwitch.send(valueToSend, 24);
                mySwitch.disableTransmit();
                pinMode(23, INPUT);
                
                int* freeAdresses = ip.getTakenAdresses();
                int counter = 0;
                
                while(true){
                    
                    //loopa tills adress blivit tilldelad till nod
                    while(counter < NUMBER_OF_ADRESSES){
                        
                        if(*freeAdresses != 0){
                            
                            valueToSend = *freeAdresses;
                            //freeAdresses++;
                            break;
                            
                        }
                        
                        freeAdresses++;
                        
                    }
                    
                    printf("adress som skickas till nod:%d\n", valueToSend);
                    
                    ip.unAssignedAdresses[valueToSend] = 0;
                    
                    pinMode(23, OUTPUT);
                    mySwitch.enableTransmit(transmitterPin);
                    mySwitch.send(valueToSend, 24);
                    mySwitch.disableTransmit();
                    pinMode(23, INPUT);
                    
                    break;
                    
                }
                
            }
            
            mySwitch.resetAvailable();
            delay(500);
            system("gpio edge 27 both");
            
        }
        
        //break;
        
    }
    
    //turns off interrupt on pinnumber 2
    system("gpio edge 27 none");
    
    //mySwitch.enableTransmit(transmitterPin);
    
    //printf("Sending...\n");
     

    printf("Allokerade adresser är:\n");
    
    int* ptr;
    ptr = ip.getTakenAdresses();
    int i = 1;
    
    while(i < NUMBER_OF_ADRESSES){
        
        if(*ptr == 0){
            
            printf("192.168.1.%d\n", i);
            
        }
        
        i++;
        ptr++;
        
    }
    
    
    
	return 0;
}

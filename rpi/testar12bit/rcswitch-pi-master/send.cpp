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
    
    //mySwitch.enableTransmit(transmitterPin);
    
    //mySwitch.disableTransmit();
    mySwitch.enableReceive(receiverPin);
    
    wiringPiISR(receiverPin, INT_EDGE_BOTH, mySwitch.handleInterrupt);
    
    int recValue = 0;
    int valueToSend = 0;
    
    while(true){
        
        printf("back in main loop\n");
        
        if(mySwitch.available()){
            
            recValue = mySwitch.getReceivedValue();
            
            if(recValue == 555){
                
                //a node asks for an ip adress
                system("gpio edge 27 none");
                printf("%d\n", recValue);
                mySwitch.enableTransmit(transmitterPin);
                valueToSend = 777;
                mySwitch.switchOn(valueToSend, 24);
                //mySwitch.disableTransmit();
                printf("handshake sent\n");
                
                int* freeAdresses = ip.getTakenAdresses();
                int counter = 0;
                int adressToSend = 0;
                while(counter < NUMBER_OF_ADRESSES){
                    
                    if(*freeAdresses != 0){
                        
                        adressToSend = *freeAdresses;
                        break;
                        
                    }
                    
                    freeAdresses++;
                    counter++;
                    
                }
                
                printf("found an adress:%d\n", adressToSend);
                
                mySwitch.enableTransmit(transmitterPin);
                mySwitch.setRepeatTransmit(20);
                mySwitch.switchOn(adressToSend, 8);
                
                printf("adress sent\n");
                
                system("gpio edge 27 both");
                mySwitch.enableReceive(receiverPin);
                //wiringPiISR(receiverPin, INT_EDGE_BOTH, mySwitch.handleInterrupt);
                
                counter = 0;
                
                while(counter < 200000000){
                    
                    //printf("waiting for receiving...\n");
                    
                    if(mySwitch.available()){
                        
                        system("gpio edge 27 none");
                        recValue = mySwitch.getReceivedValue();
                        
                        printf("received value:%d\n", recValue);
                        
                        if(ip.adressAssignment(adressToSend, recValue)){
                            
                            //send okay sign and allocate the adress
                            ip.unAssignedAdresses[adressToSend] = 0;
                            valueToSend = 888;
                            printf("adress set succesfully\n");
                            
                        }
                        else{
                            
                            //send not okay sign
                            valueToSend = 666;
                            printf("failed to set adress\n");
                            
                        }
                        
                        mySwitch.switchOn(valueToSend, 24);
                        
                        mySwitch.resetAvailable();
                        system("gpio edge 27 both");
                        mySwitch.enableReceive(receiverPin);
                        //wiringPiISR(receiverPin, INT_EDGE_BOTH, mySwitch.handleInterrupt);
                        
                    }
                    
                    counter++;
                    
                }
                
                //mySwitch.disableTransmit();
                
                system("gpio edge 27 both");
                mySwitch.enableReceive(receiverPin);
                //wiringPiISR(receiverPin, INT_EDGE_BOTH, mySwitch.handleInterrupt);
                
            }
                
            system("gpio edge 27 both");
            mySwitch.enableReceive(receiverPin);
            //wiringPiISR(receiverPin, INT_EDGE_BOTH, mySwitch.handleInterrupt);
            valueToSend = 0;
            recValue = 0;
            mySwitch.resetAvailable();
            
            delay(3000);
            
        }
        
    }
    
    //turns off interrupt on pinnumber 2
    system("gpio edge 27 none");
    
    //mySwitch.enableTransmit(transmitterPin);
    
    printf("Sending...\n");
     

    printf("Taken adresses are\n");
    
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

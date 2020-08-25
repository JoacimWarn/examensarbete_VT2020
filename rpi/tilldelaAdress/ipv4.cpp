#include "ipv4.h"

/*
ipv4 class definition for server
*/

ipv4::ipv4(){
	
	for(int i = 1; i < NUMBER_OF_ADRESSES; i++){
		
		unAssignedAdresses[i] = i;
		
	}
	
	for(int i = 0; i < 4; i++){
		
		ipHeader.destination[i] = 0;
		
	}
	//memset(ipHeader.source, 0, 4);
	//memset(ipHeader.destination, 0, 4);
	this->gotAdress = false;
	ipHeader.TTL = 0;
	
	ipHeader.source[0] = 192;
	ipHeader.source[1] = 168;
	ipHeader.source[2] = 1;
	ipHeader.source[3] = 1;
	
	unAssignedAdresses[ipHeader.source[3]] = 0;
	
}

/*
 * Check if adress was succesfully assigned
 * */
 bool ipv4::adressAssignment(int sentAdress, int receivedAdress){
	 
	 if(sentAdress == receivedAdress) return true;
	 
	 return false;
	 
}

/*
 * Acknowledge that server and node is synced and ready to exchange data
 * */
 bool ipv4::transmissionSync(int received, int sent){
	
	if(received == sent) return true;
	
	return false;
	
}

/*
 * returns the source adress
 * */
int* ipv4::getSourceAdress(){
	
	return ipHeader.source;
	
}

/*
Attempt to get an adress from the Raspberry Pi
Also set TTL
*/
bool ipv4::setSourceAdress(int* adress){
	
	bool success = false;
	int i;
	
	int* ptrToAdress;
	ptrToAdress = adress;
	i = 0;
	
	while(*ptrToAdress && i < 4){
		
		ipHeader.destination[i++] = *ptrToAdress;
		
		ptrToAdress++;
		
	}
	
	if(!success){
		
		for(int i = 0; i < 4; i++){
			
			if(ipHeader.destination[i] == 0){
				
				this->gotAdress = false;
				return false;
				
			}
			
		}
		
		unAssignedAdresses[ipHeader.destination[3]] = 0;
		
		ipHeader.TTL++;
		
		this->gotAdress = true;
		return true;
		
	}
	
	return false;
	
}

int* ipv4::getTakenAdresses(){
	
	return &unAssignedAdresses[1];
	
}

/*
 * Disconnects the given node and releases the ip adress
 * */
void ipv4::disconnectNode(int adress){
	
	unAssignedAdresses[adress] = adress;
	ipHeader.TTL--;
	
}

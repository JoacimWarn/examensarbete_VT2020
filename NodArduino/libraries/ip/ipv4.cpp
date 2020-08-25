#include "ipv4.h"
#include <time.h>

/*
ipv4 class definition
*/

ipv4::ipv4(){
	
	for(int i = 0; i < 4; i++){
		
		ipHeader.source[i] = 0;
		ipHeader.destination[i] = 0;
		
	}
	
	ipHeader.source[0] = 192;
	ipHeader.source[1] = 168;
	ipHeader.source[2] = 1;
	ipHeader.source[3] = -1;
	//memset(ipHeader.source, 0, 4);
	//memset(ipHeader.destination, 0, 4);
	gotAdress = false;
	ipHeader.TTL = 0;
	isTransmitting = true;
	
}

/*
Checks the server feedback to see if the adress can be assigned
*/
bool ipv4::adressAssignment(int val){
	
	if(val == 888){
		
		//assign the adress
		return true;
		
	}
	
	return false;
	
}

/*
Ser till så att server och nod är synkade med varandra och redo att utbyta data.
*/
bool ipv4::transmissionSync(int received){
	
	if(received == 777) return true;
	
	return false;
	
}

/*
CSMA/CA, lyssnar på kanalen och tittar ifall någon sänder.
Om det inte är någon som sänder, börja skicka.
Om någon sänder, wait ett slumpmässigt intervall på 1 - 3 sekunder, och försök igen.
*/
void ipv4::csmaca(bool listen){
	
	if(listen){
		
		srand(time(NULL));
		
		//slumpmässig väntetid 1 - 3 sekunder
		int randomNumber = (rand() % 3 + 1);
		
		isTransmitting = true;
		
		delay(randomNumber);
		
		return;
		
	}
	
	isTransmitting = false;
	
}

/*
Returns the ip adress
*/
int* ipv4::getSourceAdress(){
	
	return ipHeader.source;
	
}

/*
Disconnects the given node and releases the ip adress
*/
void ipv4::disconnectNode(int adress){
	
	for(int i = 0; i < 4; i++){
		
		ipHeader.source[i] = 0;
		
	}
	
	ipHeader.TTL--;
	
}


/*
Sätt den adress som skickats av Raspberry Pi
*/
void ipv4::setSourceAdress(int adress){
	
	ipHeader.source[3] = adress;
	
	/*
	int i;
	
	int* ptrToAdress;
	ptrToAdress = adress;
	i = 0;
	
	while(*ptrToAdress && i < 4){
		
		ipHeader.source[i++] = *ptrToAdress;
		
		ptrToAdress++;
		
	}
	*/
	
	gotAdress = true;
	
}


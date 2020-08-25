/*
	IPv4 implementation for Arduino and RaspberryPi
	-Source
	-Destination
	-TTL
*/

#ifndef _ipv4_h
#define _ipv4_h

#define NUMBER_OF_ADRESSES 255

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad, FraunchPad and StellarPad specific
    #include "Energia.h"
#elif defined(RPI) // Raspberry Pi
    #define RaspberryPi

    // Include libraries for RPi:
    #include <string.h> /* memcpy */
    #include <stdlib.h> /* abs */
    #include <wiringPi.h>
#elif defined(SPARK)
    #include "application.h"
#else
    //#include "WProgram.h"
#endif


class ipv4{
	
	public:
	
	ipv4();
	
	int unAssignedAdresses[NUMBER_OF_ADRESSES];
	
	bool adressAssignment(int, int);
	bool transmissionSync(int, int);
	int* getSourceAdress();
	bool setSourceAdress(int*);
	int* getTakenAdresses();
	
	void disconnectNode(int);
	
	struct ipv4Header{
		
		int source[4];
		int destination[4];
		int TTL;
		
	};
	
	ipv4Header ipHeader;
	bool gotAdress;
	
};
	

#endif

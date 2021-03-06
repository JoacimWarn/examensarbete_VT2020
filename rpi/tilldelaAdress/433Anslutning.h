/*
  RCSwitch - Arduino libary for remote control outlet switches
  Copyright (c) 2011 Suat Özgür.  All right reserved.

  Contributors:
  - Andre Koehler / info(at)tomate-online(dot)de
  - Gordeev Andrey Vladimirovich / gordeev(at)openpyro(dot)com
  
  Project home: http://code.google.com/p/rc-switch/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _433Anslutning_h
#define _433Anslutning_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include <wiringPi.h>
    #include <stdint.h>
    #define NULL 0
    #define CHANGE 1
#ifdef __cplusplus
extern "C"{
#endif
typedef uint8_t boolean;
typedef uint8_t byte;

#if !defined(NULL)
#endif
#ifdef __cplusplus
}
#endif
#endif


// Number of maximum High/Low changes per packet.
// We can handle up to (unsigned long) => 32 bit * 2 H/L changes per bit + 2 for sync
#define RCSWITCH_MAX_CHANGES 67


class RCSwitch {

  public:
    RCSwitch();
    
    static void handleInterrupt();
    static bool receiveProtocol(const int p, unsigned int changeCount);
    
    static bool receiveProtocol1(unsigned int changeCount);
    static bool receiveProtocol2(unsigned int changeCount);
    
    void switchOn(int, int);
    void switchOn(char* sGroup, int nSwitchNumber);
    void switchOff(char* sGroup, int nSwitchNumber);

    void sendTriState(char* Code);
    void send(unsigned long Code, unsigned int length);
    void send(char* Code);
    
    void enableReceive(int interrupt);
    void enableReceive();
    void disableReceive();
    bool available();
	void resetAvailable();
	
    unsigned long getReceivedValue();
    unsigned int getReceivedBitlength();
    unsigned int getReceivedDelay();
	unsigned int getReceivedProtocol();
    unsigned int* getReceivedRawdata();
  
    void enableTransmit(int nTransmitterPin);
    void disableTransmit();
    void setPulseLength(int nPulseLength);
    void setRepeatTransmit(int nRepeatTransmit);
    void setReceiveTolerance(int nPercent);
	void setProtocol(int nProtocol);
	void setProtocol(int nProtocol, int nPulseLength);
  
      struct HighLow {
        uint8_t high;
        uint8_t low;
    };
  
      struct Protocol {
        /** base pulse length in microseconds, e.g. 350 */
        uint16_t pulseLength;

        HighLow syncFactor;
        HighLow zero;
        HighLow one;

        /**
         * If true, interchange high and low logic levels in all transmissions.
         *
         * By default, RCSwitch assumes that any signals it sends or receives
         * can be broken down into pulses which start with a high signal level,
         * followed by a a low signal level. This is e.g. the case for the
         * popular PT 2260 encoder chip, and thus many switches out there.
         *
         * But some devices do it the other way around, and start with a low
         * signal level, followed by a high signal level, e.g. the HT6P20B. To
         * accommodate this, one can set invertedSignal to true, which causes
         * RCSwitch to change how it interprets any HighLow struct FOO: It will
         * then assume transmissions start with a low signal lasting
         * FOO.high*pulseLength microseconds, followed by a high signal lasting
         * FOO.low*pulseLength microseconds.
         */
        bool invertedSignal;
    };
  
  private:
  Protocol protocol;
  
    const static unsigned int nSeparationLimit;
    char* getCodeWordA(char* sGroup, int nSwitchNumber, boolean bStatus);
    void sendT0();
    void sendT1();
    void sendTF();
    void send0();
    void send1();
    void sendSync();
    void transmit(int nHighPulses, int nLowPulses);

    static char* dec2binWzerofill(unsigned long dec, unsigned int length);
    
    int nReceiverInterrupt;
    int nTransmitterPin;
    int nPulseLength;
    int nRepeatTransmit;
	char nProtocol;

	static int nReceiveTolerance;
    static unsigned long nReceivedValue;
    static unsigned int nReceivedBitlength;
	static unsigned int nReceivedDelay;
	static unsigned int nReceivedProtocol;
    static unsigned int timings[RCSWITCH_MAX_CHANGES];

    
};

#endif

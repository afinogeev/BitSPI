/*
 * 2021, Afinogeev Ruslan
 */


#pragma once
#include <Arduino.h>


class BitSPI{

    private:
        byte _miso;
        byte _mosi;
        byte _sck;
		byte _cpha;
		byte _cpol;
		
		void sendBit(byte value, byte bit, byte cpha = 0, byte cpol = 0);
		int quant;

    public:
        BitSPI(byte mosi, byte miso, byte sck, int speed = 9600, byte cpha = 0, byte cpol = 0);
		void begin();
		void end();
        byte* transfer(byte* data, byte sizeBit = 8, byte startBit = 0, byte cpha = 0, byte cpol = 0);
		void setSpeed(int speed);
};

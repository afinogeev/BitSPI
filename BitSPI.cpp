/*
 * 2021, Afinogeev Ruslan
 */


#include <BitSPI.h>

BitSPI::BitSPI(byte mosi, byte miso, byte sck, int speed = 9600, byte cpha = 0, byte cpol = 0) {
    _mosi = mosi;
    _miso = miso;
    _sck = sck;
	_cpha = cpha;
	_cpol = cpol;
	setSpeed(speed);
} 

void BitSPI::begin() {
    pinMode(_mosi, OUTPUT);
    pinMode(_miso, INPUT);
    pinMode(_sck, OUTPUT);
	digitalWrite(_sck, _cpol ? HIGH : LOW);
}

void BitSPI::end() {
    pinMode(_mosi, INPUT);
    pinMode(_miso, INPUT);
    pinMode(_sck, INPUT);
}

byte* BitSPI::transfer(byte* data, byte sizeBit = 8, byte startBit = 0, byte cpha = 0, byte cpol = 0) {
    byte* out = 0;
	
	byte quantityByte = (sizeBit-1+startBit)/8+1u;
	byte stopBit = quantityByte>1?(sizeBit-1+startBit)%8:(sizeBit-1+startBit);
	byte countBit = 0;
	

    for(byte ibyte = 0; ibyte < quantityByte; ibyte++)
    {
		byte curByte = *(data + ibyte);
		byte shift = ibyte?0:startBit;
		byte stop = ((ibyte+1)==quantityByte)?stopBit:7;
		
		for(byte ibit = shift; ibit<=stop; ibit++)
			sendBit(curByte, ibit, cpha, cpol);
		digitalWrite(_mosi, LOW);
    }
	
    return out;
}

void BitSPI::sendBit(byte value, byte bit, byte cpha = 0, byte cpol = 0) {
	
	if(!cpha)
	{
		digitalWrite(_mosi, bitRead(value, 7-bit));
		delayMicroseconds(quant);
		digitalWrite(_sck, cpol ? LOW : HIGH);
	}
	else
	{
		digitalWrite(_sck, cpol ? LOW : HIGH);
		delayMicroseconds(quant);
		digitalWrite(_mosi, bitRead(value, 7-bit));
	}
	delayMicroseconds(2*quant);
	digitalWrite(_sck, cpol ? HIGH : LOW);
	delayMicroseconds(quant);
}

void BitSPI::setSpeed(int speed) {
	float time = 1./((float)speed);
	time *= 1000000.
	time /= 4;
	if(time > 50)
		quant = (int) time;
	else 
		quant = 50;
	//quant = 500;//int((1./float(speed))*1000000./4.);
}

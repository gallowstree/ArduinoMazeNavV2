#include "Led.h"

Led::Led(int outPin): outPin(outPin) {  pinMode(outPin, OUTPUT); disable(); }

void Led::enable()
{
    digitalWrite(outPin,HIGH);
}

void Led::disable()
{
    digitalWrite(outPin,LOW);
}

void Led::blink(int repeat)
{
	for (int i = 0; i < repeat; i++)
	{
		digitalWrite(outPin, HIGH);
		delay(200);
		digitalWrite(outPin, LOW);
		delay(200);
	}
}
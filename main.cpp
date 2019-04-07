
#include <iostream>
#include "LEDController.h"

int main(int argc, char **argv)
{
	RGB colour = {0,0,0};
	int len = 1;
	int pin = 18;
	for (int i = 1; i < argc; i++)
	{
		std::string arg(argv[i]);
		if (arg=="-l" && i+1<argc)
		{
			len = atoi(argv[i+1]);
		}
		else if (arg=="-p" && i+1<argc)
		{
			pin = atoi(argv[i+1]);
		}
		else
		{
			u32 col = (int)strtol(argv[i], 0, 0);;
			colour.R = (col>>8*2)&0xFF;
			colour.G = (col>>8*1)&0xFF;
			colour.B = (col>>8*0)&0xFF;
		}
	}
	std::cout << std::hex << (int)colour.R << "," << (int)colour.G << "," << (int)colour.B << std::dec << " [" << len << "] on pin " << pin << "\n";
	LEDController leds;
	leds.Init(len, pin);
	leds.DrawColour(colour);
	leds.Destroy();
	return 0;
}

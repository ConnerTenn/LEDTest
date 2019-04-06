
#include "LEDController.h"

bool LEDController::Init(int len, int pin)
{
	{
		memset(&LedDef, 0, sizeof(LedDef));
		LedDef.freq = WS2811_TARGET_FREQ;
		LedDef.dmanum = 10;

		ws2811_channel_t channel;
		memset(&channel, 0, sizeof(channel));
		
		channel.gpionum = pin;
		channel.count = len;
		channel.invert = 0;
		channel.brightness = 255;
		channel.strip_type = WS2811_STRIP_GRB;

		LedDef.channel[0] = channel;
	}
	if((Ret = ws2811_init(&LedDef)) != WS2811_SUCCESS)
	{
		std::cerr << "ws2811_init failed: " << ws2811_get_return_t_str(Ret) << "\n";
			return false;
	}

	return Clear();
}

void LEDController::Destroy()
{
	ws2811_fini(&LedDef);
}

bool LEDController::Clear()
{
	for (int i = 0; i < LedDef.channel[0].count; i++)
	{
		LedDef.channel[0].leds[i] = 0x000000;
	}

	return Render();
}

bool LEDController::Render()
{
	if ((Ret = ws2811_render(&LedDef)) != WS2811_SUCCESS)
	{
		std::cerr << "ws2811_render failed: " << ws2811_get_return_t_str(Ret) << "\n";
		return false;
	}

	return true;
}

bool LEDController::DrawColour(RGB colour)
{
	for (int i = 0; i < LedDef.channel[0].count; i++)
	{
		LedDef.channel[0].leds[i] = RGBToHEX(colour);
	}

	return Render();
}

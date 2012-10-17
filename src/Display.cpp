#include <Display.hpp>
#include <polo.h>

using namespace std;

Display::Display(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
}

void Display::print(void)
{
	clearScreen();
	printGrid(140, 640, 80, 480);
	float Rs, Gs, Bs, Ru, Gu, Bu;
	if(state.getSelectedChannel() != Configuration::CHANNEL_B)
	{
		Rs = 0.2;
		Gs = 0.2;
		Bs = 1.0;
		Ru = 1.0;
		Gu = 0.0;
		Bu = 0.0;
	}
	else
	{
		Rs = 1.0;
		Gs = 0.0;
		Bs = 0.0;
		Ru = 0.2;
		Gu = 0.2;
		Bu = 1.0;
	}
	if(configuration.getChannel(state.getUnselectedChannel()))
	{
		printSamples(samplesToPixels(samples.getSamples(state.getUnselectedChannel()), configuration.getVerticalScale(state.getUnselectedChannel()), 50), samples.getDelay(state.getUnselectedChannel()), Ru, Gu, Bu, 140, 640, 80, 480);
	}
	if(configuration.getChannel(state.getSelectedChannel()))
	{
		printSamples(samplesToPixels(samples.getSamples(state.getSelectedChannel()), configuration.getVerticalScale(state.getSelectedChannel()), 50), samples.getDelay(state.getSelectedChannel()), Rs, Gs, Bs, 140, 640, 80, 480);
	}
	if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
	{
		printOffset(configuration.getOffset(state.getSelectedChannel()) / configuration.getVerticalScale(state.getSelectedChannel()) * 50, configuration.getOffsetString(state.getSelectedChannel()), Rs, Gs, Bs, 140, 640, 80, 480);
		printVerticalScale(configuration.getVerticalScaleString(state.getSelectedChannel()), Rs, Gs, Bs, 140, 640, 80, 480);
	}
	printHorizontalScale(configuration.getHorizontalScaleString(), 140, 640, 80, 480);
	printDelay(configuration.getDelay(), configuration.getDelayString(), 140, 640, 80, 480);
	printChannelButton("Channel A", configuration.getChannel(Configuration::CHANNEL_A), state.getSelectedChannel() == Configuration::CHANNEL_A, 0.2, 0.2, 1.0, 0, 140, 330, 380);
	printChannelButton("Channel B", configuration.getChannel(Configuration::CHANNEL_B), state.getSelectedChannel() == Configuration::CHANNEL_B, 1.0, 0.0, 0.0, 0, 140, 180, 230);
	printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_A), state.getSelectedChannel() == Configuration::CHANNEL_A, 0.2, 0.2, 1.0, 20, 120, 290, 330);
	printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_B), state.getSelectedChannel() == Configuration::CHANNEL_B, 1.0, 0.0, 0.0, 20, 120, 140, 180);
	printButton("Meassures", configuration.getMeassureString(state.getSelectedChannel()), state.getMeassuresButtonActive(), 0, 213, 0, 80);
	printButton("Mathematics", configuration.getMathematicString(), state.getMathematicsButtonActive(), 213, 427, 0, 80);
	printButton("Mode", configuration.getModeString(), state.getModeButtonActive(), 427, 640, 0, 80);
	updateScreen();
}

vector<int> Display::samplesToPixels(const vector<double>& samples, double verticalScale, int pixelsPerDivision)
{
	vector<int> pixels(samples.size(), 0);
	for(int i = 0; i < samples.size(); i++)
	{
		pixels[i] = (int) (samples[i] * pixelsPerDivision / verticalScale);
	}
	return pixels;
}

void Display::printGrid(int x1, int x2, int y1, int y2)
{
	setPenColor(getColorFromRGB(0.2, 0.2, 0.2));
	for(int x = x1; x <= x2; x+=((x2 - x1) / 10))
	{
		drawLine(x, y1, x, y2);
	}
	for(int y = y1; y <= y2; y+=((y2 - y1) / 8))
	{
		drawLine(x1, y, x2, y);
	}
}

void Display::printOffset(int offsetValue, string offsetString, float R, float G, float B, int x1, int x2, int y1, int y2)
{
	setTextFont(POLO_HELVETICA_12);
	setPenColor(getColorFromRGB(R, G, B));
	drawText(x1 + 5, (y1 + y2) / 2 + offsetValue, offsetString.data());
}

void Display::printVerticalScale(string verticalScale, float R, float G, float B, int x1, int x2, int y1, int y2)
{
	setTextFont(POLO_HELVETICA_12);
	setPenColor(getColorFromRGB(R, G, B));
	drawText(x2 - getTextDrawWidth(verticalScale.data()) - 5, (y1 + y2) / 2, verticalScale.data());
}

void Display::printDelay(int delayValue, std::string delayString, int x1, int x2, int y1, int y2)
{
	setTextFont(POLO_HELVETICA_12);
	setPenColor(getColorFromRGB(0.5, 0.5, 0.5));
	drawText((x1 + x2) / 2 + delayValue, y1 + 5, delayString.data());
}

void Display::printHorizontalScale(string horizontalScale, int x1, int x2, int y1, int y2)
{
	setTextFont(POLO_HELVETICA_12);
	setPenColor(getColorFromRGB(0.5, 0.5, 0.5));
	drawText((x1 + x2) / 2 + 5, y2 - getTextDrawHeight(horizontalScale.data()) - 5, horizontalScale.data());
}

void Display::printChannelButton(string channel, bool isActive, bool isSelected, float R, float G, float B, int x1, int x2, int y1, int y2)
{
	setPenColor(getColorFromRGB(R, G, B));
	if(isSelected)
	{
		setFillColor(getColorFromRGB(R / 4, G / 4, B / 4));
	}
	else
	{
		setFillColor(getColorFromRGB(R / 16, G / 16, B / 16));
	}
	drawRect(x1, y1, x2 - x1, y2 - y1);
	if(isActive)
	{
		setFillColor(getColorFromRGB(R, G, B));
	}
	else
	{
		setFillColor(getColorFromRGB(R / 16, G / 16, B / 16));
	}
	drawRect(x1 + (y2 - y1) / 4 , (3 * y1 + y2) / 4, (y2 - y1) / 2, (y2 - y1) / 2);
	setTextFont(POLO_HELVETICA_18);
	drawText(x1 + (y2 - y1), (y1 + y2 - getTextDrawHeight(channel.data())) / 2, channel.data());
}

void Display::printCouplingButton(string text, bool isSelected, float R, float G, float B, int x1, int x2, int y1, int y2)
{
	setPenColor(getColorFromRGB(R, G, B));
	if(isSelected)
	{
		setFillColor(getColorFromRGB(R / 4, G / 4, B / 4));
	}
	else
	{
		setFillColor(getColorFromRGB(R / 16, G / 16, B / 16));
	}
	drawRect(x1, y1, x2 - x1, y2 - y1);
	setTextFont(POLO_HELVETICA_12);
	drawText((x1 + x2 - getTextDrawWidth("Coupling")) / 2, (y1 + 2 * y2) / 3 - getTextDrawHeight("Coupling") / 2, "Coupling");
	setTextFont(POLO_HELVETICA_10);
	drawText((x1 + x2 - getTextDrawWidth(text.data())) / 2, (2 * y1 + y2) / 3 - getTextDrawHeight(text.data()) / 2, text.data());
}

void Display::printButton(string title, string text, bool isActive, int x1, int x2, int y1, int y2)
{
	setPenColor(getColorFromRGB(0.5, 0.5, 0.5));
	if(isActive)
	{
		setFillColor(getColorFromRGB(0.2, 0.2, 0.2));
	}
	else
	{
		setFillColor(getColorFromRGB(0.1, 0.1, 0.1));
	}
	drawRect(x1, y1, x2 - x1, y2 - y1);
	setTextFont(POLO_HELVETICA_18);
	drawText((x1 + x2 - getTextDrawWidth(title.data())) / 2, (y1 + 2 * y2) / 3 - getTextDrawHeight(title.data()) / 2, title.data());
	setTextFont(POLO_HELVETICA_10);
	drawText((x1 + x2 - getTextDrawWidth(text.data())) / 2, (2 * y1 + y2) / 3 - getTextDrawHeight(text.data()) / 2, text.data());
}

void Display::printSamples(std::vector<int> samples, int delay, float R, float G, float B, int x1, int x2, int y1, int y2)
{
	setPenColor(getColorFromRGB(R, G, B));
	for(int i = delay; i < (delay + x2 - x1); i++)
	{
		int ya = (y1 + y2) / 2 + samples[i];
		int yb = (y1 + y2) / 2 + samples[i + 1];
		if(ya < y1)
		{
			ya = y1;
		}
		else if(ya > y2)
		{
			ya = y2;
		}
		if(yb < y1)
		{
			yb = y1;
		}
		else if(yb > y2)
		{
			yb = y2;
		}
		drawLine(x1 + i - delay, ya, x1 + i - delay + 1, yb);
	}
}


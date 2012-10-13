#include <Display.hpp>
#include <polo.h>

using namespace std;

Display::Display(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
}

void Display::print(void)
{
	this->printGrid(140, 640, 80, 480);
	switch(this->state.getSelectedChannel())
	{
		case State::CHANNEL_A:
			if(this->configuration.getChannelB())
			{
				this->printSamples(this->samples.getSamplesB(), this->samples.getDelayB(), 1.0, 0.0, 0.0, 140, 640, 80, 480);
			}
			if(this->configuration.getChannelA())
			{
				this->printSamples(this->samples.getSamplesA(), this->samples.getDelayA(), 0.2, 0.2, 1.0, 140, 640, 80, 480);
			}
			this->printOffset(this->configuration.getOffsetA() / this->configuration.getVerticalScale(Configuration::CHANNEL_A) * 50, this->configuration.getOffsetString(Configuration::CHANNEL_A), 0.2, 0.2, 1.0, 140, 640, 80, 480);
			this->printVerticalScale(this->configuration.getVerticalScaleString(Configuration::CHANNEL_A), 0.2, 0.2, 1.0, 140, 640, 80, 480);
			break;
		case State::CHANNEL_B:
			if(this->configuration.getChannelA())
			{
				this->printSamples(this->samples.getSamplesA(), this->samples.getDelayA(), 0.2, 0.2, 1.0, 140, 640, 80, 480);
			}
			if(this->configuration.getChannelB())
			{
				this->printSamples(this->samples.getSamplesB(), this->samples.getDelayB(), 1.0, 0.0, 0.0, 140, 640, 80, 480);
			}
			this->printOffset(this->configuration.getOffsetB() / this->configuration.getVerticalScale(Configuration::CHANNEL_B) * 50 , this->configuration.getOffsetString(Configuration::CHANNEL_B), 1.0, 0.0, 0.0, 140, 640, 80, 480);
			this->printVerticalScale(this->configuration.getVerticalScaleString(Configuration::CHANNEL_B), 1.0, 0.0, 0.0, 140, 640, 80, 480);
			break;
		case State::NO_CHANNEL:
			if(this->configuration.getChannelB())
			{
				this->printSamples(this->samples.getSamplesB(), this->samples.getDelayB(), 1.0, 0.0, 0.0, 140, 640, 80, 480);
			}
			if(this->configuration.getChannelA())
			{
				this->printSamples(this->samples.getSamplesA(), this->samples.getDelayA(), 0.2, 0.2, 1.0, 140, 640, 80, 480);
			}
			break;
	}
	this->printHorizontalScale(this->configuration.getHorizontalScaleString(), 140, 640, 80, 480);
	this->printDelay(this->configuration.getDelay(), this->configuration.getDelayString(50), 140, 640, 80, 480);
	this->printChannelButton("Channel A", this->configuration.getChannelA(), this->state.getSelectedChannel() == State::CHANNEL_A, 0.2, 0.2, 1.0, 0, 140, 330, 380);
	this->printChannelButton("Channel B", this->configuration.getChannelB(), this->state.getSelectedChannel() == State::CHANNEL_B, 1.0, 0.0, 0.0, 0, 140, 180, 230);
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
	drawText(x2 - 45, (y1 + y2) / 2, verticalScale.data());
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
	drawText((x1 + x2) / 2 + 5, y2 - 25, horizontalScale.data());
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
		setFillColor(getColorFromRGB(0.2, 0.2, 0.2));
	}
	drawRect(x1, y1, x2 - x1, y2 - y1);
	if(isActive)
	{
		setFillColor(getColorFromRGB(R, G, B));
	}
	else
	{
		setFillColor(getColorFromRGB(0.5, 0.5, 0.5));
	}
	drawCircle(x1 + (y2 - y1) / 2, (y1 + y2) / 2, 10);
	setTextFont(POLO_HELVETICA_18);
	setPenColor(getColorFromRGB(R, G, B));
	drawText(x1 + (y2 - y1), (y1 + y2) / 2 - 10, channel.data());
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


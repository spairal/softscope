#include <Display.hpp>
#include <polo.h>

using namespace std;

Display::Display(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
}

void Display::print(void)
{
	clearScreen();
	printGrid(state.getGridCoordenates());
	if(configuration.getChannel(state.getUnselectedChannel()))
	{
		printSamples(samplesToPixels(samples.getSamples(state.getUnselectedChannel()), configuration.getVerticalScale(state.getUnselectedChannel()), state.getPixelsPerDivision()), samples.getDelay(state.getUnselectedChannel()), state.getColor(state.getUnselectedChannel()), state.getGridCoordenates());
	}
	if(configuration.getChannel(state.getSelectedChannel()))
	{
		printSamples(samplesToPixels(samples.getSamples(state.getSelectedChannel()), configuration.getVerticalScale(state.getSelectedChannel()), state.getPixelsPerDivision()), samples.getDelay(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
	}
	if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
	{
		printOffset(configuration.getOffset(state.getSelectedChannel()) / configuration.getVerticalScale(state.getSelectedChannel()) * state.getPixelsPerDivision(), configuration.getOffsetString(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
		printVerticalScale(configuration.getVerticalScaleString(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
	}
	printHorizontalScale(configuration.getHorizontalScaleString(), state.getGridCoordenates());
	printDelay(configuration.getDelay(), configuration.getDelayString(), state.getGridCoordenates());
	printChannelButton("Channel A", configuration.getChannel(Configuration::CHANNEL_A), state.getSelectedChannel() == Configuration::CHANNEL_A, state.getColor(Configuration::CHANNEL_A), state.getChannelCoordenates(Configuration::CHANNEL_A));
	printChannelButton("Channel B", configuration.getChannel(Configuration::CHANNEL_B), state.getSelectedChannel() == Configuration::CHANNEL_B, state.getColor(Configuration::CHANNEL_B), state.getChannelCoordenates(Configuration::CHANNEL_B));
	printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_A), state.getColor(Configuration::CHANNEL_A), state.getCouplingCoordenates(Configuration::CHANNEL_A));
	printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_B), state.getColor(Configuration::CHANNEL_B), state.getCouplingCoordenates(Configuration::CHANNEL_B));
	printButton("Measures", configuration.getMeasureString(state.getSelectedChannel()), state.getMeasuresButtonActive(), state.getMeasuresCoordenates());
	printButton("Mathematics", configuration.getMathematicString(), state.getMathematicsButtonActive(), state.getMathematicsCoordenates());
	printButton("Mode", configuration.getModeString(), state.getModeButtonActive(), state.getModeCoordenates());
	if(state.getMeasuresButtonActive())
	{
		printMenu(configuration.getAllMeasures(), state.getMeasuresMenuCoordenates());
	}
	if(state.getMathematicsButtonActive())
	{
		printMenu(configuration.getAllMathematics(), state.getMathematicsMenuCoordenates());
	}
	if(state.getModeButtonActive())
	{
		printMenu(configuration.getAllModes(), state.getModeMenuCoordenates());
	}
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

void Display::printGrid(vector<int> coordenates)
{
	setPenColor(getColorFromRGB(0.2, 0.2, 0.2));
	for(int x = coordenates[0]; x <= coordenates[1]; x+=((coordenates[1] - coordenates[0]) / 10))
	{
		drawLine(x, coordenates[2], x, coordenates[3]);
	}
	for(int y = coordenates[2]; y <= coordenates[3]; y+=((coordenates[3] - coordenates[2]) / 8))
	{
		drawLine(coordenates[0], y, coordenates[1], y);
	}
}

void Display::printOffset(int offsetValue, string offsetString, vector<float> color, vector<int> coordenates)
{
	setTextFont(POLO_HELVETICA_12);
	setPenColor(getColorFromRGB(color[0], color[1], color[2]));
	drawText(coordenates[0] + 5, (coordenates[2] + coordenates[3]) / 2 + offsetValue, offsetString.data());
}

void Display::printVerticalScale(string verticalScale, vector<float> color, vector<int> coordenates)
{
	setTextFont(POLO_HELVETICA_12);
	setPenColor(getColorFromRGB(color[0], color[1], color[2]));
	drawText(coordenates[1] - getTextDrawWidth(verticalScale.data()) - 5, (coordenates[2] + coordenates[3]) / 2, verticalScale.data());
}

void Display::printDelay(int delayValue, std::string delayString, vector<int> coordenates)
{
	setTextFont(POLO_HELVETICA_12);
	setPenColor(getColorFromRGB(0.5, 0.5, 0.5));
	drawText((coordenates[0] + coordenates[1]) / 2 + delayValue, coordenates[2] + 5, delayString.data());
}

void Display::printHorizontalScale(string horizontalScale, vector<int> coordenates)
{
	setTextFont(POLO_HELVETICA_12);
	setPenColor(getColorFromRGB(0.5, 0.5, 0.5));
	drawText((coordenates[0] + coordenates[1]) / 2 + 5, coordenates[3] - getTextDrawHeight(horizontalScale.data()) - 5, horizontalScale.data());
}

void Display::printChannelButton(string channel, bool isActive, bool isSelected, vector<float> color, vector<int> coordenates)
{
	setPenColor(getColorFromRGB(color[0], color[1], color[2]));
	if(isSelected)
	{
		setFillColor(getColorFromRGB(color[0] / 4, color[1] / 4, color[2] / 4));
	}
	else
	{
		setFillColor(getColorFromRGB(color[0] / 16, color[1] / 16, color[2] / 16));
	}
	drawRect(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], coordenates[3] - coordenates[2]);
	if(isActive)
	{
		setFillColor(getColorFromRGB(color[0], color[1], color[2]));
	}
	else
	{
		setFillColor(getColorFromRGB(color[0] / 16, color[1] / 16, color[2] / 16));
	}
	drawRect(coordenates[0] + (coordenates[3] - coordenates[2]) / 4 , (3 * coordenates[2] + coordenates[3]) / 4, (coordenates[3] - coordenates[2]) / 2, (coordenates[3] - coordenates[2]) / 2);
	setTextFont(POLO_HELVETICA_18);
	drawText(coordenates[0] + (coordenates[3] - coordenates[2]), (coordenates[2] + coordenates[3] - getTextDrawHeight(channel.data())) / 2, channel.data());
}

void Display::printCouplingButton(string text, vector<float> color, vector<int> coordenates)
{
	setPenColor(getColorFromRGB(color[0], color[1], color[2]));
	setFillColor(getColorFromRGB(color[0] / 16, color[1] / 16, color[2] / 16));
	drawRect(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], coordenates[3] - coordenates[2]);
	setTextFont(POLO_HELVETICA_12);
	drawText((coordenates[0] + coordenates[1] - getTextDrawWidth("Coupling")) / 2, (coordenates[2] + 2 * coordenates[3]) / 3 - getTextDrawHeight("Coupling") / 2, "Coupling");
	setTextFont(POLO_HELVETICA_10);
	drawText((coordenates[0] + coordenates[1] - getTextDrawWidth(text.data())) / 2, (2 * coordenates[2] + coordenates[3]) / 3 - getTextDrawHeight(text.data()) / 2, text.data());
}

void Display::printButton(string title, string text, bool isActive, vector<int> coordenates)
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
	drawRect(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], coordenates[3] - coordenates[2]);
	setTextFont(POLO_HELVETICA_18);
	drawText((coordenates[0] + coordenates[1] - getTextDrawWidth(title.data())) / 2, (coordenates[2] + 2 * coordenates[3]) / 3 - getTextDrawHeight(title.data()) / 2, title.data());
	setTextFont(POLO_HELVETICA_10);
	drawText((coordenates[0] + coordenates[1] - getTextDrawWidth(text.data())) / 2, (2 * coordenates[2] + coordenates[3]) / 3 - getTextDrawHeight(text.data()) / 2, text.data());
}

void Display::printMenu(vector<string> options, vector<int> coordenates)
{
	setPenColor(getColorFromRGB(0.5, 0.5, 0.5));
	setFillColor(getColorFromRGB(0.1, 0.1, 0.1));
	setTextFont(POLO_HELVETICA_12);
	drawRect(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], (coordenates[3] - coordenates[2]) * options.size());
	for(int i = 0; i < options.size(); i++)
	{
		drawText((coordenates[0] + coordenates[1] - getTextDrawWidth(options[i].data())) / 2, coordenates[2] + (options.size() - i - 0.5) * (coordenates[3] - coordenates[2]) - getTextDrawHeight(options[i].data()) / 2, options[i].data());
	}
}

void Display::printSamples(std::vector<int> samples, int delay, vector<float> color, vector<int> coordenates)
{
	setPenColor(getColorFromRGB(color[0], color[1], color[2]));
	for(int i = delay; i < (delay + coordenates[1] - coordenates[0]); i++)
	{
		int ya = (coordenates[2] + coordenates[3]) / 2 + samples[i];
		int yb = (coordenates[2] + coordenates[3]) / 2 + samples[i + 1];
		if(ya < coordenates[2])
		{
			ya = coordenates[2];
		}
		else if(ya > coordenates[3])
		{
			ya = coordenates[3];
		}
		if(yb < coordenates[2])
		{
			yb = coordenates[2];
		}
		else if(yb > coordenates[3])
		{
			yb = coordenates[3];
		}
		drawLine(coordenates[0] + i - delay, ya, coordenates[0] + i - delay + 1, yb);
	}
}


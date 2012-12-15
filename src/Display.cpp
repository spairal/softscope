#include <Display.hpp>
#include <cmath>

using namespace std;

Display::Display(Configuration& configuration, State& state, Samples& samples, Measurer& measurer, Mathematician& mathematician, MiniFB& miniFB) : configuration(configuration), state(state), samples(samples), measurer(measurer), mathematician(mathematician), miniFB(miniFB)
{
}

void Display::print(void)
{
	printGrid(state.getGridCoordenates());
	if(configuration.getChannel(state.getUnselectedChannel()))
	{
		printSamples(samplesToPixels(samples.getSamples(state.getUnselectedChannel()), configuration.getOffset(state.getUnselectedChannel()), configuration.getVerticalScaleValue(state.getUnselectedChannel()), state.getPixelsPerDivision()), configuration.getMemoryDepth() / 2 - (configuration.getDelay() + 5) * state.getPixelsPerDivision(), configuration.getMemoryDepth(), configuration.getStep(), state.getColor(state.getUnselectedChannel()), state.getGridCoordenates());
	}
	if(configuration.getChannel(state.getSelectedChannel()))
	{
		printSamples(samplesToPixels(samples.getSamples(state.getSelectedChannel()), configuration.getOffset(state.getSelectedChannel()), configuration.getVerticalScaleValue(state.getSelectedChannel()), state.getPixelsPerDivision()), configuration.getMemoryDepth() / 2 - (configuration.getDelay() + 5) * state.getPixelsPerDivision(), configuration.getMemoryDepth(), configuration.getStep(), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
	}
	if(configuration.getMathematic() != Configuration::NOMATHEMATIC)
	{
		printSamples(samplesToPixels(mathematician.getSamples(), 0, configuration.getVerticalScaleValue(state.getSelectedChannel()), state.getPixelsPerDivision()), 0, configuration.getMemoryDepth(), 1, state.getColorMathematics(), state.getGridCoordenates());
	}
	if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
	{
		printOffset(max(min(configuration.getOffset(state.getSelectedChannel()) / configuration.getVerticalScaleValue(state.getSelectedChannel()) * state.getPixelsPerDivision(), 3.5 * state.getPixelsPerDivision()), - 4.0 * state.getPixelsPerDivision()), configuration.getOffsetString(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
		printVerticalScale(configuration.getVerticalScaleString(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
	}
	printHorizontalScale(configuration.getHorizontalScaleString(), state.getGridCoordenates());
	printDelay(max(min(configuration.getDelay() * state.getPixelsPerDivision(), 3.5 * state.getPixelsPerDivision()), -5.0 * state.getPixelsPerDivision()), configuration.getDelayString(), state.getGridCoordenates());
	printChannelButton("Channel A", configuration.getChannel(Configuration::CHANNEL_A), state.getSelectedChannel() == Configuration::CHANNEL_A, state.getColor(Configuration::CHANNEL_A), state.getChannelCoordenates(Configuration::CHANNEL_A));
	printChannelButton("Channel B", configuration.getChannel(Configuration::CHANNEL_B), state.getSelectedChannel() == Configuration::CHANNEL_B, state.getColor(Configuration::CHANNEL_B), state.getChannelCoordenates(Configuration::CHANNEL_B));
	printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_A), state.getColor(Configuration::CHANNEL_A), state.getCouplingCoordenates(Configuration::CHANNEL_A));
	printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_B), state.getColor(Configuration::CHANNEL_B), state.getCouplingCoordenates(Configuration::CHANNEL_B));
	printButton("Measures", measurer.getMeasure(), state.getMeasuresButtonActive(), state.getMeasuresCoordenates());
	printButton("Mathematics", configuration.getMathematicString(), state.getMathematicsButtonActive(), state.getMathematicsCoordenates());
	printButton("Mode", configuration.getModeString(), state.getModeButtonActive(), state.getModeCoordenates());
	if(configuration.getMeasure() == Configuration::CURSORS)
	{
		vector<double> cursor = configuration.getCursor();
		vector<int> gridCoordenates = state.getGridCoordenates();
		vector<int> cursorCoordenates;
		cursorCoordenates.push_back(min(cursor[0], cursor[1]) * state.getPixelsPerDivision() + gridCoordenates[0] + 5 * state.getPixelsPerDivision());
		cursorCoordenates.push_back(max(cursor[0], cursor[1]) * state.getPixelsPerDivision() + gridCoordenates[0] + 5 * state.getPixelsPerDivision());
		cursorCoordenates.push_back(min(cursor[2], cursor[3]) * state.getPixelsPerDivision() + gridCoordenates[2] + 4 * state.getPixelsPerDivision());
		cursorCoordenates.push_back(max(cursor[2], cursor[3]) * state.getPixelsPerDivision() + gridCoordenates[2] + 4 * state.getPixelsPerDivision());
		printCursor(cursorCoordenates);
	}
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
	if(state.getAverageActive())
	{
		printMenu(configuration.getAllAverages(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerModeActive())
	{
		printMenu(configuration.getAllTriggerModes(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerChannelActive())
	{
		printMenu(configuration.getAllChannels(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerSlopeActive())
	{
		printMenu(configuration.getAllTriggerSlopes(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerNoiseRejectActive())
	{
		printMenu(configuration.getAllTriggerNoiseRejects(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerHighFrequencyRejectActive())
	{
		printMenu(configuration.getAllTriggerHighFrequencyRejects(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerLevelActive())
	{
		printAlert("Select the trigger level and hold off", state.getGridCoordenates());
	}
}

vector<int> Display::samplesToPixels(const vector<double>& samples, double offset, double verticalScale, int pixelsPerDivision)
{
	vector<int> pixels(samples.size(), 0);
	for(int i = 0; i < samples.size(); i++)
	{
		pixels[i] = (int) ((samples[i] + offset) * pixelsPerDivision / verticalScale);
	}
	return pixels;
}

void Display::printGrid(vector<int> coordenates)
{
	int color = miniFB.thinColor(state.getColorGeneral(), 1);
	for(int x = coordenates[0]; x <= coordenates[1]; x += ((coordenates[1] - coordenates[0]) / 10))
	{
		miniFB.drawLine(x, coordenates[2], x, coordenates[3], color);
	}
	for(int y = coordenates[2]; y <= coordenates[3]; y += ((coordenates[3] - coordenates[2]) / 8))
	{
		miniFB.drawLine(coordenates[0], y, coordenates[1], y, color);
	}
}

void Display::printOffset(int offsetValue, string offsetString, int color, vector<int> coordenates)
{
	miniFB.drawText(coordenates[0] + 5, (coordenates[2] + coordenates[3]) / 2 + offsetValue, offsetString, color, MiniFB::MEDIUM);
}

void Display::printVerticalScale(string verticalScale, int color, vector<int> coordenates)
{
	miniFB.drawText(coordenates[1] - miniFB.getTextWidth(verticalScale, MiniFB::MEDIUM) - 5, (coordenates[2] + coordenates[3]) / 2, verticalScale, color, MiniFB::MEDIUM);
}

void Display::printDelay(int delayValue, std::string delayString, vector<int> coordenates)
{
	miniFB.drawText((coordenates[0] + coordenates[1]) / 2 + delayValue, coordenates[2] + 5, delayString, state.getColorGeneral(), MiniFB::MEDIUM);
}

void Display::printHorizontalScale(string horizontalScale, vector<int> coordenates)
{
	miniFB.drawText((coordenates[0] + coordenates[1]) / 2 + 5, coordenates[3] - miniFB.getTextHeight(horizontalScale, MiniFB::MEDIUM) - 5, horizontalScale, state.getColorGeneral(), MiniFB::MEDIUM);
}

void Display::printChannelButton(string channel, bool isActive, bool isSelected, int color, vector<int> coordenates)
{
	int fillColor;
	if(isSelected)
	{
		fillColor = miniFB.thinColor(color, 2);
	}
	else
	{
		fillColor = miniFB.thinColor(color, 4);
	}
	miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], coordenates[3] - coordenates[2], fillColor, color);
	if(isActive)
	{
		fillColor = color;
	}
	else
	{
		fillColor = miniFB.thinColor(color, 4);
	}
	miniFB.drawRectangle(coordenates[0] + (coordenates[3] - coordenates[2]) / 4 , (3 * coordenates[2] + coordenates[3]) / 4, (coordenates[3] - coordenates[2]) / 2, (coordenates[3] - coordenates[2]) / 2, fillColor, color);
	miniFB.drawText(coordenates[0] + (coordenates[3] - coordenates[2]), (coordenates[2] + coordenates[3] - miniFB.getTextHeight(channel, MiniFB::LARGE)) / 2, channel, color, MiniFB::LARGE);
}

void Display::printCouplingButton(string text, int color, vector<int> coordenates)
{
	miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], coordenates[3] - coordenates[2], miniFB.thinColor(color, 4), color);
	miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth("Coupling", MiniFB::MEDIUM)) / 2, (coordenates[2] + 2 * coordenates[3]) / 3 - miniFB.getTextHeight("Coupling", MiniFB::MEDIUM) / 2, "Coupling", color, MiniFB::MEDIUM);
	miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(text, MiniFB::SMALL)) / 2, (2 * coordenates[2] + coordenates[3]) / 3 - miniFB.getTextHeight(text, MiniFB::SMALL) / 2, text, color, MiniFB::SMALL);
}

void Display::printButton(string title, string text, bool isActive, vector<int> coordenates)
{
	int color = state.getColorGeneral();
	int fillColor;
	if(isActive)
	{
		fillColor = miniFB.thinColor(color, 1);
	}
	else
	{
		fillColor = miniFB.thinColor(color, 2);
	}
	miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], coordenates[3] - coordenates[2], fillColor, color);
	miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(title, MiniFB::LARGE)) / 2, (coordenates[2] + 6 * coordenates[3]) / 7 - miniFB.getTextHeight(title, MiniFB::LARGE) / 2, title, color, MiniFB::LARGE);
	miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(text, MiniFB::SMALL)) / 2, (4 * coordenates[2] + 3 * coordenates[3]) / 7 - miniFB.getTextHeight(text, MiniFB::SMALL) / 2, text, color, MiniFB::SMALL);
}

void Display::printMenu(vector<string> options, vector<int> coordenates)
{
	int color = state.getColorGeneral();
	miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], (coordenates[3] - coordenates[2]) * options.size(), miniFB.thinColor(color, 2), color);
	for(int i = 0; i < options.size(); i++)
	{
		miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(options[i], MiniFB::MEDIUM)) / 2, coordenates[2] + (options.size() - i - 0.5) * (coordenates[3] - coordenates[2]) - miniFB.getTextHeight(options[i], MiniFB::MEDIUM) / 2, options[i], color, MiniFB::MEDIUM);
	}
}

void Display::printAlert(string text, vector<int> coordenates)
{
	miniFB.drawText(coordenates[0] + state.getPixelsPerDivision(), coordenates[3] - state.getPixelsPerDivision(), text, state.getColorGeneral(), MiniFB::MEDIUM);
}

void Display::printSamples(std::vector<int> samples, int delay, int memoryDepth, double step, int color, vector<int> coordenates)
{
	int upStep = max(1.0, round(step));
	int start = (delay - memoryDepth / 2) * step + memoryDepth / 2;
	for(int i = max(start, 0); i < min((int) (start + round((coordenates[1] - coordenates[0]) * step)), memoryDepth - upStep); i += upStep)
	{
		int ya = (coordenates[2] + coordenates[3]) / 2 + samples[i];
		int yb = (coordenates[2] + coordenates[3]) / 2 + samples[i + upStep];
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
		miniFB.drawLine(round(coordenates[0] + (i - start) / step), ya, round(coordenates[0] + (i - start + upStep) / step), yb, color);
	}
}

void Display::printCursor(vector<int> coordenates)
{
	miniFB.drawRectangleBorder(coordenates[0], coordenates[2], coordenates[1] - coordenates[0], coordenates[3] - coordenates[2], state.getColorGeneral());
}


#include <State.hpp>

using namespace std;

State::State(void)
{
	gridCoordenates.push_back(140);
	gridCoordenates.push_back(640);
	gridCoordenates.push_back(80);
	gridCoordenates.push_back(480);
	channelCoordenatesA.push_back(0);
	channelCoordenatesA.push_back(140);
	channelCoordenatesA.push_back(330);
	channelCoordenatesA.push_back(380);
	channelCoordenatesB.push_back(0);
	channelCoordenatesB.push_back(140);
	channelCoordenatesB.push_back(180);
	channelCoordenatesB.push_back(230);
	couplingCoordenatesA.push_back(20);
	couplingCoordenatesA.push_back(120);
	couplingCoordenatesA.push_back(290);
	couplingCoordenatesA.push_back(330);
	couplingCoordenatesB.push_back(20);
	couplingCoordenatesB.push_back(120);
	couplingCoordenatesB.push_back(140);
	couplingCoordenatesB.push_back(180);
	measuresCoordenates.push_back(0);
	measuresCoordenates.push_back(213);
	measuresCoordenates.push_back(0);
	measuresCoordenates.push_back(80);
	measuresMenuCoordenates.push_back(0);
	measuresMenuCoordenates.push_back(213);
	measuresMenuCoordenates.push_back(80);
	measuresMenuCoordenates.push_back(110);
	mathematicsCoordenates.push_back(213);
	mathematicsCoordenates.push_back(427);
	mathematicsCoordenates.push_back(0);
	mathematicsCoordenates.push_back(80);
	mathematicsMenuCoordenates.push_back(213);
	mathematicsMenuCoordenates.push_back(427);
	mathematicsMenuCoordenates.push_back(80);
	mathematicsMenuCoordenates.push_back(110);
	modeCoordenates.push_back(427);
	modeCoordenates.push_back(640);
	modeCoordenates.push_back(0);
	modeCoordenates.push_back(80);
	modeMenuCoordenates.push_back(427);
	modeMenuCoordenates.push_back(640);
	modeMenuCoordenates.push_back(80);
	modeMenuCoordenates.push_back(110);
	colorA.push_back(0.2);
	colorA.push_back(0.2);
	colorA.push_back(1.0);
	colorB.push_back(1.0);
	colorB.push_back(0.0);
	colorB.push_back(0.0);
	colorMathematics.push_back(1.0);
	colorMathematics.push_back(1.0);
	colorMathematics.push_back(0.0);
	cursorDrag = false;
	offsetDrag = false;
	verticalScaleDrag = false;
	horizontalScaleDrag = false;
	triggerLevelDrag = false;
	initialOffset.push_back(0);
	initialOffset.push_back(0);
	initialVerticalScale = 0;
	initialHorizontalScale = 0;
	selectedChannel = Configuration::NO_CHANNEL;
	measuresButtonActive = false;
	mathematicsButtonActive = false;
	modeButtonActive = false;
	triggerModeActive = false;
	triggerChannelActive = false;
	triggerSlopeActive = false;
	triggerNoiseRejectActive = false;
	triggerHighFrequencyRejectActive = false;
	triggerLevelActive = false;
	averageActive = false;
}

vector<int> State::getGridCoordenates(void)
{
	return gridCoordenates;
}

int State::getPixelsPerDivision(void)
{
	return (gridCoordenates[1] - gridCoordenates[0]) / 10;
}

vector<int> State::getChannelCoordenates(Configuration::Channels channel)
{
	vector<int> channelCoordenates;
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			channelCoordenates = channelCoordenatesA;
			break;
		case Configuration::CHANNEL_B:
			channelCoordenates = channelCoordenatesB;
			break;
	}
	return channelCoordenates;
}

vector<int> State::getCouplingCoordenates(Configuration::Channels channel)
{
	vector<int> couplingCoordenates;
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			couplingCoordenates = couplingCoordenatesA;
			break;
		case Configuration::CHANNEL_B:
			couplingCoordenates = couplingCoordenatesB;
			break;
	}
	return couplingCoordenates;
}

vector<int> State::getMeasuresCoordenates(void)
{
	return measuresCoordenates;
}

vector<int> State::getMathematicsCoordenates(void)
{
	return mathematicsCoordenates;
}

vector<int> State::getModeCoordenates(void)
{
	return modeCoordenates;
}

vector<int> State::getMeasuresMenuCoordenates(void)
{
	return measuresMenuCoordenates;
}

vector<int> State::getMathematicsMenuCoordenates(void)
{
	return mathematicsMenuCoordenates;
}

vector<int> State::getModeMenuCoordenates(void)
{
	return modeMenuCoordenates;
}

vector<float> State::getColor(Configuration::Channels channel)
{
	vector<float> color;
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			color = colorA;
			break;
		case Configuration::CHANNEL_B:
			color = colorB;
			break;
	}
	return color;
}

vector<float> State::getColorMathematics(void)
{
	return colorMathematics;
}

bool State::getCursorDrag(void)
{
	return cursorDrag;
}

bool State::getOffsetDrag(void)
{
	return offsetDrag;
}

bool State::getVerticalScaleDrag(void)
{
	return verticalScaleDrag;
}

bool State::getHorizontalScaleDrag(void)
{
	return horizontalScaleDrag;
}

bool State::getTriggerLevelDrag(void)
{
	return triggerLevelDrag;
}

void State::setCursorDrag(bool drag)
{
	cursorDrag = drag;
}

void State::setOffsetDrag(bool drag)
{
	offsetDrag = drag;
}

void State::setVerticalScaleDrag(bool drag)
{
	verticalScaleDrag = drag;
}

void State::setHorizontalScaleDrag(bool drag)
{
	horizontalScaleDrag = drag;
}

void State::setTriggerLevelDrag(bool drag)
{
	triggerLevelDrag = drag;
}

vector<int> State::getInitialOffset(void)
{
	return initialOffset;
}

int State::getInitialVerticalScale(void)
{
	return initialVerticalScale;
}

int State::getInitialHorizontalScale(void)
{
	return initialHorizontalScale;
}

void State::setInitialOffset(vector<int> offset)
{
	initialOffset = offset;
}

void State::setInitialVerticalScale(int scale)
{
	initialVerticalScale = scale;
}

void State::setInitialHorizontalScale(int scale)
{
	initialHorizontalScale = scale;
}

Configuration::Channels State::getSelectedChannel(void)
{
	return selectedChannel;
}

Configuration::Channels State::getUnselectedChannel(void)
{
	Configuration::Channels channel;
	switch(selectedChannel)
	{
		case Configuration::CHANNEL_A:
			channel = Configuration::CHANNEL_B;
			break;
		case Configuration::CHANNEL_B:
			channel = Configuration::CHANNEL_A;
			break;
		case Configuration::NO_CHANNEL:
			channel = Configuration::NO_CHANNEL;
			break;
	}
	return channel;
}

void State::setSelectedChannel(Configuration::Channels channel)
{
	selectedChannel = channel;
}

bool State::getMeasuresButtonActive(void)
{
	return measuresButtonActive;
}

bool State::getMathematicsButtonActive(void)
{
	return mathematicsButtonActive;
}

bool State::getModeButtonActive(void)
{
	return modeButtonActive;
}

bool State::getTriggerModeActive(void)
{
	return triggerModeActive;
}

bool State::getTriggerChannelActive(void)
{
	return triggerChannelActive;
}

bool State::getTriggerSlopeActive(void)
{
	return triggerSlopeActive;
}

bool State::getTriggerNoiseRejectActive(void)
{
	return triggerNoiseRejectActive;
}

bool State::getTriggerHighFrequencyRejectActive(void)
{
	return triggerHighFrequencyRejectActive;
}

bool State::getTriggerLevelActive(void)
{
	return triggerLevelActive;
}

bool State::getAverageActive(void)
{
	return averageActive;
}

void State::setMeasuresButtonActive(bool active)
{
	measuresButtonActive = active;
}

void State::setMathematicsButtonActive(bool active)
{
	mathematicsButtonActive = active;
}

void State::setModeButtonActive(bool active)
{
	modeButtonActive = active;
}

void State::setTriggerModeActive(bool active)
{
	triggerModeActive = active;
}

void State::setTriggerChannelActive(bool active)
{
	triggerChannelActive = active;
}

void State::setTriggerSlopeActive(bool active)
{
	triggerSlopeActive = active;
}

void State::setTriggerNoiseRejectActive(bool active)
{
	triggerNoiseRejectActive = active;
}

void State::setTriggerHighFrequencyRejectActive(bool active)
{
	triggerHighFrequencyRejectActive = active;
}

void State::setTriggerLevelActive(bool active)
{
	triggerLevelActive = active;
}

void State::setAverageActive(bool active)
{
	averageActive = active;
}


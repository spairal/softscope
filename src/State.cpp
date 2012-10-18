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
	mathematicsCoordenates.push_back(213);
	mathematicsCoordenates.push_back(427);
	mathematicsCoordenates.push_back(0);
	mathematicsCoordenates.push_back(80);
	modeCoordenates.push_back(427);
	modeCoordenates.push_back(640);
	modeCoordenates.push_back(0);
	modeCoordenates.push_back(80);
	colorA.push_back(0.2);
	colorA.push_back(0.2);
	colorA.push_back(1.0);
	colorB.push_back(1.0);
	colorB.push_back(0.0);
	colorB.push_back(0.0);
	selectedChannel = Configuration::NO_CHANNEL;
	measuresButtonActive = false;
	mathematicsButtonActive = false;
	modeButtonActive = false;
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


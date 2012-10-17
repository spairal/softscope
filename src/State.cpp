#include <State.hpp>

State::State(void)
{
	selectedChannel = Configuration::CHANNEL_A;
	meassuresButtonActive = false;
	mathematicsButtonActive = false;
	modeButtonActive = false;
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

bool State::getMeassuresButtonActive(void)
{
	return meassuresButtonActive;
}

bool State::getMathematicsButtonActive(void)
{
	return mathematicsButtonActive;
}

bool State::getModeButtonActive(void)
{
	return modeButtonActive;
}


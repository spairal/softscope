#include <Touch.hpp>

using namespace std;

Touch::Touch(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
	buttonPressed = false;
}

void Touch::setButtonPressed(bool pressed)
{
	buttonPressed = pressed;
}

void Touch::parseScreen(int x, int y)
{
	if(buttonPressed)
	{
		buttonPressed = false;
		if(isIn(x, y, state.getChannelCoordenates(Configuration::CHANNEL_A)))
		{
			pressChannelButton(Configuration::CHANNEL_A);
		}
		if(isIn(x, y, state.getChannelCoordenates(Configuration::CHANNEL_B)))
		{
			pressChannelButton(Configuration::CHANNEL_B);
		}
		if(isIn(x, y, state.getCouplingCoordenates(Configuration::CHANNEL_A)))
		{
			pressCouplingButton(Configuration::CHANNEL_A);
		}
		if(isIn(x, y, state.getCouplingCoordenates(Configuration::CHANNEL_B)))
		{
			pressCouplingButton(Configuration::CHANNEL_B);
		}
	}
}

void Touch::pressChannelButton(Configuration::Channels channel)
{
	if(configuration.getChannel(channel))
	{
		if(state.getSelectedChannel() == channel)
		{
			configuration.setChannel(channel, false);
			if(configuration.getChannel(state.getUnselectedChannel()))
			{
				state.setSelectedChannel(state.getUnselectedChannel());
			}
			else
			{
				state.setSelectedChannel(Configuration::NO_CHANNEL);
			}
		}
		else
		{
			state.setSelectedChannel(channel);
		}
	}
	else
	{
		configuration.setChannel(channel, true);
		state.setSelectedChannel(channel);
	}
}

void Touch::pressCouplingButton(Configuration::Channels channel)
{
	switch(configuration.getCoupling(channel))
	{
		case Configuration::AC:
			configuration.setCoupling(channel, Configuration::DC);
			break;
		case Configuration::DC:
			configuration.setCoupling(channel, Configuration::AC);
			break;
	}
}

bool Touch::isIn(int x, int y, vector<int> coordenates)
{
	return (x > coordenates[0]) && (x < coordenates[1]) && (y > coordenates[2]) && (y < coordenates[3]);
}


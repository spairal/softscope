#include <State.hpp>

State::State(void)
{
	this->selectedChannel = State::CHANNEL_A;
}

State::Channels State::getSelectedChannel(void)
{
	return this->selectedChannel;
}

#ifndef STATE_HPP
#define STATE_HPP

#include <Configuration.hpp>

class State
{
	private:
		Configuration::Channels selectedChannel;
		bool meassuresButtonActive;
		bool mathematicsButtonActive;
		bool modeButtonActive;

	public:
		State(void);
		Configuration::Channels getSelectedChannel(void);
		Configuration::Channels getUnselectedChannel(void);
		bool getMeassuresButtonActive(void);
		bool getMathematicsButtonActive(void);
		bool getModeButtonActive(void);
};

#endif

#ifndef STATE_HPP
#define STATE_HPP

class State
{
	public:
		enum Channels {NO_CHANNEL, CHANNEL_A, CHANNEL_B};

	private:
		Channels selectedChannel;

	public:
		State(void);
		Channels getSelectedChannel(void);
};

#endif

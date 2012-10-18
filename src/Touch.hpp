#ifndef TOUCH_HPP
#define TOUCH_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <vector>

class Touch
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;
		bool buttonPressed;

	public:
		Touch(Configuration& configuration, State& state, Samples& samples);
		void setButtonPressed(bool pressed);
		void parseScreen(int x, int y);

	private:
		void pressChannelButton(Configuration::Channels channel);
		void pressCouplingButton(Configuration::Channels channel);
		bool isIn(int x, int y, std::vector<int> coordenates);
};

#endif


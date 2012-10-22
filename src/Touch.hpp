#ifndef TOUCH_HPP
#define TOUCH_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <vector>

class Touch
{
	private:
		Configuration& configuration;
		State& state;
		bool buttonPressed;

	public:
		Touch(Configuration& configuration, State& state);
		void setButtonPressed(bool pressed);
		void parseScreen(int x, int y);

	private:
		void pressChannelButton(Configuration::Channels channel);
		void pressCouplingButton(Configuration::Channels channel);
		void pressMeasuresButton(void);
		void pressMathematicsButton(void);
		void pressModeButton(void);
		void selectMeasure(Configuration::Measures measure);
		void selectMathematic(Configuration::Mathematics mathematic);
		void selectMode(Configuration::Modes mode);
		bool isIn(int x, int y, std::vector<int> coordenates);
};

#endif


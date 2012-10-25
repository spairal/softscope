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
		bool buttonReleased;

	public:
		Touch(Configuration& configuration, State& state);
		void setButtonPressed(bool pressed);
		void setButtonReleased(bool released);
		void parseScreen(int x, int y);

	private:
		void startDragOffset(int x, int y);
		void startDragVerticalScale(int y);
		void startDragHorizontalScale(int x);
		void resetDrag(void);
		void dragOffset(int x, int y);
		void dragVerticalScale(int y);
		void dragHorizontalScale(int x);
		void resetButtons(void);
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


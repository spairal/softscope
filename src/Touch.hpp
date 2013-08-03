#ifndef TOUCH_HPP
#define TOUCH_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <MiniInput.hpp>
#include <vector>

class Touch
{
	private:
		Configuration& configuration;
		State& state;
		MiniInput miniInput;
		bool buttonPressed;
		bool buttonReleased;

	public:
		Touch(Configuration& configuration, State& state);
		void getInput(void);

	private:
		void setButtonPressed(bool pressed);
		void setButtonReleased(bool released);
		void parseScreen(int x, int y);
		void startDragCursors(int x, int y);
		void startDragOffset(int x, int y);
		void startDragVerticalScale(int y);
		void startDragHorizontalScale(int x);
		void startDragTriggerLevel(void);
		void resetDrag(void);
		void dragCursor(int x, int y);
		void dragOffset(int x, int y);
		void dragVerticalScale(int y);
		void dragHorizontalScale(int x);
		void dragTriggerLevel(int x, int y);
		void resetButtons(void);
		void pressChannelButton(Configuration::Channels channel);
		void pressCouplingButton(Configuration::Channels channel);
		void pressMeasuresButton(void);
		void pressMathematicsButton(void);
		void pressModeButton(void);
		void selectMeasure(Configuration::Measures measure);
		void selectMathematic(Configuration::Mathematics mathematic);
		void selectOption(int option);
		void selectMode(Configuration::Modes mode);
		void selectTriggerMode(Configuration::TriggerModes mode);
		void selectTriggerChannel(Configuration::Channels channel);
		void selectTriggerSlope(Configuration::TriggerSlopes slope);
		void selectTriggerNoiseReject(bool reject);
		void selectTriggerHighFrequencyReject(bool reject);
		void selectAverage(Configuration::Averages average);
		bool isIn(int x, int y, const std::vector<int>& coordenates);
};

#endif


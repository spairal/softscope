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
		bool buttonReleased;

	public:
		Touch(Configuration& configuration, State& state, Samples& samples);
		void setButtonPressed(bool pressed);
		void setButtonReleased(bool released);
		void parseScreen(int x, int y);

	private:
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
		void selectMode(Configuration::Modes mode);
		void selectTriggerMode(Configuration::TriggerModes mode);
		void selectTriggerChannel(Configuration::Channels channel);
		void selectTriggerSlope(Configuration::TriggerSlopes slope);
		void selectTriggerNoiseReject(bool reject);
		void selectTriggerHighFrequencyReject(bool reject);
		void selectAverage(Configuration::Averages average);
		bool isIn(int x, int y, std::vector<int> coordenates);
};

#endif


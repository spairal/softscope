#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <string>
#include <vector>

class Display
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;

	public:
		Display(Configuration& configuration, State& state, Samples& samples);
		void print(void);

	private:
		std::vector<int> samplesToPixels(const std::vector<double>& samples, double verticalScale, int pixelsPerDivision);
		void printGrid(int x1, int x2, int y1, int y2);
		void printOffset(int offsetValue, std::string offsetString, float R, float G, float B, int x1, int x2, int y1, int y2);
		void printVerticalScale(std::string verticalScale, float R, float G, float B, int x1, int x2, int y1, int y2);
		void printDelay(int delayValue, std::string delayString, int x1, int x2, int y1, int y2);
		void printHorizontalScale(std::string horizontalScale, int x1, int x2, int y1, int y2);
		void printChannelButton(std::string channel, bool isActive, bool isSelected, float R, float G, float B, int x1, int x2, int y1, int y2);
		void printCouplingButton(std::string text, bool isSelected, float R, float G, float B, int x1, int x2, int y1, int y2);
		void printButton(std::string title, std::string text, bool isActive, int x1, int x2, int y1, int y2);
		void printSamples(std::vector<int> samples, int delay, float R, float G, float B, int x1, int x2, int y1, int y2);
};

#endif


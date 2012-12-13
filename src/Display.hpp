#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <Measurer.hpp>
#include <Mathematician.hpp>
#include <MiniFB.hpp>
#include <string>
#include <vector>

class Display
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;
		Measurer& measurer;
		Mathematician& mathematician;
		MiniFB& miniFB;

	public:
		Display(Configuration& configuration, State& state, Samples& samples, Measurer& measurer, Mathematician& mathematician, MiniFB& miniFB);
		void print(void);

	private:
		std::vector<int> samplesToPixels(const std::vector<double>& samples, double offset, double verticalScale, int pixelsPerDivision);
		void printGrid(std::vector<int> coordenates);
		void printOffset(int offsetValue, std::string offsetString, int color, std::vector<int> coordenates);
		void printVerticalScale(std::string verticalScale, int color, std::vector<int> coordenates);
		void printDelay(int delayValue, std::string delayString, std::vector<int> coordenates);
		void printHorizontalScale(std::string horizontalScale, std::vector<int> coordenates);
		void printChannelButton(std::string channel, bool isActive, bool isSelected, int color, std::vector<int> coordenates);
		void printCouplingButton(std::string text, int color, std::vector<int> coordenates);
		void printButton(std::string title, std::string text, bool isActive, std::vector<int> coordenates);
		void printMenu(std::vector<std::string> options, std::vector<int> coordenates);
		void printAlert(std::string text, std::vector<int> coordenates);
		void printSamples(std::vector<int> samples, int delay, int memoryDepth, double step, int color, std::vector<int> coordenates);
		void printCursor(std::vector<int> coordenates);
};

#endif


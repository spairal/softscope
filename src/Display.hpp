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
		void printGrid(std::vector<int> coordenates);
		void printOffset(int offsetValue, std::string offsetString, std::vector<float> color, std::vector<int> coordenates);
		void printVerticalScale(std::string verticalScale, std::vector<float> color, std::vector<int> coordenates);
		void printDelay(int delayValue, std::string delayString, std::vector<int> coordenates);
		void printHorizontalScale(std::string horizontalScale, std::vector<int> coordenates);
		void printChannelButton(std::string channel, bool isActive, bool isSelected, std::vector<float> color, std::vector<int> coordenates);
		void printCouplingButton(std::string text, std::vector<float> color, std::vector<int> coordenates);
		void printButton(std::string title, std::string text, bool isActive, std::vector<int> coordenates);
		void printMenu(std::vector<std::string> options, std::vector<int> coordenates);
		void printSamples(std::vector<int> samples, int delay, std::vector<float> color, std::vector<int> coordenates);
};

#endif


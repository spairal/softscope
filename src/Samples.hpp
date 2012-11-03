#ifndef SAMPLES_HPP
#define SAMPLES_HPP

#include <Configuration.hpp>
#include <vector>

class Samples
{
	private:
		int memoryDepth;
		std::vector<double> samplesA;
		std::vector<double> samplesB;
		int delayA;
		int delayB;

	public:
		Samples(void);
		int getMemoryDepth(void);
		std::vector<double> getSamples(Configuration::Channels channel);
		void setSamples(Configuration::Channels channel, std::vector<double> samples);
		int getDelay(Configuration::Channels channel);
		void setDelay(Configuration::Channels channel, int delay);
};

#endif

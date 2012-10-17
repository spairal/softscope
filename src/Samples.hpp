#ifndef SAMPLES_HPP
#define SAMPLES_HPP

#include <Configuration.hpp>
#include <vector>

class Samples
{
	private:
		std::vector<double> samplesA;
		std::vector<double> samplesB;
		int delayA;
		int delayB;

	public:
		Samples(void);
		std::vector<double>& getSamples(Configuration::Channels channel);
		int getDelay(Configuration::Channels channel);
};

#endif

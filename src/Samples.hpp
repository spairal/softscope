#ifndef SAMPLES_HPP
#define SAMPLES_HPP

#include <Configuration.hpp>
#include <vector>

class Samples
{
	private:
		std::vector<double> samplesA;
		std::vector<double> samplesB;

	public:
		Samples(void);
		std::vector<double> getSamples(Configuration::Channels channel);
		void setSamples(Configuration::Channels channel, std::vector<double> samples);
};

#endif

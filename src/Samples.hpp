#ifndef SAMPLES_HPP
#define SAMPLES_HPP

#include <Configuration.hpp>
#include <fix.hpp>
#include <vector>

class Samples
{
	private:
		std::vector<fix> samplesA;
		std::vector<fix> samplesB;

	public:
		Samples(void);
		std::vector<fix> getSamples(Configuration::Channels channel);
		void setSamples(Configuration::Channels channel, const std::vector<fix>& samples);
};

#endif

#ifndef SAMPLES_HPP
#define SAMPLES_HPP

#include <Configuration.hpp>
#include <vector>

class Samples
{
	private:
		std::vector<float> samplesA;
		std::vector<float> samplesB;

	public:
		Samples(void);
		std::vector<float> getSamples(Configuration::Channels channel);
		void setSamples(Configuration::Channels channel, const std::vector<float>& samples);
};

#endif

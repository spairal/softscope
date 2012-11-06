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
		int delay;
		double step;

	public:
		Samples(void);
		int getMemoryDepth(void);
		std::vector<double> getSamples(Configuration::Channels channel);
		void setSamples(Configuration::Channels channel, std::vector<double> samples);
		int getDelay(void);
		void setDelay(int d);
		double getStep(void);
		void setStep(double s);
};

#endif

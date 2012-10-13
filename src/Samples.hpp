#ifndef SAMPLES_HPP
#define SAMPLES_HPP

#include <vector>

class Samples
{
	private:
		std::vector<int> samplesA;
		std::vector<int> samplesB;
		int delayA;
		int delayB;

	public:
		Samples(void);
		std::vector<int> getSamplesA(void);
		std::vector<int> getSamplesB(void);
		int getDelayA(void);
		int getDelayB(void);
};

#endif

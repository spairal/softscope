#include <FPGA.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

FPGA::FPGA(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
	srand(time(NULL));
}

void FPGA::fetchSamples(void)
{
	static double roll = 0;
	if(configuration.getMode() != Configuration::STOP)
	{
		vector<double> samplesA;
		vector<double> samplesB;
		if(configuration.getMode() == Configuration::ROLL)
		{
			int step = state.getPixelsPerDivision() / configuration.getHorizontalScaleValue() / 30;
			samplesA = samples.getSamples(Configuration::CHANNEL_A);
			samplesB = samples.getSamples(Configuration::CHANNEL_B);
			int i;
			for(i = 0; i < configuration.getMemoryDepth() - step; i++)
			{
				samplesA[i] = samplesA[i + step];
				samplesB[i] = samplesB[i + step];
			}
			roll = roll / configuration.getHorizontalScaleValue() - i;
			for(; i < configuration.getMemoryDepth(); i++)
			{
				samplesA[i] = 3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i + roll) / 30) + 0.4 * rand() / RAND_MAX - 0.2;
				int mod = (int)(i + roll) % (int)(20 / configuration.getHorizontalScaleValue());
				samplesB[i] = (((mod > (10 / configuration.getHorizontalScaleValue())) || ((mod > -10 / configuration.getHorizontalScaleValue()) && (mod < 0))) ? 2.0 : -2.0) + 0.6 * rand() / RAND_MAX - 0.3;
				//samplesB[i] = 3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i + roll) / 30 - 0.02) + 0.4 * rand() / RAND_MAX - 0.2;
			}
			roll = configuration.getHorizontalScaleValue() * (i + roll);
		}
		else
		{
			for(int i = 0; i < configuration.getMemoryDepth(); i++)
			{
				samplesA.push_back(3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * i / 30) + 0.4 * rand() / RAND_MAX - 0.2);
				int mod = (int)i % (int)(20 / configuration.getHorizontalScaleValue());
				samplesB.push_back((((mod > (10 / configuration.getHorizontalScaleValue())) || ((mod > -10 / configuration.getHorizontalScaleValue()) && (mod < 0))) ? 2.0 : -2.0) + 0.6 * rand() / RAND_MAX - 0.3);
				//samplesB.push_back(3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i - 100) / 30) + 0.4 * rand() / RAND_MAX - 0.2);
			}
		}
		samples.setSamples(Configuration::CHANNEL_A, samplesA);
		samples.setSamples(Configuration::CHANNEL_B, samplesB);
		if(configuration.getMode() == Configuration::SINGLE)
		{
			configuration.setMode(Configuration::STOP);
		}
	}
}


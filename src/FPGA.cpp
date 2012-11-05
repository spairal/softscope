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
	static int roll;
	if(configuration.getMode() != Configuration::STOP)
	{
		vector<double> samplesA;
		vector<double> samplesB;
		if(configuration.getMode() == Configuration::ROLL)
		{
			int step = state.getPixelsPerDivision() / configuration.getHorizontalScaleValue() / 30;
			roll += step; 
			samplesA = samples.getSamples(Configuration::CHANNEL_A);
			samplesB = samples.getSamples(Configuration::CHANNEL_B);
			int i;
			for(i = 0; i < samples.getMemoryDepth() - step; i++)
			{
				samplesA[i] = samplesA[i + step];
				samplesB[i] = samplesB[i + step];
			}
			for(; i < samples.getMemoryDepth(); i++)
			{
				samplesA[i] = 3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i + roll - samples.getDelay(Configuration::CHANNEL_A) - configuration.getDelay() * 50) / 30) + 0.4 * rand() / RAND_MAX - 0.2;
				int mod = (int)(i + roll - samples.getDelay(Configuration::CHANNEL_B) - configuration.getDelay() * 50) % (int)(20 / configuration.getHorizontalScaleValue());
				samplesB[i] = (((mod > (10 / configuration.getHorizontalScaleValue())) || ((mod > -10 / configuration.getHorizontalScaleValue()) && (mod < 0))) ? 2.0 : -2.0) + 0.6 * rand() / RAND_MAX - 0.3;
				//samplesB[i] = 3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i + roll - samples.getDelay(Configuration::CHANNEL_B) - configuration.getDelay() * 50 - 100) / 30) + 0.4 * rand() / RAND_MAX - 0.2;
			}
		}
		else
		{
			roll = 0;
			for(int i = 0; i < samples.getMemoryDepth(); i++)
			{
				samplesA.push_back(3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i - samples.getDelay(Configuration::CHANNEL_A) - configuration.getDelay() * 50) / 30) + 0.4 * rand() / RAND_MAX - 0.2);
				int mod = (int)(i - samples.getDelay(Configuration::CHANNEL_B) - configuration.getDelay() * 50) % (int)(20 / configuration.getHorizontalScaleValue());
				samplesB.push_back((((mod > (10 / configuration.getHorizontalScaleValue())) || ((mod > -10 / configuration.getHorizontalScaleValue()) && (mod < 0))) ? 2.0 : -2.0) + 0.6 * rand() / RAND_MAX - 0.3);
				//samplesB.push_back(3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i - samples.getDelay(Configuration::CHANNEL_B) - configuration.getDelay() * 50 - 100) / 30) + 0.4 * rand() / RAND_MAX - 0.2);
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


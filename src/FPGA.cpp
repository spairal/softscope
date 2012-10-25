#include <FPGA.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

FPGA::FPGA(Configuration& configuration, Samples& samples) : configuration(configuration), samples(samples)
{
}

void FPGA::fetchSamples(void)
{
	vector<double>& samplesA = samples.getSamples(Configuration::CHANNEL_A);
	vector<double>& samplesB = samples.getSamples(Configuration::CHANNEL_B);
	srand(time(NULL));
	for(int i = 0; i < samplesA.size(); i++)
	{
		samplesA[i] = 3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i - samples.getDelay(Configuration::CHANNEL_A) - configuration.getDelay() * 50) / 30) + 0.4 * rand() / RAND_MAX - 0.2 + configuration.getOffset(Configuration::CHANNEL_A);
	}
	for(int i = 0; i < samplesB.size(); i++)
	{
		int mod = (int)(i - samples.getDelay(Configuration::CHANNEL_B) - configuration.getDelay() * 50) % (int)(20 / configuration.getHorizontalScaleValue());
		samplesB[i] = (((mod > (10 / configuration.getHorizontalScaleValue())) || ((mod > -10 / configuration.getHorizontalScaleValue()) && (mod < 0))) ? 2.0 : -2.0) + 0.6 * rand() / RAND_MAX - 0.3 + configuration.getOffset(Configuration::CHANNEL_B);
	}
}


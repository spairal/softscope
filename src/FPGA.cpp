#include <FPGA.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define PI 3.141592

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
		samplesA[i] = 3.0 * sin(2.0 * PI * i / 300.0) + 0.4 * rand() / RAND_MAX - 0.2;
	}
	for(int i = 0; i < samplesB.size(); i++)
	{
		samplesB[i] = (((i % 200) > 100) ? 2.0 : -2.0) + 0.6 * rand() / RAND_MAX - 0.3;
	}
}


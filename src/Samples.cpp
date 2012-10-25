#include <Samples.hpp>

using namespace std;

Samples::Samples(void)
{
	samplesA.assign(1500,0.0);
	samplesB.assign(1500,1.0);
	delayA = 750;
	delayB = 750;
}

vector<double>& Samples::getSamples(Configuration::Channels channel)
{
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			return samplesA;
		case Configuration::CHANNEL_B:
			return samplesB;
	}
}

int Samples::getDelay(Configuration::Channels channel)
{
	int delay;
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			delay = delayA;
			break;
		case Configuration::CHANNEL_B:
			delay = delayB;
			break;
	}
	return delay;
}


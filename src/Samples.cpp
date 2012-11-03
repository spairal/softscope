#include <Samples.hpp>

using namespace std;

Samples::Samples(void)
{
	memoryDepth = 1500;
	samplesA.assign(memoryDepth,0.0);
	samplesB.assign(memoryDepth,0.0);
	delayA = memoryDepth / 2;
	delayB = memoryDepth / 2;
}

int Samples::getMemoryDepth(void)
{
	return memoryDepth;
}

vector<double> Samples::getSamples(Configuration::Channels channel)
{
	vector<double> samples;
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			samples = samplesA;
			break;
		case Configuration::CHANNEL_B:
			samples = samplesB;
			break;
	}
	return samples;
}

void Samples::setSamples(Configuration::Channels channel, vector<double> samples)
{
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			samplesA = samples;
			break;
		case Configuration::CHANNEL_B:
			samplesB = samples;
			break;
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

void Samples::setDelay(Configuration::Channels channel, int delay)
{
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			delayA = delay;
			break;
		case Configuration::CHANNEL_B:
			delayB = delay;
			break;
	}
}


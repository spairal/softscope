#include <Samples.hpp>

using namespace std;

Samples::Samples(void)
{
	memoryDepth = 1500;
	samplesA.assign(memoryDepth, 0.0);
	samplesB.assign(memoryDepth, 0.0);
	delay = memoryDepth / 2;
	step = 1;
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

int Samples::getDelay(void)
{
	return delay;
}

void Samples::setDelay(int d)
{
	delay = d;
}

double Samples::getStep(void)
{
	return step;
}

void Samples::setStep(double s)
{
	step = s;
}


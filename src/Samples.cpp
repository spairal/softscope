#include <Samples.hpp>

using namespace std;

Samples::Samples(void)
{
	samplesA.assign(1024, 0.0);
	samplesB.assign(1024, 0.0);
}

vector<float> Samples::getSamples(Configuration::Channels channel)
{
	vector<float> samples;
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

void Samples::setSamples(Configuration::Channels channel, const vector<float>& samples)
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


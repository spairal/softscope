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
	static fix roll = 0;
	if(configuration.getMode() != Configuration::STOP)
	{
		vector<fix> samplesA;
		vector<fix> samplesB;
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
				samplesA[i] = 3.0f * sin((float)(2.0f * 3.141592f * configuration.getHorizontalScaleValue() * (i + roll) / 30)) + 0.4f * rand() / RAND_MAX - 0.2f;
				int mod = (int)(i + roll) % (int)(20 / configuration.getHorizontalScaleValue());
				samplesB[i] = (((mod > (10 / configuration.getHorizontalScaleValue())) || ((mod > -10 / configuration.getHorizontalScaleValue()) && (mod < 0))) ? 2.0f : -2.0f) + 0.6f * rand() / RAND_MAX - 0.3f;
				//samplesB[i] = 3.0 * sin((float)(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i + roll) / 30 - 0.02)) + 0.4 * rand() / RAND_MAX - 0.2;
			}
			roll = configuration.getHorizontalScaleValue() * (i + roll);
		}
		else
		{
			vector<fix> oldSamplesA = samples.getSamples(Configuration::CHANNEL_A);
			vector<fix> oldSamplesB = samples.getSamples(Configuration::CHANNEL_B);
			fix averageCoefficient = 1.0f / configuration.getAverageValue();
			for(int i = 0; i < configuration.getMemoryDepth(); i++)
			{
				samplesA.push_back(averageCoefficient * (3.0f * sin((float)(2.0f * 3.141592f * configuration.getHorizontalScaleValue() * i / 30)) + 0.4f * rand() / RAND_MAX - 0.2f) + (1 - averageCoefficient) * oldSamplesA[i]);
				int mod = (int)i % (int)(20 / configuration.getHorizontalScaleValue());
				samplesB.push_back(averageCoefficient * ((((mod > (10 / configuration.getHorizontalScaleValue())) || ((mod > -10 / configuration.getHorizontalScaleValue()) && (mod < 0))) ? 2.0f : -2.0f) + 0.6f * rand() / RAND_MAX - 0.3f) + (1 - averageCoefficient) * oldSamplesB[i]);
				//samplesB.push_back(averageCoefficient * (3.0f * sin((float)(2.0f * 3.141592f * configuration.getHorizontalScaleValue() * (i - 100) / 30)) + 0.4f * rand() / RAND_MAX - 0.2f) + (1 - averageCoefficient) * oldSamplesB[i]);
			}
		}
		samples.setSamples(Configuration::CHANNEL_A, samplesA);
		samples.setSamples(Configuration::CHANNEL_B, samplesB);
		if(configuration.getMode() == Configuration::SINGLE)
		{
			configuration.setMode(Configuration::RUN);
		}
	}
}

int FPGA::getMask(int bits)
{
	int mask = 0;
	for(int i = 0; i < bits; i++)
	{
		mask = (mask << 1) | 1;
	}
	return mask;
}

int FPGA::quantize(bool value, int shift)
{
	return ((value ? 1 : 0) << shift);
}

int FPGA::quantize(fix value, fix minimum, int bits, int shift)
{
	return ((((int) round(value / minimum)) & getMask(bits)) << shift);
}

int FPGA::getFirstMessage(void)
{
	int message = 0;
	message |= quantize(configuration.getChannel(Configuration::CHANNEL_A), 0);
	message |= quantize(configuration.getChannel(Configuration::CHANNEL_B), 1);
	message |= quantize(configuration.getHorizontalScale(), 1, 5, 2);
	message |= quantize(configuration.getMode() == Configuration::ROLL, 7);
	message |= quantize(configuration.getTriggerMode() == Configuration::AUTOMATIC, 8);
	message |= quantize(configuration.getTriggerLevel(), 0.03125f, 8, 9);
	message |= quantize(configuration.getTriggerHoldOff(), 1, 5, 17);
	message |= quantize(configuration.getTriggerSlope() == Configuration::POSITIVE, 22);
	message |= quantize(configuration.getTriggerChannel() == Configuration::CHANNEL_B, 23);
	message |= quantize(configuration.getVerticalScale(Configuration::CHANNEL_A), 1, 4, 24);
	message |= quantize(configuration.getVerticalScale(Configuration::CHANNEL_B), 1, 4, 28);
	message |= quantize(configuration.getCoupling(Configuration::CHANNEL_A) == Configuration::AC, 32);
	message |= quantize(configuration.getCoupling(Configuration::CHANNEL_B) == Configuration::AC, 33);
	message |= quantize(configuration.getTriggerNoiseReject(), 34);
	message |= quantize(configuration.getTriggerHighFrequencyReject(), 35);
	return message;
}

int FPGA::getSecondMessage(void)
{
	int message = 0;
	message |= quantize(configuration.getOffset(Configuration::CHANNEL_A), 0.0003125f, 18, 0);
	message |= quantize(configuration.getOffset(Configuration::CHANNEL_B), 0.0003125f, 18, 18);
	return message;
}


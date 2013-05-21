#include <FPGA.hpp>

using namespace std;

FPGA::FPGA(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples), miniWahoo("/sys/class/spi_master/spi1/device/spi1.0")
{
	channelABuffer = miniWahoo.getChannelDataBuffer(Configuration::CHANNEL_A);
	channelBBuffer = miniWahoo.getChannelDataBuffer(Configuration::CHANNEL_B);
}

void FPGA::fetchSamples(void)
{
	setTriggerConf(quantize(configuration.getTriggerChannel() == Configuration::CHANNEL_B), quantize(configuration.getTriggerSlope() == Configuration::POSITIVE), quantize(configuration.getTriggerMode() == Configuration::AUTOMATIC), quantize(configuration.getMode() == Configuration::ROLL), quantize(configuration.getTriggerNoiseReject()), quantize(configuration.getTriggerHighFrequencyReject()), quantize(configuration.getTriggerHoldOff(), 1, 5), quantize(configuration.getTriggerLevel(), 0.03125, 8));
	setSampleRate(quantize(configuration.getHorizontalScale(), 1, 5));
	setChannelConf(Configuration::CHANNEL_A, quantize(configuration.getChannel(Configuration::CHANNEL_A)), quantize(configuration.getVerticalScale(Configuration::CHANNEL_A), 1, 4), quantize(configuration.getCoupling(Configuration::CHANNEL_A) == Configuration::AC), quantize(configuration.getOffset(Configuration::CHANNEL_A), 0.0003125, 18));
	setChannelConf(Configuration::CHANNEL_B, quantize(configuration.getChannel(Configuration::CHANNEL_B)), quantize(configuration.getVerticalScale(Configuration::CHANNEL_B), 1, 4), quantize(configuration.getCoupling(Configuration::CHANNEL_B) == Configuration::AC), quantize(configuration.getOffset(Configuration::CHANNEL_B), 0.0003125, 18));
	if(configuration.getMode() != Configuration::STOP)
	{
		if(configuration.getMode() == Configuration::ROLL)
		{
		
		}
		else
		{
			if(configuration.getChannel(Configuration::CHANNEL_A))
			{
				int N = fetchChannelSamples(Configuration::CHANNEL_A);
				if(N > 0)
				{
					vector<float> oldSamplesA = samples.getSamples(Configuration::CHANNEL_A);
					vector<float> samplesA;
					float averageCoefficient = 1.0 / configuration.getAverageValue();
					for(int i = 0; i < N; i++)
					{
						samplesA.push_back(averageCoefficient * getVerticalScaleValue(Channels channel) * (channelABuffer[i] - 128) / 256 + (1 - averageCoefficient) * oldSamplesA[i]);
					}
					samples.setSamples(Configuration::CHANNEL_A, samplesA);
				}
			}
			
			/*if(configuration.getMode() == Configuration::SINGLE)
			{
				configuration.setMode(Configuration::RUN);
			}*/
		}
	}
	/*static float roll = 0;
	if(configuration.getMode() != Configuration::STOP)
	{
		vector<float> samplesA;
		vector<float> samplesB;
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
			vector<float> oldSamplesA = samples.getSamples(Configuration::CHANNEL_A);
			vector<float> oldSamplesB = samples.getSamples(Configuration::CHANNEL_B);
			float averageCoefficient = 1.0 / configuration.getAverageValue();
			for(int i = 0; i < configuration.getMemoryDepth(); i++)
			{
				samplesA.push_back(averageCoefficient * (3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * i / 30) + 0.4 * rand() / RAND_MAX - 0.2) + (1 - averageCoefficient) * oldSamplesA[i]);
				int mod = (int)i % (int)(20 / configuration.getHorizontalScaleValue());
				samplesB.push_back(averageCoefficient * ((((mod > (10 / configuration.getHorizontalScaleValue())) || ((mod > -10 / configuration.getHorizontalScaleValue()) && (mod < 0))) ? 2.0 : -2.0) + 0.6 * rand() / RAND_MAX - 0.3) + (1 - averageCoefficient) * oldSamplesB[i]);
				//samplesB.push_back(averageCoefficient * (3.0 * sin(2.0 * 3.141592 * configuration.getHorizontalScaleValue() * (i - 100) / 30) + 0.4 * rand() / RAND_MAX - 0.2) + (1 - averageCoefficient) * oldSamplesB[i]);
			}
		}
		samples.setSamples(Configuration::CHANNEL_A, samplesA);
		samples.setSamples(Configuration::CHANNEL_B, samplesB);
		if(configuration.getMode() == Configuration::SINGLE)
		{
			configuration.setMode(Configuration::RUN);
		}
	}*/
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

int FPGA::quantize(bool value)
{
	return (value ? 1 : 0);
}

int FPGA::quantize(float value, float minimum, int bits)
{
	return (((int) round(value / minimum)) & getMask(bits));
}


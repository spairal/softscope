#include <FPGA.hpp>
#include <cmath>

using namespace std;

FPGA::FPGA(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples), miniWahoo("/sys/class/spi_master/spi1/device/spi1.0")
{
	channelABuffer = miniWahoo.getChannelDataBuffer(Configuration::CHANNEL_A);
	channelBBuffer = miniWahoo.getChannelDataBuffer(Configuration::CHANNEL_B);
}

void FPGA::fetchSamples(void)
{
	if(configuration.getModifiedTrigger())
	{
	   miniWahoo.setTriggerConf(configuration.getTriggerChannel(), quantize(configuration.getTriggerSlope() == Configuration::POSITIVE), quantize(configuration.getTriggerMode() == Configuration::AUTOMATIC), quantize(configuration.getMode() == Configuration::ROLL), quantize(configuration.getTriggerNoiseReject()), quantize(configuration.getTriggerHighFrequencyReject()), quantize(configuration.getTriggerHoldOff(), 1, 5), quantize(configuration.getTriggerLevel(), 0.03125f, 8));
	}
	if(configuration.getModifiedSampleRate())
	{
      miniWahoo.setSampleRate(quantize(configuration.getHorizontalScale(), 1, 5));
   }
   if(configuration.getModifiedChannel(Configuration::CHANNEL_A))
   {
	   miniWahoo.setChannelConf(Configuration::CHANNEL_A, quantize(configuration.getChannel(Configuration::CHANNEL_A)), quantize(configuration.getVerticalScale(Configuration::CHANNEL_A), 1, 4), quantize(configuration.getCoupling(Configuration::CHANNEL_A) == Configuration::AC), quantize(configuration.getOffset(Configuration::CHANNEL_A), 0.0003125f, 18));
	}
	if(configuration.getModifiedChannel(Configuration::CHANNEL_A))
   {
	   miniWahoo.setChannelConf(Configuration::CHANNEL_B, quantize(configuration.getChannel(Configuration::CHANNEL_B)), quantize(configuration.getVerticalScale(Configuration::CHANNEL_B), 1, 4), quantize(configuration.getCoupling(Configuration::CHANNEL_B) == Configuration::AC), quantize(configuration.getOffset(Configuration::CHANNEL_B), 0.0003125f, 18));
	}
	if(configuration.getMode() != Configuration::STOP)
	{
		if(configuration.getMode() == Configuration::ROLL)
		{
			if(configuration.getChannel(Configuration::CHANNEL_A))
			{
				int N = miniWahoo.fetchChannelSamples(Configuration::CHANNEL_A);
				if(N > 0)
				{
					vector<fix> samplesA = samples.getSamples(Configuration::CHANNEL_A);
					int i;
					for(i = 0; i < configuration.getMemoryDepth() - N; i++)
					{
						samplesA[i] = samplesA[i + N];
					}
					for(; i < configuration.getMemoryDepth(); i++)
					{
						samplesA[i] = configuration.getVerticalScaleValue(Configuration::CHANNEL_A) * (channelABuffer[i] - 128) / 32;
					}
					samples.setSamples(Configuration::CHANNEL_A, samplesA);
				}
			}
			if(configuration.getChannel(Configuration::CHANNEL_B))
			{
				int N = miniWahoo.fetchChannelSamples(Configuration::CHANNEL_B);
				if(N > 0)
				{
					vector<fix> samplesB = samples.getSamples(Configuration::CHANNEL_B);
					int i;
					for(i = 0; i < configuration.getMemoryDepth() - N; i++)
					{
						samplesB[i] = samplesB[i + N];
					}
					for(; i < configuration.getMemoryDepth(); i++)
					{
						samplesB[i] = configuration.getVerticalScaleValue(Configuration::CHANNEL_B) * (channelBBuffer[i] - 128) / 32;
					}
					samples.setSamples(Configuration::CHANNEL_B, samplesB);
				}
			}
		}
		else
		{
			if(configuration.getChannel(Configuration::CHANNEL_A))
			{
				int N = miniWahoo.fetchChannelSamples(Configuration::CHANNEL_A);
				if(N == configuration.getMemoryDepth())
				{
					vector<fix> oldSamplesA = samples.getSamples(Configuration::CHANNEL_A);
					vector<fix> samplesA;
					fix averageCoefficient = 1.0f / configuration.getAverageValue();
					for(int i = 0; i < configuration.getMemoryDepth(); i++)
					{
						samplesA.push_back(averageCoefficient * configuration.getVerticalScaleValue(Configuration::CHANNEL_A) * (channelABuffer[i] - 128) / 32 + (1 - averageCoefficient) * oldSamplesA[i]);
					}
					samples.setSamples(Configuration::CHANNEL_A, samplesA);
					if(configuration.getMode() == Configuration::SINGLE)
					{
						configuration.setMode(Configuration::RUN);
					}
				}
			}
			if(configuration.getChannel(Configuration::CHANNEL_B))
			{
				int N = miniWahoo.fetchChannelSamples(Configuration::CHANNEL_B);
				if(N == configuration.getMemoryDepth())
				{
					vector<fix> oldSamplesB = samples.getSamples(Configuration::CHANNEL_B);
					vector<fix> samplesB;
					fix averageCoefficient = 1.0f / configuration.getAverageValue();
					for(int i = 0; i < configuration.getMemoryDepth(); i++)
					{
						samplesB.push_back(averageCoefficient * configuration.getVerticalScaleValue(Configuration::CHANNEL_B) * (channelBBuffer[i] - 128) / 32 + (1 - averageCoefficient) * oldSamplesB[i]);
					}
					samples.setSamples(Configuration::CHANNEL_B, samplesB);
					if(configuration.getMode() == Configuration::SINGLE)
					{
						configuration.setMode(Configuration::RUN);
					}
				}
			}
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

int FPGA::quantize(bool value)
{
	return (value ? 1 : 0);
}

int FPGA::quantize(fix value, fix minimum, int bits)
{
	return (((int) round(value / minimum)) & getMask(bits));
}


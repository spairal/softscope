#include <Measurer.hpp>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

Measurer::Measurer(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
	measure = configuration.getMeasureString(state.getSelectedChannel());
	cachedTime = time(NULL);
	cachedChannel = state.getSelectedChannel();
	cachedMeasure = configuration.getMeasure();
}

string Measurer::getMeasure(void)
{
	if((cachedTime != time(NULL)) || (cachedChannel != state.getSelectedChannel()) || (cachedMeasure != configuration.getMeasure()))
	{
		stringstream ss;
		ss << configuration.getMeasureString(state.getSelectedChannel());
		if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
		{
			switch(configuration.getMeasure())
			{
				case Configuration::MEAN:
					ss << " = " << getMean();
					break;
				case Configuration::PEAK:
					ss << " = " << getPeak();
					break;
				case Configuration::RMS:
					ss << " = " << getRMS();
					break;
				case Configuration::FREQUENCY:
					ss << " = " << getFrequency();
					break;
				case Configuration::PERIOD:
					ss << " = " << getPeriod();
					break;
				case Configuration::RISETIME:
					ss << " = " << getRiseTime();
					break;
				case Configuration::FALLTIME:
					ss << " = " << getFallTime();
					break;
				case Configuration::DUTYCYCLE:
					ss << " = " << getDutyCycle();
					break;
				case Configuration::PHASE:
					ss << " = " << getPhase();
					break;
				case Configuration::RATIO:
					ss << " = " << getRatio();
					break;
			}
		}
		measure = ss.str();
		cachedTime = time(NULL);
		cachedChannel = state.getSelectedChannel();
		cachedMeasure = configuration.getMeasure();
	}
	return measure;
}

string Measurer::getMean(void)
{
	vector<float> signal = samples.getSamples(state.getSelectedChannel());
	float mean = 0;
	for(int i = 0; i < signal.size(); i++)
	{
		mean += signal[i];
	}
	mean /= signal.size();
	return configuration.voltageToString(mean);
}

string Measurer::getPeak(void)
{
	vector<float> signal = samples.getSamples(state.getSelectedChannel());
	return configuration.voltageToString((maximum(signal) - minimum(signal)) / 2);
}

string Measurer::getRMS(void)
{
	vector<float> signal = samples.getSamples(state.getSelectedChannel());
	float rms = 0;
	for(int i = 0; i < signal.size(); i++)
	{
		rms += pow(signal[i], 2);
	}
	rms = sqrt(rms / signal.size());
	return configuration.voltageToString(rms);
}

string Measurer::getFrequency(void)
{
	vector<float> signal = samples.getSamples(state.getSelectedChannel());
	return configuration.frequencyToString(state.getPixelsPerDivision() / (configuration.getHorizontalScaleValue() * getMaxCorrelation(signal, signal)));
}

string Measurer::getPeriod(void)
{
	vector<float> signal = samples.getSamples(state.getSelectedChannel());
	return configuration.timeToString(configuration.getHorizontalScaleValue() * getMaxCorrelation(signal, signal) / state.getPixelsPerDivision());
}

string Measurer::getRiseTime(void)
{
	vector<float> signal = samples.getSamples(state.getSelectedChannel());
	float maxi = maximum(signal);
	float mini = minimum(signal);
	float low = 0.9 * mini + 0.1 * maxi;
	float high = 0.9 * maxi + 0.1 * mini;
	bool count = false;
	int pixels = 0;
	int edges = 0;
	int tmp = 0;
	for(int i = 1; i < signal.size(); i++)
	{
		if((signal[i] >= low) && (signal[i - 1] < low))
		{
			count = true;
		}
		if(count)
		{
			tmp++;
		}
		if(count && (signal[i] <= low) && (signal[i - 1] > low))
		{
			count = false;
			tmp = 0;
		}
		if(count && (signal[i] >= high) && (signal[i - 1] < high))
		{
			count = false;
			pixels += tmp;
			edges++;
			tmp = 0;
		}
	}
	string riseTime;
	if(edges == 0)
	{
		riseTime = "N/A";
	}
	else
	{
		riseTime = configuration.timeToString(configuration.getHorizontalScaleValue() * pixels / (edges * state.getPixelsPerDivision()));
	}
	return riseTime; 
}

string Measurer::getFallTime(void)
{
	vector<float> signal = samples.getSamples(state.getSelectedChannel());
	float maxi = maximum(signal);
	float mini = minimum(signal);
	float low = 0.9 * mini + 0.1 * maxi;
	float high = 0.9 * maxi + 0.1 * mini;
	bool count = false;
	int pixels = 0;
	int edges = 0;
	int tmp = 0;
	for(int i = 1; i < signal.size(); i++)
	{
		if((signal[i] <= high) && (signal[i - 1] > high))
		{
			count = true;
		}
		if(count)
		{
			tmp++;
		}
		if(count && (signal[i] >= high) && (signal[i - 1] < high))
		{
			count = false;
			tmp = 0;
		}
		if(count && (signal[i] <= low) && (signal[i - 1] > low))
		{
			count = false;
			pixels += tmp;
			edges++;
			tmp = 0;
		}
	}
	string fallTime;
	if(edges == 0)
	{
		fallTime = "N/A";
	}
	else
	{
		fallTime = configuration.timeToString(configuration.getHorizontalScaleValue() * pixels / (edges * state.getPixelsPerDivision()));
	}
	return fallTime;
}

string Measurer::getDutyCycle(void)
{
	vector<float> signal = samples.getSamples(state.getSelectedChannel());
	float maxi = maximum(signal);
	float mini = minimum(signal);
	int pixels = 0;
	int N = signal.size();
	for(int i = 0; i < N; i++)
	{
		if(signal[i] >= ((maxi + mini) / 2))
		{
			pixels++;
		}
	}
	return configuration.percentageToString((float)pixels / N);
}

string Measurer::getPhase(void)
{
	string phase;
	if(configuration.getChannel(Configuration::CHANNEL_A) && configuration.getChannel(Configuration::CHANNEL_B))
	{
		vector<float> signalA = samples.getSamples(state.getSelectedChannel());
		vector<float> signalB = samples.getSamples(state.getUnselectedChannel());
		int periodA = getMaxCorrelation(signalA, signalA);
		int periodB = getMaxCorrelation(signalB, signalB);
		int correlation = getMaxCorrelation(signalA, signalB);
		float p = 2.0 * 360 * correlation / (periodA + periodB);
		bool wrap = true;
		while(wrap)
		{
			wrap = false;
			if(p > 180)
			{
				wrap = true;
				p -= 360;
			}
		}
		phase = configuration.degreesToString(p);
	}
	else
	{
		phase = "N/A";
	}
	return phase;
}

string Measurer::getRatio(void)
{
	string ratio;
	if(configuration.getChannel(Configuration::CHANNEL_A) && configuration.getChannel(Configuration::CHANNEL_B))
	{
		vector<float> signalA = samples.getSamples(state.getSelectedChannel());
		vector<float> signalB = samples.getSamples(state.getUnselectedChannel());
		float maxA = maximum(signalA);
		float minA = minimum(signalA);
		float maxB = maximum(signalB);
		float minB = minimum(signalB);
		ratio = configuration.deciBellToString(20 * log10((maxA - minA) / (maxB - minB)));
	}
	else
	{
		ratio = "N/A";
	}
	return ratio;
}

float Measurer::maximum(const vector<float>& signal)
{
	float maxi = signal[0];
	for(int i = 0; i < signal.size(); i++)
	{
		maxi = max(maxi, signal[i]);
	}
	return maxi;
}

float Measurer::minimum(const vector<float>& signal)
{
	float mini = signal[0];
	for(int i = 0; i < signal.size(); i++)
	{
		mini = min(mini, signal[i]);
	}
	return mini;
}

int Measurer::getMaxCorrelation(const vector<float>& signalA, const vector<float>& signalB)
{
	int N = min(signalA.size(), signalB.size());
	float maxCorrelation = 0;
	int maxI = 0;
	for(int i = state.getPixelsPerDivision(); i < N / 2; i++)
	{
		float correlation = 0;
		for(int j = 0; j < (N - i); j++)
		{
			correlation += (signalA[j] * signalB[j + i]);
		}
		correlation /= N;
		if(correlation > maxCorrelation)
		{
			maxCorrelation = correlation;
			maxI = i;
		}
	}
	return maxI;
}


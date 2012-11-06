#include <Mathematician.hpp>
#include <fftw3.h>
#include <cmath>

using namespace std;

Mathematician::Mathematician(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
}

vector<double> Mathematician::getSamples(void)
{
	vector<double> signal(10 * state.getPixelsPerDivision(), 0);
	switch(configuration.getMathematic())
	{
		case Configuration::DIFFERENCE:
			signal = getDifference();
			break;
		case Configuration::FFT:
			signal = getFFT();
			break;
	}
	return signal;
}

vector<double> Mathematician::getDifference(void)
{
	vector<double> signal(10 * state.getPixelsPerDivision(), 0);
	if(configuration.getChannel(Configuration::CHANNEL_A) && configuration.getChannel(Configuration::CHANNEL_B))
	{
		vector<double> signalA = samples.getSamples(state.getSelectedChannel());
		int delay = samples.getDelay();
		vector<double> signalB = samples.getSamples(state.getUnselectedChannel());
		for(int i = 0; i < signal.size(); i++)
		{
			signal[i] = signalA[delay - 5 * state.getPixelsPerDivision() + i] - signalB[delay - 5 * state.getPixelsPerDivision() + i];
		}
	}
	return signal;
}

vector<double> Mathematician::getFFT(void)
{
	vector<double> fft(10 * state.getPixelsPerDivision(), 0);
	if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
	{
		vector<double> signal = samples.getSamples(state.getSelectedChannel());
		int delay = samples.getDelay();
		double verticalScale = configuration.getVerticalScale(state.getSelectedChannel());
		int pixelsPerDivision = state.getPixelsPerDivision();
		int N = fft.size();
		int M = 2 * (N - 1);
		double* in = (double*) fftw_malloc(sizeof(double) * M);
		fftw_complex* out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
		fftw_plan p = fftw_plan_dft_r2c_1d(M, in, out, FFTW_ESTIMATE);
		vector<double> w = hamming(M);
		int start = delay - 10 * state.getPixelsPerDivision();
		if(start < 0)
		{
			start = 0;
		}
		if((start + M) > samples.getMemoryDepth())
		{
			start = samples.getMemoryDepth() - M;
		}
		for(int i = 0; i < M; i++)
		{
			in[i] = w[i] * pixelsPerDivision * signal[start + i] / verticalScale;
		}
		fftw_execute(p);
		for(int i = 0; i < N; i++)
		{
			fft[i] = verticalScale * 20 * log10(sqrt((pow(out[i][0], 2) + pow(out[i][1], 2))) / M) / pixelsPerDivision;
		}
		fftw_destroy_plan(p);
		fftw_free(in);
		fftw_free(out);
	}
	return fft;
}

vector<double> Mathematician::hamming(int N)
{
	vector<double> w;
	for(int i = 0; i < N; i++)
	{
		w.push_back(0.54 - 0.46 * cos(2 * 3.1415926 * i / (N - 1)));
	}
	return w;
}


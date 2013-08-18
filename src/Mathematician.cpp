#include <Mathematician.hpp>
#include <fftw3.h>
#include <cmath>

using namespace std;

Mathematician::Mathematician(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
}

vector<fix> Mathematician::getSamples(void)
{
   vector<fix> signal(10 * state.getPixelsPerDivision(), 0);
   switch(configuration.getMathematic())
   {
      case Configuration::SUM:
         signal = getSum();
         break;
      case Configuration::DIFFERENCE:
         signal = getDifference();
         break;
      case Configuration::FFT:
         signal = getFFT();
         break;
   }
   return signal;
}

vector<fix> Mathematician::getSum(void)
{
   vector<fix> signal(10 * state.getPixelsPerDivision() + 1, 0);
   if(configuration.getChannel(Configuration::CHANNEL_A) && configuration.getChannel(Configuration::CHANNEL_B))
   {
      vector<fix> signalA = samples.getSamples(state.getSelectedChannel());
      int delay = configuration.getMemoryDepth() / 2 - round(configuration.getDelay() * state.getPixelsPerDivision()) - 5 * state.getPixelsPerDivision();
      vector<fix> signalB = samples.getSamples(state.getUnselectedChannel());
      for(int i = 0; i < signal.size(); i++)
      {
         signal[i] = signalA[delay + i] + signalB[delay + i];
      }
   }
   return signal;
}

vector<fix> Mathematician::getDifference(void)
{
   vector<fix> signal(10 * state.getPixelsPerDivision() + 1, 0);
   if(configuration.getChannel(Configuration::CHANNEL_A) && configuration.getChannel(Configuration::CHANNEL_B))
   {
      vector<fix> signalA = samples.getSamples(state.getSelectedChannel());
      int delay = configuration.getMemoryDepth() / 2 - round(configuration.getDelay() * state.getPixelsPerDivision()) - 5 * state.getPixelsPerDivision();
      vector<fix> signalB = samples.getSamples(state.getUnselectedChannel());
      for(int i = 0; i < signal.size(); i++)
      {
         signal[i] = signalA[delay + i] - signalB[delay + i];
      }
   }
   return signal;
}

vector<fix> Mathematician::getFFT(void)
{
   vector<fix> fft(10 * state.getPixelsPerDivision() + 1, 0);
   if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
   {
      vector<fix> signal = samples.getSamples(state.getSelectedChannel());
      fix verticalScale = configuration.getVerticalScale(state.getSelectedChannel());
      int pixelsPerDivision = state.getPixelsPerDivision();
      int N = fft.size();
      int M = 2 * (N - 1);
      double* in = (double*) fftw_malloc(sizeof(double) * M);
      fftw_complex* out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
      fftw_plan p = fftw_plan_dft_r2c_1d(M, in, out, FFTW_ESTIMATE);
      vector<fix> w = hamming(M);
      int start = configuration.getMemoryDepth() / 2 - round(configuration.getDelay() * state.getPixelsPerDivision()) - 5 * state.getPixelsPerDivision();
      if(start < 0)
      {
         start = 0;
      }
      if((start + M) > configuration.getMemoryDepth())
      {
         start = configuration.getMemoryDepth() - M;
      }
      for(int i = 0; i < M; i++)
      {
         in[i] = w[i] * pixelsPerDivision * signal[start + i] / verticalScale;
      }
      fftw_execute(p);
      for(int i = 0; i < N; i++)
      {
         fft[i] = verticalScale * 20 * log10(sqrt((float)(pow(out[i][0], 2) + pow(out[i][1], 2))) / M + 0.000001f) / pixelsPerDivision;
      }
      fftw_destroy_plan(p);
      fftw_free(in);
      fftw_free(out);
   }
   return fft;
}

vector<fix> Mathematician::hamming(int N)
{
   vector<fix> w;
   for(int i = 0; i < N; i++)
   {
      w.push_back(0.54f - 0.46f * cos(2 * 3.1415926f * i / (N - 1)));
   }
   return w;
}


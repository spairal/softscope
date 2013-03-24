#ifndef MATHEMATICIAN_HPP
#define MATHEMATICIAN_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>

class Mathematician
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;

	public:
		Mathematician(Configuration& configuration, State& state, Samples& samples);
		std::vector<float> getSamples(void);

	private:
		std::vector<float> getDifference(void);
		std::vector<float> getFFT(void);
		std::vector<float> hamming(int N);
};

#endif


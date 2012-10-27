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
		std::vector<double> getSamples(void);

	private:
		std::vector<double> getDifference(void);
		std::vector<double> getFFT(void);
		std::vector<double> hamming(int N);
};

#endif


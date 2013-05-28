#ifndef MATHEMATICIAN_HPP
#define MATHEMATICIAN_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <fix.hpp>

class Mathematician
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;

	public:
		Mathematician(Configuration& configuration, State& state, Samples& samples);
		std::vector<fix> getSamples(void);

	private:
		std::vector<fix> getDifference(void);
		std::vector<fix> getFFT(void);
		std::vector<fix> hamming(int N);
};

#endif


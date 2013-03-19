#ifndef FPGA_HPP
#define FPGA_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>

class FPGA
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;

	public:
		FPGA(Configuration& configuration, State& state, Samples& samples);
		void fetchSamples(void);
	
	private:
		int getMask(int bits);
		int quantize(bool value, int shift);
		int quantize(double value, double minimum, int bits, int shift);
		int getFirstMessage(void);
		int getSecondMessage(void);
};

#endif

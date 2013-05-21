#ifndef FPGA_HPP
#define FPGA_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <MiniWahoo.hpp>

class FPGA
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;
		MiniWahoo miniWahoo;
		char* channelABuffer;
		char* channelBBuffer;

	public:
		FPGA(Configuration& configuration, State& state, Samples& samples);
		void fetchSamples(void);
	
	private:
		int getMask(int bits);
		int quantize(bool value);
		int quantize(float value, float minimum, int bits);
};

#endif

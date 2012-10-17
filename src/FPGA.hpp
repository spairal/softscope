#ifndef FPGA_HPP
#define FPGA_HPP

#include <Configuration.hpp>
#include <Samples.hpp>

class FPGA
{
	private:
		Configuration& configuration;
		Samples& samples;

	public:
		FPGA(Configuration& configuration, Samples& samples);
		void fetchSamples(void);
};

#endif

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <Measurer.hpp>
#include <Mathematician.hpp>
#include <Touch.hpp>
#include <FPGA.hpp>
#include <Display.hpp>
#include <MiniFB.hpp>

using namespace std;

int main(int argc, char** argv)
{
	Configuration configuration;
	State state;
	Samples samples;
	Touch touch(configuration, state, samples);
	FPGA fpga(configuration, state, samples);
	Display display(configuration, state, samples);
	while(true)
	{
		touch.getInput();
		fpga.fetchSamples();
		display.print();
	}
	return 0;
}


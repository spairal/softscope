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
	MiniFB miniFB("/dev/fb0");
	Configuration configuration;
	State state;
	Samples samples;
	Measurer measurer(configuration, state, samples);
	Mathematician mathematician(configuration, state, samples);
	Touch touch(configuration, state, samples);
	FPGA fpga(configuration, state, samples);
	Display display(configuration, state, samples, measurer, mathematician, miniFB);
	while(true)
	{
		if(false)
		{
			touch.setButtonPressed(true);
		}
		if(false)
		{
			touch.setButtonReleased(true);
		}
		fpga.fetchSamples();
		display.print();
	}
	return 0;
}


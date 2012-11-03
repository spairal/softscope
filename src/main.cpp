#include <polo.h>
#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <Measurer.hpp>
#include <Mathematician.hpp>
#include <Touch.hpp>
#include <FPGA.hpp>
#include <Display.hpp>

using namespace std;

class UserData
{
	public:
		Touch touch;
		FPGA fpga;
		Display display;
	
	public:
		UserData(Configuration& configuration, State& state, Samples& samples, Measurer& measurer, Mathematician& mathematician) : touch(configuration, state, samples), fpga(configuration, state, samples), display(configuration, state, samples, measurer, mathematician)
		{
		}
};

void mouseMotionCallback(void* userData, int x, int y)
{
	Touch& touch = ((UserData*)userData)->touch;
	touch.parseScreen(x, y);
}

void mouseButtonCallback(void* userData, int button, int pressed)
{
	Touch& touch = ((UserData*)userData)->touch;
	if(pressed)
	{
		touch.setButtonPressed(true);
	}
	else
	{
		touch.setButtonReleased(true);
	}
}

void drawCallback(void* userData)
{
	FPGA& fpga = ((UserData*)userData)->fpga;
	Display& display = ((UserData*)userData)->display;
	fpga.fetchSamples();
	display.print();
}

int main(int argc, char** argv)
{
	int width = 640;
	int height = 480;
	int fullscreen = 0;
	string windowTitle = "Oscilloscope";
	initPolo(width, height, fullscreen, windowTitle.data());
	Configuration configuration;
	State state;
	Samples samples;
	Measurer measurer(configuration, state, samples);
	Mathematician mathematician(configuration, state, samples);
	UserData userData(configuration, state, samples, measurer, mathematician);
	setPoloUserData(&userData);
	setMouseMotionCallback(mouseMotionCallback);
	setMouseButtonCallback(mouseButtonCallback);
	setDrawCallback(drawCallback);
	runPolo();
	return 0;
}

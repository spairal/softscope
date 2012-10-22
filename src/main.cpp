#include <polo.h>
#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
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
		UserData(Configuration& configuration, State& state, Samples& samples) : touch(configuration, state), fpga(configuration, samples), display(configuration, state, samples)
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
	UserData userData(configuration, state, samples);
	setPoloUserData(&userData);
	setMouseMotionCallback(mouseMotionCallback);
	setMouseButtonCallback(mouseButtonCallback);
	setDrawCallback(drawCallback);
	runPolo();
	return 0;
}

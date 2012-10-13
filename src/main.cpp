#include <polo.h>
#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <Display.hpp>

class UserData
{
	public:
		Display display;
	
	public:
		UserData(Configuration& configuration, State& state, Samples& samples) : display(configuration, state, samples)
		{
		}
};

void drawCallback(void* userData)
{
	Display& display = ((UserData*)userData)->display;
	display.print();
}

int main(int argc, char** argv)
{
	int width = 640;
	int height = 480;
	int fullscreen = 0;
	char windowTitle[] = "Oscilloscope";
	initPolo(width, height, fullscreen, windowTitle);
	setDrawCallback(drawCallback);
	Configuration configuration;
	State state;
	Samples samples;
	UserData userData(configuration, state, samples);
	setPoloUserData(&userData);
	runPolo();
	return 0;
}

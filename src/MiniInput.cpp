#include <MiniInput.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>

using namespace std;

MiniInput::MiniInput(string input)
{
	fd = open(input.data(), O_RDONLY);
	x = 0;
	y = 0;
	pressed = false;
	released = false;
	ifstream myFile("calibrate.txt");
	if(myFile.is_open())
	{
		myFile >> ax >> bx >> ay >> by;
	}
	pthread_create(&inputThread, NULL, updateInput, (void*) this);
}

MiniInput::~MiniInput(void)
{
	pthread_cancel(inputThread);
}

int MiniInput::getX(void)
{
	return x;
}

int MiniInput::getY(void)
{
	return y;
}

bool MiniInput::getPressed(void)
{
	bool p = pressed;
	pressed = false;
	return p;
}

bool MiniInput::getReleased(void)
{
	bool r = released;
	released = false;
	return r;
}

void* updateInput(void* arg)
{
	MiniInput* miniInput = (MiniInput*) arg;
	while(read(miniInput->fd, &(miniInput->ie), sizeof(struct input_event)))
	{
		switch (miniInput->ie.type)
		{	
			case EV_SYN:
				break;
			case EV_KEY:
				switch(miniInput->ie.value)
				{
					case 0:
						miniInput->released = true;
						break;
					case 1:
						miniInput->pressed = true;
						break;
				}
				break;
			case EV_REL:
				switch(miniInput->ie.code)
				{
					case REL_X:
						miniInput->x += miniInput->ie.value;
						break;
					case REL_Y:
						miniInput->y += miniInput->ie.value;
						break;
				}
				break;
			case EV_ABS:
				switch(miniInput->ie.code)
				{
					case ABS_X:
						miniInput->x = (miniInput->ie.value - miniInput->bx) / miniInput->ax;
						break;
					case ABS_Y:
						miniInput->y = (miniInput->ie.value - miniInput->by) / miniInput->ay;
						break;
				}
				break;
		}	
	}
}


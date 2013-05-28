#ifndef MINIINPUT_HPP
#define MINIINPUT_HPP

#include <fix.hpp>
#include <linux/input.h>
#include <pthread.h>
#include <string>

void* updateInput(void* arg);

class MiniInput
{
	friend void* updateInput(void* arg);

	private:
		int fd;
		struct input_event ie;
		pthread_t inputThread;
		int x;
		int y;
		bool pressed;
		bool released;
		bool drag;
		fix ax;
		fix bx;
		fix ay;
		fix by;
		fix alfa;

	public:
		MiniInput(std::string input);
		~MiniInput(void);
		int getX(void);
		int getY(void);
		bool getPressed(void);
		bool getReleased(void);
};

#endif


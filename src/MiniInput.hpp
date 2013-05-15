#ifndef MINIINPUT_HPP
#define MINIINPUT_HPP

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
		float ax;
		float bx;
		float ay;
		float by;

	public:
		MiniInput(std::string input);
		~MiniInput(void);
		int getX(void);
		int getY(void);
		bool getPressed(void);
		bool getReleased(void);
};

#endif


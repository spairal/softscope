#include <MiniFB.hpp>
#include <MiniInput.hpp>
#include <iostream>
#include <unistd.h>
#include <fstream>

#define N 10
#define US 10000

using namespace std;

int main(int argc, char** argv)
{
	ofstream tmpFile("calibrate.txt");
	if(tmpFile.is_open())
	{
		tmpFile << 1 << endl;
		tmpFile << 0 << endl;
		tmpFile << 1 << endl;
		tmpFile << 0 << endl;
		tmpFile.close();
	}
	MiniFB miniFB("/dev/fb0");
	MiniInput miniInput("/dev/input/event0");
	int xi1 = 100;
	int xo1 = 0;
	int yi1 = 100;
	int yo1 = 0;
	int xi2 = 600;
	int xo2 = 0;
	int yi2 = 400;
	int yo2 = 0;
	bool pressed;
	cout << "Touch the Xs!" << endl;
	miniFB.clearScreen();
	miniFB.drawText(xi1 - miniFB.getTextWidth("X") / 2, yi1 - miniFB.getTextHeight("X") / 2, "X", 0xFF);
	miniFB.updateScreen();
	pressed = false;
	while(!pressed)
	{
		if(miniInput.getPressed())
		{
			pressed = true;
			for(int i = 0; i < N; i++)
			{
				usleep(US);
				xo1 += miniInput.getX();
				yo1 += miniInput.getY();
			}
			xo1 /= N;
			yo1 /= N;
			cout << "xo1 = " << xo1 << "; yo1 = " << yo1 << endl; 
		}
	}
	miniFB.clearScreen();
	miniFB.drawText(xi2 - miniFB.getTextWidth("X") / 2, yi2 - miniFB.getTextHeight("X") / 2, "X", 0xFF);
	miniFB.updateScreen();
	pressed = false;
	while(!pressed)
	{
		if(miniInput.getPressed())
		{
			pressed = true;
			for(int i = 0; i < N; i++)
			{
				usleep(US);
				xo2 += miniInput.getX();
				yo2 += miniInput.getY();
			}
			xo2 /= N;
			yo2 /= N;
			cout << "xo2 = " << xo2 << "; yo2 = " << yo2 << endl;
		}
	}
	float ax = (float)(xo2 - xo1) / (float)(xi2 - xi1);
	float bx = (float)(xi2 * xo1 - xi1 * xo2) / (float)(xi2 - xi1);
	float ay = (float)(yo2 - yo1) / (float)(yi2 - yi1);
	float by = (float)(yi2 * yo1 - yi1 * yo2) / (float)(yi2 - yi1);
	cout << "ax = " << ax << "; bx = " << bx << endl;
	cout << "ay = " << ay << "; by = " << by << endl;
	ofstream myFile("calibrate.txt");
	if(myFile.is_open())
	{
		myFile << ax << endl;
		myFile << bx << endl;
		myFile << ay << endl;
		myFile << by << endl;
		myFile.close();
	}
	return 0;
}


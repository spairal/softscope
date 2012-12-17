#include <MiniFB.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cstdlib>

using namespace std;

MiniFB::MiniFB(string fb)
{
	int fd = open(fb.data(), O_RDWR);
	struct fb_var_screeninfo screeninfo;
	ioctl(fd, FBIOGET_VSCREENINFO, &screeninfo);
	width = screeninfo.xres;
	height = screeninfo.yres;
	data = (unsigned int*) mmap(0, 4 * width * height, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	buffer = new unsigned int[width * height];
}

MiniFB::~MiniFB()
{
	munmap(data, 4 * width * height);
	delete[] buffer;
}

void MiniFB::clearScreen(void)
{
	drawRectangleFill(0, 0, width - 1, height - 1, 0x000000);
}

void MiniFB::updateScreen(void)
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			data[y * width + x] = buffer[y * width + x];
		}
	}
}

void MiniFB::drawPixel(int x, int y, int color)
{
	x += 40;
	y += 48;
	if((x >= 0) && (x < width) && (y >= 0) && (y < height))
	{
		buffer[y * width + x] = color;
	}
}

void MiniFB::drawLine(int x1, int y1, int x2, int y2, int color)
{
	if(abs(x2 - x1) > abs(y2 - y1))
	{
		int xStep = (x1 < x2) ? 1 : -1;
		double y = y1 + 0.5;
		double yStep = (double) (y2 - y1) / (x2 - x1);
		for(int x = x1; x != x2; x += xStep)
		{
			drawPixel(x, y, color);
			y += yStep;
		}
	}
	else
	{
		int yStep = (y1 < y2) ? 1 : -1;
		double x = x1 + 0.5;
		double xStep = (double) (x2 - x1) / (y2 - y1);
		for(int y = y1; y != y2; y += yStep)
		{
			drawPixel(x, y, color);
			x += xStep;
		}
	}
}

void MiniFB::drawRectangleFill(int x1, int y1, int x2, int y2, int color)
{
	int xStep = (x1 > x2) ? -1 : 1;
	int yStep = (y1 > y2) ? -1 : 1;
	for(int x = x1; x <= x2; x += xStep)
	{
		for(int y = y1; y <= y2; y += yStep)
		{
			drawPixel(x, y, color);
		}
	}
}

void MiniFB::drawRectangleBorder(int x1, int y1, int x2, int y2, int color)
{
	drawLine(x1, y1, x2, y1, color);
	drawLine(x1, y2, x2, y2, color);
	drawLine(x1, y1, x1, y2, color);
	drawLine(x2, y1, x2, y2, color);
}

void MiniFB::drawRectangle(int x1, int y1, int x2, int y2, int fillColor, int borderColor)
{
	drawRectangleFill(x1, y1, x2, y2, fillColor);
	drawRectangleBorder(x1, y1, x2, y2, borderColor);
}

void MiniFB::drawText(int x, int y, string text, int color, FONTS font)
{
}

int MiniFB::getTextWidth(string text, FONTS font)
{
	return 0;
}

int MiniFB::getTextHeight(string text, FONTS font)
{
	return 0;
}

int MiniFB::thinColor(int color, int times)
{
	int r = color & 0xFF0000;
	int g = color & 0x00FF00;
	int b = color & 0x0000FF;
	r >>= times;
	g >>= times;
	b >>= times;
	r &= 0xFF0000;
	g &= 0x00FF00;
	b &= 0x0000FF;
	return r | g | b;
}


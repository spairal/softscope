#ifndef MINIFB_HPP
#define MINIFB_HPP

class MiniFB
{
	private:
		int width;
		int height;
		unsigned int* data;

	public:
		MiniFB(std::string fb);
		~MiniFB();
		void drawPixel(int x, int y, int color);
		void drawLine(int x1, int y1, int x2, int y2, int color);
		void drawRectangleFill(int x1, int y1, int x2, int y2, int color);
		void drawRectangleBorder(int x1, int y1, int x2, int y2, int color);
		void drawRectangle(int x1, int y1, int x2, int y2, int fillColor, int borderColor);
};

#endif


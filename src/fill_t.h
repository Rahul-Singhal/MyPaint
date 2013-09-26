#ifndef FILL_T
#define FILL_T

#include <queue>
#include <GL/glut.h>
#include "color_t.h"
#include "point_t.h"
class fill_t{
private:
	color_t color1;
	color_t color2;
	int fillMode;
	static color_t ** colorArray;
	void find_min_max(point_t p,int& YMin, int& YMax, int& XMin, int& XMax,float width,float height);
public:
	fill_t();
	void draw(point_t p,float width,float height);
	int getFillMode();
	color_t getColor1();
	void setFillMode(int fill);
	void setColor1(color_t c);
	void setColor2(color_t c);
	color_t getColor2();
	void solid_fill(point_t p,float width,float height);
	void checkerboard_fill(point_t p,float width,float height);
	void setColorArray(color_t ** & colorArray);
	void printPointColor(point_t p);
};

#endif

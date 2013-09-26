#ifndef POINT_T
#define POINT_T

#include "pen_t.h"
#include "color_t.h"

class point_t{
	private:
	float x;
	float y;
	float size;
	static color_t ** colorArray;
	public:
	point_t();
	float getSize() const;
	float getX() const;
	float getY() const;
	void setX(float);
	void setY(float);
	point_t(float xn,float yn);
	point_t(float xn,float yn,float size1);
	void draw(pen_t p);
	void setColorArray(color_t ** & colorArray);
	point_t & operator = (const point_t & p);
	//color_t ** & getColorArray();
};
#endif

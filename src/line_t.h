#ifndef LINE_T
#define LINE_T
#include <GL/glut.h>
#include "color_t.h"
#include "point_t.h"
#include "pen_t.h"

class line_t{
	private:
	point_t start;
	point_t end;
	color_t color;
	float size;
	void swap(float & a, float & b);
	public:
	void draw();
	line_t();
	line_t(point_t start, point_t end_t, pen_t p);
	line_t(point_t start, point_t end, color_t c, float s);
	line_t & operator= (const line_t & l) ;
	void setStart(point_t p);
	void setEnd(point_t p);
	point_t getStart() const;
	point_t getEnd() const;
	color_t getColor() const;
	float getSize();
	float getR();
	void setColor(color_t c);
	void setSize(float s);
	void getLineData(char* & ch);
};
#endif

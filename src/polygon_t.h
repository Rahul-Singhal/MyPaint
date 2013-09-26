#ifndef POLYGON_T
#define POLYGON_T

#include "line_t.h"
#include "fill_t.h"
#include "pen_t.h"
#include<cstdio>
#include <vector>

class polygon_t{
	private:
	std::vector <point_t> vertices;
	color_t border;
	bool filled;
	color_t fill_color;
	float size;
	public:
	polygon_t(pen_t);
	void draw();
	point_t getFirstVertex();
	void addPoint(point_t p);
	void putDataInFile(FILE* &file);
	
};
#endif

#ifndef DRAWING_T
#define DRAWING_T

#include "fill_t.h"
#include "polygon_t.h"
#include "pen_t.h"
#include <vector>

enum elementType{ FILLPOINT = 1, LINE =  2, POLYGON = 3, CHECKPOINT = 4};

class drawing_t{
	private:
	std::vector<line_t> lines;
	std::vector<polygon_t> polygons;
	std::vector<point_t> points;
	std::vector<int> drawingOrder;
	std::vector<color_t> fillColors;
	fill_t fillObject;
	public:
	void addToLines(line_t);
	void addToPolygons(polygon_t);
	void addToPoints(point_t p, int mode, color_t c1, color_t c2);
	drawing_t();
	void draw(float width,float height);
	void save(float w, float h, color_t bcolor);
	void load(FILE* & file);
	polygon_t & getLastPolygon();
	void pushIntoQueue(int type);
	void undo();
};

#endif
	

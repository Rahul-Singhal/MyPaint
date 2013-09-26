#ifndef CANVAS_T
#define CANVAS_T

#include "drawing_t.h"
#include "pen_t.h"
#include "point_t.h"

class canvas_t{
	private:
	float width;
	float height;
	drawing_t drawing;
	color_t back_color;
	color_t ** colorArray;
	public:
	void setCanvas(float width,float height,color_t color);
	void setDrawing(drawing_t drawing);
	drawing_t& getDrawing();
	canvas_t();
	canvas_t(float width1, float height1, color_t b);
	void clear();
	void draw();
	color_t getColor();
	void setNewArray();
	void sendColorArrayReferenceToPointAndFill();
	float myFunc(float x, float y);
	void save();
	void load();
};

#endif

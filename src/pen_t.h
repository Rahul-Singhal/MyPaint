#ifndef PEN_T
#define PEN_T

#include "color_t.h"
class pen_t{
 private:
	float size;
	color_t color;
	color_t defaultColor;
	int mode;
	bool eraserActivate;
public:
	pen_t();
	pen_t(color_t c, float s);
	float getSize();
	color_t getColor();
	int getMode();
	void setSize(float s);
	void setColor(color_t c);
	void setMode(int m);
	void setModeToEraser(color_t c, float s);
	bool isEraser();
};

#endif
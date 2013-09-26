#include "pen_t.h"

float pen_t::getSize(){
	return size;
}

color_t pen_t::getColor(){
	return color;
}

int pen_t::getMode(){
	return mode;
}
void pen_t::setSize(float s){
	size = s;
}

void pen_t::setColor(color_t c){
	color = c;
}

void pen_t::setMode(int m){
	color = defaultColor;
	mode = m;
	eraserActivate = false;
}

void pen_t::setModeToEraser(color_t c, float s){
	if(!(color == c)) defaultColor = color;
	mode = 1;
	color = c;
	size=s;
	eraserActivate = true;
}

pen_t::pen_t(){

	size = 2;
	color_t c1(0,0,1);
	color = c1;
	defaultColor = c1;
	mode = 1;
	eraserActivate = false;
}

pen_t::pen_t(color_t c, float s){
	defaultColor = c;
	color = c;
	size = s;
	eraserActivate = false;
}

bool pen_t::isEraser(){
	return eraserActivate;
}
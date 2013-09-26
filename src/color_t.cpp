#include "color_t.h"
color_t::color_t(float r, float g, float b){
		r_comp=r;
		g_comp=g;
		b_comp=b;
}

float color_t::getR() const{
	return r_comp;
}

float color_t::getG() const{
	return g_comp;
}

float color_t::getB() const{
	return b_comp;
}
color_t::color_t(){
}

color_t & color_t::operator= (const color_t & c) {
	this->r_comp = c.getR();
	this->g_comp = c.getG();
	this->b_comp = c.getB();
	return *this;
}

bool color_t::operator== (const color_t & c){
	return (this->r_comp == c.getR() && this->g_comp == c.getG() && this->b_comp == c.getB());
}


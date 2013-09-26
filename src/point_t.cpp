
#include "point_t.h"
#include <GL/glut.h>
#include<iostream>

color_t ** point_t::colorArray;

void point_t::draw(pen_t p){
  glPointSize(p.getSize());     
  glBegin(GL_POINTS);
  color_t penColor = p.getColor();
  glColor3f(penColor.getR(), penColor.getG(), penColor.getB());
  //std::cout<<"r is "<<p.getColor().getR()<<" and g is "<<p.getColor().getG()<<std::endl;
  colorArray[(int)x][(int)y] = p.getColor();
  glVertex2f(x, y);
  glEnd();
}

point_t::point_t(){
}

point_t::point_t(float xn,float yn,float size1=1){
	x=xn;
	y=yn;
	size=size1;
}

point_t::point_t(float xn,float yn){
	x=xn;
	y=yn;
	size=1;
}

float point_t::getX() const{
	return x;
}

float point_t::getY() const{
	return y;
}

float point_t::getSize() const{
	return size;
}

void point_t::setX(float x){
	this->x=x;
}
void point_t::setY(float y){
	this->y=y;
}

void point_t::setColorArray(color_t ** & colorArray){
	this->colorArray = colorArray;
}

point_t & point_t::operator = (const point_t & p){
	this->x = p.getX();
	this->y = p.getY();
	this->size = p.getSize();
	return *this;
}

// color_t ** & point_t::getColorArray(){
// 	return colorArray;
// }
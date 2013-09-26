#include "line_t.h"
#include<iostream>
#include<cstring>
#include<cstdio>

float line_t::getR(){
  return color.getG();
}

line_t & line_t::operator= (const line_t & l) {
  this->start = l.getStart();
  this->end = l.getEnd();
  this->color = l.getColor();
  return *this;
}

point_t line_t::getStart() const{
  return start;
}

point_t line_t::getEnd() const{
  return end;
}

color_t line_t::getColor() const{
  return color;
}


void line_t::draw()
{
  //glColor3f(color.getR(), color.getG(), color.getB());
  float x0 = start.getX();
  float y0 = start.getY();
  float x1 = end.getX();
  float y1 = end.getY();

  //std::cout<<x0<<"  "<<y0<<" "<<x1<<"  "<<y1<<std::endl;

  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep)
    {
      swap(x0, y0);
      swap(x1, y1);
    }
    
  if (x0 > x1)
    {
      swap(x0, x1);
      swap(y0, y1);
    }
  int deltax = x1 - x0;
  int deltay = abs(y1 - y0);

  float error = 0.0;
  float deltaerr = (float)deltay / (float)deltax;

  int ystep;
  int y = y0;

  if (y0 < y1) ystep = 1; else ystep = -1;

  //glPointSize(size);     
  

  //glBegin(GL_POINTS);
  for (int x=x0; x < x1; x++)
    {
      //std::cout<<"hey bhagwaaan!!  "<<color.getR()<<std::endl;
      if (steep){point_t p1(y,x); p1.draw(pen_t(color, size)); }
      else  {point_t p1(x,y); p1.draw(pen_t(color, size)); }

      error = error + deltaerr;
      if (error >= 0.5) 
      {
        y = y + ystep;
        error = error - 1.0;
      }
    }
    //std::cout<<"yo man !!!"<<std::endl;
  //glEnd();
}


line_t::line_t(point_t start, point_t end, pen_t p){
	this->start = start;
	this->end = end;
	this->color = p.getColor();
  this->size = p.getSize();
}

line_t::line_t(point_t start, point_t end, color_t c, float s){
  this->start = start;
  this->end = end;
  this->color = c;
  this->size = s;
}

void line_t::swap(float & a, float & b){
  float temp = a;
  a = b;
  b = temp;
}

line_t::line_t(){}

void line_t::setStart(point_t p){
  start = p;
}

void line_t::setEnd(point_t p){
  end = p;
}

void line_t::setColor(color_t c){
  color = c;
}
  
void line_t::setSize(float s){
  size=s;
}

void line_t::getLineData(char* & ch){
  //char ch[100];
  //startx starty endx endy r g b size
  sprintf(ch, "%f,%f,%f,%f,%f,%f,%f,%f\n", start.getX(), start.getY(), end.getX(),end.getY(), color.getR(), color.getG(), color.getB(), size);
  //return ch;
}

float line_t::getSize(){
  return size;
}
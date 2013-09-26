
#include "polygon_t.h"
#include<iostream>
#include<string>

void polygon_t::draw(){
	line_t l;
	int i ;
	for(i = 0 ; i<vertices.size()-1; i++){
		l.setStart(vertices[i]);
		l.setEnd(vertices[i+1]);
		l.setColor(border);
		l.setSize(size);
		l.draw();
	}
	l.setStart(vertices[i]);
	l.setEnd(vertices[0]) ;
	l.setColor(border);
	l.setSize(size);
	l.draw();

}

point_t polygon_t::getFirstVertex(){
	return vertices[0];
}

void polygon_t::addPoint(point_t p){
	vertices.push_back(p);
}

polygon_t::polygon_t(pen_t p){
	size=p.getSize();
	border = p.getColor();
}

void polygon_t::putDataInFile(FILE* &file){
	//string str = "";
	//get the number of points in the polygon
	//num vertices, border r,g,b,size
	int l = vertices.size();
	char ch[200];
	sprintf(ch, "%d,%f,%f,%f,%f\n", l, border.getR(), border.getG(), border.getB(), size);
	fputs(ch,file);
	for(int i = 0 ; i<l; i++){
		sprintf(ch, "%f,%f\n", vertices[i].getX(), vertices[i].getY());
		fputs(ch, file);
	}
}


#include "canvas_t.h"
#include<iostream>
#include<cstdlib>
#include<cstdio>
void canvas_t::clear(){
	drawing_t d;
	drawing = d;
}
canvas_t::canvas_t(){
}

canvas_t::canvas_t(float width1, float height1, color_t b){
	//std::cout<<"A MI HERE"<<std::endl;
	width=width1;
	height=height1;
	back_color=b;
	setNewArray();
}

void canvas_t::setDrawing(drawing_t drawing){
	this->drawing=drawing;
}

void canvas_t::setCanvas(float width,float height,color_t color){
	//std::cout<<"HEY THERE"<<std::endl;
	this->width=width;
	this->height=height;
	this->back_color=color;
	//std::cout<<"see the back color "<<back_color.getR()<<"  "<<back_color.getG()<<"  "<<back_color.getB()<<std::endl;
	glClearColor(back_color.getR(),back_color.getG(), back_color.getB(), 1.0f);
	glClear( GL_COLOR_BUFFER_BIT );
	glutReshapeWindow(width,height);
	drawing_t draw1;
	drawing = draw1;
	setNewArray();

    //glutPostRedisplay();
}

void canvas_t::draw(){
	//std::cout<<"I HOPE THIS IS VISIBLE!!! :( "<<std::endl;
	setNewArray();
	drawing.draw(width,height);
}

drawing_t& canvas_t::getDrawing(){
	return drawing;
}

color_t canvas_t::getColor(){
	return back_color;
}

void canvas_t::setNewArray(){
	//std::cout<<height<<"  kjghkjkhkkj j "<<width<<std::endl;
	//exit(0);
	colorArray = new color_t*[(int)width];
	for(int i = 0 ; i<width; i++){
		colorArray[i] = new color_t[(int)height];
	}
	
	for(int i = 0 ; i < width; i++){
		for(int j = 0; j<height; j++){
			colorArray[i][j] = back_color;
		}
	}
	sendColorArrayReferenceToPointAndFill();
}

void canvas_t::sendColorArrayReferenceToPointAndFill(){
	point_t p1;
	p1.setColorArray(colorArray);
	fill_t f;
	f.setColorArray(colorArray);
}

float canvas_t::myFunc(float x, float y){
	return colorArray[(int)x][(int)y].getR();
}

void canvas_t::save(){
	drawing.save(width, height, back_color);
}

void canvas_t::load(){
	std::string fileName;
	//std::cout<<"Enter the file name: ";
	std::cin>>fileName;
	FILE * file = fopen(fileName.c_str(), "r");
	char getStr[200];
	fgets(getStr, 200, file);
	float w, h,r,g,b;
	sscanf(getStr, "%f,%f,%f,%f,%f\n", &w, &h,&r,&g,&b);
	setCanvas(w,h,color_t(r,g,b));
	drawing.load(file);
	
	fclose(file);
}

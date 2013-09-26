#include "fill_t.h"
#include<iostream>
#include<cstdlib>

color_t ** fill_t::colorArray;


void fill_t::draw(point_t p,float width,float height){
	if(getFillMode()==1){
		solid_fill(p,width,height);
	}
	else{
		checkerboard_fill(p,width,height);
	}
}

color_t fill_t::getColor1(){
	return color1;
}

color_t fill_t::getColor2(){
	return color2;
}

void fill_t::setFillMode(int m){
	fillMode = m;
}

void fill_t::setColor1(color_t c){
	color1 = c;
}

void fill_t::setColor2(color_t c){
	color2 = c;
}

fill_t::fill_t(){
	fillMode = 1;
	color_t c1(0,1,0);
	color_t c2(1,0,0);
	color1 = c1;
	color2 = c2;
}

int fill_t::getFillMode(){
	return fillMode;
}

void fill_t::setColorArray(color_t ** & colorArray){
	this->colorArray = colorArray;
}

void fill_t::solid_fill(point_t p,float width,float height){
	//std::cout<<"width  "<<width<<" and height "<<height<<std::endl;
	std::queue <point_t> fillQueue;
	fillQueue.push(p);
	float pointx=p.getX();
	float pointy=p.getY();
	color_t c=colorArray[(int)pointx][(int)pointy];
	
    color_t pixels;
    
    while(!fillQueue.empty()){
    	// std::cout<<c.getR()<<" ANSSS"<<std::endl;
    	// exit(0);
		p=fillQueue.front();
		pointx=p.getX();
		pointy=p.getY();
		fillQueue.pop();
		
		//Added Canvas size check
		if(pointx>=width || pointy>=height || pointx<0 || pointy<0)
			continue;
		pixels = colorArray[(int)pointx][(int)pointy];
		
		if( (pixels.getR()==c.getR()) && (pixels.getG()==c.getG()) && (pixels.getB()==c.getB()) )
		{
			
			point_t p1(pointx, pointy);
			p1.draw(pen_t(color1,1));
			fillQueue.push(point_t(pointx+1,pointy));
			fillQueue.push(point_t(pointx,pointy+1));
			fillQueue.push(point_t(pointx-1,pointy));
			fillQueue.push(point_t(pointx,pointy-1));
		}
	}
}


void fill_t::find_min_max(point_t p,int& YMin, int& YMax, int& XMin, int& XMax,float width,float height){
	//std::cout<<"Min max\n";
	std::queue <point_t> fmmQueue;
	fmmQueue.push(p);
	float pointx = p.getX();
	float pointy = p.getY();
	
	color_t c=colorArray[(int)pointx][(int)pointy];
    color_t pixels;
    
     while(!fmmQueue.empty()){
		p=fmmQueue.front();
		pointx=p.getX();
		pointy=p.getY();
		fmmQueue.pop();
		//Added Canvas size check
		if(pointx>=width || pointy>=height || pointx<0 || pointy<0)
			continue;
		
		pixels = colorArray[(int)pointx][(int)pointy];
		//glReadPixels(pointx,pointy,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
		
		if( (pixels.getR()==c.getR()) && (pixels.getG()==c.getG()) && (pixels.getB()==c.getB()) )
		{
			if(pointy<YMin){
				YMin=pointy;
			}
			if(pointy>YMax){
				YMax=pointy;
			}
			
			if(pointx<XMin){
				XMin=pointx;
			}
			if(pointx>XMax){
				XMax=pointx;
			}
			p.draw(pen_t(color_t(0.5,0.5,0.5),1));
			//std::cout<<" let me pass!!! I am the point "<<pointx<<" and "<<pointy<<std::endl;
			fmmQueue.push(point_t(pointx+1,pointy));
			fmmQueue.push(point_t(pointx,pointy+1));
			fmmQueue.push(point_t(pointx-1,pointy));
			fmmQueue.push(point_t(pointx,pointy-1));
			// fmmQueue.push(point_t(pointx+1,pointy+1));
			// fmmQueue.push(point_t(pointx-1,pointy-1));
			// fmmQueue.push(point_t(pointx+1,pointy-1));
			// fmmQueue.push(point_t(pointx-1,pointy+1));
		}
	}
}
    


void fill_t::checkerboard_fill(point_t p,float width,float height){
	int minx=p.getX();
	int miny=p.getY();
	int maxx=p.getX();
	int maxy=p.getY();
	find_min_max(p,miny,maxy,minx,maxx,width,height);

	std::queue <point_t> fillQueue;
	fillQueue.push(p);
	float pointx=p.getX();
	float pointy=p.getY();
	color_t c=colorArray[(int)pointx][(int)pointy];
	
    color_t pixels;
    float trans_x,trans_y;
    while(!fillQueue.empty()){
    	// std::cout<<c.getR()<<" ANSSS"<<std::endl;
    	// exit(0);
		p=fillQueue.front();
		pointx=p.getX();
		pointy=p.getY();
		fillQueue.pop();
		
		//Added Canvas size check
		if(pointx>=width || pointy>=height || pointx<0 || pointy<0)
			continue;
		//glReadPixels(pointx,pointy,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
		pixels = colorArray[(int)pointx][(int)pointy];
		
		if( (pixels.getR()==c.getR()) && (pixels.getG()==c.getG()) && (pixels.getB()==c.getB()) )
		{
			point_t p1(pointx, pointy);
			trans_x=pointx-minx;
			trans_y=pointy-miny;
			if((((int)trans_x/16)%2)==0){
				if((((int)trans_y/16)%2)==0){
					p1.draw(pen_t(color1,1));
				}
				else{
					p1.draw(pen_t(color2,1));
				}
			}
			else{
				if((((int)trans_y/16)%2)==0){
					p1.draw(pen_t(color2,1));
				}
				else{
					p1.draw(pen_t(color1,1));
				}
			}
			
			
			fillQueue.push(point_t(pointx+1,pointy));
			fillQueue.push(point_t(pointx,pointy+1));
			fillQueue.push(point_t(pointx-1,pointy));
			fillQueue.push(point_t(pointx,pointy-1));
		}
		
	}
	
}

void fill_t::printPointColor(point_t p){
	std::cout<<"COLOR "<<colorArray[(int)p.getX()][(int)p.getY()].getR()<<std::endl;
}
	

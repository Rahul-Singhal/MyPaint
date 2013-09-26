#include "drawing_t.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>

void drawing_t::undo(){
	if(drawingOrder.size() == 0) return;
	else{
		int type = drawingOrder.back();
		drawingOrder.pop_back();
		if(type == LINE){
			lines.pop_back();
		}
		else if(type == POLYGON){
			polygons.pop_back();
		} 
		else if(type == FILLPOINT){
			fillColors.pop_back();
			points.pop_back();
		}
		else{
			points.pop_back();
			fillColors.pop_back();
			fillColors.pop_back();
		}
	}
}

void drawing_t::draw(float width,float height){
	//std::cout<<" hey thjkhjkhkjhetre kehkuhekuh   "<<drawingOrder.size()<<std::endl;
	int lineCounter, polygonCounter, fillPointCounter, fillColorPointer;
	lineCounter = 0;
	polygonCounter = 0;
	fillPointCounter = 0;
	fillColorPointer = 0;
	std::vector<int>::iterator it;

	for(it = drawingOrder.begin(); it!=drawingOrder.end(); ++it){
		//std::cout<<*it<<" hey thetre kehkuhekuh"<<std::endl;
		if(*it == LINE){
			lines[lineCounter++].draw();
		}
		else if(*it == POLYGON){
			polygons[polygonCounter++].draw();
		}
		else if(*it == FILLPOINT){
			//std::cout<<*it<<" yippeeeeeeeee!!!    "<<fillColors.size()<<std::endl;
			fillObject.setFillMode(1);
			fillObject.setColor1(fillColors[fillColorPointer++]);
			fillObject.draw(points[fillPointCounter++],width,height);
		}
		else{
			fillObject.setFillMode(2);
			fillObject.setColor1(fillColors[fillColorPointer++]);
			fillObject.setColor2(fillColors[fillColorPointer++]);
			fillObject.draw(points[fillPointCounter++],width,height);
		}

	}

	// for(int i = 0 ; i<lines.size(); i++){
	// 	//std::cout<<"hey bhagwaaan!!  "<<lines[i].getR()<<std::endl;
	// 	lines[i].draw();
	// }
	// for(int i = 0 ; i<polygons.size(); i++){
	// 	polygons[i].draw();
	// }

	// for(int i = 0 ; i<points.size(); i++){
	// 	std::cout<<"yoness "<<std::endl;
	// 	std::cout<<"help!! "<<fillObject.getColor1().getB()<<std::endl;
	// 	fillObject.printPointColor(points[i]);
	// 	//exit(0);
	// 	fillObject.draw(points[i]);
	// }
	
}
void drawing_t::save(float w, float h, color_t bcolor){
	//std::cout<<"Enter the fileName: ";
	std::string fileName;
	std::cin>>fileName;
	char putStr[200];
	FILE * file;
	file = fopen(fileName.c_str(), "w");

	sprintf(putStr, "%f,%f,%f,%f,%f\n", w,h,bcolor.getR(),bcolor.getG(),bcolor.getB());
	fputs(putStr, file);

	int leng = drawingOrder.size();
	sprintf(putStr, "%d\n",leng);
	fputs(putStr, file);
	for(int i = 0 ; i<leng; i++){
		sprintf(putStr, "%d\n",drawingOrder[i]);
		fputs(putStr, file);
	}

	leng = lines.size();
	sprintf(putStr, "%d\n",leng);
	fputs(putStr, file);
	point_t start, end;
	color_t lineColor;
	float lineSize;

	for(int i = 0 ; i<leng; i++){
		//lines[i].getLineData(putString);
		start = lines[i].getStart();
		end = lines[i].getEnd();
		lineColor = lines[i].getColor();
		lineSize = lines[i].getSize();
		sprintf(putStr, "%f,%f,%f,%f,%f,%f,%f,%f\n", start.getX(), start.getY(), end.getX(),end.getY(), lineColor.getR(), lineColor.getG(), lineColor.getB(), lineSize);
		fputs(putStr, file);
	}
	// std::cout<<"yo boy!!"<<std::endl;
	// exit(0);
	leng = polygons.size();
	sprintf(putStr, "%d\n",leng);
	fputs(putStr, file);
	for(int i = 0 ; i<leng; i++){
		polygons[i].putDataInFile(file);
	}

	leng = points.size();
	sprintf(putStr, "%d\n",leng);
	fputs(putStr, file);
	for(int i = 0 ; i<leng; i++){
		sprintf(putStr, "%f,%f\n", points[i].getX(), points[i].getY());
		fputs(putStr, file);
	}

	leng = fillColors.size();
	sprintf(putStr, "%d\n",leng);
	fputs(putStr, file);
	for(int i = 0 ; i<leng; i++){
		sprintf(putStr, "%f,%f,%f\n",fillColors[i].getR(), fillColors[i].getG(), fillColors[i].getB());
		fputs(putStr, file);
	}

	fclose(file);


}
void drawing_t::load(FILE* & file){
	
	
	//read the drwaing order
	char getStr[200];
	drawingOrder.clear();
	int readOrder;
	float leng;
	fgets(getStr, 200, file);
	sscanf(getStr, "%f\n", &leng);
	for(int i = 0; i<leng; i++){
		fgets(getStr, 200, file);
		sscanf(getStr, "%d\n", &readOrder);
		drawingOrder.push_back(readOrder);
	}

	//read the lines
	lines.clear();
	fgets(getStr, 200, file);
	sscanf(getStr, "%f\n", &leng);
	float p1x, p1y, p2x, p2y, r,g,b,lineSize;
	for(int i = 0; i<leng; i++){
		fgets(getStr, 200, file);
		sscanf(getStr, "%f,%f,%f,%f,%f,%f,%f,%f\n", &p1x, &p1y, &p2x, &p2y, &r, &g, &b, &lineSize);

		lines.push_back(line_t(point_t(p1x,p1y), point_t(p2x,p2y), color_t(r,g,b), lineSize));
	}

	//read the polygons
	int l;
	polygons.clear();
	fgets(getStr, 200, file);
	sscanf(getStr, "%f\n", &leng);
	//sscanf(getStr, "%d,%f,%f,%f,%f\n", &leng, &r, &g, &b, lineSize);
	//sprintf(ch, "%d,%f,%f,%f,%f\n", l, border.getR(), border.getG(), border.getB(), size);
	for(int i = 0; i<leng; i++){
		fgets(getStr, 200, file);
		sscanf(getStr, "%d,%f,%f,%f,%f\n", &l, &r, &g, &b, &lineSize);
		polygon_t poly(pen_t(color_t(r,g,b),lineSize));
		for(int j = 0 ; j<l; j++){
			fgets(getStr, 200, file);
			sscanf(getStr, "%f,%f\n", &p1x, &p1y);
			poly.addPoint(point_t(p1x,p1y));
		}
		polygons.push_back(poly);
	}

	//read the fill points
	points.clear();
	fgets(getStr, 200, file);
	sscanf(getStr, "%f\n", &leng);
	for(int i = 0; i<leng; i++){
		fgets(getStr, 200, file);
		sscanf(getStr, "%f,%f\n", &p1x,&p1y);
		points.push_back(point_t(p1x,p1y));
	}
	//read the fillColors
	fillColors.clear();
	fgets(getStr, 200, file);
	//std::cout<<"last line "<<getStr<<std::endl;
	sscanf(getStr, "%f\n", &leng);
	for(int i = 0; i<leng; i++){
		fgets(getStr, 200, file);
		sscanf(getStr, "%f,%f,%f\n", &r, &g, &b);
		fillColors.push_back(color_t(r,g,b));
	}

	

	//exit(0);
	//scan the width and the heigth


}
drawing_t::drawing_t(){
}

void drawing_t::addToLines(line_t l){
	lines.push_back(l);
}
void drawing_t::addToPolygons(polygon_t p){
	polygons.push_back(p);
}
void drawing_t::addToPoints(point_t p, int mode, color_t c1, color_t c2){
	points.push_back(p);
	if(mode == 1){
		//std::cout<<"the last color added is "<<c1.getR()<<std::endl;
		drawingOrder.push_back(FILLPOINT);
		fillColors.push_back(c1);
	}
	else{
		drawingOrder.push_back(CHECKPOINT);
		fillColors.push_back(c1);
		fillColors.push_back(c2);
	}
	//fillObject.draw(p);
	//std::cout<<colorArray[(int)p.getX()][(int)p.getY()].getG()<<std::endl;
}

polygon_t & drawing_t::getLastPolygon(){
	polygons[polygons.size()-1];
}

void drawing_t::pushIntoQueue(int type){
	drawingOrder.push_back(type);
}

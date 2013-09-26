#include <cstdlib>
#include <iostream>
#include <string>
#include "drawing_t.h"
#include "polygon_t.h"
#include "canvas_t.h"
#include "pen_t.h"
#include "fill_t.h"
#include <GL/glut.h>
#include <vector>
using namespace std;

//enum elementType{ FILLPOINT = 1, LINE =  2, POLYGON = 3};

int numpoints=0;
float xx0,yy0,xx1,yy1;
int win_width = 1024;
int win_height = 768;
canvas_t myCanvas(win_width,win_height,color_t(1,1,1));
pen_t pen(color_t(0,0,0), 3);
fill_t fillObject;
bool clearScreen = true;


bool fillActive=false;

void render_bitmap_string(float x, float y, float z, void *font, const char *string) 
{  
  const char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) 
    {
      glutBitmapCharacter(font, *c);
    }
}

void display( void )
{
  if(clearScreen){
    glClear( GL_COLOR_BUFFER_BIT );
  }
  //cout<<"DISPLAY CALLED HJHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl;
    myCanvas.draw();
  glutSwapBuffers();
}

void reshape( int w, int h )
{
  if  ( h == 0 ) h = 1;

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  glOrtho( 0.0, (GLdouble)w, 0.0, (GLdouble)h, -1., 1. );
  glViewport( 0, 0, w, h );

  win_width = w;
  win_height = h;

  glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ) {
  float w,h,r,g,b, s;
  switch(key) {
  case 27: 
    exit(0);
    break;
  case 'z':
  case 'Z':
    (myCanvas.getDrawing()).undo();
    clearScreen = true;
    glutPostRedisplay();
    break;
  case 'D':
  case 'd':
    cout<<"clear it!!!"<<endl;
    myCanvas.clear();
    clearScreen = true;
    glutPostRedisplay();
    break;
  case 'n':
  case 'N': 
    cout<<"Enter the width of the canvas:";
    cin>>w;
    cout<<"Enter the height of the canvas:";
    cin>>h;
    cout<<"Enter the color of the canvas (ex. 1 1 0.5):";
    cin>>r>>g>>b;
    //cout<<r<<" and "<<g<<" and "<<b<<endl;
    myCanvas.setCanvas(w,h,color_t(r,g,b));
    glutPostRedisplay();
    //glClearColor(r, g, b, 1.0f);
    break;
  case 's':
  case 'S':
    //save the image
    myCanvas.save();
    break;
  case '1':
    if(pen.getMode() == 1 && pen.isEraser()) { pen.setMode(1); return;}
    else if(pen.getMode() == 1) return;
    if(pen.getMode() == 2 && numpoints >= 3){
    	//cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<endl;
    	polygon_t & poly = (myCanvas.getDrawing()).getLastPolygon();
      clearScreen = true;
      (myCanvas.getDrawing()).pushIntoQueue(POLYGON);
    	// point_t q;
    	// //cout<<xx0<<" and the other point is " <<yy0<<endl;
    	// q.setX(xx0);
    	// q.setY(yy0);
    	// point_t p2 = poly.getFirstVertex();
    	// //cout<<"for the other point "<<p2.getX()<<"  and "<<p2.getY()<<endl;
    	// //cout<<"look at me now "<<pen.getColor().getR()<<" and "<<pen.getColor().getG()<<endl;
    	// line_t l(p2,q,pen);
    	// l.draw();
      glutPostRedisplay();
    }
    numpoints = 0;

    cout<<"line mode activated!!"<<endl;
    pen.setMode(1);
  break;
  case '2':
    if(pen.getMode() == 2) break;
    cout<<"polygon mode activated"<<endl;
    numpoints = 0;
    pen.setMode(2);
    break;
  case '3':
    cout<<"eraser mode activated"<<endl;
    numpoints = 0;
    cout<<"Enter the size of the eraser: ";
    cin>>s;
    pen.setModeToEraser(myCanvas.getColor(),s);
  break;
  case 'c':
  case 'C':
    if(!fillActive){
      cout<<"Change pen attributes:"<<endl<<endl;
      cout<<"Enter the pen color <R G B>:"<<endl;
      cin>>r>>g>>b;
      pen.setColor(color_t(r,g,b));
      cout<<"Enter the pen size in pixels:"<<endl;
      cin>>s;
      pen.setSize(s);
    }
    else{
      int modeIn;
      cout<<"Change fill attributes:"<<endl<<endl;
      cout<<"Press 1 for 'solid' fill mode and 2 for 'checkBoard' fill mode:";
      cin>>modeIn;
      if(modeIn == 1){
        //get solid fill attributes
        cout<<"Enter the fill color <R G B>"<<endl;
        cin>>r>>g>>b;
        //TODO
        fillObject.setFillMode(1);
        fillObject.setColor1(color_t(r,g,b));
        cout<<"fill attributes modified!"<<endl;
      }
      else{
        fillObject.setFillMode(2);
        cout<<"Enter the color 1 for checkBoard fill <R G B>"<<endl;
        cin>>r>>g>>b;
        fillObject.setColor1(color_t(r,g,b));
        cout<<"Enter the color 2 for checkBoard fill <R G B>"<<endl;
        cin>>r>>g>>b;
        fillObject.setColor2(color_t(r,g,b));
        cout<<"fill attributes modified!"<<endl;
      }
    }
    break;
  case 'F':
  case 'f':
    if(fillActive){
      cout<<"Fill mode deactivated"<<endl;
      fillActive = false;
    }
    else{
      cout<<"Fill mode activated"<<endl;
      fillActive = true;
    }
    break;
  case 'l':
  case 'L':
    myCanvas.load();
    // clearScreen = true;
    glutPostRedisplay();
    break;
  default:
    break;
  }
  
}

void mouse(int button, int state, int x, int y) 
{
  //cout<<x<<" and "<<y<<endl;
   point_t p,q;
   clearScreen = false;
   int temp = 0;
   
   //glColor3f(1,1,0);
   if (state == GLUT_DOWN)
   	{
   		if (button == GLUT_LEFT_BUTTON){
        if(fillActive){
          fillActive = false;
          
          //fillObject.setPointColor()
          //cout<<x<<" and "<<y<<endl;
          //exit(0);
          
          clearScreen = true;
          if(fillObject.getFillMode()==1){
            //cout<<"fill me now "<<fillObject.getColor1().getR()<<endl;
            //(myCanvas.getDrawing()).pushIntoQueue(FILLPOINT);
            (myCanvas.getDrawing()).addToPoints(point_t(x,win_height-y), 1, fillObject.getColor1(), fillObject.getColor2());
          }
          else{
            //(myCanvas.getDrawing()).pushIntoQueue(CHECKPOINT);
            (myCanvas.getDrawing()).addToPoints(point_t(x,win_height-y), 2, fillObject.getColor1(), fillObject.getColor2()); 
          }
          //std::cout<<"jahahjahjahjhajahj  "<<myCanvas.myFunc(x,win_height-y)<<std::endl;
          //exit(0);
          //cout<<"hahahah "<<endl;
          temp = 1;
          //cout<<"rediplay number 1"<<endl;
          glutPostRedisplay();

        }
   			else if(pen.getMode()==1){

   				if ((numpoints % 2 )== 0)
   				{
             
			         numpoints = 0;
			         xx0 = x;
			         yy0 = win_height - y;
			         p.setX(xx0);
			         p.setY(yy0);
               //cout<<"look at me NOWWWW "<<pen.getColor().getG()<<endl;
			         p.draw(pen);
			         numpoints++;
               //cout<<"rediplay number 2"<<endl;
               clearScreen = false;
               glutPostRedisplay();
               //clearScreen = false;
			    }
			    else
			    {  

                //cout<<"draw line"<<endl;
			         xx1 = x;
			         yy1 =  win_height - y;
			         numpoints++;
			         q.setX(xx1);
			         q.setY(yy1);
		             p.setX(xx0);
		            p.setY(yy0);
			         q.draw(pen);
               //cout<<pen.getColor.getR()<<"  hjkhkh "<<endl;
			         line_t l(p,q,pen);
               //cout<<"line added!!"<<endl;
			         (myCanvas.getDrawing()).addToLines(l);
               clearScreen = true;
               (myCanvas.getDrawing()).pushIntoQueue(LINE);
               //cout<<"rediplay number 3"<<endl;
               glutPostRedisplay();
			         //l.draw();
			    }
			}

      else if(pen.getMode()==2){

        	if(numpoints == 0){
        		xx0 = x;
		         yy0 = win_height - y;
		         p.setX(xx0);
		         p.setY(yy0);
		         p.draw(pen);
		         numpoints++;
		         polygon_t poly(pen);
		         poly.addPoint(p);
		         (myCanvas.getDrawing()).addToPolygons(poly);
             //cout<<"rediplay number 4"<<endl;
             glutPostRedisplay();
             //clearScreen = false;
        	}
        	else{
        		xx1 = x;
		         yy1 =  win_height - y;
		         numpoints++;
		         q.setX(xx1);
		         q.setY(yy1);
	             p.setX(xx0);
	             p.setY(yy0);
		         q.draw(pen);
		         //cout<<"here I am"<<endl;
		         line_t l(p,q,pen);
		         l.draw();
		         xx0 = xx1;
		         yy0 = yy1;
		         ((myCanvas.getDrawing()).getLastPolygon()).addPoint(q);
             //cout<<"rediplay number 5"<<endl;
             glutPostRedisplay();
             //clearScreen = false;
        	}
        }
        
		}
	}
	//cout<<"OUT"<<endl;
  //cout<<pen.getMode()<<" hjkdehkhkehk "<<numpoints<<endl;

}       


int main (int argc, char *argv[]) 
{

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  float r,g,b;
  cout<<"Enter the background color of canvas:";
  cin>>r>>g>>b;
  glutInitWindowSize( win_width, win_height );

  glutCreateWindow( "Graphics Assignment 1" );
  glClearColor(r,g,b, 1.0f);
  pen.setMode(1);

  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutMouseFunc( mouse );
  //glClear( GL_COLOR_BUFFER_BIT );
  glutMainLoop();
}

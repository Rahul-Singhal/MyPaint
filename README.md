MyPaint
=======

An interface created in openGL to provide user similar functionality as that provided by ms-paint.

CONTENTS:
----------------------
1. This tar archive contains following files:
	a. pen_t.h & pen_t.cpp
	b. line_t.h & line_t.cpp
	c. fill_t.h & fill_t.cpp 
	d. color_t.h & color_t.cpp
	e. canvas_t.h & canvas_t.cpp
	f. drawing_t.h & drawing_t.cpp
	g. point_t.h & point_t.cpp
	h. polygon_t.h & polygon_t.cpp 
	i. main.cpp
	j. README
	k. finalRoomImage

HOW TO RUN:
------------------------
1. Extract the archive and change the directory into that folder.
2. Run the following command to compile the source files:
	"g++ -c *.h -lGL -lGLU -lglut"
	"g++  *.cpp -lGL -lGLU -lglut -o main"
3. This will create a binary named "main" in the current folder.
4. Run the binary using the command "./main"


INSTRUCTIONS:
------------------------
1.There are three pen modes:
	1. line mode: use key '1' to activate this mode. 
	2. polygon mode: use key '2' to activate this mode. When you are done making the polygon, press '1', this will complete the polygon and activate the line mode.
	3. eraser mode
2. Rest implementation is same as that given in the problem statement. Follow the instructions given on the terminal when 	creating a keyboard event.
3. Save the drawing using the key 's' and give the file name on terminal. This will save the drawing in that file.
4. To load a file, open a new drawing i.e run the main binary, press load and give the file name on the terminal.


ADDITIONAL IMPLEMENTATION:
---------------------------
1. We have implemented "UNDO" functionality in our program. The key to be pressed for undo is 'z'.

KEYS TO USE
---------------------------
(a) ’N’ : Initialize a new canvas, including all elements of the 2D array to the background color. Assume that the size of canvas is equal
to the size of your window (and is fixed). Take the background color for the canvas as input from the terminal or an initial config
file.
(b) ’D’ : Initialize a new drawing.
(c) ’S/L’ : Save/Load drawing. For load, input filename on terminal.
(d) ’1’: Toggle Line drawing mode. Left clicking on the drawing line should draw a line between two successively clicked points, with
the current pen.
(e) ’2’: Toggle Polygon drawing mode. Left clicking on the drawing line should draw a line between two successively clicked points,
with the current pen.
(f) ’F’: Toggle Fill mode. Left clicking anywhere in the drawing now fills that bounded region with current fill color and type. When
this mode is on, you will draw the 2D array to the screen. Read chapter 8 in the OpenGL programming guide on “Drawing Pixels,
Bitmaps, Fonts, and Images” to figure out how to draw a array to the screen. Remember to set your coordinate system properly
(see examples in the chapter mentioned above). When fill mode is off, directly draw only the lines and polygon boundaries to the
screen using the corresponding draw functions.
(g) ’C’: If fill mode is active, pressing ’C’ must let you change the current fill type and colors, else it should let you change the
attributes of the pen.
(h) ’Esc’: Exit the program.


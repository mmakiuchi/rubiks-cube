
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
//#include <GL/gl.h>

#include <math.h>
#include <iostream>
#include <map>


/* PI */
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif


void drawSphere(double r, int lats, int longs) {
	int i, j;
	for(i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
		double z0  = r * sin(lat0);
		double zr0 = r *  cos(lat0);

		double lat1 = M_PI * (-0.5 + (double) i / lats);
		double z1  = r * sin(lat1);
		double zr1 = r * cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double) (j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f((GLfloat)(x * zr0), (GLfloat)(y * zr0), (GLfloat)z0);
			glVertex3f((GLfloat)(x * zr0), (GLfloat)(y * zr0), (GLfloat)z0);
			glNormal3f((GLfloat)(x * zr1), (GLfloat)(y * zr1), (GLfloat)z1);
			glVertex3f((GLfloat)(x * zr1), (GLfloat)(y * zr1), (GLfloat)z1);
		}
		glEnd();
	}
}


void solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
	glBegin(GL_LINE_LOOP);
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);

	gluCylinder(quadric, base, 0, height, slices, stacks);

	gluDeleteQuadric(quadric);
	glEnd();
}

// Added in Exercise 9 - Start *****************************************************************
void drawCube(std::array<std::array<int, 4>, 6> & cube_facelet)
{
	float max_vertex = 0.01; //defines the size of the cube

	// definition of openGL colors
	float yellow[] = { 1.0, 1.0, 0.0 };
	float blue[] = { 0.0, 0.0, 1.0 };
	float red[] = { 1.0, 0.0, 0.0 };
	float white[] = { 1.0, 1.0, 1.0 };
	float green[] = { 0.0, 1.0, 0.0 };
	float orange[] = { 1.0, 0.5, 0.0 };

	std::map<int, float*> colorLookupTable;

	//lookup table to correlate the cube_facelet mapping with the colors
	colorLookupTable[0] = yellow;
	colorLookupTable[1] = blue;
	colorLookupTable[2] = red;
	colorLookupTable[3] = white;
	colorLookupTable[4] = green;
	colorLookupTable[5] = orange;

	/// Draw the black lines of rubik's cube
	// Draw corners
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(max_vertex, max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, -max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, -max_vertex);
	glVertex3f(-max_vertex, max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, -max_vertex);
	glVertex3f(max_vertex, -max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(max_vertex, -max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, -max_vertex);
	glVertex3f(max_vertex, -max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, -max_vertex);
	glVertex3f(-max_vertex, max_vertex, -max_vertex);
	glEnd();

	// Lines of upper side
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, -max_vertex, -max_vertex);
	glVertex3f(0, max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, 0, -max_vertex);
	glVertex3f(-max_vertex, -0, -max_vertex);
	glEnd();

	// Lines of Side A
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, 0, -max_vertex);
	glVertex3f(max_vertex, 0, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, 0);
	glVertex3f(max_vertex, -max_vertex, 0);
	glEnd();

	// Lines of side B
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, max_vertex, -max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, 0);
	glVertex3f(-max_vertex, max_vertex, 0);
	glEnd();

	// Lines of side C
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, 0);
	glVertex3f(-max_vertex, max_vertex, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, 0, max_vertex);
	glVertex3f(-max_vertex, 0, -max_vertex);
	glEnd();

	// Lines of side D
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, -max_vertex, -max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, -max_vertex, 0);
	glVertex3f(-max_vertex, -max_vertex, 0);
	glEnd();

	// Lines of the bottom
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glEnd();

	/// DRAW THE SIDES OF THE CUBE
	// Upper side (facelet 2)
	glBegin(GL_POLYGON);
	glColor3f(white[0], white[1], white[2]);
	glVertex3f(max_vertex, 0, -max_vertex);
	glVertex3f(max_vertex, max_vertex, -max_vertex);
	glVertex3f(0, max_vertex, -max_vertex);
	glVertex3f(0, 0, -max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(red[0], red[1], red[2]);
	glVertex3f(0, 0, -max_vertex);
	glVertex3f(0, max_vertex, -max_vertex);
	glVertex3f(-max_vertex, max_vertex, -max_vertex);
	glVertex3f(-max_vertex, 0, -max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(yellow[0], yellow[1], yellow[2]);
	glVertex3f(-max_vertex, 0, -max_vertex);
	glVertex3f(0, 0, -max_vertex);
	glVertex3f(0, -max_vertex, -max_vertex);
	glVertex3f(-max_vertex, -max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex3f(0, 0, -max_vertex);
	glVertex3f(max_vertex, 0, -max_vertex);
	glVertex3f(max_vertex, -max_vertex, -max_vertex);
	glVertex3f(0, -max_vertex, -max_vertex);
	glEnd();

	// Side A (facelet 0)
	glBegin(GL_POLYGON);
	glColor3f(yellow[0], yellow[1], yellow[2]);
	glVertex3f(max_vertex, -max_vertex, -max_vertex);
	glVertex3f(max_vertex, 0, -max_vertex);
	glVertex3f(max_vertex, 0, 0);
	glVertex3f(max_vertex, -max_vertex, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(red[0], red[1], red[2]);
	glVertex3f(max_vertex, 0, -max_vertex);
	glVertex3f(max_vertex, max_vertex, -max_vertex);
	glVertex3f(max_vertex, max_vertex, 0);
	glVertex3f(max_vertex, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(green[0], green[1], green[2]);
	glVertex3f(max_vertex, -max_vertex, 0);
	glVertex3f(max_vertex, 0, 0);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(blue[0], blue[1], blue[2]);
	glVertex3f(max_vertex, 0, 0);
	glVertex3f(max_vertex, max_vertex, 0);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(max_vertex, 0, max_vertex);
	glEnd();

	// Side B (facelet 1)
	glBegin(GL_POLYGON);
	glColor3f(blue[0], blue[1], blue[2]);
	glVertex3f(0, max_vertex, 0);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(max_vertex, max_vertex, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(green[0], green[1], green[2]);
	glVertex3f(0, max_vertex, 0);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(white[0], white[1], white[2]);
	glVertex3f(0, max_vertex, 0);
	glVertex3f(max_vertex, max_vertex, 0);
	glVertex3f(max_vertex, max_vertex, -max_vertex);
	glVertex3f(0, max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(yellow[0], yellow[1], yellow[2]);
	glVertex3f(0, max_vertex, 0);
	glVertex3f(0, max_vertex, -max_vertex);
	glVertex3f(-max_vertex, max_vertex, -max_vertex);
	glVertex3f(-max_vertex, max_vertex, 0);
	glEnd();

	// Side C (facelet 5)
	glBegin(GL_POLYGON);
	glColor3f(red[0], red[1], red[2]);
	glVertex3f(-max_vertex, 0, 0);
	glVertex3f(-max_vertex, 0, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(yellow[0], yellow[1], yellow[2]);
	glVertex3f(-max_vertex, 0, 0);
	glVertex3f(-max_vertex, max_vertex, 0);
	glVertex3f(-max_vertex, max_vertex, -max_vertex);
	glVertex3f(-max_vertex, 0, -max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(white[0], white[1], white[2]);
	glVertex3f(-max_vertex, 0, 0);
	glVertex3f(-max_vertex, -max_vertex, 0);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex3f(-max_vertex, 0, 0);
	glVertex3f(-max_vertex, 0, -max_vertex);
	glVertex3f(-max_vertex, -max_vertex, -max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 0);
	glEnd();

	// Side D (facelet 3)
	glBegin(GL_POLYGON);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex3f(0, -max_vertex, 0);
	glVertex3f(0, -max_vertex, max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(max_vertex, -max_vertex, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(blue[0], blue[1], blue[2]);
	glVertex3f(0, -max_vertex, 0);
	glVertex3f(max_vertex, -max_vertex, 0);
	glVertex3f(max_vertex, -max_vertex, -max_vertex);
	glVertex3f(0, -max_vertex, -max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(red[0], red[1], red[2]);
	glVertex3f(0, -max_vertex, 0);
	glVertex3f(-max_vertex, -max_vertex, 0);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(white[0], white[1], white[2]);
	glVertex3f(0, -max_vertex, 0);
	glVertex3f(0, -max_vertex, -max_vertex);
	glVertex3f(-max_vertex, -max_vertex, -max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 0);
	glEnd();

	// Bottom (facelet 4)
	glBegin(GL_POLYGON);
	glColor3f(green[0], green[1], green[2]);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(max_vertex, 0, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(green[0], green[1], green[2]);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(blue[0], blue[1], blue[2]);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glEnd();
}
// Added in Exercise 9 - End *****************************************************************

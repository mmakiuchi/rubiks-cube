
#define GLFW_INCLUDE_GLU
#if __APPLE__
#include <GLFW/glfw3.h>
#else
#include <glfw3.h>
#endif
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

void showCube(std::array<std::array<int, 4>, 6>& cube_facelet, int n1, int n2, int n3, int n4, int n5, int n6){

	float max_vertex = 0.015; //defines the size of the cube

// definition of openGL colors
	float yellow[] = { 1.0, 1.0, 0.0 };
	float blue[] = { 0.0, 0.0, 1.0 };
	float red[] = { 1.0, 0.0, 0.0 };
	float white[] = { 1.0, 1.0, 1.0 };
	float green[] = { 0.0, 1.0, 0.0 };
	float orange[] = { 1.0, 0.5, 0.0 };

	std::map<int, float*> colorLookupTable;
	int color_index;

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
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
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

	//
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, -max_vertex, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(-max_vertex, -0, max_vertex);
	glEnd();

	//
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, 2*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	//
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	//
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glEnd();

	//
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, -max_vertex, max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	//
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glEnd();


	/// DRAW THE SIDES OF THE CUBE
		// Upper side (facelet 2)
	glBegin(GL_POLYGON);
	// glColor3f(red[0], red[1], red[2]);
	color_index = cube_facelet[n1][0];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n1][1];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, max_vertex);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n1][2];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n1][3];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(0, 0, max_vertex);
	glEnd();


	// facelet 0
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n2][0];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(max_vertex, max_vertex, 2*max_vertex);
	glVertex3f(max_vertex, 0, 2*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n2][1];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, 0, 2* max_vertex);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n2][2];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, 0, 2* max_vertex);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n2][3];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, 0, 2* max_vertex);
	glVertex3f(max_vertex, max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glEnd();

	// facelet 1
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n3][0];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, max_vertex, 2* max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n3][1];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, max_vertex, 2* max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n3][2];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n3][3];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, max_vertex, 2* max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	// facelet 5
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n4][0];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, 2* max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n4][1];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n4][2];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, 2* max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n4][3];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, 2* max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glEnd();

	// facelet 3
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n5][0];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, -max_vertex, 2* max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n5][1];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, -max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n5][2];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, -max_vertex, 2* max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n5][3];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, -max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glEnd();

	// facelet 4
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n6][0];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, 3*max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n6][1];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, 3*max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n6][2];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, 3*max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n6][3];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, 3*max_vertex);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glEnd();
}

// Added in Exercise 9 - Start ****************************************************************
void drawCube(std::array<std::array<int, 4>, 6> & cube_facelet, Marker marker)
{
	int marker_code = marker.code;

	/// MARKERS CODES (on which marker the facelet is projected)
	// facelet 0				// facelet 4				// facelet 1
	// 0x272 = 626				// 0x690 = 1680				// 0xB44 = 2884
	// 0 0 0 0					// 0 0 0 0					// 0 0 0 0
	// 0 0 1 0					// 0 1 1 0					// 1 0 1 1
	// 0 1 1 1					// 1 0 0 1					// 0 1 0 0
	// 0 0 1 0					// 0 0 0 0					// 0 1 0 0
	
	// facelet 2				// facelet 3				// facelet 5
	// 0x5A = 90				// 0x1C44 =	7236			// 0x1228 = 4648
	// 0 0 0 0					// 0 0 0 1					// 0 0 0 1
	// 0 0 0 0					// 1 1 0 0					// 0 0 1 0
	// 0 1 0 1					// 0 1 0 0					// 0 0 1 0
	// 1 0 1 0					// 0 1 0 0					// 1 0 0 0

	float m_x, m_y, m_z;
	//same values printed with marker.print_matrix()
	m_x = marker.resultMatrix[1];
	m_y = marker.resultMatrix[6];
	m_z = marker.resultMatrix[11];

	if (marker_code == 90) {
		showCube(cube_facelet, 2, 0, 1, 5, 3, 4);
	} else if (marker_code == 626) {
		showCube(cube_facelet, 0, 3, 4, 1, 2, 5);
	} else if (marker_code == 1680) {
		showCube(cube_facelet, 4, 3, 5, 1, 0, 2);
	} else if (marker_code == 2884) {
		showCube(cube_facelet, 1, 0, 4, 5, 2, 3);
	} else if (marker_code == 7236) {
		showCube(cube_facelet, 3, 2, 5, 4, 0, 1);
	} else if (marker_code == 4648) {
		showCube(cube_facelet, 5, 2, 1, 4, 3, 0);
	}


}

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

void showCube(std::array<std::array<int, 4>, 6>& cube_facelet, std::array<int, 6> n, std::array<int, 6> r){

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
	color_index = cube_facelet[n[0]][(r[0]+0)%4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[0]][(r[0] + 1) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, max_vertex);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[0]][(r[0] + 2) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, max_vertex);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[0]][(r[0] + 3) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(0, 0, max_vertex);
	glEnd();


	// facelet 0
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[1]][(r[1] + 0) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(max_vertex, max_vertex, 2*max_vertex);
	glVertex3f(max_vertex, 0, 2*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[1]][(r[1] + 1) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(max_vertex, 0, max_vertex);
	glVertex3f(max_vertex, 0, 2* max_vertex);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[1]][(r[1] + 2) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, 0, 2* max_vertex);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[1]][(r[1] + 3) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(max_vertex, 0, 2* max_vertex);
	glVertex3f(max_vertex, max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glEnd();

	// facelet 1
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[2]][(r[2] + 0) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, max_vertex, 2* max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[2]][(r[2] + 1) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, max_vertex, 2* max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[2]][(r[2] + 2) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, max_vertex, max_vertex);
	glVertex3f(0, max_vertex, max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[2]][(r[2] + 3) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, max_vertex, 2* max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	// facelet 5
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[3]][(r[3] + 0) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, 2* max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[3]][(r[3] + 1) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[3]][(r[3] + 2) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, 2* max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[3]][(r[3] + 3) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(-max_vertex, 0, 2* max_vertex);
	glVertex3f(-max_vertex, max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, max_vertex, max_vertex);
	glVertex3f(-max_vertex, 0, max_vertex);
	glEnd();

	// facelet 3
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[4]][(r[4] + 0) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, -max_vertex, 2* max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[4]][(r[4] + 1) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, -max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[4]][(r[4] + 2) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, -max_vertex, 2* max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[4]][(r[4] + 3) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, -max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, -max_vertex, 2* max_vertex);
	glVertex3f(max_vertex, -max_vertex, max_vertex);
	glVertex3f(0, -max_vertex, max_vertex);
	glEnd();

	// facelet 4
	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[5]][(r[5] + 0) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, 3*max_vertex);
	glVertex3f(0, -max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, -max_vertex, 3*max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[5]][(r[5] + 1) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, 3*max_vertex);
	glVertex3f(-max_vertex, 0, 3*max_vertex);
	glVertex3f(-max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[5]][(r[5] + 2) % 4];
	glColor3f(colorLookupTable[color_index][0], colorLookupTable[color_index][1], colorLookupTable[color_index][2]);
	glVertex3f(0, 0, 3*max_vertex);
	glVertex3f(0, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, max_vertex, 3*max_vertex);
	glVertex3f(max_vertex, 0, 3*max_vertex);
	glEnd();

	glBegin(GL_POLYGON);
	color_index = cube_facelet[n[5]][(r[5] + 3) % 4];
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

	std::array<int, 6> n;
	std::array<int, 6> r;
	if (marker_code == 626) {
		n = { 0, 3, 4, 1, 2, 5 };
		r = { 3, 2, 1, 0, 3, 0 };
	} else if (marker_code == 2884) {
		n = {1, 0, 4, 5, 2, 3};
		r = { 0, 3, 0, 1, 0, 0 };
	} else if (marker_code == 90) {
		n = { 2, 0, 1, 5, 3, 4 };
		r = { 0, 0, 0, 0, 0, 0 };
	} else if (marker_code == 7236) {
		n = { 3, 2, 5, 4, 0, 1 };
		r = { 1, 1, 0, 1, 2, 0 };
	} else if (marker_code == 1680) {
		n = { 4, 3, 5, 1, 0, 2 };
		r = { 1, 1, 3, 1, 3, 0 };
	} else if (marker_code == 4648) {
		n = { 5, 2, 1, 4, 3, 0 };
		r = { 0, 0, 3, 2, 1, 0 };
	} else {
		return;
	}

	showCube(cube_facelet, n, r);

}

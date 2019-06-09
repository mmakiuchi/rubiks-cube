#define GLFW_INCLUDE_GLU
#define GLFW_DLL

#if __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#if __APPLE__
  #include <GLFW/glfw3.h>
#else 
  #include <glfw3.h> //changed directory
  #include <freeglut.h> //added here to work with Windows (please comment)
#endif
//#include <GL/glew.h>

#include <iostream>
#include <iomanip>
#include <opencv2/core.hpp>    // include OpenCV core headers
#include <opencv2/imgproc.hpp> // include image processing headers
#include <opencv2/highgui.hpp> // include GUI-related headers

#include "PoseEstimation.h"
#include "MarkerTracker.h"
#include "DrawPrimitives.h"
#include "Cube.h"

//#define _USE_MATH_DEFINES
//#include <cmath>

#define MARKER_SIZE 0.048 // size of AR marker [m]

// change here for your PC configuration
//#define SCALE 0.45 //Mari
//#define THRESH 138 // Mari
//#define BW_THRESH 146 // Mari
#define SCALE 0.3 // for OSX
#define THRESH 87   // threshold for finding contours
#define BW_THRESH 95    // threshold for getting values of AR marker

// Added in Exercise 9 - Start *****************************************************************

struct Position { double x, y, z; };

bool debugmode = false;
bool balldebug = false;

int towards = 0x005A;
int towardsList[2] = { 0x005a, 0x0272 };
int towardscounter = 0;
Position ballpos;
int ballspeed = 100;
// Added in Exercise 9 - End *****************************************************************

//camera settings
#if __APPLE__
const int camera_width = 1280;
const int camera_height = 720;
#else
const int camera_width = 640;
const int camera_height = 480;
#endif

const int virtual_camera_angle = 30;
unsigned char bkgnd[camera_width * camera_height * 3];

void InitializeVideoStream(cv::VideoCapture& camera) {
	if (camera.isOpened())
		camera.release();

	camera.open(0); // open the default camera
	if (camera.isOpened() == false) {
		std::cout << "No webcam found, using a video file" << std::endl;
		camera.open("MarkerMovie.mpg");
		if (camera.isOpened() == false) {
			std::cout << "No video file found. Exiting." << std::endl;
			exit(0);
		}
	}
}

/* program & OpenGL initialization */
void initGL(int argc, char* argv[])
{
	// initialize the GL library
	// Added in Exercise 8 - End *****************************************************************
		// pixel storage/packing stuff
	glPixelStorei(GL_PACK_ALIGNMENT, 1);// for glReadPixels
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // for glTexImage2D
	glPixelZoom(1.0, -1.0);
	// Added in Exercise 8 - End *****************************************************************
		// enable and set colors
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0, 0, 0, 1.0);

	// enable and set depth parameters
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	// light parameters
	GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat light_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_dif[] = { 0.7f, 0.7f, 0.7f, 1.0f };

	// enable lighting
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void printMatrix(float matrix[]){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << std::setw(6);
            std::cout << std::setprecision(4);
            std::cout << matrix[4 * i + j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int calcState(float tan_t){
    if( -M_PI_4 <= tan_t && tan_t < M_PI_4){
        return 0;
    }else if(M_PI_4 <= tan_t && tan_t < M_PI*3/4){
        return 1;
    }else if(-M_PI*3/4 <= tan_t && tan_t < -M_PI_4){
        return 3;
    }else{
        return 2;
    }
}

void detectRotation(std::vector<Marker> & markers, int code, int state[]){
    for (int i = 0; i < markers.size(); i++) {
        float resultMatrix[16];
        if(markers[i].code == code){
            state[1] = state[0];
            for (int j = 0; j < 16; j++)
                resultMatrix[j] = markers[i].resultMatrix[j];
            
//            printMatrix(resultMatrix);
            
            float cos_t = resultMatrix[0];
            float sin_t = resultMatrix[4];
            float tan_t = atan2(sin_t, cos_t);
//            std::cout << tan_t << std::endl;
            
            state[0] = calcState(tan_t);
            
//            std::cout << std::hex << std::uppercase <<code << ": [" << state[0] << ", " << state[1] << "]" << std::endl;
        }
    }
}

void display(GLFWwindow * window, const cv::Mat & img_bgr, std::vector<Marker> & markers, std::array<std::array<int, 4>, 6> & cube_facelet)
{
	const auto camera_image_size = sizeof(unsigned char) * img_bgr.rows * img_bgr.cols * 3;
	auto background_buffer_size = sizeof(bkgnd);
	memcpy(bkgnd, img_bgr.data, background_buffer_size);

	int width0, height0;
	glfwGetFramebufferSize(window, &width0, &height0);
	//	reshape(window, width, height);

		// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw background image
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, camera_width, 0.0, camera_height);

	glRasterPos2i(0, camera_height - 1);
#if __APPLE__
	glDrawPixels(camera_width, camera_height, GL_BGR, GL_UNSIGNED_BYTE, bkgnd);
#else
	glDrawPixels(camera_width, camera_height, GL_BGR_EXT, GL_UNSIGNED_BYTE, bkgnd);
#endif


	glPopMatrix();

	glEnable(GL_DEPTH_TEST);

	//	return;

		// move to marker-position
	glMatrixMode(GL_MODELVIEW);

	// Added in Exercise 9 - Start *****************************************************************
	
	float scale = SCALE;
	for (int i = 0; i < markers.size(); i++) {
		const int code = markers[i].code;
        
		float resultMatrix[16];
        std::array<GLfloat, 16> tmp;
        for (int j = 0; j < 16; j++)
			resultMatrix[j] = markers[i].resultMatrix[j];

		float resultTransposedMatrix[16];
		for (int x = 0; x < 4; ++x)
			for (int y = 0; y < 4; ++y)
				resultTransposedMatrix[x * 4 + y] = resultMatrix[y * 4 + x];

		resultTransposedMatrix[12] *= scale;
		resultTransposedMatrix[13] *= scale;

		glLoadMatrixf(resultTransposedMatrix);
		glTranslatef(0, 0, -0.015);
		drawCube(cube_facelet, markers.at(i));
	}

	
	// Added in Exercise 9 - End *****************************************************************

	// draw the cube only if there is an identified marker
	/*if (!markers.empty()) {
		// send the cube side colors and the identified marker
		glTranslatef(0, 0, -0.015);
		drawCube(cube_facelet, markers.at(markers.size() - 1));
	}*/
		
	// Added in Exercise 9 - Start *****************************************************************
	//rotateToMarker(resultMatrix_005A, resultMatrix_0272, 0x005a);

	//drawSnowman();

	//for (int x = 0; x < 4; ++x)
		//for (int y = 0; y < 4; ++y)
			//resultTransposedMatrix[x * 4 + y] = resultMatrix_0272[y * 4 + x];


	//glLoadMatrixf(resultTransposedMatrix);

	//rotateToMarker(resultMatrix_0272, resultMatrix_005A, 0x0272);

	//drawSnowman();

	int key = cv::waitKey(10);
	if (key == 27) exit(0);
	// Added in Exercise 9 - Start *****************************************************************
	else if (key == 100) debugmode = !debugmode;
	else if (key == 98) balldebug = !balldebug;
	// Added in Exercise 9 - End *****************************************************************

}

void reshape(GLFWwindow * window, int width, int height) {

	// set a whole-window viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// create a perspective projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, ((GLfloat)width / (GLfloat)height), 0.01, 100);

	// invalidate display
	//glutPostRedisplay();
}

int main(int argc, char* argv[]) {

	cv::VideoCapture cap;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	// initialize the window system
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(camera_width, camera_height, "Augmented Rubik's-cube", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Set callback functions for GLFW
	glfwSetFramebufferSizeCallback(window, reshape);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	int window_width, window_height;
	glfwGetFramebufferSize(window, &window_width, &window_height);
	reshape(window, window_width, window_height);

	glViewport(0, 0, window_width, window_height);

	// initialize the GL library
	initGL(argc, argv);

	// setup OpenCV
	cv::Mat img_bgr;
	InitializeVideoStream(cap);

	const double kMarkerSize = MARKER_SIZE;
	MarkerTracker markerTracker(kMarkerSize, THRESH, BW_THRESH);

	std::vector<Marker> markers;
	
	// define the model of the cube
	Cube cube_model;
	std::array<std::array<int, 4>, 6> facelet;

	// shuffle the cube model
	cube_model.shuffle();
	facelet = cube_model.toFacelet();
	
	// Prints the color representation
	cube_model.print();
    
    // states of controller
    int controller_506B[2] = {0, 0};
    int controller_37CE[2] = {0, 0};
    int controller_128F[2] = {0, 0};
	
	//	float resultMatrix[16];
		/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		markers.resize(0);
		/* Capture here */
		cap >> img_bgr;

		if (img_bgr.empty()) {
			std::cout << "Could not query frame. Trying to reinitialize." << std::endl;
			InitializeVideoStream(cap);
			cv::waitKey(1000); /// Wait for one sec.
			continue;
		}

		/* Track a marker */
		markerTracker.findMarker(img_bgr, markers);///resultMatrix);

//		cv::imshow("img_bgr", img_bgr);
//		cv::waitKey(10); /// Wait for one sec.

        // detect the rotation of the controller
        detectRotation(markers, 0x506b, controller_506B);
        detectRotation(markers, 0x37ce, controller_37CE);
        detectRotation(markers, 0x128f, controller_128F);
        
        // turn Left
        int rot_diff = controller_506B[0] - controller_506B[1];
        if(rot_diff == 1 || rot_diff == -3){
            cube_model.turnLeft(3);
        }else if(rot_diff == -1 || rot_diff == 3){
            cube_model.turnLeft(1);
        }
        
        rot_diff = controller_37CE[0] - controller_37CE[1];
        if(rot_diff == 1 || rot_diff == -3){
            cube_model.turnUp(3);
        }else if(rot_diff == -1 || rot_diff == 3){
            cube_model.turnUp(1);
        }
        
        rot_diff = controller_128F[0] - controller_128F[1];
        if(rot_diff == 1 || rot_diff == -3){
            cube_model.turnFront(3);
        }else if(rot_diff == -1 || rot_diff == 3){
            cube_model.turnFront(1);
        }
        
//        cube_model.print();
        facelet = cube_model.toFacelet();
        
		/* Render here */
		display(window, img_bgr, markers, facelet);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;

}



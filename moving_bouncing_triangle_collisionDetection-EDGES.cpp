//
//
//
//
//
#include <windows.h>
#include <GL/glut.h>
#include <Math.h>
#define PI 3.14159265f

GLfloat triRadius = 0.04f;  //radius of the fan function
GLfloat triX = 900;		// first position of the triangle or object depends on the  	//number of numSegments used..
GLfloat triY = 800;
GLfloat triXMax, triXMin, triYMax, triYMin;  //x y parametreleri
GLfloat xSpeed = 0.004f;		//speed
GLfloat ySpeed = 0.004f;
int refreshMillis = 1;  //refresh period in miliseconds if it's too much it will move slowly

// projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

void initGL() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

}

// callback handler for window re-point event
void display() {
	glClear(GL_COLOR_BUFFER_BIT); //CLEAR THE COLOR BUFFER
	glMatrixMode(GL_MODELVIEW); // to operate on model view matrix
	glLoadIdentity();		// reset moldeview matrix

	glTranslatef(triX, triY, 0.0f); // translate to xpos y pos

	glBegin(GL_TRIANGLE_FAN); // use triangular segments to form circle
	glColor3f(0.1f, 0.4f, 0.0f); //blue color
	glVertex2f(0.0f, 0.0f);	//center points
	int numSegments = 3;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) { //last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments; //360 degree for all segments
		glVertex2f(cos(angle) *triRadius, sin(angle)*triRadius);
	}
	glEnd();

	glutSwapBuffers(); //swap buffers

	//animation control
	triX += xSpeed;
	triY += ySpeed;

	//check if the ball exceeds the edges

	if (triX > triXMax) {
		triX = triXMax;
		xSpeed = -xSpeed;
	}
	else if (triX < triXMin) {
		triX = triXMin;
		xSpeed = -xSpeed;
	}
	if (triY > triYMax) {
		triY = triYMax;
		ySpeed = -ySpeed;
	}
	else if (triY < triYMin) {
		triY = triYMin;
		ySpeed = -ySpeed;
	}
}

//call back when the windows is resized
void reshape(GLsizei width, GLsizei height) {
	//compute aspect ratio of the windows
	if (height == 0) height = 1;			//to prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION); //to operate on the projection matrix
	glLoadIdentity();			//reset the proj matrix
	if (width >= height) {
		clipAreaXLeft = -1.0 *aspect;
		clipAreaXRight = 1.0 *aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}
	else {
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0 / aspect;
	}
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	triXMin = clipAreaXLeft + triRadius;
	triXMax = clipAreaXRight - triRadius;
	triYMin = clipAreaYBottom + triRadius;
	triYMax = clipAreaYTop - triRadius;

}
// called back when the timer expired 
void Timer(int value) {
	glutPostRedisplay(); //post a plant request to activate display
	glutTimerFunc(refreshMillis, Timer, 0);		//subsequent timer call at milis
}

int windowWidth = 600;
int windowHeight = 900;
int windowPosX = 0; // top left corner
int windowPosY = 0;

// maint function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); //enable double buffer mode
	glutInitWindowSize(windowWidth, windowHeight); // initial window width and height
	glutInitWindowPosition(windowPosX, windowPosY); //top left corner
	glutCreateWindow("bouncing triangle to infinity and beyond");
	glutDisplayFunc(display);	//register callback
	glutReshapeFunc(reshape);

	glutTimerFunc(0, Timer, 0);	//timer call
	initGL();
	glutMainLoop();
	return 0;

}
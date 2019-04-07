#include <stdlib.h>
#include <math.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
// angle of rotation for the camera direction TODO
float angle = 90.0f;
float angle2 = 0.0f;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly=0.0f;

// XYZ position of the camera TODO
float x = -7.0f, z = 10.0f, y=1.0f;
float degreeXD = 0;
float degreeXD2 = 0;
float degreeXD3 = 0;
bool changeDegree = false;

float deltaAngle = 0.0f;
float deltaAngle2 = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
int yOrigin = -1;
float deltaDegree = 0.0f;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}
void computeDegree(float deltaDegree) {
	degreeXD3 += deltaDegree;
}
//tak naprawdê to nie xD (jest ¿ó³ty)
void kwadratCzerwony(float x, float y, float z, float size)
{
	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + size, y, z);
	glVertex3f(x+size, y, z + size);
	glVertex3f(x, y, z + size);
	glEnd();
}
//tak naprawdê to lekki ¿ó³ty
void kwadratNiebieski(float x, float y, float z, float size)
{
	glColor3f(1, 1, 0.9);
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + size, y, z);
	glVertex3f(x + size, y, z + size);
	glVertex3f(x, y, z + size);
	glEnd();
}
void szachownica(float x, float y, float z, float sizeOfSquare)
{
	float offsetX = 0;
	float offsetZ = 0;
	bool kolor;
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			kolor = true;
		}
		else
		{
			kolor = false;
		}
		for (int j = 0; j < 10; j++)
		{
			if (kolor)
			{
				kwadratCzerwony(x + offsetX, y, z + offsetZ, sizeOfSquare);
				kolor = false;
			}
			else {
				kwadratNiebieski(x + offsetX, y, z + offsetZ, sizeOfSquare);
				kolor = true;
			}
			offsetX += sizeOfSquare;
		}
		offsetZ += sizeOfSquare;
		offsetX = 0;
	}
}
void prostopadloscian(float x, float y, float z, float a, float b)
{
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x+a, y, z);
	glVertex3f(x + a, y, z+a);
	glVertex3f(x, y, z + a);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x, y+b, z);
	glVertex3f(x + a, y+b, z);
	glVertex3f(x + a, y+b, z + a);
	glVertex3f(x, y+b, z + a);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + a, y, z);
	glVertex3f(x + a, y+b, z);
	glVertex3f(x, y+b, z);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x, y, z+a);
	glVertex3f(x + a, y, z+a);
	glVertex3f(x + a, y + b, z+a);
	glVertex3f(x, y + b, z+a);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + a);
	glVertex3f(x, y + b, z + a);
	glVertex3f(x, y + b, z);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x+a, y, z);
	glVertex3f(x+a, y, z + a);
	glVertex3f(x+a, y + b, z + a);
	glVertex3f(x+a, y + b, z);
	glEnd();
}
void walec(float x, float y, float z, float r, float h)
{
	float cosDeg; // degree in Radians
	float sinDeg;
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 361; i++)
	{
		cosDeg = cos(3.1415 * 2 * i / 360);
		sinDeg = sin(3.1415 * 2 * i / 360);
		glVertex3f(x+r*cosDeg, y+r*sinDeg,z);
		glVertex3f(x+r*cosDeg, y+r*sinDeg, z+h);
	}
	glEnd();
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	for (int i = 0; i <= 361; i++)
	{
		cosDeg = cos(3.1415 * 2 * i / 360);
		sinDeg = sin(3.1415 * 2 * i / 360);
		glVertex3f(x + r * cosDeg, y + r * sinDeg,z);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z+h);
	for (int i = 0; i <= 361; i++)
	{
		cosDeg = cos(3.1415 * 2 * i / 360);
		sinDeg = sin(3.1415 * 2 * i / 360);
		glVertex3f(x + r * cosDeg, y + r * sinDeg, z + h);
	}
	glEnd();
}
void uszy(float x, float y, float z, float r, float h, float degree)
{
	float cosDeg;
	float sinDeg;
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 361; i++)
	{
		if (degree < 0)		
		{
			int pom = 360 + degree;
			for (int i = 0; i < 361; i++)
			{
				if (i >= pom)
				{
					cosDeg = cos(3.1415 * 2 * i / 360);
					sinDeg = sin(3.1415 * 2 * i / 360);
					glVertex3f(x + r * cosDeg, y + r * sinDeg, z);
					glVertex3f(x + r * cosDeg, y + r * sinDeg, z + h);
				}
			}
		}
		if (i >=degree && i <= 45+degree)
		{
			cosDeg = cos(3.1415 * 2 * i / 360);
			sinDeg = sin(3.1415 * 2 * i / 360);
			glVertex3f(x + r * cosDeg, y + r * sinDeg, z);
			glVertex3f(x + r * cosDeg, y + r * sinDeg, z + h);
		}
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		if (degree < 0)
		{
			int pom = 360 + degree;
			for (int i = 0; i < 361; i++)
			{
				if (i >= pom)
				{
					cosDeg = cos(3.1415 * 2 * i / 360);
					sinDeg = sin(3.1415 * 2 * i / 360);
					glVertex3f(x + (r-0.4) * cosDeg, y + (r - 0.4)* sinDeg, z);
					glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4) * sinDeg, z + h);
				}
			}
		}
		for (int i = 0; i <= 361; i++)
		{
			if (i >= degree && i <= 45 + degree)
			{
				cosDeg = cos(3.1415 * 2 * i / 360);
				sinDeg = sin(3.1415 * 2 * i / 360);
				glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4) * sinDeg, z);
				glVertex3f(x + (r - 0.4)* cosDeg, y + (r - 0.4) * sinDeg, z + h);
			}
	}
	glEnd();
	glBegin(GL_QUADS);
		if (degree < 0)
		{
			int pom = 360 + degree;
			cosDeg = cos(3.1415 * 2 * pom / 360);
			sinDeg = sin(3.1415 * 2 * pom / 360);
			glVertex3f(x + r * cosDeg, y + r * sinDeg, z);
			glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z);
			glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z + h);
			glVertex3f(x + r * cosDeg, y + r * sinDeg, z+h);
		}
		else {
			cosDeg = cos(3.1415 * 2 * (degree + 0.5) / 360);
			sinDeg = sin(3.1415 * 2 * (degree + 0.5) / 360);
			glVertex3f(x + r * cosDeg, y + r * sinDeg, z);
			glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z);
			glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z + h);
			glVertex3f(x + r * cosDeg, y + r * sinDeg, z + h);
		}
	glEnd();
	glBegin(GL_QUADS);
	cosDeg = cos(3.1415 * 2 * (degree + 44.5) / 360);
	sinDeg = sin(3.1415 * 2 * (degree + 44.5) / 360);
		glVertex3f(x + r * cosDeg, y + r * sinDeg, z);
		glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z);
		glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z + h);
		glVertex3f(x + r * cosDeg, y + r * sinDeg, z + h);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	if (degree < 0)
	{
		int pom = 360 + degree;
		for (int i = 0; i < 361; i++)
		{
			if (i >= pom)
			{
				cosDeg = cos(3.1415 * 2 * i / 360);
				sinDeg = sin(3.1415 * 2 * i / 360);
				glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z+h);
				glVertex3f(x + r  * cosDeg, y + r * sinDeg, z + h);
			}
		}
	}
	for (int i = 0; i <= 361; i++)
	{
		if (i >= degree && i <= 45 + degree)
		{
			cosDeg = cos(3.1415 * 2 * i / 360);
			sinDeg = sin(3.1415 * 2 * i / 360);
			glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z + h);
			glVertex3f(x + r * cosDeg, y + r * sinDeg, z + h);
		}
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	if (degree < 0)
	{
		int pom = 360 + degree;
		for (int i = 0; i < 361; i++)
		{
			if (i >= pom)
			{
				cosDeg = cos(3.1415 * 2 * i / 360);
				sinDeg = sin(3.1415 * 2 * i / 360);
				glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z);
				glVertex3f(x + r * cosDeg, y + r * sinDeg, z);
			}
		}
	}
	for (int i = 0; i <= 361; i++)
	{
		if (i >= degree && i <= 45 + degree)
		{
			cosDeg = cos(3.1415 * 2 * i / 360);
			sinDeg = sin(3.1415 * 2 * i / 360);
			glVertex3f(x + (r - 0.4) * cosDeg, y + (r - 0.4)* sinDeg, z);
			glVertex3f(x + r * cosDeg, y + r * sinDeg, z);
		}
	}
	glEnd();
}
void osie()
{	//CZEROWONA X
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-5, 0.01, 0);
	glVertex3f(5, 0.01, 0);
	glEnd();
	glBegin(GL_LINES);
	//ZIELONA Y
	glColor3f(0, 1, 0);
	glVertex3f(0, 5, 0);
	glVertex3f(0, -5, 0);
	glEnd();
	//NIEBIESKA Z
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0.01, 5);
	glVertex3f(0, 0.01, -5);
	glEnd();
}

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);
	if (deltaDegree)
		computeDegree(deltaDegree);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z,
		x + lx, y+ly, z + lz,
		0.0f, 1.0f, 0.0f);

	szachownica(-50, 0, -50, 10);
	prostopadloscian(-5, 0, -10, 10, 10);
	osie();
	glPushMatrix();
		glTranslatef(0, 2, 14.6);
		glRotatef(degreeXD, 1, 0, 0);
		glRotatef(degreeXD3, 0, 0, 1);
		glTranslatef(0, -2, -14.6);
		walec(0, 2, 0, 1, 10);
		walec(0, 2, 10, 2, 2);
		uszy(0, 2, 12, 2, 3.2,90-22.5);
		uszy(0, 2, 12, 2, 3.2, 270-22.5);
			glPushMatrix();
			glTranslatef(0, 2, 13);
			glRotatef(90, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			walec(-1.6, 0, -1.7, 0.5, 3.4);
			glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 2, 14.6);
		glRotatef(degreeXD2, 0, 1, 0);
		glRotatef(degreeXD3, 0, 0, 1);
		glTranslatef(0, -2, -14.6);
		uszy(0, 2, 14, 2, 3.2, 180-22.5);
		uszy(0, 2, 14, 2, 3.2, 0-22.5);
		walec(0, 2, 17.2, 2, 2);
		walec(0, 2, 19.2, 1, 10);
		//prostopadloscian(-0.5, 0, 28.2, 1, 2);
		glPushMatrix();
		glTranslatef(0, 2, 13);
		glRotatef(90, 0, 1, 0);
		walec(-1.6, 0, -1.7, 0.5, 3.4);
		glTranslatef(-1.6, 0, 0);
		glColor3f(0, 0, 0);
		glutSolidSphere(0.9, 20, 20);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);
	if (key == 48)
		deltaMove = 0.5f;
}
void processNormalUpKeys(unsigned char key, int xx, int yy) {
	if (key == 48)
	{
		deltaMove = 0.0f;
	}
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	case GLUT_KEY_F1: ::y += 0.5f; break;
	case GLUT_KEY_F2: degreeXD += 2.f; break;
	case GLUT_KEY_F3: degreeXD2 += 2.f; break;
	case GLUT_KEY_F4: degreeXD3 += 5.f; break;
	case GLUT_KEY_F5: deltaDegree = 5.f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	case GLUT_KEY_LEFT: deltaAngle2+=0.1f; ly = sin(angle2 + deltaAngle2); break;
	case GLUT_KEY_RIGHT: deltaAngle2 -= 0.1f; ly = sin(angle2 + deltaAngle2); break;
	case GLUT_KEY_F5: deltaDegree = 0.0f; break;
	}
}
void mouseMove(int x, int y) {

	if (xOrigin >= 0 &&yOrigin>=0) {

		deltaAngle = (x - xOrigin) * 0.001f;
		deltaAngle2=(y-yOrigin)* 0.001f;
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
		ly = -sin(angle2 + deltaAngle2);
	}
}

void mouseButton(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {

		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
			yOrigin = -1;
			angle2 += deltaAngle2;
		}
		else {
			xOrigin = x;
			yOrigin = y;
		}
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Cardan");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(processNormalUpKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	//xD
	deltaAngle = (x - xOrigin) * 0.001f;
	deltaAngle2 = (y - yOrigin)* 0.001f;
	lx = sin(angle + deltaAngle);
	lz = -cos(angle + deltaAngle);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
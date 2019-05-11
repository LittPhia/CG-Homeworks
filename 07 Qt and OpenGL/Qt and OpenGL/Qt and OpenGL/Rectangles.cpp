#include "Rectangles.h"

Rectangles::Rectangles(QWidget *parent) : QOpenGLWidget(parent) {
	ui.setupUi(this);
}

void Rectangles::initializeGL() {
	glewExperimental = true;
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Rectangles::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.0, 1.0,
			-1.0 * (GLfloat)h / (GLfloat)w,
			1.0 * (GLfloat)h / (GLfloat)w,
			-10.0, 10.0);
	else
		glOrtho(-1.0 * (GLfloat)w / (GLfloat)h,
			1.0 * (GLfloat)w / (GLfloat)h,
			-1.0, 1.0,
			-10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void Rectangles::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT, GL_LINE);

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(-0.75, -0.5);
	glVertex2d(-0.25, -0.5);
	glVertex2d(-0.25, 0.5);
	glVertex2d(-0.75, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2d(0.25, 0.5);
	glVertex2d(0.75, 0.5);
	glVertex2d(0.75, -0.5);
	glVertex2d(0.25, -0.5);
	glEnd();

	glFlush();
}
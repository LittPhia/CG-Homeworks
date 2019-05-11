#pragma once

#include <GLEW/glew.h>
#include <QOpenGLWidget>
#include "ui_Rectangles.h"

class Rectangles : public QOpenGLWidget {
	Q_OBJECT

public:
	Rectangles(QWidget *parent = nullptr);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

private:
	Ui::RectanglesClass ui;

};
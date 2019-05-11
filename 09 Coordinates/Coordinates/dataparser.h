#pragma once
#include <QTextStream>
#include <QOpenGLWidget>

class QTextStream;
class MyQGLDataParser {
public:
	MyQGLDataParser();
	MyQGLDataParser(QTextStream *textstream);
	~MyQGLDataParser();

public:
	bool parse(QTextStream *textstream);

	const GLfloat (*vertices() const)[3] {
		return this->vertices_;
	}
	GLsizeiptr vertices_size() const {
		return this->vsize_;
	}

	const GLuint (*indces() const)[3] {
		return this->indices_;
	}
	GLsizeiptr indices_size() const {
		return this->isize_;
	}

private:
	GLfloat (*vertices_)[3];
	GLsizeiptr vsize_;

	GLuint (*indices_)[3];
	GLsizeiptr isize_;

	GLuint (*edges_)[3];
	GLsizeiptr esize_;
};


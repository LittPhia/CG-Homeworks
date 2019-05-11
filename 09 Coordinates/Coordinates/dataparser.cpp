#include "dataparser.h"

#include <QTextStream>

MyQGLDataParser::MyQGLDataParser() {
	this->vertices_ = nullptr;
	this->indices_ = nullptr;
	this->vsize_ = this->isize_ = 0;
}

MyQGLDataParser::MyQGLDataParser(QTextStream *textstream) {
	this->parse(textstream);
}

MyQGLDataParser::~MyQGLDataParser() {
	if (this->vertices_) delete[] this->vertices_;
	if (this->indices_) delete[] this->indices_;
	this->indices_ = nullptr;
	this->vertices_ = nullptr;
	this->vsize_ = this->isize_ = 0;
}

bool MyQGLDataParser::parse(QTextStream *textstream) {
	*textstream >> this->vsize_ >> this->isize_ >> this->esize_;

	this->vertices_ = new GLfloat[static_cast<size_t>(this->vsize_)][3];
	for (GLsizeiptr i = 0; i < this->vsize_; i++) {
		*textstream >> this->vertices_[i][0]
				>> this->vertices_[i][1]
				>> this->vertices_[i][2];
	}

	this->indices_ = new GLuint[static_cast<size_t>(this->isize_)][3];
	for (GLsizeiptr size_checker, i = 0; i < this->isize_; i++) {
		*textstream >> size_checker
				>> this->indices_[i][0]
				>> this->indices_[i][1]
				>> this->indices_[i][2];
		if (size_checker != 3) return false;
	}

	for (GLsizeiptr i = 0; i < this->esize_; i++) {}
	return true;
}


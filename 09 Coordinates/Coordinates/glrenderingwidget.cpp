#include "glrenderingwidget.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix>
#include <QFile>
#include <QFileDialog>

GLRenderingWidget::GLRenderingWidget(QWidget *parent, const QString &vsfilename,  const QString &fsfilename) : QOpenGLWidget (parent) {
	this->mode_ = POINT_MODE;

	this->vertices_ = nullptr;
	this->indices_ = nullptr;
	this->vsize_ = this->isize_ = 0;

	this->vsfilename_ = vsfilename;
	this->fsfilename_ = fsfilename;

	this->VBO_ = this->EBO_ = nullptr;
	this->program_ = nullptr;
}

GLRenderingWidget::~GLRenderingWidget() {
	if (this->program_) delete program_;
	if (this->VBO_) delete VBO_;
	if (this->EBO_) delete EBO_;
}

void GLRenderingWidget::initializeGL() {
	initializeOpenGLFunctions();

	this->relink_program(this->vsfilename_, this->fsfilename_);
	this->write_buffer();

	this->program_->setAttributeBuffer("pos", GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
	this->program_->enableAttributeArray("pos");

	glEnable(GL_DEPTH_TEST);
	glPointSize(4.0f);
}

void GLRenderingWidget::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	QMatrix4x4 model, view, project;
	this->program_->setUniformValue("project", model);
	this->program_->setUniformValue("view", view);
	this->program_->setUniformValue("model", project);

	switch (this->mode_) {
		case POINT_MODE:
			glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(this->vsize_));
			break;
		case LINE_MODE:
			for (size_t i = 0; static_cast<GLsizeiptr>(i) < this->isize_; i+=3) {
				glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, reinterpret_cast<void *>(i * sizeof(GLuint)));
			}
			break;
		case FACE_MODE:
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->isize_), GL_UNSIGNED_INT, nullptr);
			break;
	}
	this->update();
}

void GLRenderingWidget::resizeGL(GLsizei width, GLsizei height) {
	setGeometry(this->x(), this->y(), width, height);
}

void GLRenderingWidget::discard_current_vertices() {
	if(this->vertices_) delete this->vertices_;
	this->vertices_ = nullptr;
}

void GLRenderingWidget::reload_vertices(const GLfloat (*vertices)[3], GLsizeiptr size) {
	if(this->vertices_) delete this->vertices_;

	this->vsize_ = 3 * size;
	GLfloat *pv = new GLfloat[static_cast<GLuint>(this->vsize_)];
	memcpy(pv, vertices, 3 * static_cast<size_t>(size) * sizeof(GLfloat));
	this->vertices_ = pv;
}

void GLRenderingWidget::discard_current_indices() {
	if (this->indices_) delete this->indices_;
	this->indices_ = nullptr;
}

void GLRenderingWidget::reload_indices(const GLuint (*indices)[3], GLsizeiptr size) {
	if(this->indices_) delete this->indices_;

	GLuint *pi = new GLuint[static_cast<size_t>(3 * size)];
	void *tmp;
	for (GLsizeiptr i = 0; i < 3 * size; i++) {
		tmp = static_cast<void *>(const_cast<GLuint (*)[3]>(indices));
		pi[i] = *(static_cast<GLuint *>(tmp) + i);
	}
	this->indices_ = pi;
	this->isize_ = 3 * size;
}

void GLRenderingWidget::discard_current_program() {
	this->program_->removeAllShaders();
	this->program_->release();
	delete this->program_;
	this->program_ = nullptr;
}

void GLRenderingWidget::relink_program(const QString &vsfiledir, const QString &fsfiledir) {
	if (!vsfiledir.isEmpty()) this->vsfilename_ = vsfiledir;
	if (!fsfiledir.isEmpty()) this->fsfilename_ = fsfiledir;
	if (this->program_) {
		this->program_->removeAllShaders();
		delete this->program_;
	}
	this->program_ = new QOpenGLShaderProgram;
	this->program_->addShaderFromSourceFile(QOpenGLShader::Vertex, this->vsfilename_);
	this->program_->addShaderFromSourceFile(QOpenGLShader::Fragment, this->fsfilename_);
	this->program_->link();
	this->program_->bind();
}

void GLRenderingWidget::discard_current_buffer() {
	if (this->VBO_) {
		this->glInvalidateBufferData(this->VBO_->bufferId());
		this->VBO_->release();
		this->VBO_->destroy();
		this->VBO_ = nullptr;
	}
	if (this->EBO_) {
		this->glInvalidateBufferData(this->EBO_->bufferId());
		this->EBO_->release();
		this->EBO_->destroy();
		this->EBO_ = nullptr;
	}
}

void GLRenderingWidget::write_buffer() {
	this->VBO_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	this->VBO_->create();
	this->VBO_->bind();
	this->VBO_->allocate(this->vertices_, static_cast<int>(this->vsize_) * static_cast<int>(sizeof(GLfloat)));

	if (this->EBO_) delete this->EBO_;
	this->EBO_ = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	this->EBO_->create();
	this->EBO_->bind();
	this->EBO_->allocate(this->indices_, static_cast<int>(this->isize_) * static_cast<int>(sizeof(GLuint)));
}

void GLRenderingWidget::set_mode(GLWidgetRenderMode mode) {
	mode_ = mode;
}

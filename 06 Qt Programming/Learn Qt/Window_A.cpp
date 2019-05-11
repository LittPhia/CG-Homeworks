#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMouseEvent>

#include "Window_A.h"


Window_A::Window_A(QWidget *parent) : QMainWindow(parent) {
	window_status_.key_C = RELEASED;
	window_status_.key_R = RELEASED;
	window_status_.left_button = RELEASED;
	window_status_.right_button = RELEASED;

	setGeometry(0, 0, 800, 800);
	setStyleSheet("background:black");
}

void Window_A::keyPressEvent(QKeyEvent *key_event) {
	if (key_event->key() == Qt::Key_C) {
		window_status_.key_C = PRESSED;
		update();
	}
	if (key_event->key() == Qt::Key_R) {
		window_status_.key_R = PRESSED;
		update();
	}
}

void Window_A::keyReleaseEvent(QKeyEvent *key_event) {
	if (key_event->key() == Qt::Key_C) {
		window_status_.key_C = RELEASED;
		update();
	}
	if (key_event->key() == Qt::Key_R) {
		window_status_.key_R = RELEASED;
		update();
	}
}

void Window_A::mousePressEvent(QMouseEvent *mouse_event) {
	if (mouse_event->button() == Qt::LeftButton) {
		window_status_.left_button = PRESSED;
		update();
	}
	if (mouse_event->button() == Qt::RightButton) {
		window_status_.right_button = PRESSED;
		update();
	}
}

void Window_A::mouseReleaseEvent(QMouseEvent *mouse_event) {
	if (mouse_event->button() == Qt::LeftButton) {
		window_status_.left_button = RELEASED;
		update();
	}
	if (mouse_event->button() == Qt::RightButton) {
		window_status_.right_button = RELEASED;
		update();
	}
}

void Window_A::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	const size_t STRWIDTH = 120, STRHEIGHT = 30;

	if (window_status_.key_C == PRESSED) {
		QRect r = rect();

		painter.setBrush(Qt::white);
		painter.drawEllipse(QPointF(r.width() / 2.0, r.height() / 2.0),
			7 * r.width() / 20.0,		// 35% of r.width()
			7 * r.width() / 20.0);

		painter.setPen(Qt::white);
		painter.drawText(
			r.width() / 2.0 - STRWIDTH / 2.0,
			r.height() / 2.0 + 7 * r.width() / 20.0 + STRHEIGHT,
			STRWIDTH, STRHEIGHT,
			Qt::AlignCenter,
			"Circle");
	}

	if (window_status_.key_R == PRESSED) {
		QRect r = rect();

		painter.setBrush(Qt::white);
		painter.drawRect(r.width() / 5.0,		// x
			1.5 * r.height() / 5.0,				// y
			3 * r.width() / 5.0,				// 60% of r.width()
			2 * r.height() / 5.0);				// 40% of r.height()

		painter.setPen(Qt::white);
		painter.drawText(
			r.width() / 2.0 - STRWIDTH / 2.0,
			3.5 * r.height() / 5.0 + STRHEIGHT,
			STRWIDTH, STRHEIGHT,
			Qt::AlignCenter,
			"Rectangle");
	}

	if (window_status_.left_button == PRESSED) setStyleSheet("background:green");
	else if (window_status_.right_button == PRESSED) setStyleSheet("background:blue");
	else setStyleSheet("background:black");
}

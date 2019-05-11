#pragma once
#include <QMainWindow>
#include "ui_Window_A.h"


class Window_A : public QMainWindow {
	Q_OBJECT;

	enum status{ PRESSED, RELEASED };

public:
	Window_A(QWidget *parent = nullptr);

private:
	void keyPressEvent(QKeyEvent *key_event);
	void keyReleaseEvent(QKeyEvent *key_event);
	void mousePressEvent(QMouseEvent *mouse_event);
	void mouseReleaseEvent(QMouseEvent *mouse_event);
	void paintEvent(QPaintEvent *);

private:
	Ui::Window_AClass ui;
	struct {
		status key_C;
		status key_R;
		status left_button;
		status right_button;
	} window_status_;
};
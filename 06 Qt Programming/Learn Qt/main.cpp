#include <QApplication>
#include <QPainter>

#include "Window_A.h"


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Window_A w;
	w.show();
	return app.exec();
}

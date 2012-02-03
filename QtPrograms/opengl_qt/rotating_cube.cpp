
#include <QApplication>
#include <exception>
#include <iostream>
#include "RotatingCubeWidget.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);
	RotatingCubeWidget *widget = new RotatingCubeWidget(0);//("Rotating cube - opengl qt");
	widget->resize(500,500);
	widget->show();
	return app.exec();
}

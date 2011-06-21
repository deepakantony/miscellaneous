#include <QApplication>
#include "RotatingCubeWidget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  RotatingCubeWidget *widget = new RotatingCubeWidget("Rotating cube - opengl qt");
  widget->show();
  return app.exec();
}

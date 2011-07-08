#ifndef _ROTATING_CUBE_WIDGET_H_
#define _ROTATING_CUBE_WIDGET_H_

#include <QGLWidget>

class GLCube : public QObject {
 public:
  GLCube(GLfloat size = 1.0) {
    this->size = size;
  }
  GLCube(){
  }
 private:
  GLfloat size;
  QColor 
};


class RotatingCubeWidget : public QGLWidget {
 public:
  RotatingCubeWidget(QWidget *parent = 0);
  ~RotatingCubeWidget();

  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

 private:
  int xRot, yRot, zRot;
};


#endif // _ROTATING_CUBE_WIDGET_H_

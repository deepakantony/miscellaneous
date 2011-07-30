#ifndef _ROTATING_CUBE_WIDGET_H_
#define _ROTATING_CUBE_WIDGET_H_

#include <QGLWidget>
#include <QKeyEvent>
#include <QTimerEvent>

class RotatingCubeWidget : public QGLWidget {
  Q_OBJECT;
 public:
  RotatingCubeWidget(QWidget *parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  virtual void keyPressEvent(QKeyEvent *event);
  virtual void timerEvent(QTimerEvent *event);
  void updateRotation();

 private:
  void resetRotation();
  void resetEnablers();

 private:
  float xRot, yRot, zRot;
  float dxRot, dyRot, dzRot; // step value
  bool enablex, enabley, enablez, enableAnimation;
};


#endif // _ROTATING_CUBE_WIDGET_H_

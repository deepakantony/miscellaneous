#ifndef _ROTATING_CUBE_WIDGET_H_
#define _ROTATING_CUBE_WIDGET_H_

#include <QGLWidget>
#include <QKeyEvent>
#include <QTimerEvent>

class RotatingCubeWidget : public QGLWidget {
  Q_OBJECT;
 public:
  RotatingCubeWidget(QWidget *parent = 0);

  virtual void initializeGL();
  //virtual void paintGL();
  virtual void paintEvent(QPaintEvent *event);
  virtual void resizeGL(int width, int height);

  virtual void keyPressEvent(QKeyEvent *event);
  virtual void timerEvent(QTimerEvent *event);
  void updateRotation();

 protected:
  void animate();

 private:
  void resetRotation();
  void resetEnablers();

  void drawInstructions(QPainter*);

 private:
  float xRot, yRot, zRot;
  float dxRot, dyRot, dzRot; // step value
  bool enablex, enabley, enablez, enableAnimation;

  // variables for fps calculations
  int frames, refreshTime, fps, timeNow, timeLast;
};


#endif // _ROTATING_CUBE_WIDGET_H_

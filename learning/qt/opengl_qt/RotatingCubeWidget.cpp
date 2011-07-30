#include "RotatingCubeWidget.h"
#include <QtOpenGL>

bool drawCubeDirect(float size) {
  if(size < 0.f)
    return false;

  glBegin(GL_QUADS);
  //front 
  glColor3f(0.7f, 0.2f, 0.2f);
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);
  //back
  glColor3f(0.7f, 0.2f, 0.7f);
  glVertex3f( size, -size, -size);
  glVertex3f( size,  size, -size);
  glVertex3f(-size,  size, -size);
  glVertex3f(-size, -size, -size);
  //right
  glColor3f(0.2f, 0.2f, 0.7f);
  glVertex3f( size, -size,  size);
  glVertex3f( size, -size, -size);
  glVertex3f( size,  size, -size);
  glVertex3f( size,  size,  size);
  //left
  glColor3f(0.2f, 0.7f, 0.7f);
  glVertex3f(-size, -size, -size);
  glVertex3f(-size, -size,  size);
  glVertex3f(-size,  size,  size);
  glVertex3f(-size,  size, -size);
  //top
  glColor3f(0.2f, 0.7f, 0.2f);
  glVertex3f( size,  size,  size);
  glVertex3f( size,  size, -size);
  glVertex3f(-size,  size, -size);
  glVertex3f(-size,  size,  size);
  //bottom
  glColor3f(0.7f, 0.7f, 0.2f);
  glVertex3f( size, -size,  size);
  glVertex3f(-size, -size,  size);
  glVertex3f(-size, -size, -size);
  glVertex3f( size, -size, -size);
  
  glEnd();


  return true;
}

RotatingCubeWidget::RotatingCubeWidget(QWidget *parent)
  :QGLWidget(parent)
{
  setWindowTitle("Rotating cube");

  resetRotation();
  resetEnablers();

  dxRot = dyRot = dzRot = 40.f/60.f;

  startTimer(1000/60);
}

void RotatingCubeWidget::resetRotation() {
  // No rotation
  xRot = yRot = zRot = 0;
}

void RotatingCubeWidget::resetEnablers() {
  enablex = enabley = enablez = enableAnimation = false;
}

void RotatingCubeWidget::initializeGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glOrtho(-.5,.5,-.5,.5,-.5,.5);
  glFrustum(-.5, .5, -.5, .5, .5, 2.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.f, 0.f, 0.f, 0.f);
  glEnable(GL_DEPTH_TEST);
  
}

void RotatingCubeWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.7f, 0.2f, 0.2f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.f, 0.f, -1.0);

  glPushMatrix();
  glRotatef(xRot, 1.f, 0.f, 0.f);
  glRotatef(yRot, 0.f, 1.f, 0.f);
  glRotatef(zRot, 0.f, 0.f, 1.f);
  drawCubeDirect(0.25);
  glPopMatrix();
}

void RotatingCubeWidget::resizeGL(int width, int height) {
}

void RotatingCubeWidget::keyPressEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_A)
    enableAnimation = enableAnimation ? false:true;
  if(event->key() == Qt::Key_X)
    enablex = enablex ? false:true;
  if(event->key() == Qt::Key_Y)
    enabley = enabley ? false:true;
  if(event->key() == Qt::Key_Z)
    enablez = enablez ? false:true;
  if(event->key() == Qt::Key_R) {
    resetEnablers();
    resetRotation();
  }
}

void RotatingCubeWidget::timerEvent(QTimerEvent *event) {
  updateRotation();
  updateGL();
}

void RotatingCubeWidget::updateRotation() {
  if(enableAnimation) {
    if(enablex) {
      xRot += dxRot;
      if( xRot > 360 )
	xRot -= 360;
    }
    if(enabley) {
      yRot += dyRot;
      if(yRot > 360 )
	yRot -= 360;
    }
    if(enablez) {
      zRot += dzRot;
      if(zRot > 360)
	zRot -= 360;
    }
  }
}

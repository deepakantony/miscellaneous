#include "RotatingCubeWidget.h"
#include <QtOpenGL>

bool drawSquare(float size) {
  if(size < 0)
    return false;

  glBegin(GL_QUADS);
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);
  glEnd();

  return true;
}

bool drawCube(float size) {
  if(size < 0)
    return false;

  glPushMatrix();
  //front
  glTranslatef(0.f, 0.f, size);
  glColor3f(0.8f, 0.2f, 0.2f);
  drawSquare(size);
  glPopMatrix();

  glPushMatrix();
  //right side
  glTranslatef(size, 0.f, 0.f);
  glRotatef(90.f, 0.f, 1.f, 0.f);
  glColor3f(0.2f, 0.7f, 0.2f);
  drawSquare(size);
  glPopMatrix();

  glPushMatrix();
  //back
  glTranslatef(0.f, 0.f, -size);
  glRotatef(180.f, 0.f, 1.f, 0.f);
  glColor3f(0.2f, 0.2f, 0.7f);
  drawSquare(size);
  glPopMatrix();

  glPushMatrix();
  //left side
  glTranslatef(-size, 0.f, 0.f);
  glRotatef(90.f, 0.f, -1.f, 0.f);
  glColor3f(0.2f, 0.7f, 0.7f);
  drawSquare(size);
  glPopMatrix();

  glPushMatrix();
  //top
  glTranslatef(0.f, size, 0.f);
  glRotatef(90.f, -1.f, 0.f, 0.f);
  glColor3f(0.7f, 0.2f, 0.7f);
  drawSquare(size);
  glPopMatrix();

  glPushMatrix();
  //bottom
  glTranslatef(0.f, -size, 0.f);
  glRotatef(90.f, 1.f, 0.f, 0.f);
  glColor3f(0.7f, 0.2f, 0.7f);
  drawSquare(size);
  glPopMatrix();

  return true;
}

bool drawCubeDirect(float size) {
  if(size < 0.f)
    return false;

  glBegin(GL_QUADS);
  //front 
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);
  //back
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);
  //right
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);
  //left
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);
  //top
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);
  //bottom
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);
  
  glEnd();


  return true;
}

RotatingCubeWidget::RotatingCubeWidget(QWidget *parent)
  :QGLWidget(parent)
{
  setWindowTitle("Rotating cube");
}

RotatingCubeWidget::~RotatingCubeWidget() {
}

void RotatingCubeWidget::initializeGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glOrtho(-.5,.5,-.5,.5,-.5,.5);
  glFrustum(-.5, .5, -.5, .5, .5, -1.0);

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
  glRotatef(180.f, 0.f, 1.f, 0.f);
  drawCube(0.25);
}

void RotatingCubeWidget::resizeGL(int width, int height) {
}


#include "RotatingCubeWidget.h"
#include "cube.h"
#include <QtOpenGL>
#include <ctime>

RotatingCubeWidget::RotatingCubeWidget(QWidget *parent)
  :QGLWidget(parent)
{
  setWindowTitle("Rotating cube");

  resetRotation();
  resetEnablers();

  dxRot = dyRot = dzRot = 40.f/60.f;

  setAutoFillBackground(false);

  refreshTime = 30;
  fps = 0;
  frames = 0;
  timeNow = timeLast = 0;

  startTimer(refreshTime);
}

void RotatingCubeWidget::resetRotation() {
  // No rotation
  xRot = yRot = zRot = 0;
}

void RotatingCubeWidget::resetEnablers() {
  enablex = enabley = enablez = enableAnimation = false;
}

void RotatingCubeWidget::initializeGL() {
}

void RotatingCubeWidget::paintEvent(QPaintEvent *event) {
  makeCurrent();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-.5, .5, -.5, .5, .5, 2.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.f, 0.f, 0.f, 0.f);
  glEnable(GL_DEPTH_TEST);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.7f, 0.2f, 0.2f);
  
  glLoadIdentity();
  glTranslatef(0.f, 0.f, -1.0);

  glPushMatrix();
  glRotatef(xRot, 1.f, 0.f, 0.f);
  glRotatef(yRot, 0.f, 1.f, 0.f);
  glRotatef(zRot, 0.f, 0.f, 1.f);
  //glPushMatrix();
  //  drawCubeDirect(0.25);
  Cube(0.25).glDraw();
  glPopMatrix();

  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  // fps calculations
  timeNow = clock();
  ++frames;

  if(frames > 10) { // update every 10 frames
	if ((timeNow-timeLast) > 0)
		fps = frames*CLOCKS_PER_SEC/(timeNow-timeLast);
    timeLast = timeNow;
    frames = 0;
  }

  QPainter *painter = new QPainter(this);
  painter->setRenderHint(QPainter::Antialiasing);
  drawInstructions(painter);
  painter->end();
  delete painter;
}

void RotatingCubeWidget::resizeGL(int width, int height) {
}

void RotatingCubeWidget::keyPressEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_A) {
    enableAnimation = enableAnimation ? false:true;
    if(!enablex && !enabley && !enablez)
      enablex = true;
  }
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
  update();
}

void RotatingCubeWidget::animate() {
  updateRotation();
  update();
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

void RotatingCubeWidget::drawInstructions(QPainter *painter) {
  QString usage = tr("Press 'a' to start and stop rotating cube\n"
		     "Press 'x/y/z' to rotate about x/y/z axis and r to reset");

  QFontMetrics fontMetrics = QFontMetrics(font());
  int border = qMax(4, fontMetrics.leading());

  QRect rect = 
    fontMetrics.boundingRect(0, 0, width()-2*border, int(height()*0.875), 
			     Qt::AlignCenter |  Qt::TextWordWrap, usage);
  painter->setRenderHint(QPainter::TextAntialiasing);
  painter->fillRect(QRect(0, height() - rect.height(), width(), height()),
		    QColor(63, 63, 63, 127));
  painter->setPen(QColor(220, 220, 220, 255));
  painter->drawText((width()-rect.width())/2, height()-rect.height(), 
		    rect.width(), rect.height(),
		    Qt::AlignCenter | Qt::TextWordWrap, usage);
  
  QString fpsString("");
  fpsString += QString::number(fps) + QString(" fps");
  if(enableAnimation)
    fpsString += QString("\nRotation enabled");
  else
    fpsString += QString("\nRotation disabled");
  if(enablex)
    fpsString += QString("\nX rotation");
  if(enabley)
    fpsString += QString("\nY rotation");
  if(enablez)
    fpsString += QString("\nZ rotation");

  QRect fpsRect =
    fontMetrics.boundingRect(fpsString);

  painter->setPen(QColor(200, 50, 50, 255));
  painter->drawText(width()-fpsRect.width(), 0, fpsRect.width(), fpsRect.height()*5+2*border,
		    Qt::AlignRight, fpsString);
}

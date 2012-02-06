#ifndef _GLWIDGET_H_
#define _GLWIDGET_H_

#include <QGLWidget>

#include "GLThread.h"

class GLWidget : public QGLWidet 
{
public:
	GLWidget(GLWidget *parent);

	void startRendering();
	void stopRendering();
	
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void closeEvent(QCloseEvent *event);
private:
	GLThread glt;
};

#endif // _GLWIDGET_H_

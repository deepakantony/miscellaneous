#ifndef _GLTHREAD_H_
#define _GLTHREAD_H_

#include <QThread>

class GLWidget;

class GLThread : public QThread
{
public:
	GLThread(GLWidget *glWidget);

	void run();
	void stop();
	void resizeViewport(const QSize &size);

private:
	bool doRendering;
	bool doResize;
	int width;
	int height;
	int rotAngle;
	GLWidget *glw;
};

#endif // _GLTHREAD_H_

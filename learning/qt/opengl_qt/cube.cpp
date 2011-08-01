#include "cube.h"

Cube::Cube(float size) 
  :size(size) {
}

bool Cube::glDraw() {
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



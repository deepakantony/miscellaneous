#ifndef _CUBE_H_
#define _CUBE_H_

class Cube {
 public:
  Cube(float size = 1.f);

  bool glDraw() const;

 private:
  float size;
};

#endif

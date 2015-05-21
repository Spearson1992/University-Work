#ifndef quaternion_h
#define quaternion_h
#include <gl/glut.h>
#include "Vector.h"
class Quaternion
{
public:
    GLfloat w, x, y, z;


    Quaternion(GLfloat inW, GLfloat inX, GLfloat inY, GLfloat inZ)
        :w(inW), x(inX), y(inY), z(inZ){}
    Quaternion()
        :w(0), x(0), y(0), z(0){}
    ~Quaternion(){}
    void normalize();
    Quaternion operator *(const Quaternion &input) const;
    void conjugate();
    Quaternion fromAxis(Vector input, GLfloat angle);
private:

};
#endif
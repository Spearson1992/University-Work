#ifndef Vector_h
#define Vector_h
#include <gl\glut.h>
class Vector
{
public:
    GLfloat _x,_y,_z;
    Vector(GLfloat x,GLfloat y, GLfloat z)
        :_x(x),_y(y),_z(z){}
    Vector()
        :_x(0), _y(0), _z(0){}
    ~Vector();
    Vector crossProduct(const Vector &input) const;
    Vector crossProduct(const GLfloat &inZ, const GLfloat &inY, const GLfloat &inX) const;
    void normalize();
    Vector operator-(const Vector &input);
    Vector operator+(const Vector &input);
    //divide all values of a vector by the divisor
    Vector operator/(const GLfloat divisor);
private:
    
};
#endif
#include"Vector.h"
#include<math.h>
Vector Vector::crossProduct(const Vector &input) const
{
    GLfloat normalX = (this->_y * input._z) - (this->_z*input._y);
    GLfloat normalY = (this->_z * input._x) - (this->_x * input._z);
    GLfloat normalZ = (this->_x * input._y) -(this->_y * input._x);
    Vector normal(normalX,normalY,normalZ);
    return normal;
}

Vector Vector::crossProduct(const GLfloat &inX, const GLfloat &inY, const GLfloat &inZ) const
{
    GLfloat normalX = (this->_y * inZ) - (this->_z*inY);
    GLfloat normalY = (this->_z * inX) - (this->_x * inZ);
    GLfloat normalZ = (this->_x * inY) -(this->_y * inX);
    Vector normal(normalX,normalY,normalZ);
    return normal;
}

Vector::~Vector()
{
}

void Vector::normalize()
{
    int magnitude = sqrt(_x*_x + _y*_y + _z*_z);
    _x /= magnitude;
    _y /=  magnitude;
    _z /= magnitude;
}
Vector Vector::operator-(const Vector &input)
{
    Vector temp((this->_x - input._x),(this->_y - input._y),(this->_z - input._z));
    return temp;
}
Vector Vector::operator+(const Vector &input)
{
    Vector temp((this->_x + input._x),(this->_y + input._y),(this->_z + input._z));
    return temp;
}
Vector Vector::operator/(const GLfloat divisor)
{
    Vector temp(this->_x / divisor, this->_y/ divisor, this->_z / divisor);
    return temp;
}
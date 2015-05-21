#include "Quaternion.h"
#include <math.h>
void Quaternion::normalize()
{
    int magnitude = sqrt(w*w + x*x + y*y + z*z);
    this->w /= magnitude;
    this->x /= magnitude;
    this->y /=magnitude;
    this->z /= magnitude;
}

Quaternion Quaternion::operator*(const Quaternion &input) const
{
    Quaternion temp;
    temp.w = (this->w * input.w) - (this->x * input.x) - (this->y * input.y) - (this->z * input.z);
    temp.x = (this->w * input.x) + (this->x * input.w) + (this->y * input.z) - (this->z * input.y);
    temp.y = (this->w * input.y) - (this->x * input.z) + (this->y * input.w) + (this->z * input.x);
    temp.z = (this->w * input.z) + (this->x * input.y) - (this->y * input.x) + (this->z * input.w);
    return temp;
}
void Quaternion::conjugate()
{
    this->w = -this->w;
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

Quaternion Quaternion::fromAxis(Vector input, GLfloat angle)
{
    angle *= 0.5f;
    GLfloat sinAngle = sin(angle);
    input.normalize();

    x = input._x * sinAngle;
    y = input._y * sinAngle;
    z = input._z * sinAngle;
    w = cos(angle);
    return *this;
}
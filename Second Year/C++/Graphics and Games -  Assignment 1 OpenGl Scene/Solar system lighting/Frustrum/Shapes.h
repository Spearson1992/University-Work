#ifndef Shapes_h
#define Shapes_h
#include <gl\glut.h>
class Shapes
{
public:
    Shapes();
    ~Shapes();
    static void drawCylinder(int Sections, GLfloat Radius, GLfloat Length , bool endsTextured, bool sidesTextured, int textureReps);
    static void drawCone(GLfloat Sections, GLfloat height, GLfloat Radius, bool isTextured);
    static void drawCube(GLfloat width, GLfloat height, GLfloat depth, bool isTextured);
    static void drawCircle(int sections, GLfloat radius,GLfloat height, bool endsTextured);
    static void drawCylinderNoEnds(GLfloat sections, GLfloat topRadius,GLfloat bottomRadius, GLfloat length, bool sidesTextured, int textureReps);
     
private:

};

#endif
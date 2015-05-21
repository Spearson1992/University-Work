#ifndef Camera_h
#define Camera_h
#include <gl/glut.h>
#include "Quaternion.h"
class Camera
{
public:
    Camera();
    ~Camera();
    //Computes the midpoint of the screen
    void computeMidpoint();
    //Updates the mouse coordinates
    void updateMousePos(int x, int y);
    inline GLfloat toRadians(GLfloat angle) { return angle * (3.141592654f / 180.0f);}



    GLfloat cameraZ, 
            cameraX, 
            cameraY, 
            deltaMouseX, 
            deltaMouseY, 
            middleX,
            middleY,
            yRotation,
            xRotation;

    //bool    lbDown;
};
#endif

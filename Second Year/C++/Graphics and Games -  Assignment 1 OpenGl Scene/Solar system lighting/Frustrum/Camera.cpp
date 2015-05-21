#include "Camera.h"
#include <math.h>

Camera::Camera()
    :cameraZ(20), cameraY(10),cameraX(0), deltaMouseX(0), deltaMouseY(0),
    middleX(0), middleY(0), yRotation(0), xRotation(0){}

Camera::~Camera(){}

void Camera::computeMidpoint()
{
    middleX = glutGet(GLUT_WINDOW_WIDTH) >> 1;
    middleY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;
}

void Camera::updateMousePos(int x, int y)
{    
    deltaMouseX = (x - middleX)/100;
    deltaMouseY = (y - middleY)/100;
    xRotation += deltaMouseY;
    yRotation += deltaMouseX;

    if(xRotation > 89)
        xRotation = 89;
    if(xRotation < -89)
        xRotation = -89;
    if(yRotation > 360 || yRotation < -360)
        yRotation= 0;
    //updateCamera();
}

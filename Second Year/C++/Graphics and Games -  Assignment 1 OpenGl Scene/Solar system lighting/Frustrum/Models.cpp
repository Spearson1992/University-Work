#include <gl/glut.h>
#include "Material.h"
#include "Shapes.h"
#include "Vector.h"
#include "Models.h"
#include "Lights.h"
#include <math.h>
extern GLuint grassTex, woodTex,pedestalTex, displayLists, teacupList; // textures and display lists
extern GLfloat lift, mat_diffuse[];
extern float rot, rot1, rot2, teacupRot,teacupBaseRot, carouselRot; // rotation variables
extern Material *ceramic,  *floorMat; // materials
extern Light *light3, *light4, *light5; // lights 
Material *sunMat;
typedef  GLfloat vertex3[3];


void drawQuad(Vector frontRight, Vector frontLeft, Vector backLeft, Vector backRight)
{
    glBegin(GL_TRIANGLES);
        glColor3f(1.0,1.0,1.0);
        Vector temp1 = backLeft - frontLeft;
        Vector temp2 = frontRight - frontLeft;
        Vector normal = temp2.crossProduct(temp1);
        glNormal3f(normal._x, normal._y, normal._z);        
        glTexCoord2f(0.0,0.0);        
        glVertex3f(frontLeft._x,frontLeft._y, frontLeft._z);        
        glTexCoord2f(0.0,1.0);
        glVertex3f(backLeft._x,backLeft._y, backLeft._z);
        glTexCoord2f(1.0,0.0);
        glVertex3f(frontRight._x, frontRight._y, frontRight._z);
    glEnd();

    glBegin(GL_TRIANGLES);
        temp1 = frontRight - backLeft;
        temp2 = backRight - backLeft;
        normal = temp1.crossProduct(temp2);
        glNormal3f(normal._x, normal._y, normal._z);       
        glTexCoord2f(0.0,1.0);
        glVertex3f(backLeft._x,backLeft._y, backLeft._z);
        glTexCoord2f(1.0,0.0);
        glVertex3f(frontRight._x, frontRight._y, frontRight._z);
        glTexCoord2f(1.0,1.0); 
        glVertex3f(backRight._x, backRight._y, backRight._z);
    glEnd();

}
void subDivideQuad(Vector frontRight, Vector frontLeft, Vector backLeft, Vector backRight, int iterations)
{
    Vector midFront, midLeft, midBack, midRight, centre;
    if(iterations == 0)
        drawQuad(frontRight, frontLeft, backLeft, backRight);
    else
    {
        midFront = (frontRight + frontLeft) / 2;
        midLeft = (frontLeft + backLeft) / 2;
        midBack = (backLeft + backRight) / 2;
        midRight = (backRight + frontRight) / 2;

        if((frontRight._x > 50 && frontRight._x < 95) && frontRight._z > 50)
            centre._y = 2.0f;
        else
            centre._y = 0.0f;

        centre._x = (midLeft._x + midRight._x) / 2;
        centre._z = (midFront._z + midBack._z) / 2;
        
        subDivideQuad(frontRight,midFront, centre, midRight, iterations - 1);
        subDivideQuad(midFront, frontLeft, midLeft, centre, iterations - 1);
        subDivideQuad(centre, midLeft, backLeft, midBack, iterations -1);
        subDivideQuad(midRight, centre,midBack, backRight, iterations - 1);
    }
}


void drawTerrain()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, grassTex);
    Vector frontRight(100.0f, 0.0f,100.0f);
    Vector frontLeft(-100.f, 0.0f, 100.0f);
    Vector backLeft(-100.0f, 0.0f,-100.0f);
    Vector backRight(100.0f, 0.0f, -100.f);
    subDivideQuad(frontRight, frontLeft, backLeft, backRight,6);
    glDisable(GL_TEXTURE_2D);
}
void drawFence()
{

    glBegin(GL_QUADS);
    glNormal3f(0.0f,0.0f,-1.0f);
        glVertex3f(100,0,100);
        glVertex3f(-100,0,100);
        glVertex3f(-100,10,100);
        
        glVertex3f(100,10,100);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1.0f,0.0f,0.0f);
        glVertex3f(-100,0,100);
        glVertex3f(-100,0,-100);
        glVertex3f(-100,10,-100);
        glVertex3f(-100,10,100);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f(-100,0,-100);
        glVertex3f(100,0,-100);
        glVertex3f(100,10,-100);
        glVertex3f(-100,10,-100);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(-1.0f,0.0f,0.0f);
        glVertex3f(100,0,-100);
        glVertex3f(100,0,100);
        glVertex3f(100,10,100);
        glVertex3f(100,10,-100);
    glEnd();
}
void drawCarousel()
{
    glCallList(displayLists); //draw base
    glPushMatrix();
    //draw central pilar
    glRotatef(-carouselRot,0.0,1.0,0.0);
        glCallList(displayLists+1);
            bool reverse = false;
            for(int rotation = 0; rotation < 360; rotation +=45)
            {
                glPushMatrix();
                    glRotatef(rotation,0,1,0);
                    glTranslatef(0.0,-5.0, 6);
                    glCallList(displayLists+2);
                    glPushMatrix();
                    if(reverse)
                    {
                        glTranslatef(0,-4.5,0);
                        glTranslatef(-1.0,-lift,-0.5);
                        reverse = false;
                    }
                    else
                    {
                        glTranslatef(-1.0,lift,-0.5);
                        reverse = true;
                    }
                    //draw horse thing
                    glCallList(displayLists+3);
                    glPopMatrix();
                glPopMatrix();
            }
            glPopMatrix();
            glPopMatrix();
            glLoadIdentity();
}

void drawSolarSystem()
{
    sunMat->enableMaterial();
	glPushMatrix();
        glColor3f(1.0,1.0,0.0);
			    glutSolidSphere(10,32,32);
		    glPushMatrix();
            glColor3f(1.0,1.0,1.0);
            floorMat->enableMaterial(true,true,true, true,true);
                glColor3f(1.0,0.5,0.1);
			    glRotatef(rot,0,1,0);
			    glTranslatef(15,0,0);
			    glutSolidSphere(2,32,32);
		    glPopMatrix();

		    glPushMatrix();
                glColor3f(0.0,0.4,0.0);
			    glRotatef(rot1,0,1,0);
			    glTranslatef(30,0,0);
			    glutSolidSphere(3,32,32);
		    glPopMatrix();

		    glPushMatrix();
            glColor3f(0.0,0.0,0.4);
			    glRotatef(rot2,0,1,0);
			    glTranslatef(40,0,0);
			    glutSolidSphere(3,32,32);
		    glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawPedestal()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,pedestalTex);
    glPushMatrix();
        Shapes::drawCube(5.0f,1.0f,5.0f,true);
        glTranslatef(2.5,1.0,2.5);
        Shapes::drawCylinder(8,2.0f,4.0f,false,true,1);
        glTranslatef(-2.5,4.0,-2.5);
        Shapes::drawCube(5.0f,1.0f,5.0f,true);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawTeaCups()
{
    glCallList(teacupList);// draw teacup frame
    glPushMatrix();
    glColor3f(0.4,0.5,0.6);
    glTranslatef(0.0,0.5,0.0);
    glRotatef(teacupBaseRot, 0.0f, 1.0f, 0.0f);
    Shapes::drawCylinder(32, 20, 2,false,false,0);
    glPushMatrix();
    glTranslatef(0.0,2.0,0.0);
    Shapes::drawCylinder(32,5,8,false,false,0);
    glPopMatrix();
    for(int rotation = 0; rotation < 360; rotation +=45)
    {
        glPushMatrix();
        ceramic->enableMaterial();
        glColor3f(0.1f,0.1f,0.5f);
            glRotatef(rotation,0.0f,1.0f,0.0f);
            glTranslatef(0.0f,2.0f,15.0f);
            glRotatef(teacupRot, 0.0f, 1.0f, 0.0f);
            Shapes::drawCylinderNoEnds(8,5,4,5,false,0);
        glPopMatrix();
    }
    glPopMatrix();
}


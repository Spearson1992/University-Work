#include "Shapes.h"
#include "Vector.h"
#include <math.h>
void Shapes::drawCube(GLfloat width, GLfloat height, GLfloat depth, bool isTextured)
{
    if(isTextured)
        glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glTexCoord2f(1.0,0.0);
    glVertex3f(width, 0,0);
    glTexCoord2f(1.0,1.0);
    glVertex3f(width, height,0);
    glTexCoord2f(0.0,1.0);
    glVertex3f(0,height,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(0,0,0);
    ///////////////////////////////////////////////////////////
    glNormal3f(-1.0,0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex3f(0,0,depth);
    glTexCoord2f(1.0,1.0);
    glVertex3f(0,height,depth);
    glTexCoord2f(0.0,1.0);
    glVertex3f(0,height,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(0,0,0);
    ////////////////////////////////////////////////////////////
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(1.0,0.0);
    glVertex3f(0.0,0.0,depth);
    glTexCoord2f(1.0,1.0);
    glVertex3f(width,0.0,depth);
    glTexCoord2f(0.0,1.0);
    glVertex3f(width,height,depth);
    glTexCoord2f(0.0,0.0);
    glVertex3f(0.0,height,depth);
    /////////////////////////////////////////////////////////////
    glNormal3f(1.0,0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex3f(width,0.0,depth);
    glTexCoord2f(1.0,1.0);
    glVertex3f(width,0.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex3f(width,height,0.0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(width,height,depth);
    //////////////////////////////////////////////////////////////
    glNormal3f(0.0,1.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex3f(width,height,depth);
    glTexCoord2f(1.0,1.0);
    glVertex3f(width,height,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex3f(0.0,height,0.0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(0.0,height,depth);
    //////////////////////////////////////////////////////////////
    glNormal3f(0.0,-1.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex3f(width,0.0,depth);
    glTexCoord2f(1.0,1.0);
    glVertex3f(width,0.0,0.0);
    glTexCoord2f(0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(0.0,0.0,depth);
    glEnd();
    if(isTextured)
        glDisable(GL_TEXTURE_2D);
}
void Shapes::drawCone(GLfloat Sections, GLfloat height, GLfloat Radius,bool isTextured)
{
    if(isTextured)
        glEnable(GL_TEXTURE_2D);
    int sections = Sections;
    GLfloat radius = Radius;
    GLfloat twoPi = 2.0f * 3.14159f;
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5,0.5);
        glVertex3f(0,height,0);
        for(int j = 0; j <= sections; j++)
        {
            GLfloat angle = j*twoPi/sections;
            GLfloat nextAngle = (j*2)*twoPi/sections;
            Vector firstV(radius * cos(angle),0,radius * sin(angle));
            Vector SecondV(radius * cos(angle),height,radius * sin(angle));
            Vector Normal = firstV.crossProduct(SecondV);
            glNormal3f(Normal._x, Normal._y, Normal._z);
                glTexCoord2f((cos(angle)+1.0)*0.5,(sin(angle)+1.0)*0.5);
            glVertex3f(radius * cos(angle),0,radius * sin(angle));
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
}

void Shapes::drawCylinder(int Sections, GLfloat Radius, GLfloat Length, bool endsTextured, bool sidesTextured, int textureReps)
{
    GLfloat radius = Radius, halfLength = Length/2;
    GLfloat twoPi = 2.0f * 3.14159f;
    //glColor3f(1.0,1.0,1.0);
    if(endsTextured || sidesTextured)
        glEnable(GL_TEXTURE_2D);
    GLfloat sCoord;
    GLfloat tCoord;
    glBegin(GL_QUAD_STRIP);
        for(int i = 0; i <= Sections; i++)
        {
            if(sidesTextured)
            {
                sCoord = 1.0/(Sections/textureReps);
                tCoord = 1.0/(Sections/textureReps);
            }
            GLfloat angle = i*twoPi/Sections;
            Vector firstV(cos(angle), Length, sin(angle));
            Vector secondV(cos(angle), 0.0, sin(angle));
            Vector Normal = secondV.crossProduct(firstV);
            glNormal3f(Normal._x, Normal._y, Normal._z);
            if(sidesTextured)
                glTexCoord2f(sCoord*i,0.0);
            glVertex3f(radius* cos(angle), Length, radius *sin(angle));
            glNormal3f(Normal._x, Normal._y, Normal._z);
            if(sidesTextured)
                glTexCoord2f(sCoord*i,1.0);
            glVertex3f(radius * cos(angle), 0.0,radius * sin(angle));
        }
        
    glEnd();
    for(GLfloat i = Length; i >= 0.0; i = i - Length)
    {
        glBegin(GL_TRIANGLE_FAN);
        if(endsTextured)
            glTexCoord2f(0.5,0.5);      
        glVertex3f(0,i,0);
        for(int j = 0; j <= Sections; j++)
        {
            GLfloat angle = j*twoPi/Sections;
            if(i == 0.0)
            {
                glNormal3f(0.0,-1.0,0.0);
            }
            else
                glNormal3f(0.0,1.0,0.0);  
            if(endsTextured)
                glTexCoord2f((cos(angle)+1.0)*0.5,(sin(angle)+1.0)*0.5);
            glVertex3f(radius * cos(angle),i,radius * sin(angle));
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
}

void Shapes::drawCircle(int sections, GLfloat radius,GLfloat height, bool endsTextured)
{
    GLfloat twoPi = 2.0f * 3.14159f;
    glBegin(GL_TRIANGLE_FAN);
        if(endsTextured)
            glTexCoord2f(0.5,0.5);      
        glVertex3f(0,height,0);
        for(int j = 0; j <= sections; j++)
        {
            GLfloat angle = j*twoPi/sections;
                glNormal3f(0.0,1.0,0.0);  
            if(endsTextured)
                glTexCoord2f((cos(angle)+1.0)*0.5,(sin(angle)+1.0)*0.5);
            glVertex3f(radius * cos(angle),height,radius * sin(angle));
        }
        glEnd();
}
void Shapes::drawCylinderNoEnds(GLfloat sections, GLfloat topRadius,GLfloat bottomRadius, GLfloat length, bool sidesTextured, int textureReps)
{
    GLfloat twoPi = 2.0f * 3.14159f;
    GLfloat sCoord, tCoord;
    glBegin(GL_QUAD_STRIP);
        for(int i = 0; i <= sections; i++)
        {
            if(sidesTextured)
            {
                sCoord = 1.0/(sections/textureReps);
                tCoord = 1.0/(sections/textureReps);
            }
            GLfloat angle = i*twoPi/sections;
            Vector firstV(cos(angle), length, sin(angle));
            Vector secondV(cos(angle), 0.0, sin(angle));
            Vector Normal = secondV.crossProduct(firstV);
            glNormal3f(Normal._x, Normal._y, Normal._z);
            if(sidesTextured)
                glTexCoord2f(sCoord*i,0.0);
            glVertex3f(topRadius* cos(angle), length, topRadius *sin(angle));
            glNormal3f(Normal._x, Normal._y, Normal._z);
            if(sidesTextured)
                glTexCoord2f(sCoord*i,1.0);
            glVertex3f(bottomRadius * cos(angle), 0.0,bottomRadius * sin(angle));
        }
        
    glEnd();
}
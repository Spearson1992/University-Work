#include "Lights.h"

Light::Light(GLenum _light,GLfloat *light_position,GLfloat *light_ambient, GLfloat *light_diffuse,
        GLfloat *light_specular, GLfloat *spot_direction,
        GLfloat kc, GLfloat kl, GLfloat kq, GLfloat spot_cutoff, GLfloat spot_exponent)
        :light(_light), kC(kc), kL(kl), kQ(kq), spotCutOff(spot_cutoff), spotExponent(spot_exponent)
{
    if(light_position && light_ambient && light_diffuse && light_specular && spot_direction)
    {
        for(int i = 0; i < 4; i++)
        {
            lightPosition[i] = light_position[i];
            lightAmbient[i] = light_ambient[i];
            lightDiffuse[i] = light_diffuse[i];
            lightSpecular[i] = light_specular[i];
        }
        for(int i = 0; i < 3; i++)
            spotDirection[i] = spot_direction[i];
    }
    else if(light_position && light_ambient && light_diffuse && light_specular)
    {
        for(int i = 0; i < 4; i++)
        {
            lightPosition[i] = light_position[i];
            lightAmbient[i] = light_ambient[i];
            lightDiffuse[i] = light_diffuse[i];
            lightSpecular[i] = light_specular[i];
        }
        for(int i = 0; i < 3; i++)
            spotDirection[i] = 0;
    }
    else if(light_position && light_ambient && light_diffuse)
    {
        for(int i = 0; i < 4; i++)
        {
            lightPosition[i] = light_position[i];
            lightAmbient[i] = light_ambient[i];
            lightDiffuse[i] = light_diffuse[i];
            lightSpecular[i] = 0;
        }
        for(int i = 0; i < 3; i++)
            spotDirection[i] = 0;
    }
    else if(light_position && light_ambient)
    {
        for(int i = 0; i < 4; i++)
        {
            lightPosition[i] = light_position[i];
            lightAmbient[i] = light_ambient[i];
            lightDiffuse[i] = 0;
            lightSpecular[i] = 0;
        }
        for(int i = 0; i < 3; i++)
            spotDirection[i] = 0;
    }
    else if(light_position)
    {
        for(int i = 0; i < 4; i++)
        {
            lightPosition[i] = light_position[i];
            lightAmbient[i] = 0;
            lightDiffuse[i] = 0;
            lightSpecular[i] = 0;
        }
        for(int i = 0; i < 3; i++)
            spotDirection[i] = 0;
    }
    else
    {
        for(int i = 0; i < 4; i++)
        {
            lightPosition[i] = 0;
            lightAmbient[i] = 0;
            lightDiffuse[i] = 0;
            lightSpecular[i] = 0;
        }
        for(int i = 0; i < 3; i++)
            spotDirection[i] = 0;
    }
    
    glLightfv(light, GL_POSITION,lightPosition);
    glLightfv(light, GL_AMBIENT, lightAmbient);
    glLightfv(light,GL_DIFFUSE, lightDiffuse);
    glLightfv(light,GL_SPECULAR,light_specular);
    glLightf(light, GL_CONSTANT_ATTENUATION, kC);
    glLightf(light, GL_LINEAR_ATTENUATION, kL);
    glLightf(light, GL_QUADRATIC_ATTENUATION, kQ);
    if(spot_direction)
    glLightfv(light,GL_SPOT_DIRECTION,spotDirection);
    if(spot_cutoff)
    glLightf(light,GL_SPOT_CUTOFF,spotCutOff);
    if(spot_exponent)
    glLightf(light, GL_SPOT_EXPONENT, spotExponent);
}
Light::~Light()
{
}
void Light::setPosition(GLfloat *light_position)
{
    for(int i = 0; i < 4; i++)
        lightPosition[i] = light_position[i];
    glLightfv(light, GL_POSITION,lightPosition);
}
void Light::getPosition(GLfloat *light_position)
{
    for(int i = 0; i < 4; i++)
      light_position[i] = lightPosition[i];
}
void Light::setAmbient(GLfloat *light_ambient)
{
    for(int i = 0; i < 4; i++)
        lightAmbient[i] = light_ambient[i];
    glLightfv(light, GL_AMBIENT, lightAmbient);
}
void Light::setDiffuse(GLfloat *light_diffuse)
{
    for(int i = 0; i < 4; i++)
        lightDiffuse[i] = light_diffuse[i];
    glLightfv(light,GL_DIFFUSE, lightDiffuse);
}
void Light::setSpecular(GLfloat *light_specular)
{
    for(int i = 0; i < 4; i++)
        lightSpecular[i] = light_specular[i];
    glLightfv(light,GL_SPECULAR,light_specular);
}
void Light::setConstantAttenuation(GLfloat cATT)
{
    kC = cATT;
    glLightf(light, GL_CONSTANT_ATTENUATION, kC);
}
void Light::setLinearAttentuation(GLfloat lATT)
{
    kL = lATT;
    glLightf(light, GL_LINEAR_ATTENUATION, kL);
}
void Light::setQuadraticAttenuation(GLfloat qATT)
{
    kQ = qATT;
    glLightf(light, GL_QUADRATIC_ATTENUATION, kQ);
}
void Light::setSpotDirection(GLfloat *spot_direction)
{
    for(int i =0; i < 4; i++)
        spotDirection[i] = spot_direction[i];
    glLightfv(light,GL_SPOT_DIRECTION,spotDirection);
}
void Light::setSpotCutOff(GLfloat cutOff)
{
    spotCutOff = cutOff;
    glLightf(light,GL_SPOT_CUTOFF,spotCutOff);
}
void Light::setSpotExponent(GLfloat exponent)
{
    spotExponent = exponent;
    glLightf(light, GL_SPOT_EXPONENT, spotExponent);
}
void Light::enableLight()
{
    glEnable(light);
}
void Light::disableLight()
{
    glDisable(light);
}
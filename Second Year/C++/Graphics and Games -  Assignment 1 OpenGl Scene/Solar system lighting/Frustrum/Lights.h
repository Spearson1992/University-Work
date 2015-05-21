#ifndef Lights_h
#define Lights_h
#include <gl/glut.h>
class Light
{
public:
    Light(GLenum _light,GLfloat *light_position = 0,GLfloat *light_ambient = 0, GLfloat *light_Diffuse = 0,
        GLfloat *light_specular = 0, GLfloat *spot_direction = 0,
        GLfloat kc = 0, GLfloat kl = 0, GLfloat kq = 0, GLfloat spot_cutoff = 0, GLfloat spot_exponent = 0);
    ~Light();
    void setPosition(GLfloat *light_position);
    //returns light position in array passed to function
    void getPosition(GLfloat *light_position);
    void setAmbient(GLfloat *light_ambient);
    void setDiffuse(GLfloat *light_diffuse);
    void setSpecular(GLfloat *light_specular);
    void setConstantAttenuation(GLfloat cATT);
    void setLinearAttentuation(GLfloat lATT);
    void setQuadraticAttenuation(GLfloat qATT);
    void setSpotDirection(GLfloat *Spot_direction);
    void setSpotCutOff(GLfloat cutOff);
    void setSpotExponent(GLfloat exponent);
    void enableLight();
    void disableLight();
private:
    GLenum light;
    GLfloat lightPosition[4], lightAmbient[4], lightDiffuse[4], lightSpecular[4], spotDirection[3];
    GLfloat kC, kL,kQ;
    GLfloat spotCutOff, spotExponent;
};



#endif
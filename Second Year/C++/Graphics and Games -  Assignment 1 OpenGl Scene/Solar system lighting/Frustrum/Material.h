#ifndef Material_h
#define Material_h
#include <gl\glut.h>
class Material
{
public:
    //defines and enables material on creation, if no material reflectivities are passed all are set to 0
    Material(GLenum _face = GL_FRONT, GLfloat *matAmbient = 0, GLfloat *matDiffuse = 0, 
                   GLfloat *matSpecular = 0, GLfloat *matEmission = 0, GLfloat shininess = 0,bool enableShininess = false);
    ~Material();
    void setMaterialAmbient(GLfloat *mat_ambient);
    void setMaterialDiffuse(GLfloat *mat_diffuse);
    void setMaterialSpecular(GLfloat *mat_specular);
    void setMaterialShininess(GLfloat shininess);
    void setMaterialEmission(GLfloat *mat_emission);
    void setAmbientAndDiffuse(GLfloat *amb_and_diff);
    //sets opengl to use the material defined in this object
    void enableMaterial(bool enableAmbient = true, bool enableDiffuse = true, bool enableSpecular = true, bool enableEmission = true, bool enableShininess = true);
private:
    GLfloat materialAmbient[4], materialDiffuse[4], materialSpecular[4], materialEmission[4], materialShininess;
    GLenum face;
};

#endif
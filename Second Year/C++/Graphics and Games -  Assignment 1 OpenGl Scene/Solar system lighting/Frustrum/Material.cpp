#include "Material.h"
void Material::setMaterialAmbient(GLfloat *mat_ambient)
{
    for(int i = 0; i < 4; i++)
        materialAmbient[i] = mat_ambient[i];
    glMaterialfv(face, GL_AMBIENT, materialAmbient);
}
void Material::setMaterialDiffuse(GLfloat *mat_diffuse)
{
    for(int i = 0; i < 4; i++)
        materialDiffuse[i] = mat_diffuse[i];
    glMaterialfv(face,GL_DIFFUSE,materialDiffuse);
}
void Material::setMaterialSpecular(GLfloat *mat_specular)
{
    for(int i = 0; i < 4; i++)
        materialSpecular[i] = mat_specular[i];
    glMaterialfv(face, GL_SPECULAR, materialSpecular);
}
void Material::setMaterialEmission(GLfloat *mat_emission)
{
    for(int i = 0; i < 4; i++)
        materialEmission[i] = mat_emission[i];
    glMaterialfv(face, GL_EMISSION, materialEmission);
}
void Material::setMaterialShininess(GLfloat shininess)
{
    materialShininess = shininess;
    glMaterialf(face, GL_SHININESS, materialShininess);
}
void Material::setAmbientAndDiffuse(GLfloat *amb_and_diff)
{
    for(int i = 0; i < 4; i++)
    {
        materialAmbient[i] = amb_and_diff[i];
        materialDiffuse[i] = amb_and_diff[i];
    }
}
Material::Material(GLenum _face, GLfloat *matAmbient, GLfloat *matDiffuse, 
                   GLfloat *matSpecular, GLfloat *matEmission, GLfloat shininess, bool enableShininess)
                   :face(_face), materialShininess(shininess)
{
    if(matAmbient == 0)
    {
        for(int i = 0; i < 4; i++)
            materialAmbient[i] = 0;
    }
    else
    {
        for(int i = 0; i < 4; i++)
            materialAmbient[i] = matAmbient[i];
    }
    if(matDiffuse == 0)
    {
        for(int i = 0; i < 4; i++)
            materialDiffuse[i] = 0;
    }
    else
    {
        for(int i = 0; i < 4; i++)
        materialDiffuse[i] = matDiffuse[i];
    }
    if(matSpecular == 0)
    {
        for(int i = 0; i < 4; i++)
            materialSpecular[i] = 0;
    }
    else
    {
        for(int i = 0; i < 4; i++)
            materialSpecular[i] = matSpecular[i];
    }
    if(matEmission == 0)
    {
        for(int i = 0; i < 4; i++)
            materialEmission[i] = 0;
    }
    else
    {
        for(int i = 0; i < 4; i++)
            materialEmission[i] = matEmission[i];
    }
        glMaterialfv(face, GL_AMBIENT, materialAmbient);
        glMaterialfv(face,GL_DIFFUSE,materialDiffuse);
        glMaterialfv(face, GL_SPECULAR, materialSpecular);
    if(matEmission)
        glMaterialfv(face, GL_EMISSION, materialEmission);
    if(enableShininess)
        glMaterialf(face, GL_SHININESS, materialShininess);
}
void Material::enableMaterial(bool enableAmbient, bool enableDiffuse, bool enableSpecular, bool enableEmission, bool enableShininess)
{
    if(enableAmbient)
        glMaterialfv(face, GL_AMBIENT, materialAmbient);
    if(enableDiffuse)
        glMaterialfv(face,GL_DIFFUSE,materialDiffuse);
    if(enableSpecular)
        glMaterialfv(face, GL_SPECULAR, materialSpecular);
    if(enableEmission)
        glMaterialfv(face, GL_EMISSION, materialEmission);
    if(enableShininess)
        glMaterialf(face, GL_SHININESS, materialShininess);
}
Material::~Material()
{
}

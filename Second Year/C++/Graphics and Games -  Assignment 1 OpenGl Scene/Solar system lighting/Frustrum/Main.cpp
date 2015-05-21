/////////////////////////////////////////////////////////////////////////
// Camera controls adapted from those found on
// http://www.swiftless.com/tutorials/opengl/camera3.html.
// Texutres from Mayang's free texture library
// http://www.mayang.com/textures/.
//
//
//
//
//////////////////////////////////////////////////////////////////////////
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>
#include <GL/glut.h> 
#include "imageloader.h"
#include "Vector.h"
#include "Shapes.h"
#include "Camera.h"
#include "Lights.h"
#include "Material.h"
#include "Models.h"

float rot = 0, rot1 = 0, rot2 =0, teacupRot = 0, teacupBaseRot = 0, carouselRot = 0;
float orbit = 0;

GLfloat mat_diffuse[] = { 0.0, 0.0, 0.0, 0.0 };

//Toggles used for controlling the scene
bool lightEnabled = false;
bool flip = false;
bool frameToggle = false;
bool lbDown = false;
bool wireframeEnabled = true;
bool moveForward = false;
bool movebackWard = false;
bool isTextured = false;
bool smoothShadingEnabled = true;
bool toggleHUD = true;
int frames = 0, fps = 0, time = 0, lastTime = 0;
bool freeCamera = true, teacupRide = false, carouselRide = false;
int screenWidth = 0, screenHeight = 0, lineWidth = 1;
GLfloat zoomFactor = 1;

//images to be used as textures
Image *grassTexture = loadBMP("grass-texture-2.bmp");
Image *woodTexture = loadBMP("lightly_scratched_planks_7143300.bmp");
Image *pedestalTexture = loadBMP("marble_6110070.bmp");
Image *metalTexture = loadBMP("metal_3020588.bmp");
//screen centre variables
GLfloat middleX = 0, middleY = 0;
//carousel horse animation control variable
GLfloat lift = -2;
//display lists
GLuint displayLists; //Holds the display lists for the carousel
GLuint pedestalList; //Holds the display list for the pedestal
GLuint terrainList;  //Holds the display list for the terrain
GLuint teacupList;  // Holds the display list for the teacups

//opengl texture objects
GLuint grassTex;
GLuint woodTex;
GLuint pedestalTex; // holds marble texture for the pedestal
GLuint metalTex;

GLvoid *Font = GLUT_BITMAP_HELVETICA_12;
//Camera
Camera* viewCam = new Camera();
//Lights
Light *light1; //Sunlight
Light *light2; //Spotlight
Light *light3; //red teacup light
Light *light4; //green teacup light
Light *light5; //blue teacup light
//Materials
Material *floorMat;
Material *metal;
Material *ceramic;
extern Material *sunMat;

void reshape (int w, int h);
//void pickingRenderer(int x, int y);
void init()
{
	
   glEnable(GL_DEPTH_TEST);
	glLineWidth(1);			// Width of the drawing line	   
	glClearColor (0.0, 171.0, 235.0, 0.0); 
   glShadeModel (GL_SMOOTH);
   displayLists = glGenLists(4);
   pedestalList = glGenLists(1);
   terrainList = glGenLists(1);
   teacupList = glGenLists(2);
   glGenTextures(1, &grassTex);
   glGenTextures(1, &woodTex);
   glGenTextures(1, &metalTex);
   glGenTextures(1, &pedestalTex);
   glEnable(GL_LIGHTING);
}

void materialInit()
{
    GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat mat_shininess[] = { 5.0 };
    GLfloat mat_emission[] = { 0,0,0,1 };    
    floorMat = new Material(GL_FRONT, mat_ambient,mat_diffuse, mat_specular,mat_emission,128.0f,true);

    mat_specular[0] = 0.5f;
    mat_specular[1] = 0.5f;
    mat_specular[2] = 0.5f;
    metal = new Material(GL_FRONT, mat_ambient,mat_diffuse,mat_specular, mat_emission, 110.0f, true);

    GLfloat sun_ambient[] = {1.0,1.0,0.0,0.0};
    GLfloat sun_diffuse[] = {1.0,1.0,0.0,0.0};
    GLfloat sun_specular[] = {1.0,1.0,0.0,0.0};
    GLfloat sun_emission[] = {1.0,1.0,0.0,0.0};    
    sunMat = new Material(GL_FRONT, sun_ambient, mat_diffuse,sun_specular,sun_emission,0,true);

    GLfloat ceramic_ambient[] = {0.1,0.1,0.5,0.0};
    GLfloat ceramic_diffuse[] = {0.1,0.1,0.5,0.0};
    GLfloat ceramic_specular[] = {1.0,1.0,1.0,0.0};
    GLfloat ceramic_emission[] = {0.0,0.0,0.0,0.0};
    ceramic = new Material(GL_FRONT, ceramic_ambient, ceramic_diffuse, ceramic_specular, ceramic_emission,90.0f, true);
}

void renderInit()
{
    glNewList(displayLists, GL_COMPILE);
    floorMat->enableMaterial(true,true,true,false,false);
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, woodTex);
    Shapes::drawCylinder(32,10,0.5, true,false,1);        //draw carousel base
    glEndList();
    /////////////////////////////////////
    glNewList(displayLists+1, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D,metalTex);
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0.0,0.5,0.0);
    Shapes::drawCylinder(32,8,0.5, true,true,1);         //draw rotating base
    glTranslatef(0.0,0.0,0.0);
    glColor3f(0.75f,0.0f,0.0f);
    Shapes::drawCylinder(8,2,10, false,true,1);          //draw central pillar
    glPushMatrix();
    glTranslatef(0.0,8.0,0.0);
    glColor3f(0.8,0.498039,0.196078);
    Shapes::drawCylinder(32, 8, 2, true,true,1);         //draw roof
    glPushMatrix();
    glTranslatef(0.0, 1.0,0.0);
    Shapes::drawCone(32,4,6, true);
        glPopMatrix();
    glPopMatrix();
    glEndList();
    //////////////////////////////////
    glNewList(displayLists+2,GL_COMPILE);
    glColor3f(0.8,0.498039,0.0);
    metal->enableMaterial();
    glTranslatef(0.0f,4.0f,0.0f);
    Shapes::drawCylinder(8, 0.2, 10, false,false, 0);   //draw poles
    glEndList();
    /////////////////////////////////
    //draw horses
    /////////////////////////////////
    glNewList(displayLists+3,GL_COMPILE);
    glColor3f(0.647059,0.164706, 0.164706);
    glTranslatef(0.0f,6.0f,0.0f);
    Shapes::drawCube(2,1,1, false);
    glPushMatrix();
    glTranslatef(0.0,0.75,0.25);
    glRotatef(30,0.0,0.0,1.0);
    Shapes::drawCube(0.5,1,0.5,false);
    glPopMatrix();
    glEndList();
    ////////////////////////////////
    glNewList(pedestalList,GL_COMPILE);
    drawPedestal();
    glEndList();
    /////////////////////////////////
    glNewList(terrainList, GL_COMPILE);
    drawTerrain();
    glEndList();
    /////////////////////////////////
    glNewList(teacupList, GL_COMPILE);
    glColor3f(0.4,0.2,0.0);
    Shapes::drawCylinder(32,22,0.25,false,false,0);    //draw base
    glColor3f(0.2,0.5,0.0);
    metal->enableMaterial();
    for(int rotation = 0; rotation < 360; rotation +=45)
    {
        glPushMatrix();
            glRotatef(rotation,0.0f,1.0f,0.0f);
            glTranslatef(0.0f,0.5f,21.0f);
            Shapes::drawCylinder(8,0.2,20,false,false,0); // draw poles
        glPopMatrix();
    }
    floorMat->enableMaterial();
    glPushMatrix();
    glColor3f(0.4,0.1,0.0);
        glTranslatef(0.0f,20.f,0.0f);
        Shapes::drawCylinder(32,22,2,false,false,0); //draw roof
        ///////////////////////////////////////////////////////////////////////
        // draw red light
        ///////////////////////////////////////////////////////////////////////
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
            glTranslatef(0.0f,-0.5f,-18.0f);
            Shapes::drawCylinder(8,0.1,0.6,false,false,0); //draw light support
            glTranslatef(-0.25f, -1.0, 0.0);
            glRotatef(-20,1.0,0.0,0.0);
            Shapes::drawCube(0.5,1.0,0.5,false);  //draw light box
            glTranslatef(0.3,-0.2,0.3);
            Shapes::drawCone(8,0.3,0.5,0); //  draw light cone
            glRotatef(10,1.0,0.0,0.0);
            glPushMatrix();
            {
                GLfloat lightPos[] = {0.0,0.0,0.0,1.0};
                GLfloat spot_direction[] = {0.0,-1.0,0.0};
                light3->setPosition(lightPos);
                light3->setSpotDirection(spot_direction);
            }
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        ///////////////////////////////////////////////////////////////////////
        // draw green light
        ///////////////////////////////////////////////////////////////////////
        glRotatef(120,0.0f,1.0f,0.0f);
            glTranslatef(0.0f,-0.5f,-18.0f);
            Shapes::drawCylinder(8,0.1,0.6,false,false,0); //draw light support
            glTranslatef(-0.25f, -1.0, 0.0);
            glRotatef(-20,1.0,0.0,0.0);
            Shapes::drawCube(0.5,1.0,0.5,false);
            glTranslatef(0.3,-0.2,0.3);
            Shapes::drawCone(8,0.3,0.5,0);
            glRotatef(10,1.0,0.0,0.0);
            glPushMatrix();
            {
                GLfloat lightPos[] = {0.0,0.0,0.0,1.0};
                GLfloat spot_direction[] = {0.0,-1.0,0.0};
                light4->setPosition(lightPos);
                light4->setSpotDirection(spot_direction);
            }
            glPopMatrix();
        glPopMatrix();
    glPushMatrix();
    ///////////////////////////////////////////////////////////////////////
    // draw blue light
    ///////////////////////////////////////////////////////////////////////
        glRotatef(240,0.0f,1.0f,0.0f);
            glTranslatef(0.0f,-0.5f,-18.0f);
            Shapes::drawCylinder(8,0.1,0.6,false,false,0); //draw light support
            glTranslatef(-0.25f, -1.0, 0.0);
            glRotatef(-20,1.0,0.0,0.0);
            Shapes::drawCube(0.5,1.0,0.5,false);
            glTranslatef(0.3,-0.2,0.3);
            Shapes::drawCone(8,0.3,0.5,0);
            glRotatef(10,1.0,0.0,0.0);
            glPushMatrix();
            {
                GLfloat lightPos[] = {0.0,0.0,0.0,1.0};
                GLfloat spot_direction[] = {0.0,-1.0,0.0};
                light5->setPosition(lightPos);
                light5->setSpotDirection(spot_direction);
            }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glEndList();
}
void lightInit()
{
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLfloat light_position[] = { 1.0, 0.0, 1.0, 0.0 };
    GLfloat lightAmbient[] = {0.0,0.0,0.0,1.0};
    GLfloat lightDiffuse[] = {1.0,1.0,1.0,1.0};
    GLfloat lightSpecular[] = {1.0,1.0,1.0,1.0};
    GLfloat s1pot_direction[] = {0.0,-1.0,0.0};
    light1 = new Light(GL_LIGHT0,light_position,lightAmbient, lightDiffuse, lightSpecular,0,1,0.0,0,0,0);
    light1->enableLight();
    light_position[0] = 0.0f;
    light_position[1] = 0.0f;
    light_position[2] = 0.0f;
    light_position[3] = 1.0f;
    GLfloat spot_direction[] = {0.0,0.0,-1.0};
    light2 = new Light(GL_LIGHT1,light_position,lightAmbient, lightDiffuse, lightSpecular,spot_direction,1,0.0,0.0,60,20);
    lightDiffuse[0] = 1.0f;
    lightDiffuse[1] = 0.0f;
    lightDiffuse[2] = 0.0f;
    lightDiffuse[3] = 0.0f;
    lightSpecular[0] = 1.0f;
    lightSpecular[1] = 0.0f;
    lightSpecular[2] = 0.0f;
    lightSpecular[3] = 0.0f;
    light3 = new Light(GL_LIGHT2,light_position,lightAmbient, lightDiffuse, lightSpecular,spot_direction, 1.0, 0.0,0.0,40,0);
    lightDiffuse[0] = 0.0f;
    lightDiffuse[1] = 1.0f;
    lightSpecular[0] = 0.0f;
    lightSpecular[1] = 1.0f;
    light4 = new Light(GL_LIGHT3,light_position,lightAmbient, lightDiffuse, lightSpecular,spot_direction, 1.0, 0.0,0.0,40,0);
    lightDiffuse[1] = 0.0f;
    lightDiffuse[2] = 1.0f;
    lightSpecular[1] = 0.0f;
    lightSpecular[2] = 1.0f;
    light5 = new Light(GL_LIGHT4,light_position,lightAmbient, lightDiffuse, lightSpecular,spot_direction, 1.0, 0.0,0.0,40,0);
    glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
}

void menuHandler(int id)
{
    switch (id)
    {
    case 1:
        teacupRide = false;
        carouselRide = false;
        freeCamera = false;
        break;
    case 2:
        teacupRide = true;
        carouselRide = false;
        freeCamera = false;
        break;
    case 3:
        carouselRide = true;
        teacupRide = false;
        freeCamera = false;
        break;
    case 4: 
        teacupRide = false;
        carouselRide = false;
        freeCamera = true;
        break;
    case 5:
        glLineWidth(++lineWidth);
        break;
    case 6:
        glLineWidth(--lineWidth);
    default:
        break;
    }
    glutPostRedisplay();
}
void menuInit()
{
    int menu;
    menu = glutCreateMenu(menuHandler);
    glutAddMenuEntry("Orbit camera", 1);
    glutAddMenuEntry("Ride the teacups", 2);
    glutAddMenuEntry("Ride the carousel",3);
    glutAddMenuEntry("Free camera" , 4);
    glutAddMenuEntry("Increase line width", 5);
    glutAddMenuEntry("Decrease line width", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void mouseHandler(int button, int state, int x, int y)
{
    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
    {
        lbDown = false;
        glutSetCursor(GLUT_CURSOR_INHERIT);
    }
    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        lbDown = true;
        glutWarpPointer(viewCam->middleX,viewCam->middleY);        
    }

}

void mouseCoords(int x, int y)
{
    if(lbDown)
    {
        glutSetCursor(GLUT_CURSOR_NONE);
        viewCam->updateMousePos(x,y);
    }
}

void calcFPS()
{
    frames++;

    time = glutGet(GLUT_ELAPSED_TIME);

    int elapsedTime = time - lastTime;

    if(elapsedTime > 1000)
    {
        fps = frames / (elapsedTime / 1000);

        lastTime = time;

        frames = 0;
    }
}

void texInit()
{
	glBindTexture(GL_TEXTURE_2D, grassTex);
    glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D,
							0,
							GL_RGB,
                            grassTexture->width,
                            grassTexture->height,
							0,
							GL_RGB,
							GL_UNSIGNED_BYTE,
                            grassTexture->pixels);
            glBindTexture(GL_TEXTURE_2D, woodTex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D,
							0,
							GL_RGB,
                            woodTexture->width,
                            woodTexture->height,
							0,
							GL_RGB,
							GL_UNSIGNED_BYTE,
                            woodTexture->pixels);
            glBindTexture(GL_TEXTURE_2D, pedestalTex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D,
							0,
							GL_RGB,
                            pedestalTexture->width,
                            pedestalTexture->height,
							0,
							GL_RGB,
							GL_UNSIGNED_BYTE,
                            pedestalTexture->pixels);
            glBindTexture(GL_TEXTURE_2D, metalTex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D,
							0,
							GL_RGB,
                            metalTexture->width,
                            metalTexture->height,
							0,
							GL_RGB,
							GL_UNSIGNED_BYTE,
                            metalTexture->pixels);
            delete grassTexture;
            delete woodTexture;
            delete pedestalTexture;
            delete metalTexture;

}
void onKeyPress(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
    case 27:
        delete viewCam;
        delete light1;
        delete light2;
        delete light3;
        delete light4;
        delete light5;
        delete floorMat;
        delete sunMat;
        delete metal;
        delete ceramic;
        exit(0);
	case'a':
        if(zoomFactor > 1.9)
            zoomFactor = 1.9;
        else
            zoomFactor += 0.1; 

        reshape(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
   break;
	case 'd':
        if(zoomFactor < 0.1)
            zoomFactor = 0.1;
        else
            zoomFactor -= 0.1;
        reshape(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
   break;
    case 'w':
        viewCam->cameraX += sin(viewCam->toRadians(viewCam->yRotation));
        viewCam->cameraZ -= cos(viewCam->toRadians(viewCam->yRotation));
        viewCam->cameraY -= sin(viewCam->toRadians(viewCam->xRotation));
        break;
    case 's':
        viewCam->cameraX -= sin(viewCam->toRadians(viewCam->yRotation));
        viewCam->cameraZ += cos(viewCam->toRadians(viewCam->yRotation));
        viewCam->cameraY += sin(viewCam->toRadians(viewCam->xRotation));
        break;
		case 'l':
            if(lightEnabled)
			{
                light1->enableLight();
                light2->disableLight();
                light3->disableLight();
                light4->disableLight();
                light5->disableLight();
                glClearColor (0.0, 171.0, 235.0, 0.0); 
                lightEnabled = false;
			}
			else
			{
                light1->disableLight();
                light2->enableLight();
                light3->enableLight();
                light4->enableLight();
                light5->enableLight();
                glClearColor(0.0,0.0,0.0,0.0);
				lightEnabled = true;
			}
			break;
        case 'k':
            if(wireframeEnabled)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                wireframeEnabled = false;
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                wireframeEnabled = true;
            }
            break;
        case 'j':
            if(smoothShadingEnabled)
            {
                glShadeModel(GL_FLAT);
                smoothShadingEnabled = false;
            }
            else
            {
                glShadeModel(GL_SMOOTH);
                smoothShadingEnabled = true;
            }
            break;
        case 'h':
            if(toggleHUD)
                toggleHUD = false;
            else
                toggleHUD = true;
            break;
	}
	glutPostRedisplay();
}
void update()
{
	if(rot<360)
		rot +=1;
	else
		rot=1;

	if(rot1<360)
		rot1 +=0.5;
	else
		rot1=0.5;

	if(rot2<360)
		rot2 +=0.25;
	else
		rot2=0.25;
    if(orbit > 360)
        orbit = 0.1;
    else
        orbit += 0.1;
        if(teacupRot < 360)
            teacupRot += 2.0f;
        else
            teacupRot = 2.0f;
        if(teacupBaseRot > -360)
            teacupBaseRot -= 1.0f;
        else
            teacupBaseRot = -1.0f;
        if(carouselRot<360)
		    carouselRot +=1;
	    else
		    carouselRot=1;
        if(lift <= -1.5 && lift >= -3 && !flip)
        {
            if(lift <= -2.9)
             {
                 flip = true;
                 return;
             }
             lift -=0.01;
         
        }
        else if(lift <= 1.5 && lift >= -3 && flip)
        {
            if(lift >= -1.6)
             {
                 flip = false;
                 return;
             }
             lift +=0.01;
         
        }
	glutPostRedisplay();
}


void drawText2d(const char *text,int x, int y,void *font)
{
    glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            glLoadIdentity();
            glOrtho(0,screenWidth,0,screenHeight,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
            glColor3f(1.0,1.0,1.0);
        glRasterPos2i(x,y);

        while (*text)
        {
            glutBitmapCharacter(font,*text);
            ++text;
        }
        glPopMatrix();
    glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawHUD()
{
    //draw fps counter
    std::stringstream fpsVar;    
    fpsVar << "FPS: " << fps;
    std::string temp = fpsVar.str();
    drawText2d(temp.c_str(),10,screenHeight -10,Font);

    //draw camera position
    std::stringstream camString;
    camString << "Camera X: " << viewCam->cameraX << " " 
        << "Camera Y: " << viewCam->cameraY << " "
        << "Camera Z: " << viewCam->cameraZ;
    temp = camString.str();
    drawText2d(temp.c_str(), 10, screenHeight - 30, Font);

    std::stringstream rotString;
    rotString << "Camera X Rotation: " << viewCam->xRotation << " " 
        << "Camera Y Rotation: " << viewCam->yRotation;
    temp = rotString.str();
    drawText2d(temp.c_str(), 10, screenHeight - 50, Font);

    std::stringstream toggleString;
    toggleString << "Lighting enabled: " << !lightEnabled << " " << "Wireframe Enabled: " << !wireframeEnabled
        << " " << "Smooth Shading enabled: " << smoothShadingEnabled;
    temp = toggleString.str();
    drawText2d(temp.c_str(), 10, screenHeight - 70, Font);
}
void displayAxes(GLfloat x,GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();
    glPopMatrix();

	//glColor3f(0.5,0.5,1.0);
}


//////////////////////////////////////////////////////

void display()
{
  glColor3f(1.0,1.0,1.0); 
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
  glMatrixMode(GL_MODELVIEW); // Set matrix mode
  glLoadIdentity();
  ///////////////////////////////////////////////////////////////////////////////////
  //                         camera transformations                               //
  /////////////////////////////////////////////////////////////////////////////////
  if(freeCamera)
  {
      // move camera freely
      glRotatef(viewCam->xRotation,1.0,0.0,0.0);
      glRotatef(viewCam->yRotation,0.0,1.0,0.0);
      if(viewCam->cameraY < 1)
          viewCam->cameraY = 1;
      glTranslatef(-viewCam->cameraX,-viewCam->cameraY,-viewCam->cameraZ);
  }
  else if(teacupRide)
  { 
    /*apply transformations in reverse order and negate their original values
      inverse transformation matrix is needed to appear to rotate the camera when it is actually the
      world that is rotating.
      Produces a view that appears to ride the teacup ride*/
      glRotatef(-teacupRot, 0.0f, 1.0f, 0.0f);
      glTranslatef(0.0f,-4.0f,-15.0f);
      glRotatef(-teacupBaseRot, 0.0f, 1.0f, 0.0f);
      glTranslatef(-50.0f, -5.5f, 50.0f);
  }
  else if(carouselRide)
  {
      //transform the camera to ride the carousel
      glRotatef(viewCam->xRotation,1.0,0.0,0.0);
      glRotatef(viewCam->yRotation,0.0,1.0,0.0);
      glTranslatef(1.0,-lift+5.5,-5.5);
      glRotatef(carouselRot,0.0,1.0,0.0);
      glTranslatef(30.0f,-14.0f,0.0f);
  }
  else
  {
      //orbit the camera around the origin
      gluLookAt(-50,30,-50,0,0,0,0,1,0);
      glRotatef(orbit,0.0,1.0,0.0);
  }
  ////////////////////////////////////////////////////////////////////////////////
  glPushMatrix();
    glCallList(terrainList);
    drawFence();
  glPopMatrix();
  glPushMatrix();
      glTranslatef(50.0f, 0.0f, -50.0f);
      drawTeaCups();
      glColor3f(1.0f,1.0f,1.0f);
  glPopMatrix();
  glPushMatrix();
    glCallList(pedestalList);
  glPopMatrix();
  glPushMatrix();
      glTranslatef(2.5f, 10.0f, 2.5f);
      glScalef(0.2,0.2,0.2);
      drawSolarSystem();
  glPopMatrix();
  glPushMatrix();
      glTranslatef(-30.0,0.0,0.0);
      drawCarousel();
  glPopMatrix();
  calcFPS();
  if(toggleHUD)
    drawHUD();
  glutSwapBuffers();
}

///////////////////////////////////////////////////////////

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);	// Viewport mapping
   // Projection transformation
  glMatrixMode(GL_PROJECTION); 	// Set matrix mode	
  glLoadIdentity(); 			// Clear
  if(h==0) //prevent division by zero when scaling view
  {
	  h=1;
  }
  viewCam->computeMidpoint();
  screenWidth = glutGet(GLUT_WINDOW_WIDTH);
  screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
  gluPerspective(60 * zoomFactor, (float) w/h, .1, 250); 	// define and adjust projection
  glMatrixMode(GL_MODELVIEW);		// reset the matrix mode
}
///////////////////////////////////////////////////////////////

int main(int argc, char** argv) 
{
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
  glutInitWindowSize(300,300); 
  glutCreateWindow("Assignment 1 - Theme park");
  init();
  lightInit();
  materialInit();
  renderInit();
  texInit();
  menuInit();
  gluLookAt(0,0,20,0,0,0,0,1,0);
  glutIdleFunc(update);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(onKeyPress);
  glutMouseFunc(mouseHandler);
  glutMotionFunc(mouseCoords);
  glutMainLoop(); 
 
}

/*
 1089909_0611478
 LYNX
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <mmsystem.h>
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"

using namespace std;

const int X_MAX=1;
const int X_MIN=-1;
const int Y_MAX=1;
const int Y_MIN=-1;
const double DELTA= 0.1;
double dirX=DELTA;//derecha x=-1,Y=0 IZQUIERDA, X=0;Y=-1 ABAJO, X=0,Y=1 ARRIBA
double dirY=0.0;
int altoV = 480;
int anchoV = 640;
char msg[40];
string msg1;
string msgscore;
int crece=0;
int opcion = 1;
int ortho = 1;
int nivel = 2;
int limite = 24;
int flagtextmaster = 1; //Bandera de control en cambio de figura
int resp = 0;
char* sdplay = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/sonido/gameplay.wav";
char* sdcorrect = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/sonido/correct.wav";
char* sderror = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/sonido/error.wav";

int score = 0; //score
int minutos = 2;
int segundos = 0;
int pantalla = 1; //bandera para pantallas

/* GLUT callback Handlers */
float x=50;
float y=50;
float angle=0;
float fline=0;
static GLuint texName[36];
int colorCubo1=1;
int colorCubo2=2;
int colorCubo3=3;
int cubol1=0;
int cubol=0;
int textmaster=0;
int swapt=0;//Variable de cambio de pantalla en imagenes

int myrandom (int i) { return rand()%i;}
vector<int> thevector;
vector<int>::iterator it;

GLfloat light_ambient[] = { 0.4,0.4,0.4,1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light_position[] = {3.0, 0.0, 0.0, 1.0 };
GLfloat light_position1[] = {-3.0, 0.0, 0.0, 1.0 };

GLfloat mat_ambient[] = {0.2,0.2,0.2,1.0};
GLfloat mat_diffuse[][5] = {{0.0f, 0.0f, 0.0f, 1.0f},
                            {1.0f, 0.0f, 0.0f, 1.0f},
                            {0.0f, 1.0f, 0.0f, 1.0f},
                            {0.0f, 0.0f, 1.0f, 1.0f},
                            {0.0f, 0.65f, 0.15f, 1.0f},
                            {0.42f, 0.45f, 0.22f, 1.0f},
                            {0.5f, 0.0f, 0.0f, 1.0f}};
GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};

void theRandom(){
    //srand ( unsigned ( std::time(0) ) );

    for (int i=0; i<limite; ++i)
        thevector.push_back(i);
    random_shuffle (thevector.begin(), thevector.end());
    random_shuffle (thevector.begin(), thevector.end(), myrandom);

    /*cout << "myvector contains:";
      for (vector<int>::iterator it=thevector.begin(); it!=thevector.end(); it++)
        cout << ' ' << *it;

      cout << '\n';*/
}

void initRandom(){
    srand ( unsigned ( std::time(0) ) );

    for (int i=0; i<limite; ++i)
        thevector.push_back(i);
    random_shuffle (thevector.begin(), thevector.end());
    random_shuffle (thevector.begin(), thevector.end(), myrandom);
}

void loadTexture(Image* image, int k) {

	glBindTexture(GL_TEXTURE_2D, texName[k]);

	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
}

GLuint _textureId;

void initRendering() {
    GLuint i=0;
    glGenTextures(40, texName);
    Image* image;
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img1.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img2.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img3.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img4.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img5.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img6.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img7.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img8.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img9.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img10.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img11.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img12.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img13.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img14.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img15.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img16.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img17.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img18.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img19.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img20.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img21.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img22.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img23.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img24.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img25.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img26.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img27.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img28.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img29.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img30.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img31.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img32.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img33.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img34.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img35.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img36.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img37.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img38.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img39.bmp");loadTexture(image,i++);
	image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img40.bmp");loadTexture(image,i++);
	delete image;
}

static void init()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glClearColor(0.3,0.3,0.3,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
    //PlaySound(sdplay,NULL, SND_ASYNC|SND_NOSTOP);
}

void draw3dString (void *font, char *s, float x, float y, float z) {
    unsigned int i;
    glPushMatrix();
    glTranslatef(x, y, z);

    glScaled(0.1, 0.1, 0.1);
    //glRotatef(xMin, 1, 1, 0);
    for (i = 0; i < s[i] != '\0'; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
    glPopMatrix();
}

void colorCubo(int x){

    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);

    switch (x){
        case 1: glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[1]);
            break;
        case 2: glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[2]);
            break;
        case 3: glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[3]);
            break;
        case 4: glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[4]);
            break;
        case 5: glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[5]);
            break;
        default: glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[0]);
            break;
    }

    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
}

void drawQuad(){

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[*it]);

	if (it!=thevector.end())
        it++;
    else
        it=thevector.begin();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glScalef(0.15,0.15,0.15);
    glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void levelOne(){

    float tx=-1.2;
    fline=-.8;
    angle=25;

    //First Row
    for (int i=0; i<5; i++){
        glPushMatrix();
        glTranslatef(tx,.3,fline);
        glRotatef(angle, 0, 1, 0);
        if ((i+1)==cubol1)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.4);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.4);

        if (textmaster == *it)
            resp = i+1;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.6;
        angle-=12.5;
        if (i<2)
            fline-=.055;
        else
            fline+=.055;
    }

    //Second Row
    tx=-1.2;
    angle=25;
    fline=-.8;

    for (int i=0; i<5; i++){
        glPushMatrix();
        glTranslatef(tx,-.3,fline);
        glRotatef(angle, 0, 1, 0);
        if ((i+6)==cubol1)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.4);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.4);

        if (textmaster == *it)
            resp = i+6;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.6;
        angle-=12.5;
        if (i<2)
            fline-=.055;
        else
            fline+=.055;
    }

    //Third Row
    tx=-1.2;
    angle=25;
    fline=-.8;

    for (int i=0; i<5; i++){
        glPushMatrix();
        glTranslatef(tx,-.9,fline);
        glRotatef(angle, 0, 1, 0);
        glRotatef(-15, 1, 0, 0);
        if ((i+11)==cubol1)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.4);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.4);

        if (textmaster == *it)
            resp = i+11;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.6;
        angle-=12.5;
        if (i<2)
            fline-=.075;
        else
            fline+=.075;
    }

    //cout << "El cubo -> ";
    //cout << resp;
    //cout << *it;
    //cout << "\n";
}

void levelTwo(){
    float tx=-1.25;
    fline=-.8;
    angle=25;

    //First Row
    for (int i=0; i<6; i++){
        glPushMatrix();
        glTranslatef(tx,.3,fline);
        glRotatef(angle, 0, 1, 0);
        if ((i+1)==cubol)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.35);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.35);

        if (textmaster == *it)
            resp = i+1;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.5;
        if (i<2){
            fline-=.025;
            angle-=12.5;
        }
        else if (i>3){
            fline+=.025;
            angle-=12.5;
        }
    }

    tx=-1.25;
    fline=-.8;
    angle=25;
    //Second Row
    for (int i=0; i<6; i++){
        glPushMatrix();
        glTranslatef(tx,-.15,fline);
        glRotatef(angle, 0, 1, 0);
        if ((i+7)==cubol)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.35);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.35);

        if (textmaster == *it)
            resp = i+7;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.5;
        if (i<2){
            fline-=.025;
            angle-=12.5;
        }
        else if (i>3){
            fline+=.025;
            angle-=12.5;
        }
    }

    tx=-1.25;
    fline=-.8;
    angle=25;
    //Third Row
    for (int i=0; i<6; i++){
        glPushMatrix();
        glTranslatef(tx,-.6,fline);
        glRotatef(angle, 0, 1, 0);
        if ((i+13)==cubol)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.35);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.35);

        if (textmaster == *it)
            resp = i+13;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.5;
        if (i<2){
            fline-=.025;
            angle-=12.5;
        }
        else if (i>3){
            fline+=.025;
            angle-=12.5;
        }
    }

    tx=-1.25;
    fline=-.8;
    angle=25;
    //Forth Row
    for (int i=0; i<6; i++){
        glPushMatrix();
        glTranslatef(tx,-1.15,fline);
        glRotatef(angle, 0, 1, 0);
        glRotatef(-15, 1, 0, 0);
        if ((i+19)==cubol)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.35);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.35);

        if (textmaster == *it)
            resp = i+19;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.5;
        if (i<2){
            fline-=.025;
            angle-=12.5;
        }
        else if (i>3){
            fline+=.025;
            angle-=12.5;
        }
    }
}

void levelThree(){
    float tx=-1.4;
    fline=-.8;
    angle=25;

    //First Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,.3,fline);
        glRotatef(angle, 0, 1, 0);
        if ((i+1)==cubol1)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        if (textmaster == *it)
            resp = i+1;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.4;
        if (i<3){
            fline-=.025;
            angle-=(25/3);
        }
        else if (i>4){
            fline+=.025;
            angle-=(25/3);
        }
    }

    tx=-1.4;
    fline=-.8;
    angle=25;
    //Second Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,-0.1,fline);
        glRotatef(angle, 0, 1, 0);
        if ((i+9)==cubol1)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        if (textmaster == *it)
            resp = i+9;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.4;
        if (i<3){
            fline-=.025;
            angle-=(25/3);
        }
        else if (i>4){
            fline+=.025;
            angle-=(25/3);
        }
    }

    tx=-1.4;
    fline=-.8;
    angle=25;

    //Third Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,-0.5,fline);
        glRotatef(angle, 0, 1, 0);
        if ((i+17)==cubol1)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        if (textmaster == *it)
            resp = i+17;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.4;
        if (i<3){
            fline-=.025;
            angle-=(25/3);
        }
        else if (i>4){
            fline+=.025;
            angle-=(25/3);
        }
    }

    tx=-1.4;
    fline=-.8;
    angle=25;
    //Forth Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,-0.9,fline);
        glRotatef(angle, 0, 1, 0);
        glRotatef(-10, 1, 0, 0);
        if ((i+25)==cubol1)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        if (textmaster == *it)
            resp = i+25;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();
        tx+=0.4;
        if (i<3){
            fline-=.025;
            angle-=(25/3);
        }
        else if (i>4){
            fline+=.025;
            angle-=(25/3);
        }
    }

    tx=-1.4;
    fline=-.8;
    angle=25;
    //Fifth Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,-1.3,fline);
        glRotatef(angle, 0, 1, 0);
        glRotatef(-10, 1, 0, 0);
        if ((i+33)==cubol1)
            colorCubo(4);
        else
            colorCubo(5);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        if (textmaster == *it)
            resp = i+33;

        glPushMatrix();
        drawQuad();
        glPopMatrix();

        glPopMatrix();

        tx+=0.4;
        if (i<3){
            fline-=.025;
            angle-=(25/3);
        }
        else if (i>4){
            fline+=.025;
            angle-=(25/3);
        }
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);

    glLineWidth(3);// 10 pixels  recuerda que la ventana va de -1 a 1  en y y en x

    if (pantalla == 0){
        glPushMatrix();
        glScaled(0.6, 0.6, 0.6);
        glColor3f(0.0,0.0,0.0);
        sprintf(msg,"%s", "Click izquierdo con mouse para iniciar juego");
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1, 0, 0);
        sprintf(msg,"%s", "Click derecho con mouse para regresar");
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1, -.5, 0);
        glPopMatrix();
    }

    if (pantalla == 1){
        glPushMatrix();
        glTranslatef(0,1.2,-.8);
        glRotatef(20, 1.0, 0.0, 0.0);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[3]);
        glutSolidCube(0.5);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.5);

        ///////////////
        glPushMatrix();
        glTranslatef(0.5,0.1,0);
        glScaled(0.015, 0.015, 0.015);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[1]);
        sprintf(msg,"%s%d", "Score: ", score);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1, -.9, 0);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-1.25,0.1,0.0);
        glScaled(0.015, 0.015, 0.015);
        sprintf(msg, "%d %s %d", minutos, ":", segundos);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1, -.9, 0);
        glPopMatrix();

        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[3]);
        glPushMatrix();

        if (flagtextmaster == 1){

            switch (nivel){
                case 1: textmaster = rand() % 15; break;
                case 2: textmaster = rand() % 24; break;
                case 3: textmaster = rand() % 40; break;
                default: textmaster = rand() % 15; break;
            }
            flagtextmaster = 0;
        }
        //cout << "El master -> " << textmaster << endl;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texName[textmaster]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glScalef(0.15,0.15,0.15);
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 2.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 2.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 2.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 2.0f);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPopMatrix();

        if (nivel==1){
            it=thevector.begin();
            limite=15;
            levelOne();
        } else if (nivel==2){
            it=thevector.begin();
            limite=24;
            levelTwo();
        } else if (nivel==3){
            it=thevector.begin();
            limite=40;
            levelThree();
        }

        sprintf(msg,"%s%d", "Score:", score);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -0.9, .7, 0);

        sprintf(msg, "%d %s %d", minutos, ":", segundos);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, .4, .7, 0);
    }

    glutSwapBuffers();//por defaul invoca al glFlush();
}

void swapTimer(int valor){

    if (swapt == 5){
        thevector.clear();
        theRandom();
        it=thevector.begin();
        PlaySound(sderror,NULL, SND_ASYNC);
        flagtextmaster = 1;
        swapt=0;
        glutPostRedisplay();
    } else
        swapt++;

    glutTimerFunc(1000,swapTimer,1);
}

void myTimer( int valor){

    if(pantalla == 1 )
    {

        segundos--;
        if(segundos == -1)
        {
            segundos = 59;
            minutos--;
        }
        glutPostRedisplay();
    }

    glutTimerFunc(1000,myTimer,1);//Genera otro evento para que la funcion de animacion se ejecute en 1000 msc
}

void reshape (int w, int h)
{
    altoV = h;
    anchoV = w;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (X_MIN, X_MAX, Y_MIN, Y_MAX, 1, 20);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0, 0, 1.0, 0, 0, 0, 0.0, 1, 0.0);

}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{  //CAMBIAR EL VALOR DE dirX y dirY dependiendo de la tecla que oprima el usuario
    // activa la bandera de crecer para que la funcion myTimer crezca en una unidad la serpiente
    //Debe funcionar para mayuscula y minuscula.
    switch (theKey)
    {
        case 'd':

            colorCubo1+=1;
            colorCubo2+=1;
            colorCubo3+=1;
            glutPostRedisplay();
            break;
        case 'a':

            colorCubo1-=1;
            colorCubo2-=1;
            colorCubo3-=1;
            //PlaySound(sound1,NULL, SND_ASYNC);
            glutPostRedisplay();
            break;
        case 'w':

            break;
        case 's':

            break;
        case 'e':

            break;
        case 49:
            nivel=1;
            minutos = 2;
            segundos = 0;
            thevector.clear();
            theRandom();
            it=thevector.begin();
            glutPostRedisplay();
            break;
        case 50:
            nivel=2;
            minutos = 2;
            segundos = 0;
            thevector.clear();
            theRandom();
            it=thevector.begin();
            glutPostRedisplay();
            break;
        case 51:
            nivel=3;
            minutos = 0;
            segundos = 0;
            thevector.clear();
            theRandom();
            it=thevector.begin();
            glutPostRedisplay();
            break;
        case 52:
            ortho=0;
            glutPostRedisplay();
            break;
        case 53:
            ortho=1;
            glutPostRedisplay();
            break;
        case 27:
            exit(-1);
        default:
            break;
    }
}

void specialKeys(int key, int x, int y){
    switch (key){
        case GLUT_KEY_RIGHT:
            colorCubo1+=1;
            colorCubo2+=1;
            colorCubo3+=1;

            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            colorCubo1-=1;
            colorCubo2-=1;
            colorCubo3-=1;

            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            break;
        case GLUT_KEY_DOWN:

            break;
    }
}

int clicCuboL1(float x, float y){
    /*cout << "Posicion x -> ";
    cout << x;
    cout << "\n";*/
    cout << "Posicion y -> ";
    cout << y;
    cout << "\n";

    if (y>0 && y<0.3){
        if (x>-.9 && x<-.5)
            return 1;
        if (x>-.5 && x<-.16)
            return 2;
        if (x>-.16 && x<.16)
            return 3;
        if (x>.16 && x<.5)
            return 4;
        if (x>.5 && x<.9)
            return 5;
    } else if (y>-.3 && y<0){
        if (x>-.9 && x<-.5)
            return 6;
        if (x>-.5 && x<-.16)
            return 7;
        if (x>-.16 && x<.16)
            return 8;
        if (x>.16 && x<.5)
            return 9;
        if (x>.5 && x<.9)
            return 10;
    } else if (y>-.7 && y<-.3){
        if (x>-.9 && x<-.5)
            return 11;
        if (x>-.5 && x<-.16)
            return 12;
        if (x>-.16 && x<.16)
            return 13;
        if (x>.16 && x<.5)
            return 14;
        if (x>.5 && x<.9)
            return 15;
    }
}

int clicCuboL2(float x, float y){
    cout << "Posicion x -> ";
    cout << x;
    cout << "\n";
    /*cout << "Posicion y -> ";
    cout << y;
    cout << "\n";*/

    if (y>0.04 && y<0.32){
        if (x>-.9 && x<-.56)
            return 1;
        if (x>-.56 && x<-.28)
            return 2;
        if (x>-.28 && x<0)
            return 3;
        if (x>0 && x<.28)
            return 4;
        if (x>.28 && x<.56)
            return 5;
        if (x>.56 && x<.9)
            return 6;
    } else if (y>-.22 && y<0.04){
        if (x>-.9 && x<-.56)
            return 7;
        if (x>-.56 && x<-.28)
            return 8;
        if (x>-.28 && x<0)
            return 9;
        if (x>0 && x<.28)
            return 10;
        if (x>.28 && x<.56)
            return 11;
        if (x>.56 && x<.9)
            return 12;
    } else if (y>-.5 && y<-.22){
        if (x>-.9 && x<-.56)
            return 13;
        if (x>-.56 && x<-.28)
            return 14;
        if (x>-.28 && x<0)
            return 15;
        if (x>0 && x<.28)
            return 16;
        if (x>.28 && x<.56)
            return 17;
        if (x>.56 && x<.9)
            return 18;
    } else if (y>-.85 && y<-.5){
        if (x>-.9 && x<-.56)
            return 19;
        if (x>-.56 && x<-.28)
            return 20;
        if (x>-.28 && x<0)
            return 21;
        if (x>0 && x<.28)
            return 22;
        if (x>.28 && x<.56)
            return 23;
        if (x>.56 && x<.9)
            return 24;
    }
}

void myMouse(int button, int state, int x, int y)
{
    float x2,y2;
    int base=anchoV/2;
    int altura=altoV/2;

    if (x<=base && y<=altura){

        x2=((float)x/base)-1;
        y2=(((float)y/altura)-1)*-1;
    } else if (x>=base && y<=altura){

        x2=((float)(x-base)/base);
        y2=(((float)y/altura)-1)*-1;
    } else if (x<=base && y>=altura){

        x2=((float)x/base)-1;
        y2=(((float)(y-altura)/altura))*-1;
    } else if (x>=base && y>=altura){

        x2=((float)(x-base)/base);
        y2=(((float)(y-altura)/altura))*-1;
    }

    if (x==base)
        x2=0;
    if (y==altura)
        y2=0;

    /*cout << "Posicion x -> ";
    cout << x2;
    cout << "\n";
    cout << "Posicion y -> ";
    cout << y2;
    cout << "\n";*/

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        pantalla = 1;

        cubol1 = clicCuboL1(x2, y2);
        cubol = clicCuboL2(x2, y2);
        //cout << "El cubo2 -> ";
        //cout << cubol1;
        //cout << "\n";

        if (cubol>=1 && cubol<=limite){
            if (cubol == resp){
                score+=5;
                PlaySound(sdcorrect,NULL, SND_ASYNC);
                //cout << "!!!!! CORRECTO !!!!!" << endl;
            }
            else{
                PlaySound(sderror,NULL, SND_ASYNC);
                //cout << "XxXxX INCORRECTO XxXxX" << endl;
            }

            flagtextmaster = 1;
            swapt=0;
            thevector.clear();
            theRandom();
            it=thevector.begin();
            glutPostRedisplay();
            //glutTimerFunc(1,swapTimer,0);
        }
    }
    /*if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        pantalla = 0;
        segundos = 0;
        minutos = 0;
        cont = 0;
    }*/
}

void initLevel1(){
    glutTimerFunc(1000,swapTimer,0);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Project/LYNX");
    init();
    initRendering();
    initRandom();
    initLevel1();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);
    //glutTimerFunc(1000,myTimer,1);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouse);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return EXIT_SUCCESS;
}

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {

}

Image::~Image() {
	delete[] pixels;
}

namespace {
	//Converts a four-character array to an integer, using little-endian form
	int toInt(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}

	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes) {
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}

	//Reads the next four bytes as an integer, using little-endian form
	int readInt(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}

	//Reads the next two bytes as a short, using little-endian form
	short readShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}

	//Just like auto_ptr, but for arrays
	template<class T>
	class auto_array {
		private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array(T* array_ = NULL) :
				array(array_), isReleased(false) {
			}

			auto_array(const auto_array<T> &aarray) {
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			~auto_array() {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
			}

			T* get() const {
				return array;
			}

			T &operator*() const {
				return *array;
			}

			void operator=(const auto_array<T> &aarray) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			T* operator->() const {
				return array;
			}

			T* release() {
				isReleased = true;
				return array;
			}

			void reset(T* array_ = NULL) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = array_;
			}

			T* operator+(int i) {
				return array + i;
			}

			T &operator[](int i) {
				return array[i];
			}
	};
}

Image* loadBMP(const char* filename) {
	ifstream input;
	input.open(filename, ifstream::binary);
	assert(!input.fail() || !"Could not find file");
	char buffer[2];
	input.read(buffer, 2);
	assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
	input.ignore(8);
	int dataOffset = readInt(input);

	//Read the header
	int headerSize = readInt(input);
	int width;
	int height;
	switch(headerSize) {
		case 40:
			//V3
			width = readInt(input);
			height = readInt(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			assert(readShort(input) == 0 || !"Image is compressed");
			break;
		case 12:
			//OS/2 V1
			width = readShort(input);
			height = readShort(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			break;
		case 64:
			//OS/2 V2
			assert(!"Can't load OS/2 V2 bitmaps");
			break;
		case 108:
			//Windows V4
			assert(!"Can't load Windows V4 bitmaps");
			break;
		case 124:
			//Windows V5
			assert(!"Can't load Windows V5 bitmaps");
			break;
		default:
			assert(!"Unknown bitmap format");
	}

	//Read the data
	int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	int size = bytesPerRow * height;
	auto_array<char> pixels(new char[size]);
	input.seekg(dataOffset, ios_base::beg);
	input.read(pixels.get(), size);

	//Get the data into the right format
	auto_array<char> pixels2(new char[width * height * 3]);
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			for(int c = 0; c < 3; c++) {
				pixels2[3 * (width * y + x) + c] =
					pixels[bytesPerRow * y + 3 * x + (2 - c)];
			}
		}
	}

	input.close();
	return new Image(pixels2.release(), width, height);
}

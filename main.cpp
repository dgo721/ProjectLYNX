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
char path[70];
int crece=0;
int opcion = 1;
int ortho = 1;
int nivel = 3;
int limite = 40;
int imgrand1=1, imgrand2 = 2, imgrand3 = 3, imgrand4 = 4, imgrand5 = 5, imgrand6 = 6;
float angulo=15;
bool pausa = false;
bool menuselect = false;
bool rescorrect = false;
bool resincorrect = false;
bool notplaying = true;
int flagtextmaster = 1; //Bandera de control en cambio de figura
int resp = 0;
char* sdplay = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/sonido/gameplay.wav";
char* sdcorrect = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/sonido/correct.wav";
char* sderror = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/sonido/error.wav";
char* sdtictoc = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/sonido/tictoc.wav";
char* sdbuzzer = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/sonido/buzzer.wav";

int score = 0; //score
int minutos = 2;
int segundos = 1;
int pantalla = 0; //bandera para pantallas

/* GLUT callback Handlers */
float x=50;
float y=50;
float angle=0;
float fline=0;
static GLuint texName[36];
int cubol=0;
int textmaster=0;
int swapt=0;//Variable de cambio de pantalla en imagenes

int myrandom (int i) { return rand()%i;}
vector<int> thevector;
vector<int>::iterator it;

void loadGame();

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

void MediaPlayer (int x){
    switch (x) {
        case 1:{
            if (notplaying!=true)
                PlaySound(sdplay,NULL, SND_ASYNC|SND_LOOP);
        } break;
        case 2:PlaySound(sdcorrect,NULL, SND_ASYNC); break;
        case 3:PlaySound(sderror,NULL, SND_ASYNC); break;
        case 4:PlaySound(sdtictoc,NULL, SND_ASYNC); break;
        case 5:PlaySound(sdbuzzer,NULL, SND_ASYNC); break;
    }
}

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
    glGenTextures(55, texName);
    Image* image;

    for (int n=1; n<=limite; n++){
        sprintf(path, "%s%d%s", "/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/img", n, ".bmp");
        image = loadBMP(path);
        loadTexture(image,i++);
    }

    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/lynx.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/play.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/controls.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/credits.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/salir.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/level.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/level1.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/level2.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/level3.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/backw.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/back.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Diego/Documents/CodeBlocks/ProjectLYNX/texturas/restart.bmp");loadTexture(image,i++);

	delete image;
}

void menu(int id)
{
    switch(id)
    {
        case 0:
            pantalla = 0;
            MediaPlayer(1);
            notplaying=true;
            glutPostRedisplay();
            break;
        case 1:
            if(!pausa)
                    pausa = true;
            else pausa = false;
            break;
        case 2:
            exit(0);
            break;
        default:
            break;
    }
}

void processMenuStatus(int status, int x, int y){
    if (status == GLUT_MENU_IN_USE)
        menuselect=true;
    else
        menuselect=false;
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
    glutCreateMenu(menu);
    glutAddMenuEntry("Menu Principal", 0);
    glutAddMenuEntry("Pausa", 1);
    glutAddMenuEntry("Salir", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    PlaySound(sdplay,NULL, SND_ASYNC|SND_LOOP);
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

	float scaletx = 0.15;

	switch (nivel){
        case 3: scaletx = 0.12; break;
        default: scaletx = 0.15; break;
	}

    glScalef(scaletx,scaletx,scaletx);
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

void drawButton(int number){
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[number]);

    glTranslatef(0, 0, 0);
    glScalef(.5,.5,.5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

void cuboMenu(){

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[imgrand1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    float scaletx = 0.5;
    glScalef(scaletx,scaletx,scaletx);

    //Frente
    glBegin(GL_QUADS);
    glNormal3f( -1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f,  0.5f);
    glTexCoord2f(6.0f, 1.0f);
    glVertex3f( 0.5f,  0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[imgrand2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Atras
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[imgrand3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//Arriba
    glBegin(GL_QUADS);
    glNormal3f( 1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[imgrand4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//Abajo
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(3.0f, 0.0f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(3.0f, 1.0f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[imgrand5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Derecho
    glBegin(GL_QUADS);
    glNormal3f( 1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[imgrand6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Izquierdo
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawTitle(){

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[40]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(0, .2, 0);
    glScalef(.5,.15,.1);

    glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

static void display(void)
{
    if(!pausa){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);

    glLineWidth(3);// 10 pixels  recuerda que la ventana va de -1 a 1  en y y en x

	//Menu principal
    if (pantalla == 0){
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[4]);

        glPushMatrix();
        drawTitle();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -.2, -.1);
        glScalef(.7,.2,.1);
        drawButton(41);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.5, -.5, -.1);
        glScalef(.7,.2,.1);
        drawButton(42);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(.5, -.5, -.1);
        glScalef(.7,.2,.1);
        drawButton(43);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -.8, -.1);
        glScalef(.7,.2,.1);
        drawButton(44);
        glPopMatrix();
    }
	//Menu Seleccionar nivel
    if (pantalla == 1){
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[4]);

        glPushMatrix();
        drawTitle();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -.15, -.1);
        glScalef(.7,.15,.1);
        drawButton(45);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.6, -.5, -.1);
        glScalef(.5,.2,.1);
        drawButton(46);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -.5, -.1);
        glScalef(.5,.2,.1);
        drawButton(47);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(.6, -.5, -.1);
        glScalef(.5,.2,.1);
        drawButton(48);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.7, -.9, -.1);
        glScalef(.4,.2,.1);
        drawButton(49);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.45, -.9, -.1);
        glScalef(.1,.2,.1);
        drawButton(50);
        glPopMatrix();
    }
	//Menu Controles
    if (pantalla == 3)
    {
        glPushMatrix();
        glTranslatef(-0.05,-0.7,0.0);
        glScaled(0.005,0.005,0.005);
        sprintf(msg,"%s", "muerete");
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1.0, -1.0, 0);
        glPopMatrix();
    }
	//Menu Creditos
    if (pantalla == 4)
    {
        glPushMatrix();
        glTranslatef(-0.05,-0.7,0.0);
        glScaled(0.005,0.005,0.005);
        sprintf(msg,"%s", "maria la del barrio");
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1.0, -1.0, 0);
        glPopMatrix();
    }
	//Pantalla Juego
    if (pantalla == 2){

        glPushMatrix();
        glTranslatef(0,1.2,-.8);
        glRotatef(20, 1.0, 0.0, 0.0);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[3]);
        glutSolidCube(0.5);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.5);
        ///////////////
        glPushMatrix();
        glTranslatef(0.6,0.1,0);
        glScaled(0.015, 0.015, 0.015);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[1]);
        sprintf(msg,"%s%d", "Puntos: ", score);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1, -.9, 0);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-1.25,0.1,0.0);
        glScaled(0.015, 0.015, 0.015);
        if (segundos>=0 && segundos <=9)
            sprintf(msg, "%s%d%s%d", "0",minutos, ":0", segundos);
        else
            sprintf(msg, "%s%d%s%d", "0", minutos, ":", segundos);
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

        /*sprintf(msg,"%s%d", "Score:", score);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -0.9, .7, 0);

        sprintf(msg, "%d %s %d", minutos, ":", segundos);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, .4, .7, 0);*/
    }
    //Menu GameOver
    if (pantalla == 5)
    {
        glPushMatrix();
        glTranslatef(-0.68,0.0,-.1);
        glScaled(0.020, 0.020, 0.015);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[1]);
        sprintf(msg,"%s", "Game Over");
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1, -.9, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.6,-0.25,-.1);
        glScaled(0.015, 0.015, 0.015);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[3]);
        sprintf(msg,"%s%d", "Puntuacion: ", score);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -1, -.9, 0);
        glPopMatrix();

        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[4]);
        glPushMatrix();
        glTranslatef(-.7, -.9, -.1);
        glScalef(.4,.2,.1);
        drawButton(49);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.45, -.9, -.1);
        glScalef(.1,.2,.1);
        drawButton(50);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(.55, -.9, -.1);
        glScalef(.6,.2,.1);
        drawButton(51);
        glPopMatrix();
    }

    if (pantalla!=2){

        glPushMatrix();
        glTranslatef(-1.25,1.25,-1);
        glRotatef(50, 1.0, 0.0, 0.0);
        glRotatef(angulo, 0.0, 1.0, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        cuboMenu();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.25,1.25,-1);
        glRotatef(50, 1.0, 0.0, 0.0);
        glRotatef(-angulo, 0.0, 1.0, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        cuboMenu();
        glPopMatrix();

    }

    glutSwapBuffers();//por defaul invoca al glFlush();
    }
}

void swapTimer(int valor){

    if(!pausa && !menuselect){
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

        if (pantalla == 2) glutTimerFunc(1000,swapTimer,1);

        /*if (pantalla != 2){
            glPushMatrix();
            glTranslatef(-1.25,1.25,-1);
            glRotatef(50, 1.0, 0.0, 0.0);
            glRotatef(angulo, 0.0, 1.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            cuboMenu();
            glPopMatrix();
        }*/
    }
}

void imgRandom(int value)
{
    if (pantalla !=2 ){
        imgrand1 += 1;
        imgrand2 += 2;
        imgrand3 += 3;
        imgrand4 += 4;
        imgrand5 += 5;
        imgrand6 += 6;

        if (imgrand1 > 40)
            imgrand1 = 1;
        if (imgrand2 > 40)
            imgrand2 = 1;
        if (imgrand3 > 40)
            imgrand3 = 1;
        if (imgrand4 > 40)
            imgrand4 = 1;
        if (imgrand5 > 40)
            imgrand5 = 1;
        if (imgrand6 > 40)
            imgrand6 = 1;

        glutPostRedisplay();
    }
        glutTimerFunc(1000,imgRandom,0);
    //}
}

void movRandom(int value)
{
    angulo = angulo +1;
    if (angulo >360) angulo =0;
    glutPostRedisplay();
    glutTimerFunc(20,movRandom,0);
}

void myTimer( int valor){

    if(!pausa && !menuselect){
        if(pantalla == 2 )
        {

            segundos--;
            if(segundos == -1)
            {
                segundos = 59;
                minutos--;
            }

            if (minutos==0 && segundos<=5 && segundos>0){
                MediaPlayer(4);
            }

            if (minutos==0 && segundos==0){
                MediaPlayer(5);
                pantalla=5;
            }

            glutPostRedisplay();
            }
        }
    if (pantalla == 2)glutTimerFunc(1000,myTimer,1);//Genera otro evento para que la funcion de animacion se ejecute en 1000 msc
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

            glutPostRedisplay();
            break;
        case 'a':

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
            minutos = 2;
            segundos = 0;
            thevector.clear();
            theRandom();
            it=thevector.begin();
            glutPostRedisplay();
            break;
        case 52:

            glutPostRedisplay();
            break;
        case 53:

            glutPostRedisplay();
            break;
        case 27:
            exit(-1);
        case 32:
            if(!pausa)
                pausa = true;
            else pausa = false;
            break;
        default:
            break;
    }
}

void specialKeys(int key, int x, int y){
    switch (key){
        case GLUT_KEY_RIGHT:

            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:

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
    cout << "\n";
    cout << "Posicion y -> ";
    cout << y;
    cout << "\n";*/

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

int clicCuboL3(float x, float y){
    /*cout << "Posicion x -> ";
    cout << x;
    cout << "\n";
    cout << "Posicion y -> ";
    cout << y;
    cout << "\n";*/

    if (y>0.05 && y<0.3){
        if (x>-.94 && x<-.68)
            return 1;
        if (x>-.68 && x<-.44)
            return 2;
        if (x>-.44 && x<-.22)
            return 3;
        if (x>-.22 && x<0)
            return 4;
        if (x>0 && x<.21)
            return 5;
        if (x>.21 && x<.455)
            return 6;
        if (x>.455 && x<.685)
            return 7;
        if (x>.685 && x<.94)
            return 8;
    } else if (y>-.15 && y<0.05){
        if (x>-.94 && x<-.68)
            return 9;
        if (x>-.68 && x<-.44)
            return 10;
        if (x>-.44 && x<-.22)
            return 11;
        if (x>-.22 && x<0)
            return 12;
        if (x>0 && x<.21)
            return 13;
        if (x>.21 && x<.455)
            return 14;
        if (x>.455 && x<.685)
            return 15;
        if (x>.685 && x<.94)
            return 16;
    } else if (y>-.4 && y<-.15){
        if (x>-.94 && x<-.68)
            return 17;
        if (x>-.68 && x<-.44)
            return 18;
        if (x>-.44 && x<-.22)
            return 19;
        if (x>-.22 && x<0)
            return 20;
        if (x>0 && x<.21)
            return 21;
        if (x>.21 && x<.455)
            return 22;
        if (x>.455 && x<.685)
            return 23;
        if (x>.685 && x<.94)
            return 24;
    } else if (y>-.625 && y<-.4){
        if (x>-.94 && x<-.68)
            return 25;
        if (x>-.68 && x<-.44)
            return 26;
        if (x>-.44 && x<-.22)
            return 27;
        if (x>-.22 && x<0)
            return 28;
        if (x>0 && x<.21)
            return 29;
        if (x>.21 && x<.455)
            return 30;
        if (x>.455 && x<.685)
            return 31;
        if (x>.685 && x<.94)
            return 32;
    } else if (y>-.9 && y<-.625){
        if (x>-.94 && x<-.68)
            return 33;
        if (x>-.68 && x<-.44)
            return 34;
        if (x>-.44 && x<-.22)
            return 35;
        if (x>-.22 && x<0)
            return 36;
        if (x>0 && x<.21)
            return 37;
        if (x>.21 && x<.455)
            return 38;
        if (x>.455 && x<.685)
            return 39;
        if (x>.685 && x<.94)
            return 40;
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

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !pausa){

    cout << "Posicion x -> ";
    cout << x2;
    cout << "\n";
    cout << "Posicion y -> ";
    cout << y2;
    cout << "\n";

        switch(pantalla){
        case 0:
    {
        if( x2 >= -.35 &&  x2 <= .35 && y2 <= -.08 && y2 >= -.3)
        {
         pantalla = 1;
         glutPostRedisplay();
        }
        if( x2 >= -.84 &&  x2 <= -0.143 && y2 <= -.38 && y2 >= -.58)
        {
         pantalla = 3;
         glutPostRedisplay();
        }
        if( x2 >= .1375 &&  x2 <= .834 && y2 <= -.38 && y2 >= -.592)
        {
         pantalla = 4;
         glutPostRedisplay();
        }
        if( x2 >= -.347 &&  x2 <= .344 && y2 <= -.67 && y2 >= -.883)
        {
            exit(-1);
        }
    }
        break;
        case 1:
    {
        if( x2 >= -.84 &&  x2 <= -.337 && y2 <= -.38 && y2 >= -.59)
        {
            nivel=1;
            minutos = 1;
            segundos = 16;
            limite=15;
            thevector.clear();
            theRandom();
            it=thevector.begin();
            notplaying=false;
            MediaPlayer(2);
            pantalla = 2;
            loadGame();
        }
        if( x2 >= -.247 &&  x2 <= 0.244 && y2 <= -.388 && y2 >= -.588)
        {
            nivel=2;
            minutos = 0;
            segundos = 7;
            limite=24;
            thevector.clear();
            theRandom();
            it=thevector.begin();
            notplaying=false;
            MediaPlayer(2);
            pantalla = 2;
            loadGame();
        }
        if(x2 >= .334 &&  x2 <= .834 && y2 <= -.383 && y2 >= -.588)
        {
            nivel=3;
            minutos = 1;
            segundos = 16;
            limite=40;
            thevector.clear();
            theRandom();
            it=thevector.begin();
            notplaying=false;
            MediaPlayer(2);
            pantalla = 2;
            loadGame();
        }
        if( x2 >= -.885 &&  x2 <= .385 && y2 <= -.77 && y2 >= -.98)
        {
            pantalla = 0;
            glutPostRedisplay();
        }
    }
        break;
        case 2:
        {
        switch (nivel){
            case 1: cubol = clicCuboL1(x2, y2); break;
            case 2: cubol = clicCuboL2(x2, y2); break;
            case 3: cubol = clicCuboL3(x2, y2); break;
        }
        //cout << "El cubo2 -> ";
        //cout << cubol1;
        //cout << "\n";

        if (cubol>=1 && cubol<=limite){
            if (cubol == resp){
                rescorrect=true;
                switch (swapt){
                    case 1: score+=10; break;
                    case 2: score+=5; break;
                    case 3: score+=3; break;
                    case 4: score+=2; break;
                    default: score+=1; break;
                }

                MediaPlayer(2);
                //cout << "!!!!! CORRECTO !!!!!" << endl;
            }
            else{
                MediaPlayer(3);
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
        break;
        case 5:
        {
            if( x2 >= -.885 &&  x2 <= .385 && y2 <= -.77 && y2 >= -.98){
                pantalla = 0;
                MediaPlayer(1);
                notplaying=true;
                glutPostRedisplay();
            }
            if(x2 >= .244 &&  x2 <= .829 && y2 <= -.775 && y2 >= -.98){
                switch (nivel){
                    case 1:{
                        minutos = 1;
                        segundos = 16;
                        limite=15;
                        thevector.clear();
                        theRandom();
                        it=thevector.begin();
                        notplaying=false;
                        MediaPlayer(2);
                        pantalla = 2;
                        loadGame();
                    } break;
                    case 2:{
                        minutos = 1;
                        segundos = 16;
                        limite=24;
                        thevector.clear();
                        theRandom();
                        it=thevector.begin();
                        notplaying=false;
                        MediaPlayer(2);
                        pantalla = 2;
                        loadGame();
                    } break;
                    case 3:{
                        minutos = 1;
                        segundos = 16;
                        limite=40;
                        thevector.clear();
                        theRandom();
                        it=thevector.begin();
                        notplaying=false;
                        MediaPlayer(2);
                        pantalla = 2;
                        loadGame();
                    } break;
                }
            }
        }
        break;
        default:
        break;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        menuselect= !menuselect;
    }
}

void loadGame(){
    if(pantalla == 2){
        swapt = 0;
        glutTimerFunc(10,swapTimer,0);
        glutTimerFunc(10,myTimer,1);
    }
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
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);
    glutTimerFunc(20,movRandom,1);
    glutTimerFunc(1000,imgRandom,1);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouse);
    glutMenuStatusFunc(processMenuStatus);
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

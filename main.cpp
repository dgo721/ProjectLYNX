/*
 1089909_0611478
 LYNX
 Avance de Proyecto - Prototipo de Cubos con Sonido // Materiales Luces incluidas
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mmsystem.h>
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

const int X_MAX=1;
const int X_MIN=-1;
const int Y_MAX=1;
const int Y_MIN=-1;
const double DELTA= 0.1;
double dirX=DELTA;//derecha x=-1,Y=0 IZQUIERDA, X=0;Y=-1 ABAJO, X=0,Y=1 ARRIBA
double dirY=0.0;
char msg[40];
int crece=0;
int opcion = 1;
int nivel = 1;
char* sound1 = "C:/Users/Diego/Documents/CodeBlocks/ProjectLYNX/beep3.wav";

int cont = 0; //score
int minutos = 0;
int segundos = 0;
int pantalla = 1; //bandera para pantallas

/* GLUT callback Handlers */
float x=50;
float y=50;
int colorCubo1=1;
int colorCubo2=2;
int colorCubo3=3;

GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light_diffuse[] = { 0.85, 0.85, 0.85, 1.0 };
GLfloat light_specular[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light_position[] = { 0.5, 0.5, 0.5, 1.0 };

GLfloat mat_ambient[] = {0.2,0.2,0.2,1.0};
GLfloat mat_diffuse[][4] = {{0.0f, 0.0f, 0.0f, 1.0f},
                            {1.0f, 0.0f, 0.0f, 1.0f},
                            {0.0f, 1.0f, 0.0f, 1.0f},
                            {0.0f, 0.0f, 1.0f, 1.0f}};
GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};

static void init()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glClearColor(0.3,0.3,0.3,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
    if (x==1){
        //glColor3f(0.5,0.0,0.0);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[1]);
    } else if (x==2) {
        //glColor3f(0.0,0.5,0.0);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[2]);
    } else if (x==3) {
        //glColor3f(0.0,0.0,0.5);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[3]);
    } else {
        //glColor3f(0.0,0.0,0.0);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[0]);
    }
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
}

void coloreaCubo(int x){

    if (x==1){
        colorCubo(colorCubo1);
    } else if (x==2) {
        colorCubo(colorCubo2);
    } else if (x==3) {
        colorCubo(colorCubo3);
    }
}

void levelOne(){

    float tx=-1.2;

    //First Row
    for (int i=0; i<5; i++){
        glPushMatrix();
        glTranslatef(tx,.3,-.8);
        coloreaCubo(1);
        glutSolidCube(0.4);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.4);
        glPopMatrix();

        tx+=0.6;
    }

    //Second Row
    tx=-1.2;

    for (int i=0; i<5; i++){
        glPushMatrix();
        glTranslatef(tx,-.3,-.8);
        coloreaCubo(2);
        glutSolidCube(0.4);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.4);
        glPopMatrix();

        tx+=0.6;
    }

    //Third Row
    tx=-1.2;

    for (int i=0; i<5; i++){
        glPushMatrix();
        glTranslatef(tx,-.9,-.8);
        coloreaCubo(3);
        glutSolidCube(0.4);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.4);
        glPopMatrix();

        tx+=0.6;
    }
}

void levelTwo(){
    float tx=-1.25;

    //First Row
    for (int i=0; i<6; i++){
        glPushMatrix();
        glTranslatef(tx,.3,-.8);
        coloreaCubo(1);
        glutSolidCube(0.35);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.35);
        glPopMatrix();

        tx+=0.5;
    }

    tx=-1.25;

    //Second Row
    for (int i=0; i<6; i++){
        glPushMatrix();
        glTranslatef(tx,-.15,-.8);
        coloreaCubo(2);
        glutSolidCube(0.35);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.35);
        glPopMatrix();

        tx+=0.5;
    }

    tx=-1.25;

    //Third Row
    for (int i=0; i<6; i++){
        glPushMatrix();
        glTranslatef(tx,-.6,-.8);
        coloreaCubo(3);
        glutSolidCube(0.35);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.35);
        glPopMatrix();

        tx+=0.5;
    }

    tx=-1.25;

    //Forth Row
    for (int i=0; i<6; i++){
        glPushMatrix();
        glTranslatef(tx,-1.15,-.8);
        coloreaCubo(1);
        glutSolidCube(0.35);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.35);
        glPopMatrix();

        tx+=0.5;
    }
}

void levelThree(){
    float tx=-1.4;

    //First Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,.3,-.8);
        coloreaCubo(1);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        glPopMatrix();

        tx+=0.4;
    }

    tx=-1.4;

    //Second Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,-0.1,-.8);
        coloreaCubo(2);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        glPopMatrix();

        tx+=0.4;
    }

    tx=-1.4;

    //Third Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,-0.5,-.8);
        coloreaCubo(3);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        glPopMatrix();

        tx+=0.4;
    }

    tx=-1.4;

    //Forth Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,-0.9,-.8);
        coloreaCubo(1);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        glPopMatrix();

        tx+=0.4;
    }

    tx=-1.4;

    //Fifth Row
    for (int i=0; i<8; i++){
        glPushMatrix();
        glTranslatef(tx,-1.3,-.8);
        coloreaCubo(2);
        glutSolidCube(0.3);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.3);
        glPopMatrix();

        tx+=0.4;
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
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[0]);
        glutSolidCube(0.5);
        glColor3f(0.7,0.7,0.7);
        glutWireCube(0.5);
        glPopMatrix();

        if (nivel==1){
            levelOne();
        } else if (nivel==2){
            levelTwo();
        } else if (nivel==3){
            levelThree();
        }

        sprintf(msg,"%s%d", "Score:", cont);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, -0.9, .7, 0);

        sprintf(msg, "%d %s %d", minutos, ":", segundos);
        draw3dString(GLUT_STROKE_MONO_ROMAN, msg, .4, .7, 0);
    }

    glutSwapBuffers();//por defaul invoca al glFlush();
}

void myTimer( int valor){

    if(pantalla == 1 )
    {

        segundos++;
        if(segundos == 60)
        {
            segundos = 0;
            minutos++;
        }
    }
    glutPostRedisplay(); //Genere un evento para que se ejecute la funcion callback display
    glutTimerFunc(1000,myTimer,1);//Genera otro evento para que la funcion de animacion se ejecute en 1000 msc
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if (opcion == 1)
        glFrustum (X_MIN, X_MAX, Y_MIN, Y_MAX, 1, 20);
    else
        glOrtho(X_MIN, X_MAX, Y_MIN, Y_MAX, 2, 20);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity() ;
    if (opcion == 1)
      gluLookAt (0, 0, 1.0, 0, 0, 0, 0.0, 1, 0.0);
    else
      gluLookAt (0, 0, 0.0, 0, 0, 0, 0.0, 1, 0.0);

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
            PlaySound(sound1,NULL, SND_ASYNC);
            glutPostRedisplay();
            break;
        case 'a':

            colorCubo1-=1;
            colorCubo2-=1;
            colorCubo3-=1;
            PlaySound(sound1,NULL, SND_ASYNC);
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
            minutos = 0;
            segundos = 0;
            glutPostRedisplay();
            break;
        case 50:
            nivel=2;
            minutos = 0;
            segundos = 0;
            glutPostRedisplay();
            break;
        case 51:
            nivel=3;
            minutos = 0;
            segundos = 0;
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
            PlaySound(sound1,NULL, SND_ASYNC);
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            colorCubo1-=1;
            colorCubo2-=1;
            colorCubo3-=1;
            PlaySound(sound1,NULL, SND_ASYNC);
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            break;
        case GLUT_KEY_DOWN:

            break;
    }
}

void myMouse(int button, int state, int x, int y)
{
        //Si el usuario oprime el boton izq del mouse
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            pantalla= 1;
            //glLoadIdentity ();
            //glTranslatef(glx,gly,0);
        }
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            pantalla= 0;
            segundos = 0;
            minutos = 0;
            cont = 0;
            //glLoadIdentity ();
            //glTranslatef(glx,gly,0);
        }

}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Avance");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);
    glutTimerFunc(1,myTimer,1);
    glutReshapeFunc(reshape);
    glutMouseFunc( myMouse );
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 30


static int timer_active;
static int window_height, window_width;
static int angle;
static int animation_parameter;
static int speed;
/*static float gravity;*/

static void on_special(int key, int x, int y);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display();
static void on_timer(int id);



int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(900, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Cube Hero");

    animation_parameter = 0;
    timer_active = 0;
    angle = 0;
    speed = 1;
    /*gravity = sin(angle);*/

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutSpecialFunc(on_special);

    glClearColor(0, 0, 0.2, 0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();


    return 0;
}



static void on_timer(int value)
{
    if (value != 0)
        return;

    animation_parameter +=1;
    glutPostRedisplay();

    if (timer_active)
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}



static void on_special(int key, int x, int y)
{

    switch (key) {
        case GLUT_KEY_UP:
	if (angle < 60 && timer_active) /*platform can be rotated in-between 0° and 60° and only if the game has started */
	     {  
		angle += 10;
		/*speed *= (1+gravity);*/
		speed += 0.5;
	     }
        break;

	case GLUT_KEY_DOWN:
	if (angle > 0 && timer_active)
             {  
		angle -= 10;
	     }
        break;
    }
}



static void on_keyboard(unsigned char key, int x, int y)
{
   
    switch (key) {
    case 27:        /* escape  ---> exiting game */
        exit(0);
	break;

    case 32:        /* space  ---> starting animation */
       if (timer_active == 0) 
        {
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            timer_active = 1;
        }
        break;

    case 'p':      /* 'p'  ---> pausing animation */
	timer_active = 0;
	break;
    }
}



static void on_reshape(int width, int height)
{

    window_width = width;
    window_height = height;
    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/window_height, 1, 100);

}



void drawCubes()
{ 
 
   glPushMatrix();

	glColor3f(1,1,0); 
	glTranslatef(0,0.08,-0.75);
	glScalef(0.06, 0.06, 0.06);
	glutSolidCube(1);

   glPopMatrix();

   glPushMatrix();

	glColor3f(0,1,0); 
	glTranslatef(-0.2,0.08,-0.75);
	glScalef(0.06, 0.06, 0.06);
	glutSolidCube(1);

   glPopMatrix();

}


void drawPlatformLines()
{

 glDisable(GL_LIGHTING);
 glLineWidth(2);

    glBegin(GL_LINES);
        glColor3f(0,1,0);
        glVertex3f(-0.2,0.05,-0.75);  /* horizontal green line, length is the length of the platform */
        glVertex3f(-0.2,0.05,0.75);

        glColor3f(1,0,0);
        glVertex3f(-0.1,0.05,-0.75);  /*red*/
        glVertex3f(-0.1,0.05,0.75);  

        glColor3f(1,1,0);
        glVertex3f(0,0.05,-0.75);     /*yellow*/
        glVertex3f(0,0.05,0.75);

        glColor3f(0,0,1);
        glVertex3f(0.1,0.05,-0.75);   /*blue*/
        glVertex3f(0.1,0.05,0.75);

        glColor3f(1,0.6,0);	      /*orange*/
        glVertex3f(0.2,0.05,-0.75); 
        glVertex3f(0.2,0.05,0.75);

    glEnd();

    glEnable(GL_LIGHTING);
}


void drawSpeakers()
{

    /*left speaker*/
    glPushMatrix();

        glTranslatef(-1,0,-1);

	glColor3f(0, 0, 0);
	glScalef(0.3, 0.7, 0.3);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glTranslatef(0,0.1,0.5);
	glutSolidTorus(0.1, 0.2, 30, 30);

    glPopMatrix();


     /*right speaker*/
    glPushMatrix();

	glTranslatef(1,0,-1);

	glColor3f(0, 0, 0);
	glScalef(0.3, 0.7, 0.3);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glTranslatef(0,0.1,0.5);
	glutSolidTorus(0.1, 0.2, 30, 30);
      
    glPopMatrix();

}


void drawAxes() /*used to check platform rotation*/
{

    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(15,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,15,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,15);
    glEnd();

    glEnable(GL_LIGHTING);

}


void drawPlatform()
{

    glPushMatrix();
	glColor3f(0, 0, 0);
	glScalef(0.5, 0.1, 1.5);
	glutSolidCube(1);
    glPopMatrix();

}



static void on_display()
{
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 1.2, 1.2,
            0, 0, 0,
            0, 1, 0.99 /* just to be non-colinear to eye vector*/
        );

    /*drawAxes();*/
  
    drawSpeakers();

    
    glRotatef(angle, 1, 0, 0);

    glPushMatrix();
        glTranslatef(0, 0, animation_parameter/100.0*speed);
        drawCubes();
    glPopMatrix();

    glPushMatrix();
	drawPlatformLines();
    glPopMatrix();

    glPushMatrix();
        drawPlatform();
    glPopMatrix();


    glutSwapBuffers();

}

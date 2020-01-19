#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 30
#define PI 3.141592


static int timer_active;
static int window_height, window_width;
static int animation_parameter;

static int angle; /*rotation angle of the platform--> (0°,60°)*/
static float position; /*rotation of the viewpoint --> are we viewing from the front or from the right side of the plaftorm*/
static float speed;   /*speed increasing with stronger gravity*/
static float gravity; /*gravity parameter increasing with the higher slope (angle)*/
static float length_of_the_platform;
static int points_earned;
static float z_coord; /*remembering position of the cubes for the catching check*/

static int first_visible;
static int second_visible;
static int third_visible;
static int fourth_visible;
static int fifth_visible;


static void on_special(int key, int x, int y);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display();
static void on_timer(int id);

int catchingHappened(float z_coord);

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(900, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Cube Hero"); 

    animation_parameter = 0;
    timer_active = 0;

    points_earned = 0;
    position = 0;
    angle = 0;
    speed = 1;
    length_of_the_platform = 1.5;
    gravity = sin(angle*PI/180) * length_of_the_platform;  /* opposite side = sin(angle)*hypotenuse (hypotenuse == length_of_the_platform) */

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutSpecialFunc(on_special); /*callback function used for handling special keys (GLUT_KEY_UP etc.)*/

    glClearColor(0.1, 0.1, 0.2, 0);

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
		speed *= (1+gravity);
	     }
        break;

	case GLUT_KEY_DOWN:
	if (angle > 0 && timer_active)
             {  
		angle -= 10;
	     }
        break;

        case GLUT_KEY_LEFT:   /* going back to the original view*/
	if (!timer_active && position !=0) 
	     {  
           	position = 0;
		glutPostRedisplay();
	     }
        break;

        case GLUT_KEY_RIGHT:  /* enabling viewing to the platform from the side. NOTE: this rotation can only be done when game is inactive*/
	if (!timer_active && position == 0) 
	     {  
		position +=1.2;
		glutPostRedisplay();
	     }
        break;
    }
}



static void on_keyboard(unsigned char key, int x, int y)
{
   
    switch (key) {
    case 27:        /* escape  ---> exiting game */
        { 
	printf("Osvojili ste %d poena!\n", points_earned);
        exit(0);
        }
	break;


    case 32:        /* space  ---> starting animation */
       if (timer_active == 0) 
        {
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            timer_active = 1;
        }
        break;


    case 'p':      /* 'p'  ---> pausing animation */
    case 'P':
	timer_active = 0;
	break;


    case 'q':      /* catching cube No1 */
    case 'Q':
	if (0.69 <= z_coord && 0.75 >= z_coord)
	    points_earned+=1;
	break;

    case 'w':      /* catching cube No2 */
    case 'W':
	if (0.69 <= z_coord && 0.75 >= z_coord)
	    points_earned+=1;
	break;


    case 'e':      /* catching cube No3 */
    case 'E':
	if (0.69 <= z_coord && 0.75 >= z_coord)
	    points_earned+=1;
	break;


    case 'r':      /* catching cube No4 */
    case 'R':
	if (0.69 <= z_coord && 0.75 >= z_coord)
	    points_earned+=1;
	break;


    case 't':      /* catching cube No5 */
    case 'T':
	if (0.69 <= z_coord && 0.75 >= z_coord)
	    points_earned+=1;
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



void drawCubeOne()
{
   glPushMatrix();

	glColor3f(0,1,0); 
	glTranslatef(-0.2,0.08,-0.75);
	glScalef(0.06, 0.06, 0.06);
	glutSolidCube(1);

   glPopMatrix();
}


void drawCubeTwo()
{
   glPushMatrix();

	glColor3f(1,0,0); 
	glTranslatef(-0.1,0.08,-0.75);
	glScalef(0.06, 0.06, 0.06);
	glutSolidCube(1);

   glPopMatrix();
}


void drawCubeThree()
{
   glPushMatrix();

	glColor3f(1,1,0); 
	glTranslatef(0,0.08,-0.75);
	glScalef(0.06, 0.06, 0.06);
	glutSolidCube(1);

   glPopMatrix();
}


void drawCubeFour()
{
   glPushMatrix();

	glColor3f(0,0,1); 
	glTranslatef(0.1,0.08,-0.75);
	glScalef(0.06, 0.06, 0.06);
	glutSolidCube(1);

   glPopMatrix();
}


void drawCubeFive()
{
   glPushMatrix();

	glColor3f(1,0.5,0); 
	glTranslatef(0.2,0.08,-0.75);
	glScalef(0.06, 0.06, 0.06);
	glutSolidCube(1);

   glPopMatrix();
}



void drawCubes(int first_visible, int second_visible, int third_visible, int fourth_visible, int fifth_visible)
{ 

   if (first_visible)
  	drawCubeOne();

   if (second_visible)
	drawCubeTwo();

   if (third_visible)
	drawCubeThree();

   if (fourth_visible)
	drawCubeFour();

   if (fifth_visible)
	drawCubeFive();

}


void drawPlatformLines()
{

    glDisable(GL_LIGHTING);
    glLineWidth(2);

    glBegin(GL_LINES);  /*thin part*/

        glColor3f(0,1,0);
        glVertex3f(-0.2,0.05,-0.75);  /*horizontal green line, lenght is the lentgh_of_the_platform without catching part (cube size)*/
        glVertex3f(-0.2,0.05,0.69);

        glColor3f(1,0,0);
        glVertex3f(-0.1,0.05,-0.75);  /*red*/
        glVertex3f(-0.1,0.05,0.69);  

        glColor3f(1,1,0);
        glVertex3f(0,0.05,-0.75);     /*yellow*/
        glVertex3f(0,0.05,0.69);

        glColor3f(0,0,1);
        glVertex3f(0.1,0.05,-0.75);   /*blue*/
        glVertex3f(0.1,0.05,0.69);

        glColor3f(1,0.5,0);	      /*orange*/
        glVertex3f(0.2,0.05,-0.75); 
        glVertex3f(0.2,0.05,0.69);

     glEnd();


     glLineWidth(20); /*thick part where catching cube happens*/

     glBegin(GL_LINES);


        glColor3f(0,1,0);
        glVertex3f(-0.2,0.05,0.69);  
        glVertex3f(-0.2,0.05,0.75);

        glColor3f(1,0,0);
        glVertex3f(-0.1,0.05,0.69);  
        glVertex3f(-0.1,0.05,0.75);  

        glColor3f(1,1,0);
        glVertex3f(0,0.05,0.69);     
        glVertex3f(0,0.05,0.75);

        glColor3f(0,0,1);
        glVertex3f(0.1,0.05,0.69);  
        glVertex3f(0.1,0.05,0.75);

        glColor3f(1,0.5,0);	      
        glVertex3f(0.2,0.05,0.69); 
        glVertex3f(0.2,0.05,0.75);


    glEnd();

    glEnable(GL_LIGHTING);
}


void drawSpeakers()
{

    /*left speaker*/
    glPushMatrix();

        glTranslatef(-0.7,0,-0.7);

	glColor3f(0, 0, 0);
	glScalef(0.3, 0.7, 0.3);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glTranslatef(0,0.1,0.5);
	glutSolidTorus(0.1, 0.2, 30, 30);

    glPopMatrix();


     /*right speaker*/
    glPushMatrix();

	glTranslatef(0.7,0,-0.7);

	glColor3f(0, 0, 0);
	glScalef(0.3, 0.7, 0.3);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glTranslatef(0,0.1,0.5);
	glutSolidTorus(0.1, 0.2, 30, 30);
      
    glPopMatrix();

}


void drawAxes() /*used to check if the platform rotation is ok*/
{

    glDisable(GL_LIGHTING);
    
    glLineWidth(1);

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
	glScalef(0.5, 0.1, length_of_the_platform);
	glutSolidCube(1);

    glPopMatrix();

}

static void on_display()
{
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            position, 1.23, 1.23, 
            0, 0, 0,
            0, 1, 0  
        );

    /*drawAxes();*/


    time_t t;
    srand((unsigned) time(&t));
    

    if ((int)(animation_parameter*speed) % 170 == 0)
    {
      first_visible = rand()%2;
      second_visible = rand()%2;
      third_visible = rand()%2;
      fourth_visible = rand()%2;
      fifth_visible = rand()%2;
      
      if (!first_visible && !second_visible && !third_visible && !fourth_visible && !fifth_visible) /*just to have at least one active cube*/
		third_visible = 1;

      z_coord = -0.75-0.03; /*bringing z coordinate to the beginning of the platform; moving the center; 0.03 is half of the cube edge*/

      animation_parameter = 0;
    }
   

    z_coord +=(1/50.0*speed);  /*updating current position of the cubes*/

    /*scene drawing part*/

    glPushMatrix();
    	glScalef(1+animation_parameter%20/200.0, 1+animation_parameter%20/200.0, 1+animation_parameter%20/200.0); /*adding 0-10% of size*/
    	drawSpeakers();
    glPopMatrix();
 
   /*rotating part of the scene*/
 
    glRotatef(angle, 1, 0, 0);
    
    glPushMatrix();
        glTranslatef(0, 0, animation_parameter/50.0*speed);  
        drawCubes(first_visible, second_visible, third_visible, fourth_visible, fifth_visible);
    glPopMatrix();

 
    glPushMatrix();
	drawPlatformLines();
    glPopMatrix();


    glPushMatrix();
        drawPlatform();
    glPopMatrix();


    glutSwapBuffers();

}

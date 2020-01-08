#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 30

static int window_height, window_width;

static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display();
/*static void on_timer(int id);*/

int angle = 0;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(900, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Cube Hero");

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0, 0, 0.2, 0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

void drawPlatformLines()
{

 glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
        glColor3f(0,1,0);
        glVertex3f(-0.2,0.05,-0.75);  
        glVertex3f(-0.2,0.05,0.75);

        glColor3f(1,0,0);
        glVertex3f(-0.1,0.05,-0.75);  
        glVertex3f(-0.1,0.05,0.75);  

        glColor3f(1,1,0);
        glVertex3f(0,0.05,-0.75); 
        glVertex3f(0,0.05,0.75);

        glColor3f(0,0,1);
        glVertex3f(0.1,0.05,-0.75); 
        glVertex3f(0.1,0.05,0.75);

        glColor3f(1,0.6,0);
        glVertex3f(0.2,0.05,-0.75); 
        glVertex3f(0.2,0.05,0.75);

    glEnd();

    glEnable(GL_LIGHTING);
}

void drawSpeaker()
{
    
    glPushMatrix();
        glTranslatef(-1,0,-1);
	glColor3f(0, 0, 0);
	glScalef(0.3, 0.7, 0.3);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glTranslatef(0,0.1,0.5);
	glutSolidTorus(0.1, 0.2, 30, 30);
	

    glPopMatrix();


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


void drawAxes()
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

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 's':
    case 'S':
        exit(0);
    case 'w':
	angle+=30;
        break;
    case GLUT_KEY_DOWN:
   	/*TODO pomeranje platforme*/
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

static void on_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 1, 1,
            0, 0, 0,
            0, 1, 0
        );

    /*drawAxes();*/
   /* glRotatef(angle, 1,0,0);*/
    drawPlatformLines();
    drawPlatform();
    drawSpeaker();
    glutSwapBuffers();
}

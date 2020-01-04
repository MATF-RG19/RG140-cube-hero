#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 30

static int window_height, window_width;

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

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0, 0, 0.2, 0);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        exit(0);
    case GLUT_KEY_UP:
   	//TODO pomeranje platforme
        break;
    case GLUT_KEY_DOWN:
   	//TODO pomeranje platforme
        break;
    case GLUT_KEY_LEFT:
   	//TODO pomeranje platforme
        break;
    case GLUT_KEY_RIGHT:
   	//TODO pomeranje platforme
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
    gluPerspective(60, window_width/window_height, 1, 3);
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
    
    glColor3f(0, 0, 0);
    glScalef(1, 0.1, 7);
    glutSolidCube(1);

    glutSwapBuffers();
}

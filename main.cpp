#include <iostream>
#include <GL/glut.h>
#include <FTGL/ftgl.h>
#include <assert.h>

using namespace std;

char myString[4096] = "Kinetic Typography Generator";

// GL vars
GLint w_win = 640, h_win = 480;

const float OX = -270;
const float OY = 40;

// FTGL vars
FTSimpleLayout simpleLayout;

void setCamera()
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90, (float)w_win / (float)h_win, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, (float)h_win / 2.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void do_display()
{
    glTranslatef(OX, OY,0);

    glRotatef(40.0, 0, 1, 0);

    glColor3f(0.4, 0.4, 0.4);
    simpleLayout.Render(myString, -1, FTPoint(),
                        FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setCamera();    

    glPushMatrix();

        do_display();

    glPopMatrix();

    glutSwapBuffers();
}

FTFont *getFont(const char* file)
{
    FTFont *font = new FTPolygonFont(file);
    if (font->Error())
    {
        fprintf(stderr, "Failed to open font %s", file);
        exit(1);
    }

    if(!font->FaceSize(50))
    {
        fprintf(stderr, "Failed to set size");
        exit(1);
    }

    font->CharMap(ft_encoding_unicode);

    return font;
}

void myReshape(int w, int h)
{
    glMatrixMode (GL_MODELVIEW);
    glViewport (0, 0, w, h);
    glLoadIdentity();

    w_win = w;
    h_win = h;
    setCamera();
}

void myinit(const char* file)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0, 0, 0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH); // GL_FLAT would be also OK.

    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(1.0, 1.0);

    setCamera();

    // Configure the SimpleLayout for text
    simpleLayout.SetLineLength(600.0f);
    simpleLayout.SetFont(getFont(file));
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(w_win, h_win);
    glutCreateWindow("Kinetic Typography Generator");

    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutIdleFunc(display);

    myinit("/usr/share/fonts/TTF/DejaVuSans-Bold.ttf");

    glutMainLoop();

    return 0;
}

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.141516


// =====================================================
// GLOBAL VARIABLES
// =====================================================

int currentScenario = 1;


// =====================================================
// SCENARIO 1 VARIABLES - YOUR VARIABLES
// =====================================================

float cloudOffset = 0.0f;
float fireTime = 0.0f;
float flameAnim = 0.0f;

float starX[150];
float starY[150];


// =====================================================
// SCENARIO 2 VARIABLES
// FRIEND 2 PUTS VARIABLES HERE
// =====================================================



// =====================================================
// SCENARIO 3 VARIABLES
// FRIEND 3 PUTS VARIABLES HERE
// =====================================================



// =====================================================
// SCENARIO 4 VARIABLES
// FRIEND 4 PUTS VARIABLES HERE
// =====================================================



// =====================================================
// SCENARIO 5 VARIABLES
// FRIEND 5 PUTS VARIABLES HERE
// =====================================================




// =====================================================
// SCENARIO 1 FUNCTIONS - YOUR CODE
// =====================================================


// CIRCLE

void circleFunc(float x, float y, float r)
{
    int triangle = 100;

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (int i = 0; i <= triangle; i++)
    {
        float angle = 2.0f * PI * i / triangle;

        glVertex2f(
            x + r * cos(angle),
            y + r * sin(angle)
        );
    }

    glEnd();
}


// TRIANGLE

void drawTriangle(
    float x1, float y1,
    float x2, float y2,
    float x3, float y3)
{
    glBegin(GL_TRIANGLES);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);

    glEnd();
}


// MOON

void drawMoon()
{
    glColor3ub(220, 230, 255);

    circleFunc(
        0.88f,
        0.88f,
        0.08f
    );

    // Moon spots

    glColor3ub(190, 200, 220);

    circleFunc(0.86f, 0.90f, 0.012f);
    circleFunc(0.90f, 0.87f, 0.010f);
    circleFunc(0.88f, 0.91f, 0.007f);
    circleFunc(0.91f, 0.90f, 0.006f);
}


// STARS

void drawStars()
{
    glColor3ub(255, 255, 230);

    glPointSize(1.8f);

    glBegin(GL_POINTS);

    for (int i = 0; i < 150; i++)
    {
        glVertex2f(starX[i], starY[i]);
    }

    glEnd();
}


// CLOUD

void drawOneCloud()
{
    glColor3ub(40, 50, 70);

    circleFunc(0.03f, 0.75f, 0.04f);
    circleFunc(0.115f, 0.79f, 0.07f);
    circleFunc(0.10f, 0.79f, 0.07f);
    circleFunc(0.19f, 0.80f, 0.03f);
    circleFunc(0.18f, 0.80f, 0.03f);
    circleFunc(0.21f, 0.75f, 0.05f);
    circleFunc(0.20f, 0.75f, 0.05f);
    circleFunc(0.12f, 0.73f, 0.06f);
    circleFunc(0.06f, 0.71f, 0.03f);
}


// CLOUDS

void drawClouds()
{
    glPushMatrix();

    glTranslatef(cloudOffset, 0.0f, 0.0f);

    drawOneCloud();

    glTranslatef(2.0f, 0.0f, 0.0f);

    drawOneCloud();

    glPopMatrix();
}


// MOUNTAINS / HILLS

void drawEnvironment()
{
    // Back hill

    glColor3ub(20, 50, 20);

    glBegin(GL_POLYGON);

    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.1f, 0.25f);
    glVertex2f(0.1f, 0.45f);
    glVertex2f(0.3f, 0.60f);
    glVertex2f(0.5f, 0.45f);
    glVertex2f(0.7f, 0.25f);
    glVertex2f(0.9f, 0.0f);

    glEnd();


    // Dark side

    glColor3ub(15, 40, 15);

    glBegin(GL_POLYGON);

    glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.45f, 0.2f);
    glVertex2f(-0.3f, 0.35f);
    glVertex2f(-0.15f, 0.2f);
    glVertex2f(0.0f, 0.0f);

    glEnd();


    // Right hill

    glColor3ub(15, 40, 15);

    glBegin(GL_POLYGON);

    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.6f, 0.5f);
    glVertex2f(0.8f, 0.3f);
    glVertex2f(1.0f, 0.0f);

    glEnd();


    // River / lake

    glColor3ub(20, 40, 80);

    glBegin(GL_TRIANGLES);

    glVertex2f(-0.62f, 0.0f);
    glVertex2f(0.18f, -0.3f);
    glVertex2f(0.4f, 0.0f);

    glEnd();


    // Ground

    glColor3ub(5, 25, 5);

    glBegin(GL_POLYGON);

    glVertex2f(-1.0f, -0.2f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);

    glEnd();


    // Ground upper section

    glColor3ub(8, 35, 8);

    glBegin(GL_POLYGON);

    glVertex2f(-1.0f, -0.3f);
    glVertex2f(-0.8f, 0.2f);
    glVertex2f(-0.6f, 0.1f);
    glVertex2f(-0.4f, 0.0f);
    glVertex2f(0.0f, -0.15f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.4f, -0.3f);

    glEnd();
}


// TENT

void drawTent()
{
    // Left panel

    glColor3ub(70, 60, 0);

    glBegin(GL_POLYGON);

    glVertex2f(-0.72f, -0.45f);
    glVertex2f(-0.81f, -0.76f);
    glVertex2f(-0.78f, -0.75f);

    glEnd();


    // Main panel

    glColor3ub(90, 80, 0);

    glBegin(GL_POLYGON);

    glVertex2f(-0.72f, -0.45f);
    glVertex2f(-0.79f, -0.79f);
    glVertex2f(-0.58f, -0.80f);
    glVertex2f(-0.50f, -0.40f);

    glEnd();


    // Bright front

    glColor3ub(227, 224, 70);

    glBegin(GL_POLYGON);

    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.58f, -0.79f);
    glVertex2f(-0.50f, -0.77f);

    glEnd();


    glColor3ub(207, 204, 64);

    glBegin(GL_POLYGON);

    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.50f, -0.76f);
    glVertex2f(-0.40f, -0.76f);

    glEnd();


    // Tent small lines

    glColor3ub(180, 180, 180);

    glBegin(GL_LINES);

    glVertex2f(-0.40f, -0.76f);
    glVertex2f(-0.40f, -0.74f);

    glVertex2f(-0.58f, -0.80f);
    glVertex2f(-0.58f, -0.78f);

    glVertex2f(-0.79f, -0.79f);
    glVertex2f(-0.79f, -0.77f);

    glVertex2f(-0.81f, -0.76f);
    glVertex2f(-0.81f, -0.74f);

    glEnd();
}


// TWO TENTS

void drawTents()
{
    drawTent();

    glPushMatrix();

    glTranslatef(-0.60f, 0.05f, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f);

    drawTent();

    glPopMatrix();
}


// CAMPFIRE

void drawFire()
{
    float flicker = 0.01f * sin(flameAnim);


    // Outer fire

    glColor3ub(180, 60, 0);

    circleFunc(
        -0.32f,
        -0.78f,
        0.022f
    );


    // Orange flame

    glColor3ub(255, 120, 0);

    glBegin(GL_POLYGON);

    glVertex2f(-0.335f, -0.778f);
    glVertex2f(-0.305f, -0.778f);
    glVertex2f(-0.315f, -0.748f + flicker);
    glVertex2f(-0.320f, -0.738f + flicker);
    glVertex2f(-0.325f, -0.748f + flicker);

    glEnd();


    // Red flame

    glColor3ub(255, 80, 0);

    glBegin(GL_POLYGON);

    glVertex2f(-0.340f, -0.778f);
    glVertex2f(-0.320f, -0.778f);
    glVertex2f(-0.328f, -0.758f + flicker);
    glVertex2f(-0.336f, -0.750f + flicker);

    glEnd();


    // Yellow flame

    glColor3ub(255, 220, 0);

    glBegin(GL_POLYGON);

    glVertex2f(-0.330f, -0.778f);
    glVertex2f(-0.310f, -0.778f);
    glVertex2f(-0.316f, -0.758f + flicker);
    glVertex2f(-0.320f, -0.750f + flicker);
    glVertex2f(-0.324f, -0.758f + flicker);

    glEnd();


    circleFunc(
        -0.32f,
        -0.768f,
        0.007f
    );
}


// TREES

void drawTree(float x, float y, float s)
{
    glColor3ub(20, 50, 20);


    circleFunc(
        x - 0.10f * s,
        y + 0.35f * s,
        0.13f * s
    );


    circleFunc(
        x - 0.01f * s,
        y + 0.56f * s,
        0.13f * s
    );


    circleFunc(
        x + 0.10f * s,
        y + 0.49f * s,
        0.10f * s
    );


    circleFunc(
        x - 0.08f * s,
        y + 0.38f * s,
        0.13f * s
    );


    glColor3ub(30, 70, 30);


    circleFunc(
        x + 0.08f * s,
        y + 0.35f * s,
        0.13f * s
    );


    // trunk

    glColor3ub(40, 25, 10);

    drawTriangle(
        x,
        y + 0.5f * s,

        x - 0.02f * s,
        y,

        x + 0.02f * s,
        y
    );
}


// TREES

void drawTrees()
{
    drawTree(0.11f, -0.50f, 0.75f);
    drawTree(0.95f, -0.90f, 0.90f);
    drawTree(-0.97f, -0.75f, 1.25f);

    drawTree(-0.50f, 0.19f, 0.15f);
    drawTree(-0.15f, 0.19f, 0.11f);
    drawTree(0.40f, 0.40f, 0.11f);

    drawTree(-0.50f, -0.35f, 0.45f);
    drawTree(0.45f, -0.20f, 0.50f);
    drawTree(-0.40f, 0.14f, 0.15f);
    drawTree(0.10f, 0.12f, 0.15f);
    drawTree(0.80f, -0.30f, 0.65f);
}


// WATCH TOWER

void drawWatchTower()
{
    float x = 0.3f;
    float y = -0.2f;
    float s = 1.0f;


    // Legs

    glColor3f(0.10f, 0.06f, 0.03f);

    glBegin(GL_QUADS);

    glVertex2f(x - 0.07f*s, y);
    glVertex2f(x - 0.05f*s, y);
    glVertex2f(x - 0.05f*s, y + 0.25f*s);
    glVertex2f(x - 0.07f*s, y + 0.25f*s);

    glVertex2f(x + 0.05f*s, y);
    glVertex2f(x + 0.07f*s, y);
    glVertex2f(x + 0.07f*s, y + 0.25f*s);
    glVertex2f(x + 0.05f*s, y + 0.25f*s);

    glEnd();


    // Platform

    glColor3f(0.08f, 0.04f, 0.02f);

    glBegin(GL_QUADS);

    glVertex2f(x - 0.08f*s, y + 0.23f*s);
    glVertex2f(x + 0.08f*s, y + 0.23f*s);
    glVertex2f(x + 0.08f*s, y + 0.27f*s);
    glVertex2f(x - 0.08f*s, y + 0.27f*s);

    glEnd();


    // Roof

    glColor3f(0.10f, 0.03f, 0.01f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x - 0.12f*s, y + 0.35f*s);
    glVertex2f(x,             y + 0.40f*s);
    glVertex2f(x + 0.12f*s, y + 0.35f*s);

    glEnd();


    // Support lines

    glColor3f(0.05f, 0.03f, 0.01f);

    glBegin(GL_LINES);

    glVertex2f(x - 0.05f*s, y + 0.07f*s);
    glVertex2f(x + 0.05f*s, y + 0.15f*s);

    glVertex2f(x - 0.05f*s, y + 0.15f*s);
    glVertex2f(x + 0.05f*s, y + 0.07f*s);

    glEnd();
}



// =====================================================
// SCENARIO 2 FUNCTIONS
// FRIEND 2 PUTS HIS FUNCTIONS HERE
// =====================================================


// Example:
//
// void drawSomething()
// {
//     ...
// }
//
// void drawSomethingElse()
// {
//     ...
// }



// =====================================================
// SCENARIO 3 FUNCTIONS
// FRIEND 3 PUTS HIS FUNCTIONS HERE
// =====================================================



// =====================================================
// SCENARIO 4 FUNCTIONS
// FRIEND 4 PUTS HIS FUNCTIONS HERE
// =====================================================



// =====================================================
// SCENARIO 5 FUNCTIONS
// FRIEND 5 PUTS HIS FUNCTIONS HERE
// =====================================================




// =====================================================
// SCENARIO 1
// =====================================================

void scenario1()
{
    drawMoon();

    drawStars();

    drawClouds();

    drawEnvironment();

    drawTrees();

    drawWatchTower();

    drawTents();

    drawFire();
}


// =====================================================
// SCENARIO 2
// =====================================================

void scenario2()
{
    // FRIEND 2 PUTS HIS DRAWING CALLS HERE


    // Example:
    //
    // drawSky();
    // drawSun();
    // drawClouds();
    // drawTrees();
}


// =====================================================
// SCENARIO 3
// =====================================================

void scenario3()
{
    // FRIEND 3 PUTS HIS DRAWING CALLS HERE
}


// =====================================================
// SCENARIO 4
// =====================================================

void scenario4()
{
    // FRIEND 4 PUTS HIS DRAWING CALLS HERE
}


// =====================================================
// SCENARIO 5
// =====================================================

void scenario5()
{
    // FRIEND 5 PUTS HIS DRAWING CALLS HERE
}




// =====================================================
// DISPLAY
// =====================================================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();


    // =================================================
    // SCENARIO 1
    // =================================================

    if (currentScenario == 1)
    {
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        gluOrtho2D(
            -1,
            1,
            -1,
            1
        );

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();


        glClearColor(
            0.05f,
            0.08f,
            0.18f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        scenario1();
    }


    // =================================================
    // SCENARIO 2
    // =================================================

    else if (currentScenario == 2)
    {
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();


        // FRIEND 2 CHANGE THIS
        // ACCORDING TO HIS COORDINATE SYSTEM

        gluOrtho2D(
            -1,
            1,
            -1,
            1
        );


        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();


        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        scenario2();
    }


    // =================================================
    // SCENARIO 3
    // =================================================

    else if (currentScenario == 3)
    {
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();


        // FRIEND 3 CHANGE THIS
        // ACCORDING TO HIS COORDINATE SYSTEM

        gluOrtho2D(
            -1,
            1,
            -1,
            1
        );


        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();


        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        scenario3();
    }


    // =================================================
    // SCENARIO 4
    // =================================================

    else if (currentScenario == 4)
    {
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();


        // FRIEND 4 CHANGE THIS
        // ACCORDING TO HIS COORDINATE SYSTEM

        gluOrtho2D(
            -1,
            1,
            -1,
            1
        );


        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();


        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        scenario4();
    }


    // =================================================
    // SCENARIO 5
    // =================================================

    else if (currentScenario == 5)
    {
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();


        // FRIEND 5 CHANGE THIS
        // ACCORDING TO HIS COORDINATE SYSTEM

        gluOrtho2D(
            -1,
            1,
            -1,
            1
        );


        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();


        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        scenario5();
    }


    glFlush();
}



// =====================================================
// KEYBOARD
// =====================================================

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
    {
        currentScenario = 1;
    }

    else if (key == '2')
    {
        currentScenario = 2;
    }

    else if (key == '3')
    {
        currentScenario = 3;
    }

    else if (key == '4')
    {
        currentScenario = 4;
    }

    else if (key == '5')
    {
        currentScenario = 5;
    }


    glutPostRedisplay();
}



// =====================================================
// TIMER
// =====================================================

void update(int value)
{
    // =================================================
    // YOUR SCENARIO 1 ANIMATION
    // =================================================

    cloudOffset += 0.0005f;

    flameAnim += 0.1f;


    if (cloudOffset > 1.0f)
    {
        cloudOffset = -1.0f;
    }


    fireTime += 0.05f;


    // =================================================
    // FRIENDS CAN ADD THEIR ANIMATION HERE
    // =================================================

    // Friend 2:
    // animation code


    // Friend 3:
    // animation code


    // Friend 4:
    // animation code


    // Friend 5:
    // animation code


    glutPostRedisplay();


    glutTimerFunc(
        16,
        update,
        0
    );
}



// =====================================================
// INITIALIZATION
// =====================================================

void init()
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();


    gluOrtho2D(
        -1,
        1,
        -1,
        1
    );


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    // =================================================
    // STARS
    // =================================================

    for (int i = 0; i < 150; i++)
    {
        starX[i] =
            (rand() % 200) / 100.0f - 1.0f;

        starY[i] =
            (rand() % 60) / 100.0f + 0.40f;
    }
}



// =====================================================
// MAIN
// =====================================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);


    glutInitDisplayMode(
        GLUT_SINGLE |
        GLUT_RGB
    );


    glutInitWindowSize(
        1000,
        700
    );


    glutCreateWindow(
        "Group Graphics Project"
    );


    init();


    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);


    glutTimerFunc(
        16,
        update,
        0
    );


    glutMainLoop();


    return 0;
}

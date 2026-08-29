#include <windows.h>
#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

GLfloat carPos = 0.0f;
GLfloat carSpeed = 0.02f;

GLfloat cloudPos = 0.0f;
GLfloat cloudSpeed = 0.002f;

GLfloat turbineAngle = 0.0f;
GLfloat turbineSpeed = 2.0f;

GLfloat birdPos = 0.0f;
GLfloat birdSpeed = 0.005f;

bool isRaining = false;
GLfloat rainDropOffset = 0.0f;
GLfloat rainSpeed = 0.05f;
GLfloat sunYPos = 0.45f;

void drawCircle(GLfloat x, GLfloat y, GLfloat radius, int triangleAmount = 100) {
    GLfloat twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawTurbine() {
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.02f, 0.0f);
    glVertex2f(0.02f, 0.0f);
    glVertex2f(0.01f, 0.4f);
    glVertex2f(-0.01f, 0.4f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    glRotatef(turbineAngle, 0.0f, 0.0f, 1.0f);

    glLineWidth(4.0f);
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, -0.2f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.17f, 0.1f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.17f, 0.1f);
    glEnd();
    glPopMatrix();

    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(0.0f, 0.4f, 0.02f);
}

void drawRain() {
    glColor3f(0.6f, 0.8f, 1.0f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (float i = -1.2f; i < 1.2f; i += 0.15f) {
        for (float j = -1.0f; j < 1.2f; j += 0.2f) {
            float x = i + (fmod(j, 0.4f) < 0.1f ? 0.05f : 0.0f);
            float y = j - rainDropOffset;

            if (y < -1.0f) y += 2.0f;

            glVertex2f(x, y);
            glVertex2f(x - 0.02f, y - 0.05f);
        }
    }
    glEnd();
}

void display() {
    /**........................................ Sky ...........................................**/
    if (isRaining) {
        glClearColor(0.4f, 0.6f, 0.7f, 1.0f);
    } else {
        glClearColor(0.3f, 0.65f, 0.9f, 1.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    /**........................................Sun...........................................**/
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.0f);
    drawCircle(-0.05f, sunYPos, 0.15f);
    glPopMatrix();

    /**........................................Hill...........................................**/
    glPushMatrix();
    glColor3f(0.18f, 0.54f, 0.34f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.0f, 0.2f);
    glVertex2f(-0.4f, 0.6f);
    glVertex2f(0.2f, 0.2f);

    glVertex2f(-0.1f, 0.2f);
    glVertex2f(0.4f, 0.5f);
    glVertex2f(1.0f, 0.2f);
    glEnd();
    glPopMatrix();

    /**........................................ Wind Turbines ...........................................**/
    glPushMatrix();
    glTranslatef(-0.6f, 0.35f, 0.0f);
    glScalef(0.6f, 0.6f, 1.0f);
    drawTurbine();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, 0.45f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    drawTurbine();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.3f, 0.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    drawTurbine();
    glPopMatrix();

    /**........................................ Ground...........................................**/
    glPushMatrix();
    glColor3f(0.33f, 0.68f, 0.22f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.2f);
    glVertex2f(1.0f, 0.2f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    glPopMatrix();

    /**........................................ River ...........................................**/
    glPushMatrix();
    glColor3f(0.12f, 0.45f, 0.85f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(0.8f, -1.0f);
    glVertex2f(-0.5f, -1.0f);
    glVertex2f(-0.3f, -0.4f);
    glEnd();
    glPopMatrix();

    /**........................................ Road ...........................................**/
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.6f);
    glVertex2f(1.0f, -0.6f);
    glVertex2f(1.0f, -0.85f);
    glVertex2f(-1.0f, -0.85f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    for(float i = -1.0f; i < 1.0f; i += 0.2f) {
        glVertex2f(i, -0.71f);
        glVertex2f(i + 0.1f, -0.71f);
        glVertex2f(i + 0.1f, -0.74f);
        glVertex2f(i, -0.74f);
    }
    glEnd();
    glPopMatrix();

    /**........................................ Car ...........................................**/
    glPushMatrix();
    glTranslatef(carPos, -0.725f, 0.0f);

    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(-0.08f, -0.06f, 0.035f);
    drawCircle(0.08f, -0.06f, 0.035f);

    glColor3f(0.8f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.05f);
    glVertex2f(0.15f, -0.05f);
    glVertex2f(0.15f, 0.03f);
    glVertex2f(-0.15f, 0.03f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.08f, 0.03f);
    glVertex2f(0.05f, 0.03f);
    glVertex2f(0.02f, 0.09f);
    glVertex2f(-0.05f, 0.09f);
    glEnd();

    glColor3f(0.6f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.07f, 0.03f);
    glVertex2f(-0.01f, 0.03f);
    glVertex2f(-0.01f, 0.08f);
    glVertex2f(-0.04f, 0.08f);

    glVertex2f(0.01f, 0.03f);
    glVertex2f(0.04f, 0.03f);
    glVertex2f(0.015f, 0.08f);
    glVertex2f(0.01f, 0.08f);
    glEnd();
    glPopMatrix();

    /**........................................ Clouds(Left) ...........................................**/
    glPushMatrix();
    glTranslatef(cloudPos, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    if(isRaining) glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(-0.2f, 0.8f, 0.08f);
    drawCircle(-0.3f, 0.75f, 0.06f);
    drawCircle(-0.1f, 0.75f, 0.06f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, 0.69f);
    glVertex2f(-0.1f, 0.69f);
    glVertex2f(-0.1f, 0.75f);
    glVertex2f(-0.3f, 0.75f);
    glEnd();
    glPopMatrix();

    /**........................................ Clouds(Right) ...........................................**/
    glPushMatrix();
    glTranslatef(cloudPos * 0.8f, 0.0f, 0.0f);
    drawCircle(0.5f, 0.7f, 0.06f);
    drawCircle(0.43f, 0.67f, 0.04f);
    drawCircle(0.57f, 0.67f, 0.04f);
    glBegin(GL_QUADS);
    glVertex2f(0.43f, 0.63f);
    glVertex2f(0.57f, 0.63f);
    glVertex2f(0.57f, 0.67f);
    glVertex2f(0.43f, 0.67f);
    glEnd();
    glPopMatrix();

    /**........................................ Trees(Left) ...........................................**/
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(-0.85f, -0.2f);
    glVertex2f(-0.75f, -0.2f);
    glVertex2f(-0.75f, 0.5f);
    glVertex2f(-0.85f, 0.5f);
    glEnd();

    glColor3f(0.13f, 0.54f, 0.13f);
    drawCircle(-0.8f, 0.6f, 0.2f);
    drawCircle(-0.95f, 0.45f, 0.15f);
    drawCircle(-0.65f, 0.45f, 0.15f);
    glPopMatrix();

    /**........................................ Trees(Right) ...........................................**/
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(0.8f, -0.1f);
    glVertex2f(0.85f, -0.1f);
    glVertex2f(0.85f, 0.3f);
    glVertex2f(0.8f, 0.3f);
    glEnd();

    glColor3f(0.13f, 0.54f, 0.13f);
    drawCircle(0.825f, 0.4f, 0.15f);
    drawCircle(0.7f, 0.3f, 0.12f);
    drawCircle(0.95f, 0.3f, 0.12f);
    glPopMatrix();

    /**........................................ Tent...........................................**/
    glPushMatrix();
    glTranslatef(0.6f, -0.2f, 0.0f);

    glColor3f(0.9f, 0.5f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.15f, -0.05f);
    glVertex2f(0.15f, -0.05f);
    glEnd();

    glColor3f(0.3f, 0.1f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.1f);
    glVertex2f(-0.06f, -0.05f);
    glVertex2f(0.06f, -0.05f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(0.0f, 0.24f);
    glEnd();
    glPopMatrix();

    /**........................................Bird...........................................**/
    glPushMatrix();
    glTranslatef(birdPos, 0.0f, 0.0f);

    glColor3f(0.15f, 0.15f, 0.15f);
    glLineWidth(2.0f);

    glTranslatef(0.05f, 0.85f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.04f, -0.03f);
    glVertex2f(0.08f, 0.0f);
    glEnd();

    glScalef(0.8f, 0.8f, 1.0f);
    glTranslatef(0.2f, 0.05f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.04f, -0.03f);
    glVertex2f(0.08f, 0.0f);
    glEnd();

    glScalef(1.2f, 1.2f, 1.0f);
    glTranslatef(-0.3f, 0.02f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.04f, -0.03f);
    glVertex2f(0.08f, 0.0f);
    glEnd();

    glScalef(0.6f, 0.6f, 1.0f);
    glTranslatef(0.5f, -0.1f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.04f, -0.03f);
    glVertex2f(0.08f, 0.0f);
    glEnd();

    glScalef(1.5f, 1.5f, 1.0f);
    glTranslatef(0.15f, 0.12f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.04f, -0.03f);
    glVertex2f(0.08f, 0.0f);
    glEnd();
    glPopMatrix();

    /**........................................ Rain ...........................................**/
    if (isRaining) {
        drawRain();
    }

    glFlush();
}

void update(int value) {
    carPos += carSpeed;
    if (carPos > 1.2f) {
        carPos = -1.2f;
    } else if (carPos < -1.2f) {
        carPos = 1.2f;
    }

    cloudPos += cloudSpeed;
    if (cloudPos > 1.5f) {
        cloudPos = -1.5f;
    }

    turbineAngle -= turbineSpeed;
    if (turbineAngle < -360.0f) {
        turbineAngle += 360.0f;
    }

    birdPos += birdSpeed;
    if (birdPos > 2.0f) {
        birdPos = -2.0f;
    }

    if (isRaining) {
        if (sunYPos > 0.05f) {
            sunYPos -= 0.005f;
        }

        rainDropOffset += rainSpeed;
        if (rainDropOffset > 2.0f) {
            rainDropOffset -= 2.0f;
        }
    } else {
        if (sunYPos < 0.45f) {
            sunYPos += 0.005f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void weatherChange(int value) {
    isRaining = !isRaining;

    if(isRaining) {
        PlaySound("rain.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    } else {
        PlaySound("birds.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    }

    glutTimerFunc(10000, weatherChange, 0);
}

void KeyboardInput(unsigned char key, int x, int y) {
    if (key == 'h' || key == 'H') {
        PlaySound("horn.wav", NULL, SND_ASYNC|SND_FILENAME);
    }
}


void SpecialInput(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            carSpeed += 0.01f;
            break;
        case GLUT_KEY_DOWN:
            carSpeed -= 0.01f;
            break;
        case GLUT_KEY_LEFT:
            carSpeed = -fabs(carSpeed);
            break;
        case GLUT_KEY_RIGHT:
            carSpeed = fabs(carSpeed);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Md Mahfuzar Rahman Bhuban (24-56367-1)");
    glutDisplayFunc(display);

    PlaySound("birds.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

    glutKeyboardFunc(KeyboardInput);
    glutSpecialFunc(SpecialInput);
    glutTimerFunc(100, update, 0);
    glutTimerFunc(10000, weatherChange, 0);

    glutMainLoop();
    return 0;
}

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
const float PI = 3.1416f;
float cloud1Offset = 0.0f;
float cloud2Offset = 0.0f;
float sunOffset = 0.0f;
bool paused = false;
// ELLIPSE
void drawEllipse(float x, float y,float radiusX, float radiusY)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 80; i++)
    {float angle = 2.0f * PI * i / 80.0f;
        glVertex2f(x + cos(angle) * radiusX,y + sin(angle) * radiusY);}
    glEnd();
}
// CIRCLE
void drawCircle(float x, float y, float radius)
{
    drawEllipse(x,y,radius,radius);
}
// SKY
void drawSky()
{
    glBegin(GL_QUADS);

    // Bottom of sky
    glColor3f(1.0f,0.776f,0.216f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    // Top of sky
    glColor3f(1.0f,0.565f,0.141f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
}
// SUN
void drawSun()
{
    // Original sun position converted
    const float sunX = 0.04f;
    const float sunY = 0.354f;
    // Sun rays
    glLineWidth(5.0f);
    glColor3f(1.0f,0.843f,0.325f);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++)
    {
        float angle =2.0f * PI * i / 12.0f;
        glVertex2f(sunX + cos(angle) * 0.207f,sunY + sin(angle) * 0.259f);
        glVertex2f(
            sunX + cos(angle) * 0.278f,
            sunY + sin(angle) * 0.348f
        );
    }
    glEnd();
    // Sun body
    glColor3f(1.0f,0.812f,0.231f);
    drawEllipse(
        sunX,
        sunY,
        0.168f,
        0.210f
    );
}
// CLOUD
void drawCloud(float x, float y, float scale)
{
    glColor3f(1.0f,0.898f,0.643f);
    // Cloud base
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(
        x + 0.371f * scale,
        y
    );
    glVertex2f(
        x + 0.350f * scale,
        y + 0.053f * scale
    );
    glVertex2f(
        x + 0.021f * scale,
        y + 0.053f * scale
    );
    glEnd();
    // Cloud 1
    drawEllipse(
        x + 0.074f * scale,
        y + 0.050f * scale,
        0.071f * scale,
        0.075f * scale
    );
    // Cloud 2
    drawEllipse(
        x + 0.150f * scale,
        y + 0.084f * scale,
        0.078f * scale,
        0.116f * scale
    );
    // Cloud 3
    drawEllipse(
        x + 0.228f * scale,
        y + 0.139f * scale,
        0.083f * scale,
        0.128f * scale
    );
    // Cloud 4
    drawEllipse(
        x + 0.296f * scale,
        y + 0.075f * scale,
        0.075f * scale,
        0.089f * scale
    );
}
// MOVING CLOUDS
void drawClouds()
{
    // CLOUD 1
    glPushMatrix();
    glTranslatef(
        cloud1Offset,
        0.0f,
        0.0f
    );
    drawCloud(
        -0.573f,
        0.247f,
        1.0f
    );
    glPopMatrix();
    // CLOUD 2
    glPushMatrix();
    glTranslatef(
        cloud2Offset,
        0.0f,
        0.0f
    );
    drawCloud(
        0.292f,
        0.675f,
        0.82f
    );
    glPopMatrix();
}
// MOVING SUN
void drawMovingSun()
{
    glPushMatrix();
    glTranslatef(
        0.0f,
        sunOffset,
        0.0f
    );

    drawSun();

    glPopMatrix();
}
// MOUNTAINS
void drawMountains()
{
    // BACK MOUNTAIN
    glColor3f(0.243f,0.565f,0.325f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 0.123f);
    glVertex2f(-0.786f, 0.255f);
    glVertex2f(-0.558f, 0.043f);
    glVertex2f(-0.404f, 0.163f);
    glVertex2f(-0.179f, -0.037f);
    glVertex2f(-0.100f, 0.017f);
    glVertex2f(0.083f, -0.136f);
    glVertex2f(0.344f, 0.075f);
    glVertex2f(0.548f, -0.046f);
    glVertex2f(0.777f, 0.106f);
    glVertex2f(1.0f, 0.024f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    // FRONT MOUNTAIN
    glColor3f(0.145f,0.490f,0.290f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 0.043f);
    glVertex2f(-0.743f, 0.185f);
    glVertex2f(-0.515f, -0.064f);
    glVertex2f(-0.294f, -0.251f);
    glVertex2f(-0.102f, -0.082f);
    glVertex2f(0.055f, -0.224f);
    glVertex2f(0.326f, 0.007f);
    glVertex2f(0.560f, -0.198f);
    glVertex2f(0.795f, -0.037f);
    glVertex2f(1.0f, -0.153f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    // CENTER MOUNTAIN
    glColor3f(0.173f,0.518f,0.306f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.636f, -0.030f);
    glVertex2f(-0.387f, -0.224f);
    glVertex2f(-0.186f, -0.376f);
    glVertex2f(0.005f, -0.251f);
    glVertex2f(0.197f, -0.404f);
    glVertex2f(0.504f, -0.126f);
    glVertex2f(0.639f, -0.278f);
    glVertex2f(0.639f, -1.0f);
    glVertex2f(-0.636f, -1.0f);
    glEnd();
}
// BUSH ROW
void drawBushRow(
    float y,
    float radius,
    int red,
    int green,
    int blue,
    float spacing,
    float offset)
{
    glColor3f(
        red / 255.0f,
        green / 255.0f,
        blue / 255.0f
    );

    for (
        float x = -1.0f - radius + offset;
        x < 1.0f + radius;
        x += spacing)
    {
        float wave =
            ((int)(x / spacing) % 3)
            * 0.023f;

        drawCircle(
            x,
            y + wave,
            radius
        );

        drawCircle(
            x + radius * 0.62f,
            y + radius * 0.28f
              - wave * 0.25f,
            radius * 0.78f
        );
    }
}
// BROAD LEAF
void drawBroadLeaf(
    float x,
    float y,
    float angle,
    float length,
    float width,
    int red,
    int green,
    int blue)
{
    glPushMatrix();

    glTranslatef(
        x,
        y,
        0.0f
    );

    glRotatef(
        angle,
        0.0f,
        0.0f,
        1.0f
    );

    glColor3f(
        red / 255.0f,
        green / 255.0f,
        blue / 255.0f
    );

    glBegin(GL_POLYGON);

    glVertex2f(
        0.0f,
        0.0f
    );

    glVertex2f(
        length * 0.18f,
        width * 0.48f
    );

    glVertex2f(
        length * 0.48f,
        width * 0.58f
    );

    glVertex2f(
        length * 0.78f,
        width * 0.35f
    );

    glVertex2f(
        length,
        0.0f
    );

    glVertex2f(
        length * 0.75f,
        -width * 0.30f
    );

    glVertex2f(
        length * 0.43f,
        -width * 0.48f
    );

    glVertex2f(
        length * 0.16f,
        -width * 0.38f
    );

    glEnd();


    // Leaf vein

    glLineWidth(3.0f);

    glColor3f(
        16.0f / 255.0f,
        91.0f / 255.0f,
        48.0f / 255.0f
    );

    glBegin(GL_LINES);

    glVertex2f(
        0.0f,
        0.0f
    );

    glVertex2f(
        length * 0.88f,
        0.0f
    );

    glEnd();

    glPopMatrix();
}
// PALM LEAF
void drawJaggedPalmLeaf(
    float x,
    float y,
    float angle,
    float length,
    float width)
{
    glPushMatrix();

    glTranslatef(
        x,
        y,
        0.0f
    );

    glRotatef(
        angle,
        0.0f,
        0.0f,
        1.0f
    );

    glColor3f(
        12.0f / 255.0f,
        105.0f / 255.0f,
        47.0f / 255.0f
    );

    glBegin(GL_POLYGON);

    glVertex2f(0.0f, 0.0f);

    glVertex2f(
        length * 0.12f,
        width * 0.28f
    );

    glVertex2f(
        length * 0.22f,
        width * 0.16f
    );

    glVertex2f(
        length * 0.31f,
        width * 0.42f
    );

    glVertex2f(
        length * 0.42f,
        width * 0.22f
    );

    glVertex2f(
        length * 0.54f,
        width * 0.45f
    );

    glVertex2f(
        length * 0.65f,
        width * 0.20f
    );

    glVertex2f(
        length * 0.78f,
        width * 0.32f
    );

    glVertex2f(
        length,
        0.0f
    );

    glVertex2f(
        length * 0.76f,
        -width * 0.28f
    );

    glVertex2f(
        length * 0.62f,
        -width * 0.16f
    );

    glVertex2f(
        length * 0.49f,
        -width * 0.38f
    );

    glVertex2f(
        length * 0.38f,
        -width * 0.17f
    );

    glVertex2f(
        length * 0.24f,
        -width * 0.34f
    );

    glVertex2f(
        length * 0.12f,
        -width * 0.15f
    );

    glEnd();
    // Middle line of leaf
    glColor3f(
        8.0f / 255.0f,
        79.0f / 255.0f,
        41.0f / 255.0f
    );
    glLineWidth(3.0f);

    glBegin(GL_LINES);

    glVertex2f(
        0.0f,
        0.0f
    );

    glVertex2f(
        length * 0.91f,
        0.0f
    );

    glEnd();

    glPopMatrix();
}
// LARGE LEFT TREE
void drawLargeLeftTree()
{
    // TRUNK
    glColor3f(
        68.0f / 255.0f,
        45.0f / 255.0f,
        24.0f / 255.0f
    );

    glBegin(GL_POLYGON);

    glVertex2f(-0.922f, -0.350f);
    glVertex2f(-0.840f, 0.283f);
    glVertex2f(-0.826f, 0.907f);
    glVertex2f(-0.754f, 0.934f);
    glVertex2f(-0.746f, 0.333f);
    glVertex2f(-0.780f, -0.359f);

    glEnd();
    glBegin(GL_POLYGON);

    glVertex2f(-0.823f, 0.355f);
    glVertex2f(-0.943f, 0.683f);
    glVertex2f(-0.925f, 0.719f);
    glVertex2f(-0.785f, 0.478f);

    glEnd();
    glBegin(GL_POLYGON);

    glVertex2f(-0.786f, 0.397f);
    glVertex2f(-0.644f, 0.749f);
    glVertex2f(-0.615f, 0.722f);
    glVertex2f(-0.758f, 0.283f);

    glEnd();
    glBegin(GL_POLYGON);

    glVertex2f(-0.786f, 0.627f);
    glVertex2f(-0.707f, 0.979f);
    glVertex2f(-0.663f, 0.979f);
    glVertex2f(-0.751f, 0.565f);

    glEnd();
    // DEEP CANOPY
    glColor3f(
        4.0f / 255.0f,
        79.0f / 255.0f,
        48.0f / 255.0f
    );

    drawCircle(-0.946f, 0.674f, 0.133f);
    drawCircle(-0.840f, 0.783f, 0.154f);
    drawCircle(-0.712f, 0.811f, 0.150f);
    drawCircle(-0.583f, 0.802f, 0.157f);
    drawCircle(-0.480f, 0.746f, 0.150f);
    drawCircle(-0.387f, 0.639f, 0.111f);

    drawCircle(-0.966f, 0.878f, 0.171f);
    drawCircle(-0.832f, 0.979f, 0.192f);
    drawCircle(-0.662f, 0.991f, 0.188f);
    drawCircle(-0.501f, 0.942f, 0.160f);
    // LIGHTER LEAVES
    glColor3f(
        23.0f / 255.0f,
        102.0f / 255.0f,
        45.0f / 255.0f
    );
    drawCircle(-0.974f, 0.991f, 0.174f);
    drawCircle(-0.850f, 1.010f, 0.179f);
    drawCircle(-0.705f, 1.023f, 0.169f);
    drawCircle(-0.565f, 1.009f, 0.168f);
    drawCircle(-0.444f, 0.979f, 0.108f);
    // HANGING VINE 1
    glColor3f(
        3.0f / 255.0f,
        101.0f / 255.0f,
        49.0f / 255.0f
    );

    glLineWidth(5.0f);

    glBegin(GL_LINE_STRIP);

    glVertex2f(-0.980f, 0.674f);
    glVertex2f(-0.974f, 0.483f);
    glVertex2f(-0.954f, 0.336f);
    glVertex2f(-0.927f, 0.261f);
    glVertex2f(-0.908f, 0.318f);

    glEnd();
    // HANGING VINE 2
    glBegin(GL_LINE_STRIP);

    glVertex2f(-0.581f, 0.659f);
    glVertex2f(-0.581f, 0.436f);
    glVertex2f(-0.565f, 0.333f);
    glVertex2f(-0.536f, 0.294f);
    glVertex2f(-0.506f, 0.338f);
    glVertex2f(-0.487f, 0.404f);
    glVertex2f(-0.484f, 0.659f);

    glEnd();

    // HANGING VINE 3

    glBegin(GL_LINE_STRIP);

    glVertex2f(-0.669f, 0.677f);
    glVertex2f(-0.671f, 0.459f);
    glVertex2f(-0.657f, 0.348f);
    glVertex2f(-0.629f, 0.298f);
    glVertex2f(-0.602f, 0.334f);
    glVertex2f(-0.584f, 0.441f);

    glEnd();
}
//plam tree

void drawPalmTree()
{
//trunk

    glColor3f(
        116.0f / 255.0f,
        71.0f / 255.0f,
        18.0f / 255.0f
    );

    glBegin(GL_POLYGON);

    glVertex2f(0.725f, -0.457f);
    glVertex2f(0.776f, -0.457f);
    glVertex2f(0.753f, -0.154f);
    glVertex2f(0.715f, 0.145f);
    glVertex2f(0.696f, 0.355f);
    glVertex2f(0.667f, 0.355f);
    glVertex2f(0.683f, 0.137f);
    glVertex2f(0.706f, -0.161f);

    glEnd();

//trunk line

    glColor3f(
        81.0f / 255.0f,
        53.0f / 255.0f,
        18.0f / 255.0f
    );

    glLineWidth(3.0f);

    glBegin(GL_LINES);

    glVertex2f(0.709f, 0.230f);
    glVertex2f(0.742f, 0.212f);

    glVertex2f(0.705f, 0.144f);
    glVertex2f(0.748f, 0.127f);

    glVertex2f(0.698f, 0.059f);
    glVertex2f(0.753f, 0.038f);

    glVertex2f(0.698f, -0.029f);
    glVertex2f(0.760f, -0.055f);

    glVertex2f(0.701f, -0.126f);
    glVertex2f(0.768f, -0.150f);

    glVertex2f(0.708f, -0.234f);
    glVertex2f(0.772f, -0.258f);

    glVertex2f(0.718f, -0.340f);
    glVertex2f(0.775f, -0.358f);

    glEnd();

//plam leaves

    float leafX = 0.686f;
    float leafY = 0.353f;

    drawJaggedPalmLeaf(
        leafX,
        leafY,
        166.0f,
        0.356f,
        0.134f
    );

    drawJaggedPalmLeaf(
        leafX,
        leafY,
        141.0f,
        0.392f,
        0.137f
    );

    drawJaggedPalmLeaf(
        leafX,
        leafY,
        112.0f,
        0.349f,
        0.125f
    );

    drawJaggedPalmLeaf(
        leafX,
        leafY,
        76.0f,
        0.314f,
        0.114f
    );

    drawJaggedPalmLeaf(
        leafX,
        leafY,
        38.0f,
        0.349f,
        0.132f
    );

    drawJaggedPalmLeaf(
        leafX,
        leafY,
        5.0f,
        0.378f,
        0.139f
    );

    drawJaggedPalmLeaf(
        leafX,
        leafY,
        -27.0f,
        0.328f,
        0.128f
    );

    drawJaggedPalmLeaf(
        leafX,
        leafY,
        -62.0f,
        0.285f,
        0.111f
    );
}
//left forground

void drawLeftForegroundPlants()
{
    drawBroadLeaf(
        -0.883f,
        -0.875f,
        25.0f,
        0.470f,
        0.143f,
        51, 139, 37
    );

    drawBroadLeaf(
        -0.883f,
        -0.875f,
        45.0f,
        0.513f,
        0.152f,
        45, 151, 44
    );

    drawBroadLeaf(
        -0.883f,
        -0.875f,
        67.0f,
        0.570f,
        0.146f,
        54, 159, 45
    );

    drawBroadLeaf(
        -0.883f,
        -0.875f,
        91.0f,
        0.642f,
        0.137f,
        50, 152, 42
    );

    drawBroadLeaf(
        -0.883f,
        -0.875f,
        112.0f,
        0.563f,
        0.132f,
        44, 139, 38
    );

    drawBroadLeaf(
        -0.883f,
        -0.875f,
        135.0f,
        0.492f,
        0.128f,
        37, 126, 37
    );


    drawBroadLeaf(
        -0.479f,
        -0.875f,
        40.0f,
        0.207f,
        0.080f,
        40, 133, 37
    );

    drawBroadLeaf(
        -0.479f,
        -0.875f,
        65.0f,
        0.221f,
        0.080f,
        48, 142, 38
    );

    drawBroadLeaf(
        -0.479f,
        -0.875f,
        95.0f,
        0.185f,
        0.071f,
        42, 128, 35
    );

    drawBroadLeaf(
        -0.479f,
        -0.875f,
        120.0f,
        0.221f,
        0.078f,
        45, 138, 36
    );
}


//right forground plants

void drawRightForegroundPlants()
{
    drawBroadLeaf(
        0.783f,
        -0.875f,
        40.0f,
        0.492f,
        0.139f,
        43, 137, 40
    );

    drawBroadLeaf(
        0.783f,
        -0.875f,
        61.0f,
        0.613f,
        0.152f,
        47, 149, 42
    );

    drawBroadLeaf(
        0.783f,
        -0.875f,
        83.0f,
        0.649f,
        0.146f,
        55, 158, 44
    );

    drawBroadLeaf(
        0.783f,
        -0.875f,
        105.0f,
        0.549f,
        0.136f,
        47, 143, 39
    );

    drawBroadLeaf(
        0.783f,
        -0.875f,
        128.0f,
        0.477f,
        0.130f,
        36, 126, 36
    );

    drawBroadLeaf(
        0.783f,
        -0.875f,
        153.0f,
        0.406f,
        0.125f,
        32, 115, 35
    );


    drawBroadLeaf(
        0.326f,
        -0.884f,
        25.0f,
        0.257f,
        0.086f,
        36, 126, 34
    );

    drawBroadLeaf(
        0.326f,
        -0.884f,
        52.0f,
        0.264f,
        0.086f,
        42, 137, 36
    );

    drawBroadLeaf(
        0.326f,
        -0.884f,
        80.0f,
        0.271f,
        0.084f,
        45, 142, 37
    );

    drawBroadLeaf(
        0.326f,
        -0.884f,
        110.0f,
        0.250f,
        0.082f,
        39, 129, 34
    );

    drawBroadLeaf(
        0.326f,
        -0.884f,
        140.0f,
        0.228f,
        0.077f,
        34, 119, 32
    );
}


//forest floor

void drawForestFloor()
{
    glColor3f(
        42.0f / 255.0f,
        117.0f / 255.0f,
        25.0f / 255.0f
    );

    glBegin(GL_POLYGON);

    glVertex2f(-0.615f, -1.0f);
    glVertex2f(0.602f, -1.0f);

    glVertex2f(0.504f, -0.861f);
    glVertex2f(0.105f, -0.831f);
    glVertex2f(-0.259f, -0.854f);
    glVertex2f(-0.501f, -0.884f);

    glEnd();


    glColor3f(
        24.0f / 255.0f,
        91.0f / 255.0f,
        38.0f / 255.0f
    );

    drawEllipse(
        -0.250f,
        -0.921f,
        0.264f,
        0.053f
    );

    drawEllipse(
        0.235f,
        -0.938f,
        0.293f,
        0.050f
    );

    drawEllipse(
        0.611f,
        -0.943f,
        0.271f,
        0.053f
    );
}

//sunset darkness animations

float getSunsetDarkness()
{
    float sunY =
        0.354f + sunOffset;

//daytime

    if (sunY >= 0.158f)
    {
        return 0.0f;
    }

//sunset start

    if (sunY >= -0.109f)
    {
        float amount =
            (0.158f - sunY) / 0.267f;

        return amount * 0.18f;
    }


   //darkness start grudally

    if (sunY >= -0.376f)
    {
        float amount =
            (-0.109f - sunY) / 0.267f;

        return 0.18f +
               amount * 0.25f;
    }

//full darkness

    if (sunY >= -0.643f)
    {
        float amount =
            (-0.376f - sunY) / 0.267f;

        return 0.43f +
               amount * 0.30f;
    }


    float amount =
        (-0.643f - sunY) / 0.160f;

    if (amount > 1.0f)
    {
        amount = 1.0f;
    }

    return 0.73f +
           amount * 0.22f;
}


//cloud shawdow

float getCloudDarkness()
{
    float sunX = 0.04f;

    float sunY =
        0.354f + sunOffset;


    float darkness1 = 0.0f;
    float darkness2 = 0.0f;


//clouds one

    float cloud1X =
        -0.388f +
        cloud1Offset +
        0.185f;

    float cloud1Y =
        0.247f +
        0.098f;


    float dx1 =
        cloud1X - sunX;

    float dy1 =
        cloud1Y - sunY;


    float distance1 =
        sqrt(
            dx1 * dx1 +
            dy1 * dy1
        );


    if (distance1 < 0.513f)
    {
        float amount =
            (0.513f - distance1)
            / 0.513f;

        darkness1 =
            amount * 0.18f;
    }
//cloud two

    float cloud2X =
        0.292f +
        cloud2Offset +
        0.151f;

    float cloud2Y =
        0.675f +
        0.080f;


    float dx2 =
        cloud2X - sunX;

    float dy2 =
        cloud2Y - sunY;


    float distance2 =
        sqrt(
            dx2 * dx2 +
            dy2 * dy2
        );


    if (distance2 < 0.513f)
    {
        float amount =
            (0.513f - distance2)
            / 0.513f;

        darkness2 =
            amount * 0.15f;
    }


    float totalDarkness =
        darkness1 +
        darkness2;


    if (totalDarkness > 0.22f)
    {
        totalDarkness = 0.22f;
    }


    return totalDarkness;
}

//dark overlay

void drawDarkOverlay()
{
    float sunsetDarkness =
        getSunsetDarkness();

    float cloudDarkness =
        getCloudDarkness();


    float totalDarkness =
        sunsetDarkness +
        cloudDarkness;


    if (totalDarkness > 0.95f)
    {
        totalDarkness = 0.95f;
    }


    if (totalDarkness <= 0.0f)
    {
        return;
    }


    // Enable transparency

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );


    glColor4f(
        0.0f,
        0.0f,
        0.0f,
        totalDarkness
    );


    glBegin(GL_QUADS);

    glVertex2f(
        -1.0f,
        -1.0f
    );

    glVertex2f(
        1.0f,
        -1.0f
    );

    glVertex2f(
        1.0f,
        1.0f
    );

    glVertex2f(
        -1.0f,
        1.0f
    );

    glEnd();


    glDisable(GL_BLEND);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    // SKY
    drawSky();
    // SUN
    drawMovingSun();
    // CLOUDS
    drawClouds();
    // MOUNTAINS
    drawMountains();
    // BACK BUSHES
    drawBushRow(
        -0.305f,
        0.074f,
        28,
        119,
        66,
        0.111f,
        0.014f
    );

    drawBushRow(
        -0.439f,
        0.103f,
        7,
        91,
        54,
        0.150f,
        0.0f
    );

    drawBushRow(
        -0.608f,
        0.125f,
        3,
        77,
        48,
        0.185f,
        0.064f
    );


    // LARGE TREE
    drawLargeLeftTree();
    // PALM TREE
    drawPalmTree();
    // FOREGROUND BUSH

    drawBushRow(
        -0.777f,
        0.150f,
        3,
        73,
        44,
        0.214f,
        0.0f
    );

    // FOREST FLOOR
    drawForestFloor();
    // LEFT PLANTS
    drawLeftForegroundPlants();

    // RIGHT PLANTS

    drawRightForegroundPlants();
    // DARKNESS EFFECT
    drawDarkOverlay();
    glutSwapBuffers();
}
//time updaate

void update(int value)
{
    if (!paused)
    {
    //cloud move right

        cloud1Offset += 0.00114f;

        if (cloud1Offset > 2.14f)
        {
            cloud1Offset = -0.855f;
        }

//cloud two move left

        cloud2Offset -= 0.00064f;

        if (cloud2Offset < -1.711f)
        {
            cloud2Offset = 0.713f;
        }
//sunset

        sunOffset -= 0.000802f;

        if (sunOffset < -1.159f)
        {
            sunOffset = 0.0f;
        }
    }

    // Redraw scene

    glutPostRedisplay();

    // Call update again after 16 ms

    glutTimerFunc(
        16,
        update,
        0
    );
}


//reshape
void reshape(
    int width,
    int height)
{
    float targetRatio =
        1402.0f / 1122.0f;

    float windowRatio =
        (float)width /
        (float)height;

    if (windowRatio > targetRatio)
    {
        int viewWidth =
            (int)(
                height *
                targetRatio
            );

        glViewport(
            (width - viewWidth) / 2,
            0,
            viewWidth,
            height
        );
    }

    else
    {
        int viewHeight =
            (int)(
                width /
                targetRatio
            );

        glViewport(
            0,
            (height - viewHeight) / 2,
            width,
            viewHeight
        );
    }


    // Projection matrix

    glMatrixMode(
        GL_PROJECTION
    );

    glLoadIdentity();

//normalize coordinate

    gluOrtho2D(
        -1.0f,
        1.0f,
        -1.0f,
        1.0f
    );
// Model view matrix

    glMatrixMode(
        GL_MODELVIEW
    );

    glLoadIdentity();
}
//keyboard

void keyboard(
    unsigned char key,
    int,
    int)
{
    //reset

    if (
        key == 'r' ||
        key == 'R'
    )
    {
        cloud1Offset = 0.0f;
        cloud2Offset = 0.0f;
        sunOffset = 0.0f;

        paused = false;
    }


  //pause

    else if (key == ' ')
    {
        paused = !paused;
    }
//exits

    else if (key == 27)
    {
        glutDestroyWindow(
            glutGetWindow()
        );
    }
}
//initilizations

void init()
{
    // Background color

    glClearColor(
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );


    // Smooth shading

    glShadeModel(
        GL_SMOOTH
    );
}


int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB);
    glutInitWindowSize(1000,700);
    glutInitWindowPosition(60,40);
    glutCreateWindow("SRLeon -sunset");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16,update,0);
    glutMainLoop();
    return 0;
}

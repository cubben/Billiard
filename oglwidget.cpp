#include "oglwidget.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <QTimer>

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    rotx = -60;
    roty = 0;
    rotz = 0;
    zoom = 10;
    dx = 0;
    dz = 0;
    kugelx = 0;
    kugelz = 0;
    frames = 16;
    duration = 1;
    einfallswinkel = 0;
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));
    animstep = 0;
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::stepAnimation()
{
    animstep++;    // Increase animation steps
    update();      // Trigger redraw of scene with paintGL
}
void OGLWidget::setRotX(int newrx)
{
    rotx = newrx;
    //std::cout << "xrot: " << rotx << std::endl;
    update();
}

void OGLWidget::setRotY(int newry)
{
    roty = newry;
    //std::cout << "yrot: " << roty << std::endl;
    update();
}

void OGLWidget::setRotZ(int newrz)
{
    rotz = newrz;
    //std::cout << "zrot: " << rotz << std::endl;
    update();
}

void OGLWidget::setZoom(int newzoom)
{
    zoom = newzoom;
    update();
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // For wireframe replace GL_FILL with GL_LINE
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void OGLWidget::checkTableEdge(float x, float z){
    //Kugel nicht ausserhalb des Randes bewegen lassen
    //Wand rechts;
    if(x > 4-0.5){
        dx = dx * (-1);
    }
    //Wand links
    if(x < -4+0.5){
        dx = dx * (-1);
    }
    //Wand oben
    if(z > 8-0.5){

        dz = dz * (-1);
    }

    //Wand unten
    if(z < -8+0.5){
        dz = dz * (-1);
    }
}

void OGLWidget::createWhiteBall(float x,float z){
    //Weisse Kugel
    kWhite.drawKugel(0.3, x, 0.3, z, 1.0,1.0,1.0, true);
}

void OGLWidget::createBalls(){
    float frontZ = 3.5;
    float radius = 0.3;
    int row = 1;
    int column = 1;

    float colorArray[8][3];
    /* 0 Schwarz
    * 1 Gelb
    * 2 Dunkel Rot
    * 3 Hell Rot
    * 4 Grün
    * 5 Blau
    * 6 Lila
    * 7 Orange
    */
    /*  colorArray[0][0] = 0.0;
   colorArray[0][1] = 0.0;
   colorArray[0][2] = 0.0;

   colorArray[1][0] = 0.8;
   colorArray[1][1] = 0.8;
   colorArray[1][2] = 0.0;

   colorArray[2][0] = 0.3;
   colorArray[2][1] = 0.0;
   colorArray[2][2] = 0.0;

   colorArray[3][0] = 0.8;
   colorArray[3][1] = 0.0;
   colorArray[3][2] = 0.0;

   colorArray[4][0] = 0.0;
   colorArray[4][1] = 0.2;
   colorArray[4][2] = 0.0;

   colorArray[5][0] = 0.0;
   colorArray[5][1] = 0.0;
   colorArray[5][2] = 0.4;

   colorArray[6][0] = 0.1;
   colorArray[6][1] = 0.03;
   colorArray[6][2] = 0.2;

   colorArray[7][0] = 0.25;
   colorArray[7][1] = 0.15;
   colorArray[7][2] = 0.0;

   int color = 0;
   int columnCounter = 0;
   int solid = 0;
   bool solidArr[15] = {true, false, false, true, true, true, false, true, false, false, true, false, false, true, false};
   float transx = -0.3;
   int columnArr[15] = {0, 1, 1, 2, 0, 2, 3, 1, 1, 3, 4, 2, 0, 2, 4};
   int colorSort[15] = {1, 3, 4, 2, 0, 7, 7, 6, 4, 1, 5, 2, 3, 3, 6};

   for(int i = 0; i < 1; i++){
       for(int j = 0; j <= i; j++){
           int half = (i+1)/2;

           if(j < half){
               transx = -0.3;
           }
           else{
               transx = 0.3;
           }

           k.drawKugel(radius, transx*columnArr[columnCounter], radius, frontZ + radius*2*i, colorArray[colorSort[color]][0],colorArray[color][1],colorArray[color][2], solidArr[solid]);
           color++;
           solid++;
           columnCounter++;
       }
   }
*/
    //gelb-volle
    balls[0].drawKugel(radius, 0, radius, frontZ, 0.8,0.8,0.0, true);
    //blaue-halbe
    balls[1].drawKugel(radius, -0.3*column, radius, frontZ + (radius*2*row), 0.0, 0.0,6.0, false);
    //hell-rot-halbe
    balls[2].drawKugel(radius, 0.3*column, radius, frontZ + (radius*2*row), 0.8, 0.0, 0.0, false);
    row = 2;
    column = 2;
    //rot-voll
    balls[3].drawKugel(radius, -0.3*column, radius, frontZ + (radius*2*row), 0.5, 0.0, 0.0, true);
    //schwarz-voll
    balls[4].drawKugel(radius, 0, radius, frontZ + (radius*2*row), 0.0, 0.0, 0.0, true);
    //orange-voll
    balls[5].drawKugel(radius, 0.3*column, radius, frontZ + (radius*2*row), 0.25, 0.15, 0.0, true);
    row = 3;
    column = 3;
    //orange-halb
    balls[6].drawKugel(radius, -0.3*column, radius, frontZ + (radius*2*row), 0.25, 0.15, 0.0, false);
    //lila-voll
    balls[7].drawKugel(radius, -0.3*(column-2), radius, frontZ + (radius*2*row), 0.1, 0.03, 0.2, true);
    //grün-halb
    balls[8].drawKugel(radius, 0.3*(column-2), radius, frontZ + (radius*2*row), 0.0, 0.2, 0.0, false);
    //gelb-halb
    balls[9].drawKugel(radius, 0.3*column, radius, frontZ + (radius*2*row), 0.8, 0.8, 0.0, false);
    row = 4;
    column = 4;
    //blau-voll
    balls[10].drawKugel(radius, -0.3*column, radius, frontZ + (radius*2*row), 0.0, 0.0, 0.4, true);
    //grün-voll
    balls[11].drawKugel(radius, -0.3*(column-2), radius, frontZ + (radius*2*row), 0.0, 0.2, 0.0, false);
    //rot-halb
    balls[12].drawKugel(radius, 0, radius, frontZ + (radius*2*row), 0.5, 0.0, 0.0, false);
    //orange-voll
    balls[13].drawKugel(radius, 0.3*(column-2), radius, frontZ + (radius*2*row), 0.25, 0.15, 0.0, true);
    //lila-halb
    balls[14].drawKugel(radius, 0.3*(column), radius, frontZ + (radius*2*row), 0.1, 0.03, 0.2, false);

}

void OGLWidget::checkCollision(float& x, float& z, float dx, float dz){
    bool collision = false;
    float diffx = 0;
    float diffz = 0;

    for(int i = 0; i < 15; i++){
        if(x+dx+0.3 >= balls[i].lastx-0.3 && x+dx-0.3 <= balls[i].lastx+0.3){
           if(x > balls[i].lastx){
             diffx = x - balls[i].lastx;
           }
           else{
               diffx = balls[i].lastx - x;
           }

            if(z+dz+0.3 >= balls[i].lastz-0.3 && z+dz-0.3 <= balls[i].lastz+0.3){
                if(z > balls[i].lastz){
                 diffz = z - balls[i].lastz;
                }
                else{
                    diffz = balls[i].lastz - z;
                }
                collision = true;
            }
        }
        if(collision == true){
            std::cout << "collission truee" << std::endl;
            animtimer->stop();
            animstep = 0;
            break;
        }
            x += dx;
            z += dz;

    }
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glOrtho(-10.0,10.0,-10.0,10.0,1,10);
    glLoadIdentity();

    // Apply rotation angles
    glRotatef(rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    // Apply scaling
    float scale = zoom/100.0;
    glScalef( scale, scale, scale ); // Scale along all axis
    glShadeModel(GL_FLAT);

    t.drawTable(0.0,0.1,0.0);
    //neue bewegungskoordinate delta x/z mal dem animationsschritt
    float z = kWhite.lastz;
    float x = kWhite.lastx;
    checkCollision(x,z, dx, dz);
    checkTableEdge(x,z);
    createWhiteBall(x,z);
    createBalls();

    //Letzen kugel koordinaten speichern
    //kugelx = x;
    //kugelz = z;
    glLoadIdentity();

    if(animstep >= (duration  / frames)){
        animtimer->stop();
        std::cout << "animtimer stop frames: " << animstep << std::endl;
        animstep = 0;
        dx = 0;
        dz = 0;

    }
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    // Upon mouse pressed, we store the current position...
    lastpos = event->pos();
}

void OGLWidget::mouseReleaseEvent(QMouseEvent *event){
    double mouseDeltaX = event->x() - lastpos.x();
    double mouseDeltaZ = event->y() - lastpos.y();

    //Geschwindikeit
    if(mouseDeltaX == 0 && mouseDeltaZ == 0){
        dx = 0;
        dz = 0;
        duration = 0;
        //Wenn mouse klick auf der ein und derselben stelle ist, kugel zur Ausgangsposition bewegen
        kWhite.lastx = 0;
        kWhite.lastz = -3;
    }else{
        float v = mouseDeltaZ * 0.001; //Einheit pro sekunde
        std::cout << "v: " << v << std::endl;

        double px = pow(mouseDeltaX,2);
        double pz = pow(mouseDeltaZ,2);
        double s = sqrt(px + pz);
        std::cout << "s: " << s << std::endl;
        //time
        duration = s/v;
        std::cout << "d: " << duration << std::endl;

        //teil strecke
        dx =  mouseDeltaX / duration * (-1);
        dz =  mouseDeltaZ / duration;

        //float pi = 3.1415926;
        //einfallswinkel = 90 - sin(dx*pi/180) * s;

        std::cout << "dx: " << dx << std::endl;
        std::cout << "dz: " << dz << std::endl;
    }
    animtimer->start(frames);
    std::cout << "animtimer start " << std::endl;

}

void OGLWidget::keyPressEvent(QKeyEvent *event)
{
    // This is the delta we want to use for rotating
    const int keyDelta = 10;

    switch(event->key())
    {
    // Up/Down: Rotating around x axis
    case Qt::Key_Up:
        emit changeRotation( keyDelta, 0, 0 );
        break;
    case Qt::Key_Down:
        emit changeRotation( -keyDelta, 0, 0 );
        break;

        // Left/Right: Rotating around y axis
    case Qt::Key_Left:
        emit changeRotation( 0, keyDelta, 0 );
        break;
    case Qt::Key_Right:
        emit changeRotation( 0, -keyDelta, 0 );
        break;

        // Pg up/down: Rotating around z axis
    case Qt::Key_PageUp:
        emit changeRotation( 0, 0, keyDelta );
        break;
    case Qt::Key_PageDown:
        emit changeRotation( 0, 0, -keyDelta );
        break;

        // All other will be ignored
    default:
        break;
    }
}

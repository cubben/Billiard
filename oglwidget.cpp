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

    t.drawTable(0.0,1.0,0.0);

    //Wenn mouse klick auf der ein und derselben stelle ist, kugel zur Ausgangsposition bewegen
    if(dx == 0 && dz == 0){
        kugelx = 0;
        kugelz = -3;
    }

    //neue bewegungskoordinate delta x/z mal dem animationsschritt
    float z = kugelz + dz;
    float x = kugelx + dx;
    checkTableEdge(x,z);

    //Weisse Kugel
    k.drawKugel(0.3, x, 0.3, z, 1.0,1.0,1.0, true);

    //gelb-volle
    k.drawKugel(0.3, 0, 0.3, 3.5, 0.8,0.8,0.0, true);
    //blaue-volle
    k.drawKugel(0.3, -0.3, 0.3, 4.1, 0.0, 0.0,6.0, true);
    //rot-volle
    k.drawKugel(0.3, 0.3, 0.3, 4.1, 0.6, 0.0, 0.0, true);

    //Letzen kugel koordinaten speichern
    kugelx = x;
    kugelz = z;
    glLoadIdentity();

    if(animstep >= (duration  / frames)){
        animtimer->stop();
        std::cout << "animtimer stop frames: " << animstep << std::endl;
        animstep = 0;
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

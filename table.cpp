#include "table.h"

table::table()
{
}

void table::drawBoden(float red, float green, float blue){
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glVertex3f(4, 0, -8);
    glVertex3f( -4, 0, -8);
    glVertex3f( -4,  0, 8);
    glVertex3f( 4,  0, 8);
    glEnd();
}

void table::seiteAB(float red, float green, float blue){
    //Left
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glVertex3f(4, 0, -8);
    glVertex3f( 4, 0.5, -8);
    glVertex3f( 4,  0.5, 8.5);
    glVertex3f(4,  0, 8.5);
    glEnd();

    //Top
    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(4, 0.5, -8);
    glVertex3f( 4.5, 0.5, -8);
    glVertex3f( 4.5,  0.5, 8.5);
    glVertex3f(4,  0.5, 8.5);
    glEnd();
    //Right
    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(4.5, 0.0, -8.5);
    glVertex3f( 4.5, 0.5, -8.5);
    glVertex3f( 4.5,  0.5, 8.5);
    glVertex3f(4.5,  0.0, 8.5);
    glEnd();
    //Bottom
    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(4, 0.0, -8);
    glVertex3f( 4.5, 0.0, -8);
    glVertex3f( 4.5,  0.0, 8.5);
    glVertex3f(4,  0.0, 8.5);
    glEnd();

}

void table::seiteBC(float red, float green, float blue){
    glBegin(GL_QUADS);
    glColor3f(red, green,blue);
    glVertex3f(4.5, 0, -8);
    glVertex3f(4.5, 0.5, -8);
    glVertex3f(-4, 0.5,-8);
    glVertex3f(-4,  0, -8);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(4.5, 0.5, -8);
    glVertex3f(4.5, 0.5, -8.5);
    glVertex3f(-4, 0.5,-8.5);
    glVertex3f(-4,  0.5, -8);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(4.5, 0, -8.5);
    glVertex3f(4.5, 0.5, -8.5);
    glVertex3f(-4.5, 0.5,-8.5);
    glVertex3f(-4.5,  0, -8.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(4.5, 0, -8);
    glVertex3f(4.5, 0, -8.5);
    glVertex3f(-4, 0,-8.5);
    glVertex3f(-4,  0, -8);
    glEnd();

}

void table::seiteCD(float red, float green, float blue){
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glVertex3f(-4, 0, -8.5);
    glVertex3f( -4, 0.5, -8.5);
    glVertex3f( -4,  0.5, 8);
    glVertex3f( -4,  0, 8);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(-4, 0.5, -8.5);
    glVertex3f( -4.5, 0.5, -8.5);
    glVertex3f( -4.5,  0.5, 8);
    glVertex3f( -4,  0.5, 8);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(-4.5, 0, -8.5);
    glVertex3f( -4.5, 0.5, -8.5);
    glVertex3f( -4.5,  0.5, 8);
    glVertex3f( -4.5,  0, 8);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(-4, 0, -8.5);
    glVertex3f( -4.5, 0, -8.5);
    glVertex3f( -4.5,  0, 8);
    glVertex3f( -4,  0, 8);
    glEnd();
}

void table::seiteAD(float red, float green, float blue){
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glVertex3f(-4.5, 0, 8);
    glVertex3f( -4.5, 0.5, 8);
    glVertex3f( 4,  0.5, 8);
    glVertex3f( 4,  0, 8);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(-4.5, 0.5, 8);
    glVertex3f( -4.5, 0.5, 8.5);
    glVertex3f( 4,  0.5, 8.5);
    glVertex3f( 4,  0.5, 8);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(-4.5, 0, 8.5);
    glVertex3f( -4.5, 0.5, 8.5);
    glVertex3f( 4,  0.5, 8.5);
    glVertex3f( 4,  0, 8.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0545, 0.0352, 0.0168);
    glVertex3f(-4.5, 0, 8);
    glVertex3f( -4.5, 0, 8.5);
    glVertex3f( 4,  0, 8.5);
    glVertex3f( 4,  0, 8);
    glEnd();
}

void table::drawTable(float red, float green, float blue){

    drawBoden(red,green,blue);
    seiteAB(red,green,blue);
    seiteBC(red,green,blue);
    seiteCD(red,green,blue);
    seiteAD(red,green,blue);

}


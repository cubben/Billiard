#include "kugel.h"
#include <math.h>
kugel::kugel()
{
}
    void kugel::drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta, float red, float green, float blue){
    glBegin(GL_QUADS);
        glColor4f(red, green, blue, 1.0);

        float pi = 3.1415926;
        float breite = 10*pi/180;


        float x1 = radius * cos(alpha) * cos(beta);
        float y1 = radius * sin(beta);
        float z1 = radius * (-sin(alpha)) * cos(beta);

        float x2 = radius * cos(alpha+breite) * cos(beta);
        float y2 = radius * sin(beta);
        float z2 = radius * (-sin(alpha+breite)) * cos(beta);

        float x3 = radius * cos(alpha+breite) * cos(beta+breite);
        float y3 = radius * sin(beta+breite);
        float z3 = radius * (-sin(alpha+breite)) * cos(beta+breite);

        float x4 = radius * cos(alpha) * cos(beta+breite);
        float y4 = radius * sin(beta+breite);
        float z4 = radius * (-sin(alpha)) * cos(beta+breite);

        glVertex3f(dx + x1, dy + y1, dz +z1);
        glVertex3f(dx + x2, dy + y2, dz +z2);
        glVertex3f(dx + x3, dy + y3, dz +z3);
        glVertex3f(dx + x4, dy + y4, dz +z4);

        glEnd();

    }

    void kugel::drawKugel(float radius, float x, float y, float z, float red, float green, float blue, bool solid){

            double alpha = 0;
            double beta = -90;
            float pi = 3.1415926;

            float r = red;
            float g = green;
            float b = blue;

            //beta = z achse, alpha = y achse
            while(beta <=90){
                   alpha = 0.0;

                if(!solid){
                   if(beta < -30 || beta >=30){
                       r = 1.0;
                       g = 1.0;
                       b = 1.0;
                   }
                   else{
                        r = red;
                        g = green;
                        b = blue;
                   }
                }
                while(alpha <= 360){

                    drawQuad(radius, x, y, z, alpha*pi/180, beta*pi/180, r, g, b);
                    alpha+= 10;
                }

                beta += 10;

            }

      }

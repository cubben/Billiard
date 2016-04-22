#include "kugel.h"
#include <math.h>
kugel::kugel()
{
}
    void kugel::drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta, float red, float green, float blue){
    glBegin(GL_QUADS);
        glColor4f(red, green, blue, 1.0);

        float x1 = radius * cos(alpha) * cos(beta);
        float y1 = radius * sin(beta);
        float z1 = radius * sin(alpha) * cos(beta);

        float x2 = radius * cos(alpha+0.1) * cos(beta);
        float y2 = radius * sin(beta);
        float z2 = radius * sin(alpha+0.1) * cos(beta);

        float x3 = radius * cos(alpha+0.1) * cos(beta+0.1);
        float y3 = radius * sin(beta+0.1);
        float z3 = radius * sin(alpha+0.1) * cos(beta+0.1);

        float x4 = radius * cos(alpha) * cos(beta);
        float y4 = radius * sin(beta+0.1);
        float z4 = radius * sin(alpha) * cos(beta+0.1);


        glVertex3f(dx + x1, dy + y1, dz +z1);
        glVertex3f(dx + x2, dy + y2, dz +z2);
        glVertex3f(dx + x3, dy + y3, dz +z3);
        glVertex3f(dx + x4, dy + y4, dz +z4);

        glEnd();

    }

    void kugel::drawKugel(float radius, float x, float y, float z, float red, float green, float blue){

            double alpha = 10.0;
            double beta = 0;
            float pi = 3.1415926;
            int i = 0;
            int j = 0;

            while(j <=72){
                beta += 5;
                i=0;
                 while(i <= 72){
                    drawQuad(radius, x, y, z, alpha*pi/180, beta*pi/180, red, green, blue);
                    alpha+= 5;
                    i++;
                }
                j++;
            }

      }

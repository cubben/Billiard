#ifndef KUGEL_H
#define KUGEL_H

#include <QWidget>
#include <QOpenGLWidget>

class kugel
{
public:
    kugel();
    void drawKugel(float radius, float x, float y, float z, float red, float green, float blue);

private:
    void drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta, float red, float green, float blue);

};

#endif // KUGEL_H

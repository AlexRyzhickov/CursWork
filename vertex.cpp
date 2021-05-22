#include "vertex.h"
#include <QtMath>

Vertex::Vertex(float x,float y, float z, double angle, float red, float green, float blue, float alpha)
{
    this->x = x * cos(angle) - z * sin(angle);
    this->y = y;
    this->z = x * sin(angle) + z * cos(angle);
    this->red = red;
    this->blue = blue;
    this->green = green;
    this->alpha = alpha;
}



float Vertex::getBlue() const
{
    return blue;
}

void Vertex::setBlue(int value)
{
    blue = value;
}

float Vertex::getAlpha() const
{
    return alpha;
}

void Vertex::setAlpha(int value)
{
    alpha = value;
}

float Vertex::getGreen() const
{
    return green;
}

void Vertex::setGreen(int value)
{
    green = value;
}

float Vertex::getRed() const
{
    return red;
}

void Vertex::setRed(int value)
{
    red = value;
}

float Vertex::getY() const
{
    return y;
}

void Vertex::setY(double value)
{
    y = value;
}

float Vertex::getX() const
{
    return x;
}

void Vertex::setX(double value)
{
    x = value;
}

float Vertex::getZ() const
{
    return z;
}

void Vertex::setZ(float value)
{
    z = value;
}

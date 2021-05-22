#ifndef VERTEX_H
#define VERTEX_H


class Vertex
{
public:
    Vertex(float x,float y, float z, double angle, float red, float green, float blue, float alpha);
    float x;
    float y;
    float z;
    float red;
    float blue;
    float green;
    float alpha;

    float getX() const;
    void setX(double value);
    float getY() const;
    void setY(double value);
    float getZ() const;
    void setZ(float value);
    float getRed() const;
    void setRed(int value);
    float getGreen() const;
    void setGreen(int value);
    float getBlue() const;
    void setBlue(int value);
    float getAlpha() const;
    void setAlpha(int value);


};

#endif // VERTEX_H

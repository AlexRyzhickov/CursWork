#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vertex.h>

class Triangle
{
public:
    Triangle(Vertex *vertex_one, Vertex *vertex_two,Vertex *vertex_three);
    Vertex *vertex_one = nullptr;
    Vertex *vertex_two = nullptr;
    Vertex *vertex_three = nullptr;
    Vertex *getVertex_one() const;
    Vertex *getVertex_two() const;
    Vertex *getVertex_three() const;
};

#endif // TRIANGLE_H

#include "triangle.h"

Triangle::Triangle(Vertex *vertex_one, Vertex *vertex_two,Vertex *vertex_three)
{
    this->vertex_one = vertex_one;
    this->vertex_two = vertex_two;
    this->vertex_three = vertex_three;
}

Vertex *Triangle::getVertex_three() const
{
    return vertex_three;
}

Vertex *Triangle::getVertex_two() const
{
    return vertex_two;
}

Vertex *Triangle::getVertex_one() const
{
    return vertex_one;
}

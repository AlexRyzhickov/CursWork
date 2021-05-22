#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>



class Material
{
public:
    Material();
    QVector3D diffuse_color;
    QVector3D ambient_light;
    QVector3D specular_color;
    float shininess;
    void setEmeraldMaterial();
    void setJadeMaterial();
    void setObsidianMaterial();
    void setPearlMaterial();
    void setRubyMaterial();
    void setTurquoiseMaterial();
};

#endif // MATERIAL_H

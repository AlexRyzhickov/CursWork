#include "material.h"

Material::Material()
{
    setEmeraldMaterial();
}

void Material::setEmeraldMaterial()
{
    this->diffuse_color = QVector3D(0.07568,0.61424,0.07568);
    this->ambient_light = QVector3D(0.0215,0.1745,0.0215);
    this->specular_color = QVector3D(0.633,0.727811, 0.633);
    this->shininess = 0.6;
}

void Material::setJadeMaterial()
{
    this->diffuse_color = QVector3D(0.54,0.89,0.63);
    this->ambient_light = QVector3D(0.135,0.2225,0.1575);
    this->specular_color = QVector3D(0.316228,0.316228,0.316228);
    this->shininess = 0.1;
}

void Material::setObsidianMaterial()
{
    this->diffuse_color = QVector3D(0.18275,0.17,0.22525);
    this->ambient_light = QVector3D(0.05375	,0.05,0.06625);
    this->specular_color = QVector3D(0.332741,0.328634,0.346435);
    this->shininess = 0.3;
}

void Material::setPearlMaterial()
{
    this->diffuse_color = QVector3D(1,0.829,0.829);
    this->ambient_light = QVector3D(0.25,0.20725,0.20725);
    this->specular_color = QVector3D(0.296648,0.296648	,0.296648);
    this->shininess = 0.088;
}

void Material::setRubyMaterial()
{
    this->diffuse_color = QVector3D(0.61424,0.04136,0.04136);
    this->ambient_light = QVector3D(0.1745,0.01175,0.01175);
    this->specular_color = QVector3D(0.727811,0.626959,0.626959);
    this->shininess = 0.6;
}

void Material::setTurquoiseMaterial()
{
    this->diffuse_color = QVector3D(0.396,0.74151,0.69102);
    this->ambient_light = QVector3D(0.1	,0.18725,0.1745);
    this->specular_color = QVector3D(0.297254,0.30829,0.306678);
    this->shininess = 0.1;
}

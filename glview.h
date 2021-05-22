#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <vertex.h>
#include <QList>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <triangle.h>
#include <material.h>
#include <string>
#include <vector>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

struct glView : QGLWidget, protected QOpenGLFunctions
{
public:
  glView(QWidget *parent);
  void initializeGL() override;
  void resizeGL(int w, int h)override;
  void paintGL()override;
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);
  void mouseReleaseEvent(QMouseEvent*);

private:
  void init_fdata();
  void init_vertex();
  void parse_line(const std::string &line);
  void chk_vertex_vec();

  GLfloat x_pos = 0, y_pos = 0;
  GLfloat angle_x = 0, angle_y = 0;

  std::string fdata;
  struct coord{
      float x,y,z;
  };
  std::vector<coord> vertex_vec;
  std::vector<int> vertex_ind;
  std::vector<coord> nlight_vec;
  std::vector<int> nlight_ind;
private:
  QTimer mpTimer;

  GLint m_posAttr = 0;
  GLint m_colAttr = 0;
  GLint m_matrixUniform = 0;
  GLint v_matrixUniform = 0;
  GLint p_matrixUniform = 0;
  GLint intensityUniform = 0;
  GLint lightColorUniform = 0;
  GLint view_position = 0;
  GLint diffuse_color = 0;
  GLint ambient_light = 0;
  GLint specular_color = 0;
  GLint shininess = 0;
  GLint light_positionUniform = 0;
  QOpenGLShaderProgram *m_program = nullptr;
  int m_frame = 0;

public:
  int split_step = 3;
  float radius_high_face = 0.4f;
  float radius_low_face = 0.9f;
  float y_high_face = 0.4f;
  float y_low_face = -0.4f;
  float rotation_x = 0.0f;
  float rotation_y = 0.0f;
  float rotation_z = 0.0f;
  float translate_x = 0.0f;
  float translate_y = 0.0f;
  float translate_z = 0.0f;
  float scale_x = 1.0f;
  float scale_y = 1.0f;
  float scale_z = 1.0f;
  float camera_rotation_x = 0.0f;
  float camera_rotation_y = 0.0f;
  float camera_rotation_z = 0.0f;
  float camera_translate_x = 0.0f;
  float camera_translate_y = 0.0f;
  float camera_translate_z = 0.0f;
  bool isPerspectiveOrOrtho = true;
  bool isDrawFill = false;
  float intensity = 1;
  QColor *color = nullptr;
  Material *material = nullptr;
  QVector3D *light_position = nullptr;
public slots:  

};

#endif // GLVIEW_H

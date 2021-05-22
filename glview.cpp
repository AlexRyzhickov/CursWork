#include "glview.h"
#include "QDebug"
#include <QList>
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
#include <material.h>
#include <fstream>
#include <stdlib.h>

static const char *vertexShaderSource = R"(
    #version 330
    layout (location = 0) in  highp vec4 posAttr;
    uniform highp mat4 view_matrix;
    uniform highp mat4 proj_matrix;
    uniform highp mat4 matrix;
    void main() {
       gl_Position = proj_matrix * view_matrix * matrix * posAttr;
    }
)";

static const char *fragmentShaderSource = R"(
            #version 330 core
            out vec4 fragment_color;
            uniform vec4 color;
            void main() {
                fragment_color = color;
            }
)";

glView::glView(QWidget *parent)
{
    init_fdata();
    color = new QColor(255,255,255,255);
    light_position = new QVector3D(15.0, 30.0, 15.0);
    connect(&mpTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    mpTimer.start(33);
}

void glView::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(127/255,118/255,121/255,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);



    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
    v_matrixUniform = m_program->uniformLocation("view_matrix");
    Q_ASSERT(v_matrixUniform != -1);
    p_matrixUniform = m_program->uniformLocation("proj_matrix");
    Q_ASSERT(p_matrixUniform != -1);
    lightColorUniform = m_program->uniformLocation("color");
    Q_ASSERT(lightColorUniform != -1);

}

void glView::resizeGL(int w, int h)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(-60,60,-60,60,-60,60);


}

void glView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat light1_diffuse[] = {1.0, 1.0, 1.0};

    GLfloat light1_position[] = {light_position->x(),light_position->y(),light_position->z(), 1.0};

    if(isDrawFill){
        glEnable(GL_LIGHT0);
    }else{
        glDisable(GL_LIGHT0);
    }

    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glRotatef(angle_x,1,0,0);
    glRotatef(angle_y,0,1,0);

    glTranslatef(0.0, -10.0f, 0.0);

    glBegin(GL_TRIANGLES);
     glColor3f(0.7,0.7,0.7);


        for (int i=0; i< vertex_ind.size(); i++) {

            int num_pnt2 = nlight_ind.at(i) - 1;

            GLfloat x2 = nlight_vec.at(num_pnt2).x;
            GLfloat y2 = nlight_vec.at(num_pnt2).y;
            GLfloat z2 = nlight_vec.at(num_pnt2).z;

            glNormal3f(x2,y2,z2);

            int num_pnt = vertex_ind.at(i) - 1;
            GLfloat x = vertex_vec.at(num_pnt).x;
            GLfloat y = vertex_vec.at(num_pnt).y;
            GLfloat z = vertex_vec.at(num_pnt).z;

            glVertex3f(x,y,z);
        }

        for (int i=0; i< nlight_ind.size(); i++) {

        }


    glEnd();

//    glEnable(GL_DEPTH_TEST);

//    const qreal retinaScale = devicePixelRatio();
//    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 proj_matrix;
//    if(isPerspectiveOrOrtho){
//        proj_matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 3000.0f);
//    }else{
        proj_matrix.ortho(-60,60,-60,60,-60,60);
//    }


//    QMatrix4x4 view_matrix_eye;
//    view_matrix_eye.rotate(angle_x, 1, 0, 0);
//    view_matrix_eye.rotate(angle_y, 0, 1, 0);
//    view_matrix_eye.rotate(camera_rotation_z, 0, 0, 1);
//    QVector3D vector(camera_translate_x,camera_translate_y,camera_translate_z);

//    QVector3D eye = view_matrix_eye.map(vector);

//    QVector3D up(0.0f,1.0f,0.0f);

//    QVector3D center(0.0f,0.0f,0.0f);

    QMatrix4x4 view_matrix;
    view_matrix.rotate(angle_x, 1, 0, 0);
    view_matrix.rotate(angle_y, 0, 1, 0);

//    view_matrix.lookAt(eye,center,up);

    QMatrix4x4 matrix;
    m_program->setUniformValue(p_matrixUniform, proj_matrix);
    m_program->setUniformValue(v_matrixUniform, view_matrix);
    m_program->setUniformValue(m_matrixUniform, matrix);
    glUniform4f(lightColorUniform,color->red()/255,color->green()/255,color->blue()/255,1.0);

    GLfloat vertices[3];
    vertices[0] = light_position->x();
    vertices[1] = light_position->y();
    vertices[2] = light_position->z();

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);

    glEnableVertexAttribArray(m_posAttr);

    glPointSize(15);
    glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(m_colAttr);

    m_program->release();

}

void glView::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        x_pos = e->x();
        y_pos = e->y();
    }
}

void glView::mouseMoveEvent(QMouseEvent *e)
{
    angle_x = 180 * (GLfloat(e->y()) - y_pos) / width();
    angle_y = 180 * (GLfloat(e->x()) - x_pos) / height();
    updateGL();
}

void glView::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        y_pos = e->y();
        x_pos = e->x();
    }
}

void glView::init_fdata()
{
    std::ifstream ifile("C:\\Mila_curs\\Mila_curs\\model.obj");
    while(ifile.good()){
        fdata.push_back(ifile.get());
    }

    ifile.close();
    init_vertex();
    chk_vertex_vec();
}

void glView::init_vertex()
{
    std::string line;
    for (int i=0; i<fdata.size(); i++) {
        line.push_back(fdata.at(i));
        if(fdata.at(i)=='\n'){
            //qDebug() << QString::fromStdString(line);
            parse_line(line);
            line.clear();
        }
    }

}

void glView::parse_line(const std::string &line)
{
    coord curr_c;

    if(line.at(0)=='v' && line.at(1)==' '){
        QStringList list = QString::fromStdString(line).split(" ");
        curr_c.x =  list.at(1).toFloat();
        curr_c.y =  list.at(2).toFloat();
        curr_c.z =  list.at(3).toFloat();
        vertex_vec.push_back(curr_c);
        return;
    } else if (line.at(0)=='f' && line.at(1)==' '){
        QStringList list = QString::fromStdString(line).split(" ");

        QStringList list_1 = list[1].split("/");
        vertex_ind.push_back(list_1[0].toFloat());
        nlight_ind.push_back(list_1[2].toFloat());

        QStringList list_2 = list[2].split("/");   
        vertex_ind.push_back(list_2[0].toFloat());
        nlight_ind.push_back(list_2[2].toFloat());

        QStringList list_3 = list[3].split("/");
        vertex_ind.push_back(list_3[0].toFloat());
        nlight_ind.push_back(list_3[2].toFloat());

    } else if (line.at(0)=='v' && line.at(1)=='n'){
        QStringList list = QString::fromStdString(line).split(" ");
        curr_c.x =  list.at(1).toFloat();
        curr_c.y =  list.at(2).toFloat();
        curr_c.z =  list.at(3).toFloat();
        nlight_vec.push_back(curr_c);
    }
}

void glView::chk_vertex_vec()
{
//    for (int i=0; i<vertex_vec.size(); i++) {
//        qDebug() << "X = " << float(vertex_vec.at(i).x) << ", Y = " << vertex_vec.at(i).y << ", Z = " << vertex_vec.at(i).z;
//    }

//    foreach (int num, vertex_ind){
//        qDebug() << num;
//    }

//        foreach (int num, nlight_ind){
//            qDebug() << num;
//        }

//        for (int i=0; i< nlight_vec.size(); i++) {
//            qDebug() << "X = " << float(nlight_vec.at(i).x) << ", Y = " << nlight_vec.at(i).y << ", Z = " << nlight_vec.at(i).z;
//        }

}



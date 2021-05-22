#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <vertex.h>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->split_step,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->radius_high_face,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->radius_low_face,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->y_high_face,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->y_low_face,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->rotation_x,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->rotation_y,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->rotation_z,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->translation_x,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->translation_y,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->translation_z,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->scale_x,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->scale_y,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->scale_z,SIGNAL(valueChanged(double)),SLOT(changeSettings()));

  connect(ui->camera_rotate_x,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->camera_rotate_y,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->camera_rotate_z,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->camera_translate_x,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->camera_translate_y,SIGNAL(valueChanged(int)),SLOT(changeSettings()));
  connect(ui->camera_translate_z,SIGNAL(valueChanged(int)),SLOT(changeSettings()));

  connect(ui->perspective_btn,SIGNAL(toggled(bool)),SLOT(changeSettings()));
  connect(ui->fillMode,SIGNAL(stateChanged(int)),SLOT(changeSettings()));
  connect(ui->intensity,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->colorPicker,SIGNAL(clicked(bool)),SLOT(openColorPicker()));

  connect(ui->light_pos_x,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->light_pos_y,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->light_pos_z,SIGNAL(valueChanged(double)),SLOT(changeSettings()));
  connect(ui->comboBox,SIGNAL(activated(int)),SLOT(changeSettings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeSettings()
{
    ui->openGLWidget->split_step = ui->split_step->value();
    ui->openGLWidget->radius_high_face = ui->radius_high_face->value();
    ui->openGLWidget->radius_low_face = ui->radius_low_face->value();
    ui->openGLWidget->y_high_face = ui->y_high_face->value();
    ui->openGLWidget->y_low_face = ui->y_low_face->value();
    ui->openGLWidget->rotation_x = double(ui->rotation_x->value());
    ui->openGLWidget->rotation_y = double(ui->rotation_y->value());
    ui->openGLWidget->rotation_z = double(ui->rotation_z->value());
    ui->rotation_x_label->setText("Вращение по x: " + QString::number(ui->rotation_x->value(), 'g', 9));
    ui->rotation_y_label->setText("Вращение по y: " + QString::number(ui->rotation_y->value(), 'g', 9));
    ui->rotation_z_label->setText("Вращение по z: " + QString::number(ui->rotation_z->value(), 'g', 9));
    ui->openGLWidget->translate_x = double(ui->translation_x->value())/10;
    ui->openGLWidget->translate_y = double(ui->translation_y->value())/10;
    ui->openGLWidget->translate_z = double(ui->translation_z->value())/10;
    ui->translate_x_label->setText("Перененос по x: " + QString::number(double(ui->translation_x->value())/10, 'g', 9));
    ui->translate_y_label->setText("Перененос по y: " + QString::number(double(ui->translation_y->value())/10, 'g', 9));
    ui->translate_z_label->setText("Перененос по z: " + QString::number(double(ui->translation_z->value())/10, 'g', 9));
    ui->openGLWidget->scale_x = ui->scale_x->value();
    ui->openGLWidget->scale_y = ui->scale_y->value();
    ui->openGLWidget->scale_z = ui->scale_z->value();

    ui->openGLWidget->camera_rotation_x = double(ui->camera_rotate_x->value());
    ui->openGLWidget->camera_rotation_y = double(ui->camera_rotate_y->value());
    ui->openGLWidget->camera_rotation_z = double(ui->camera_rotate_z->value());
    ui->camera_rotate_x_label->setText("Вращение камеры по x: " + QString::number(ui->camera_rotate_x->value(), 'g', 9));
    ui->camera_rotate_y_label->setText("Вращение камеры по y: " + QString::number(ui->camera_rotate_y->value(), 'g', 9));
    ui->camera_rotate_z_label->setText("Вращение камеры по z: " + QString::number(ui->camera_rotate_z->value(), 'g', 9));
    ui->openGLWidget->camera_translate_x = double(ui->camera_translate_x->value())/10;
    ui->openGLWidget->camera_translate_y = double(ui->camera_translate_y->value())/10;
    ui->openGLWidget->camera_translate_z = double(ui->camera_translate_z->value())/10;
    ui->camera_translate_x_label->setText("Перененос камеры по x: " + QString::number(double(ui->camera_translate_x->value())/10, 'g', 9));
    ui->camera_translate_y_label->setText("Перененос камеры по y: " + QString::number(double(ui->camera_translate_y->value())/10, 'g', 9));
    ui->camera_translate_z_label->setText("Перененос камеры по z: " + QString::number(double(ui->camera_translate_z->value())/10, 'g', 9));

    if(ui->perspective_btn->isChecked()){
        ui->openGLWidget->isPerspectiveOrOrtho = true;
    }else{
        ui->openGLWidget->isPerspectiveOrOrtho = false;
    }

    if(ui->fillMode->isChecked()){
        ui->openGLWidget->isDrawFill = true;
    }else{
        ui->openGLWidget->isDrawFill = false;
    }

    ui->openGLWidget->intensity = ui->intensity->value();
    ui->openGLWidget->light_position->setX(ui->light_pos_x->value());
    ui->openGLWidget->light_position->setY(ui->light_pos_y->value());
    ui->openGLWidget->light_position->setZ(ui->light_pos_z->value());

    switch (ui->comboBox->currentIndex()) {
        case 0:
            ui->openGLWidget->material->setEmeraldMaterial();
            break;
        case 1:
            ui->openGLWidget->material->setJadeMaterial();
            break;
        case 2:
            ui->openGLWidget->material->setObsidianMaterial();
            break;
        case 3:
            ui->openGLWidget->material->setPearlMaterial();
            break;
        case 4:
            ui->openGLWidget->material->setRubyMaterial();
            break;
        case 5:
            ui->openGLWidget->material->setTurquoiseMaterial();
            break;
    }

}

void MainWindow::openColorPicker()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    ui->openGLWidget->color->setRgb(color.red(),color.green(),color.blue());
}


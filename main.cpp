#include "mainwindow.h"
#include <QApplication>
#include "glview.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);


//  glView *win = new glView(new QWidget);
//  win->setGeometry(0,0,800,600);
//  win->show();
  //win->showFullScreen();

  MainWindow w;
  w.show();

  return a.exec();
}

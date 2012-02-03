#include <QtGui>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QPushButton *helloWorldPB = new QPushButton("Hello World");
  helloWorldPB->show();
  return app.exec();
}

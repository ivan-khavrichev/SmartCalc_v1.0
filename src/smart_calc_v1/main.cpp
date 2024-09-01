#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "front/s21_calculator.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Calculator w;
  w.show();
  return a.exec();
}

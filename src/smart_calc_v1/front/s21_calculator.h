#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef __cplusplus
extern "C" {
#endif

#include "./../back/s21_calc.h"
#ifdef __cplusplus
}
#endif

#include <QColor>
#include <QLineEdit>
#include <QMainWindow>
#include <QWidget>

#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();

 private:
  Ui::Calculator *ui;
  std::string str_x, str, str_x_min, str_x_max, str_y_min, str_y_max;
  double value_x_min, value_x_max, value_y_min, value_y_max, step, value_x;

  QVector<double> x, y;

  QColor background_color;
  QColor axis_color;
  QColor graph_line_color;

 private slots:
  void simple_button();
  void function_button();
  void hard_button();
  void AC_button();
  void backspace_button();
  void eq_button();
  void plot_button();
  void answer_preparation();
  QLineEdit *line_focus_input();
  void stylize();
};

#endif  // MAINWINDOW_H

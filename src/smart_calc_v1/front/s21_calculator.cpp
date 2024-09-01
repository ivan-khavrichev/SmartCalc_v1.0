#include "s21_calculator.h"

#include <QPixmap>

#include "ui_s21_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);

  ui->input->setMaxLength(255);
  ui->input_x->setMaxLength(50);

  background_color = QColor(0, 0, 0, 0);
  axis_color = QColor(255, 255, 255);
  graph_line_color = QColor(241, 164, 60);

  stylize();

  QPushButton *simle_buttons[] = {
      ui->pushButton_1,         ui->pushButton_2,         ui->pushButton_3,
      ui->pushButton_4,         ui->pushButton_5,         ui->pushButton_6,
      ui->pushButton_7,         ui->pushButton_8,         ui->pushButton_9,
      ui->pushButton_0,         ui->pushButton_x,         ui->pushButton_e,
      ui->pushButton_dot,       ui->pushButton_plus,      ui->pushButton_minus,
      ui->pushButton_bracket_o, ui->pushButton_bracket_c, ui->pushButton_mod,
      ui->pushButton_pow};

  QPushButton *function_buttons[] = {ui->pushButton_ln,   ui->pushButton_log,
                                     ui->pushButton_sin,  ui->pushButton_cos,
                                     ui->pushButton_tan,  ui->pushButton_asin,
                                     ui->pushButton_acos, ui->pushButton_atan};

  QPushButton *hard_button[] = {ui->pushButton_pi, ui->pushButton_EE,
                                ui->pushButton_div, ui->pushButton_mul,
                                ui->pushButton_sqrt};

  for (QPushButton *button : simle_buttons) {
    connect(button, SIGNAL(clicked()), this, SLOT(simple_button()));
  }

  for (QPushButton *button : function_buttons) {
    connect(button, SIGNAL(clicked()), this, SLOT(function_button()));
  }

  for (QPushButton *button : hard_button) {
    connect(button, SIGNAL(clicked()), this, SLOT(hard_button()));
  }

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(AC_button()));
  connect(ui->pushButton_backspace, SIGNAL(clicked()), this,
          SLOT(backspace_button()));

  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(eq_button()));

  connect(ui->pushButton_plot, SIGNAL(clicked()), this, SLOT(plot_button()));
}

Calculator::~Calculator() { delete ui; }

void Calculator::simple_button() {
  QLineEdit *line_input = line_focus_input();
  QPushButton *button = (QPushButton *)sender();
  line_input->setText(line_input->text() + button->text());

  line_input->setFocus();
}

void Calculator::function_button() {
  QLineEdit *line_input = line_focus_input();
  QPushButton *button = (QPushButton *)sender();
  line_input->setText(line_input->text() + button->text() + "(");

  line_input->setFocus();
}

void Calculator::hard_button() {
  QLineEdit *line_input = line_focus_input();
  QPushButton *button = (QPushButton *)sender();

  QString hard_symbols[5] = {"π", "EE", "÷", "×", "√"};
  QString simle_symbols[5] = {"pi", "E", "/", "*", "sqrt("};
  for (int i = 0; i < 5; i++) {
    if (button->text() == hard_symbols[i]) {
      line_input->setText(line_input->text() + simle_symbols[i]);
    }
  }

  line_input->setFocus();
}

void Calculator::AC_button() {
  QLineEdit *line_input = line_focus_input();
  line_input->clear();

  line_input->setFocus();
}

void Calculator::backspace_button() {
  QLineEdit *line_input = line_focus_input();
  line_input->backspace();

  line_input->setFocus();
}

void Calculator::eq_button() {
  bool empty_x = true;
  double x_value = 0;
  double error_x = 0;
  double result = 0;
  double error = 0;

  str = ui->input->text().toStdString();

  empty_x = ui->input_x->displayText().isEmpty();

  if (empty_x == false) {
    str_x = ui->input_x->text().toStdString();
    error_x = smart_calculation(&str_x[0], &x_value, 0, 1);
  }

  error = smart_calculation(&str[0], &result, x_value, empty_x);

  if (error == EMPTY_INPUT) {
    answer_preparation();
    ui->input->setText("EMPTY INPUT");
  } else if (error == INVALID_VALUE) {
    answer_preparation();
    ui->input->setText("INVALID VALUE");
  } else if (error == CALCULATION_ERROR) {
    answer_preparation();
    ui->input->setText("CALCULATION ERROR");
  } else if (error == INVALID_X || error_x != OK) {
    answer_preparation();
    ui->input->setText("INVALID X");
  } else if (error == OK) {
    answer_preparation();
    QString ans = QString::number(result, 'f', 7);
    ui->input->setText(ans);
  }

  ui->input->setFocus();
}

void Calculator::plot_button() {
  double error_x_min = 0;
  double error_x_max = 0;
  double error_y_min = 0;
  double error_y_max = 0;
  double result = 0;
  int status = 0;

  str = ui->input->text().toStdString();

  ui->plot_window->clearGraphs();

  str_x_min = ui->x_min->text().toStdString();
  str_x_max = ui->x_max->text().toStdString();
  str_y_min = ui->y_min->text().toStdString();
  str_y_max = ui->y_max->text().toStdString();

  error_x_min = smart_calculation(&str_x_min[0], &value_x_min, 0, 1);
  error_x_max = smart_calculation(&str_x_max[0], &value_x_max, 0, 1);
  error_y_min = smart_calculation(&str_y_min[0], &value_y_min, 0, 1);
  error_y_max = smart_calculation(&str_y_max[0], &value_y_max, 0, 1);

  if (error_x_min == OK && error_x_max == OK && error_y_min == OK &&
      error_y_max == OK && value_x_max > value_x_min &&
      value_y_max > value_y_min && value_x_min >= MIN_VALUE &&
      value_y_min >= MIN_VALUE && value_x_max <= MAX_VALUE &&
      value_y_max <= MAX_VALUE) {
    ui->plot_window->xAxis->setRange(value_x_min, value_x_max);
    ui->plot_window->yAxis->setRange(value_y_min, value_y_max);
    ui->plot_window->replot();

    step = (value_x_max - value_x_min) / 10000.0;

    for (value_x = value_x_min; value_x <= value_x_max && status == OK;
         value_x += step) {
      status = smart_calculation(&str[0], &result, value_x, 0);
      if (status == OK && result <= MAX_VALUE && result >= MIN_VALUE &&
          result == result) {  //
        x.push_back(value_x);
        y.push_back(result);
      } else if (status == EMPTY_INPUT) {
        answer_preparation();
        ui->input->setText("EMPTY INPUT");
      } else if (status == INVALID_VALUE) {
        answer_preparation();
        ui->input->setText("INVALID VALUE");
      } else if (status == CALCULATION_ERROR) {
        answer_preparation();
        ui->input->setText("CALCULATION ERROR");
      }
    }
    ui->plot_window->addGraph();
    ui->plot_window->graph(0)->setPen(QPen(graph_line_color, 2));
    ui->plot_window->graph(0)->setData(x, y);
    ui->plot_window->replot();
    x.clear();
    y.clear();

    if (status == OK) {
      answer_preparation();
    }

    ui->input->setFocus();

  } else {
    ui->x_min->clear();
    ui->x_max->clear();
    ui->y_min->clear();
    ui->y_max->clear();
    ui->entered->clear();
    ui->entered->setText(ui->input->text());
    ui->input->clear();
    ui->input->setText("INVALID BORDERS");

    ui->input->setFocus();
  }
}

QLineEdit *Calculator::line_focus_input() {
  QLineEdit *line_input = NULL;
  QLineEdit *line_inputs[] = {
      ui->input, ui->input_x, ui->x_min, ui->x_max, ui->y_min, ui->y_max,
  };
  for (QLineEdit *line : line_inputs) {
    if (line->hasFocus() == true) {
      line_input = line;
    }
  }
  return line_input;
}

void Calculator::answer_preparation() {
  ui->entered->clear();
  ui->entered->setText(ui->input->text());
  ui->input->clear();
  ui->input_x->clear();
}

void Calculator::stylize() {
  ui->plot_window->setBackground(QBrush(background_color));
  QPen axisPen(axis_color);
  axisPen.setWidth(1);
  ui->plot_window->xAxis->setBasePen(axisPen);
  ui->plot_window->yAxis->setBasePen(axisPen);
  ui->plot_window->xAxis->setTickPen(axisPen);
  ui->plot_window->yAxis->setTickPen(axisPen);
  ui->plot_window->xAxis->setSubTickPen(axisPen);
  ui->plot_window->yAxis->setSubTickPen(axisPen);
  ui->plot_window->xAxis->setTickLabelColor(axis_color);
  ui->plot_window->yAxis->setTickLabelColor(axis_color);
  ui->plot_window->xAxis->setLabelColor(axis_color);
  ui->plot_window->yAxis->setLabelColor(axis_color);
}

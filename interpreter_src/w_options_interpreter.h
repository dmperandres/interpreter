//LIC

#ifndef _W_OPTIONS_INTERPRETER_H
#define _W_OPTIONS_INTERPRETER_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <iostream>

#include "button_color_simple.h"

//#include "glwidget_positions.h"

class _window_interpreter;

//HEA

class _w_options_interpreter: public QDialog
{
Q_OBJECT

public:
  _w_options_interpreter(_window_interpreter *Window1);

public slots:
  void apply_slot();
  void close_slot();
//  void copy_to_print_slot(int);

protected:
  // XRF
  QSpinBox *Spinbox_interpreter_xrf_title_font_size=nullptr;
  QSpinBox *Spinbox_interpreter_xrf_legend_font_size=nullptr;
  QSpinBox *Spinbox_interpreter_xrf_graph_line_width=nullptr;

  // XRD
  QSpinBox *Spinbox_interpreter_xrd_title_font_size=nullptr;
  QSpinBox *Spinbox_interpreter_xrd_legend_font_size=nullptr;
  QSpinBox *Spinbox_interpreter_xrd_graph_line_width=nullptr;

  QTabWidget *Tab=nullptr;

  _window_interpreter *Window=nullptr;
};

#endif

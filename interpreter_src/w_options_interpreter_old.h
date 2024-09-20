//LIC

#ifndef _w_options_interpreter_INTERPRETER_H
#define _w_options_interpreter_INTERPRETER_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <iostream>
#include <QDialog>
#include <QSpinBox>
#include <QTabWidget>

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

protected:
  QSpinBox * Spinbox_general_font_size=nullptr;

  QTabWidget *Tab=nullptr;

  _window_interpreter *Window=nullptr;
};

#endif

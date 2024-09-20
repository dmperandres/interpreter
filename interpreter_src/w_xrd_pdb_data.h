//LIC

#ifndef _W_XRD_PDB_DATA_H
#define _W_XRD_PDB_DATA_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QDateTime>
#include <QStringView>
#include <QCalendarWidget>

#include <iostream>

class _window_interpreter;

//HEA

class _w_xrd_pdb_data: public QDialog
{
Q_OBJECT

public:
  _w_xrd_pdb_data(_window_interpreter *Window1);

public slots:

  void accept_slot();

//  void apply_slot();

protected:
  QComboBox *Combobox_type=nullptr;
  QComboBox *Combobox_tube_type=nullptr;
  QComboBox *Combobox_normalized=nullptr;
  QLineEdit *Lineedit_name=nullptr;
  QLineEdit *Lineedit_formula=nullptr;
  QLineEdit *Lineedit_xrf_elements=nullptr;
  QLineEdit *Lineedit_rgb_color=nullptr;

  _window_interpreter *Window=nullptr;
};

#endif

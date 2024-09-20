//LIC

#ifndef _W_XRD_PDB_OPTIONS_H
#define _W_XRD_PDB_OPTIONS_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <iostream>
#include <QCheckBox>
#include <QDialog>
#include <QComboBox>
#include <QListWidget>

class _window_interpreter;

//HEA

class _w_xrd_pdb_options: public QDialog
{
Q_OBJECT

public:
  _w_xrd_pdb_options(_window_interpreter *Window1,QStringList &Folders_short_names);


public slots:
  void apply_slot();
//  void close_slot();
//  void xrd_use_pdb_spectral_Cu_slot(int State);
//  void xrd_use_pdb_spectral_Co_slot(int State);
//  void xrd_use_pdb_astm_Cu_slot(int State);

protected:
//  QCheckBox* Checkbox_use_xrd_pdb_spectral_Cu=nullptr;
//  QCheckBox* Checkbox_use_xrd_pdb_spectral_Co=nullptr;
//  QCheckBox* Checkbox_use_xrd_pdb_astm_Cu=nullptr;
  QListWidget *List_xrd_pdbs=nullptr;
  QComboBox* Combobox_tube_type=nullptr;

  _window_interpreter *Window=nullptr;
};

#endif

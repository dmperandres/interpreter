//LIC

#include "w_xrd_pdb_data.h"
#include "window_interpreter.h"

_w_xrd_pdb_data::_w_xrd_pdb_data(_window_interpreter *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  setMinimumWidth(300);

  // Type input. Default type of input file (DAT or CSV
  QFrame *Frame_main=new QFrame;

  QGridLayout *Grid=new QGridLayout;

  QLabel *Label1=new QLabel("TYPE: ");
  QLabel *Label2=new QLabel("TUBE: ");
  QLabel *Label3=new QLabel("NORMALIZED: ");
  QLabel *Label4=new QLabel("NAME: ");
  QLabel *Label5=new QLabel("FORMULA: ");
  QLabel *Label6=new QLabel("XRF: ");
  QLabel *Label7=new QLabel("COLOR: ");

  Combobox_type=new QComboBox;
  for (unsigned int i=0;i<_data_xrd_ns::Vec_type_name.size();i++){
    Combobox_type->addItem(_data_xrd_ns::Vec_type_name[i]);
  }
  Combobox_type->setCurrentIndex(int(_data_xrd_ns::_pdb_type::PDB_TYPE_SPECTRAL));

  Combobox_tube_type=new QComboBox;
  for (unsigned int i=0;i<_data_xrd_ns::Vec_tube_name.size();i++){
    Combobox_tube_type->addItem(_data_xrd_ns::Vec_tube_name[i]);
  }
  Combobox_type->setCurrentIndex(int(Window->tube_type()));

  Combobox_normalized=new QComboBox;
  for (unsigned int i=0;i<_data_xrd_ns::Vec_normalized_name.size();i++){
    Combobox_normalized->addItem(_data_xrd_ns::Vec_normalized_name[i]);
  }
  Combobox_normalized->setCurrentIndex(int(_data_xrd_ns::_normalized_type::NORMALIZED_YES));

  Lineedit_name=new QLineEdit;
  Lineedit_name->setPlaceholderText("Name");

  Lineedit_formula=new QLineEdit;
  Lineedit_formula->setPlaceholderText("Formula");

  Lineedit_xrf_elements=new QLineEdit;
  Lineedit_xrf_elements->setPlaceholderText("Elements");

  Lineedit_rgb_color=new QLineEdit;
  Lineedit_rgb_color->setPlaceholderText("255,255,255");

  Grid->addWidget(Label1,0,0,Qt::AlignRight);
  Grid->addWidget(Combobox_type,0,1,Qt::AlignLeft);
  Grid->addWidget(Label2,1,0,Qt::AlignRight);
  Grid->addWidget(Combobox_tube_type,1,1,Qt::AlignLeft);
  Grid->addWidget(Label3,2,0,Qt::AlignRight);
  Grid->addWidget(Combobox_normalized,2,1,Qt::AlignLeft);
  Grid->addWidget(Label4,3,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_name,3,1,Qt::AlignLeft);
  Grid->addWidget(Label5,4,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_formula,4,1,Qt::AlignLeft);
  Grid->addWidget(Label6,5,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_xrf_elements,5,1,Qt::AlignLeft);
  Grid->addWidget(Label7,6,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_rgb_color,6,1,Qt::AlignLeft);

  //
  Frame_main->setLayout(Grid);

  //
  QHBoxLayout *Horizontal1=new QHBoxLayout;

  Horizontal1->addWidget(Frame_main);

  QWidget *Widged_p=new QWidget;

  Widged_p->setLayout(Horizontal1);

  // control buttons
  QPushButton *Button_ok = new QPushButton(tr("Accept"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept_slot()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Widged_p);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Options");
}

//HEA

void _w_xrd_pdb_data::accept_slot()
{
  if (Lineedit_name->text()!=""){
    Window->pdb_parameters(_data_xrd_ns::_pdb_type(Combobox_type->currentIndex()), _data_xrd_ns::_tube_type(Combobox_tube_type->currentIndex()),bool(Combobox_normalized), Lineedit_name->text(), Lineedit_formula->text(), Lineedit_xrf_elements->text(), Lineedit_rgb_color->text());
    accept();
  }
  else{
    QMessageBox::warning(this, tr("Warning"),tr("Please, insert one or several names separated by commas"));
  }
}

//HEA

//void _w_xrd_pdb_data::apply_slot()
//{
//  Window->pdb_parameters(Lineedit_name->text(),Lineedit_formula->text(),Lineedit_xrf_elements->text(),Lineedit_rgb_color->text());
//}



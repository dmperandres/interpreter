//LIC

#include "w_options_interpreter.h"
#include "window_interpreter.h"

_w_options_interpreter::_w_options_interpreter(_window_interpreter *Window1):QDialog(Window1)
{
  Window=Window1;

  // ui options
  QWidget *W_general=new QWidget;

  QGridLayout *Grid_general=new QGridLayout;

  QLabel *Label_general_font_size=new QLabel("Font size");

  Spinbox_general_font_size=new QSpinBox;
  Spinbox_general_font_size->setValue(Window->ui_font_size());

  Grid_general->addWidget(Label_general_font_size,0,0,Qt::AlignRight);
  Grid_general->addWidget(Spinbox_general_font_size,0,1,Qt::AlignLeft);

  W_general->setLayout(Grid_general);

  // control buttons
  QPushButton *Button_apply = new QPushButton(tr("Apply"));
  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

  QPushButton *Button_ok = new QPushButton(tr("Close window"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_apply);
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);

  Tab=new QTabWidget(this);
  Tab->addTab(W_general,"General");

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Tab);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Options");
}


//HEA

void _w_options_interpreter::apply_slot()
{
  Window->ui_set_font_size(Spinbox_general_font_size->value());
}

//HEA

void _w_options_interpreter::close_slot()
{
  Window->ui_set_font_size(Spinbox_general_font_size->value());
  close();
}


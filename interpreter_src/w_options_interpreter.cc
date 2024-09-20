//LIC

#include "w_options_interpreter.h"
#include "window_interpreter.h"


_w_options_interpreter::_w_options_interpreter(_window_interpreter *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  // XRF
  QWidget *W_interpreter_xrf=new QWidget;
  QGridLayout *Grid_interpreter_xrf=new QGridLayout;

  QLabel *Label_interpreter_xrf1=new QLabel("Title font size");
  QLabel *Label_interpreter_xrf2=new QLabel("Legend font size");
  QLabel *Label_interpreter_xrf3=new QLabel("Graph line width");

  Spinbox_interpreter_xrf_title_font_size=new QSpinBox;
  Spinbox_interpreter_xrf_title_font_size->setValue(Window->interpreter_xrf_title_font_size());

  Spinbox_interpreter_xrf_legend_font_size=new QSpinBox;
  Spinbox_interpreter_xrf_legend_font_size->setValue(Window->interpreter_xrf_legend_font_size());

  Spinbox_interpreter_xrf_graph_line_width=new QSpinBox;
  Spinbox_interpreter_xrf_graph_line_width->setValue(Window->interpreter_xrf_graph_line_widht());

  Grid_interpreter_xrf->addWidget(Label_interpreter_xrf1,0,0,Qt::AlignRight);
  Grid_interpreter_xrf->addWidget(Spinbox_interpreter_xrf_title_font_size,0,1,Qt::AlignLeft);
  Grid_interpreter_xrf->addWidget(Label_interpreter_xrf2,1,0,Qt::AlignRight);
  Grid_interpreter_xrf->addWidget(Spinbox_interpreter_xrf_legend_font_size,1,1,Qt::AlignLeft);
  Grid_interpreter_xrf->addWidget(Label_interpreter_xrf3,2,0,Qt::AlignRight);
  Grid_interpreter_xrf->addWidget(Spinbox_interpreter_xrf_graph_line_width,2,1,Qt::AlignLeft);

  W_interpreter_xrf->setLayout(Grid_interpreter_xrf);

//  QWidget *Widged_xrf=new QWidget;
//  QVBoxLayout *Vboxlayout_xrf=new QVBoxLayout;

//  Vboxlayout_xrf->addWidget(W_interpreter_xrf);

//  Widged_xrf->setLayout(Vboxlayout_xrf);

  // XRD
  QWidget *W_interpreter_xrd=new QWidget;
  QGridLayout *Grid_interpreter_xrd=new QGridLayout;

  QLabel *Label_interpreter_xrd1=new QLabel("Title font size");
  QLabel *Label_interpreter_xrd2=new QLabel("Legend font size");
  QLabel *Label_interpreter_xrd3=new QLabel("Graph line width");

  Spinbox_interpreter_xrd_title_font_size=new QSpinBox;
  Spinbox_interpreter_xrd_title_font_size->setValue(Window->interpreter_xrd_title_font_size());

  Spinbox_interpreter_xrd_legend_font_size=new QSpinBox;
  Spinbox_interpreter_xrd_legend_font_size->setValue(Window->interpreter_xrd_legend_font_size());

  Spinbox_interpreter_xrd_graph_line_width=new QSpinBox;
  Spinbox_interpreter_xrd_graph_line_width->setValue(Window->interpreter_xrd_graph_line_widht());

  Grid_interpreter_xrd->addWidget(Label_interpreter_xrd1,0,0,Qt::AlignRight);
  Grid_interpreter_xrd->addWidget(Spinbox_interpreter_xrd_title_font_size,0,1,Qt::AlignLeft);
  Grid_interpreter_xrd->addWidget(Label_interpreter_xrd2,1,0,Qt::AlignRight);
  Grid_interpreter_xrd->addWidget(Spinbox_interpreter_xrd_legend_font_size,1,1,Qt::AlignLeft);
  Grid_interpreter_xrd->addWidget(Label_interpreter_xrd3,2,0,Qt::AlignRight);
  Grid_interpreter_xrd->addWidget(Spinbox_interpreter_xrd_graph_line_width,2,1,Qt::AlignLeft);

  W_interpreter_xrd->setLayout(Grid_interpreter_xrd);


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
  Tab->addTab(W_interpreter_xrf,"XRF");
  Tab->addTab(W_interpreter_xrd,"XRD");

//  if (Window->copy_display_values()) Tab->setTabEnabled(1,false);

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
  if (Tab->currentIndex()==0) Window->options_parameters_xrf(Spinbox_interpreter_xrf_title_font_size->value(), Spinbox_interpreter_xrf_legend_font_size->value(), Spinbox_interpreter_xrf_graph_line_width->value());
  else Window->options_parameters_xrd(Spinbox_interpreter_xrd_title_font_size->value(), Spinbox_interpreter_xrd_legend_font_size->value(), Spinbox_interpreter_xrd_graph_line_width->value());
}

//HEA

void _w_options_interpreter::close_slot()
{
  Window->options_parameters_xrf(Spinbox_interpreter_xrf_title_font_size->value(), Spinbox_interpreter_xrf_legend_font_size->value(), Spinbox_interpreter_xrf_graph_line_width->value());

  Window->options_parameters_xrd(Spinbox_interpreter_xrd_title_font_size->value(), Spinbox_interpreter_xrd_legend_font_size->value(), Spinbox_interpreter_xrd_graph_line_width->value());

  close();
}


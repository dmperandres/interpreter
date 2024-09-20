#include "w_tab_interpreter.h"
#include "window_interpreter.h"

//HEA

_w_tab_interpreter::_w_tab_interpreter(_window_interpreter *Window1): Window(Window1)
{
}

//HEA

_w_tab_interpreter::~_w_tab_interpreter()
{
#ifdef DEBUG_XML
  std::cout << "Terminando w_tab" << std::endl;
#endif
}

//HEA

void _w_tab_interpreter::initialize()
{
  create_data_xrf_widget();

  addTab(Widget_xrf, tr("XRF data"));
//  addTab(Widget_elements, tr("Elements"));
//  addTab(Widget_palettes, tr("Palettes"));

  for (int i=0;i<_w_tab_interpreter_ns::TAB_LAST;i++){
    setTabEnabled(i,false);
  }

}

//HEA

void _w_tab_interpreter::create_data_xrf_widget()
{
  Widget_xrf=new QWidget;

  Verticalbox_layers=new QVBoxLayout;
  //
  Verticalbox_layers->addWidget(static_cast<QTableWidget *>(Table_data_xrf));

  Widget_xrf->setLayout(Verticalbox_layers);

  Widget_xrf->setEnabled(true);
}

//HEAD

void _w_tab_interpreter::tab_bar_clicked_slot(int Tab1)
{
  Window->Selected_tab=Tab1;

//  update_color_bar();
}

#ifndef WIDGET_TAB_INTERPRETER
#define WIDGET_TAB_INTERPRETER

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QIcon>
#include <QProgressDialog>

#include <vector>

#include "table.h"
//#include "table_xrf.h"

//#include "color_bar_abstract.h"
//#include "dialog_create_palette.h"
//#include "layer_compound.h"

class _table_xrf;
class _window_interpreter;

namespace _w_tab_interpreter_ns {
  typedef enum {TAB_XRF,TAB_LAST} _tabs;
}

class _w_tab_interpreter: public QTabWidget
{
Q_OBJECT
public:
  _table_xrf *Table_data_xrf=nullptr;

  _w_tab_interpreter(_window_interpreter *Window1);
  ~_w_tab_interpreter();

  void initialize();

  void create_data_xrf_widget();


//  void select_layers_row(int Row){Table_layers->selectRow(Row);}

//  void add_layer(_table_layers_ns::_info Info, QIcon *Icon1);

//  void remove_layer_from_layout(string Name1);

//  void remove_layer(string Name1);


//  void update_color_bar();

//  void change_state_table_layer(int Row,int Col);

//  void move_layers_backward(int Initial_pos,int Destination_pos);
//  void move_layers_forward(int Initial_pos,int Destination_pos);

//  void show_layer_parameters(int Row, int Col);

//  void change_button_state(int Row,int Col);

//  void add_element(string Name);

//  void change_buttons_state(bool State){
//    Button_create_element->setEnabled(State);
//    Button_create_all_elements->setEnabled(State);
//  }

//  void restart();

//  void reverse_col(int Col);

protected slots:
  void tab_bar_clicked_slot(int Tab1);
//  void add_filter_layer_slot(int Value);
//  void remove_layer_slot();
//  void remove_all_layers_slot();
//  void create_single_element_slot();
//  void create_all_elements_slot();
//  void create_palette_slot();
//  void change_row_palette_slot(int Row);

//  void state_changed_use_colors_slot(int State);
//  void state_changed_use_positions_slot(int State);

protected:
  _window_interpreter *Window=nullptr;

  QTabWidget *Tab_widget=nullptr;

  // layers tab
  QWidget *Widget_xrf=nullptr;
  QVBoxLayout *Verticalbox_layers=nullptr;
//  QComboBox *Combo_add_layer=nullptr;

  // elements tab
//  QWidget *Widget_elements=nullptr;
//  QVBoxLayout *Verticalbox_elements=nullptr;
//  QListWidget *Listwidget_layers=nullptr;
//  QListWidget *Listwidget_elements=nullptr;
//  QPushButton *Button_create_element=nullptr;
//  QPushButton *Button_create_all_elements=nullptr;
//  QComboBox *Combobox_probe=nullptr;
//  QCheckBox *Checkbox_use_colors=nullptr;
//  QCheckBox *Checkbox_use_positions=nullptr;
//  QFrame *Frame_element_parameters=nullptr;


  QIcon Icon_discrete;
  QIcon Icon_continuous;
  QPixmap *Pixmap_palette_discrete=nullptr;
  QPixmap *Pixmap_palette_continuous=nullptr;
};

#endif



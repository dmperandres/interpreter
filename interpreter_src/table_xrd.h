#ifndef TABLE_XRD
#define TABLE_XRD

#include <QTableWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QHeaderView>
#include <QDropEvent>
#include <QString>
#include <iostream>
#include <vector>

#include "table.h"
//#include "button_icon.h"

#include "data_xrd.h"

namespace _table_xrd_ns
{
const int NUM_BUTTONS=2;

const int NUM_COLS=2;
const int NUM_ROWS=5;
const int WIDTH_BUTTON_COLUMN=50;

enum{VISIBILITY,WRITABILITY};

class _icon_state {
  public:
  QIcon Icon_on;
  QIcon Icon_off;
};

struct _info {
  //    _button_icon *Buttons[NUM_BUTTONS]={nullptr,nullptr};
  bool States[NUM_BUTTONS]={true,true};
  float Transparence=0;
  QString Name="NONE";
};
}

class _window_interpreter;


class CustomButton : public QPushButton
{
public:
  CustomButton(QWidget* parent = nullptr) : QPushButton(parent) {}
};


class _table_xrd: public QTableWidget
{
  Q_OBJECT

  public:
  std::vector<_table_xrd_ns::_info> Vec_info;

  _table_xrd(_window_interpreter *Window1);
  ~_table_xrd();

  void check_data(int Row, int Col, QPushButton* Button, bool Selected);
  void set_data(std::vector<std::string> Row_names, std::vector<std::string> Col_names);

  //  void remove_widget(QWidget *Widget);

  //  void change_button(int Row,int Col);

  //  void add_row(_table_xrd_ns::_info Info, int Row=-1);

  //  void update_table();

  //  void move_layers_backward(int Initial_row,int Destination_row);
  //  void move_layers_forward(int Initial_row,int Destination_row);

  //  void remove_row(int Row);

public slots:
  //  void button_clicked_slot(int Row,int Col);
  //  void cell_clicked_slot(int Row,int Col);
  void button_clicked_slot(int Row,int Col);
  //  void header_clicked_slot(int Col);

protected:
  void wheelEvent(QWheelEvent *Event) override;
  void mousePressEvent(QMouseEvent* Event);

  //  void dropEvent(QDropEvent *Event);
  //  // for update
  //  void remove_all_rows();

  //  QList<QTableWidgetItem*> get_row(int Row);
  //  void set_row(int row, const QList<QTableWidgetItem*>& rowItems);

  //  std::vector<_table_xrd_ns::_icon_state> Vec_icons;

  void create_table();
  void update_table(int Row,int Col);
//  void update_cells_font();

  _window_interpreter *Window=nullptr;

  std::vector<bool> Vec_valid_rows;

  int Previous_row;
  int Previous_col;
  int Current_row;
  int Current_col;

  QPixmap Pixmap_valid;
  QPixmap Pixmap_invalid;

  std::vector<std::string> Row_names;
  std::vector<std::string> Col_names;
  //  uint Num_rows;
  //  uint Active_row;
};

#endif

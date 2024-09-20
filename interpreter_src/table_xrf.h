#ifndef TABLE_XRF_H
#define TABLE_XRF_H

#include <QTableWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QHeaderView>
#include <QDropEvent>
#include <iostream>
#include <vector>

#include "data_xrf.h"

#include "button_icon.h"

namespace _table_xrf_ns
{
  const int NUM_BUTTONS=1;

  const int NUM_COLS=5;
  const int NUM_COLS_BUTTONS=2;
  const int NUM_ROWS=5;
  const int WIDTH_BUTTON_COLUMN=50;

  enum{VISIBILITY,WRITABILITY};

  const std::vector<std::string> VEC_TABLE_XRF_COL_NAMES={"","Found","Thres","","Ka","Value"};

  enum class _column_type:unsigned char{COLUMN_TYPE_SELECTION,COLUMN_TYPE_FOUND,COLUMN_TYPE_VALID,COLUMN_TYPE_ELEMENT,COLUMN_TYPE_KA_POSITION,COLUMN_TYPE_KA_VALUE};

  class _icon_state {
    public:
    QIcon Icon_on;
    QIcon Icon_off;
  };

  struct _info {
    //    _button_icon *Buttons[NUM_BUTTONS]={nullptr,nullptr};
    bool States[NUM_BUTTONS]={true};
    float Transparence=0;
    QString Name="NONE";
  };
}

class _window_interpreter;

class _table_xrf: public QTableWidget
{
  Q_OBJECT

  public:
  //  std::vector<_table_xrf_ns::_info> Vec_info;

  _table_xrf(std::string Name1, _window_interpreter *Window1);
  ~_table_xrf();
  void change_button(int Row, int Col);
  void update_table(std::vector<_data_xrf_ns::_data_xrf_ka_kb> Result_elements, std::vector<std::string> Vec_superposition);

  public slots:
  void button_clicked_slot(int Row,int Col);
  //  void cell_clicked_slot(int Row,int Col);
  void header_clicked_slot(int Col);

  protected:
  //  void dropEvent(QDropEvent *Event);
  // for update
  //  void remove_all_rows();

  _window_interpreter *Window=nullptr;

  QList<QTableWidgetItem*> get_row(int Row);
  void set_row(int row, const QList<QTableWidgetItem*>& rowItems);

  std::vector<_table_xrf_ns::_icon_state> Vec_icons;

  std::string Name;
  uint Num_rows;
  uint Active_row;

  std::vector<_table_xrf_ns::_column_type> Vec_cols;
};

#endif

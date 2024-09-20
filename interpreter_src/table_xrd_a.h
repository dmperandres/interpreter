#ifndef TABLE_XRD_A_H
#define TABLE_XRD_A_H

#include <QTableWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QHeaderView>
#include <QDropEvent>
#include <iostream>
#include <vector>

#include "data_xrd.h"
#include "data_xrf.h"
#include "button_icon.h"
#include "best_color.h"

namespace _table_xrd_a_ns
{
  const int NUM_BUTTONS=1;

  const int NUM_COLS=5;
  const int NUM_COLS_BUTTONS=2;
  const int NUM_ROWS=5;
  const int WIDTH_BUTTON_COLUMN=50;

  enum{VISIBILITY,WRITABILITY};

  const std::vector<std::string> VEC_TABLE_XRD_COL_NAMES={"S","C","",""};
  const std::vector<std::string> VEC_TABLE_XRD_COL_NAMES_TIPS={"State","Correlation","Selection","Pigment"};

  enum class _column_type:unsigned char{COLUMN_TYPE_STATE,COLUMN_TYPE_CORRELATION,COLUMN_TYPE_SELECTION,COLUMN_TYPE_PIGMENT};

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

class _table_xrd_a: public QTableWidget
{
  Q_OBJECT

  public:
  //  std::vector<_table_xrd_a_ns::_info> Vec_info;

  _table_xrd_a(std::string Name1, _window_interpreter *Window1);
  ~_table_xrd_a();
  void change_button(int Row, int Col);
  void update_table(int Position, std::vector<_data_xrd_ns::_data_xrd_pdb> &Vec_xrd_pdb_data, std::vector<_data_xrd_ns::_data_xrd_obs_pdb> &Mat_xrd_obs_vs_pdb_data, std::vector<_data_xrd_ns::_selection> &Mat_xrd_obs_vs_pdb_data_selected, std::vector<_data_xrd_ns::_xrd_order_data> &Vec_order);

  public slots:
  void button_clicked_slot(int Row,int Col);
  void cell_clicked_slot(int Row,int Col);
  void header_clicked_slot(int Col);

  protected:
  void keyPressEvent(QKeyEvent *Event);
  void mouseReleaseEvent(QMouseEvent *Event);
  //  void dropEvent(QDropEvent *Event);
  // for update
  //  void remove_all_rows();

  _window_interpreter *Window=nullptr;

  QList<QTableWidgetItem*> get_row(int Row);
  void set_row(int row, const QList<QTableWidgetItem*>& rowItems);

  std::vector<_table_xrd_a_ns::_icon_state> Vec_icons;

  std::string Name;
//  uint Num_rows;
//  uint Active_row;
  int Selected_row=-1;

  std::vector<_table_xrd_a_ns::_column_type> Vec_cols;

  std::vector<int> Vec_positions;
};

#endif

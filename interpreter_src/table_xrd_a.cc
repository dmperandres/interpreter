#include "table_xrd_a.h"
#include "window_interpreter.h"

//using namespace _table_xrd_a_ns;

//HEA

_table_xrd_a::_table_xrd_a(std::string Name1, _window_interpreter *Window1)
{
  Name=Name1;
  Window=Window1;

  Vec_cols.push_back(_table_xrd_a_ns::_column_type::COLUMN_TYPE_STATE);
  Vec_cols.push_back(_table_xrd_a_ns::_column_type::COLUMN_TYPE_CORRELATION);
  Vec_cols.push_back(_table_xrd_a_ns::_column_type::COLUMN_TYPE_SELECTION);
  Vec_cols.push_back(_table_xrd_a_ns::_column_type::COLUMN_TYPE_PIGMENT);


  QStringList List_words;
  for (unsigned int i=0;i<Vec_cols.size();i++){
    List_words.push_back(QString::fromStdString(_table_xrd_a_ns::VEC_TABLE_XRD_COL_NAMES[int(Vec_cols[i])]));
  }

  setColumnCount(List_words.size());
  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  setHorizontalHeaderLabels(List_words);

  // for mor info
  for (unsigned int i=0;i<Vec_cols.size();i++){
    horizontalHeaderItem(i)->setToolTip(QString::fromStdString(_table_xrd_a_ns::VEC_TABLE_XRD_COL_NAMES_TIPS[i]));
  }


  QFont Font=font();
  QFontMetrics Font_metric(Font);
  int Width_char1=Font_metric.horizontalAdvance("M");

//  std::vector<int> Widths={Width_char1,Width_char1*2,Width_char1*2,Width_char1*2};

//  for (unsigned int i=0;i<Widths.size();i++ ){
//    setColumnWidth(i,Widths[i]);
//  }

  setColumnWidth(0,Width_char1);

  // stretch the last column to the father size
  horizontalHeader()->setStretchLastSection(true);

  resizeColumnsToContents();

  connect(horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(header_clicked_slot(int)));

  connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));

  // read icons
  Vec_icons.resize(_table_xrd_a_ns::NUM_COLS_BUTTONS);
  QPixmap Pixmap;
  Pixmap.load(":/common/icons/valid.png");
  Vec_icons[_table_xrd_a_ns::VISIBILITY].Icon_on.addPixmap(Pixmap);
  Pixmap.load(":/common/icons/invalid.png");
  Vec_icons[_table_xrd_a_ns::VISIBILITY].Icon_off.addPixmap(Pixmap);
}


_table_xrd_a::~_table_xrd_a()
{
#ifdef DEBUG_XML
  std::cout << "Terminando table layers" << std::endl;
#endif
}

//HEA

QList<QTableWidgetItem*> _table_xrd_a::get_row(int Row)
{
  QList<QTableWidgetItem*> rowItems;
  for (int col = 0; col < columnCount(); ++col){
    rowItems << takeItem(Row, col);
  }
  return rowItems;
}

//HEA

void _table_xrd_a::set_row(int row, const QList<QTableWidgetItem*>& rowItems)
{
  for (int col = 0; col < columnCount(); ++col){
    setItem(row, col, rowItems.at(col));
  }
}

//HEA

void _table_xrd_a::update_table(int Position, std::vector<_data_xrd_ns::_data_xrd_pdb> &Vec_xrd_pdb_data, std::vector<_data_xrd_ns::_data_xrd_obs_pdb> &Mat_xrd_obs_vs_pdb_data, std::vector<_data_xrd_ns::_selection> &Mat_xrd_obs_vs_pdb_data_selected, std::vector<_data_xrd_ns::_xrd_order_data> &Vec_order)
{
  int Col;
//  int Value;
  QString Text;
  int Current_row=0;
  int True_position;
  int Selected_position;

  // delete all the rows
  for (int i=rowCount()-1;i>=0;i--) removeRow(i);

  Vec_positions.clear();

  QTableWidgetItem *Item;
  _button_icon *Button;
//  for (unsigned int i=0;i<Mat_xrd_obs_vs_pdb_data.size();i++){
  for (unsigned int i=0;i<Vec_order.size();i++){
    True_position=Vec_order[i].Position;

    // to match the position that must be marked as selected
    if (True_position==Position) Selected_position=i;

    if (Mat_xrd_obs_vs_pdb_data[True_position].Show==true){

      insertRow(Current_row);
      Vec_positions.push_back(True_position); // save the true position

      Col=0;
      // Elements Col 2
      Item = new QTableWidgetItem;
      switch (Mat_xrd_obs_vs_pdb_data[True_position].Class_type){
      case _data_xrd_ns::_class_type::CLASS_TYPE_NO_XRF_FILE:Item->setBackground(Window->xrd_color_file_not_exists());break;
      case _data_xrd_ns::_class_type::CLASS_TYPE_NO_ELEMENTS:Item->setBackground(Window->xrd_color_element_not_exists());break;
      case _data_xrd_ns::_class_type::CLASS_TYPE_VALID:Item->setBackground(Window->xrd_color_valid_good());break;
      }
      setItem(Current_row,Col,Item); // Element
      Col++;

      // correlation col 3
      int Value=int(roundf(Mat_xrd_obs_vs_pdb_data[True_position].Correlation_coefficient_squared*100.0f)); // R^2
      Text=QString("%1%").arg(Value,2,10,QChar('0'));
      Item = new QTableWidgetItem(Text);
      Item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
      //    Item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled);

      QColor Color_background;
      switch (int(Mat_xrd_obs_vs_pdb_data[True_position].Valid_type)){
        case int(_data_xrd_ns::_valid_type::VALID_TYPE_GOOD):Color_background=Window->xrd_color_valid_good();break;
        case int(_data_xrd_ns::_valid_type::VALID_TYPE_MEDIUM):Color_background=Window->xrd_color_valid_medium();break;
        case int(_data_xrd_ns::_valid_type::VALID_TYPE_BAD):Color_background=Window->xrd_color_valid_bad();break;
      }
      Item->setBackground(Color_background);
      Item->setForeground(_best_color::best_color_between_bw(Color_background));
      setItem(Current_row,Col,Item);
      Col++;

      // button Col 0
      Button=new _button_icon(Current_row,Col);
      if (Mat_xrd_obs_vs_pdb_data_selected[True_position].Selected==true) Button->setIcon(Vec_icons[0].Icon_on);
      else Button->setIcon(Vec_icons[0].Icon_off);
      connect(Button,SIGNAL(change_state(int,int)),this,SLOT(button_clicked_slot(int,int)));
      setCellWidget(Current_row,Col,(QWidget*)Button);
      Col++;

      // Pigment Col 1
      Item = new QTableWidgetItem(QString::fromStdString(Vec_xrd_pdb_data[True_position].File_name));
      Item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      //    Item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled);
      setItem(Current_row,Col,Item); // Element
      Col++;

      Current_row++;
    }
  }

  resizeRowsToContents();

  selectRow(Selected_position);

  Selected_row=Selected_position;
}

//HEA

void _table_xrd_a::change_button(int Row,int Col)
{
  _button_icon *Button=static_cast<_button_icon *>(cellWidget(Row,Col));

  if (Window->mat_obs_vs_pdb_data_selected(Window->selected_xrf_file(),Vec_positions[Row])==true){
    Button->setIcon(Vec_icons[0].Icon_off);
  }
  else{
    Button->setIcon(Vec_icons[0].Icon_on);
  }
}

//HEA

void _table_xrd_a::button_clicked_slot(int Row,int Col)
{
  Q_UNUSED(Col)

  change_button(Row,Col);

  blockSignals(true);
  selectRow(Row);
  blockSignals(false);

  Window->xrd_change_button_state(Vec_positions[Row]);
}

//HEA

void _table_xrd_a::cell_clicked_slot(int Row,int Col)
{
  Q_UNUSED(Col)

  Selected_row=Row;

  blockSignals(true);
  selectRow(Row);
  blockSignals(false);

  Window->xrd_select_position(Vec_positions[Row]);
}

//HEA

void _table_xrd_a::header_clicked_slot(int Col)
{
  if (Col==int(_table_xrd_a_ns::_column_type::COLUMN_TYPE_CORRELATION) ||
      Col==int(_table_xrd_a_ns::_column_type::COLUMN_TYPE_PIGMENT)) Window->xrd_order_obs_data(_table_xrd_a_ns::_column_type(Col));
}


//HEA

void _table_xrd_a::keyPressEvent(QKeyEvent *Event)
{
  if (Event->key() == Qt::Key_Down || Event->key() == Qt::Key_Up){
    Event->ignore();
    return;
  }
}

//HEA

void _table_xrd_a::mouseReleaseEvent(QMouseEvent *Event)
{
  QTableWidget::mouseReleaseEvent(Event);

  // Obtener la posición del clic
  QPoint Click_position = Event->pos();

  // Obtener la fila y la columna en la que se hizo clic
  int Row = rowAt(Click_position.y());
  int Col = columnAt(Click_position.x());

  if (Row == -1 || Col == -1) {
    selectRow(Selected_row);
  }

//    Event->accept();
    // Llamar al manejador del evento del padre (si es necesario)
//    QTableWidget::mousePressEvent(Event);
}


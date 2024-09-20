#include "table_xrf.h"
#include "window_interpreter.h"

//using namespace _table_xrf_ns;

//HEA

_table_xrf::_table_xrf(std::string Name1, _window_interpreter *Window1)
{
  Name=Name1;
  Window=Window1;

  Vec_cols.push_back(_table_xrf_ns::_column_type::COLUMN_TYPE_SELECTION);
  Vec_cols.push_back(_table_xrf_ns::_column_type::COLUMN_TYPE_ELEMENT);
  Vec_cols.push_back(_table_xrf_ns::_column_type::COLUMN_TYPE_KA_POSITION);
  Vec_cols.push_back(_table_xrf_ns::_column_type::COLUMN_TYPE_KA_VALUE);

  QStringList List_words;
  for (unsigned int i=0;i<Vec_cols.size();i++){
    List_words.push_back(QString::fromStdString(_table_xrf_ns::VEC_TABLE_XRF_COL_NAMES[int(Vec_cols[i])]));
  }

  setColumnCount(List_words.size());
  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  setHorizontalHeaderLabels(List_words);

  QFont Font=font();
  QFontMetrics Font_metric(Font);
  int Width_char1=Font_metric.horizontalAdvance("M");

  std::vector<int> Widths={Width_char1,Width_char1,Width_char1,Width_char1*3,Width_char1*4,Width_char1*6};

  for (unsigned int i=0;i<Widths.size();i++ ){
    setColumnWidth(i,Widths[i]);
  }

  // stretch the last column to the father size
  horizontalHeader()->setStretchLastSection(true);

  connect(horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(header_clicked_slot(int)));

  // read icons
  Vec_icons.resize(_table_xrf_ns::NUM_COLS_BUTTONS);
  QPixmap Pixmap;
  Pixmap.load(":/common/icons/valid.png");
  Vec_icons[_table_xrf_ns::VISIBILITY].Icon_on.addPixmap(Pixmap);
  Pixmap.load(":/common/icons/invalid.png");
  Vec_icons[_table_xrf_ns::VISIBILITY].Icon_off.addPixmap(Pixmap);

  //  Pixmap.load(":/icons/invalid.png");
  //  Vec_icons[WRITABILITY].Icon_on.addPixmap(Pixmap);
  //  Pixmap.load(":/icons/button_no_write");
  //  Vec_icons[WRITABILITY].Icon_off.addPixmap(Pixmap);

  //  connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));
}


_table_xrf::~_table_xrf()
{
#ifdef DEBUG_XML
  std::cout << "Terminando table layers" << std::endl;
#endif
}

//HEA

QList<QTableWidgetItem*> _table_xrf::get_row(int Row)
{
  QList<QTableWidgetItem*> rowItems;
  for (int col = 0; col < columnCount(); ++col){
    rowItems << takeItem(Row, col);
  }
  return rowItems;
}

//HEA

void _table_xrf::set_row(int row, const QList<QTableWidgetItem*>& rowItems)
{
  for (int col = 0; col < columnCount(); ++col){
    setItem(row, col, rowItems.at(col));
  }
}

//HEA

void _table_xrf::update_table(std::vector<_data_xrf_ns::_data_xrf_ka_kb> Result_elements,std::vector<std::string> Vec_superposition)
{
  int Col;

  // delete all the rows
  for (int i=rowCount()-1;i>=0;i--) removeRow(i);

  QTableWidgetItem *Item;
  _button_icon *Button;
  for (unsigned int i=0;i<Result_elements.size();i++){
    insertRow(i);

    Col=0;
    // button Col 0
    Button=new _button_icon(i,Col);
    if (Result_elements[i].Selected==true) Button->setIcon(Vec_icons[0].Icon_on);
    else Button->setIcon(Vec_icons[0].Icon_off);
    connect(Button,SIGNAL(change_state(int,int)),this,SLOT(button_clicked_slot(int,int)));
    setCellWidget(i,Col,(QWidget*)Button);
    Col++;

//    // col 1
//    Item = new QTableWidgetItem;
//    if (Result_elements[i].Selected_found==true) Item->setBackground(Qt::green);
//    else Item->setBackground(Qt::red);
//    setItem(i,Col,Item); // Element
//    Col++;

//    // col 2
//    Item = new QTableWidgetItem;
//    if (Result_elements[i].Selected_threshold==true) Item->setBackground(Qt::green);
//    else Item->setBackground(Qt::red);
//    setItem(i,Col,Item); // Element
//    Col++;

    //    Button=new _button_icon(i,Col);
    //    if (Result_elements[i].Selected_valid==true) Button->setIcon(Vec_icons[0].Icon_on);
    //    else Button->setIcon(Vec_icons[0].Icon_off);
    //    connect(Button,SIGNAL(change_state(int,int)),this,SLOT(button_clicked_slot(int,int)));
    //    setCellWidget(i,Col,(QWidget*)Button);
    //    Col++;

    // Element Col 3
    Item = new QTableWidgetItem(QString::fromStdString(Result_elements[i].Name));
    Item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    //    Item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled);
    setItem(i,Col,Item); // Element
    Col++;

    // Ka Col 4
    Item = new QTableWidgetItem(QString::number(Result_elements[i].Ka.Position_kev,'f',2));
    Item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    //    Item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled);
    setItem(i,Col,Item); // Element
    Col++;

    // Value Col 5
    // check if there is superposition
    auto it = std::find(Vec_superposition.begin(), Vec_superposition.end(), Result_elements[i].Name);

    // Comprobar si se encontró el elemento
    bool Superpostion=false;
    if (it != Vec_superposition.end()) Superpostion=true;

    float Value=Result_elements[i].Ka.Value;
    Item = new QTableWidgetItem(QString::number(Value,'f',4));
    Item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    //    Item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled);
    if (Superpostion==false){
      if (Result_elements[i].Selected==true){
        Item->setBackground(Qt::green);
        Item->setForeground(Qt::black);
      }
      else{
        Item->setBackground(Qt::red);
        Item->setForeground(Qt::white);
      }
    }
    else{
      Item->setBackground(QColorConstants::Svg::orange);
      Item->setForeground(Qt::white);
    }

    setItem(i,Col,Item); // Element
  }

  resizeRowsToContents();
}

//HEA

void _table_xrf::change_button(int Row,int Col)
{
  if (Row<rowCount()){
    _button_icon *Button=static_cast<_button_icon *>(cellWidget(Row,Col));

    if (Window->xrf_selected(Row)==true){
      Button->setIcon(Vec_icons[0].Icon_off);
    }
    else{
      Button->setIcon(Vec_icons[0].Icon_on);
    }
  }
}

//HEA

void _table_xrf::button_clicked_slot(int Row,int Col)
{
  // Buttonat col 0
  if (Col==0){
    //
    change_button(Row,0);

    blockSignals(true);
    selectRow(Row);
    blockSignals(false);

    Window->xrf_change_button_state(Row);
  }
}

//

void _table_xrf::header_clicked_slot(int Col)
{
  if (Col>int(_table_xrf_ns::_column_type::COLUMN_TYPE_SELECTION)) Window->xrf_order_obs_data(Vec_cols[Col]);
}

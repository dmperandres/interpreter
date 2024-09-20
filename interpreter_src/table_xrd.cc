#include "table_xrd.h"
#include "window_interpreter.h"

using namespace _table_xrd_ns;

//HEA

_table_xrd::_table_xrd(_window_interpreter *Window1)
{
  Window=Window1;

  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  //  horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  setSelectionMode(QAbstractItemView::SingleSelection);

  //  connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));

  Pixmap_valid.load(":/common/icons/valid_background.png");
  Pixmap_invalid.load(":/common/icons/invalid_background.png");
}

//HEA

_table_xrd::~_table_xrd()
{
}


//HEA

//void _table_xrd::check_data(int Row, int Col, QPushButton* Button,bool Selected)
//{
//  QString Stylesheet;

//  //  int True_col=Window->xrd_get_true_col(Col);

//  int True_col=Col;

//  int Value=int(roundf(powf(Window->mat_obs_vs_pdb_correlation_coefficient(Row,True_col),2)*100.0f)); // R^2
//  int Num_elements_not_found=Window->mat_obs_vs_pdb_num_elements_not_found(Row,True_col);
//  bool XRF_used=Window->mat_obs_vs_pdb_xrf_used(Row,True_col);

//  // conditions to show a cell

//  if ((Window->xrd_show_file_not_exists() && XRF_used) ||
//      (Window->xrd_show_element_not_exists() && Num_elements_not_found>0) ||
//      (Window->xrd_show_valid() && Window->xrd_show_valid_good() && Value>=Window->xrd_maximum_threshold_correlation()) ||
//      (Window->xrd_show_valid() && Window->xrd_show_valid_medium() && Value>=Window->xrd_medium_threshold_correlation()) ||
//      (Window->xrd_show_valid() && Window->xrd_show_valid_bad() && Value<Window->xrd_medium_threshold_correlation())){

//    QColor Color_valid_good=Window->color_valid_good();
//    QColor Color_valid_medium=Window->color_valid_medium();
//    QColor Color_valid_bad=Window->color_valid_bad();

//    QString Text;
//    if (XRF_used==false) Text=Text+"NF/"; // Not file
//    else if (Num_elements_not_found>0) Text=Text+"NE/"; // Not Element

//    Text=Text+QString("%1%").arg(Value,2,10,QChar('0'));
//    Button->setText(Text);

//    switch (int(Window->mat_obs_vs_pdb_valid_type(Row,Col))){
//    case int(_data_xrd_ns::_valid_type::VALID_TYPE_GOOD):
//      Stylesheet = "background-color: "+Color_valid_good.name()+";";
//      break;
//    case int(_data_xrd_ns::_valid_type::VALID_TYPE_MEDIUM):
//      Stylesheet = "background-color: "+Color_valid_medium.name()+";";
//      break;
//    case int(_data_xrd_ns::_valid_type::VALID_TYPE_BAD):
//      Stylesheet = "background-color: "+Color_valid_bad.name()+";";
//      break;
//    }

//    if (Window->mat_obs_vs_pdb_selected_state(Row,True_col)==true) Button->setIcon(QIcon(Pixmap_valid));
//    else Button->setIcon(QIcon(Pixmap_invalid));
//  }
//  else{
//    Stylesheet= "background-color: #ffffff;";
//  }

//  if (Selected==true) Stylesheet=Stylesheet+_data_xrd_ns::SYTLE_PIGMENT_BUTTON_SELECTED;

//  Button->setStyleSheet(Stylesheet);
//}

//HEA
// Row and Col must be in the table index domain not the QTable index domain

void _table_xrd::check_data(int Row, int Col, QPushButton* Button,bool Selected)
{
  QString Stylesheet;

  if (Window->mat_xrd_obs_vs_pdb_data_show(Row,Col)==true){
    int True_col=Col;
    QColor Color_valid_good=Window->color_valid_good();
    QColor Color_valid_medium=Window->color_valid_medium();
    QColor Color_valid_bad=Window->color_valid_bad();
    int Value=int(roundf(powf(Window->mat_obs_vs_pdb_correlation_coefficient(Row,True_col),2)*100.0f)); // R^2
    QString Text;
    bool Apply_color=false;

    switch (Window->mat_xrd_obs_vs_pdb_data_class_type(Row,Col)){
      case _data_xrd_ns::_class_type::CLASS_TYPE_NO_XRF_FILE:
        if (Window->xrd_show_file_not_exists()){
          Text=Text+"NF/";
          Apply_color=true;
        }
        break;
      case _data_xrd_ns::_class_type::CLASS_TYPE_NO_ELEMENTS:
        if (Window->xrd_show_element_not_exists()){
          Text=Text+"NE/";
          Apply_color=true;
        }
        break;
      case _data_xrd_ns::_class_type::CLASS_TYPE_VALID:
        if (Window->xrd_show_valid()){
          Apply_color=true;
        }
        break;
    }

    if (Apply_color){
      Text=Text+QString("%1%").arg(Value,2,10,QChar('0'));

      switch (int(Window->mat_obs_vs_pdb_valid_type(Row,Col))){
      case int(_data_xrd_ns::_valid_type::VALID_TYPE_GOOD):
        Stylesheet = "background-color: "+Color_valid_good.name()+";";
        break;
      case int(_data_xrd_ns::_valid_type::VALID_TYPE_MEDIUM):
        Stylesheet = "background-color: "+Color_valid_medium.name()+";";
        break;
      case int(_data_xrd_ns::_valid_type::VALID_TYPE_BAD):
        Stylesheet = "background-color: "+Color_valid_bad.name()+";";
        break;
      }

      if (Window->mat_obs_vs_pdb_data_selected(Row,True_col)==true) Button->setIcon(QIcon(Pixmap_valid));
      else Button->setIcon(QIcon(Pixmap_invalid));
    }

    Button->setText(Text);
  }
  else{
    Stylesheet= "background-color: #ffffff;";
  }

  if (Selected==true) Stylesheet=_data_xrd_ns::SYTLE_PIGMENT_BUTTON_SELECTED+Stylesheet;

  Button->setStyleSheet(Stylesheet);
}

//HEA

void _table_xrd::create_table()
{
  int Num_valid_columns=Window->num_visible_columns_in_table();
  int Pos;
  int Col;

  for (int Row=rowCount()-1;Row>=0;Row--) removeRow(Row);

  int Num_spaces=6;

  setColumnCount(Num_valid_columns+1);
  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QStringList List1;
  QFont Font=font();
  QFontMetrics Font_metric(Font);
  QString String;
  int Width_char1;
  int Max_width=0;
  int Min_width=Font_metric.horizontalAdvance("0.000000000");

  // search for the largest name for rows
  for (unsigned int Row=0; Row<Row_names.size();Row++){
    String=QString::fromStdString(Row_names[Row]);
    Width_char1=Font_metric.horizontalAdvance(String);
    if (Width_char1>Max_width) Max_width=Width_char1;
  }
  setColumnWidth(0,Max_width+Num_spaces*3);

  List1.push_back("File");
  Pos=1;
  for (int i=0; i<Num_valid_columns;i++){
    String=QString::fromStdString(Col_names[Window->xrd_get_true_col(i)]);
    List1.push_back(String);

    Width_char1=Font_metric.horizontalAdvance(String);
    if (Width_char1<Min_width) Width_char1=Min_width;
    setColumnWidth(Pos,Width_char1+Num_spaces*3);
    Pos=Pos+1;
  }

  setHorizontalHeaderLabels(List1);

  //  horizontalHeader()->setStretchLastSection(true);

  //
  int Pos_first_valid_row;
  for (unsigned int Row=0;Row<Row_names.size();Row++){
    if (Row_names[Row]!="NULL"){
      Pos_first_valid_row=Row;
      break;
    }
  }

  Vec_valid_rows.resize(Row_names.size());

  for (unsigned int Row=0;Row<Row_names.size();Row++){
    insertRow(Row);

    // insert the name of the row
    QPushButton* Button=new QPushButton;
    Button->setFont(Font);
    Button->setStyleSheet(_data_xrd_ns::SYTLE_FILE_BUTTON_UNSELECTED);
    Button->setText(QString::fromStdString(Row_names[Row]));
    QObject::connect(Button, &QPushButton::clicked, [=]() {
      int rowIndex = indexAt(Button->mapTo(viewport(), QPoint(0, 0))).row();
      int colIndex = indexAt(Button->mapTo(viewport(), QPoint(0, 0))).column();
      button_clicked_slot(rowIndex,colIndex);
    });
    setCellWidget(Row,0,Button);

    if (Row_names[Row]!="NULL"){
      Vec_valid_rows[Row]=true;

      // insert the rest of values
      Pos=1;
      for (int j=0;j<Num_valid_columns;j++){
        QPushButton* Button=new QPushButton;
        Button->setFont(Font);
        Col=Window->xrd_get_true_col(j);
        //
        check_data(Row,Col,Button,false);

        // connect the button
        QObject::connect(Button, &QPushButton::clicked, [=]() {
          int rowIndex = indexAt(Button->mapTo(viewport(), QPoint(0, 0))).row();
          int colIndex = indexAt(Button->mapTo(viewport(), QPoint(0, 0))).column();
          button_clicked_slot(rowIndex,colIndex);
        });

        setCellWidget(Row,Pos,Button);

        Pos=Pos+1;
      }
    }
    else Vec_valid_rows[Row]=false;
  }

  // initialize
  Previous_row=Pos_first_valid_row;
  Previous_col=0;
  Current_row=Pos_first_valid_row;
  Current_col=0;

  // select the first one
  Window->xrd_selected_row_in_table(Pos_first_valid_row);
  Window->xrd_selected_col_in_table(-1);
  update_table(Pos_first_valid_row,0);
  QPushButton* Pushbutton=static_cast<QPushButton*>(cellWidget(Pos_first_valid_row,0));
  Pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_FILE_BUTTON_SELECTED+"background-color: "+_common_ns::SELECTED_COLOR.name());
}


//HEA

void _table_xrd::set_data(std::vector<std::string> Row_names1, std::vector<std::string> Col_names1)
{
  Row_names=Row_names1;
  Col_names=Col_names1;

  create_table();
}

//HEA

//void _table_xrd::cell_clicked_slot(int Row,int Col)
//{
//  Previous_row=Current_row;
//  Previous_col=Current_col;

//  Current_row=Row;
//  Current_col=Col;

//  Window->xrd_selected_row_in_table(Row);
//  if (Col==0) Window->xrd_selected_col_in_table(-1);
//  else Window->xrd_selected_col_in_table(Col-1);

//  if (Vec_valid_rows[Row]==true) Window->xrd_update_info_and_chart_of_selected_table_cell();
//}

//HEA


void _table_xrd::update_table(int Row,int Col)
{
  int True_previous_col=Window->xrd_get_true_col(Previous_col-1);
  int True_current_col=Window->xrd_get_true_col(Current_col-1);

  // change all the row
  // unselect
  QPushButton* Current_pushbutton;
  if (Previous_row!=Current_row){
    for (int Col=0;Col<columnCount();Col++){
      Current_pushbutton=static_cast<QPushButton*>(cellWidget(Previous_row,Col));
      if (Col==0){
        Current_pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_FILE_BUTTON_UNSELECTED+"background-color: #ffffff;");
      }
      else{
        // convert to the true col but taking into account that in QTable the index 1 is related to the index of the 0 position
        check_data(Previous_row,Window->xrd_get_true_col(Col-1),Current_pushbutton,false);
      }
    }
  }

  // select
  for (int Col=0;Col<columnCount();Col++){
    Current_pushbutton=static_cast<QPushButton*>(cellWidget(Current_row,Col));
    if (Col==0){
      Current_pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_FILE_BUTTON_SELECTED+"background-color: #ffffff;");
    }
    else{
      // convert to the true col but taking into account that in QTable the index 1 is related to the index of the 0 position
      check_data(Current_row,Window->xrd_get_true_col(Col-1),Current_pushbutton,true);
    }
  }

  // check if there is a change in the selecte cell
  QPushButton* Previous_pushbutton=static_cast<QPushButton*>(cellWidget(Previous_row,Previous_col));
  Current_pushbutton=static_cast<QPushButton*>(cellWidget(Current_row,Current_col));
  if (Previous_row==Current_row && Previous_col==Current_col){
    // no change -> change the Selected state
    if (Current_col>0){
      // take into account only the correlation values not the names of the files
      bool Result=Window->mat_obs_vs_pdb_data_selected(Current_row,True_current_col);

      Window->mat_obs_vs_pdb_flip_selected_state(Current_row,True_current_col);

      Result=Window->mat_obs_vs_pdb_data_selected(Current_row,True_current_col);

      if (Window->mat_obs_vs_pdb_data_selected(Current_row,True_current_col)==true) Current_pushbutton->setIcon(QIcon(Pixmap_valid));
      else Current_pushbutton->setIcon(QIcon(Pixmap_invalid));

      Current_pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_PIGMENT_BUTTON_SELECTED+"background-color: "+_common_ns::SELECTED_COLOR.name());
    }
  }
  else{
    // change between cells. The new one must be show as selected and the previous one must be show with its color
    if (Current_col>0){
      // Select -> change to correlation cell
      Current_pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_PIGMENT_BUTTON_SELECTED+"background-color: "+_common_ns::SELECTED_COLOR.name());

      // unselect
      if (Previous_col==0){
        // from file name cell to correlation cell
        if (Previous_row==Current_row){
          Previous_pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_FILE_BUTTON_SELECTED+"background-color: #ffffff;");
        }
        else{
          Previous_pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_FILE_BUTTON_UNSELECTED+"background-color: #ffffff;");
        }
      }
      else{
        // from correlation cell to correlation cell
        if (Previous_row==Current_row){
          check_data(Previous_row,True_previous_col,Previous_pushbutton,true);
        }
        else{
          check_data(Previous_row,True_previous_col,Previous_pushbutton,false);
        }
      }
    }
    else{
      // change to file name cell
      // Select File
      Current_pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_FILE_BUTTON_SELECTED+"background-color: "+_common_ns::SELECTED_COLOR.name());

      // unselect
      if (Previous_col==0){
        // from file name cell to file name cell
        Previous_pushbutton->setStyleSheet(_data_xrd_ns::SYTLE_FILE_BUTTON_UNSELECTED+"background-color: #ffffff;");
      }
      else{
        // from correlation cell to file name cell
        if (Previous_row==Current_row){
          check_data(Previous_row,True_previous_col,Previous_pushbutton,true);
        }
        else{
          check_data(Previous_row,True_previous_col,Previous_pushbutton,false);
        }
      }
    }
  }
}

//HEA

void _table_xrd::button_clicked_slot(int Row,int Col)
{
  if (Vec_valid_rows[Row]==true){
    Previous_row=Current_row;
    Previous_col=Current_col;

    Current_row=Row;
    Current_col=Col;

    update_table(Row,Col);


    Window->xrd_selected_row_in_table(Row);
    if (Col==0) Window->xrd_selected_col_in_table(-1);
    else Window->xrd_selected_col_in_table(Col-1);

    Window->xrd_update_info_and_chart_of_selected_table_cell();
  }
}


//HEA

//void _table_xrd::update_cells_font()
//{
//  QFont Font(font());
//  QPushButton* Current_pushbutton;

//  for(int Row=0;Row<rowCount();Row++){
//    for (int Col=0;Col<columnCount();Col++){
//      Current_pushbutton=static_cast<QPushButton*>(cellWidget(Row,Col));
//      if (Current_pushbutton!=nullptr) Current_pushbutton->setFont(Font);
//    }
//  }
//}

//HEA

void _table_xrd::wheelEvent(QWheelEvent *Event)
{
  // Check if the Shift key is being held down
  if (Event->modifiers() & Qt::ControlModifier) {
    // Get the delta value to determine the direction of the mouse wheel
    int Delta = Event->angleDelta().y();
    QFont Font(font());
    int Font_size=Font.pointSize();

    // Depending on the direction of the wheel, perform some action
    if (Delta > 0) {
      Font_size=Font_size+1;
      if (Font_size>40) Font_size=40;
    }
    else if (Delta < 0){
      Font_size=Font_size-1;
      if (Font_size<6) Font_size=6;
    }

    Font.setPointSize(Font_size);
    setFont(Font);

    create_table();

//    update_cells_font();
  }

  // Call the base class implementation to allow default behavior
//  QTableWidget::wheelEvent(Event);
}

//HEA

void _table_xrd::mousePressEvent(QMouseEvent* Event)
{
//  if (event->button() == Qt::LeftButton){
//    // Aquí puedes poner el código para manejar el clic del botón izquierdo del ratón
//    setText("Botón Izquierdo");
//  }
//  else if (event->button() == Qt::RightButton){
//    // Aquí puedes poner el código para manejar el clic del botón derecho del ratón
//    setText("Botón Derecho");
//  }

//  // Llamar al evento base para que el botón se comporte normalmente
//  QPushButton::mousePressEvent(Event);
}

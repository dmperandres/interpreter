//LIC

#include "w_xrd_pdb_options.h"
#include "window_interpreter.h"

_w_xrd_pdb_options::_w_xrd_pdb_options(_window_interpreter *Window1, QStringList &Folders_short_names):QDialog((QWidget*)Window1)
{
  Window=Window1;

//  //
//  QGroupBox *Groupbox_xrd_pdb_options=new QGroupBox;
//  Groupbox_xrd_pdb_options->setTitle("XRD PDB options");

//  QVBoxLayout *Verticalbox_xrd_pdb_options=new QVBoxLayout;
//  QGridLayout *Grid_xrd_pdb_options=new QGridLayout;

  // for the list
  QGroupBox *Groupbox_xrd_pdb_options_list=new QGroupBox;
  Groupbox_xrd_pdb_options_list->setTitle("PDB folders");

  QVBoxLayout *Verticalbox_xrd_pdb_options_list=new QVBoxLayout;

  List_xrd_pdbs=new QListWidget;
  List_xrd_pdbs->setSelectionMode(QAbstractItemView::MultiSelection);

  List_xrd_pdbs->addItems(Folders_short_names);

  Verticalbox_xrd_pdb_options_list->addWidget(List_xrd_pdbs);
  Groupbox_xrd_pdb_options_list->setLayout(Verticalbox_xrd_pdb_options_list);

  // for the Tube type
//  QGroupBox *Groupbox_xrd_pdb_options_tube_type=new QGroupBox;
//  Groupbox_xrd_pdb_options_tube_type->setTitle("OBS tube");

//  QVBoxLayout *Verticalbox_xrd_pdb_options_tube_type=new QVBoxLayout;

//  Combobox_tube_type=new QComboBox;
//  for (unsigned int i=0;i<_data_xrd_ns::Vec_tube_type_names.size();i++){
//    Combobox_tube_type->addItem(QString::fromStdString(_data_xrd_ns::Vec_tube_type_names[i]));
//  }
//  Combobox_tube_type->setCurrentIndex(0);

//  Verticalbox_xrd_pdb_options_tube_type->addWidget(Combobox_tube_type);
//  Groupbox_xrd_pdb_options_tube_type->setLayout(Verticalbox_xrd_pdb_options_tube_type);

  // now the PDB folders list and the Tube

//  Verticalbox_xrd_pdb_options->addWidget(Groupbox_xrd_pdb_options_list);
//  Verticalbox_xrd_pdb_options->addWidget(Groupbox_xrd_pdb_options_tube_type);
//  Groupbox_xrd_pdb_options->setLayout(Verticalbox_xrd_pdb_options);

//  //
//  QHBoxLayout *Horizontal1=new QHBoxLayout;

////  Horizontal1->addWidget(Groupbox_type_input);
//  Horizontal1->addWidget(Groupbox_xrd_pdb_options);

//  QWidget *Widged_p=new QWidget;

//  Widged_p->setLayout(Horizontal1);

  // control buttons
//  QPushButton *Button_apply = new QPushButton(tr("Apply"));
//  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

  QPushButton *Button_ok = new QPushButton(tr("OK"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
//  Horizontal_layout->addWidget(Button_apply);
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Groupbox_xrd_pdb_options_list);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("XRD PDB options");
}

//HEA

//void _w_xrd_pdb_options::xrd_use_pdb_spectral_Cu_slot(int State)
//{
//  if (State==Qt::Unchecked){
//    if (Window->use_xrd_pdb_spectral_Co()==false && Window->use_xrd_pdb_astm_Cu()==false){
//      Checkbox_use_xrd_pdb_spectral_Cu->blockSignals(true);
//      Checkbox_use_xrd_pdb_spectral_Cu->setCheckState(Qt::Checked);
//      Checkbox_use_xrd_pdb_spectral_Cu->blockSignals(false);
//    }
//    else Window->use_xrd_pdb_spectral_Cu(false);
//  }
//  else Window->use_xrd_pdb_spectral_Cu(true);
//}

//HEA

//void _w_xrd_pdb_options::xrd_use_pdb_spectral_Co_slot(int State)
//{
//  if (State==Qt::Unchecked){
//    if (Window->use_xrd_pdb_spectral_Cu()==false && Window->use_xrd_pdb_astm_Cu()==false){
//      Checkbox_use_xrd_pdb_spectral_Co->blockSignals(true);
//      Checkbox_use_xrd_pdb_spectral_Co->setCheckState(Qt::Checked);
//      Checkbox_use_xrd_pdb_spectral_Co->blockSignals(false);
//    }
//    else Window->use_xrd_pdb_spectral_Co(false);
//  }
//  else Window->use_xrd_pdb_spectral_Co(true);
//}

//HEA

//void _w_xrd_pdb_options::xrd_use_pdb_astm_Cu_slot(int State)
//{
//  if (State==Qt::Unchecked){
//    if (Window->use_xrd_pdb_spectral_Cu()==false && Window->use_xrd_pdb_spectral_Co()==false){
//      Checkbox_use_xrd_pdb_astm_Cu->blockSignals(true);
//      Checkbox_use_xrd_pdb_astm_Cu->setCheckState(Qt::Checked);
//      Checkbox_use_xrd_pdb_astm_Cu->blockSignals(false);
//    }
//    else Window->use_xrd_pdb_astm_Cu(false);
//  }
//  else Window->use_xrd_pdb_astm_Cu(true);

//}

//HEA

void _w_xrd_pdb_options::apply_slot()
{
  QList<QListWidgetItem*> List_selected=List_xrd_pdbs->selectedItems();
  std::vector<std::string> Vec_selected_folders;

  if (List_selected.size()>0){
    for (int i=0;i<List_selected.size();i++){
      Vec_selected_folders.push_back(List_selected[i]->text().toStdString());
    }

    Window->xrd_selected_pdb_folders(Vec_selected_folders);
//    Window->tube_type(_data_xrd_ns::_tube_type(Combobox_tube_type->currentIndex()));

    close();
  }
  else{
    QMessageBox::information(Window, Window->tr("Information"),Window->tr("Please, select one folder at least"));
  }
}

//HEA

//void _w_xrd_pdb_options::close_slot()
//{
//  Window->options_parameters(Button_color_xrd_file_not_exists->color(), Button_color_xrd_element_not_exists->color(), Button_color_xrd_valid_good->color(),Button_color_xrd_valid_medium->color(),Button_color_xrd_valid_bad->color(),Button_color_xrd_font->color());

//  close();
//}

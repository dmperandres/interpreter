//LIC

#include "window_main.h"
#include "window_interpreter.h"


//static int Counter=0;

float Two_theta_start=29.0f;
float Position_show=int((Two_theta_start-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA);
int Num_positions_show=10;

//HEA

_window_interpreter::_window_interpreter(_window_main *Window_main1)
{
#ifdef DEBUG_XML
  std::cout << "en _window_interpreter " << __LINE__ << std::endl;
#endif

  Window_main=Window_main1;

  // the dimensions of the main window
  QRect Screen_size = QApplication::primaryScreen()->geometry();
  Screen_width=Screen_size.width();
  Screen_height=Screen_size.height();

  // the default font size
  QFont Font=QApplication::font();
  UI_font_size=Font.pointSize();

  XRF_title_font_size=UI_font_size;
  XRF_legend_font_size=UI_font_size;

  XRD_title_font_size=UI_font_size;
  XRD_legend_font_size=UI_font_size;

  create_widgets();

  // Menu
  Load_project = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Load project data"), this);
//  Load_project->setShortcuts(QKeySequence::Open);
  Load_project->setToolTip(tr("Load project data"));
  connect(Load_project, SIGNAL(triggered()), this, SLOT(load_project_data_slot()));

  Save_project = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save interpreted data"), this);
  Save_project->setEnabled(false);
//  Save_project->setShortcuts(QKeySequence::Save);
  Save_project->setToolTip(tr("Save project data"));
  connect(Save_project, SIGNAL(triggered()), this, SLOT(save_project_data_slot()));

  // for user selections
//  Load_user_selections = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Load user selections"), this);
//  Load_user_selections->setEnabled(false);
//  Load_user_selections->setToolTip(tr("Load user selections"));
//  connect(Load_user_selections, SIGNAL(triggered()), this, SLOT(load_user_selections_slot()));

//  Save_user_selections = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save user_selections"), this);
//  Save_user_selections->setEnabled(false);
////  Save_user_selections->setShortcuts(QKeySequence::Save);
//  Save_user_selections->setToolTip(tr("Save user_selections"));
//  connect(Save_user_selections, SIGNAL(triggered()), this, SLOT(save_user_selections_slot()));

  Save_one_graph = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save selected graph"), this);
  Save_one_graph->setEnabled(false);
//  Save_one_graph->setShortcuts(QKeySequence::Save);
  Save_one_graph->setToolTip(tr("Save the selected graph"));
  connect(Save_one_graph, SIGNAL(triggered()), this, SLOT(save_one_graph_slot()));

  Save_all_graphs = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save all graphs"), this);
  Save_all_graphs->setEnabled(false);
//  Save_all_graphs>setShortcuts(QKeySequence::Save);
  Save_all_graphs->setToolTip(tr("Save all graphs"));
  connect(Save_all_graphs, SIGNAL(triggered()), this, SLOT(save_all_graphs_slot()));

#ifdef XRD_ACTIVE
//  QAction_xrd_save_correlation_data_csv = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save XRD correlation table (CSV)"), this);
//  QAction_xrd_save_correlation_data_csv->setEnabled(false);
//  QAction_xrd_save_correlation_data_csv->setToolTip(tr("Save XRD correlation table"));
//  connect(QAction_xrd_save_correlation_data_csv, SIGNAL(triggered()), this, SLOT(xrd_save_correlation_data_csv_slot()));
#endif


//  QAction_xrf_save_process_info_csv = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save process info of selected XRF item"), this);
//  QAction_xrf_save_process_info_csv->setEnabled(false);
//  QAction_xrf_save_process_info_csv->setToolTip(tr("Save process info of selected XRF item"));
//  connect(QAction_xrf_save_process_info_csv, SIGNAL(triggered()), this, SLOT(xrf_save_process_info_csv_slot()));

#ifdef XRD_ACTIVE
//  QAction_xrd_save_process_info_csv = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save process info of selected XRD item (CSV)"), this);
//  QAction_xrd_save_process_info_csv->setEnabled(false);
//  QAction_xrd_save_process_info_csv->setToolTip(tr("Save process info of selected XRD item"));
//  connect(QAction_xrd_save_process_info_csv, SIGNAL(triggered()), this, SLOT(xrd_save_process_info_csv_slot()));
#endif

  Options = new QAction(tr("Options"), this);
//  Options->setShortcuts(QKeySequence::Save);
  Options->setToolTip(tr("Save data"));
  connect(Options, SIGNAL(triggered()), this, SLOT(options_slot()));

  //
  Action_pdb_mode = new QAction(tr("PDB mode"), this);
  Action_pdb_mode->setCheckable(true);
  Action_pdb_mode->setChecked(false);
  connect(Action_pdb_mode, SIGNAL(triggered()), this, SLOT(pdb_mode_slot()));

  //
  Action_save_pdb = new QAction(tr("Save selected PDB"), this);
  Action_save_pdb->setEnabled(false);
  connect(Action_save_pdb, SIGNAL(triggered()), this, SLOT(save_pdb_slot()));

  //
  QAction *Exit = new QAction(QIcon(":/common/icons/exit.png"), tr("&Exit..."), this);
  Exit->setShortcut(tr("Ctrl+Q"));
  Exit->setToolTip(tr("Exit the application"));
  connect(Exit, SIGNAL(triggered()), Window_main, SLOT(close()));

  // actions for programs
//  QAction *Positions = new QAction(tr("Positions"), this);
//  connect(Positions,SIGNAL(triggered()),this,SLOT(program_positions_slot()));

//  QAction *Maplab = new QAction(tr("MapLab"), this);
//  connect(Maplab,SIGNAL(triggered()),this,SLOT(program_maplab_slot()));


  // actions for file menu
#ifndef UNIFIED
  QAction *Help_info = new QAction(tr("&Info"), this);
  connect(Help_info, SIGNAL(triggered()), this, SLOT(info_slot()));
#endif

  // menus
  QMenu *File_menu=menuBar()->addMenu(tr("&File"));
  File_menu->addAction(Load_project);
  File_menu->addAction(Save_project);
  File_menu->addSeparator();
//  File_menu->addAction(Load_user_selections);
//  File_menu->addAction(Save_user_selections);
  File_menu->addSeparator();
  File_menu->addAction(Save_one_graph);
  File_menu->addAction(Save_all_graphs);

//  File_menu->addSeparator();
//  File_menu->addAction(QAction_xrd_save_correlation_data_csv);

//  File_menu->addSeparator();
//  File_menu->addAction(QAction_xrd_save_process_info_csv);


  File_menu->addSeparator();
  File_menu->addAction(Options);

  File_menu->addSeparator();
  File_menu->addAction(Action_pdb_mode);
  File_menu->addAction(Action_save_pdb);

  File_menu->addSeparator();
  File_menu->addAction(Exit);

  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

//  QMenu *Menu_programs=menuBar()->addMenu(tr("Programs"));
//  Menu_programs->addAction(Positions);
//  Menu_programs->addAction(Maplab);


  // View
  View_split_screen = new QAction(tr("Split screen"), this);
  View_split_screen->setCheckable(true);
  View_split_screen->setChecked(true);
  connect(View_split_screen, SIGNAL(triggered()), this, SLOT(split_screen_slot()));

  Menu_view=menuBar()->addMenu(tr("&View"));
  Menu_view->addAction(View_split_screen);

  Menu_view->setEnabled(false);

#ifndef UNIFIED
  QMenu *Menu_help=menuBar()->addMenu(tr("&Help"));
  Menu_help->addAction(Help_info);

  Menu_help->setAttribute(Qt::WA_AlwaysShowToolTips);

  setWindowTitle(_window_interpreter_ns::Program_name);

//  resize(Screen_size.width()*_window_interpreter_interpreter_interpreter_ns::SCREEN_WIDTH_FACTOR,Screen_size.height()*_window_interpreter_interpreter_interpreter_ns::SCREEN_HEIGHT_FACTOR);
  resize(Screen_width/2,Screen_height/2);
#endif
}

//HEA

_window_interpreter::~_window_interpreter()
{
#ifdef DEBUG_XML
  std::cout << "terminando window" <<endl;
#endif
  save_settings();
}

//HEA

//void _window_interpreter::ui_font_size(int Size)
//{
//  UI_font_size=Size;

//  QFont Font=QApplication::font();
//  Font.setPointSize(Size);
////  QApplication::setFont(Font);
//  setFont(Font);

//  menuBar()->setFont(Font);

//  save_settings();
//}

//HEA

//void _window_interpreter::pass_ui_font_size(int UI_font_size1)
//{
//  Window_main->ui_font_size(UI_font_size1);
//}

//HEA

void _window_interpreter::read_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_interpreter_interpreter_interpreter_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  settings.beginGroup("Interpreter");
#ifdef XRD_ACTIVE
    settings.beginGroup("XRD");

      settings.beginGroup("Colors");
        XRD_color_file_not_exists=settings.value("FileNotExist",_data_xrd_ns::XRD_COLOR_FILE_NOT_EXISTS).value<QColor>();
        XRD_color_element_not_exists=settings.value("ElementNotExist",_data_xrd_ns::XRD_COLOR_ELEMENT_NOT_EXISTS).value<QColor>();
        XRD_color_valid_good=settings.value("ValidGood",_data_xrd_ns::XRD_COLOR_VALID_GOOD).value<QColor>();
//        Color_valid_medium=settings.value("ValidMedium",_data_xrd_ns::COLOR_VALID_MEDIUM_DEFAULT).value<QColor>();
//        Color_valid_bad=settings.value("ValidBad",_data_xrd_ns::COLOR_VALID_BAD_DEFAULT).value<QColor>();
//        Color_font=settings.value("Font",_data_xrd_ns::COLOR_FONT_DEFAULT).value<QColor>();
      settings.endGroup();

//      settings.beginGroup("ShowColumns");
//        XRD_show_file_not_exists=settings.value("FileNotExist",_data_xrd_ns::SHOW_FILE_NOT_EXISTS_DEFAULT).toBool();
//        XRD_show_element_not_exists=settings.value("ElementNotExist",_data_xrd_ns::SHOW_ELEMENT_NOT_EXISTS_DEFAULT).toBool();
//        XRD_show_valid=settings.value("Valid",_data_xrd_ns::SHOW_VALID_DEFAULT).toBool();
//        XRD_show_valid_good=settings.value("ValidGood",_data_xrd_ns::SHOW_VALID_GOOD_DEFAULT).toBool();
//        XRD_show_valid_medium=settings.value("ValidMedium",_data_xrd_ns::SHOW_VALID_MEDIUM_DEFAULT).toBool();
//        XRD_show_valid_bad=settings.value("ValidBad",_data_xrd_ns::SHOW_VALID_BAD_DEFAULT).toBool();
//      settings.endGroup();

    settings.endGroup();
#endif
  settings.endGroup();

//  settings.beginGroup("General");
//    Window_size=settings.value("size", QSize(_common_ns::WINDOW_WIDTH_DEFAULT,_common_ns::WINDOW_HEIGHT_DEFAULT)).toSize();
//    Window_position=settings.value("pos", QPoint(_common_ns::WINDOW_X_POS_DEFAULT,_common_ns::WINDOW_Y_POS_DEFAULT)).toPoint();
//    UI_font_size=settings.value("UIFontSize",_common_ns::UI_FONT_SIZE_DEFAULT).toInt();
//  settings.endGroup();
}

//HEA

void _window_interpreter::save_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_interpreter_interpreter_interpreter_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  settings.beginGroup("Interpreter");
#ifdef XRD_ACTIVE
    settings.beginGroup("XRD");
      settings.beginGroup("Colors");
        settings.setValue("FileNotExist",XRD_color_file_not_exists);
        settings.setValue("ElementNotExist",XRD_color_element_not_exists);
        settings.setValue("ValidGood",XRD_color_valid_good);
//        settings.setValue("ValidMedium",Color_valid_medium);
//        settings.setValue("ValidBad",Color_valid_bad);
//        settings.setValue("Font",Color_font);
      settings.endGroup();

//      settings.beginGroup("ShowColumns");
//        settings.setValue("FileNotExist",XRD_show_file_not_exists);
//        settings.setValue("ElementNotExist",XRD_show_element_not_exists);
//        settings.setValue("Valid",XRD_show_valid);
//        settings.setValue("Validgood",XRD_show_valid_good);
//        settings.setValue("ValidMedium",XRD_show_valid_medium);
//        settings.setValue("ValidBad",XRD_show_valid_bad);
//      settings.endGroup();
    settings.endGroup();
#endif
  settings.endGroup();

//  settings.beginGroup("General");
//    settings.setValue("UIFontSize",UI_font_size);
//  settings.endGroup();
}

//HEA

//void _window_interpreter::closeEvent(QCloseEvent *Event)
//{
//  save_settings();
//  Event->accept();
//}

//HEA

bool _window_interpreter::xrf_load_obs_data()
{
  std::vector<float> Values;
  float Step;
  std::string Error;

  // check that there are a xrd folder
  if (QDir(Project_dir+"/xrf").exists()){
    // check that there are a xrd/raw folder
    if (QDir(Project_dir+"/xrf/raw").exists()){
      // check if there are files

      QDir Directory(Project_dir+"/xrf/raw/");
      std::string Dir_xrf=Directory.absolutePath().toStdString();

      QStringList Files_xrf;

      if (XRF_artax_files_exist==true){
        Files_xrf = Directory.entryList(QStringList() << "*.txt",QDir::Files);
      }
      else{
        Files_xrf = Directory.entryList(QStringList() << "*.xy",QDir::Files);
      }

      Files_xrf.sort();

      if (Files_xrf.size()>0){
        // check the maximum index for the name of a file
        int Max_position=-1;
        int Pos;
        int File_pos;

        foreach(QString File_name, Files_xrf){
          QFileInfo File_info(File_name);
          QString Base_name=File_info.baseName();
          // Pos=Base_name.indexOf('_');
          File_pos=Base_name.left(3).toInt();
          if (File_pos>Max_position) Max_position=File_pos;
        }

        // intitalize to the number of positions
        Vec_xrf_obs_data.clear();
        Vec_xrf_obs_data.resize(Max_position);

        foreach(QString File_name, Files_xrf){
          QFileInfo File_info(File_name);
          QString Base_name=File_info.baseName();
          QString Extension=File_info.suffix();

          // Pos=Base_name.indexOf('_');
          File_pos=Base_name.left(3).toInt()-1;

          std::string Short_name=File_info.baseName().toStdString();
          std::string Long_name=Dir_xrf+"/"+File_info.fileName().toStdString();

          if (Extension.toUpper()=="TXT"){
            _file_xrf_artax File_xrf_artax;
            bool Opened=File_xrf_artax.open(Long_name,_file_io::_mode::MODE_READ);
            if (Opened){
              if (File_xrf_artax.read(Values,Step,Error)==true){
                File_xrf_artax.close();

                Vec_xrf_obs_data[File_pos].File_name=Short_name;
                Vec_xrf_obs_data[File_pos].Position=File_pos;
                Vec_xrf_obs_data[File_pos].Step=Step;
                Vec_xrf_obs_data[File_pos].Vec_values=Values;
              }
              else{
                File_xrf_artax.close();

                QMessageBox::critical(this, tr("Error"),QString::fromStdString(Error));
                QApplication::quit();
                exit(-1);
              }
            }
            else{
              QMessageBox::warning(this, tr("Warning"),"The file "+File_name+" cannot be opened");

              File_xrf_artax.close();
              std::fill(Values.begin(),Values.end(),0.0f);

              Vec_xrf_obs_data[File_pos].File_name=Short_name;
              Vec_xrf_obs_data[File_pos].Position=File_pos;
              Vec_xrf_obs_data[File_pos].Step=Step;
              Vec_xrf_obs_data[File_pos].Vec_values=Values;
            }
          }

          if (Extension.toUpper()=="XY"){
            _file_xrf_xy File_xrf_xy;
            float Step;
            bool Opened=File_xrf_xy.open(Long_name,_file_io::_mode::MODE_READ);
            if (Opened){
              if (File_xrf_xy.read(Values,Step,Error)==true){
                File_xrf_xy.close();

                Vec_xrf_obs_data[File_pos].File_name=Short_name;
                Vec_xrf_obs_data[File_pos].Position=File_pos;
                Vec_xrf_obs_data[File_pos].Step=Step;
                Vec_xrf_obs_data[File_pos].Vec_values=Values;
              }
              else{
                File_xrf_xy.close();

                QMessageBox::critical(this, tr("Error"),QString::fromStdString(Error));
                QApplication::quit();
                exit(-1);
              }
            }
            else{
              QMessageBox::warning(this, tr("Warning"),"The file "+File_name+" cannot be opened");

              File_xrf_xy.close();
              std::fill(Values.begin(),Values.end(),0.0f);

              Vec_xrf_obs_data[File_pos].File_name=Short_name;
              Vec_xrf_obs_data[File_pos].Position=File_pos;
              Vec_xrf_obs_data[File_pos].Step=Step;
              Vec_xrf_obs_data[File_pos].Vec_values=Values;
            }
          }
        }

        // search for the first valid position
        for (Selected_file_position=0;Selected_file_position<int(Vec_xrf_obs_data.size());Selected_file_position++){
          if (Vec_xrf_obs_data[Selected_file_position].Position!=-1) break;
        }
        // this is to get data for the cases where the file is null
        XRF_good_file_position=Selected_file_position;

        return true;
      }
      else{
        QMessageBox::critical(this, tr("Error"),tr("There are not '.txt' files in 'xrf/raw' folder"));
//        QApplication::quit();
//        exit(-1);
        return false;
      }
    }
    else{
      QMessageBox::critical(this, tr("Error"),tr("There is not 'xrf/raw/' folder"));
      return false;
    }
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There is not 'xrf' folder"));
    return false;
  }
}

//HEA

#ifdef XRD_ACTIVE
bool _window_interpreter::xrd_load_obs_data()
{
//  _file_xrd_obs_uxd File_xrd_obs_uxd;
//  _file_xrd_obs_plv File_xrd_obs_plv;
//  _file_xrd_obs_txt File_xrd_obs_txt;
  std::string Error;
  std::string Line;
//  std::string File_name;
  std::vector<std::string> Vec_names;
  std::vector<std::string> Vec_formulas;
  std::vector<std::string> Vec_elements;
  _vertex3f Color;
  int Area=0;
  std::vector<_common_ns::_peak_data> Peaks;

  // check that there are a xrd folder
  if (QDir(Project_dir+"/xrd").exists()){
    // check that there are a xrd/raw folder
    if (QDir(Project_dir+"/xrd/raw").exists()){
      // check if there are files
      QDir Directory(Project_dir+"/xrd/raw/");
      std::string Dir=Directory.absolutePath().toStdString();

      QStringList Files_xrd;
      if (XRD_uxd_files_exist==true){
        Files_xrd = Directory.entryList(QStringList() << "*.uxd",QDir::Files);
      }
      else{
        Files_xrd = Directory.entryList(QStringList() << "*.plv",QDir::Files);
      }

//      Files_xrd << Directory.entryList(QStringList() << "*.txt",QDir::Files);
      Files_xrd.sort();

      if (Files_xrd.size()>0){
        // check the maximum index for the name of a file
        int Max_position=-1;
        int Pos;
        int File_pos;

        foreach(QString File_name, Files_xrd){
          QFileInfo File_info(File_name);
          QString Base_name=File_info.baseName();
          // Pos=Base_name.indexOf('_');
          File_pos=Base_name.left(3).toInt();
          if (File_pos>Max_position) Max_position=File_pos;
        }

        if (Max_position==0){
          QMessageBox::warning(this, tr("Warning"),tr("The numbers of XRD OBS files are wrong"));
        }

        Vec_xrd_obs_data.clear();
        Vec_xrd_obs_data.resize(Max_position);

        foreach(QString File_name, Files_xrd){
          std::vector<float> Values;
          std::vector<_data_xrd_ns::_xrd_order_data> Vec_order;
          QFileInfo File_info(File_name);
          QString Base_name=File_info.baseName();
          QString Extension=File_info.suffix();

          // Pos=Base_name.indexOf('_');
          File_pos=Base_name.left(3).toInt()-1;

          std::string Short_name=File_info.baseName().toStdString();
          std::string Long_name=Dir+"/"+File_info.fileName().toStdString();

          // UXD
          if (Extension=="uxd"){
            _file_xrd_obs_uxd File_xrd_obs_uxd;
            bool Opened=File_xrd_obs_uxd.open(Long_name,_file_io::_mode::MODE_READ);
            if (Opened){
              if (File_xrd_obs_uxd.read(Values,Error)==true){
                File_xrd_obs_uxd.close();

                Vec_xrd_obs_data[File_pos]={Short_name,File_pos,Values,Values,Values,Values,Area,Peaks,Vec_order};
              }
              else{
                File_xrd_obs_uxd.close();

                QMessageBox::critical(this, tr("Error"),QString::fromStdString(Error));
                QApplication::quit();
                exit(-1);
              }
            }
            else{
              QMessageBox::warning(this, tr("Warning"),"The file "+File_name+" cannot be opened");

              File_xrd_obs_uxd.close();
              std::fill(Values.begin(),Values.end(),0.0f);
              Vec_xrd_obs_data[File_pos]={Short_name,File_pos,Values,Values,Values,Values,Area,Peaks,Vec_order};
            }
          }

          if (Extension=="plv"){
            _file_xrd_obs_plv File_xrd_obs_plv;
            bool Opened=File_xrd_obs_plv.open(Long_name,_file_io::_mode::MODE_READ);
            if (Opened){
              if (File_xrd_obs_plv.read(Values,Error)==true){
                File_xrd_obs_plv.close();

                Vec_xrd_obs_data[File_pos]={Short_name,File_pos,Values,Values,Values,Values,Area,Peaks,Vec_order};
              }
              else{
                File_xrd_obs_plv.close();

                QMessageBox::critical(this, tr("Error"),QString::fromStdString(Error));
                QApplication::quit();
                exit(-1);
              }
            }
            else{
              QMessageBox::warning(this, tr("Warning"),"The file "+File_name+" cannot be opened");

              File_xrd_obs_plv.close();
              std::fill(Values.begin(),Values.end(),0.0f);
              Vec_xrd_obs_data[File_pos]={Short_name,File_pos,Values,Values,Values,Values,Area,Peaks,Vec_order};
            }
          }
        }

        return true;
      }
      else{
        QMessageBox::warning(this, tr("Warning"),tr("There are not '.uxd' files in 'xrd/raw' folder"));
//        QApplication::quit();
//        exit(-1);
      }
    }
    else{
      QMessageBox::warning(this, tr("Warning"),tr("There is not 'xrd/raw' folder"));
//      QApplication::quit();
//      exit(-1);
    }
  }
  else{
    QMessageBox::warning(this, tr("Warning"),tr("There is not 'xrd' folder"));
//    QApplication::quit();
//    exit(-1);
  }

  return false;
}
#endif

//HEA

//vector<_window_interpreter_interpreter_interpreter_ns::_pigment_data_obs> _window_interpreter::load_data_xrd_ka_txt()
//{
//  _file_ka_txt File_ka_txt;
//  std::vector<_window_interpreter_interpreter_interpreter_ns::_pigment_data_obs> Vec_xrf_obs_data;
//  std::vector<float> Values;
//  std::string Error;
//  std::string Line;
//  std::string File_name;
//  int Error_position=-1;
//  std::vector<std::string> Vec_names;
//  std::vector<std::string> Vec_formulas;
//  std::vector<std::string> Vec_elements;
//  _vertex3f Color;

//  // check that there are a xrd folder
//  if (QDir(Project_dir+"/xrd").exists()){
//    // check if there are files

//    QDir Directory(Project_dir+"/xrd/");
//    std::string Dir_images=Directory.absolutePath().toStdString();

//    QStringList Files_uxd = Directory.entryList(QStringList() << "*ka.txt",QDir::Files);

//    if (Files_uxd.size()>0){
//      foreach(QString File_name, Files_uxd) {
//        QFileInfo File_info(File_name);
//        std::string Short_name=File_info.baseName().toStdString();
//        std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

//        File_ka_txt.open(Long_name,_file_ka_txt::_mode::MODE_READ);
//        if (File_ka_txt.read(Values,Error,Line,Error_position)==true){
//          File_ka_txt.close();

//           Vec_xrd_obs_data.push_back({Short_name,Vec_names,Vec_formulas,Vec_elements,Color,Values,Values,Values});
//        }
//        else{
//          QMessageBox MsgBox(this);
//          MsgBox.setText("Error: There is an error in ka.txt file: "+QString::fromStdString(Error)+"\nLine "+QString("%1").arg(Error_position)+" : "+QString::fromStdString(Line));
//          MsgBox.exec();
//          QApplication::quit();
//          exit(-1);
//        }
//      }

//      return Vec_xrd_obs_data;
//    }
//    else{
//      QMessageBox MsgBox(this);
//      MsgBox.setText("Error: there are not ka.txt files in xrd folder");
//      MsgBox.exec();
//      QApplication::quit();
//      exit(-1);
//    }
//  }
//  else{
//    QMessageBox MsgBox(this);
//    MsgBox.setText("Error: there is not xrd folder ");
//    MsgBox.exec();
//    QApplication::quit();
//    exit(-1);
//  }
//}


//HEA

//void _window_interpreter::load_data_xrd_txt()
//{
//  _file_txt File_txt;
//  std::vector<_data_xrd_ns::_data_xrd_obs> Vec_xrf_obs_data;
//  std::vector<float> Values;
//  std::string Error;
//  std::string Line;
//  std::string File_name;
//  int Error_position=-1;
//  std::vector<std::string> Vec_names;
//  std::vector<std::string> Vec_formulas;
//  std::vector<std::string> Vec_elements;
//  _vertex3f Color;
//  int Area=0;
//  std::vector<_common_ns::_peak_data> Peaks;
//  unsigned int Num_passes=_data_xrd_ns::NUM_PASS_DEFAULT;

//  // check that there are a xrd folder
//  if (QDir(Project_dir+"/xrd").exists()){
//    // check that there are a xrd/raw folder
//    if (QDir(Project_dir+"/xrd/raw").exists()){
//      // check if there are files
//      QDir Directory(Project_dir+"/xrd/raw/");
//      std::string Dir_images=Directory.absolutePath().toStdString();

//      QStringList Files_txt = Directory.entryList(QStringList() << "*_raw.txt",QDir::Files);

//      if (Files_txt.size()>0){
//        Vec_xrd_obs_data.clear();

//        foreach(QString File_name, Files_txt) {
//          QFileInfo File_info(File_name);
//          QString Base_name=File_info.baseName();
//          int Pos=Base_name.indexOf('_');
//          int File_pos=Base_name.leftRef(Pos).toInt();

//          std::string Short_name=File_info.baseName().toStdString();
//          std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

//          File_txt.open(Long_name,_file_txt::_mode::MODE_READ);
//          if (File_txt.read(Vec_names,Vec_formulas,Vec_elements,Color,Values,Error,Line,Error_position)==true){
//            File_txt.close();

//             Vec_xrd_obs_data.push_back({Short_name,File_pos,Values,Values,Values,Values,Area,Peaks,Num_passes});
//          }
//          else{
//            File_txt.close();

//            QMessageBox::critical(this, tr("Error"),"There is an error in .txt file: "+QString::fromStdString(Error)+"\nLine "+QString("%1").arg(Error_position)+" : "+QString::fromStdString(Line));
//            QApplication::quit();
//            exit(-1);
//          }
//        }
//      }
//      else{
//        QMessageBox::critical(this, tr("Error"),tr("There are not '.txt' files in 'xrd/raw' folder"));
//        QApplication::quit();
//        exit(-1);
//      }
//    }
//    else{
//      QMessageBox::critical(this, tr("Error"),tr("There is not 'xrd/raw' folder"));
//      QApplication::quit();
//      exit(-1);
//    }
//  }
//  else{
//    QMessageBox::critical(this, tr("Error"),tr("There is not 'xrd' folder"));
//    QApplication::quit();
//    exit(-1);
//  }
//}

//HEA

#ifdef XRD_ACTIVE
//void _window_interpreter::left_handle_slot()
//{
////  QList<int> List=Splitter_xrd->sizes();
////  if (Left_part_full==true){
////    Left_part_full=false;
////    Left_part_size=List[0];
////    List[0]=0;
////  }
////  else{
////    Left_part_full=true;
////    List[0]=Left_part_size;
////  }
////  Splitter_xrd->setSizes(List);
//}

////HEA

//void _window_interpreter::right_handle_slot()
//{
////  QList<int> List=Splitter_xrd->sizes();
////  if (Right_part_full==true){
////    Right_part_full=false;
////    Right_part_size=List[2];
////    List[2]=0;
////  }
////  else{
////    Right_part_full=true;
////    List[2]=Right_part_size;
////  }
////  Splitter_xrd->setSizes(List);
//}



void _window_interpreter::adjust_splitter()
{
  if (Split_screen==true){
    Customplot_xrf->show();
    Customplot_xrd->show();

//    if (Splitter_xrf_xrd->widget(0)!=Customplot_xrf) Splitter_xrf_xrd->replaceWidget(0,Customplot_xrf);
//    if (Splitter_xrf_xrd->widget(1)!=Customplot_xrd) Splitter_xrf_xrd->replaceWidget(1,Customplot_xrd);

//    QList<int> Sizes={Splitter_xrf_xrd->height()/2,Splitter_xrf_xrd->height()/2};
//    Splitter_xrf_xrd->setSizes(Sizes);
  }
  else{
    if (XRF_tab_active==true){
      Customplot_xrf->show();
      Customplot_xrd->hide();
//      if (Splitter_xrf_xrd->widget(0)!=Customplot_xrf) Splitter_xrf_xrd->replaceWidget(0,Customplot_xrf);
//      QWidget *Aux=new QWidget;
//      Splitter_xrf_xrd->replaceWidget(1,Aux);

//      QList<int> Sizes={Splitter_xrf_xrd->height(),0};
//      Splitter_xrf_xrd->setSizes(Sizes);
    }
    else{
      Customplot_xrf->hide();
      Customplot_xrd->show();
//      QWidget *Aux=new QWidget;
//      Splitter_xrf_xrd->replaceWidget(0,Aux);
//      if (Splitter_xrf_xrd->widget(1)!=Customplot_xrd) Splitter_xrf_xrd->replaceWidget(1,Customplot_xrd);


    }
  }
}

void _window_interpreter::split_screen_slot()
{
  Split_screen=!Split_screen;
  adjust_splitter();
}


//HEA

void _window_interpreter::xrd_update()
{
  xrd_classify_cells_threshold_mat_obs_vs_pdb();
  //
  xrd_assign_data_to_table();
  // compute the ranges
  //
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else
    xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}


//HEA

void _window_interpreter::xrd_good_threshold_slot(int Value)
{
//  std::cout << Value << std::endl;
  XRD_correlation_good_threshold=float(Value);
  if (XRD_valid==true) xrd_update();
}

//HEA

void _window_interpreter::xrd_medium_threshold_slot(int Value)
{
//  std::cout << Value << std::endl;
  XRD_correlation_medium_threshold=float(Value);
  if (XRD_valid==true) xrd_update();
}

//HEA

void _window_interpreter::xrd_bad_threshold_slot(int Value)
{
//  std::cout << Value << std::endl;
  XRD_correlation_bad_threshold=float(Value);
  if (XRD_valid==true) xrd_update();
}

//HEA

void _window_interpreter::xrd_level_subtract_slot(double Value)
{
  //  std::cout << Value << std::endl;
  XRD_level_subtract=float(Value);
  if (XRD_valid==true) xrd_process_data();
}

//HEA

//void _window_interpreter::num_removed_peaks_xrd_slot(int Value)
//{
//  XRD_num_removed_peaks=Value;
//  xrd_process_data();
//  xrd_update_info(true);
//}
#endif

//HEA

//void _window_interpreter::adjust_image_sizes(int &Width1, int &Height1)
//{
//  float Rest;

//  if (Width1%4!=0){
//    Rest=roundf(float(Width1)/4.0f);
//    Width1=int(Rest)*4;

//  }
//  if (Height1%4!=0){
//    Rest=roundf(float(Height1)/4.0f);
//    Height1=int(Rest)*4;
//  }
//}

//HEA
// Text for the info

QWizardPage *_window_interpreter::createIntroPage()
{
  QWizardPage *page = new QWizardPage;
  page->setTitle("General information");

  QLabel *label = new QLabel(_window_interpreter_ns::Help_string);

  label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  page->setLayout(layout);

  return page;
}


//HEA

//void _window_interpreter::program_positions_slot()
//{
//#ifdef LINUX
//  QString Program("positions");
//#else
//  QString Program("Positions.exe");
//#endif

//  QProcess::startDetached(Program,QStringList(""));
//}

//HEA

//void _window_interpreter::program_maplab_slot()
//{
//#ifdef LINUX
//  QString Program("maplab");
//#else
//  QString Program("MapLab.exe");
//#endif

//  QProcess::startDetached(Program,QStringList(""));
//}

#ifndef UNIFIED
//HEA

void _window_interpreter::info_slot()
{
  QWizard wizard(this);

  QFont Font=font();
  Font.setPointSize(24);
  wizard.setFont(Font);
  wizard.setOptions(QWizard::NoCancelButton | QWizard::NoBackButtonOnLastPage);
  wizard.addPage(createIntroPage());
  wizard.setWindowTitle("Info");
  wizard.exec();
}
#endif

// Interpreter
//*******************************************************************************************

//HEA

void _window_interpreter::xrf_update_parameters()
{
  Spinbox_xrf_num_steps_smooth->blockSignals(true);
  Spinbox_xrf_num_steps_smooth->setValue(XRF_num_steps_smooth);
  Spinbox_xrf_num_steps_smooth->blockSignals(false);

  Spinbox_xrf_num_steps_subtract_background->blockSignals(true);
  Spinbox_xrf_num_steps_subtract_background->setValue(XRF_num_steps_subtract_background);
  Spinbox_xrf_num_steps_subtract_background->blockSignals(false);

  Spinbox_xrf_num_steps_search_window->blockSignals(true);
  Spinbox_xrf_num_steps_search_window->setValue(XRF_num_steps_search_window);
  Spinbox_xrf_num_steps_search_window->blockSignals(false);

//  Radiobutton_xrf_mean_smooth_type->blockSignals(true);
//  Radiobutton_xrf_mean_smooth_type->setChecked(XRF_mean_smooth_type);
//  Radiobutton_xrf_mean_smooth_type->blockSignals(false);

//  Radiobutton_xrf_gs_smooth_type->blockSignals(true);
//  Radiobutton_xrf_gs_smooth_type->setChecked(XRF_gs_smooth_type);
//  Radiobutton_xrf_gs_smooth_type->blockSignals(false);
}


//HEA

void _window_interpreter::xrf_process_change()
{
  // process
  xrf_preprocess_obs_data();

  // take into account the manual selection over the other selections
  xrf_update_using_manual_selection();

  // order the data using the Ka value
  xrf_order_obs_data_for_all_files(int(_table_xrf_ns::_column_type::COLUMN_TYPE_KA_POSITION),_window_interpreter_ns::_order_mode::ORDER_MODE_INCREASE);

  // select those elements that have a value greater than the threshold
  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

  // update tab XRF data
  xrf_set_threshold(XRF_threshold_percentage);

  xrf_create_spectral_chart(Selected_file_position);

  Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);

  // recompute the XRD
  xrd_update();
}

//HEA

void _window_interpreter::num_steps_smooth_xrf_slot(int Value)
{
  XRF_num_steps_smooth=Value;

  xrf_process_change();
}

//HEA

void _window_interpreter::num_steps_subtract_mean_xrf_slot(int Value)
{
  XRF_num_steps_subtract_background=Value;

  xrf_process_change();
}

//HEA

void _window_interpreter::num_steps_search_window_xrf_slot(int Value)
{
  XRF_num_steps_search_window=Value;

  xrf_process_change();
}


//HEA
#ifdef XRD_ACTIVE
void _window_interpreter::xrd_num_steps_smooth_slot(int Value)
{
  XRD_num_steps_smooth=Value;
  xrd_process_data();
//  xrd_update_info(true);
}

//HEA

void _window_interpreter::xrd_num_steps_subtract_background_slot(int Value)
{
  XRD_num_steps_subtract_background=Value;
  xrd_process_data();

//  xrd_update_info(true);
}

//HEA

void _window_interpreter::xrd_num_steps_shift_slot(int Value)
{
  XRD_num_steps_shift=Value;
  xrd_process_data();
//  xrd_update_info(true);
}


//HEA

//void _window_interpreter::recompute_values_xrd_slot()
//{
//  for (unsigned int i=0;i<Vec_xrd_obs_data.size();i++){
//    for (unsigned int j=0;j<Vec_xrd_pdb_data.size();j++){
//      compute_data_xrd_obs_pdb(i,j);
//    }
//  }

//  Table_xrd_obs_vs_pdb_data->set_data(Vec_xrd_row_names,Vec_xrd_col_names,Mat_xrd_obs_vs_pdb_data,Vec_xrd_visible_columns_in_table);

//  xrd_create_pdb_obs_sqrt_spectral_chart();
//}

//HEA

//void _window_interpreter::xrd_recompute_all_values_slot()
//{
//  xrd_process_data();
//  xrd_update_info(true);
//}
#endif

//HEA

void _window_interpreter::create_widgets()
{
  if (Widgets_created==false){
    Widgets_created=true;

    QWidget *Main_widget=new QWidget;
    QHBoxLayout *Vboxlayout_main=new QHBoxLayout;

    // Customplot_xrf
    Customplot_xrf = new QCustomPlot();
    Customplot_xrf->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    Customplot_xrf->setInteractions(QCP::iRangeZoom); //QCP::iRangeDrag
    Customplot_xrf->axisRect()->setRangeZoom(Qt::Vertical); //Qt::Horizontal

    // XRF
    //
//    QLineSeries *Series_line = new QLineSeries(); //??
//    for (unsigned int i=0;i<10;i++){
//      Series_line->append(i,i);
//    }

    // double click
    connect(Customplot_xrf,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(chart_bar_xrf_double_click_slot(QMouseEvent*)));
    // for showing elements
    connect(Customplot_xrf,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(chart_bar_xrf_mouse_press_slot(QMouseEvent*)));
    connect(Customplot_xrf,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(chart_bar_xrf_mouse_move_slot(QMouseEvent*)));
    connect(Customplot_xrf,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(chart_bar_xrf_mouse_release_slot(QMouseEvent*)));
    // for saving the change in the ranges
    connect(Customplot_xrf->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xrf_x_axis_changed_slot(QCPRange)));
    connect(Customplot_xrf->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xrf_y_axis_changed_slot(QCPRange)));

    Customplot_xrf->legend->setVisible(true);
    Customplot_xrf->legend->setFont(QFont("Helvetica", 9));

    QCPTextElement *Title = new QCPTextElement(Customplot_xrf);
    Customplot_xrf->plotLayout()->insertRow(0);
    Customplot_xrf->plotLayout()->addElement(0, 0,Title);

    // XRF elements
    // for the files
    QWidget *W_xrf_files=new QWidget;
    QVBoxLayout *Vboxlayout_xrf_files=new QVBoxLayout;

    Listwidget_data_xrf_obs=new QListWidget;
    Listwidget_data_xrf_obs->setMinimumHeight(300);
    //    Listwidget_data_xrf_obs->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    //    Listwidget_data_xrf_obs->sizePolicy().setVerticalStretch(50);

    connect(Listwidget_data_xrf_obs,SIGNAL(currentRowChanged(int)),this,SLOT(xrf_elements_obs_row_changed_slot(int)));

    Vboxlayout_xrf_files->addWidget(Listwidget_data_xrf_obs);
    W_xrf_files->setLayout(Vboxlayout_xrf_files);


    // for the found elements
    QGroupBox *Groupbox_xrf_found_elements=new QGroupBox("Elements data");
    Groupbox_xrf_found_elements->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *Vboxlayout_xrf_found_elements=new QVBoxLayout;

    Table_data_xrf=new _table_xrf("Elements",this);
    //    Table_data_xrf->sizePolicy().setVerticalStretch(1);

    Vboxlayout_xrf_found_elements->addWidget(Table_data_xrf);
    Groupbox_xrf_found_elements->setLayout(Vboxlayout_xrf_found_elements);

    // for the elements
    QWidget *W_xrf_elements=new QWidget;
    QVBoxLayout *Vboxlayout_xrf_elements=new QVBoxLayout;

    Vboxlayout_xrf_elements->addWidget(Groupbox_xrf_found_elements);
    W_xrf_elements->setLayout(Vboxlayout_xrf_elements);

    // Parameters ***
    QWidget* W_xrf_parameters=new QWidget;
    QVBoxLayout* Vboxlayout_parameters_xrf=new QVBoxLayout;

    // Numpass
    QGroupBox *Groupbox_num_passes_xrf=new QGroupBox("Num steps");
    Groupbox_num_passes_xrf->setAlignment(Qt::AlignHCenter);

    QGridLayout *Gridlayout_num_passes_xrf=new QGridLayout;

    QLabel *Label_num_steps_smooth_xrf=new QLabel("Smooth");
    QLabel *Label_num_steps_subtract_mean_xrf=new QLabel("Subtract background");
    QLabel *Label_num_steps_search_window_xrf=new QLabel("Search window");

    Spinbox_xrf_num_steps_smooth=new QSpinBox;
    Spinbox_xrf_num_steps_smooth->setRange(0,_data_xrf_ns::XRF_MAX_NUM_STEPS_SMOOTH);
    Spinbox_xrf_num_steps_smooth->setValue(_data_xrf_ns::XRF_NUM_STEPS_SMOOTH);
    connect(Spinbox_xrf_num_steps_smooth,SIGNAL(valueChanged(int)),this,SLOT(num_steps_smooth_xrf_slot(int)));

    Spinbox_xrf_num_steps_subtract_background=new QSpinBox;
    Spinbox_xrf_num_steps_subtract_background->setRange(0,_data_xrf_ns::XRF_MAX_NUM_STEPS_SUBTRACT_BACKGROUND);
    Spinbox_xrf_num_steps_subtract_background->setValue(_data_xrf_ns::XRF_NUM_STEPS_SUBTRACT_BACKGROUND);
    connect(Spinbox_xrf_num_steps_subtract_background,SIGNAL(valueChanged(int)),this,SLOT(num_steps_subtract_mean_xrf_slot(int)));

    Spinbox_xrf_num_steps_search_window=new QSpinBox;
    Spinbox_xrf_num_steps_search_window->setRange(0,_data_xrf_ns::MAX_NUM_STEPS_SEARCH_WINDOW_XRF);
    Spinbox_xrf_num_steps_search_window->setValue(_data_xrf_ns::NUM_STEPS_SEARCH_WINDOW_XRF);
    connect(Spinbox_xrf_num_steps_search_window,SIGNAL(valueChanged(int)),this,SLOT(num_steps_search_window_xrf_slot(int)));


    Gridlayout_num_passes_xrf->addWidget(Label_num_steps_smooth_xrf,0,0,Qt::AlignRight);
    Gridlayout_num_passes_xrf->addWidget(Spinbox_xrf_num_steps_smooth,0,1,Qt::AlignLeft);
    Gridlayout_num_passes_xrf->addWidget(Label_num_steps_subtract_mean_xrf,1,0,Qt::AlignRight);
    Gridlayout_num_passes_xrf->addWidget(Spinbox_xrf_num_steps_subtract_background,1,1,Qt::AlignLeft);
    Gridlayout_num_passes_xrf->addWidget(Label_num_steps_search_window_xrf,2,0,Qt::AlignRight);
    Gridlayout_num_passes_xrf->addWidget(Spinbox_xrf_num_steps_search_window,2,1,Qt::AlignLeft);

    Groupbox_num_passes_xrf ->setLayout(Gridlayout_num_passes_xrf);

    // smooth type
//    QGroupBox *Groupbox_smooth_type_xrf=new QGroupBox("Smooth type");
//    Groupbox_smooth_type_xrf->setAlignment(Qt::AlignHCenter);

//    QGridLayout *Gridlayout_smooth_type_xrf=new QGridLayout;

//    QLabel *Label_smooth_type_xrf1=new QLabel("Mean");
//    QLabel *Label_smooth_type_xrf2=new QLabel("GS");

//    //
//    Radiobutton_xrf_mean_smooth_type=new QRadioButton;
//    Radiobutton_xrf_mean_smooth_type->setChecked(XRF_mean_smooth_type);
//    connect(Radiobutton_xrf_mean_smooth_type,SIGNAL(toggled(bool)),this,SLOT(xrf_smooth_type_mean_slot(bool)));

//    Radiobutton_xrf_gs_smooth_type=new QRadioButton;
//    Radiobutton_xrf_gs_smooth_type->setChecked(XRF_gs_smooth_type);
//    connect(Radiobutton_xrf_gs_smooth_type,SIGNAL(toggled(bool)),this,SLOT(xrf_smooth_type_gs_slot(bool)));

//    Gridlayout_smooth_type_xrf->addWidget(Label_smooth_type_xrf1,0,0,Qt::AlignRight);
//    Gridlayout_smooth_type_xrf->addWidget(Radiobutton_xrf_mean_smooth_type,0,1,Qt::AlignLeft);
//    Gridlayout_smooth_type_xrf->addWidget(Label_smooth_type_xrf2,0,2,Qt::AlignRight);
//    Gridlayout_smooth_type_xrf->addWidget(Radiobutton_xrf_gs_smooth_type,0,3,Qt::AlignLeft);

//    //Frame_smooth_type_xrd->setLayout(Gridlayout_smooth_type_xrd);
//    Groupbox_smooth_type_xrf->setLayout(Gridlayout_smooth_type_xrf);

    // Threshold
    QGroupBox *Groupbox_threshold_xrf=new QGroupBox("Threshold");
    Groupbox_threshold_xrf->setAlignment(Qt::AlignCenter);

    QGridLayout *Gridlayout_threshold_xrf=new QGridLayout;

    Spinbox_threshold_xrf=new QSpinBox;
    Spinbox_threshold_xrf->setRange(1, 100);
    Spinbox_threshold_xrf->setSuffix("%");
    Spinbox_threshold_xrf->setAlignment(Qt::AlignRight);
    Spinbox_threshold_xrf->setValue(0);
    connect(Spinbox_threshold_xrf,SIGNAL(valueChanged(int)),this,SLOT(xrf_threshold_slot(int)));
    Gridlayout_threshold_xrf->addWidget(Spinbox_threshold_xrf,0,1,Qt::AlignHCenter);

    Groupbox_threshold_xrf->setLayout(Gridlayout_threshold_xrf);

    //
    Vboxlayout_parameters_xrf->addWidget(Groupbox_num_passes_xrf);
//    Vboxlayout_parameters_xrf->addWidget(Groupbox_smooth_type_xrf);
//    Vboxlayout_parameters_xrf->addWidget(Groupbox_char_scale_xrf);
    Vboxlayout_parameters_xrf->addWidget(Groupbox_threshold_xrf);
    Vboxlayout_parameters_xrf->addStretch();

    W_xrf_parameters->setLayout(Vboxlayout_parameters_xrf);

    // Show ****
    QWidget* W_xrf_show=new QWidget;
    QVBoxLayout* Vboxlayout_show_xrf=new QVBoxLayout;

    // Show graphs
    QGroupBox *Groupbox_show_graph_xrf=new QGroupBox("Data");
    Groupbox_show_graph_xrf->setAlignment(Qt::AlignHCenter);

    QGridLayout *Gridlayout_show_graph_xrf=new QGridLayout;

    QLabel *Label_show_graph_xrf1=new QLabel("OBS raw");
    QLabel *Label_show_graph_xrf2=new QLabel("OBS processed");
    QLabel *Label_show_graph_xrf3=new QLabel("OBS proc. shifted");
    QLabel *Label_show_graph_xrf4=new QLabel("Gaussians");

    //
    Checkbox_show_graph_obs_xrf=new QCheckBox; // ???? cambiar nombre
    Checkbox_show_graph_obs_xrf->setChecked(XRF_show_graph_obs_values);
    connect(Checkbox_show_graph_obs_xrf,SIGNAL(stateChanged(int)),this,SLOT(xrf_show_obs_graph_slot(int)));

    Checkbox_show_graph_processed_xrf=new QCheckBox;
    Checkbox_show_graph_processed_xrf->setChecked(XRF_show_graph_processed_values);
    connect(Checkbox_show_graph_processed_xrf,SIGNAL(stateChanged(int)),this,SLOT(xrf_show_processed_graph_slot(int)));

    Checkbox_show_graph_processed_shifted_xrf=new QCheckBox;
    Checkbox_show_graph_processed_shifted_xrf->setChecked(XRF_show_graph_processed_values);
    connect(Checkbox_show_graph_processed_shifted_xrf,SIGNAL(stateChanged(int)),this,SLOT(xrf_show_processed_shifted_graph_slot(int)));

    Checkbox_show_graph_gaussians_xrf=new QCheckBox;
    Checkbox_show_graph_gaussians_xrf->setChecked(XRF_show_graph_gaussians_values);
    connect(Checkbox_show_graph_gaussians_xrf,SIGNAL(stateChanged(int)),this,SLOT(xrf_show_gaussians_graph_slot(int)));

    // colors
    Button_color_xrf_obs_raw=new _button_color_simple(XRF_color_obs_raw,false);
    connect(Button_color_xrf_obs_raw,SIGNAL(colorChanged(QColor)),this,SLOT(xrf_color_obs_raw_slot(QColor)));

    Button_color_xrf_obs_processed=new _button_color_simple(XRF_color_obs_processed,false);
    connect(Button_color_xrf_obs_processed,SIGNAL(colorChanged(QColor)),this,SLOT(xrf_color_obs_processed_slot(QColor)));

    Button_color_xrf_obs_processed_shifted=new _button_color_simple(XRF_color_obs_processed_shifted,false);
    connect(Button_color_xrf_obs_processed_shifted,SIGNAL(colorChanged(QColor)),this,SLOT(xrf_color_obs_processed_shifted_slot(QColor)));

    Button_color_xrf_gaussians=new _button_color_simple(XRF_color_gaussians,false);
    connect(Button_color_xrf_gaussians,SIGNAL(colorChanged(QColor)),this,SLOT(xrf_color_gaussians_slot(QColor)));


    Gridlayout_show_graph_xrf->addWidget(Label_show_graph_xrf1,0,0,Qt::AlignRight);
    Gridlayout_show_graph_xrf->addWidget(Checkbox_show_graph_obs_xrf,0,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrf->addWidget(Button_color_xrf_obs_raw,0,2,Qt::AlignLeft);
    Gridlayout_show_graph_xrf->addWidget(Label_show_graph_xrf2,1,0,Qt::AlignRight);
    Gridlayout_show_graph_xrf->addWidget(Checkbox_show_graph_processed_xrf,1,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrf->addWidget(Button_color_xrf_obs_processed,1,2,Qt::AlignLeft);
    Gridlayout_show_graph_xrf->addWidget(Label_show_graph_xrf3,2,0,Qt::AlignRight);
    Gridlayout_show_graph_xrf->addWidget(Checkbox_show_graph_processed_shifted_xrf,2,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrf->addWidget(Button_color_xrf_obs_processed_shifted,2,2,Qt::AlignLeft);
    Gridlayout_show_graph_xrf->addWidget(Label_show_graph_xrf4,3,0,Qt::AlignRight);
    Gridlayout_show_graph_xrf->addWidget(Checkbox_show_graph_gaussians_xrf,3,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrf->addWidget(Button_color_xrf_gaussians,3,2,Qt::AlignLeft);

    Groupbox_show_graph_xrf->setLayout(Gridlayout_show_graph_xrf);

    // Chart scale
    QGroupBox *Groupbox_char_scale_xrf=new QGroupBox("Scale");
    Groupbox_char_scale_xrf->setAlignment(Qt::AlignCenter);

    QGridLayout *Gridlayout_xrf_char_scale=new QGridLayout;

    QLabel *Label_xrf_char_scale1=new QLabel("Linear");
    QLabel *Label_xrf_char_scale2=new QLabel("Log");

    //
    Radiobutton_xrf_chart_scale_linear=new QRadioButton;
    if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) Radiobutton_xrf_chart_scale_linear->setChecked(true);
    else Radiobutton_xrf_chart_scale_linear->setChecked(false);
    connect(Radiobutton_xrf_chart_scale_linear,SIGNAL(toggled(bool)),this,SLOT(xrf_chart_scale_slot(bool)));

    Radiobutton_xrf_chart_scale_log=new QRadioButton;
    if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) Radiobutton_xrf_chart_scale_log->setChecked(false);
    else Radiobutton_xrf_chart_scale_log->setChecked(true);
//    connect(Radiobutton_xrf_chart_scale_log,SIGNAL(toggled(bool)),this,SLOT(xrf_chart_scale_slot(bool)));

    Gridlayout_xrf_char_scale->addWidget(Label_xrf_char_scale1,0,0,Qt::AlignRight);
    Gridlayout_xrf_char_scale->addWidget(Radiobutton_xrf_chart_scale_linear,0,1,Qt::AlignLeft);
    Gridlayout_xrf_char_scale->addWidget(Label_xrf_char_scale2,0,2,Qt::AlignRight);
    Gridlayout_xrf_char_scale->addWidget(Radiobutton_xrf_chart_scale_log,0,3,Qt::AlignLeft);

    Groupbox_char_scale_xrf->setLayout(Gridlayout_xrf_char_scale);

    //
    Vboxlayout_show_xrf->addWidget(Groupbox_show_graph_xrf);
    Vboxlayout_show_xrf->addWidget(Groupbox_char_scale_xrf);
    Vboxlayout_show_xrf->addStretch();

    W_xrf_show->setLayout(Vboxlayout_show_xrf);


    // tab
    QTabWidget *Tab_xrf=new QTabWidget;
    Tab_xrf->setMaximumWidth(_window_interpreter_ns::XRF_TAB_WIDTH);

    Tab_xrf->addTab(W_xrf_files,"Files");
    Tab_xrf->addTab(W_xrf_elements,"Elements");
    Tab_xrf->addTab(W_xrf_parameters,"Parameters");
    Tab_xrf->addTab(W_xrf_show,"Show");


    // XRD *********************
    // Customplot_xrd

    Customplot_xrd = new QCustomPlot();
    Customplot_xrd->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //    Customplot_xrd->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //    Customplot_xrd->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
    Customplot_xrd->setInteractions(QCP::iRangeZoom);
    Customplot_xrd->axisRect()->setRangeZoom(Qt::Vertical);
    //    Customplot_xrd->setAttribute(Qt::WA_NoMousePropagation, false);
    // to put the legend on the left side
    Customplot_xrd->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    // double click
    connect(Customplot_xrd,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(chart_bar_xrd_double_click_slot(QMouseEvent*)));
    // for saving the change in the ranges
    //    connect(Customplot_xrd->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xrd_x_axis_changed_slot(QCPRange)));
//    connect(Customplot_xrd->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xrd_y_axis_changed_slot(QCPRange)));

    // double click
    connect(Customplot_xrd,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(chart_bar_xrd_mouse_wheel_slot(QWheelEvent*)));

    // for showing elements
    connect(Customplot_xrd,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(chart_bar_xrd_mouse_press_slot(QMouseEvent*)));
    connect(Customplot_xrd,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(chart_bar_xrd_mouse_move_slot(QMouseEvent*)));
    connect(Customplot_xrd,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(chart_bar_xrd_mouse_release_slot(QMouseEvent*)));


    Customplot_xrd->legend->setVisible(true);
    Customplot_xrd->legend->setFont(QFont("Helvetica", 9));

    Title = new QCPTextElement(Customplot_xrd);
    Customplot_xrd->plotLayout()->insertRow(0);
    Customplot_xrd->plotLayout()->addElement(0, 0,Title);

    // for the files
    QWidget *W_xrd_files=new QWidget;
    QVBoxLayout *Vboxlayout_xrd_files=new QVBoxLayout;

    Listwidget_data_xrd_obs=new QListWidget;
    Listwidget_data_xrd_obs->setMinimumHeight(300);

    connect(Listwidget_data_xrd_obs,SIGNAL(currentRowChanged(int)),this,SLOT(xrd_pigments_obs_row_changed_slot(int)));

    // Button for edit the OBS
//    QPushButton *Button_edit_obs= new QPushButton("Edit OBS data", this);
//    connect(Button_edit_obs, SIGNAL(clicked()),this,SLOT(remove_selected_layer_slot()));


    Vboxlayout_xrd_files->addWidget(Listwidget_data_xrd_obs);
    W_xrd_files->setLayout(Vboxlayout_xrd_files);

    // Pigments --
    QWidget *Widget_pigments_xrd=new QWidget;
    QVBoxLayout *Vboxlayout_pigments_xrd=new QVBoxLayout;

    QGroupBox *Groupbox_xrd_found_pigments=new QGroupBox("Pigments data");
    Groupbox_xrd_found_pigments->setAlignment(Qt::AlignHCenter);

    QVBoxLayout *Vboxlayout_xrd_found_pigments=new QVBoxLayout;

    Table_data_xrd=new _table_xrd_a("Pigments",this);
    //    Table_data_xrf->sizePolicy().setVerticalStretch(1);

    Vboxlayout_xrd_found_pigments->addWidget(Table_data_xrd);
    Groupbox_xrd_found_pigments->setLayout(Vboxlayout_xrd_found_pigments);

    //
    Vboxlayout_pigments_xrd->addWidget(Groupbox_xrd_found_pigments);
    Widget_pigments_xrd->setLayout(Vboxlayout_pigments_xrd);


    // Parameters
    QWidget *Widget_parameters_xrd=new QWidget;
    QVBoxLayout *Vboxlayout_parameters_xrd=new QVBoxLayout;

    // Numpas
    QGroupBox *Groupbox_num_passes_xrd=new QGroupBox("Num steps");
    Groupbox_num_passes_xrd->setAlignment(Qt::AlignHCenter);

    //    QFrame *Frame_num_passes_xrd=new QFrame;
    //    Frame_num_passes_xrd->setFrameStyle(QFrame::Panel);

    QGridLayout *Gridlayout_num_passes_xrd=new QGridLayout;

    QLabel *Label_num_steps_smooth1=new QLabel("Smooth");
    QLabel *Label_num_steps_subtract_mean1=new QLabel("Subtract background");
    QLabel *Label_num_steps_shift1=new QLabel("Shift");

    Spinbox_xrd_num_steps_smooth=new QSpinBox;
    Spinbox_xrd_num_steps_smooth->setRange(0,_data_xrd_ns::MAX_NUM_STEPS_SMOOTH_XRD);
    Spinbox_xrd_num_steps_smooth->setValue(_data_xrd_ns::NUM_STEPS_SMOOTH_XRD);
    connect(Spinbox_xrd_num_steps_smooth,SIGNAL(valueChanged(int)),this,SLOT(xrd_num_steps_smooth_slot(int)));

    Spinbox_xrd_num_steps_subtract_background=new QSpinBox;
    Spinbox_xrd_num_steps_subtract_background->setRange(0,_data_xrd_ns::XRD_MAX_NUM_STEPS_SUBTRACT_BACKGROUND);
    Spinbox_xrd_num_steps_subtract_background->setValue(_data_xrd_ns::XRD_NUM_STEPS_SUBTRACT_BACKGROUND);
    connect(Spinbox_xrd_num_steps_subtract_background,SIGNAL(valueChanged(int)),this,SLOT(xrd_num_steps_subtract_background_slot(int)));

    Spinbox_xrd_num_steps_shift=new QSpinBox;
    Spinbox_xrd_num_steps_shift->setRange(0,_data_xrd_ns::MAX_NUM_STEPS_SHIFT_XRD);
    Spinbox_xrd_num_steps_shift->setValue(_data_xrd_ns::NUM_STEPS_SHIFT_XRD);
    connect(Spinbox_xrd_num_steps_shift,SIGNAL(valueChanged(int)),this,SLOT(xrd_num_steps_shift_slot(int)));


    Gridlayout_num_passes_xrd->addWidget(Label_num_steps_smooth1,0,0,Qt::AlignRight);
    Gridlayout_num_passes_xrd->addWidget(Spinbox_xrd_num_steps_smooth,0,1,Qt::AlignLeft);
    Gridlayout_num_passes_xrd->addWidget(Label_num_steps_subtract_mean1,1,0,Qt::AlignRight);
    Gridlayout_num_passes_xrd->addWidget(Spinbox_xrd_num_steps_subtract_background,1,1,Qt::AlignLeft);
    Gridlayout_num_passes_xrd->addWidget(Label_num_steps_shift1,2,0,Qt::AlignRight);
    Gridlayout_num_passes_xrd->addWidget(Spinbox_xrd_num_steps_shift,2,1,Qt::AlignLeft);

    Groupbox_num_passes_xrd ->setLayout(Gridlayout_num_passes_xrd);

    //    Frame_num_passes_xrd->setLayout(Gridlayout_num_passes_xrd);

    // smooth type
//    QGroupBox *Groupbox_smooth_type_xrd=new QGroupBox("Smooth type");
//    Groupbox_smooth_type_xrd->setAlignment(Qt::AlignHCenter);

//    QGridLayout *Gridlayout_smooth_type_xrd=new QGridLayout;

//    QLabel *Label_smooth_type_xrd1=new QLabel("Mean");
//    QLabel *Label_smooth_type_xrd2=new QLabel("GS");

//    //
//    Radiobutton_xrd_mean_smooth_type=new QRadioButton;
//    Radiobutton_xrd_mean_smooth_type->setChecked(XRD_mean_smooth_type);
//    connect(Radiobutton_xrd_mean_smooth_type,SIGNAL(toggled(bool)),this,SLOT(xrd_smooth_type_mean_slot(bool)));

//    Radiobutton_xrd_gs_smooth_type=new QRadioButton;
//    Radiobutton_xrd_gs_smooth_type->setChecked(XRD_gs_smooth_type);
//    connect(Radiobutton_xrd_gs_smooth_type,SIGNAL(toggled(bool)),this,SLOT(xrd_smooth_type_gs_slot(bool)));

//    Gridlayout_smooth_type_xrd->addWidget(Label_smooth_type_xrd1,0,0,Qt::AlignRight);
//    Gridlayout_smooth_type_xrd->addWidget(Radiobutton_xrd_mean_smooth_type,0,1,Qt::AlignLeft);
//    Gridlayout_smooth_type_xrd->addWidget(Label_smooth_type_xrd2,0,2,Qt::AlignRight);
//    Gridlayout_smooth_type_xrd->addWidget(Radiobutton_xrd_gs_smooth_type,0,3,Qt::AlignLeft);

//    //Frame_smooth_type_xrd->setLayout(Gridlayout_smooth_type_xrd);
//    Groupbox_smooth_type_xrd->setLayout(Gridlayout_smooth_type_xrd);

    // normalization type
    //    QFrame *Frame_normalization_type_xrd=new QFrame;
    //    Frame_normalization_type_xrd->setFrameStyle(QFrame::Panel);
    QGroupBox *Groupbox_normalization_type_xrd=new QGroupBox("Normalization type");
    Groupbox_normalization_type_xrd->setAlignment(Qt::AlignHCenter);

    QGridLayout *Gridlayout_normalization_type_xrd=new QGridLayout;

    QLabel *Label_normalization_type_xrd1=new QLabel("Mean");
    QLabel *Label_normalization_type_xrd2=new QLabel("Percentage");

    //
    Radiobutton_xrd_normalization_type_mean=new QRadioButton;
    if (XRD_normalization_type==_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_MEAN)
      Radiobutton_xrd_normalization_type_mean->setChecked(true);
    else
      Radiobutton_xrd_normalization_type_mean->setChecked(false);

    connect(Radiobutton_xrd_normalization_type_mean,SIGNAL(toggled(bool)),this,SLOT(xrd_normalization_type_mean_slot(bool)));

    Radiobutton_xrd_normalization_type_percentage=new QRadioButton;
    if (XRD_normalization_type==_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_PERCENTAGE)
      Radiobutton_xrd_normalization_type_percentage->setChecked(true);
    else
      Radiobutton_xrd_normalization_type_percentage->setChecked(false);

    connect(Radiobutton_xrd_normalization_type_percentage,SIGNAL(toggled(bool)),this,SLOT(xrd_normalization_type_percentage_slot(bool)));

    Gridlayout_normalization_type_xrd->addWidget(Label_normalization_type_xrd1,0,0,Qt::AlignRight);
    Gridlayout_normalization_type_xrd->addWidget(Radiobutton_xrd_normalization_type_mean,0,1,Qt::AlignLeft);
    Gridlayout_normalization_type_xrd->addWidget(Label_normalization_type_xrd2,0,2,Qt::AlignRight);
    Gridlayout_normalization_type_xrd->addWidget(Radiobutton_xrd_normalization_type_percentage,0,3,Qt::AlignLeft);

    //    Frame_normalization_type_xrd->setLayout(Gridlayout_normalization_type_xrd);
    Groupbox_normalization_type_xrd->setLayout(Gridlayout_normalization_type_xrd);


    // computation type
    QGroupBox *Groupbox_computation_type_xrd=new QGroupBox("Computation type");
    Groupbox_computation_type_xrd->setAlignment(Qt::AlignHCenter);

    QGridLayout *Gridlayout_computation_type_xrd=new QGridLayout;

    QLabel *Label_computation_type_xrd1=new QLabel("SQRT");
    QLabel *Label_computation_type_xrd2=new QLabel("NOT 0");

    //
    Radiobutton_xrd_computation_type_sqrt=new QRadioButton;
    if (XRD_computation_type==_data_xrd_ns::_computation_type::COMPUTATION_TYPE_SQRT)
      Radiobutton_xrd_computation_type_sqrt->setChecked(true);
    else
      Radiobutton_xrd_computation_type_sqrt->setChecked(false);

    connect(Radiobutton_xrd_computation_type_sqrt,SIGNAL(toggled(bool)),this,SLOT(xrd_computation_type_sqrt_slot(bool)));

    Radiobutton_xrd_computation_type_not_zero=new QRadioButton;
    if (XRD_computation_type==_data_xrd_ns::_computation_type::COMPUTATION_TYPE_NOT_ZERO)
      Radiobutton_xrd_computation_type_not_zero->setChecked(true);
    else
      Radiobutton_xrd_computation_type_not_zero->setChecked(false);

    connect(Radiobutton_xrd_computation_type_not_zero,SIGNAL(toggled(bool)),this,SLOT(xrd_computation_type_not_zero_slot(bool)));

    Gridlayout_computation_type_xrd->addWidget(Label_computation_type_xrd1,0,0,Qt::AlignRight);
    Gridlayout_computation_type_xrd->addWidget(Radiobutton_xrd_computation_type_sqrt,0,1,Qt::AlignLeft);
    Gridlayout_computation_type_xrd->addWidget(Label_computation_type_xrd2,0,2,Qt::AlignRight);
    Gridlayout_computation_type_xrd->addWidget(Radiobutton_xrd_computation_type_not_zero,0,3,Qt::AlignLeft);

    //    Frame_computation_type_xrd->setLayout(Gridlayout_computation_type_xrd);
    Groupbox_computation_type_xrd->setLayout(Gridlayout_computation_type_xrd);

    // Thresholds
    QGroupBox *Groupbox_thresholds_xrd=new QGroupBox("Thresholds");
    Groupbox_thresholds_xrd->setAlignment(Qt::AlignHCenter);

    QGridLayout *Gridlayout_thresholds_xrd=new QGridLayout;

    QLabel *Label1=new QLabel("Good");
    QLabel *Label2=new QLabel("Medium");
    QLabel *Label3=new QLabel("Bad");
    //    QLabel *Label3=new QLabel("Num removed peaks:");

    // this is for the parameter
    Spinbox_xrd_max_threshold=new QSpinBox;
    Spinbox_xrd_max_threshold->setRange(0,100);
    Spinbox_xrd_max_threshold->setValue(_data_xrd_ns::XRD_THRESHOLD_GOOD_CORRELATION);
    connect(Spinbox_xrd_max_threshold,SIGNAL(valueChanged(int)),this,SLOT(xrd_good_threshold_slot(int)));

    Spinbox_xrd_medium_threshold=new QSpinBox;
    Spinbox_xrd_medium_threshold->setRange(0,100);
    Spinbox_xrd_medium_threshold->setValue(_data_xrd_ns::XRD_THRESHOLD_MEDIUM_CORRELATION);
    connect(Spinbox_xrd_medium_threshold,SIGNAL(valueChanged(int)),this,SLOT(xrd_medium_threshold_slot(int)));

    Spinbox_xrd_bad_threshold=new QSpinBox;
    Spinbox_xrd_bad_threshold->setRange(0,100);
    Spinbox_xrd_bad_threshold->setValue(_data_xrd_ns::XRD_THRESHOLD_BAD_CORRELATION);
    connect(Spinbox_xrd_bad_threshold,SIGNAL(valueChanged(int)),this,SLOT(xrd_bad_threshold_slot(int)));

    Gridlayout_thresholds_xrd->addWidget(Label1,0,0,Qt::AlignRight);
    Gridlayout_thresholds_xrd->addWidget(Spinbox_xrd_max_threshold,0,1,Qt::AlignLeft);
    Gridlayout_thresholds_xrd->addWidget(Label2,1,0,Qt::AlignRight);
    Gridlayout_thresholds_xrd->addWidget(Spinbox_xrd_medium_threshold,1,1,Qt::AlignLeft);
    Gridlayout_thresholds_xrd->addWidget(Label3,2,0,Qt::AlignRight);
    Gridlayout_thresholds_xrd->addWidget(Spinbox_xrd_bad_threshold,2,1,Qt::AlignLeft);

    //    Frame_thresholds_xrd->setLayout(Gridlayout_thresholds_xrd);
    Groupbox_thresholds_xrd->setLayout(Gridlayout_thresholds_xrd);

    // Level subtract
    Groupbox_level_subtract_xrd=new QGroupBox("Level subtract");
    Groupbox_level_subtract_xrd->setAlignment(Qt::AlignHCenter);
    Groupbox_level_subtract_xrd->setEnabled(false);

    QGridLayout *Gridlayout_level_subtract_xrd=new QGridLayout;

    QLabel *Label_level_subtract_xrd1=new QLabel("Value");

    // this is for the parameter
    Doublespinbox_xrd_level_subtract=new QDoubleSpinBox;
    Doublespinbox_xrd_level_subtract->setRange(0,100);
    Doublespinbox_xrd_level_subtract->setValue(0);
    connect(Doublespinbox_xrd_level_subtract,SIGNAL(valueChanged(double)),this,SLOT(xrd_level_subtract_slot(double)));

    Gridlayout_level_subtract_xrd->addWidget(Label_level_subtract_xrd1,0,0,Qt::AlignRight);
    Gridlayout_level_subtract_xrd->addWidget(Doublespinbox_xrd_level_subtract,0,1,Qt::AlignLeft);

    Groupbox_level_subtract_xrd->setLayout(Gridlayout_level_subtract_xrd);


    //
    Vboxlayout_parameters_xrd->addWidget(Groupbox_num_passes_xrd);
//    Vboxlayout_parameters_xrd->addWidget(Groupbox_smooth_type_xrd);
    Vboxlayout_parameters_xrd->addWidget(Groupbox_normalization_type_xrd);
    Vboxlayout_parameters_xrd->addWidget(Groupbox_computation_type_xrd);
    //    Vboxlayout_parameters_xrd->addWidget(Groupbox_xrd_gaussian_parameters);
    Vboxlayout_parameters_xrd->addWidget(Groupbox_thresholds_xrd);
    Vboxlayout_parameters_xrd->addWidget(Groupbox_level_subtract_xrd);
//    Vboxlayout_parameters_xrd->addWidget(Groupbox_colors_xrd);
    Vboxlayout_parameters_xrd->addStretch();

    Widget_parameters_xrd->setLayout(Vboxlayout_parameters_xrd);

    // Show --
    QWidget *Widget_show_xrd=new QWidget;
    QVBoxLayout *Vboxlayout_show_xrd=new QVBoxLayout;


    // Chart type
    QGroupBox *Groupbox_chart_type_xrd=new QGroupBox("Chart type");
    Groupbox_chart_type_xrd->setAlignment(Qt::AlignHCenter);;

    QGridLayout *Gridlayout_xrd_chart_type=new QGridLayout;

    QLabel *Label_xrd_chart_type1=new QLabel("Spectral");
    QLabel *Label_xrd_chart_type2=new QLabel("Correlation");

    //
    Radiobutton_xrd_chart_type_spectra=new QRadioButton;
    if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) Radiobutton_xrd_chart_type_spectra->setChecked(true);
    else Radiobutton_xrd_chart_type_spectra->setChecked(false);
    connect(Radiobutton_xrd_chart_type_spectra,SIGNAL(toggled(bool)),this,SLOT(xrd_chart_type_slot(bool)));

    Radiobutton_xrd_chart_type_correlation=new QRadioButton;
    if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_CORRELATION) Radiobutton_xrd_chart_type_correlation->setChecked(true);
    else Radiobutton_xrd_chart_type_correlation->setChecked(false);
    connect(Radiobutton_xrd_chart_type_correlation,SIGNAL(toggled(bool)),this,SLOT(xrd_chart_type_slot(bool)));

    Gridlayout_xrd_chart_type->addWidget(Label_xrd_chart_type1,0,0,Qt::AlignRight);
    Gridlayout_xrd_chart_type->addWidget(Radiobutton_xrd_chart_type_spectra,0,1,Qt::AlignLeft);
    Gridlayout_xrd_chart_type->addWidget(Label_xrd_chart_type2,0,2,Qt::AlignRight);
    Gridlayout_xrd_chart_type->addWidget(Radiobutton_xrd_chart_type_correlation,0,3,Qt::AlignLeft);

    Groupbox_chart_type_xrd->setLayout(Gridlayout_xrd_chart_type);
    //    Frame_xrd_chart_type->setLayout(Gridlayout_xrd_chart_type);


    // Shown graphs
    QGroupBox *Groupbox_show_graph_xrd=new QGroupBox("Data");
    Groupbox_show_graph_xrd->setAlignment(Qt::AlignHCenter);

    QGridLayout *Gridlayout_show_graph_xrd=new QGridLayout;

    QLabel *Label_show_graph_xrd1=new QLabel("OBS raw");
    QLabel *Label_show_graph_xrd2=new QLabel("OBS processed");
    QLabel *Label_show_graph_xrd3=new QLabel("OBS proc. shifted");
    QLabel *Label_show_graph_xrd4=new QLabel("PDB");
    Label_computation_type=new QLabel();

    if (XRD_computation_type==_data_xrd_ns::_computation_type::COMPUTATION_TYPE_SQRT)
      Label_computation_type->setText("SQRT(OBS*PDB)");
    else
      Label_computation_type->setText("PDB NOT 0");

    //
    Checkbox_xrd_show_raw_obs_graph=new QCheckBox;
    Checkbox_xrd_show_raw_obs_graph->setChecked(XRD_show_graph_obs_raw);
    connect(Checkbox_xrd_show_raw_obs_graph,SIGNAL(stateChanged(int)),this,SLOT(xrd_show_graph_raw_obs_slot(int)));

    Checkbox_xrd_show_obs_graph=new QCheckBox;
    Checkbox_xrd_show_obs_graph->setChecked(XRD_show_graph_obs_processed);
    connect(Checkbox_xrd_show_obs_graph,SIGNAL(stateChanged(int)),this,SLOT(xrd_show_graph_obs_processed_slot(int)));

    Checkbox_xrd_show_obs_shifted_graph=new QCheckBox;
    Checkbox_xrd_show_obs_shifted_graph->setChecked(XRD_show_graph_obs_processed_shifted);
    connect(Checkbox_xrd_show_obs_shifted_graph,SIGNAL(stateChanged(int)),this,SLOT(xrd_show_graph_obs_processed_shifted_slot(int)));

    Checkbox_xrd_show_pdb_graph=new QCheckBox;
    Checkbox_xrd_show_pdb_graph->setChecked(XRD_show_graph_obs_processed);
    connect(Checkbox_xrd_show_pdb_graph,SIGNAL(stateChanged(int)),this,SLOT(xrd_show_graph_pdb_slot(int)));

    Checkbox_xrd_show_sqrt_graph=new QCheckBox;
    Checkbox_xrd_show_sqrt_graph->setChecked(XRD_show_graph_obs_processed);
    connect(Checkbox_xrd_show_sqrt_graph,SIGNAL(stateChanged(int)),this,SLOT(xrd_show_graph_sqrt_slot(int)));

    // colors
    Button_color_xrd_obs_raw=new _button_color_simple(XRD_color_obs_raw,false);
    connect(Button_color_xrd_obs_raw,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_obs_raw_slot(QColor)));

    Button_color_xrd_obs_processed=new _button_color_simple(XRD_color_obs_processed,false);
    connect(Button_color_xrd_obs_processed,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_obs_processed_slot(QColor)));

    Button_color_xrd_obs_processed_shifted=new _button_color_simple(XRD_color_obs_processed_shifted,false);
    connect(Button_color_xrd_obs_processed_shifted,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_obs_processed_shifted_slot(QColor)));

    Button_color_xrd_pdb=new _button_color_simple(XRD_color_pdb,false);
    connect(Button_color_xrd_pdb,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_pdb_slot(QColor)));

    Button_color_xrd_sqrt=new _button_color_simple(XRD_color_sqrt,false);
    connect(Button_color_xrd_sqrt,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_sqrt_slot(QColor)));


    Gridlayout_show_graph_xrd->addWidget(Label_show_graph_xrd1,0,0,Qt::AlignRight);
    Gridlayout_show_graph_xrd->addWidget(Checkbox_xrd_show_raw_obs_graph,0,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrd->addWidget(Button_color_xrd_obs_raw,0,2,Qt::AlignLeft);
    Gridlayout_show_graph_xrd->addWidget(Label_show_graph_xrd2,1,0,Qt::AlignRight);
    Gridlayout_show_graph_xrd->addWidget(Checkbox_xrd_show_obs_graph,1,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrd->addWidget(Button_color_xrd_obs_processed,1,2,Qt::AlignLeft);
    Gridlayout_show_graph_xrd->addWidget(Label_show_graph_xrd3,2,0,Qt::AlignRight);
    Gridlayout_show_graph_xrd->addWidget(Checkbox_xrd_show_obs_shifted_graph,2,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrd->addWidget(Button_color_xrd_obs_processed_shifted,2,2,Qt::AlignLeft);
    Gridlayout_show_graph_xrd->addWidget(Label_show_graph_xrd4,3,0,Qt::AlignRight);
    Gridlayout_show_graph_xrd->addWidget(Checkbox_xrd_show_pdb_graph,3,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrd->addWidget(Button_color_xrd_pdb,3,2,Qt::AlignLeft);
    Gridlayout_show_graph_xrd->addWidget(Label_computation_type,4,0,Qt::AlignRight);
    Gridlayout_show_graph_xrd->addWidget(Checkbox_xrd_show_sqrt_graph,4,1,Qt::AlignHCenter);
    Gridlayout_show_graph_xrd->addWidget(Button_color_xrd_sqrt,4,2,Qt::AlignLeft);

    //    Frame_show_graph_xrd->setLayout(Gridlayout_show_graph_xrd);
    Groupbox_show_graph_xrd->setLayout(Gridlayout_show_graph_xrd);

    // Chart scale
    QGroupBox *Groupbox_char_scale_xrd=new QGroupBox("Scale");
    Groupbox_char_scale_xrd->setAlignment(Qt::AlignCenter);

    QGridLayout *Gridlayout_xrd_char_scale=new QGridLayout;

    QLabel *Label_xrd_char_scale1=new QLabel("Linear");
    QLabel *Label_xrd_char_scale2=new QLabel("Log");

    //
    Radiobutton_xrd_chart_scale_linear=new QRadioButton;
    if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR) Radiobutton_xrd_chart_scale_linear->setChecked(true);
    else Radiobutton_xrd_chart_scale_linear->setChecked(false);
    connect(Radiobutton_xrd_chart_scale_linear,SIGNAL(toggled(bool)),this,SLOT(xrd_chart_scale_slot(bool)));

    Radiobutton_xrd_char_scale_log=new QRadioButton;
    if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR) Radiobutton_xrd_char_scale_log->setChecked(false);
    else Radiobutton_xrd_char_scale_log->setChecked(true);
//    connect(Radiobutton_xrd_char_scale_log,SIGNAL(toggled(bool)),this,SLOT(xrd_chart_scale_slot(bool)));

    Gridlayout_xrd_char_scale->addWidget(Label_xrd_char_scale1,0,0,Qt::AlignRight);
    Gridlayout_xrd_char_scale->addWidget(Radiobutton_xrd_chart_scale_linear,0,1,Qt::AlignLeft);
    Gridlayout_xrd_char_scale->addWidget(Label_xrd_char_scale2,0,2,Qt::AlignRight);
    Gridlayout_xrd_char_scale->addWidget(Radiobutton_xrd_char_scale_log,0,3,Qt::AlignLeft);

    Groupbox_char_scale_xrd->setLayout(Gridlayout_xrd_char_scale);

    // colors
    QGroupBox *Groupbox_colors_xrd=new QGroupBox("Colors");
    Groupbox_colors_xrd->setAlignment(Qt::AlignHCenter);

    QGridLayout *Grid_xrd_colors=new QGridLayout;

    QLabel *Label_color_file_not_exists=new QLabel("XRF file not exist");
    QLabel *Label_color_element_not_exists=new QLabel("XRF element(s) not exist");
    QLabel *Label_color_valid_good=new QLabel("Good");
    QLabel *Label_color_valid_medium=new QLabel("Medium");
    QLabel *Label_color_valid_bad=new QLabel("Bad");
//    QLabel *Label_color_font=new QLabel("Font color");

    Button_color_xrd_file_not_exists=new _button_color_simple(XRD_color_file_not_exists,false);
    connect(Button_color_xrd_file_not_exists,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_file_not_exists_slot(QColor)));

    Button_color_xrd_element_not_exists=new _button_color_simple(XRD_color_element_not_exists,false);
    connect(Button_color_xrd_element_not_exists,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_element_not_exists_slot(QColor)));

    Button_color_xrd_valid_good=new _button_color_simple(XRD_color_valid_good,false);
    connect(Button_color_xrd_valid_good,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_valid_good_slot(QColor)));

    Button_color_xrd_valid_medium=new _button_color_simple(XRD_color_valid_medium,false);
    connect(Button_color_xrd_valid_medium,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_valid_medium_slot(QColor)));

    Button_color_xrd_valid_bad=new _button_color_simple(XRD_color_valid_bad,false);
    connect(Button_color_xrd_valid_bad,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_valid_bad_slot(QColor)));

//    Button_color_xrd_font=new _button_color_simple(XRD_color_font,false);
//    connect(Button_color_xrd_font,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_color_font_slot(QColor)));

    //
    Grid_xrd_colors->addWidget(Label_color_valid_good,0,0,Qt::AlignRight);
    Grid_xrd_colors->addWidget(Button_color_xrd_valid_good,0,1,Qt::AlignLeft);
    Grid_xrd_colors->addWidget(Label_color_valid_medium,1,0,Qt::AlignRight);
    Grid_xrd_colors->addWidget(Button_color_xrd_valid_medium,1,1,Qt::AlignLeft);
    Grid_xrd_colors->addWidget(Label_color_valid_bad,2,0,Qt::AlignRight);
    Grid_xrd_colors->addWidget(Button_color_xrd_valid_bad,2,1,Qt::AlignLeft);
    Grid_xrd_colors->addWidget(Label_color_element_not_exists,3,0,Qt::AlignRight);
    Grid_xrd_colors->addWidget(Button_color_xrd_element_not_exists,3,1,Qt::AlignLeft);
    Grid_xrd_colors->addWidget(Label_color_file_not_exists,4,0,Qt::AlignRight);
    Grid_xrd_colors->addWidget(Button_color_xrd_file_not_exists,4,1,Qt::AlignLeft);
//    Grid_xrd_colors->addWidget(Label_color_font,5,0,Qt::AlignRight);
//    Grid_xrd_colors->addWidget(Button_color_xrd_font,5,1,Qt::AlignLeft);

    Groupbox_colors_xrd->setLayout(Grid_xrd_colors);

    //
    Vboxlayout_show_xrd->addWidget(Groupbox_chart_type_xrd);
    Vboxlayout_show_xrd->addWidget(Groupbox_show_graph_xrd);
    Vboxlayout_show_xrd->addWidget(Groupbox_char_scale_xrd);
    Vboxlayout_show_xrd->addWidget(Groupbox_colors_xrd);
    Vboxlayout_show_xrd->addStretch();

    Widget_show_xrd->setLayout(Vboxlayout_show_xrd);


    // tab for XRD
    QTabWidget *Tab_xrd=new QTabWidget;
    Tab_xrd->setMaximumWidth(_window_interpreter_ns::XRD_TAB_WIDTH);

    Tab_xrd->addTab(W_xrd_files,"Files");
    Tab_xrd->addTab(Widget_pigments_xrd,"Pigments");
    Tab_xrd->addTab(Widget_parameters_xrd,"Parameters");
    Tab_xrd->addTab(Widget_show_xrd,"Show");

    // main
    // XRF+XRD spectral information
    Splitter_xrf_xrd=new _splitter(Qt::Vertical);

    Tab=new QTabWidget(this);
    Tab->setMaximumWidth(_window_interpreter_ns::XRF_TAB_WIDTH);
    Tab->setObjectName("Interpreter_tab");

    QString Tab_style = "QTabWidget::tab-bar#Interpreter_tab { \
        alignment: center; \
        background-color: #0000ff; \
  }";

    Tab->setStyleSheet(Tab_style);

    Tab->addTab(Tab_xrf,"XRF");
    Tab->addTab(Tab_xrd,"XRD");

    Tab->setTabEnabled(0,false);
    Tab->setTabEnabled(1,false);

    connect(Tab,SIGNAL(currentChanged(int)),this,SLOT(tab_changed_slot(int)));

    Tab->hide();

    Splitter_xrf_xrd->addWidget(Customplot_xrf);
    Splitter_xrf_xrd->addWidget(Customplot_xrd);

    QList<int> Sizes={Splitter_xrf_xrd->height()/2,Splitter_xrf_xrd->height()/2};
    Splitter_xrf_xrd->setSizes(Sizes);

    Vboxlayout_main->addWidget(Splitter_xrf_xrd);
    Vboxlayout_main->addWidget(Tab);

    Main_widget->setLayout(Vboxlayout_main);

    setCentralWidget(Main_widget);
  }
}

//HEA

void _window_interpreter::tab_changed_slot(int Index)
{
  if (Index>=0){
    if (Index==0) XRF_tab_active=true;
    else XRF_tab_active=false;
  adjust_splitter();
  }
}


//HEA
#ifdef XRD_ACTIVE
void _window_interpreter::check_xrf_xrd_file_numbers_match()
{
  if (XRF_obs_data_loaded){
    // check what xrf numbers match xrd numbers
    int Pos_file_xrd;
    int Pos_file_xrf;

    for (unsigned int i=0;i<Vec_xrd_obs_data.size();i++){
      Pos_file_xrd=Vec_xrd_obs_data[i].Position;
      for (unsigned int j=0;j<Vec_xrf_obs_data.size();j++){
        Pos_file_xrf=Vec_xrf_obs_data[j].Position;
        if (Pos_file_xrf==Pos_file_xrd){
          for (unsigned int k=0;k<Vec_xrd_pdb_data.size();k++){
            Mat_xrd_obs_vs_pdb_data[i][k].XRF_used=true;
            Mat_xrd_obs_vs_pdb_data[i][k].Pos_data_xrf=j;
          }
          break;
        }
      }
    }
  }  
}
#endif

//HEA

#ifdef XRD_ACTIVE
void _window_interpreter::xrd_update_parameters()
{
  Spinbox_xrd_num_steps_smooth->blockSignals(true);
  Spinbox_xrd_num_steps_smooth->setValue(XRD_num_steps_smooth);
  Spinbox_xrd_num_steps_smooth->blockSignals(false);

  Spinbox_xrd_num_steps_subtract_background->blockSignals(true);
  Spinbox_xrd_num_steps_subtract_background->setValue(XRD_num_steps_subtract_background);
  Spinbox_xrd_num_steps_subtract_background->blockSignals(false);

  Spinbox_xrd_num_steps_shift->blockSignals(true);
  Spinbox_xrd_num_steps_shift->setValue(XRD_num_steps_shift);
  Spinbox_xrd_num_steps_shift->blockSignals(false);

//  Radiobutton_xrd_mean_smooth_type->blockSignals(true);
//  Radiobutton_xrd_mean_smooth_type->setChecked(XRD_mean_smooth_type);
//  Radiobutton_xrd_mean_smooth_type->blockSignals(false);

//  Radiobutton_xrd_gs_smooth_type->blockSignals(true);
//  Radiobutton_xrd_gs_smooth_type->setChecked(XRD_gs_smooth_type);
//  Radiobutton_xrd_gs_smooth_type->blockSignals(false);

  Radiobutton_xrd_normalization_type_mean->blockSignals(true);
  if (XRD_normalization_type==_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_MEAN)
    Radiobutton_xrd_normalization_type_mean->setChecked(true);
  else
    Radiobutton_xrd_normalization_type_mean->setChecked(false);
  Radiobutton_xrd_normalization_type_mean->blockSignals(false);

  Radiobutton_xrd_normalization_type_percentage->blockSignals(true);
  if (XRD_normalization_type==_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_PERCENTAGE)
    Radiobutton_xrd_normalization_type_percentage->setChecked(true);
  else
    Radiobutton_xrd_normalization_type_percentage->setChecked(false);
  Radiobutton_xrd_normalization_type_percentage->blockSignals(false);

  Spinbox_xrd_max_threshold->blockSignals(true);
  Spinbox_xrd_max_threshold->setValue(XRD_correlation_good_threshold);
  Spinbox_xrd_max_threshold->blockSignals(false);

  Spinbox_xrd_medium_threshold->blockSignals(true);
  Spinbox_xrd_medium_threshold->setValue(XRD_correlation_medium_threshold);
  Spinbox_xrd_medium_threshold->blockSignals(false);

//  Button_color_xrd_file_not_exists->blockSignals(true);
//  Button_color_xrd_file_not_exists->color(XRD_color_file_not_exists);
//  Button_color_xrd_file_not_exists->blockSignals(false);

//  Button_color_xrd_element_not_exists->blockSignals(true);
//  Button_color_xrd_element_not_exists->color(XRD_color_element_not_exists);
//  Button_color_xrd_element_not_exists->blockSignals(false);

//  Button_color_xrd_valid_good->blockSignals(true);
//  Button_color_xrd_valid_good->color(XRD_color_valid_good);
//  Button_color_xrd_valid_good->blockSignals(false);

//  Button_color_xrd_valid_medium->blockSignals(true);
//  Button_color_xrd_valid_medium->color(Color_valid_medium);
//  Button_color_xrd_valid_medium->blockSignals(false);

//  Button_color_xrd_valid_bad->blockSignals(true);
//  Button_color_xrd_valid_bad->color(Color_valid_bad);
//  Button_color_xrd_valid_bad->blockSignals(false);

//  Button_color_xrd_font->blockSignals(true);
//  Button_color_xrd_font->color(Color_font);
//  Button_color_xrd_font->blockSignals(false);

//  Checkbox_xrd_show_main_file_not_exists->blockSignals(true);
//  Checkbox_xrd_show_main_file_not_exists->setChecked(XRD_show_file_not_exists);
//  Checkbox_xrd_show_main_file_not_exists->blockSignals(false);

//  Checkbox_xrd_show_main_element_not_exists->blockSignals(true);
//  Checkbox_xrd_show_main_element_not_exists->setChecked(XRD_show_element_not_exists);
//  Checkbox_xrd_show_main_element_not_exists->blockSignals(false);

//  Checkbox_xrd_show_main_valid->blockSignals(true);
//  Checkbox_xrd_show_main_valid->setChecked(XRD_show_valid);
//  Checkbox_xrd_show_main_valid->blockSignals(false);

//  Checkbox_xrd_show_valid_good->blockSignals(true);
//  Checkbox_xrd_show_valid_good->setChecked(XRD_show_valid_good);
//  Checkbox_xrd_show_valid_good->blockSignals(false);

//  Checkbox_xrd_show_valid_medium->blockSignals(true);
//  Checkbox_xrd_show_valid_medium->setChecked(XRD_show_valid_medium);
//  Checkbox_xrd_show_valid_medium->blockSignals(false);

//  Checkbox_xrd_show_valid_bad->blockSignals(true);
//  Checkbox_xrd_show_valid_bad->setChecked(XRD_show_valid_bad);
//  Checkbox_xrd_show_valid_bad->blockSignals(false);



//  if (XRD_show_valid==false) Groupbox_xrd_show_valid->hide();
//  else Groupbox_xrd_show_valid->show();

}
#endif


//HEA

bool _window_interpreter::check_xrf_files_exist()
{
  // check that there are a xrf folder
  if (QDir(Project_dir+"/xrf").exists()){
    // check that there are a xrf/raw folder
    if (QDir(Project_dir+"/xrf/raw").exists()){
      // check if there are files
      QDir Directory(Project_dir+"/xrf/raw/");
//      std::string Dir_xrf=Directory.absolutePath().toStdString();

      QStringList Files_artax = Directory.entryList(QStringList() << "*.txt",QDir::Files);

      if (Files_artax.size()>0) return true;
    }
  }
  return false;
}

//HEA

bool _window_interpreter::check_xy_files_exist()
{
  // check that there are a xrf folder
  if (QDir(Project_dir+"/xrf").exists()){
    // check that there are a xrf/raw folder
    if (QDir(Project_dir+"/xrf/raw").exists()){
      // check if there are files
      QDir Directory(Project_dir+"/xrf/raw/");
      //      std::string Dir_xrf=Directory.absolutePath().toStdString();

      QStringList Files_xy = Directory.entryList(QStringList() << "*.xy",QDir::Files);

      if (Files_xy.size()>0) return true;
    }
  }
  return false;
}

//HEA

bool _window_interpreter::check_xrd_uxd_files_exist()
{
  // check that there are a xrd folder
  if (QDir(Project_dir+"/xrd").exists()){
    // check that there are a xrd/raw folder
    if (QDir(Project_dir+"/xrd/raw").exists()){
      // check if there are files
      QDir Directory(Project_dir+"/xrd/raw/");
//      std::string Dir_xrf=Directory.absolutePath().toStdString();

      QStringList Files_uxd = Directory.entryList(QStringList() << "*.uxd",QDir::Files);

      if (Files_uxd.size()>0) return true;
    }
  }
  return false;
}

bool _window_interpreter::check_xrd_plv_files_exist()
{
  // check that there are a xrd folder
  if (QDir(Project_dir+"/xrd").exists()){
    // check that there are a xrd/raw folder
    if (QDir(Project_dir+"/xrd/raw").exists()){
      // check if there are files
      QDir Directory(Project_dir+"/xrd/raw/");
      //      std::string Dir_xrf=Directory.absolutePath().toStdString();

      QStringList Files_plv = Directory.entryList(QStringList() << "*.plv",QDir::Files);

      if (Files_plv.size()>0) return true;
    }
  }
  return false;
}


//HEA

void _window_interpreter::xrf_load_data()
{
  // check if there is a PDB
  // check that there are a pdb folder
  if (QDir("./pdb").exists()){
    // load the elements data
    _data_io::xrf_load_pdb(this,Vec_xrf_pdb_data,Vec_xrf_pdb_names);
  }
  else{
    QMessageBox::critical(this,tr("Error"),tr("There is not pdb folder"));
    QApplication::quit();
    exit(-1);
  }

  // load the XRF data
  XRF_obs_data_loaded=xrf_load_obs_data();
  if (XRF_obs_data_loaded==true){
    xrf_process_obs_data();
  }
}

//HEA
#ifdef XRD_ACTIVE

#ifdef ASTM_MODE_ACTIVE
//void _window_interpreter::xrd_load_pdb_astm(std::string Folder_name)
//{
//  std::string File_name;
//  std::string Error;
//  std::string Short_name;

//  std::vector<_data_xrd_ns::_data_xrd_pdb> Vec_xrd_pdb_data_astm_Cu;
//  std::vector<std::string> Vec_names_xrd_pdb_astm_Cu;

//  QDir Directory(QString::fromStdString(_common_window_ns::FOLDER_PDB+"/"+Folder_name+"/"));
//  std::string Dir_images=Directory.absolutePath().toStdString();

//  QStringList Files_txt = Directory.entryList(QStringList() << "*astm.pgm.csv",QDir::Files);

//  Files_txt.sort();

//  if (Files_txt.size()>0){
//    foreach(QString File_name, Files_txt) {
//      QFileInfo File_info(File_name);
//      Short_name=File_info.baseName().toStdString();
//      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

//      std::vector<float> Vec_values;
//      std::vector<_common_ns::_peak_data> Vec_peaks;

//      std::string Type;
//      std::string Tube;
//      std::string Normalized;
//      std::vector<std::string> Vec_names;
//      std::vector<std::string> Vec_formulas;
//      std::vector<std::string> Vec_elements;
//      _vertex3f Color;
//      std::vector<float> Vec_2theta;
//      std::vector<float> Vec_intensity;
//      std::vector<float> Vec_d_spacing;

//      _file_xrd_pdb_astm_csv File;
//      File.open(Long_name,_file_io::_mode::MODE_READ);

//      if (File.read(Type, Tube, Normalized, Vec_names, Vec_formulas, Vec_elements, Color, Vec_2theta, Vec_intensity, Vec_d_spacing, Error)==true){
//        File.close();

//        xrf_create_pdb(Vec_2theta,Vec_intensity,Vec_values);

//        _data_xrd_ns::_pdb_type PDB_type;
//        if (Type==_data_xrd_ns::PDB_type_peaks) PDB_type=_data_xrd_ns::_pdb_type::PDB_TYPE_PEAKS;
//        else if (Type==_data_xrd_ns::PDB_type_spectral) PDB_type=_data_xrd_ns::_pdb_type::PDB_TYPE_SPECTRAL;
//        else{ // error
//          QMessageBox::critical(this, tr("Error"),QString::fromStdString("TYPE of file "+Long_name+" is wrong"));
//          QApplication::quit();
//          exit(-1);
//        }

//        _data_xrd_ns::_tube_type PDB_tube_type;
//        if (Tube==_data_xrd_ns::PDB_tube_type_Co) PDB_tube_type=_data_xrd_ns::_tube_type::TUBE_TYPE_CO;
//        else if (Tube==_data_xrd_ns::PDB_tube_type_Cu) PDB_tube_type=_data_xrd_ns::_tube_type::TUBE_TYPE_CU;
//        else{ // error
//          QMessageBox::critical(this, tr("Error"),QString::fromStdString("TUBE of file "+Long_name+" is wrong"));
//          QApplication::quit();
//          exit(-1);
//        }

//        Vec_xrd_pdb_data_astm_Cu.push_back(_data_xrd_ns::_data_xrd_pdb{Short_name,PDB_type, PDB_tube_type, PDB_normalized, Vec_names, Vec_formulas, Vec_elements, Color, Vec_values, Vec_values, Vec_values, Vec_values, 0, Vec_peaks});
//        Vec_names_xrd_pdb_astm_Cu.push_back(Short_name);
//      }
//      else{
//        File.close();

//        QMessageBox::critical(this,tr("Error"),QString::fromStdString(Error));
//        QApplication::quit();
//        exit(-1);
//      }
//    }
//  }
//  else{
//    QMessageBox::critical(this,tr("Error"),tr("there are not 'astm.pgm.txt' files in pdb folder"));
//    QApplication::quit();
//    exit(-1);
//  }

//  // tube conversion
//  if (Project_data.XRD_tube_type==_data_xrd_ns::_tube_type::TUBE_TYPE_CO){
//    // change Cu to CO
//    for (unsigned int i=0;i<Vec_xrd_pdb_data_astm_Cu.size();i++){
//      Vec_xrd_pdb_data_astm_Cu[i].Vec_values=xrd_tube_conversion(_data_xrd_ns::_tube_conversion_mode::TUBE_CONVERSION_CU_TO_CO, Vec_xrd_pdb_data_astm_Cu[i].Vec_values);
//    }
//  }

//  // include the data
//  for (unsigned int i=0;i<Vec_xrd_pdb_data_astm_Cu.size();i++){
//    Vec_xrd_pdb_data.push_back(Vec_xrd_pdb_data_astm_Cu[i]);
//    Vec_xrd_pdb_names.push_back(Vec_names_xrd_pdb_astm_Cu[i]);
//  }
//}
#endif

#endif

//HEA

#ifdef XRD_ACTIVE
void _window_interpreter::xrd_load_data()
{
  std::vector<std::string> Vec_names;
  std::vector<std::string> Vec_formulas;
  std::vector<std::string> Vec_elements;
  _vertex3f Color;
  std::vector<float> Vec_values;
  bool Normalize=false;

#ifdef SPECTRAL_MODE_ACTIVE
  std::size_t Found;

  for (size_t i=0;i<Vec_xrd_selected_pdb_folders.size();i++){ // visit all the selected folders
//    std::vector<_data_xrd_ns::_data_xrd_pdb> Vec_xrd_pdb_data;
//    std::vector<std::string> Vec_names_xrd_pdb;

    _data_io::xrd_load_pdb(this,_common_window_ns::FOLDER_PDB+"/"+Vec_xrd_selected_pdb_folders[i],Vec_xrd_pdb_data,Vec_xrd_pdb_names);

    // change Cu to Co or Co tu Cu
    for (unsigned int i=0;i<Vec_xrd_pdb_data.size();i++){
      if (Vec_xrd_pdb_data[i].Tube!=Project_data.XRD_tube_type){ // needs conversion
        if (Project_data.XRD_tube_type==_data_xrd_ns::_tube_type::TUBE_TYPE_CO){ // PDB tube is Cu
          Vec_xrd_pdb_data[i].Vec_values=xrd_tube_conversion(_data_xrd_ns::_tube_conversion_mode::TUBE_CONVERSION_CU_TO_CO, Vec_xrd_pdb_data[i].Vec_values);
        }
        else{ // PDB tube is Co
          Vec_xrd_pdb_data[i].Vec_values=xrd_tube_conversion(_data_xrd_ns::_tube_conversion_mode::TUBE_CONVERSION_CO_TO_CU, Vec_xrd_pdb_data[i].Vec_values);
          //        }
        }
      }
    }
  }

//  // Cu ASTM
//  for (size_t i=0;i<Vec_xrd_selected_pdb_folders.size();i++){
//    Found=Vec_xrd_selected_pdb_folders[i].find("Cu_astm_");
//    if (Found!=std::string::npos){
//      xrd_load_pdb_astm(Vec_xrd_selected_pdb_folders[i]);
//    }
//  }


#endif

  // load the XRD data
  XRD_obs_data_loaded=xrd_load_obs_data();
  if (XRD_obs_data_loaded==true){
    // create the Matrix with the results and a separate matrix for the selection
    Mat_xrd_obs_vs_pdb_data.resize(Vec_xrd_obs_data.size());
    Mat_xrd_obs_vs_pdb_data_selected.resize(Vec_xrd_obs_data.size());
    // for each PDB compound a position must be created
    for (unsigned int i=0;i<Mat_xrd_obs_vs_pdb_data.size();i++){
      Mat_xrd_obs_vs_pdb_data[i].resize(Vec_xrd_pdb_data.size());
      Mat_xrd_obs_vs_pdb_data_selected[i].resize(Vec_xrd_pdb_data.size());
      //initialize the vector for order the output
    }

    // controls if a column is or is not shown
//    Vec_xrd_visible_columns_in_table.resize(Vec_xrd_pdb_data.size(),true);

    if (XRF_valid==true) check_xrf_xrd_file_numbers_match();

    // assign the names
    Vec_xrd_row_names.resize(Vec_xrd_obs_data.size());
    Vec_xrd_col_names.resize(Vec_xrd_pdb_data.size());
    for (unsigned int i=0;i<Vec_xrd_pdb_data.size();i++){
      Vec_xrd_col_names[i]=Vec_xrd_pdb_data[i].File_name;
    }
  }
}
#endif


//HEA

void _window_interpreter::load_project_data()
{
  // check if there are xrf files
  XRF_artax_files_exist=check_xrf_files_exist();
  XRF_xy_files_exist=check_xy_files_exist();

#ifdef XRD_ACTIVE
  // check if there are xrd files
  XRD_uxd_files_exist=check_xrd_uxd_files_exist();
  XRD_plv_files_exist=check_xrd_plv_files_exist();
#endif

  if (XRF_artax_files_exist==true || XRF_xy_files_exist==true || XRD_uxd_files_exist==true || XRD_plv_files_exist==true){
    // initialize
    _data_io::load_project_data_csv(this,Project_dir.toStdString(),Project_data,Vec_xrf_pdb_names,Vec_xrd_pdb_names);

    // there is not treatment, so the input data is copied to output data
    Project_data.Width_pixel=Project_data.Width_original_pixel;
    Project_data.Height_pixel=Project_data.Height_original_pixel;
    Project_data.Vec_coordinate_x=Project_data.Vec_coordinate_x_original;
    Project_data.Vec_coordinate_y=Project_data.Vec_coordinate_y_original;

    // check if there is a file with the user selections
    bool User_selections_file=false;
    QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS));

    if (Check_file.exists() && Check_file.isFile()){
      _data_io::load_interpreter_user_selections_csv(this, Project_dir.toStdString(), Vec_xrd_selected_pdb_folders);
      User_selections_file=true;
    }

    // check if there is a PDB
    if (XRD_uxd_files_exist==true || XRD_plv_files_exist==true){
      // check that there are a pdb folder
      if (!QDir("./pdb").exists()){
        QMessageBox::critical(this,tr("Error"),tr("There is not pdb folder"));
        QApplication::quit();
        exit(-1);
      }
      // get the PDB options
      if (User_selections_file==false) xrd_pdb_options_slot();
    }

    // XRF section
    if (XRF_artax_files_exist==true || XRF_xy_files_exist==true){
      xrf_load_data();
      XRF_valid=true;
    }

    if (XRD_uxd_files_exist==true || XRD_plv_files_exist==true){
      xrd_load_data();
      xrd_process_data();
      xrd_update_parameters();
      XRD_valid=true;
    }

    // if there is a file with the user selections, load it and update
    if (User_selections_file==true) {
      load_user_selections_slot();
    }
    //
    Save_project->setEnabled(true);

    if (XRF_valid==true){
      Customplot_xrf->show();
      Tab->setTabEnabled(0,true);
      Tab->setCurrentIndex(0);
    }
    else Customplot_xrf->hide();

    if (XRD_valid==true){
      Customplot_xrd->show();
      Tab->setTabEnabled(1,true);
      Tab->setCurrentIndex(1);
    }
    else Customplot_xrd->hide();

    if (XRF_valid==false || XRD_valid==false){
      View_split_screen->setEnabled(false);
    }

    Tab->show();

    Save_project->setEnabled(true);
//    Save_user_selections->setEnabled(true);
    Save_one_graph->setEnabled(true);
    Save_all_graphs->setEnabled(true);

    Load_project->setEnabled(false);
    Menu_view->setEnabled(true);

//    QAction_xrd_save_correlation_data_csv->setEnabled(true);
//    QAction_xrd_save_process_info_csv->setEnabled(true);

    // now it is possible to read the settings of the project
//      read_settings();

//      ui_set_font_size(UI_font_size);
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("<p>There are not XRF or XRD files.</p><p>Nothing to do</p>"));
    QApplication::quit();
    exit(-1);
  }
}

#ifndef UNIFIED
//HEA

void _window_interpreter::load_project_data_slot()
{
  // check the project folder
  _w_directory Dialog(this,"projects",&Project_name);
  if (Dialog.exec()==QDialog::Accepted && Project_name!=""){
    QDir Dir(Project_name);
    Project_dir=Dir.absolutePath();

    load_project_data();
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There is not project folder selected"));
    QApplication::quit();
    exit(-1);
  }
}
#else
void _window_interpreter::load_project_data_slot()
{
  load_project_data();
}
#endif

//HEA

void _window_interpreter::load_user_selections_slot()
{
  _data_io::load_interpreter_user_selections_csv(this, Project_dir.toStdString(), Selected_file_position, XRF_num_steps_smooth, XRF_num_steps_subtract_background, XRF_num_steps_search_window, XRF_smooth_type, XRF_threshold_percentage, Vec_xrf_obs_data, Vec_xrd_selected_pdb_folders, XRD_num_steps_smooth, XRD_num_steps_subtract_background, XRD_num_steps_shift, XRD_smooth_type, XRD_normalization_type, XRD_correlation_good_threshold, XRD_correlation_medium_threshold, XRD_correlation_bad_threshold, Mat_xrd_obs_vs_pdb_data_selected);

  // XRF
//  xrf_process_change();
//  xrf_update_parameters();
  if (XRF_obs_data_loaded){
    Listwidget_data_xrf_obs->blockSignals(true);
    Listwidget_data_xrf_obs->setCurrentRow(Selected_file_position);
    Listwidget_data_xrf_obs->blockSignals(false);

    xrf_set_threshold(XRF_threshold_percentage);

    xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

    xrf_update_using_manual_selection();

    xrf_create_spectral_chart(Selected_file_position);
    Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
  }

  // XRD
//  xrd_process_data();
//  xrd_update_parameters();
  if (XRD_obs_data_loaded==true){
    Listwidget_data_xrd_obs->blockSignals(true);
    Listwidget_data_xrd_obs->setCurrentRow(Selected_file_position);
    Listwidget_data_xrd_obs->blockSignals(false);

    xrd_assign_data_to_table();

    if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
      xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
    else
      xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  }
}

//HEA

//void _window_interpreter::save_user_selections_slot()
//{
//  _data_io::save_interpreter_user_selections_csv(this, Project_dir.toStdString(), Selected_file_position, XRF_num_steps_smooth, XRF_num_steps_subtract_background, XRF_num_steps_search_window, XRF_smooth_type, XRF_threshold_percentage, Vec_xrf_obs_data, Vec_xrd_selected_pdb_folders, XRD_num_steps_smooth, XRD_num_steps_subtract_background, XRD_num_steps_shift, XRD_smooth_type, XRD_normalization_type, XRD_correlation_good_threshold, XRD_correlation_medium_threshold, XRD_correlation_bad_threshold,Mat_xrd_obs_vs_pdb_data_selected);

//}


//HEA

void _window_interpreter::save_one_graph_slot()
{
  QString Subdir;
  QString File_name;

  if (Tab->currentIndex()==0){
    //XRF
    Subdir="/xrf/graphs/";
    File_name=QString::fromStdString(Vec_xrf_obs_data[Selected_file_position].File_name);
  }
  else{
    //XRD
#ifdef XRD_ACTIVE
    Subdir="/xrd/graphs/";
    File_name=QString::fromStdString(Vec_xrd_obs_data[Selected_file_position].File_name+"_vs_"+Vec_xrd_pdb_data[Vec_xrd_selected_position[Selected_file_position]].File_name);

#endif
  }

  QFileDialog Dialog(this,"Save graph",Project_dir+Subdir,"*.png");
  Dialog.setWindowModality(Qt::WindowModal);
  Dialog.setAcceptMode(QFileDialog::AcceptSave);
  Dialog.setDefaultSuffix("png");
  Dialog.selectFile(File_name);
  if (Dialog.exec()== QDialog::Accepted){
    if (Tab->currentIndex()==0){
      Customplot_xrf->hide();

      xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

//      File_name=Subdir+QString::fromStdString(Vec_xrf_obs_data[Selected_file_position].File_name)+".png";

      xrf_create_spectral_chart(Selected_file_position);
      Customplot_xrf->savePng(Dialog.selectedFiles().at(0),1500,1000,1.0,-1);
      Customplot_xrf->show();
    }
    else{
#ifdef XRD_ACTIVE
      Customplot_xrd->hide();
//      File_name=Subdir+QString::fromStdString(Vec_xrd_obs_data[XRD_selected_row_in_table].File_name)+"_vs_"+QString::fromStdString(Vec_xrd_pdb_data[XRD_selected_col_in_mat].File_name)+".png";

      xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
      Customplot_xrd->savePng(Dialog.selectedFiles().at(0),1500,1000,1.0,-1);
      Customplot_xrd->show();
#endif
    }
  }
}


//HEA

void _window_interpreter::save_all_graphs_slot()
{
  QString Subdir;
  QString File_name;

  if (Tab->currentIndex()==0){
    //XRF
    Subdir=Project_dir+"/xrf/graphs/";

    Customplot_xrf->hide();
    for (unsigned int i=0;i<Vec_xrf_obs_data.size();i++){
      if (Vec_xrf_obs_data[i].Position!=-1){
        xrf_select_elements_using_threshold(Vec_xrf_obs_data[i],Vec_XRF_maximum_values[i]*float(XRF_threshold_percentage)/100.0f);
        File_name=Subdir+QString::fromStdString(Vec_xrf_obs_data[i].File_name)+".png";
        xrf_create_spectral_chart(i);
        Customplot_xrf->savePng(File_name,1500,1000,1.0,-1);
      }
    }
    Customplot_xrf->show();

    // recover the selected values
    xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);
    xrf_create_spectral_chart(Selected_file_position);
  }
  else{
    //XRD
#ifdef XRD_ACTIVE
    Subdir=Project_dir+"/xrd/graphs/";

    Customplot_xrd->hide();

//    unsigned int Col;
    for (unsigned int i=0;i<Vec_xrd_obs_data.size();i++){
      if (Vec_xrd_obs_data[i].Position!=-1){
        for (unsigned int j=0;j<Vec_xrd_pdb_data.size();j++){
          if ((Mat_xrd_obs_vs_pdb_data_selected[i][j].Hand_selection==true && Mat_xrd_obs_vs_pdb_data_selected[i][j].Selected==true) ||
              (Mat_xrd_obs_vs_pdb_data_selected[i][j].Hand_selection==true && Mat_xrd_obs_vs_pdb_data_selected[i][j].Selected==true)){
            File_name=Subdir+QString::fromStdString(Vec_xrd_obs_data[i].File_name)+"_vs_"+QString::fromStdString(Vec_xrd_pdb_data[j].File_name)+".png";
            xrd_create_pdb_obs_sqrt_spectral_chart(i,j);
            Customplot_xrd->savePng(File_name,1500,1000,1.0,-1);
          }
        }
      }
    }
    Customplot_xrd->show();

    // recover the selected values
    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);

#endif
  }

  QMessageBox::information(this,tr("Information"),"All the graphs have been saved");
}

//HEA

void _window_interpreter::xrf_save_process_info_csv_slot()
{
  QString Subdir;
  QString File_name=Subdir+QString::fromStdString(Vec_xrf_obs_data[Selected_file_position].File_name)+"_process_info.csv";

  Subdir="/xrf/graphs/";

  QFileDialog Dialog(this,"Save XRF process info",Project_dir+Subdir,"*.csv");
  Dialog.setWindowModality(Qt::WindowModal);
  Dialog.setAcceptMode(QFileDialog::AcceptSave);
  Dialog.setDefaultSuffix("csv");
  Dialog.selectFile(File_name);
  if (Dialog.exec()== QDialog::Accepted){
    File_name=Project_dir+Subdir+File_name;
//    _data_io::xrf_save_process_info_csv(this,File_name.toStdString(),XRF_num_steps_smooth, XRF_num_steps_subtract_background, 3.0, Vec_xrf_obs_data[Selected_file_position].Step, Vec_xrf_obs_data[Selected_file_position].Vec_values, Vec_xrf_obs_data[Selected_file_position].Vec_processed_values, Vec_xrf_obs_data[Selected_file_position].Vec_subtract_noise_values, Vec_xrf_obs_data[Selected_file_position].Vec_subtract_noise_values); //????
  }
}


#ifdef XRD_ACTIVE
#ifdef XLSX_ACTIVE
//HEA

void _window_interpreter::xrd_save_correlation_data_xlsx_slot()
{
  _data_io::xrd_save_correlation_table_xlsx(this,Project_dir.toStdString(),Vec_xrd_row_names,Vec_xrd_col_names,Vec_xrd_visible_columns_in_table,Mat_xrd_obs_vs_pdb_data);
}

//HEA

void _window_interpreter::xrd_save_process_info_xlsx_slot()
{
  QString Subdir;
  QString File_name=Subdir+QString::fromStdString(Vec_xrd_obs_data[XRD_selected_row_in_table].File_name)+"_vs_"+QString::fromStdString(Vec_xrd_pdb_data[XRD_selected_col_in_mat].File_name)+"_process_info.xlsx";

  Subdir="/xrd/graphs/";

  QFileDialog Dialog(this,"Save XRD process info",Project_dir+Subdir,"*.xlsx");
  Dialog.setWindowModality(Qt::WindowModal);
  Dialog.setAcceptMode(QFileDialog::AcceptSave);
  Dialog.setDefaultSuffix("csv");
  Dialog.selectFile(File_name);
  if (Dialog.exec()== QDialog::Accepted){
    File_name=Project_dir+Subdir+File_name;
    _data_io::xrd_save_process_info_xlsx(this,File_name.toStdString(),XRD_num_steps_smooth,XRD_num_steps_subtract_background, _data_xrd_ns::START_2THETA, _data_xrd_ns::STEPS_2THETA, Vec_xrd_obs_data[XRD_selected_row_in_table].Vec_values, Vec_xrd_obs_data[XRD_selected_row_in_table].Vec_smooth_values, Vec_xrd_obs_data[XRD_selected_row_in_table].Vec_filtered_values, Vec_xrd_obs_data[XRD_selected_row_in_table].Vec_normalized_values, Vec_xrd_pdb_data[XRD_selected_col_in_mat].Vec_values, Vec_xrd_pdb_data[XRD_selected_col_in_mat].Vec_smooth_values, Vec_xrd_pdb_data[XRD_selected_col_in_mat].Vec_filtered_values, Vec_xrd_pdb_data[XRD_selected_col_in_mat].Vec_normalized_values, Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].Vec_sqrt_values);
  }
}
#else
void _window_interpreter::xrd_save_correlation_data_csv_slot()
{
  _data_io::xrd_save_correlation_table_csv(this,Project_dir.toStdString(),Vec_xrd_row_names,Vec_xrd_col_names,Mat_xrd_obs_vs_pdb_data,Mat_xrd_obs_vs_pdb_data_selected);
}

//HEA

void _window_interpreter::xrd_save_process_info_csv_slot()
{
  QString Subdir;
  QString File_name=Subdir+QString::fromStdString(Vec_xrd_obs_data[Selected_file_position].File_name)+"_vs_"+QString::fromStdString(Vec_xrd_pdb_data[Vec_xrd_selected_position[Selected_file_position]].File_name)+"_process_info.csv";

  Subdir="/xrd/graphs/";

  QFileDialog Dialog(this,"Save XRD process info",Project_dir+Subdir,"*.csv");
  Dialog.setWindowModality(Qt::WindowModal);
  Dialog.setAcceptMode(QFileDialog::AcceptSave);
  Dialog.setDefaultSuffix("csv");
  Dialog.selectFile(File_name);
  if (Dialog.exec()== QDialog::Accepted){
    File_name=Project_dir+Subdir+File_name;
    _data_io::xrd_save_process_info_csv(this,File_name.toStdString(),XRD_num_steps_smooth,XRD_num_steps_subtract_background, _data_xrd_ns::START_2THETA, _data_xrd_ns::STEPS_2THETA, Vec_xrd_obs_data[Selected_file_position].Vec_values, Vec_xrd_obs_data[Selected_file_position].Vec_smooth_values, Vec_xrd_obs_data[Selected_file_position].Vec_filtered_values, Vec_xrd_obs_data[Selected_file_position].Vec_normalized_values, Vec_xrd_pdb_data[Vec_xrd_selected_position[Selected_file_position]].Vec_values, Vec_xrd_pdb_data[Vec_xrd_selected_position[Selected_file_position]].Vec_smooth_values, Vec_xrd_pdb_data[Vec_xrd_selected_position[Selected_file_position]].Vec_filtered_values, Vec_xrd_pdb_data[Vec_xrd_selected_position[Selected_file_position]].Vec_normalized_values, Mat_xrd_obs_vs_pdb_data[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].Vec_sqrt_values);
  }
}
#endif
#endif

//HEA

#ifdef XRD_ACTIVE
//float _window_interpreter::compute_xrd_area(int Row,int Col)
//{
//  float Value=0;

//  for (unsigned int i=0;i<Vec_xrd_obs_data[Row].Vec_smooth_values.size();i++){
//    if (Mat_xrd_obs_vs_pdb_data[Row][Col].Vec_sqrt_values[i]>0) Value=Value+Vec_xrd_obs_data[Row].Vec_smooth_values[i];
//  }

//  return Value;
//}
#endif

//HEA

void _window_interpreter::save_project_data_slot()
{
  // Save the data in Project_data

  // XRF
  // search for all elements in all fies that are valid and are selected
  std::string Element_name;
  std::set<std::string> Selected_elements;
//  std::vector<bool> Vec_valid(Vec_xrf_pdb_data.size(),false);

  // check all the positions
  for (unsigned int Pos_file=0;Pos_file<Vec_xrf_obs_data.size();Pos_file++){
    // check the selected positions
    if (Vec_xrf_obs_data[Pos_file].Position!=-1){
      // the found elements for that position
      for (unsigned int Pos_element=0;Pos_element<Vec_xrf_obs_data[Pos_file].Vec_elements_ka_kb.size();Pos_element++){
        // Check if the element was manually selected
        Element_name=Vec_xrf_obs_data[Pos_file].Vec_elements_ka_kb[Pos_element].Name;
        if (Vec_xrf_obs_data[Pos_file].Map_elements_manually_selected[Element_name].Manual_selection==true){
          // manually selected
          if (Vec_xrf_obs_data[Pos_file].Map_elements_manually_selected[Element_name].Selected==true){
            Selected_elements.insert(Element_name);
          }
        }
        else{ // automatically classified
          if (Vec_xrf_obs_data[Pos_file].Vec_elements_ka_kb[Pos_element].Selected==true){
            Selected_elements.insert(Element_name);
          }
        }
      }
    }
  }

  // convert the set to a vector
  std::vector<std::string> Vec_names(Selected_elements.size());
  int Pos=0;
  for (const std::string& Name : Selected_elements){
    Vec_names[Pos++]=Name;
  }

  // create the vector of elemens that have data
  int Position=0;
  // each row is for one element
  Project_data.Vec_xrf_interpreted_data.resize(Vec_names.size());

  for (unsigned int Pos_element=0;Pos_element<Vec_names.size();Pos_element++){
    // save the name of the element
    Project_data.Vec_xrf_interpreted_data[Pos_element].Name=Vec_names[Pos_element];
    // resizethe vector to the number of positions
    Project_data.Vec_xrf_interpreted_data[Pos_element].Vec_values.resize(Vec_xrf_obs_data.size(),0.0f);
  }

  // now assign the value for each position
  for (unsigned int Pos_file=0;Pos_file<Vec_xrf_obs_data.size();Pos_file++){
    // check that the position is valid
    if (Vec_xrf_obs_data[Pos_file].Position!=-1){
      // for all the found elements
      for (unsigned int Pos_element=0;Pos_element<Vec_xrf_obs_data[Pos_file].Vec_elements_ka_kb.size();Pos_element++){
        // check the manual selection
        Element_name=Vec_xrf_obs_data[Pos_file].Vec_elements_ka_kb[Pos_element].Name;
        // find the Element_name in Project_data.Vec_xrf_interpreted_data
        unsigned int Pos_in_vec;
        bool Found=false;

        for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
          if (Project_data.Vec_xrf_interpreted_data[i].Name==Element_name){
            Found=true;
            Pos_in_vec=i;
            break;
          }
        }

        if (Found==true){
          if (Vec_xrf_obs_data[Pos_file].Map_elements_manually_selected[Element_name].Manual_selection==true){
            // manually selected
            if (Vec_xrf_obs_data[Pos_file].Map_elements_manually_selected[Element_name].Selected==true){
              Project_data.Vec_xrf_interpreted_data[Pos_in_vec].Vec_values[Pos_file]=Vec_xrf_obs_data[Pos_file].Vec_elements_ka_kb[Pos_element].Gaussian_area_ka;
            }
          }
          else{ // automatically classified
            if (Vec_xrf_obs_data[Pos_file].Vec_elements_ka_kb[Pos_element].Selected==true){
              Project_data.Vec_xrf_interpreted_data[Pos_in_vec].Vec_values[Pos_file]=Vec_xrf_obs_data[Pos_file].Vec_elements_ka_kb[Pos_element].Gaussian_area_ka;
            }
          }
        }
      }
    }
    else{
      // there is not data
      // search for the position of the element
      for (unsigned int Pos_element=0;Pos_element<Vec_names.size();Pos_element++){
        Project_data.Vec_xrf_interpreted_data[Pos_element].Vec_values[Pos_file]=0.0f;
      }
    }
  }

// XRD
// first check the columns that are valid (the found compounds)
  std::vector<bool> Vec_valid_columns(Vec_xrd_pdb_data.size(),false);

  for (unsigned int Row=0;Row<Vec_xrd_obs_data.size();Row++){
    if (Vec_xrd_obs_data[Row].Position!=-1){
      for (unsigned int Col=0;Col<Vec_xrd_pdb_data.size();Col++){
        if (Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected==true){
          Vec_valid_columns[Col]=true;
        }
      }
    }
  }

  int Num_valid_columns=count(Vec_valid_columns.begin(),Vec_valid_columns.end(),true);

  // now assign the value for each position
  Project_data.Vec_xrd_interpreted_data.resize(Num_valid_columns);

  Position=0;
  for (unsigned Col=0;Col<Vec_valid_columns.size();Col++){
    if (Vec_valid_columns[Col]==true){
      Project_data.Vec_xrd_interpreted_data[Position].Name=Vec_xrd_pdb_data[Col].File_name;

      // depending on the number of defined positions, the number of data can be less, equal or greater
      // in the case that there are less or equal, we use the number of positions
      if (Project_data.Vec_coordinate_x.size()>=Vec_xrd_obs_data.size()){
        Project_data.Vec_xrd_interpreted_data[Position].Vec_values.resize(Project_data.Vec_coordinate_x.size(),0.0f);
      }
      else{
        Project_data.Vec_xrd_interpreted_data[Position].Vec_values.resize(Vec_xrd_obs_data.size(),0.0f);
      }

      // compute area
      for (unsigned int Row=0;Row<Vec_xrd_obs_data.size();Row++){
        if (Vec_xrd_obs_data[Row].Position!=-1){
          if (Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected==true){
            Project_data.Vec_xrd_interpreted_data[Position].Vec_values[Row]=accumulate(Mat_xrd_obs_vs_pdb_data[Row][Col].Vec_sqrt_values.begin(),Mat_xrd_obs_vs_pdb_data[Row][Col].Vec_sqrt_values.end(),0.0f);
          }
        }
      }

      Position++;
    }
  }


  // now save the information
  _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

  _data_io::save_interpreter_user_selections_csv(this, Project_dir.toStdString(), Selected_file_position, XRF_num_steps_smooth, XRF_num_steps_subtract_background, XRF_num_steps_search_window, XRF_smooth_type, XRF_threshold_percentage, Vec_xrf_obs_data, Vec_xrd_selected_pdb_folders, XRD_num_steps_smooth, XRD_num_steps_subtract_background, XRD_num_steps_shift, XRD_smooth_type, XRD_normalization_type, XRD_correlation_good_threshold, XRD_correlation_medium_threshold, XRD_correlation_bad_threshold,Mat_xrd_obs_vs_pdb_data_selected);

  Window_main->check_project_state();
}

//HEA

#ifdef XRD_ACTIVE
void _window_interpreter::compute_data_xrd_obs_pdb(int OBS_pos,int PDB_pos)
{
  // Check if there are XRF elements
  if (Mat_xrd_obs_vs_pdb_data[OBS_pos][PDB_pos].XRF_used){
    int Pos_data_xrf=Mat_xrd_obs_vs_pdb_data[OBS_pos][PDB_pos].Pos_data_xrf;
    // there is xrf file with the same position than the xrd file
    std::vector<std::string> Vec_elements_not_found;

    // Vec_xrd_pdb_data[PDB_pos] -> data of pigment in j position (the PDB)
    if (Vec_xrd_pdb_data[PDB_pos].Vec_elements.size()>0){
      // therea are elements for the pigment && there are xrf files corresponding to the xrd file
      bool Found;
      std::string Element;
      for (unsigned int k=0;k<Vec_xrd_pdb_data[PDB_pos].Vec_elements.size();k++){
        Element=Vec_xrd_pdb_data[PDB_pos].Vec_elements[k];
        Found=false;
        for (unsigned int l=0;l<Vec_xrf_obs_data[Pos_data_xrf].Vec_elements_ka_kb.size();l++){
          if (Element==Vec_xrf_obs_data[Pos_data_xrf].Vec_elements_ka_kb[l].Name){
            Found=true;
            break;
          }
        }
        if (Found==false) Vec_elements_not_found.push_back(Element);
      }

      Mat_xrd_obs_vs_pdb_data[OBS_pos][PDB_pos].Vec_elements_not_found=Vec_elements_not_found;
    }
  }

  // compute the convolution between the PDB and the OBS
  xrd_convolution(Vec_xrd_pdb_data[PDB_pos].Vec_normalized_values,Vec_xrd_obs_data[OBS_pos].Vec_normalized_values,Mat_xrd_obs_vs_pdb_data[OBS_pos][PDB_pos],XRD_num_steps_shift);

//  unsigned int Num_checked_peaks=0;

//  unsigned int Stop;
//  if (XRD_num_removed_peaks>=int(Vec_xrd_pdb_data[PDB_pos].Vec_peaks.size())) Stop=1;
//  else Stop=Vec_xrd_pdb_data[PDB_pos].Vec_peaks.size()-XRD_num_removed_peaks;

//  for (unsigned int k=0;k<Stop;k++){
//    for (int Pos=Vec_xrd_pdb_data[PDB_pos].Vec_peaks[k].Start_pos;Pos<=Vec_xrd_pdb_data[PDB_pos].Vec_peaks[k].End_pos;Pos++){
//      if (Mat_xrd_obs_vs_pdb_data[OBS_pos][PDB_pos].Vec_sqrt_values[Pos]>0){
//        Num_checked_peaks++;
//        break;
//      }
//    }
//  }

//  Mat_xrd_obs_vs_pdb_data[OBS_pos][PDB_pos].Num_counted_peaks=Num_checked_peaks;
}
#endif

//HEA

void _window_interpreter::save_values(std::string File_name,std::vector<std::string> &Names,std::vector<std::vector<float>> &Values)
{
  std::string Text;
  std::fstream File;

  File.open(File_name,std::ios::out);
  File << Names[0];
  for (unsigned int i=1;i<Names.size();i++){
    File << ";" << Names[i];
  }
  File << "\n";

  for (unsigned int i=0;i<Values[0].size();i++){
    Text=QString("%1").arg(Values[0][i],6,'f').toStdString();
    File << Text;
    for (unsigned int j=1;j<Values.size();j++){
      Text=QString("%1").arg(Values[j][i],6,'f').toStdString();
      File << ";" << Text;
    }
    File << "\n";
  }
  File.close();
}

//HEA
// double click reset the position

void _window_interpreter::chart_bar_xrf_double_click_slot(QMouseEvent *Event)
{
  Q_UNUSED(Event);

  if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR){
    Customplot_xrf->xAxis->setRange(Vec_xrf_axis_ranges_linear[Selected_file_position].X_default_range);
    Customplot_xrf->yAxis->setRange(Vec_xrf_axis_ranges_linear[Selected_file_position].Y_default_range);
  }
  else{
    Customplot_xrf->xAxis->setRange(Vec_xrf_axis_ranges_log[Selected_file_position].X_default_range);
    Customplot_xrf->yAxis->setRange(Vec_xrf_axis_ranges_log[Selected_file_position].Y_default_range);
  }
  Customplot_xrf->replot();
}

// double click reset the position
void _window_interpreter::chart_bar_xrf_before_replot_slot()
{
//  QCPRange Range_x=Customplot_xrf->xAxis->range();
//  Chart_xrf_axis_x_min=Range_x.lower;
//  Chart_xrf_axis_x_max=Range_x.upper;

//  QCPRange Range_y=Customplot_xrf->yAxis->range();
//  Chart_xrf_axis_y_min=Range_y.lower;
//  Chart_xrf_axis_y_max=Range_y.upper;
}

//HEA
// using the processed data instead of the observed data!

int _window_interpreter::search_near_element_in_data(float X_coord,float Y_coord,float Window)
{
  // get the step of the file
  float Step=Vec_xrf_obs_data[Selected_file_position].Step;

  // get the position in array
  int Pos_Ka=int(round(X_coord/Step))-int(round(3/Step));

  float Value=Vec_xrf_obs_data[Selected_file_position].Vec_processed_shifted_values[Pos_Ka];
  float Distance=fabs(Value-Y_coord);
  if (Distance<=Window) return 1;
  else return 0;
}

//HEA

//int _window_interpreter::search_near_element_in_pdb(int Pos_ka,int Window,float Step)
//{
//  float Ka;
//  int Distance;
//  int Min_distance=1000;
//  int Selected_element_pos=-1;

//  for (unsigned int i=0;i<Vec_xrf_pdb_data.size();i++){
//    // get the Ka value in keV
//    Ka=Vec_xrf_pdb_data[i].Ka;

//    // convert the position in keV to position in the list ( the minimum value for keV is 3)
//    int Pos_element_ka=int(round(Ka/Step))-int(round(3/Step));

//    // first check that the position of the peak is in the search window
//    if (Pos_element_ka>=Pos_ka-Window && Pos_element_ka<=Pos_ka+Window){
//      // there is ka peak
//      // get the distance between the real peak and the element peak (positions)
//      Distance=int(fabs(Pos_ka-Pos_element_ka));

//      if (Distance<Min_distance){
//        Min_distance=Distance;
//        Selected_element_pos=i;
//      }
//    }
//  }

//  return Selected_element_pos;
//}

int _window_interpreter::search_near_element_in_pdb(float Pos_ka)
{
  float Ka_pdb;
  float Distance;
  float Min_distance=1000;
  int Selected_element_pos=-1;

  for (unsigned int i=0;i<Vec_xrf_pdb_data.size();i++){
    // get the Ka value in keV
    Ka_pdb=Vec_xrf_pdb_data[i].Ka;

    // get the distance between the real peak and the element peak (positions)
    Distance=fabs(Pos_ka-Ka_pdb);

    if (Distance<Min_distance){
      Min_distance=Distance;
      Selected_element_pos=i;
    }
  }

  return Selected_element_pos;
}


//HEA

int _window_interpreter::search_near_element_in_found(int Pos_ka,int Window,float Step)
{
  Q_UNUSED(Step)

  int Pos_element_ka;
  int Distance;
  int Min_distance=1000;
  int Selected_element_pos=-1;

  for (unsigned int i=0;i<Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.size();i++){
    // get the Ka value in keV
    Pos_element_ka=Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[i].Ka.Position;

    // first check that the position of the peak is in the search window
    if (Pos_element_ka>=Pos_ka-Window && Pos_element_ka<=Pos_ka+Window){
      // there is ka peak
      // get the distance between the real peak and the element peak (positions)
      Distance=int(fabs(Pos_ka-Pos_element_ka));

      if (Distance<Min_distance){
        Min_distance=Distance;
        Selected_element_pos=i;
      }
    }
  }

  return Selected_element_pos;
}


//HEA
// for adding elements

//void _window_interpreter::chart_bar_xrf_mouse_press_slot(QMouseEvent* Event)
//{
//  float Window_search_data=0.2;

//  Action_type=_window_interpreter_ns::_action_type::ACTION_ADD_ELEMENT;

//  switch(Event->button()){
//    case Qt::LeftButton:
//    {
//      if (Action_type==_window_interpreter_ns::_action_type::ACTION_ADD_ELEMENT){
//        const int Window=5;

//        // get the coordinates
//        float X_coord=float(Customplot_xrf->xAxis->pixelToCoord(Event->pos().x()));
//        float Y_coord=float(Customplot_xrf->yAxis->pixelToCoord(Event->pos().y()));

//        // check that there is data near of the position
//        int Result=search_near_element_in_data(X_coord,Y_coord,Window_search_data);
//        if (Result==1){

//          // get the step of the file
//          float Step=Vec_xrf_obs_data[Selected_file_position].Step;

//          // get the position in array
//          int Pos_Ka=int(round(X_coord/Step))-int(round(3/Step));

//          // search the nearer element in the elements PDB
//          int Selected_element_pos=search_near_element_in_pdb(Pos_Ka,Window,Step);

//          // there is one element found
//          if (Selected_element_pos!=-1){

//            bool Found=false;
//            for (unsigned int i=0;i<Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.size();i++){
//              if (Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[i].Name==Vec_xrf_pdb_data[Selected_element_pos].Name){
//                Found=true;
//                break;
//              }
//            }

//            if (Found==false && Element_selected.Name!=Vec_xrf_pdb_data[Selected_element_pos].Name){
//              Element_selected.Name=Vec_xrf_pdb_data[Selected_element_pos].Name;

//              // ka
//              float Ka=Vec_xrf_pdb_data[Selected_element_pos].Ka;
//              Element_selected.Ka.Position=int(round(Ka/Step))-int(round(3/Step));
//              float Value_ka=Vec_xrf_obs_data[Selected_file_position].Vec_smooth_values[Element_selected.Ka.Position];
//              Element_selected.Ka.Value=Value_ka;
//              // kb
//              float Kb=Vec_xrf_pdb_data[Selected_element_pos].Kb;
//              Element_selected.Kb.Position=int(round(Kb/Step))-int(round(3/Step));
//              float Value_kb=Vec_xrf_obs_data[Selected_file_position].Vec_smooth_values[Element_selected.Kb.Position];
//              // aplies the ratio if kb is very big
//              if (Value_kb>Value_ka) Value_kb=Value_ka*Vec_xrf_pdb_data[Selected_element_pos].Kb_Ka_ratio;
//              Element_selected.Kb.Value=Value_kb;

//              xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(Vec_threshold_percentage_xrf[Selected_file_position])/100.0f);

//              // update tab XRF data
//              xrf_set_threshold(Vec_threshold_percentage_xrf[Selected_file_position]);

//              xrf_create_spectral_chart(Selected_file_position);

//              Listwidget_data_xrf_obs->setCurrentRow(0);

//              Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
//            }
//          }
//        }
//      }
//    }
//    break;
//    case Qt::RightButton:
//    {
//      switch (Action_type){
//        case _window_interpreter_ns::_action_type::ACTION_ADD_ELEMENT:
//        {
//          if (Element_selected.Name!=""){
//            QMenu menu;
//            menu.addAction("Add element "+QString::fromStdString(Element_selected.Name));
//            QAction *Selection = menu.exec(Event->globalPos());
//            if (Selection){
//              xrf_add_element_action();
//            }
//          }
//        }
//        break;
//        case _window_interpreter_ns::_action_type::ACTION_REMOVE_ELEMENT:
//        { // search the element
//          const int Window=5;

//          // get the x coordinate in x axis range
//          float X_coord=float(Customplot_xrf->xAxis->pixelToCoord(Event->pos().x()));
//          float Y_coord=float(Customplot_xrf->yAxis->pixelToCoord(Event->pos().y()));

//          // check that there is data near of the position
//          int Result=search_near_element_in_data(X_coord,Y_coord,Window_search_data);
//          if (Result==1){
//            // get the step of the file
//            float Step=Vec_xrf_obs_data[Selected_file_position].Step;

//            // get the position in array
//            int Pos_Ka=int(round(X_coord/Step))-int(round(3/Step));

//            // search the nearer element in the elements PDB
//            int Selected_element_pos=search_near_element_in_found(Pos_Ka,Window,Step);

//            // there is one element found
//            if (Selected_element_pos!=-1){
//              std::string Element_name=Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[Selected_element_pos].Name;
//              QMenu menu;
//              menu.addAction("delete element "+QString::fromStdString(Element_name));
//              QAction *Selection = menu.exec(Event->globalPos());
//              if (Selection){
//                xrf_remove_element_action(Selected_element_pos);
//              }
//            }
//          }
//        }
//        break;
//        default:break;
//      }
//    }
//    break;
//    default:break;
//  }
//}

//HEA

void _window_interpreter::chart_bar_xrf_mouse_press_slot(QMouseEvent* Event)
{
  Key_pressed=true;

  if (Event->button() == Qt::LeftButton) Left_button=true;
  else Left_button=false;

  // Crear un cursor personalizado (cursor de mano señalando)
  QCursor Cursor(Qt::CrossCursor);

  // Asignar el cursor al widget
  setCursor(Cursor);

  chart_bar_xrf_mouse_move_slot(Event);
}

//HEA

void _window_interpreter::chart_bar_xrf_mouse_move_slot(QMouseEvent* Event)
{
  if (Key_pressed){
    // get the coordinates
    X_pos=float(Customplot_xrf->xAxis->pixelToCoord(Event->pos().x()));
    Y_pos=float(Customplot_xrf->yAxis->pixelToCoord(Event->pos().y()));

    if (Left_button==true){
      // search the nearer element in the elements PDB
      int Selected_element_pos=search_near_element_in_pdb(X_pos);

      Element_selected.Name=Vec_xrf_pdb_data[Selected_element_pos].Name;

      X_pos_ka=Vec_xrf_pdb_data[Selected_element_pos].Ka;
      X_pos_kb=Vec_xrf_pdb_data[Selected_element_pos].Kb;
    }

    xrf_create_spectral_chart(Selected_file_position);
  }
}

//HEA

void _window_interpreter::chart_bar_xrf_mouse_release_slot(QMouseEvent* Event)
{
  Q_UNUSED(Event);

  Key_pressed=false;

  // Crear un cursor personalizado (cursor de mano señalando)
  QCursor Cursor(Qt::ArrowCursor);

  // Asignar el cursor al widget
  setCursor(Cursor);

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_x_axis_changed_slot(QCPRange Range)
{
  if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) Vec_xrf_axis_ranges_linear[Selected_file_position].X_range=Range;
  else Vec_xrf_axis_ranges_log[Selected_file_position].X_range=Range;
}

//HEA

void _window_interpreter::xrf_y_axis_changed_slot(QCPRange Range)
{
  Range.lower=0;
  if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR){
    Vec_xrf_axis_ranges_linear[Selected_file_position].Y_range=Range;
  }
  else Vec_xrf_axis_ranges_log[Selected_file_position].Y_range=Range;

  Customplot_xrf->yAxis->blockSignals(true);
  if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) Customplot_xrf->yAxis->setRange(Vec_xrf_axis_ranges_linear[Selected_file_position].Y_range);
  else Customplot_xrf->yAxis->setRange(Vec_xrf_axis_ranges_log[Selected_file_position].Y_range);
  Customplot_xrf->yAxis->blockSignals(false);
//  Customplot_xrf->replot();
}

//HEA

void _window_interpreter::xrf_create_spectral_chart(int Selected_file_position)
{
  int Pos_graph=0;

  if (Split_screen==false && XRF_tab_active==false) return;

  QFont Font=QApplication::font();
  Font.setPointSize(Font.pointSize()*1.5);

  // block to not produce an event
  Customplot_xrf->blockSignals(true);

  // clear data
  if (Customplot_xrf->plottable()!=nullptr) Customplot_xrf->clearPlottables();
  if (Customplot_xrf->item()!=nullptr) Customplot_xrf->clearItems();
  if (Customplot_xrf->graphCount()>0) Customplot_xrf->clearGraphs();
  if (Customplot_xrf->plotLayout()->elementCount()>0) Customplot_xrf->plotLayout()->remove(Customplot_xrf->plotLayout()->element(0,0));
  Customplot_xrf->plotLayout()->simplify();

  QPen pen;
  pen.setWidth(XRF_graph_line_width);

  // valid data
  if (Vec_xrf_obs_data[Selected_file_position].Position!=-1){
    float Step=Vec_xrf_obs_data[Selected_file_position].Step;
    std::vector<float> &Vec_values=Vec_xrf_obs_data[Selected_file_position].Vec_values;
    std::vector<float> &Vec_processed_values=Vec_xrf_obs_data[Selected_file_position].Vec_processed_values;
    std::vector<float> &Vec_processed_shifted_values=Vec_xrf_obs_data[Selected_file_position].Vec_processed_shifted_values;
    std::vector<float> &Vec_values_composition_of_gaussians=Vec_xrf_obs_data[Selected_file_position].Vec_values_composition_of_gaussians;
    //  std::vector<float> &Values1=Vec_xrf_obs_data[Selected_file_position].Vec_smooth_values;
    std::vector<_data_xrf_ns::_data_xrf_ka_kb> &Vec_elements_ka_kb=Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb;

    // values
    QVector<double> x(Vec_values.size()), y(Vec_values.size());
    // insert input data as 1
    for (unsigned int i=0;i<Vec_values.size();i++){
      x[i]=_data_xrf_ns::XRF_START_KEV+Step*float(i);
    }

    if (XRF_show_graph_obs_values){
      //    QCPGraph *Pointer=
      Customplot_xrf->addGraph();
      pen.setColor(XRF_color_obs_raw);
      Customplot_xrf->graph(Pos_graph)->setPen(pen);
      Customplot_xrf->graph(Pos_graph)->setName("OBS raw");
      Customplot_xrf->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);
      //  Customplot_xrf->graph(Pos_graph)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

      for (unsigned int i=0;i<Vec_values.size();i++){
        if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) y[i]=Vec_values[i];
        else y[i]=Vec_values[i]+0.01;
      }

      Customplot_xrf->graph(Pos_graph)->setData(x, y);
      //  Customplot_xrf->graph(Pos_graph)->rescaleAxes(true);
      Pos_graph=Pos_graph+1;
    }

    // insert processed values
    if (XRF_show_graph_processed_values){
      Customplot_xrf->addGraph();
      pen.setColor(XRF_color_obs_processed);
      Customplot_xrf->graph(Pos_graph)->setPen(pen);
      Customplot_xrf->graph(Pos_graph)->setName("OBS proc.");
      Customplot_xrf->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

      for (unsigned int i=0;i<Vec_processed_shifted_values.size();i++){
        //    y[i]=Vec_processed_shifted_values[i];
        if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) y[i]=Vec_processed_values[i];
        else y[i]=Vec_processed_values[i]+0.01;
      }

      Customplot_xrf->graph(Pos_graph)->setData(x, y);
      //  Customplot_xrf->graph(Pos_graph)->rescaleAxes(true);
      Pos_graph=Pos_graph+1;
    }


//    if (XRF_show_graph_processed_values){
//      Customplot_xrf->addGraph();
//      pen.setColor(Qt::magenta);
//      Customplot_xrf->graph(Pos_graph)->setPen(pen);
//      Customplot_xrf->graph(Pos_graph)->setName("OBS proc1.");
//      Customplot_xrf->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

//      for (unsigned int i=0;i<Vec_processed_shifted_values.size();i++){
//        //    y[i]=Vec_processed_shifted_values[i];
//        if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) y[i]=Vec_tube_peak[i];
//        else y[i]=Vec_tube_peak[i]+0.01;
//      }

//      Customplot_xrf->graph(Pos_graph)->setData(x, y);
//      //  Customplot_xrf->graph(Pos_graph)->rescaleAxes(true);
//      Pos_graph=Pos_graph+1;
//    }

    // insert processed_shifted values
    if (XRF_show_graph_processed_shifted_values){
      Customplot_xrf->addGraph();
      pen.setColor(XRF_color_obs_processed_shifted);
      Customplot_xrf->graph(Pos_graph)->setPen(pen);
      Customplot_xrf->graph(Pos_graph)->setName("OBS proc. shifted");
      Customplot_xrf->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

      for (unsigned int i=0;i<Vec_processed_shifted_values.size();i++){
        //    y[i]=Vec_processed_shifted_values[i];
        if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) y[i]=Vec_processed_shifted_values[i];
        else y[i]=Vec_processed_shifted_values[i]+0.01;
      }

      Customplot_xrf->graph(Pos_graph)->setData(x, y);
      //  Customplot_xrf->graph(Pos_graph)->rescaleAxes(true);
      Pos_graph=Pos_graph+1;
    }

    // insert the Gaussian
    if (XRF_show_graph_gaussians_values){
      Customplot_xrf->addGraph();
      pen.setColor(XRF_color_gaussians);
      Customplot_xrf->graph(Pos_graph)->setPen(pen);
      Customplot_xrf->graph(Pos_graph)->setName("Gaussian");
      Customplot_xrf->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);
      for (unsigned int i=0;i<Vec_values.size();i++){
        //    y[i]=Values_gaussians[i];
        if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) y[i]=Vec_values_composition_of_gaussians[i];
        else y[i]=Vec_values_composition_of_gaussians[i]+0.01;
      }
      Customplot_xrf->graph(Pos_graph)->setData(x, y);
      //  Customplot_xrf->graph(Pos_graph)->rescaleAxes(true);
      Pos_graph=Pos_graph+1;
    }

    // add the found elements as peaks
    float Additional_vspace=Vec_xrf_axis_ranges_linear[Selected_file_position].Y_range.upper/30.0f;
    QVector<double> x1(2), y1(2);
    int Pos;

    for (Pos=0;Pos<int(Vec_elements_ka_kb.size());Pos++){
      if (Vec_elements_ka_kb[Pos].Selected){
        x1[0]=float(Vec_elements_ka_kb[Pos].Ka.Position)*Step+3;
        y1[0]=Vec_elements_ka_kb[Pos].Ka.Value;

        x1[1]=float(Vec_elements_ka_kb[Pos].Kb.Position)*Step+3;
        y1[1]=Vec_elements_ka_kb[Pos].Kb.Value;

        Customplot_xrf->addGraph();
        pen.setColor(_window_interpreter_ns::VEC_COLORS[Pos%14]);
        pen.setWidth(XRD_graph_line_width+1);
        Customplot_xrf->graph(Pos_graph)->setPen(pen);
        Customplot_xrf->graph(Pos_graph)->setName(QString::fromStdString(Vec_elements_ka_kb[Pos].Name));
        Customplot_xrf->graph(Pos_graph)->setLineStyle(QCPGraph::lsImpulse);
        Customplot_xrf->graph(Pos_graph)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape((int(QCPScatterStyle::ssCross)+Pos%14)), 10));

        Customplot_xrf->graph(Pos_graph)->setData(x1, y1);
        //Customplot_xrf->graph(Pos_graph)->rescaleAxes(true);

        QCPItemText *Text_label = new QCPItemText(Customplot_xrf);
        Text_label->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        Text_label->position->setCoords(3+Step*float(Vec_elements_ka_kb[Pos].Ka.Position) ,Vec_elements_ka_kb[Pos].Ka.Value+Additional_vspace);
        Text_label->setFont(Font);
        Text_label->setText(QString::fromStdString(Vec_elements_ka_kb[Pos].Name));

        Pos_graph=Pos_graph+1;
      }
    }

    // to show the nearest element
    if (Key_pressed){
      if (Left_button==true){
        // Element name
        QCPItemText *Text_label = new QCPItemText(Customplot_xrf);
        Text_label->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        Text_label->position->setType(QCPItemPosition::ptPlotCoords);
        Text_label->position->setCoords(X_pos, Y_pos);
        Text_label->setFont(Font);
        Text_label->setText(QString::fromStdString(" "+Element_selected.Name)+" ");
        Text_label->setBrush(QBrush(QColor(240, 240, 240)));
        Text_label->setPen(QPen(Qt::black)); // show black border around text

        QCPItemLine *Line = new QCPItemLine(Customplot_xrf);
        Line->end->setParentAnchor(Text_label->bottom);
        Line->start->setCoords(X_pos, 0); // point to (4, 1.6) in x-y-plot coordinates
        Line->setHead(QCPLineEnding::esSpikeArrow);

        // The height to place lower the boxes of Ka and Kb
        QCPRange Range=Customplot_xrf->yAxis->range();
        float Height=float(Range.upper-Range.lower)/15;

        // Ka
        QCPItemText *Text_label_ka = new QCPItemText(Customplot_xrf);
        Text_label_ka->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        Text_label_ka->position->setType(QCPItemPosition::ptPlotCoords);
        Text_label_ka->position->setCoords(X_pos_ka, Y_pos-Height);
        Text_label_ka->setFont(Font);
        Text_label_ka->setText(QString::fromStdString(" Ka "));
        Text_label_ka->setBrush(QBrush(QColor(255, 230, 230)));
        Text_label_ka->setPen(QPen(Qt::black)); // show black border around text

        QCPItemLine *Line_ka = new QCPItemLine(Customplot_xrf);
        Line_ka->end->setParentAnchor(Text_label_ka->bottom);
        Line_ka->start->setCoords(X_pos_ka, 0); // point to (4, 1.6) in x-y-plot coordinates
        Line_ka->setHead(QCPLineEnding::esSpikeArrow);

        // Kb
        QCPItemText *Text_label_kb = new QCPItemText(Customplot_xrf);
        Text_label_kb->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        Text_label_kb->position->setType(QCPItemPosition::ptPlotCoords);
        Text_label_kb->position->setCoords(X_pos_kb, Y_pos-Height);
        Text_label_kb->setFont(Font);
        Text_label_kb->setText(QString::fromStdString(" Kb "));
        Text_label_kb->setBrush(QBrush(QColor(230, 230, 255)));
        Text_label_kb->setPen(QPen(Qt::black)); // show black border around text

        QCPItemLine *Line_kb = new QCPItemLine(Customplot_xrf);
        Line_kb->end->setParentAnchor(Text_label_kb->bottom);
        Line_kb->start->setCoords(X_pos_kb, 0); // point to (4, 1.6) in x-y-plot coordinates
        Line_kb->setHead(QCPLineEnding::esSpikeArrow);
      }
      else{
        QCPItemLine *Line = new QCPItemLine(Customplot_xrf);
        Line->start->setCoords(X_pos, 0); // point to (4, 1.6) in x-y-plot coordinates
        Line->end->setCoords(X_pos,Y_pos);

        QCPItemLine *Line1 = new QCPItemLine(Customplot_xrf);
        Line1->start->setCoords(0, Y_pos); // point to (4, 1.6) in x-y-plot coordinates
        Line1->end->setCoords(X_pos,Y_pos);

        QCPItemText *Text_label = new QCPItemText(Customplot_xrf);
        Text_label->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        Text_label->position->setType(QCPItemPosition::ptPlotCoords);
        Text_label->position->setCoords(X_pos, Y_pos);
        Text_label->setFont(Font);
        Text_label->setText(" "+QString::number(X_pos, 'f', 2)+" , "+QString::number(Y_pos, 'f', 2)+" ");
        Text_label->setBrush(QBrush(QColor(240, 240, 240)));
        Text_label->setPen(QPen(Qt::black));
      }
    }

    Customplot_xrf->xAxis->setVisible(true);
    Customplot_xrf->xAxis->setTickLabels(true);
    // give the axes some labels:
    Customplot_xrf->xAxis->setLabel("KeV");
    Customplot_xrf->yAxis->setLabel("Int");
    // set axes ranges, so we see all data:

    if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR){
      Customplot_xrf->xAxis->setRange(Vec_xrf_axis_ranges_linear[Selected_file_position].X_range);
      Customplot_xrf->yAxis->setRange(Vec_xrf_axis_ranges_linear[Selected_file_position].Y_range);
      QSharedPointer<QCPAxisTicker> Ticker(new QCPAxisTicker);
      Customplot_xrf->yAxis->setTicker(Ticker);
      Customplot_xrf->yAxis->ticker()->setTickCount(5);
      Customplot_xrf->yAxis->setScaleType(QCPAxis::stLinear);
    }
    else{
//      Customplot_xrf->yAxis->setScaleType(QCPAxis::stLogarithmic);
      Customplot_xrf->xAxis->setRange(Vec_xrf_axis_ranges_log[Selected_file_position].X_range); //??
      Customplot_xrf->yAxis->setRange(Vec_xrf_axis_ranges_log[Selected_file_position].Y_range);
      QSharedPointer<QCPAxisTickerLog> Ticker(new QCPAxisTickerLog);
      Customplot_xrf->yAxis->setTicker(Ticker);
      Customplot_xrf->yAxis->ticker()->setTickCount(3);
      Customplot_xrf->yAxis->setScaleType(QCPAxis::stLogarithmic);
    }

    Customplot_xrf->xAxis->ticker()->setTickCount(10);

    Customplot_xrf->yAxis->grid()->setSubGridVisible(true);
    Customplot_xrf->xAxis->grid()->setSubGridVisible(true);


    // make top right axes clones of bottom left axes. Looks prettier:
    Customplot_xrf->axisRect()->setupFullAxesBox();

    QCPTextElement *Title = new QCPTextElement(Customplot_xrf);
    QString Text=QString::fromStdString(Vec_xrf_obs_data[Selected_file_position].File_name);
    Font.setPointSize(XRF_title_font_size);
    Title->setFont(Font);
    Title->setText(Text);
    Customplot_xrf->plotLayout()->insertRow(0);
    Customplot_xrf->plotLayout()->addElement(0, 0,Title);

    Font.setPointSize(XRF_legend_font_size);
    Customplot_xrf->legend->setFont(Font);
  }
  else{ // not valid
    float Step=Vec_xrf_obs_data[XRF_good_file_position].Step;
    std::vector<float> &Vec_values=Vec_xrf_obs_data[XRF_good_file_position].Vec_values;

    // values
    QVector<double> x(Vec_values.size()), y(Vec_values.size());
    // insert input data as 1
    for (unsigned int i=0;i<Vec_values.size();i++){
      x[i]=_data_xrf_ns::XRF_START_KEV+Step*float(i);
      if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) y[i]=0;
      else y[i]=1;
    }

    Customplot_xrf->addGraph();
    pen.setColor(XRF_color_obs_raw);
    Customplot_xrf->graph(Pos_graph)->setPen(pen);
    Customplot_xrf->graph(Pos_graph)->setName("OBS raw");
    Customplot_xrf->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);
    Customplot_xrf->graph(Pos_graph)->setData(x, y);

    Customplot_xrf->xAxis->setVisible(true);
    Customplot_xrf->xAxis->setTickLabels(true);
    // give the axes some labels:
    Customplot_xrf->xAxis->setLabel("KeV");
    Customplot_xrf->yAxis->setLabel("Int");
    // set axes ranges, so we see all data:

    if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR){
      Customplot_xrf->xAxis->setRange(Vec_xrf_axis_ranges_linear[XRF_good_file_position].X_range);
      Customplot_xrf->yAxis->setRange(Vec_xrf_axis_ranges_linear[XRF_good_file_position].Y_range);
      QSharedPointer<QCPAxisTicker> Ticker(new QCPAxisTicker);
      Customplot_xrf->yAxis->setTicker(Ticker);
      Customplot_xrf->yAxis->ticker()->setTickCount(5);
      Customplot_xrf->yAxis->setScaleType(QCPAxis::stLinear);
    }
    else{
      Customplot_xrf->xAxis->setRange(Vec_xrf_axis_ranges_log[XRF_good_file_position].X_range.lower, Vec_xrf_axis_ranges_log[XRF_good_file_position].X_range.upper);
      Customplot_xrf->yAxis->setRange(Vec_xrf_axis_ranges_log[XRF_good_file_position].Y_range.lower, Vec_xrf_axis_ranges_log[XRF_good_file_position].Y_range.upper);
      QSharedPointer<QCPAxisTickerLog> Ticker(new QCPAxisTickerLog);
      Customplot_xrf->yAxis->setTicker(Ticker);
      Customplot_xrf->yAxis->ticker()->setTickCount(3);
      Customplot_xrf->yAxis->setScaleType(QCPAxis::stLogarithmic);
    }

    Customplot_xrf->xAxis->ticker()->setTickCount(10);

    Customplot_xrf->yAxis->grid()->setSubGridVisible(true);
    Customplot_xrf->xAxis->grid()->setSubGridVisible(true);

    // make top right axes clones of bottom left axes. Looks prettier:
    Customplot_xrf->axisRect()->setupFullAxesBox();

    QCPTextElement *Title = new QCPTextElement(Customplot_xrf);
    QString Text=QString::fromStdString("NULL");
    Font.setPointSize(XRF_title_font_size);
    Title->setFont(Font);
    Title->setText(Text);
    Customplot_xrf->plotLayout()->insertRow(0);
    Customplot_xrf->plotLayout()->addElement(0, 0,Title);

    Font.setPointSize(XRF_legend_font_size);
    Customplot_xrf->legend->setFont(Font);
  }

  Customplot_xrf->replot();

  Customplot_xrf->blockSignals(false);
}

//HEA

void _window_interpreter::xrf_convolution(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrf_ns::_data_xrf_obs &Data_xrf_obs1,unsigned int Half_shift)
{
  // The input data is enlarged to include halft_shift to the left and half_shift to the right
  // it is initialized to 0
  std::vector<float> Vec_y_aux(Vec_y.size());
  // vector that will save the results for each step in the convolution
  std::vector<float> Vec_shifted_result(2*Half_shift+1);

  for (size_t i=0;i<2*Half_shift+1;i++){
    // initialize to 0
    std::fill(Vec_y_aux.begin(),Vec_y_aux.end(),0);

    // shift the vector
    Vec_y_aux=shift_vector(Vec_y,int(-Half_shift+i));

    // compute the convolution
    Vec_shifted_result[i]=std::inner_product(Vec_x.begin(), Vec_x.end(), Vec_y_aux.begin(), 0.0f);
  }

  // look for the maximum
  auto It_max = std::max_element(Vec_shifted_result.begin(), Vec_shifted_result.end());
  int Pos;
  if (It_max != Vec_shifted_result.end()){
    // Compute the shif int 2Theta degree
    Pos=std::distance(Vec_shifted_result.begin(), It_max);
    Data_xrf_obs1.Vec_processed_shifted_values=shift_vector(Data_xrf_obs1.Vec_processed_values,Pos-Half_shift);
  }
}



//HEA
// double click reset the position

#ifdef XRD_ACTIVE
void _window_interpreter::chart_bar_xrd_double_click_slot(QMouseEvent *Event)
{
  Q_UNUSED(Event);

  // this is for PDB vs OBS
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL){
    Customplot_xrd->xAxis->setRange(Mat_xrd_spectral_axis_range_linear[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].X_default_range);
    Customplot_xrd->yAxis->setRange(Mat_xrd_spectral_axis_range_linear[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].Y_default_range);
  }
  else{
    Customplot_xrd->xAxis->setRange(Mat_xrd_correlation_axis_range_linear[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].X_default_range);
    Customplot_xrd->yAxis->setRange(Mat_xrd_correlation_axis_range_linear[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].Y_default_range);
  }

  Customplot_xrd->replot();
}

//HEA

void _window_interpreter::chart_bar_xrd_mouse_wheel_slot(QWheelEvent *Event)
{
  // Check if the Shift key is being held down
  if (Event->modifiers() & Qt::ControlModifier) {
    // Get the delta value to determine the direction of the mouse wheel
    int Delta = Event->angleDelta().y();
    QFont Font(Customplot_xrd->font());
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
    Customplot_xrd->setFont(Font);

    xrd_create_obs_spectral_chart(Selected_file_position);
  }
}


//HEA

void _window_interpreter::xrd_x_axis_changed_slot(QCPRange Range)
{
  // for PDB vs OBS
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL){
    Mat_xrd_spectral_axis_range_linear[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].X_range=Range;
  }
  else{
    Mat_xrd_correlation_axis_range_linear[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].X_range=Range;
  }

  Customplot_xrd->replot();
}

//HEA

void _window_interpreter::xrd_y_axis_changed_slot(QCPRange Range)
{

  // for PDB vs OBS
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL){
    Mat_xrd_spectral_axis_range_linear[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].Y_range=Range;
  }
  else{
    Mat_xrd_correlation_axis_range_linear[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].Y_range=Range;
  }

  Customplot_xrd->replot();
}

//HEA

void _window_interpreter::chart_bar_xrd_mouse_press_slot(QMouseEvent* Event)
{
  Key_pressed=true;

  if (Event->button() == Qt::LeftButton){
    Left_button=true;
  }
  else Left_button=false;

  // Crear un cursor personalizado (cursor de mano señalando)
  QCursor Cursor(Qt::CrossCursor);

  // Asignar el cursor al widget
  setCursor(Cursor);

  chart_bar_xrd_mouse_move_slot(Event);
}

//HEA

void _window_interpreter::chart_bar_xrd_mouse_move_slot(QMouseEvent* Event)
{
  if (Key_pressed){
    // get the coordinates
    X_pos=float(Customplot_xrd->xAxis->pixelToCoord(Event->pos().x()));
    Y_pos=float(Customplot_xrd->yAxis->pixelToCoord(Event->pos().y()));

    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
  }
}

//HEA

void _window_interpreter::chart_bar_xrd_mouse_release_slot(QMouseEvent* Event)
{
  Q_UNUSED(Event);

  Key_pressed=false;

  // Crear un cursor personalizado (cursor de mano señalando)
  QCursor Cursor(Qt::ArrowCursor);

  // Asignar el cursor al widget
  setCursor(Cursor);

  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}


//HEA

void _window_interpreter::xrd_create_pdb_obs_sqrt_spectral_chart(int Selected_row_in_mat,int Selected_col_in_mat)
{
  int Pos_graph=0;
  QString Text;

  if (Split_screen==false && XRF_tab_active==true) return;

  QFont Font=QApplication::font();
  Font.setPointSize(Font.pointSize()*1.5);

  // block to not produce an event
  Customplot_xrd->blockSignals(true);

  // clear data
  if (Customplot_xrd->plottable()!=nullptr) Customplot_xrd->clearPlottables();
  if (Customplot_xrd->item()!=nullptr) Customplot_xrd->clearItems();
  if (Customplot_xrd->graphCount()>0) Customplot_xrd->clearGraphs();
  if (Customplot_xrd->plotLayout()->elementCount()>0) Customplot_xrd->plotLayout()->remove(Customplot_xrd->plotLayout()->element(0,0));
  Customplot_xrd->plotLayout()->simplify();

  QPen pen;
  pen.setWidth(XRD_graph_line_width);

  if (Vec_xrd_obs_data[Selected_row_in_mat].Position!=-1){
    std::vector<QColor> Vec_colors={QColor(255,0,0),QColor(0,255,0),QColor(0,0,255),QColor(0,255,255),QColor(255,0,255),QColor(225,225,0),QColor(255,186,14)};

    std::vector<float>& Vec_values_raw=Vec_xrd_obs_data[Selected_row_in_mat].Vec_values;
    std::vector<float>& Vec_values_input=Vec_xrd_obs_data[Selected_row_in_mat].Vec_normalized_values;
    std::vector<float>& Vec_values_compound=Vec_xrd_pdb_data[Selected_col_in_mat].Vec_normalized_values;
    std::string Name_obs=Vec_xrd_obs_data[Selected_row_in_mat].File_name;
    std::string Name_pdb=Vec_xrd_pdb_data[Selected_col_in_mat].File_name;
    _data_xrd_ns::_data_xrd_obs_pdb &Data_xrd_obs_pdb_ref=Mat_xrd_obs_vs_pdb_data[Selected_row_in_mat][Selected_col_in_mat];
    int R2=int(roundf(Mat_xrd_obs_vs_pdb_data[Selected_row_in_mat][Selected_col_in_mat].Correlation_coefficient_squared*100.0f));

    //insert data 1
    if (XRD_data_to_show==true){
      QVector<double> x(Vec_values_input.size()), y(Vec_values_input.size());
      for (unsigned int i=0;i<Vec_values_input.size();i++){
        x[i]=float(_data_xrd_ns::START_2THETA)+float(i)/float(_data_xrd_ns::STEPS_2THETA);
      }


      if (XRD_show_graph_obs_raw){
        Customplot_xrd->addGraph();
        pen.setColor(XRD_color_obs_raw);
        Customplot_xrd->graph(Pos_graph)->setPen(pen);
        Customplot_xrd->graph(Pos_graph)->setName("OBS raw");
        Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

  //      for (unsigned int i=0;i<Vec_values_input.size();i++){
  //        y[i]=Vec_values_raw[i];
  //      }

        for (unsigned int i=0;i<Vec_values_input.size();i++){
          if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR) y[i]=Vec_values_raw[i];
          else y[i]=Vec_values_raw[i]+0.01;
        }

        Customplot_xrd->graph(Pos_graph)->setData(x, y);
        //  Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);
        Pos_graph=Pos_graph+1;
      }


      if (XRD_show_graph_obs_processed){
        Customplot_xrd->addGraph();
        pen.setColor(XRD_color_obs_processed);
        Customplot_xrd->graph(Pos_graph)->setPen(pen);
        Customplot_xrd->graph(Pos_graph)->setName("OBS proc.");
        Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

  //      for (unsigned int i=0;i<Vec_values_input.size();i++){
  //        y[i]=Vec_values_input[i];
  //      }
        for (unsigned int i=0;i<Vec_values_input.size();i++){
          if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR) y[i]=Vec_values_input[i];
          else y[i]=Vec_values_input[i]+0.01;
        }

        Customplot_xrd->graph(Pos_graph)->setData(x, y);
      //  Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);
        Pos_graph=Pos_graph+1;
      }

      if (XRD_show_graph_obs_processed_shifted){
        Customplot_xrd->addGraph();
        pen.setColor(XRD_color_obs_processed_shifted);
        Customplot_xrd->graph(Pos_graph)->setPen(pen);
        Customplot_xrd->graph(Pos_graph)->setName("OBS proc. shifted");
        Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

  //      for (unsigned int i=0;i<Vec_values_input.size();i++){
  //        y[i]=Data_xrd_obs_pdb_ref.Vec_obs_values_shifted[i];
  //      }
        for (unsigned int i=0;i<Vec_values_input.size();i++){
          if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR) y[i]=Data_xrd_obs_pdb_ref.Vec_obs_values_shifted[i];
          else y[i]=Data_xrd_obs_pdb_ref.Vec_obs_values_shifted[i]+0.01;
        }

        Customplot_xrd->graph(Pos_graph)->setData(x, y);
        //  Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);
        Pos_graph=Pos_graph+1;
      }


      //insert data 2 PDB
      if (XRD_show_graph_pdb){
        Customplot_xrd->addGraph();
        pen.setColor(XRD_color_pdb);
        Customplot_xrd->graph(Pos_graph)->setPen(pen);
        Customplot_xrd->graph(Pos_graph)->setName("PDB");
        Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

  //      for (unsigned int i=0;i<Vec_values_compound.size();i++){
  //        y[i]=Vec_values_compound[i];
  //      }
        for (unsigned int i=0;i<Vec_values_compound.size();i++){
          if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR) y[i]=Vec_values_compound[i];
          else y[i]=Vec_values_compound[i]+0.01;
        }
        Customplot_xrd->graph(Pos_graph)->setData(x, y);
      //  Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);
        Pos_graph=Pos_graph+1;
      }

      // insert data 3.  the sqrt of product of both functions
      if (XRD_show_graph_sqrt){
        Customplot_xrd->addGraph();
        pen.setColor(XRD_color_sqrt);
        Customplot_xrd->graph(Pos_graph)->setPen(pen);

        if (XRD_computation_type==_data_xrd_ns::_computation_type::COMPUTATION_TYPE_SQRT)
          Customplot_xrd->graph(Pos_graph)->setName("SQRT(OBS*PDB)");
        else
          Customplot_xrd->graph(Pos_graph)->setName("PDB NOT 0)");

        Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

  //      for (unsigned int i=0;i<Vec_values_input.size();i++){
  //    //    y[i]=sqrtf(Values_input[i]*Values_compound[i]);
  //        y[i]=Data_xrd_obs_pdb_ref.Vec_sqrt_values[i];
  //      }

        for (unsigned int i=0;i<Vec_values_input.size();i++){
          if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR) y[i]=Data_xrd_obs_pdb_ref.Vec_sqrt_values[i];
          else y[i]=Data_xrd_obs_pdb_ref.Vec_sqrt_values[i]+0.01;
        }

        Customplot_xrd->graph(Pos_graph)->setData(x, y);
      //  Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);
        Pos_graph=Pos_graph+1;
      }

      // the title text with the information
    //  int R2=int(roundf(powf(Data_xrd_obs_pdb_ref.Correlation_coefficient_squared,2)*100.0f));
      QString Text_R2=Text+QString(" / R2=%1%").arg(R2,2,10,QChar('0'));
      Text=QString::fromStdString("OBS: "+Name_obs+" vs PDB: "+Name_pdb)+Text_R2;
    }


    // to show the nearest element
    if (Key_pressed){
      if (Left_button==false){
        QCPItemLine *Line = new QCPItemLine(Customplot_xrd);
        Line->start->setCoords(X_pos, 0); // point to (4, 1.6) in x-y-plot coordinates
        Line->end->setCoords(X_pos,Y_pos);

        QCPItemLine *Line1 = new QCPItemLine(Customplot_xrd);
        Line1->start->setCoords(0, Y_pos); // point to (4, 1.6) in x-y-plot coordinates
        Line1->end->setCoords(X_pos,Y_pos);

        QCPItemText *Text_label = new QCPItemText(Customplot_xrd);
        Text_label->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        Text_label->position->setType(QCPItemPosition::ptPlotCoords);
        Text_label->position->setCoords(X_pos, Y_pos);
        Text_label->setFont(Font);
        Text_label->setText(" "+QString::number(X_pos, 'f', 2)+" , "+QString::number(Y_pos, 'f', 2)+" ");
        Text_label->setBrush(QBrush(QColor(240, 240, 240)));
        Text_label->setPen(QPen(Qt::black));
      }
    }

    //
    Customplot_xrd->xAxis->setVisible(true);
    Customplot_xrd->xAxis->setTickLabels(true);
    // give the axes some labels:
    Customplot_xrd->xAxis->setLabel("2\u03b8");
    Customplot_xrd->yAxis->setLabel("Int");

    if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR){      
      Customplot_xrd->xAxis->setRange(Mat_xrd_spectral_axis_range_linear[Selected_row_in_mat][Selected_col_in_mat].X_range);
      Customplot_xrd->yAxis->setRange(Mat_xrd_spectral_axis_range_linear[Selected_row_in_mat][Selected_col_in_mat].Y_range);
      QSharedPointer<QCPAxisTicker> Ticker(new QCPAxisTicker);
      Customplot_xrd->yAxis->setTicker(Ticker);
      Customplot_xrd->yAxis->ticker()->setTickCount(5);
      Customplot_xrd->yAxis->setScaleType(QCPAxis::stLinear);
    }
    else{
      Customplot_xrd->xAxis->setRange(Mat_xrd_spectral_axis_range_log[Selected_row_in_mat][Selected_col_in_mat].X_range);
      Customplot_xrd->yAxis->setRange(Mat_xrd_spectral_axis_range_log[Selected_row_in_mat][Selected_col_in_mat].Y_range);
      QSharedPointer<QCPAxisTickerLog> Ticker(new QCPAxisTickerLog);
      Customplot_xrd->yAxis->setTicker(Ticker);
      Customplot_xrd->yAxis->ticker()->setTickCount(3);
      Customplot_xrd->yAxis->setScaleType(QCPAxis::stLogarithmic);
    }

    Customplot_xrd->xAxis->ticker()->setTickCount(10);

    Customplot_xrd->yAxis->grid()->setSubGridVisible(true);
    Customplot_xrd->xAxis->grid()->setSubGridVisible(true);

    Customplot_xrd->axisRect()->setupFullAxesBox();

    //+QString(" / R^2=%1% / %2 of %3 peaks").arg(R2).arg(Data_xrd_obs_pdb_ref.Num_counted_peaks).arg(Data_xrd_obs_pdb_ref.Num_peaks);

    QCPTextElement *Title = new QCPTextElement(Customplot_xrd);
    Font.setPointSize(XRD_title_font_size);
    Title->setFont(Font);
    Title->setText(Text);
    Customplot_xrd->plotLayout()->insertRow(0);
    Customplot_xrd->plotLayout()->addElement(0, 0,Title);

    Font.setPointSize(XRD_legend_font_size);
    Customplot_xrd->legend->setFont(Font);
  }
  else{
    // not valid
    std::vector<float>& Vec_values_input=Vec_xrd_obs_data[XRD_good_file_position].Vec_normalized_values;

    QVector<double> x(Vec_values_input.size()), y(Vec_values_input.size());
    for (unsigned int i=0;i<Vec_values_input.size();i++){
      x[i]=float(_data_xrd_ns::START_2THETA)+float(i)/float(_data_xrd_ns::STEPS_2THETA);
      if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR) y[i]=0;
      else y[i]=1;
    }

    Customplot_xrd->addGraph();
    pen.setColor(XRD_color_obs_raw);
    Customplot_xrd->graph(Pos_graph)->setPen(pen);
    Customplot_xrd->graph(Pos_graph)->setName("OBS raw");
    Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);
    Customplot_xrd->graph(Pos_graph)->setData(x, y);

    Customplot_xrd->xAxis->setVisible(true);
    Customplot_xrd->xAxis->setTickLabels(true);
    // give the axes some labels:
    Customplot_xrd->xAxis->setLabel("2\u03b8");
    Customplot_xrd->yAxis->setLabel("Int");

    if (XRD_chart_scale==_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR){
      Customplot_xrd->yAxis->setScaleType(QCPAxis::stLinear);
      Customplot_xrd->xAxis->setRange(Mat_xrd_spectral_axis_range_linear[XRD_good_file_position][Selected_col_in_mat].X_range);
      Customplot_xrd->yAxis->setRange(Mat_xrd_spectral_axis_range_linear[XRD_good_file_position][Selected_col_in_mat].Y_range);
      QSharedPointer<QCPAxisTicker> Ticker(new QCPAxisTicker);
      Customplot_xrd->yAxis->setTicker(Ticker);
      Customplot_xrd->yAxis->ticker()->setTickCount(5);
    }
    else{
      Customplot_xrd->yAxis->setScaleType(QCPAxis::stLogarithmic);
      Customplot_xrd->xAxis->setRange(Mat_xrd_spectral_axis_range_log[XRD_good_file_position][Selected_col_in_mat].X_range);
      Customplot_xrd->yAxis->setRange(Mat_xrd_spectral_axis_range_log[XRD_good_file_position][Selected_col_in_mat].Y_range);
      QSharedPointer<QCPAxisTickerLog> Ticker(new QCPAxisTickerLog);
      Customplot_xrd->yAxis->setTicker(Ticker);
      Customplot_xrd->yAxis->ticker()->setTickCount(3);
    }

    Customplot_xrd->xAxis->ticker()->setTickCount(10);

    Customplot_xrd->yAxis->grid()->setSubGridVisible(true);
    Customplot_xrd->xAxis->grid()->setSubGridVisible(true);

    Customplot_xrd->axisRect()->setupFullAxesBox();

    if (XRF_chart_scale==_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR) Customplot_xrf->yAxis->setScaleType(QCPAxis::stLinear);
    else Customplot_xrf->yAxis->setScaleType(QCPAxis::stLogarithmic);


    //+QString(" / R^2=%1% / %2 of %3 peaks").arg(R2).arg(Data_xrd_obs_pdb_ref.Num_counted_peaks).arg(Data_xrd_obs_pdb_ref.Num_peaks);

    QCPTextElement *Title = new QCPTextElement(Customplot_xrd);
    Font.setPointSize(XRD_title_font_size);
    Title->setFont(Font);
    Title->setText("NULL");
    Customplot_xrd->plotLayout()->insertRow(0);
    Customplot_xrd->plotLayout()->addElement(0, 0,Title);

    Font.setPointSize(XRD_legend_font_size);
    Customplot_xrd->legend->setFont(Font);
  }

  Customplot_xrd->replot();

  Customplot_xrd->blockSignals(false);
}

//HEA

void _window_interpreter::xrd_create_obs_spectral_chart(int Selected_row_in_table)
{
  int Pos_graph=0;

  std::vector<float> &Vec_values_input=Vec_xrd_obs_data[Selected_row_in_table].Vec_values;
  std::vector<float> &Vec_values_modified=Vec_xrd_obs_data[Selected_row_in_table].Vec_filtered_values;
  std::string Name=Vec_xrd_obs_data[Selected_row_in_table].File_name;
//  float Step=0.05f;

  // block to not produce an event
  Customplot_xrd->blockSignals(true);

  // clear data
  Customplot_xrd->clearPlottables();
  Customplot_xrd->clearItems();
  Customplot_xrd->clearGraphs();
  Customplot_xrd->plotLayout()->remove(Customplot_xrd->plotLayout()->element(0,0));
  Customplot_xrd->plotLayout()->simplify();

  QPen pen;
  pen.setWidth(XRD_graph_line_width);

  //insert data 1
  Customplot_xrd->addGraph();
  pen.setColor(Qt::red);
  Customplot_xrd->graph(Pos_graph)->setPen(pen);
  Customplot_xrd->graph(Pos_graph)->setName("Raw OBS");
  Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

  QVector<double> x(Vec_values_input.size()), y(Vec_values_input.size());
  for (unsigned int i=0;i<Vec_values_input.size();i++){
    x[i]=_data_xrd_ns::START_2THETA+float(i)/_data_xrd_ns::STEPS_2THETA;
    y[i]=Vec_values_input[i];
  }
  Customplot_xrd->graph(Pos_graph)->setData(x, y);
//  Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);
  Pos_graph=Pos_graph+1;

  //insert data 2
  Customplot_xrd->addGraph();
  pen.setColor(Qt::black);
  Customplot_xrd->graph(Pos_graph)->setPen(pen);
  Customplot_xrd->graph(Pos_graph)->setName("Processed OBS");
  Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

  for (unsigned int i=0;i<Vec_values_modified.size();i++){
    y[i]=Vec_values_modified[i];
  }
  Customplot_xrd->graph(Pos_graph)->setData(x, y);
//  Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);

  // general
  Customplot_xrd->xAxis->setVisible(true);
  Customplot_xrd->xAxis->setTickLabels(true);
  // give the axes some labels:
  Customplot_xrd->xAxis->setLabel("2\u03b8");
  Customplot_xrd->yAxis->setLabel("Int");

  Customplot_xrd->xAxis->blockSignals(true);
  Customplot_xrd->xAxis->setRange(Vec_xrd_axis_ranges_linear[Selected_row_in_table].X_range);
  Customplot_xrd->xAxis->blockSignals(false);

  Customplot_xrd->yAxis->blockSignals(true);
  Customplot_xrd->yAxis->setRange(Vec_xrd_axis_ranges_linear[Selected_row_in_table].Y_range);
  Customplot_xrd->yAxis->blockSignals(false);

  Customplot_xrd->xAxis->ticker()->setTickCount(10);

  Customplot_xrd->yAxis->grid()->setSubGridVisible(true);
  Customplot_xrd->xAxis->grid()->setSubGridVisible(true);

  Customplot_xrd->axisRect()->setupFullAxesBox();

  QFont Font;
  Font.setPixelSize(XRD_title_font_size);
  QCPTextElement *Title = new QCPTextElement(Customplot_xrd);
  Title->setFont(Font);
  Title->setText("Raw OBS / Processed OBS");
  Customplot_xrd->plotLayout()->insertRow(0);
  Customplot_xrd->plotLayout()->addElement(0, 0,Title);

  Font.setPointSize(XRD_legend_font_size);
  Customplot_xrd->legend->setFont(Font);

  Customplot_xrd->replot();

  Customplot_xrd->blockSignals(false);

//  Table_xrd_obs_vs_pdb_data->scrollTo(Table_xrd_obs_vs_pdb_data->model()->index(Selected_row_in_table,0));

  // update Spinbox
  Spinbox_xrd_num_steps_smooth->blockSignals(true);
  Spinbox_xrd_num_steps_smooth->setValue(XRD_num_steps_smooth);
  Spinbox_xrd_num_steps_smooth->blockSignals(false);
}

//HEA

void _window_interpreter::xrd_create_pdb_sqrt_correlation_chart(int Selected_row_in_mat,int Selected_col_in_mat)
{
  int Pos_graph=0;

  if (Split_screen==false && XRF_tab_active==true) return;

  QFont Font=QApplication::font();
  Font.setPointSize(Font.pointSize()*1.5);

  // block to not produce an event
  Customplot_xrd->blockSignals(true);

  // clear data
  // clear data
  if (Customplot_xrd->plottable()!=nullptr) Customplot_xrd->clearPlottables();
  if (Customplot_xrd->item()!=nullptr) Customplot_xrd->clearItems();
  if (Customplot_xrd->graphCount()>0) Customplot_xrd->clearGraphs();
  if (Customplot_xrd->plotLayout()->elementCount()>0) Customplot_xrd->plotLayout()->remove(Customplot_xrd->plotLayout()->element(0,0));
  Customplot_xrd->plotLayout()->simplify();

  QPen pen;
  pen.setWidth(XRD_graph_line_width);

  if (Vec_xrd_obs_data[Selected_row_in_mat].Position!=-1){
    std::vector<QColor> Vec_colors={QColor(255,0,0),QColor(0,255,0),QColor(0,0,255),QColor(0,255,255),QColor(255,0,255),QColor(225,225,0),QColor(255,186,14)};

    std::string Name_obs=Vec_xrd_obs_data[Selected_row_in_mat].File_name;
    std::string Name_pdb=Vec_xrd_pdb_data[Selected_col_in_mat].File_name;

    std::vector<float>& Vec_sqrt=Mat_xrd_obs_vs_pdb_data[Selected_row_in_mat][Selected_col_in_mat].Vec_sqrt_values;
    std::vector<float>& Vec_pdb=Vec_xrd_pdb_data[Selected_col_in_mat].Vec_normalized_values;
    float Slope=Mat_xrd_obs_vs_pdb_data[Selected_row_in_mat][Selected_col_in_mat].Slope;
    float Intercept=Mat_xrd_obs_vs_pdb_data[Selected_row_in_mat][Selected_col_in_mat].Intercept;
    int R2=int(roundf(Mat_xrd_obs_vs_pdb_data[Selected_row_in_mat][Selected_col_in_mat].Correlation_coefficient_squared*100.0f));

    QString Text;
    float Min_x=0;
    float Min_y=0;
    float Max_x=1.0f;
    float Max_y=1.0f;

    if (XRD_data_to_show==true){
        //insert data 1
        Customplot_xrd->addGraph();
        pen.setColor(Qt::black);
        Customplot_xrd->graph(Pos_graph)->setPen(pen);
        Customplot_xrd->graph(Pos_graph)->setName("SQRT(OBS*PDB)");
        Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsNone);
        Customplot_xrd->graph(Pos_graph)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

        QVector<double> x(Vec_sqrt.size()), y(Vec_sqrt.size());
        for (unsigned int i=0;i<Vec_sqrt.size();i++){
          if (Vec_pdb[i]>Max_x) Max_x=Vec_pdb[i];
          x[i]=Vec_pdb[i];
          if (Vec_sqrt[i]>Max_y) Max_y=Vec_sqrt[i];
          y[i]=Vec_sqrt[i];
        }
        Customplot_xrd->graph(Pos_graph)->setData(x, y);
        Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);
        Pos_graph=Pos_graph+1;

        //  //insert data 2 PDB
        Customplot_xrd->addGraph();
        pen.setColor(Qt::blue);
        Customplot_xrd->graph(Pos_graph)->setPen(pen);
        Customplot_xrd->graph(Pos_graph)->setName("Corr. line");
        Customplot_xrd->graph(Pos_graph)->setLineStyle(QCPGraph::lsLine);

        //  float Step=Max_x/float(Vec_sqrt.size());
        for (unsigned int i=0;i<Vec_sqrt.size();i++){
          //x[i]=float(i);
          y[i]=Slope*x[i]+Intercept;
        }
        Customplot_xrd->graph(Pos_graph)->setData(x, y);
        Customplot_xrd->graph(Pos_graph)->rescaleAxes(true);
        Pos_graph=Pos_graph+1;

        QString Text_R2=Text+QString(" / R2=%1%").arg(R2,2,10,QChar('0'));
        Text=QString::fromStdString("OBS: "+Name_obs+" vs PDB: "+Name_pdb)+Text_R2;
        Min_x=-1;
        Min_y=-1;
    }

    //
    Customplot_xrd->xAxis->setVisible(true);
    Customplot_xrd->xAxis->setTickLabels(true);
    Customplot_xrd->yAxis->setLabel("Int");

    QCPRange Range_x(Min_x,Max_x*1.05f);
    QCPRange Range_y(Min_y,Max_y*1.05f);
    Customplot_xrd->xAxis->setRange(Range_x);
    Customplot_xrd->yAxis->setRange(Range_y);
    Customplot_xrd->xAxis->ticker()->setTickCount(10);

    Customplot_xrd->yAxis->grid()->setSubGridVisible(true);
    Customplot_xrd->xAxis->grid()->setSubGridVisible(true);

    Customplot_xrd->axisRect()->setupFullAxesBox();

    QCPTextElement *Title = new QCPTextElement(Customplot_xrd);
    Font.setPointSize(XRD_title_font_size);
    Title->setFont(Font);
    Title->setText(Text);
    Customplot_xrd->plotLayout()->insertRow(0);
    Customplot_xrd->plotLayout()->addElement(0, 0,Title);
    Customplot_xrd->replot();

    Customplot_xrd->blockSignals(false);
  }
  else{ // not valid

  }
}

//HEA

void show_data(std::vector<float> &Data,int Start, int Num_values)
{
  float Pos;

  for (int i=Start;i<Start+Num_values;i++){
    Pos=(float(i)+_data_xrd_ns::START_2THETA*_data_xrd_ns::STEPS_2THETA)/_data_xrd_ns::STEPS_2THETA;
    std::cout << Pos << " " << Data[i] << std::endl;
  }

  std::cout << "/**********/ " << std::endl;

}


//HEA

//void _window_interpreter::remove_noise_xrd_pdb(std::vector<float> &Raw_data, std::vector<float> &Normalized_data, unsigned int Num_steps_smooth, unsigned int Num_steps_subtract_mean)
//{
//  show_data(Raw_data,Position_show,Num_positions_show);

//  std::vector<float> Smooth_data=Raw_data;

//  Smooth_data=Raw_data;

//  if (XRD_smooth_type==_data_xrd_ns::_smooth_type::SMOOTH_TYPE_MEAN) smooth_data_mean(Num_steps_smooth,Smooth_data,Smooth_data);
//  else smooth_data_gs(Num_steps_smooth,Raw_data,Smooth_data);

//  std::vector<float> Filtered_data=Smooth_data;
//  float Mean;
//  for (unsigned int Step=0;Step<=Num_steps_subtract_mean;Step++){
//    Mean=0;

//    for (unsigned int i=0;i<Filtered_data.size();i++) Mean=Mean+Filtered_data[i];
//    Mean=Mean/float(Filtered_data.size());

//    // remove the mean
//    for (unsigned int i=0;i<Filtered_data.size();i++){
//      Filtered_data[i]=Smooth_data[i]-Mean;
//      if (Filtered_data[i]<0) Filtered_data[i]=0;
//    }
//  }

//  // normalize
//  Normalized_data.resize(Filtered_data.size());

//  if (XRD_normalization_type==_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_MEAN){
//    Mean=0;
//    for (unsigned int i=0;i<Filtered_data.size();i++){
//      Mean=Mean+Filtered_data[i];
//    }
//    Mean=Mean/float(Filtered_data.size());

//    for (unsigned int i=0;i<Filtered_data.size();i++) Normalized_data[i]=Filtered_data[i]/Mean;
//  }
//  else{
//    //  Normalize 0-1
//    float Max=*(max_element(Filtered_data.begin(), Filtered_data.end()));

//    for (unsigned int i=0;i<Normalized_data.size();i++) Normalized_data[i]=Filtered_data[i]/Max;
//  }
//}


//HEA

void _window_interpreter::xrd_preprocess_data(std::vector<float> &Raw_data, std::vector<float> &Smooth_data, std::vector<float> &Filtered_data, std::vector<float> &Normalized_data, unsigned int Num_steps_smooth, unsigned int Num_steps_subtract_mean)
{
  Q_UNUSED(Num_steps_subtract_mean)

  // remove noise
  Smooth_data.resize(Raw_data.size());
  if (XRD_smooth_type==_data_xrd_ns::_smooth_type::SMOOTH_TYPE_MEAN) smooth_data_mean(Num_steps_smooth,Raw_data,Smooth_data);
  else smooth_data_gs(Num_steps_smooth,Raw_data,Smooth_data);

  //
  remove_background(XRD_num_steps_subtract_background,Smooth_data,Filtered_data);

  if (XRD_pdb_mode==true){
    for (unsigned int i=0;i<Filtered_data.size();i++){
      Filtered_data[i]=Filtered_data[i]-XRD_level_subtract;
      if (Filtered_data[i]<0) Filtered_data[i]=0;
    }
  }

  // normalize
  Normalized_data.resize(Filtered_data.size());
  if (XRD_normalization_type==_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_MEAN){
    float Mean=std::accumulate(Filtered_data.begin(),Filtered_data.end(),0.0f);

    Mean=Mean/float(Filtered_data.size());
    for (unsigned int i=0;i<Filtered_data.size();i++) Normalized_data[i]=Filtered_data[i]/Mean;

  }
  else{
    //  Normalize 0-100
    float Max=*(max_element(Filtered_data.begin(), Filtered_data.end()));

    for (unsigned int i=0;i<Normalized_data.size();i++) Normalized_data[i]=Filtered_data[i]*_data_xrd_ns::NORMALIZATION_FACTOR/Max;
  }
}

/*
void _window_interpreter::xrd_preprocess_data(std::vector<float> &Raw_data, std::vector<float> &Smooth_data, std::vector<float> &Filtered_data, std::vector<float> &Normalized_data, unsigned int Num_steps_smooth, unsigned int Num_steps_subtract_mean)
{
  //  cout << "raw" << endl;
  //  show_data(Raw_data,Position_show,Num_positions_show);

  bool XRD_mean_smooth_type=false;

  // remove noise
  Smooth_data.resize(Raw_data.size());
  if (XRD_mean_smooth_type==true) smooth_data_mean(Num_steps_smooth,Raw_data,Smooth_data);
  else smooth_data_gs(Num_steps_smooth,Raw_data,Smooth_data);

  //  cout << "smooth" << endl;
  //  show_data(Smooth_data,Position_show,Num_positions_show);


  Filtered_data=Smooth_data;
  // subtract mean
  float Mean;
//  for (unsigned int Step=0;Step<Num_steps_subtract_mean;Step++){
//    Mean=0;
//    for (unsigned int i=0;i<Filtered_data.size();i++) Mean=Mean+Filtered_data[i];
//    //    cout << "mean=" << Mean << endl;
//    Mean=Mean/float(Filtered_data.size());
//    //    cout << "mean=" << Mean << " num=" << Filtered_data.size() << endl;

//    for (unsigned int i=0;i<Filtered_data.size();i++){
//      Filtered_data[i]=Filtered_data[i]-Mean;
//      if (Filtered_data[i]<0) Filtered_data[i]=0;
//    }
//  }

  //  cout << "subtract mean" << endl;
  //  show_data(Filtered_data,Position_show,Num_positions_show);

  // normalize
  bool XRD_mean_type_normalization=false;

  Normalized_data.resize(Filtered_data.size());
  if (XRD_mean_type_normalization==true){
    Mean=0;
    for (unsigned int i=0;i<Filtered_data.size();i++){
      Mean=Mean+Filtered_data[i];
    }

    Mean=Mean/float(Filtered_data.size());
    for (unsigned int i=0;i<Filtered_data.size();i++) Normalized_data[i]=Filtered_data[i]/Mean;

    //    cout << "normalized" << endl;
    //    show_data(Normalized_data,Position_show,Num_positions_show);
    //    exit(-1);
  }
  else{
    //  Normalize 0-100
    float Max=*(max_element(Filtered_data.begin(), Filtered_data.end()));

    for (unsigned int i=0;i<Normalized_data.size();i++) Normalized_data[i]=Filtered_data[i]*_data_xrd_ns::NORMALIZATION_FACTOR/Max;
  }
}
*/


#endif

//HEA
// This apply a convolution to search the maximum correlation
// Shift is the size of the interval. Half on the interval to the right and the left is applied
// Vec_x is the input data PDB
// Vec_y is the pigment data OBS

#ifdef XRD_ACTIVE
//void _window_interpreter::xrd_convolution(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrd_ns::_data_xrd_obs_pdb &Data_xrd_obs_pdb1,unsigned int Half_shift)
//{
//  // The input data is enlarged to include halft_shift to the left and half_shift to the right
//  // it is initialized to 0
//  std::vector<float> Vec_x_aux(Vec_x.size()+2*Half_shift);
//  std::vector<_data_xrd_ns::_data_xrd_obs_pdb> Data_xrd_obs_pdb_aux;

//  // vector that will save the results for each step in the convolution
//  Data_xrd_obs_pdb_aux.resize(2*Half_shift+1);

//  // initialize to 0
//  std::fill(Vec_x_aux.begin(),Vec_x_aux.end(),0);

//  // copy the original data but shifted to the left half_shift
//  std::copy(Vec_x.begin(),Vec_x.end(),Vec_x_aux.begin()+Half_shift);


//  for (int i=0;i<int(2*Half_shift+1);i++){
//    // Do the convolution
//    linear_regression(Vec_x_aux.begin()+i, Vec_y.begin(),Vec_x.size(),Data_xrd_obs_pdb_aux[i]);
//  }

//  // look for the maximum
//  float Maximum=-1;
//  unsigned int Pos;
//  for (unsigned int i=0;i<Data_xrd_obs_pdb_aux.size();i++){
//    if (Data_xrd_obs_pdb_aux[i].Correlation_coefficient_squared>Maximum){
//      Maximum=Data_xrd_obs_pdb_aux[i].Correlation_coefficient_squared;
//      Pos=i;
//    }
//  }

////  if (Pos!=Half_shift){
////    int o=0;
////  }

//  // Compute the shif int 2Theta degree
//  float Shift_aux=(float(Pos)-float(Half_shift))/_data_xrd_ns::STEPS_2THETA;

//  Data_xrd_obs_pdb1.Correlation_coefficient_squared=Data_xrd_obs_pdb_aux[Pos].Correlation_coefficient_squared;
//  Data_xrd_obs_pdb1.Slope=Data_xrd_obs_pdb_aux[Pos].Slope;
//  Data_xrd_obs_pdb1.Intercept=Data_xrd_obs_pdb_aux[Pos].Intercept;
//  Data_xrd_obs_pdb1.Shift=Shift_aux;
//}

std::vector<float> _window_interpreter::shift_vector(std::vector<float> &Vec_data,int Shift)
{
  std::vector<float> Vec_data_aux(Vec_data.size(),0);

  if (Shift<0) std::copy(Vec_data.begin()-Shift,Vec_data.end(),Vec_data_aux.begin());
  else std::copy(Vec_data.begin(),Vec_data.end()-Shift,Vec_data_aux.begin()+Shift);

  return Vec_data_aux;
}


// Vec_x = PDB_data
// Vec_y = OBS_data

void _window_interpreter::xrd_convolution(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrd_ns::_data_xrd_obs_pdb &Data_xrd_obs_pdb1,unsigned int Half_shift)
{
  // The input data is enlarged to include halft_shift to the left and half_shift to the right
  // it is initialized to 0
  std::vector<float> Vec_y_aux(Vec_y.size());
  // the result of the SQRT
  std::vector<float> Vec_sqrt_values(Vec_y.size());

  // vector that will save the results for each step in the convolution
  std::vector<_data_xrd_ns::_data_xrd_obs_pdb> Vec_data_shift_results(2*Half_shift+1);

  for (size_t i=0;i<2*Half_shift+1;i++){
    // initialize to 0
    std::fill(Vec_y_aux.begin(),Vec_y_aux.end(),0);

    // shift the vector
    Vec_y_aux=shift_vector(Vec_y,int(-Half_shift+i));

    // compute the sqrt of the PDB with the SQRT(PDB*SHIFT(OBS))
    xrd_compute_sqrt_values(Vec_x,Vec_y_aux,Vec_sqrt_values);

    // Do the regression
    linear_regression(Vec_x.begin(), Vec_sqrt_values.begin(),Vec_x.size(),Vec_data_shift_results[i]);
//    linear_regression1(Vec_x, Vec_sqrt_values,Vec_data_shift_results[i]);
  }

  // look for the maximum
  float Maximum=-1;
  unsigned int Pos;
  for (unsigned int i=0;i<Vec_data_shift_results.size();i++){
    if (Vec_data_shift_results[i].Correlation_coefficient_squared>Maximum){
      Maximum=Vec_data_shift_results[i].Correlation_coefficient_squared;
      Pos=i;
    }
  }

  // Compute the shif int 2Theta degree
  float Shift_aux=(float(Pos)-float(Half_shift))/_data_xrd_ns::STEPS_2THETA;

  Data_xrd_obs_pdb1.Correlation_coefficient_squared=Vec_data_shift_results[Pos].Correlation_coefficient_squared;
  Data_xrd_obs_pdb1.Slope=Vec_data_shift_results[Pos].Slope;
  Data_xrd_obs_pdb1.Intercept=Vec_data_shift_results[Pos].Intercept;
  Data_xrd_obs_pdb1.Shift=Shift_aux;
  // the shifted data
  Data_xrd_obs_pdb1.Vec_obs_values_shifted=shift_vector(Vec_y,-Half_shift+Pos);
  // the sqrt
  xrd_compute_sqrt_values(Vec_x,Data_xrd_obs_pdb1.Vec_obs_values_shifted,Vec_sqrt_values);
  Data_xrd_obs_pdb1.Vec_sqrt_values=Vec_sqrt_values;
}
#endif

//HEA

#ifdef XRD_ACTIVE
void _window_interpreter::linear_regression(std::vector<float>::iterator Iter_vec_x, std::vector<float>::iterator Iter_vec_y,int Num_iter, _data_xrd_ns::_data_xrd_obs_pdb &Data_xrd_obs_pdb1)
{
  float Sum_x=0;
  float Sum_x2=0;
  float Sum_y=0;
  float Sum_y2=0;
  float Sum_xy=0;
  float Numerator=0;
  float Denominator=0;
  float n=float(Num_iter);
//  float n=0;

//  // To use only the values when PDB is !=0
//  for(int i=0;i<Num_iter;i++){
//    if (*Iter_vec_y!=0){
//      Sum_x = Sum_x + *Iter_vec_x;
//      Sum_x2 = Sum_x2 + *Iter_vec_x*(*Iter_vec_x);
//      Sum_y = Sum_y + *Iter_vec_y;
//      Sum_y2 = Sum_y2 + *Iter_vec_y*(*Iter_vec_y);
//      Sum_xy = Sum_xy + *Iter_vec_x*(*Iter_vec_y);
//      Iter_vec_x++;
//      Iter_vec_y++;
//      n++;
//    }
//    else{
//      Iter_vec_x++;
//      Iter_vec_y++;
//    }
//  }

  for(int i=0;i<Num_iter;i++){
    Sum_x = Sum_x + *Iter_vec_x;
    Sum_x2 = Sum_x2 + *Iter_vec_x*(*Iter_vec_x);
    Sum_y = Sum_y + *Iter_vec_y;
    Sum_y2 = Sum_y2 + *Iter_vec_y*(*Iter_vec_y);
    Sum_xy = Sum_xy + *Iter_vec_x*(*Iter_vec_y);
    Iter_vec_x++;
    Iter_vec_y++;
  }

  Denominator=n*Sum_x2-Sum_x*Sum_x;
  if (Denominator!=0){
    Data_xrd_obs_pdb1.Slope = (n*Sum_xy-Sum_x*Sum_y)/Denominator;

    Data_xrd_obs_pdb1.Intercept = (Sum_y - Data_xrd_obs_pdb1.Slope*Sum_x)/n;
    Numerator=Sum_xy - Sum_x * Sum_y / n;
    Denominator=sqrtf((Sum_x2 - Sum_x*Sum_x/n) *(Sum_y2 - Sum_y*Sum_y/n));
    if (Denominator!=0){
      // r_squared
      Data_xrd_obs_pdb1.Correlation_coefficient_squared = std::pow(Numerator/Denominator,2);

//      Data_xrd_obs_pdb1.Correlation_coefficient_squared=powf(Data_xrd_obs_pdb1.Correlation_coefficient_squared,2);

//      if (Data_xrd_obs_pdb1.Correlation_coefficient_squared<0) Data_xrd_obs_pdb1.Correlation_coefficient_squared=0;
    }
    else{
      Data_xrd_obs_pdb1.Correlation_coefficient_squared=0;
    }
  }
  else{
    Data_xrd_obs_pdb1.Correlation_coefficient_squared=0;
  }

//  std::cout << "m1=" << Data_xrd_obs_pdb1.Slope << " b1=" << Data_xrd_obs_pdb1.Intercept << " r2=" << std::pow(Data_xrd_obs_pdb1.Correlation_coefficient_squared,2) << std::endl;
}
#endif

//HEA
#ifdef XRD_ACTIVE
/*
out << "Data descriptions -----------------------------------------------------------------\n";
cout << "Sample Size: " << regression.sample << "     X mean: " << regression.xbar << ";      Y mean: " << regression.ybar << "\n";
cout << "Pearson correlation (r): " << regression.r << "\n\n";
cout << "Regression Model  -----------------------------------------------------------------\n";
cout << "R squared:           " << regression.rsquared << "\n";
cout << "Alpha Coefficient:   " << regression.alpha << "\n";
cout << "Beta Coefficient:    " << regression.beta << "     Std. Error (B):  " << regression.SEBeta << "     t-value:   " << regression.t << "\n\n";
cout << "Residuals         -----------------------------------------------------------------\n";
cout << "Residual Std. Error: " << regression.residualSE << " on " << (regression.sample-2) << " degrees of freedom\n";
cout << "Mean Residual Dist.: " << regression.residualmean << "\n";
cout << "Max. Residual:       " << regression.residualmax << "\n";
cout << "Min. Residual:       " << regression.residualmin << "\n \n";
cout << "Additional Stats  -----------------------------------------------------------------\n";
cout << "SSResiduals          " << regression.SSR << "\n";
cout << "SSExplained          " << regression.SSE << "\n";
cout << "SSTotal              " << regression.SST << "\n\n";


void _window_interpreter::linear_regression1(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrd_ns::_data_xrd_obs_pdb &Data_xrd_obs_pdb1)
{
  float WN1 = 0, WN2 = 0, WN3 = 0, WN4 = 0, Sy = 0, Sx = 0;
  float r = 0, rsquared = 0, alpha = 0, beta = 0, x = 0, y = 0;
  float yhat = 0, ybar = 0, xbar = 0;
  float SSR = 0, SSE = 0, SST = 0;
  float residualSE = 0, residualmax = 0, residualmin = 0, residualmean = 0, t = 0;
  float SEBeta = 0;
  std::vector<float> residuals;

  //Calculate means
  int samplesize=float(Vec_x.size());
  xbar = std::accumulate(Vec_x.begin(),Vec_x.end(),0.0f)/float(samplesize);
  ybar = std::accumulate(Vec_y.begin(),Vec_y.end(),0.0f)/float(samplesize);

  //Calculate r correlation
  for (int n = 0; n < samplesize; ++n){
    WN1 += (Vec_x[n]-xbar)*(Vec_y[n]-ybar);
    WN2 += pow((Vec_x[n]-xbar), 2);
    WN3 += pow((Vec_y[n]-ybar), 2);
  }
  WN4 = WN2 * WN3;
  r = WN1 / (sqrt(WN4));

  //Calculate alpha and beta
  Sy = sqrt(WN3/float(samplesize-1));
  Sx = sqrt(WN2/float(samplesize-1));
  beta = r*(Sy/Sx);
  alpha = ybar - beta*xbar;

  //Calculate SSR, SSE, R-Squared, residuals
  residuals.resize(samplesize);
  for (int n = 0; n < samplesize; n++){
    yhat = alpha + (beta * Vec_x[n]);
    SSE += pow((yhat - ybar), 2);
    SSR += pow((Vec_y[n] - yhat), 2);
    residuals[n] = (Vec_y[n] - yhat);
    if (residuals[n] > residualmax){
      residualmax = residuals[n];
    }
    if (residuals[n] < residualmin){
      residualmin = residuals[n];
    }
    residualmean += fabsf(residuals[n]);
  }
  residualmean = (residualmean/samplesize);
  SST = SSR + SSE;
  rsquared = SSE / SST;           //Can also be obtained by r ^ 2 for simple regression (i.e. 1 independent variable)

  std::cout << "m2=" << beta << " b2=" << alpha << " r2=" << r*r << " R2=" << rsquared << std::endl;

  //Calculate T-test for Beta
  residualSE = sqrtf(SSR/(samplesize-2));
  SEBeta = (residualSE/(Sx * sqrt(samplesize-1)));
  t = beta / SEBeta;
}
*/

//void _window_interpreter::linear_regression(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrd_ns::_data_xrd_obs_pdb &Data_xrd_obs_pdb1)
//{
//  float Sum_x=0;
//  float Sum_x2=0;
//  float Sum_y=0;
//  float Sum_y2=0;
//  float Sum_xy=0;
//  float Numerator=0;
//  float Denominator=0;
//  float n=float(Vec_x.size());

//  for(unsigned int i=0;i<Vec_x.size();i++){
//    Sum_x = Sum_x + Vec_x[i];
//    Sum_x2 = Sum_x2 + Vec_x[i]*Vec_x[i];
//    Sum_y = Sum_y + Vec_y[i];
//    Sum_y2 = Sum_y2 + Vec_y[i]*Vec_y[i];
//    Sum_xy = Sum_xy + Vec_x[i]*Vec_y[i];
//  }

//  // d=n*sumx2-sumx*sumx;
//  // m=(n*sumxy-sumx*sumy)/d;
//  // c=(sumy*sumx2-sumx*sumxy)/d;

//  Denominator=n*Sum_x2-Sum_x*Sum_x;
//  if (Denominator!=0){
//    Data_xrd_obs_pdb1.Slope = (n*Sum_xy-Sum_x*Sum_y)/Denominator;

//    Data_xrd_obs_pdb1.Intercept = (Sum_y - Data_xrd_obs_pdb1.Slope*Sum_x)/n;
//    Numerator=Sum_xy - (Sum_x*Sum_y) / n;
//    Denominator=sqrtf((Sum_x2 - (Sum_x*Sum_x)/n)*(Sum_y2 - (Sum_y*Sum_y)/n));
//    if (Denominator!=0){
//      // changed to get the abs value

//      Data_xrd_obs_pdb1.Correlation_coefficient_squared = fabs(Numerator/Denominator);

//      //if (Data_xrd_obs_pdb1.Correlation_coefficient_squared<0) Data_xrd_obs_pdb1.Correlation_coefficient_squared=0;
//    }
//    else{
//      Data_xrd_obs_pdb1.Correlation_coefficient_squared=0;
//    }
//  }
//  else{
//    Data_xrd_obs_pdb1.Correlation_coefficient_squared=0;
//  }

//  std::cout << "m1=" << Data_xrd_obs_pdb1.Slope << " b1=" << Data_xrd_obs_pdb1.Intercept << " r2=" << std::powf(Data_xrd_obs_pdb1.Correlation_coefficient_squared,2) << std::endl;
//}
#endif

//HEA

#ifdef XRD_ACTIVE
void _window_interpreter::xrd_update_info(bool Valid)
{
  Q_UNUSED(Valid)
//  if (XRD_data_to_show && XRD_selected_col_in_table>=0 && Valid){
//    int Value=int(roundf(powf(Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].Correlation_coefficient_squared,2)*100.0f)); // R^2
//    int Num_elements_not_found=Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].Vec_elements_not_found.size();
//    bool XRF_used=Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].XRF_used;
//    float Shift=Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].Shift;
//    int Num_counted_peaks=Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].Num_counted_peaks;
//    int Num_peaks=Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].Num_peaks;

//    if (XRF_used==true){
//      Lineedit_xrd_file_exists->setStyleSheet("QLineEdit {color: white; background-color: green;}");
//      Lineedit_xrd_file_exists->setText("YES");
//      //
//      if (Num_elements_not_found==0){
//        Lineedit_xrd_all_elements_exist->setStyleSheet("QLineEdit {color: white; background-color: green;}");
//        Lineedit_xrd_all_elements_exist->setText("YES");
//      }
//      else{
//        Lineedit_xrd_all_elements_exist->setStyleSheet("QLineEdit {color: white; background-color: red;}");

//        QString Text="NO: ";
//        for (unsigned int i=0;i<Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].Vec_elements_not_found.size();i++){
//          Text=Text+QString::fromStdString(Mat_xrd_obs_vs_pdb_data[XRD_selected_row_in_table][XRD_selected_col_in_mat].Vec_elements_not_found[i]);
//        }
//        Lineedit_xrd_all_elements_exist->setText(Text);
//      }
//    }
//    else{
//      Lineedit_xrd_file_exists->setStyleSheet("QLineEdit {color: white; background-color: red;}");
//      Lineedit_xrd_file_exists->setText("NO");

//      Lineedit_xrd_all_elements_exist->setStyleSheet("QLineEdit {color: white; background-color: red;}");
//      Lineedit_xrd_all_elements_exist->setText("NO");
//    }


//    Lineedit_xrd_correlation->setText(QString("%1%").arg(Value));
//    Lineedit_xrd_shift->setText(QString("%1").arg(Shift));
//    Lineedit_xrd_num_peaks->setText(QString("%1/%2").arg(Num_counted_peaks).arg(Num_peaks));
//  }
//  else{
//    Lineedit_xrd_file_exists->setText("---");
//    Lineedit_xrd_all_elements_exist->setText("---");
//    Lineedit_xrd_correlation->setText("---");
//    Lineedit_xrd_shift->setText("---");
//    Lineedit_xrd_num_peaks->setText("---");
//  }
}

//HEA

void _window_interpreter::xrd_update_info_and_chart_of_selected_table_cell()
{
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

//std::vector<float> _window_interpreter::xrd_tube_conversion(_window_interpreter_interpreter_interpreter_ns::_tube_conversion_mode Tube_conversion_mode, std::vector<float> Values)
//{
//  std::vector<float> Vec_result(Values.size(),0);
//  std::vector<short int> Vec_counters(Values.size(),0);

//  if (Tube_conversion_mode==_window_interpreter_interpreter_interpreter_ns::_tube_conversion_mode::TUBE_CONVERSION_CO_TO_CU){
//    // some positions coincide
//    for (unsigned int i=68;i<Result.size();i++) Result[i-68]=Values[i];
//  }
//  else{
//    // some holes are produced
//    for (unsigned int i=68;i<Result.size();i++) Result[i]=Values[i-68];
//  }

//  return Result;
//}


std::vector<float> _window_interpreter::xrd_tube_conversion(_data_xrd_ns::_tube_conversion_mode Tube_conversion_mode, std::vector<float> Values)
{
  std::vector<float> Vec_result(Values.size(),0);
  float Angle_degrees;
  float Angle_radians;
  float Result;
  int Position;
  float Ratio;
  const float Lambda_Cu=1.5406;
  const float Lambda_Co=1.7890;

  if (Tube_conversion_mode==_data_xrd_ns::_tube_conversion_mode::TUBE_CONVERSION_CO_TO_CU){
    // some positions coincide
    std::vector<short int> Vec_counters(Values.size(),0);
    Ratio=Lambda_Cu/Lambda_Co;

    for (unsigned int Pos=0;Pos<Vec_result.size();Pos++){
      Angle_degrees=_data_xrd_ns::START_2THETA+(float(Pos)/_data_xrd_ns::STEPS_2THETA);
      Angle_radians=M_PI*Angle_degrees/180.0f;
      Result=asin(sin(Angle_radians)*Ratio);
      Angle_degrees=Result*180.0f/M_PI;
      Position=int(roundf((Angle_degrees-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA));
      if (Position>=0 && Position<int(Vec_result.size())){
        Vec_result[Position]=Vec_result[Position]+Values[Pos];
        Vec_counters[Position]++;
      }
    }

    // addjust
    for (unsigned int Pos=0;Pos<Vec_result.size();Pos++){
      if (Vec_counters[Pos]>1) Vec_result[Pos]=Vec_result[Pos]/float(Vec_counters[Pos]);
    }
  }
  else{
    // some holes are produced
    std::vector<bool> Vec_used(Values.size(),false);
    Ratio=Lambda_Co/Lambda_Cu;

    for (unsigned int Pos=0;Pos<Vec_result.size();Pos++){
      Angle_degrees=_data_xrd_ns::START_2THETA+(float(Pos)/_data_xrd_ns::STEPS_2THETA);
      Angle_radians=M_PI*Angle_degrees/180.0f;
      Result=asin(sin(Angle_radians)*Ratio);
      Angle_degrees=Result*180.0f/M_PI;
      Position=int(roundf((Angle_degrees-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA));
      if (Position>=0 && Position<int(Vec_result.size())){
        Vec_result[Position]=Values[Pos];
        Vec_used[Position]=true;
      }
    }

    // addjust
    for (unsigned int Pos=68;Pos<Vec_result.size()-1;Pos++){
      if (Vec_used[Pos]==false) Vec_result[Pos]=(Vec_result[Pos-1]+Vec_result[Pos+1])/2.0f;
    }
  }

  return Vec_result;
}
#endif

//HEA

void _window_interpreter::xrd_compute_sqrt_values(std::vector<float> &Values1,std::vector<float> &Values2,std::vector<float> &Values3)
{
  if (Values3.size()!=Values1.size()){
    Values3.resize(Values1.size());
  }

  // first adjust the input values
  for (unsigned int i=0;i<Values1.size();i++){
    Values3[i]=sqrtf(Values1[i]*Values2[i]);
  }

//  float Maximum=*std::max_element(Values3.begin(),Values3.end());
//  for (unsigned int i=0;i<Values1.size();i++){
//    Values3[i]=Values3[i]*100.0f/Maximum;
//  }
}

bool compare_peaks(const _common_ns::_peak_data &Element1, const _common_ns::_peak_data &Element2)
{
  if (Element1.Height>Element2.Height) return true;
  return false;
}

//HEA

#ifdef XRD_ACTIVE
void _window_interpreter::xrd_process_pdb_data()
{
//  int Start;
//  int Stop;
  float Value1;
  float Value2;
  int Counter;
  std::vector<_data_xrd_ns::_data_xrd_pdb> Data_xrd_pdb_aux;

  for (unsigned int Element=0;Element<Vec_xrd_pdb_data.size();Element++){
//    cout << "counting " << Vec_xrd_pdb_data[Element].Name << endl;

    // ???? check the number of peaks

    // Get the positions of the maximums
    std::vector<int> Max_pos;
    for (unsigned int i=1;i<Vec_xrd_pdb_data[Element].Vec_normalized_values.size()-1;i++){
      Value1=Vec_xrd_pdb_data[Element].Vec_normalized_values[i]-Vec_xrd_pdb_data[Element].Vec_normalized_values[i-1];
      Value2=Vec_xrd_pdb_data[Element].Vec_normalized_values[i+1]-Vec_xrd_pdb_data[Element].Vec_normalized_values[i];
      if (Value1!=0 && Value2!=0){
        if (Value1>=0 && Value2<0){
//          cout << "Values1=" << Value1 << " Value2=" << Value2 << " value[i]=" << Vec_xrd_pdb_data[Element].Values[i] << endl;
          Max_pos.push_back(i);
        }
      }
    }

    if (Max_pos.size()>0 && Max_pos.size()<500){
      Data_xrd_pdb_aux.push_back(Vec_xrd_pdb_data[Element]);
      Counter=Data_xrd_pdb_aux.size()-1;

      Data_xrd_pdb_aux[Counter].Vec_peaks.resize(Max_pos.size());

      for (unsigned int i=0;i<Data_xrd_pdb_aux[Counter].Vec_peaks.size();i++){
        Data_xrd_pdb_aux[Counter].Vec_peaks[i].Position=Max_pos[i];
        // the height
        Data_xrd_pdb_aux[Counter].Vec_peaks[i].Height=Data_xrd_pdb_aux[Counter].Vec_normalized_values[Max_pos[i]];
  //      if (Data_xrd_pdb_aux[Counter].Vec_peaks[i].Height==0){
  //        cout << "Counter " << Counter << " has peak =0 at " << i << endl;
  //      }
      }

      // found the limits of each peak
      int Step;
      int Start_position;
      for (unsigned int i=0;i<Data_xrd_pdb_aux[Counter].Vec_peaks.size();i++){
        // left limit
        Step=1;
        Start_position=Data_xrd_pdb_aux[Counter].Vec_peaks[i].Position;
        while (Data_xrd_pdb_aux[Counter].Vec_normalized_values[Start_position-Step]!=0 && Data_xrd_pdb_aux[Counter].Vec_normalized_values[Start_position-Step]<=Data_xrd_pdb_aux[Counter].Vec_normalized_values[Start_position]){
          Step++;
        }
        Data_xrd_pdb_aux[Counter].Vec_peaks[i].Start_pos=Start_position-Step;
        // right limit
        Step=1;
        while (Data_xrd_pdb_aux[Counter].Vec_normalized_values[Start_position+Step]!=0 && Data_xrd_pdb_aux[Counter].Vec_normalized_values[Start_position-Step]<=Data_xrd_pdb_aux[Counter].Vec_normalized_values[Start_position]){
          Step++;
        }
        Data_xrd_pdb_aux[Counter].Vec_peaks[i].End_pos=Start_position+Step;
      }

      // order the data depending on the height
      sort(Data_xrd_pdb_aux[Counter].Vec_peaks.begin(),Data_xrd_pdb_aux[Counter].Vec_peaks.end(),compare_peaks);
    }
//    else{
//      QMessageBox::critical(this, tr("Error"),"<p>The data for pigment in file <b> "+QString::fromStdString(Vec_xrd_pdb_data[Element].File_name)+"</b> in pdb folder is wrong</p><p>There are 0 or more than 500 peaks</p><p>Remove the file from the PDB folder</p>");
//    }
  }

  Vec_xrd_pdb_data=Data_xrd_pdb_aux;

  // the initial positions in the lists of pigments. The value -1 is used to do a first assigment of the position based on the ordenation
  Vec_xrd_selected_position.resize(Vec_xrd_obs_data.size(),-1);
}
#endif


//HEA

#ifdef XRD_ACTIVE
void _window_interpreter::xrd_preprocess_pdb_data()
{
  // remove noise + subtract mean + normalization

  for (unsigned int i=0;i<Vec_xrd_pdb_data.size();i++){
    if (Vec_xrd_pdb_data[i].Normalized==false){
      xrd_preprocess_data(Vec_xrd_pdb_data[i].Vec_values,Vec_xrd_pdb_data[i].Vec_smooth_values,Vec_xrd_pdb_data[i].Vec_filtered_values, Vec_xrd_pdb_data[i].Vec_normalized_values,XRD_num_steps_smooth,XRD_num_steps_subtract_background);
    }
    else{ // for ASTM or normalized pdb
      Vec_xrd_pdb_data[i].Vec_normalized_values=Vec_xrd_pdb_data[i].Vec_values;
    }
  }
}


#endif

#ifdef XRD_ACTIVE
//HEA

void _window_interpreter::xrd_preprocess_obs_data()
{
  QListWidgetItem *Item;
  Listwidget_data_xrd_obs->clear();

  for (unsigned int i=0;i<Vec_xrd_obs_data.size();i++){
    if (Vec_xrd_obs_data[i].Position!=-1){
      // add the element to the list
      Item=new QListWidgetItem;
      Item->setText(QString::fromStdString(Vec_xrd_obs_data[i].File_name));
      Listwidget_data_xrd_obs->addItem(Item);

      xrd_preprocess_data(Vec_xrd_obs_data[i].Vec_values,Vec_xrd_obs_data[i].Vec_smooth_values, Vec_xrd_obs_data[i].Vec_filtered_values, Vec_xrd_obs_data[i].Vec_normalized_values,XRD_num_steps_smooth,XRD_num_steps_subtract_background);

      // initilize the vector with the order
      Vec_xrd_obs_data[i].Vec_order.resize(Vec_xrd_pdb_data.size());
      for (unsigned j=0;j<Vec_xrd_pdb_data.size();j++){
        Vec_xrd_obs_data[i].Vec_order[j].Name=Vec_xrd_pdb_data[j].File_name;
        Vec_xrd_obs_data[i].Vec_order[j].Position=j;
      }
    }
    else{
      // add the NULL element to the list
      Item=new QListWidgetItem;
      Item->setText(QString::fromStdString("NULL"));
      Listwidget_data_xrd_obs->addItem(Item);
    }
  }

  // search for the first not null file
  if (XRF_obs_data_loaded==false){
    for (Selected_file_position=0;Selected_file_position<int(Vec_xrd_obs_data.size());Selected_file_position++){
      if (Vec_xrd_obs_data[Selected_file_position].Position!=-1) break;
    }
  }
  // this is to get data for the cases where the file is null
  XRD_good_file_position=Selected_file_position;

  // mark it
  Listwidget_data_xrd_obs->blockSignals(true);
  Listwidget_data_xrd_obs->setCurrentRow(Selected_file_position);
  Listwidget_data_xrd_obs->blockSignals(false);
}

#endif


//HEA

#ifdef XRD_ACTIVE
void _window_interpreter::xrd_process_data()
{
  // PDB
  xrd_preprocess_pdb_data();
  xrd_process_pdb_data();

  // OBS
  xrd_preprocess_obs_data();

  // OBS vs PDB
  xrd_process_obs_vs_pdb_data();

  // classify the cells using the class. Only one time
  xrd_classify_cells_class_mat_obs_vs_pdb();

  // apply the manual selections
  xrd_apply_manual_selection_to_mat_obs_vs_pdb();

  // cllasify each cell depending on thresholds
  xrd_classify_cells_threshold_mat_obs_vs_pdb();

  // compute which columns have data to show depending on the parameters
//  xrd_compute_visible_columns_in_table(Mat_xrd_obs_vs_pdb_data);

  //
  xrd_assign_data_to_table();

  // compute the ranges
  xrd_compute_ranges();

  // create chart
//  if (XRD_selected_col_in_table==-1) xrd_create_obs_spectral_chart(XRD_selected_row_in_table);
//  else{
//    if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(XRD_selected_row_in_table,XRD_selected_col_in_mat);
//    else xrd_create_pdb_sqrt_correlation_chart(XRD_selected_row_in_table,XRD_selected_col_in_mat);
//  }


  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else
    xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_assign_data_to_table()
{
  Table_data_xrd->update_table(Vec_xrd_selected_position[Selected_file_position], Vec_xrd_pdb_data,Mat_xrd_obs_vs_pdb_data[Selected_file_position], Mat_xrd_obs_vs_pdb_data_selected[Selected_file_position],Vec_xrd_obs_data[Selected_file_position].Vec_order);
}
#endif

// XRF -----------------
//HEA

//void _window_interpreter::load_elements()
//{
//  QString File_name=_window_interpreter_interpreter_interpreter_ns::FOLDER_PDB+"/"+_window_interpreter_interpreter_interpreter_ns::FILE_ELEMENTS;
//  QFileInfo File(File_name);

//  if (File.exists() && File.isFile()){
//    std::string Error;

//    _file_elements_csv File;

//    File.open(File_name.toStdString(),_file_elements_csv::_mode::MODE_READ);
//    if (File.read(Vec_xrf_pdb_data,Error)==true){
//      File.close();
//    }
//    else{
//      File.close();

//      QMessageBox::critical(this, tr("Error"),QString::fromStdString(Error));
//      QApplication::quit();
//      exit(-1);
//    }
//  }
//  else{
//    QMessageBox::critical(this, tr("Error"),"There is not "+_window_interpreter_interpreter_interpreter_ns::FILE_ELEMENTS+" file in pdb folder (xrf)");
//    QApplication::quit();
//    exit(-1);
//  }
//}


//HEA
// search for ka repeated
//int _window_interpreter::search_ka(int Start_position,std::vector<_data_xrf_ns::_result> &Vec_results)
//{;
//  int Distance=100;
//  map<std::string,_data_xrf_ns::_data_xrf_selected> Map_selecteds;

//  for (unsigned int i=Start_position;i<Vec_results.size();i++){
//    // there is maximum after the previous one
//    if (Vec_results[i].Used==false){
//      // it is not used, it is valid
//      // get all the peaks ordered
//      Vec_selected=Vec_results[i].Vec_selected;
//      for (unsigned int j=0;j<Vec_selected.size();j++){
//        // check if there is a second peak for the element
////        if (Vec_selected[j].Name==Name && Vec_selected[j].K_name=="ka"){??
////          Distance=Vec_selected[j].Distance;
////          break;
////        }
//      }
//    }
//  }
//  return Distance;
//}


//HEA
// search for the kb of the compound
//_common_ns::_value_position _window_interpreter::search_kb(int Start_position,std::vector<_data_xrf_ns::_result> &Vec_results)
//{
//  int Pos_peak=-1;
//  int Pos_found=-1;
//  map<std::string,_data_xrf_ns::_data_xrf_selected> &Map_selecteds;

//  for (unsigned int i=Start_position;i<Vec_results.size();i++){
//    // there is maximum after the previous one
//    if (Vec_results[i].Used==false){
//      // it is not used, it is valid
//      // get all the peaks ordered
//      Vec_selected=Vec_results[i].Vec_selected;
//      for (unsigned int j=0;j<Vec_selected.size();j++){
//        // check if there is a second peak for the element
////        if (Vec_selected[j].Name==Name && Vec_selected[j].K_name=="kb"){??
////          Pos_peak=i;
////          Pos_found=j;
////          break;
////        }
//      }
//    }

//    if (Pos_found!=-1) break;
//  }

//  // found the Kb peak
//  if (Pos_found!=-1){
//    // if a Kb has been used, the vector with the rest of data is removed
//    Vec_results[Pos_peak].Used=true;

////    return {Vec_selected[Pos_found].Max_value,Vec_selected[Pos_found].Position};??
//    return {-1,-1};
//  }
//  else{
//    return {-1,-1};
//  }
//}


//HEA
// given the position of the maximums in the real data, find the elements that match those max values
//std::vector<_data_xrf_ns::_data_xrf_ka_kb> _window_interpreter::xrf_search_elements(int Index, std::vector<_common_ns::_value_position> Maximums, int Window)
//{
//  int Pos_maximum;
//  float Max_value;
//  int Min_pos;
//  int Max_pos;

//  float Step=Vec_xrf_obs_data[Index].Step;

//  std::vector<_data_xrf_ns::_result> Vec_results;

//  std::vector<_data_xrf_ns::_data_xrf_ka_kb> Vec_results_ka_kb;

//  // for each maximum try to catch the better candidates
//  // the ka and kb peaks are saved
//  for (unsigned int i=0;i<Maximums.size();i++){
//    Pos_maximum=Maximums[i].Position;
//    Max_value=Maximums[i].Value;

//    // create the search window
//    Min_pos=Pos_maximum-Window;
//    Max_pos=Pos_maximum+Window;

//    std::vector<_data_xrf_ns::_data_xrf_selected> Vec_selected;
//    std::string Name_element;
//    float Ka;
//    float Kb;
//    int Distance;

//    // search in the list of elements
//    // the Ka and Kb peaks are searched and save. Then a selection must be done
//    for (unsigned int j=0;j<Vec_xrf_pdb_data.size();j++){
//      // get the name of the element
//      Name_element=Vec_xrf_pdb_data[j].Name;

//      // get the Ka value in keV
//      Ka=Vec_xrf_pdb_data[j].Ka;
//      // get the Kb value in keV
//      Kb=Vec_xrf_pdb_data[j].Kb;

//      // convert the position in keV to position in the list ( the minimum value for keV is 3)
//      int Pos_element_ka=int(round(Ka/Step))-int(round(3/Step));

//      // first check that the position of the peak is in the search window
//      if (Pos_element_ka>=Min_pos && Pos_element_ka<=Max_pos){
//        // there is ka peak
//        // get the distance between the real peak and the element peak (positions)
//        Distance=abs(Pos_maximum-Pos_element_ka);

//        // save the information
//        Vec_selected.push_back({Name_element,"ka",Distance,Pos_maximum,Max_value,j});
//      }


//      // look for a peak at kb
//      if (Kb>0){
//        // convert the position in keV to position in the list ( the minimum value for keV is 3)
//        int Pos_element_kb=int(round(Kb/Step))-int(round(3/Step));

//        // check that the position of the peak is in the search window
//        if (Pos_element_kb>=Min_pos && Pos_element_kb<=Max_pos){
//          Distance=abs(Pos_maximum-Pos_element_kb);

//          // save the information
//          Vec_selected.push_back({Name_element,"kb",Distance,Pos_maximum,Max_value,j});
//        }
//      }
//    }

//    // Selected contains all the coincidences for each peak
//    // We need to select the best one. A Ka peak is more important than a Kb peak
//    if (Vec_selected.size()>=1){
//      // there are several candidates. They have to be ordered
//      if (Vec_selected.size()>1){
//        // order the candidates using the difference in distance between the real and the theoric value
//        // first key is distance, second key is ka or kb
//        // using a lambda funtion to do the comparison
////        sort(Vec_selected.begin(),Vec_selected.end(),[](_data_xrf_ns::_data_xrf_selected &A,_data_xrf_ns::_data_xrf_selected &B){
////          return (A.Distance < B.Distance) || (A.Distance == B.Distance && A.K_name < B.K_name);
////        });

//        sort(Vec_selected.begin(),Vec_selected.end(),[](_data_xrf_ns::_data_xrf_selected &A,_data_xrf_ns::_data_xrf_selected &B){
//          return (A.K_name < B.K_name) || (A.K_name == B.K_name && A.Distance < B.Distance);
//        });
//      }
//      // save the candidates ordered from nearer to farthest
//      // each peak has a vector of results and a boolean to mark if the peak has been used
//      Vec_results.push_back({false,Vec_selected});
//    }
//  }

//  // now the selection from the candidates
//  for (unsigned int i=0;i<Vec_results.size();i++){
//    // false -> is not used, it must be tested
//    if (Vec_results[i].Used==false){
//      // get data
//      std::vector<_data_xrf_ns::_data_xrf_selected> Data_selected=Vec_results[i].Vec_selected;

//      std::vector<_data_xrf_ns::_data_xrf_ka_kb> Vec_results_ka_kb_aux;

//      // check if the peak is due to a Ka value
//      for (unsigned int j=0;j<Data_selected.size();j++){
//        if (Data_selected[j].K_name=="ka"){
//          // search for ka repeated
//          int Distance1=search_ka(Data_selected[j].Name,i+1,Vec_results);

//          if (Data_selected[j].Distance<Distance1){
//            // save the name, the position and the value of the maximum
//            _data_xrf_ns::_data_xrf_ka_kb Result;

//            Result.Name=Data_selected[j].Name;
//            Result.Element_pos=Data_selected[j].Element_position;
//            // Ka
//            // Position
//            Result.Ka.Position=Data_selected[j].Position;
//            Result.Ka.Value=Data_selected[j].Max_value;
//            Result.Ka.Position_kev=Vec_xrf_pdb_data[Result.Element_pos].Ka;

//            // search for the kb as second peak
//            _common_ns::_value_position Value_pos=search_kb(Result.Name,i+1,Vec_results);

//            Result.Kb.Position=Value_pos.Position;
//            Result.Kb.Value=Value_pos.Value;
//            Result.Kb.Position_kev=Vec_xrf_pdb_data[Result.Element_pos].Kb;

//            Vec_results_ka_kb_aux.push_back(Result);
//          }

//          // the data is used -> true
//          Vec_results[i].Used=true;

//        }
//      }

//      // Check if there are superpostion and what is better
//      if (Vec_results_ka_kb_aux.size()>1){
//        int Count=0;
//        int Count_Ti_Ba=0;
//        int Count_Pb_As=0;

//        _data_xrf_ns::_data_xrf_ka_kb Data_ka_kb;
//        for (unsigned int j=0;j<Vec_results_ka_kb_aux.size();j++){
//          Data_ka_kb=Vec_results_ka_kb_aux[j];

//          if (Data_ka_kb.Ka.Value!=-1 && Data_ka_kb.Kb.Value!=-1){
//            Count=Count+1;
//            // case Ti/Ba
//            if (Data_ka_kb.Name=="Ti" || Data_ka_kb.Name=="Ba"){
//              Count_Ti_Ba=Count_Ti_Ba+1;
//            }
//            // case Pb/As
//            if (Data_ka_kb.Name=="Pb" || Data_ka_kb.Name=="As"){
//              Count_Pb_As=Count_Pb_As+1;
//            }
//          }
//        }

//        if (Count>0){
//          if (Count_Ti_Ba==2){
//            float Value_Ka;
//            float Value_Kb;
//            if (Vec_results_ka_kb_aux[0].Name=="Ti" && Vec_results_ka_kb_aux[1].Name=="Ba"){
//              // First Ti then Ba
//              Value_Ka=Vec_results_ka_kb_aux[0].Ka.Value;
//              Value_Kb=Vec_results_ka_kb_aux[0].Kb.Value;
//              if ((Value_Kb/Value_Ka)<0.5){
//                // Ti
//                Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[0]);
//              }
//              else{
//                // Ba
//                Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[1]);
//              }
//            }
//            else{
//              // First Ba then Ti
//              Value_Ka=Vec_results_ka_kb_aux[0].Ka.Value;
//              Value_Kb=Vec_results_ka_kb_aux[0].Kb.Value;
//              if ((Value_Kb/Value_Ka)>0.5){
//                // Ba
//                Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[0]);
//              }
//              else{
//                // Ti
//                Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[1]);
//              }
//            }
//          }
//          else{
//            if (Count_Pb_As==2){
//              // remove As
//              float Value_Ka;
//              float Value_Kb;
//              if (Vec_results_ka_kb_aux[0].Name=="Pb" && Vec_results_ka_kb_aux[1].Name=="As"){
//                // First Pb then As
//                Value_Ka=Vec_results_ka_kb_aux[0].Ka.Value;
//                Value_Kb=Vec_results_ka_kb_aux[0].Kb.Value;
//                if ((Value_Kb/Value_Ka)<0.5){
//                  // Pb
//                  Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[0]);
//                }
//                else{
//                  // As
////                  Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[1]);
//                }
//              }
//              else{
//                // First As then Pb
//                Value_Ka=Vec_results_ka_kb_aux[0].Ka.Value;
//                Value_Kb=Vec_results_ka_kb_aux[0].Kb.Value;
//                if ((Value_Kb/Value_Ka)>0.5){
//                  // As
////                  Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[0]);
//                }
//                else{
//                  // Pb
//                  Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[1]);
//                }
//              }
//            }
//            else{// Normal clase
//              for (unsigned int j=0;j<Vec_results_ka_kb_aux.size();j++){
//                Data_ka_kb=Vec_results_ka_kb_aux[j];

//                if (Data_ka_kb.Ka.Value!=-1 && Data_ka_kb.Kb.Value!=-1){
//                  Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[j]);
//                }
//              }
//            }
//          }
//        }
//        else{
//          Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[0]);
//        }
//      }
//      else{
//        if (Vec_results_ka_kb_aux.size()==1){
//          Vec_results_ka_kb.push_back(Vec_results_ka_kb_aux[0]);
//        }
//      }
//    }
//  }


//  // add the kb information
//  for (unsigned int i=0;i<Vec_results_ka_kb.size();i++){
//    if (Vec_results_ka_kb[i].Kb.Position==-1){
//      // there is not kb -> the value of the data for the kb position is asigned

//      // Element_position (this is used to get the position of the kb
//      unsigned int Element_position=Vec_results_ka_kb[i].Element_pos;
//      float Kb=Vec_xrf_pdb_data[Element_position].Kb;

//      // convert the position in keV to position in the list ( the minimum value for keV is 3)
//      Vec_results_ka_kb[i].Kb.Position=int(round(Kb/Step))-int(round(3/Step));
//      Vec_results_ka_kb[i].Kb.Value=Vec_xrf_obs_data[Index].Vec_smooth_values[Vec_results_ka_kb[i].Kb.Position];
//    }
//  }

//  // Now the not found elements are added
//  std::string Name_element_pdb;
//  std::string Name_element_found;
//  float Ka;
//  float Kb;
//  std::vector<int> Vec_pos_not_found;

//  for (unsigned int i=0;i<Vec_xrf_pdb_data.size();i++){
//    // get the name of the element
//    Name_element_pdb=Vec_xrf_pdb_data[i].Name;
//    bool Found=false;
//    for (unsigned int j=0;j<Vec_results_ka_kb.size();j++){
//      Name_element_found=Vec_results_ka_kb[j].Name;
//      if (Name_element_pdb==Name_element_found){
//        Found=true;
//        break;
//      }
//    }
//    if (Found==false) Vec_pos_not_found.push_back(i);
//  }

//  int Element_pos;
//  for (unsigned int i=0;i<Vec_pos_not_found.size();i++){
//    Element_pos=Vec_pos_not_found[i];
//    // get the name of the element
//    Name_element_pdb=Vec_xrf_pdb_data[Element_pos].Name;

//    // get the Ka value in keV
//    Ka=Vec_xrf_pdb_data[Element_pos].Ka;
//    // get the Kb value in keV
//    Kb=Vec_xrf_pdb_data[Element_pos].Kb;

//    // convert the position in keV to position in the list ( the minimum value for keV is 3)
//    int Pos_element_ka=int(round(Ka/Step))-int(round(3/Step));
//    int Pos_element_kb=int(round(Kb/Step))-int(round(3/Step));

//    _data_xrf_ns::_data_xrf_ka_kb Result;

//    Result.Name=Name_element_pdb;
//    Result.Element_pos=Element_pos;
//    Result.Selected_found=false;
//    Result.Selected_valid=false;
//    Result.Selected_orig=false;
//    // Ka
//    // Position
//    Result.Ka.Position=Pos_element_ka;
//    Result.Ka.Value=Vec_xrf_obs_data[Index].Vec_smooth_values[Pos_element_ka];
//    Result.Ka.Position_kev=Ka;

//    Result.Kb.Position=Pos_element_kb;
//    Result.Kb.Value=Vec_xrf_obs_data[Index].Vec_smooth_values[Pos_element_kb];
//    Result.Kb.Position_kev=Kb;
//    // aplies the ratio if kb is very big
//    if (Result.Kb.Value>Result.Ka.Value) Result.Kb.Value=Result.Ka.Value*Vec_xrf_pdb_data[i].kb_ka_ratio;

//    Vec_results_ka_kb.push_back(Result);
//  }

//  return Vec_results_ka_kb;
//}


//HEA
// distance, Position_in_vec_maximums, K_type

bool compare_distance_increase(_data_xrf_ns::_data_k &A,_data_xrf_ns::_data_k &B)
{
    return (A.Distance_vec_data < B.Distance_vec_data);
}

//HEA

void _window_interpreter::xrf_remove_element_from_peaks(std::string Element_name,int Pos_peak,std::vector<_data_xrf_ns::_data_maximum>& Vec_maximums)
{
  if (Pos_peak>-1){
    int Pos=-1;

    for (unsigned int i=0;i<Vec_maximums[Pos_peak].Vec_elements.size();i++){
      if (Vec_maximums[Pos_peak].Vec_elements[i].Name==Element_name){
        Pos=i;
        break;
      }
    }
    // copy the data to the previous
    for (unsigned int i=Pos;i<Vec_maximums[Pos_peak].Vec_elements.size()-1;i++){
      Vec_maximums[Pos_peak].Vec_elements[i]=Vec_maximums[Pos_peak].Vec_elements[i+1];
    }

    Vec_maximums[Pos_peak].Vec_elements.pop_back();
  }
}

//HEA

void _window_interpreter::xrf_remove_element(std::string Element_name, std::map<std::string, _data_xrf_ns::_data_xrf_selected> &Map_selecteds, std::vector<_data_xrf_ns::_data_maximum> &Vec_maximums)
{
  int Pos_peak=Map_selecteds[Element_name].Data_ka.Position_in_vec_maximums;
  if (Pos_peak!=-1) xrf_remove_element_from_peaks(Element_name,Pos_peak,Vec_maximums);

  Pos_peak=Map_selecteds[Element_name].Data_kb.Position_in_vec_maximums;
  if (Pos_peak!=-1) xrf_remove_element_from_peaks(Element_name,Pos_peak,Vec_maximums);
}

//HEA

void _window_interpreter::xrf_add_element_to_result(std::string Element_name, float Step, std::map<std::string,_data_xrf_ns::_data_xrf_selected>& Map_selecteds, std::vector<_data_xrf_ns::_data_maximum>& Vec_maximums, std::vector<_data_xrf_ns::_data_xrf_ka_kb>& Vec_results_ka_kb, std::vector< std::pair<int, int>>& Vec_maximums_aux)
{
  int Ka_position=-1;
  float Ka_value=0;
  float Ka_position_kev=-1;
  int Kb_position=-1;
  float Kb_value=0;
  float Kb_position_kev=-1;

  // get the positions in the vector of maximums
  int Position_ka_vec_maximums=Map_selecteds[Element_name].Data_ka.Position_in_vec_maximums;
  int Position_kb_vec_maximums=Map_selecteds[Element_name].Data_kb.Position_in_vec_maximums;

  // get the Ka value of the selected element
  Ka_value=Vec_maximums[Position_ka_vec_maximums].Value;
  Ka_position=Vec_maximums[Position_ka_vec_maximums].Position_vec_data;
  Ka_position_kev=float(Ka_position)*Step+3.0f;

  // get the Kb value of the selected element
  if (Map_selecteds[Element_name].Data_kb.Position_in_vec_maximums!=-1){
    // check if the kb is alone in the peak
    int Position_kb_vec_maximums=Map_selecteds[Element_name].Data_kb.Position_in_vec_maximums;
    Kb_value=Vec_maximums[Position_kb_vec_maximums].Value;
    if (Vec_maximums[Position_kb_vec_maximums].Vec_elements.size()>1){
      // check if all the peaks are kb
      bool All_kb=true;
      for (unsigned int i=0;i<Vec_maximums[Position_kb_vec_maximums].Vec_elements.size();i++){
        if (Vec_maximums[Position_kb_vec_maximums].Vec_elements[i].K_type!=_data_xrf_ns::_k_type::K_TYPE_B){
          All_kb=false;
          break;
        }
      }
      if (All_kb==false){
        // adjust the value using the ratio
        float Ratio_kb_ka=Vec_xrf_pdb_data[Map_selecteds[Element_name].Position_in_pdb].Kb_Ka_ratio;
        if (Ka_value*Ratio_kb_ka<=Kb_value) Kb_value=Ka_value*Ratio_kb_ka;
      }
    }

    Kb_position=Vec_maximums[Map_selecteds[Element_name].Data_kb.Position_in_vec_maximums].Position_vec_data;
    Kb_position_kev=float(Kb_position)*Step+3.0f;
  }


  // the element has been used
  Map_selecteds[Element_name].Valid=false;

  // save the element as final selected element
  _data_xrf_ns::_data_xrf_ka_kb Result;

  Result.Name=Element_name;
  Result.Position_in_pdb=Map_selecteds[Element_name].Position_in_pdb;

  // ka
  Result.Ka.Position=Ka_position;
  Result.Ka.Value=Ka_value;
  Result.Ka.Position_kev=Ka_position_kev;

  // kb
  Result.Kb.Position=Kb_position;
  Result.Kb.Value=Kb_value;
  Result.Kb.Position_kev=Kb_position_kev;

  // save the ka and kb positions for doing the adjustment
  if (Position_ka_vec_maximums!=-1){
    Vec_maximums_aux[Position_ka_vec_maximums].first=Vec_results_ka_kb.size();
  }
  if (Position_kb_vec_maximums!=-1){
    Vec_maximums_aux[Position_kb_vec_maximums].second=Vec_results_ka_kb.size();
  }

  Vec_results_ka_kb.push_back(Result);
}

//HEA

//vector<_data_xrf_ns::_data_xrf_ka_kb> _window_interpreter::xrf_search_elements(int Index, std::vector<_data_xrf_ns::_data_maximum>  &Vec_maximums, int Window)
//{
//  float Step=Vec_xrf_obs_data[Index].Step;
//  std::vector<_data_xrf_ns::_result> Vec_results;
//  std::vector<_data_xrf_ns::_data_xrf_ka_kb> Vec_results_ka_kb;
//  std::vector<int> Vec_pos_selected_elements;

//  // check the PDB against the maximums
//  std::string Element_name;
//  float Ka;
//  float Kb;
//  map<std::string,_data_xrf_ns::_data_xrf_selected> Map_selecteds;
////  std::vector<vector<_data_xrf_ns::_position_k_type>> Vec_elements_per_peak(Vec_maximums.size());

//  for (unsigned int Element_pos=0;Element_pos<Vec_xrf_pdb_data.size();Element_pos++){
//    // get the name of the element
//    Element_name=Vec_xrf_pdb_data[Element_pos].Name;

//    // search for Ka
//    // get the Ka value in keV
//    Ka=Vec_xrf_pdb_data[Element_pos].Ka;
//    // convert the position in keV to position in the list ( the minimum value for keV is 3)
//    int Element_ka_pos=int(round(Ka/Step))-int(round(3/Step));

//    // get the kb
//    Kb=Vec_xrf_pdb_data[Element_pos].Kb;
//    // convert the position in keV to position in the list ( the minimum value for keV is 3)
//    int Element_kb_pos=int(round(Kb/Step))-int(round(3/Step));

//    // search for an element that has the ka in the window and also computes the kb
//    _data_xrf_ns::_data_k Data_ka;
//    _data_xrf_ns::_data_k Data_kb;

////    search_maximum(Vec_maximums,Window,Element_name,Element_ka_pos,Element_ka_pos,Vec_selected.size(),Ka_data,Kb_data);

//    if (search_element_in_maximums(Vec_maximums,Window,Element_ka_pos,Element_kb_pos,Data_ka,Data_kb)==true){
//      Vec_maximums[Data_ka.Position_in_vec_maximums].Vec_elements.push_back({Element_name,_data_xrf_ns::_k_type::K_TYPE_A,static_cast<unsigned int>(Vec_selected.size())});
//      if (Data_kb.Position_in_vec_maximums!=-1){
//        Vec_maximums[Data_kb.Position_in_vec_maximums].Vec_elements.push_back({Element_name,_data_xrf_ns::_k_type::K_TYPE_B,static_cast<unsigned int>(Vec_selected.size())});
//      }
//      Vec_selected.push_back({true,Element_name,Element_pos,Data_ka,Data_kb});
//    }
//  }

//  // I have the elements that have a ka
//  // Check if there is superposition
//  // case Pb/As

//  int Pos_As=search_element("As",Vec_selected);
//  int Pos_Pb=search_element("Pb",Vec_selected);

//  if (Pos_As!=-1 && Pos_Pb!=-1){
//    // superposition Pb/As -> remove As
//    int Distance_As=Vec_selected[Pos_As].Data_ka.Distance_vec_data+Vec_selected[Pos_As].Data_kb.Distance_vec_data;
//    int Distance_Pb=Vec_selected[Pos_Pb].Data_ka.Distance_vec_data+Vec_selected[Pos_Pb].Data_kb.Distance_vec_data;
//    if (Distance_Pb<=Distance_As) xrf_remove_element("As",Vec_selected,Vec_maximums);
//    else xrf_remove_element("Pb",Vec_selected,Vec_maximums);
//  }

//  // case Ti/Ba
//  int Pos_Ti=search_element("Ti",Vec_selected);
//  int Pos_Ba=search_element("Ba",Vec_selected);

//  if (Pos_Ti!=-1 && Pos_Ba!=-1){
//    // superposition Ti/Ba

//    float Value_ka_Ti=Vec_maximums[Vec_selected[Pos_Ti].Data_ka.Position_in_vec_maximums].Value;
//    float Value_kb_Ti=Vec_maximums[Vec_selected[Pos_Ti].Data_kb.Position_in_vec_maximums].Value;//??
//    if ((Value_kb_Ti/Value_ka_Ti)<0.5){
//      // remove Ba
//      xrf_remove_element("Ba",Vec_selected,Vec_maximums);
//    }
//    else{
//      // remove Ti
//      xrf_remove_element("Ti",Vec_selected,Vec_maximums);
//    }
//  }


//  // check if there are any peak that has more than one element
//  for (unsigned int i=0;i<Vec_maximums.size();i++){
//    if (Vec_maximums[i].Vec_elements.size()==1){
//      // send the position in Vec_maximums and position in Vec_elements
//      if (Vec_maximums[i].Vec_elements[0].K_type==_data_xrf_ns::_k_type::K_TYPE_A){
//        xrf_add_element_to_result(i,0,Step,Vec_selected,Vec_maximums,Vec_results_ka_kb);
//      }
//    }
//    else{
//      // there are several candidates. Select the one with the shortest distance (Ka+kb)
//      // get the addtion of the distances
//      int Pos=-1;
//      int Min=1000;

//      for (unsigned int j=0;j<Vec_maximums[i].Vec_elements.size();j++){
//        if (Vec_maximums[i].Vec_elements[j].K_type==_data_xrf_ns::_k_type::K_TYPE_A){
//          if ((Vec_selected[Vec_maximums[i].Vec_elements[j].Position_vec_selected].Data_ka.Distance_vec_data+Vec_selected[Vec_maximums[i].Vec_elements[j].Position_vec_selected].Data_kb.Distance_vec_data)<Min){
//            Min=Vec_selected[Vec_maximums[i].Vec_elements[j].Position_vec_selected].Data_ka.Distance_vec_data+Vec_selected[Vec_maximums[i].Vec_elements[j].Position_vec_selected].Data_kb.Distance_vec_data;
//            Pos=j;
//          }
//        }
//      }

//      if (Pos!=-1){
//        xrf_add_element_to_result(i,Pos,Step,Vec_selected,Vec_maximums,Vec_results_ka_kb);
//      }
//    }
//  }

//  // adjust the values of the kb


//  // check the elements that have a kb peak in the same position of ka peak of other element.

////  std::vector<std::vector< std::pair<std::string,string>>> Vec_max_num;
////  Vec_max_num.resize(Vec_maximums.size());

////  for (unsigned int i=0;i<Vec_selected.size();i++){
////    if (Vec_selected[i].Data_ka.Position_in_vec_maximums!=-1) Vec_max_num[Vec_selected[i].Data_ka.Position_in_vec_maximums].push_back(make_ std::pair(Vec_selected[i].Name,"ka"));
////    if (Vec_selected[i].Data_kb.Position_in_vec_maximums!=-1) Vec_max_num[Vec_selected[i].Data_kb.Position_in_vec_maximums].push_back(make_ std::pair(Vec_selected[i].Name,"kb"));
////  }

////  for (unsigned int i=0;i<Vec_max_num.size();i++){
////    cout << "*******   Max=" << i <<endl;
////    for (unsigned int j=0;j<Vec_max_num[i].size();j++){
////      cout <<"Element=" << Vec_max_num[i][j].first << " K=" << Vec_max_num[i][j].second <<endl;
////    }
////  }



//  // Now the elements of the PDB that are not found in OBS are added
//  // This allows that they can be added to the list manually
//  std::string Name_element_pdb;
//  std::string Name_element_found;
////  float Ka;
////  float Kb;
//  std::vector<int> Vec_pos_not_found;

//  for (unsigned int i=0;i<Vec_xrf_pdb_data.size();i++){
//    // get the name of the element
//    Name_element_pdb=Vec_xrf_pdb_data[i].Name;
//    bool Found=false;
//    for (unsigned int j=0;j<Vec_results_ka_kb.size();j++){
//      Name_element_found=Vec_results_ka_kb[j].Name;
//      if (Name_element_pdb==Name_element_found){
//        Found=true;
//        break;
//      }
//    }
//    if (Found==false) Vec_pos_not_found.push_back(i);
//  }

//  int Element_pos;
//  for (unsigned int i=0;i<Vec_pos_not_found.size();i++){
//    Element_pos=Vec_pos_not_found[i];
//    // get the name of the element
//    Name_element_pdb=Vec_xrf_pdb_data[Element_pos].Name;

//    // get the Ka value in keV
//    Ka=Vec_xrf_pdb_data[Element_pos].Ka;
//    // get the Kb value in keV
//    Kb=Vec_xrf_pdb_data[Element_pos].Kb;

//    // convert the position in keV to position in the list ( the minimum value for keV is 3)
//    int Pos_element_ka=int(round(Ka/Step))-int(round(3/Step));
//    int Pos_element_kb=int(round(Kb/Step))-int(round(3/Step));

//    _data_xrf_ns::_data_xrf_ka_kb Result;

//    Result.Name=Name_element_pdb;
//    Result.Element_position_in_pdb=Element_pos;
//    Result.Selected_found=false;
//    Result.Selected_valid=false;
//    Result.Selected_orig=false;
//    // Ka
//    // Position
//    Result.Ka.Position=Pos_element_ka;
//    Result.Ka.Value=Vec_xrf_obs_data[Index].Vec_smooth_values[Pos_element_ka];
//    Result.Ka.Position_kev=Ka;

//    Result.Kb.Position=Pos_element_kb;
//    Result.Kb.Value=Vec_xrf_obs_data[Index].Vec_smooth_values[Pos_element_kb];
//    Result.Kb.Position_kev=Kb;
//    // aplies the ratio if kb is very big
//    if (Result.Kb.Value>Result.Ka.Value){
//      Result.Kb.Value=Result.Ka.Value*Vec_xrf_pdb_data[i].Kb_Ka_ratio;
//    }

//    Vec_results_ka_kb.push_back(Result);
//  }

//  return Vec_results_ka_kb;
//}


//HEA ****

std::vector<_data_xrf_ns::_data_xrf_ka_kb> _window_interpreter::xrf_search_elements(int Index, std::vector<_data_xrf_ns::_data_maximum>  &Vec_maximums, int Window)
{
  float Step=Vec_xrf_obs_data[Index].Step;
  std::vector<_data_xrf_ns::_result> Vec_results;
  std::vector<_data_xrf_ns::_data_xrf_ka_kb> Vec_results_ka_kb;
  std::vector<int> Vec_pos_selected_elements;

  // check the PDB elments ka against the maximums
  std::string Element_name;
  float Ka;
  float Kb;
  std::map<std::string,_data_xrf_ns::_data_xrf_selected> Map_selecteds;

  int Pos_maximum;
  int Min_pos;
  int Max_pos;
  int Window_aux;
  unsigned int Element_pos;

  // The main item to apply the algorithm is the peak
  // This implies that in some cases the ka or the kb of an element can be in the interval of two peaks

#define EXPERIMENTAL

  // Search for the elements that can match each peak
  for (unsigned int Num_peak=0;Num_peak<Vec_maximums.size();Num_peak++){
    Pos_maximum=Vec_maximums[Num_peak].Position_vec_data;
    Window_aux=Window;

    do{
      for (Element_pos=0;Element_pos<Vec_xrf_pdb_data.size();Element_pos++){
        Element_name=Vec_xrf_pdb_data[Element_pos].Name;

        // search for Ka
        // get the Ka value in keV
        Ka=Vec_xrf_pdb_data[Element_pos].Ka;
        // convert the position in keV to position in the list ( the minimum value for keV is 3)
        int Element_ka_pos=int(round(Ka/Step))-int(round(3/Step));

        Min_pos=Pos_maximum-Window_aux;
        Max_pos=Pos_maximum+Window_aux;

        // check that the Ka_pos is in the interval
        if (Element_ka_pos>=Min_pos && Element_ka_pos<=Max_pos){
          // Search for the element in the list of found elements
          if (Map_selecteds.find(Element_name)==Map_selecteds.end()){
            // it is not in the list, so we include it
            // distance, position_in_vec, K-type
            Map_selecteds[Element_name]={true,Element_pos,{Window_aux,-1,_data_xrf_ns::_k_type::K_TYPE_A},{Window_aux,-1,_data_xrf_ns::_k_type::K_TYPE_B}};
          }

          // check if the Ka data was previously included
          if (Map_selecteds[Element_name].Data_ka.Position_in_vec_maximums==-1){
            // It is the first time > include the data

            // Update the distance to the peak
            Map_selecteds[Element_name].Data_ka.Distance_vec_data=fabs(Pos_maximum-Element_ka_pos);
            // Number of the selected peak
            Map_selecteds[Element_name].Data_ka.Position_in_vec_maximums=int(Num_peak);
            // add to Vec_maximums to know how many elements have been found for the peak
            Vec_maximums[Num_peak].Vec_elements.push_back({Element_name,_data_xrf_ns::_k_type::K_TYPE_A});
          }
          else{
            // the data was previously added
//            QMessageBox::information(this,"Information","The Ka was previosly included");
          }
        }


        // search for kb
        // get the kb
        Kb=Vec_xrf_pdb_data[Element_pos].Kb;
        // convert the position in keV to position in the list ( the minimum value for keV is 3)
        int Element_kb_pos=int(round(Kb/Step))-int(round(3/Step));
        // check that the Kb_pos is in the interval
        if (Element_kb_pos>=Min_pos && Element_kb_pos<=Max_pos){
          // Search the element in the list of found elements
          if (Map_selecteds.find(Element_name)==Map_selecteds.end()){
            // it is not in the list, so we include it
            Map_selecteds[Element_name]={true,Element_pos,{Window_aux,-1,_data_xrf_ns::_k_type::K_TYPE_A},{Window_aux,-1,_data_xrf_ns::_k_type::K_TYPE_B}};
          }

          // check if the Kb data was previously included
          if (Map_selecteds[Element_name].Data_kb.Position_in_vec_maximums==-1){
            // Update the distance to the peak
            Map_selecteds[Element_name].Data_kb.Distance_vec_data=abs(Pos_maximum-Element_kb_pos);
            // Number of the selected peak
            Map_selecteds[Element_name].Data_kb.Position_in_vec_maximums=Num_peak;
            // add to Vec_maximums
            Vec_maximums[Num_peak].Vec_elements.push_back({Element_name,_data_xrf_ns::_k_type::K_TYPE_B});
          }
          else{
            // the data was previously added
//            QMessageBox::information(this,"Information","The Kb was previosly included");
          }
        }
      }
      Window_aux=Window_aux+1;
    } while (Vec_maximums[Num_peak].Vec_elements.size()==0 && Window_aux<Window*1.5); // no tiene sentido?
    //    cout << "Peak=" << Num_peak << " num elementos=" << Vec_maximums[Num_peak].Vec_elements.size() << endl;
  }

  // remove the selected elements that only have kb
  std::map<std::string,_data_xrf_ns::_data_xrf_selected> Map_selecteds_aux; // an aux is needed to avoid the problem of removing an element while processing the Map
  for (auto It=Map_selecteds.begin();It!=Map_selecteds.end();It++){
    if (It->second.Data_ka.Position_in_vec_maximums==-1){
      // remove
      xrf_remove_element(It->first,Map_selecteds,Vec_maximums);
    }
    else{// hold
      Map_selecteds_aux[It->first]=It->second;
    }
  }

  Map_selecteds=Map_selecteds_aux;

  // check if the kb is in the same peak of ka
  for (auto It=Map_selecteds.begin();It!=Map_selecteds.end();It++){
    if (It->second.Data_ka.Position_in_vec_maximums==It->second.Data_kb.Position_in_vec_maximums){
      It->second.Data_kb.Position_in_vec_maximums=-1;
    }
  }


  // Check if there is superposition
  // case Pb/As

  std::map<std::string,_data_xrf_ns::_data_xrf_selected>::iterator It_As=Map_selecteds.find("As");
  std::map<std::string,_data_xrf_ns::_data_xrf_selected>::iterator It_Pb=Map_selecteds.find("Pb");

  if (It_As!=Map_selecteds.end() && It_Pb!=Map_selecteds.end()){
    // superposition Pb/As -> remove As
    int Distance_As=(*It_As).second.Data_ka.Distance_vec_data+(*It_As).second.Data_kb.Distance_vec_data;
    int Distance_Pb=(*It_Pb).second.Data_ka.Distance_vec_data+(*It_Pb).second.Data_kb.Distance_vec_data;
    if (Distance_Pb<=Distance_As){
      xrf_remove_element("As",Map_selecteds,Vec_maximums);
      Map_selecteds.erase("As");
      Vec_superposition.push_back("As");
    }
    else{
      xrf_remove_element("Pb",Map_selecteds,Vec_maximums);
      Map_selecteds.erase("Pb");
      Vec_superposition.push_back("Pb");
    }
  }

  // Check if there is superposition
  // case Ca/Sb

  std::map<std::string,_data_xrf_ns::_data_xrf_selected>::iterator It_Ca=Map_selecteds.find("Ca");
  std::map<std::string,_data_xrf_ns::_data_xrf_selected>::iterator It_Sb=Map_selecteds.find("Sb");

  if (It_Ca!=Map_selecteds.end() && It_Sb!=Map_selecteds.end()){
    // force Sb removal
    xrf_remove_element("Sb",Map_selecteds,Vec_maximums);
    Map_selecteds.erase("Sb");
    Vec_superposition.push_back("Sb");
  }

  // case Ti/Ba
  std::map<std::string,_data_xrf_ns::_data_xrf_selected>::iterator It_Ti=Map_selecteds.find("Ti");
  std::map<std::string,_data_xrf_ns::_data_xrf_selected>::iterator It_Ba=Map_selecteds.find("Ba");

  if (It_Ti!=Map_selecteds.end() && It_Ba!=Map_selecteds.end()){
    // superposition Ti/Ba
    if (It_Ti->second.Data_ka.Position_in_vec_maximums!=-1 && It_Ti->second.Data_kb.Position_in_vec_maximums!=-1){
      float Value_ka_Ti=Vec_maximums[It_Ti->second.Data_ka.Position_in_vec_maximums].Value;
      float Value_kb_Ti=Vec_maximums[It_Ti->second.Data_kb.Position_in_vec_maximums].Value;
      if ((Value_kb_Ti/Value_ka_Ti)<0.5){
        // remove Ba
        xrf_remove_element("Ba",Map_selecteds,Vec_maximums);
        Map_selecteds.erase("Ba");
        Vec_superposition.push_back("Ba");
      }
      else{
        // remove Ti
        xrf_remove_element("Ti",Map_selecteds,Vec_maximums);
        Map_selecteds.erase("Ti");
        Vec_superposition.push_back("Ti");
      }
    }
  }

  // case Fe/Co
  std::map<std::string,_data_xrf_ns::_data_xrf_selected>::iterator It_Fe=Map_selecteds.find("Fe");
  std::map<std::string,_data_xrf_ns::_data_xrf_selected>::iterator It_Co=Map_selecteds.find("Co");

  if (It_Fe!=Map_selecteds.end() && It_Co!=Map_selecteds.end()){
    // Fe and Co -> remove Co
    if (It_Fe->second.Data_ka.Position_in_vec_maximums!=-1 && It_Co->second.Data_ka.Position_in_vec_maximums!=-1){
      float Value_ka_Fe=Vec_maximums[It_Fe->second.Data_ka.Position_in_vec_maximums].Value;
      float Value_ka_Co=Vec_maximums[It_Co->second.Data_ka.Position_in_vec_maximums].Value;
      if (Value_ka_Fe>Value_ka_Co){
        // remove Co
        xrf_remove_element("Co",Map_selecteds,Vec_maximums);
        Map_selecteds.erase("Co");
      }
      else{
        // remove Fe
        xrf_remove_element("Fe",Map_selecteds,Vec_maximums);
        Map_selecteds.erase("Fe");
      }
    }
  }


  // check if there are any peak that has more than one element

  // this vector saves the the positions of the elements with ka that was selected for a peak, and also the the kb
  std::vector< std::pair<int,int>> Vec_maximums_aux(Vec_maximums.size(),{-1,-1});

  for (unsigned int Num_peak=0;Num_peak<Vec_maximums.size();Num_peak++){
    if (Vec_maximums[Num_peak].Vec_elements.size()==1){
      // only one peak, put the position in Vec_maximums and position in Vec_elements
      if (Vec_maximums[Num_peak].Vec_elements[0].K_type==_data_xrf_ns::_k_type::K_TYPE_A){
        xrf_add_element_to_result(Vec_maximums[Num_peak].Vec_elements[0].Name,Step,Map_selecteds,Vec_maximums,Vec_results_ka_kb,Vec_maximums_aux);
      }
    }
    else{
      // The peak has several several candidates.
      // Check only the ones with Ka.
      // compute the distance (Ka+kb)
      // Select the Ka element with the shortest distance
      int Pos=-1;
      int Min=1000;
      int Ka_plus_Kb_distance;

      // check the elements that share the same peak
      for (unsigned int Element_pos=0;Element_pos<Vec_maximums[Num_peak].Vec_elements.size();Element_pos++){
        if (Vec_maximums[Num_peak].Vec_elements[Element_pos].K_type==_data_xrf_ns::_k_type::K_TYPE_A){

          // compute the total distance
          Ka_plus_Kb_distance=Map_selecteds[Vec_maximums[Num_peak].Vec_elements[Element_pos].Name].Data_ka.Distance_vec_data+Map_selecteds[Vec_maximums[Num_peak].Vec_elements[Element_pos].Name].Data_kb.Distance_vec_data;

          if (Ka_plus_Kb_distance<Min){
            // the combination is less than the previous one
            Min=Ka_plus_Kb_distance;
            Pos=Element_pos;
          }
        }
      }

      // check if there is min distance
      if (Pos!=-1){
        // save the combination with the minimum
        xrf_add_element_to_result(Vec_maximums[Num_peak].Vec_elements[Pos].Name,Step,Map_selecteds,Vec_maximums,Vec_results_ka_kb,Vec_maximums_aux);
      }
    }
  }

  // all the elements have been processed. Some adjustment must be done

  // adjust the values if the Ka of element A and Kb of element B are in the same peak
  int Pos_ka;
  int Pos_kb;
//  float Max_value;
//  float Ka_value;
//  float Kb_value;
  for (unsigned int Num_peak=0;Num_peak<Vec_maximums_aux.size();Num_peak++){
    Pos_ka=Vec_maximums_aux[Num_peak].first;
    Pos_kb=Vec_maximums_aux[Num_peak].second;
    if (Pos_ka!=-1 && Pos_kb!=-1){
      // there is peak with a ka of one element and a kb of another element
#ifndef EXPERIMENTAL
      Ka_value=Vec_results_ka_kb[Pos_ka].Ka.Value;
      Kb_value=Vec_results_ka_kb[Pos_kb].Kb.Value;
      Max_value=Vec_maximums[Num_peak].Value;
      Vec_results_ka_kb[Pos_ka].Ka.Value=Max_value*Ka_value/(Ka_value+Kb_value);
      Vec_results_ka_kb[Pos_kb].Kb.Value=Max_value*Kb_value/(Ka_value+Kb_value);
#endif
#ifdef EXPERIMENTAL
      // experimental
      // put to not valid the Kb
      // we can't have two elements in the same peak because the equation system
      Vec_results_ka_kb[Pos_kb].Kb.Position=-1;
      Vec_results_ka_kb[Pos_kb].Kb.Position_kev=-1;
      Vec_results_ka_kb[Pos_kb].Kb.Value=0;
#endif
    }
  }

  // Now the elements of the PDB that are not found in OBS are added
  // This allows that they can be added to the list manually
  std::string Name_element_pdb;
  std::string Name_element_found;
  //  float Ka;
  //  float Kb;
  std::vector<int> Vec_pos_not_found;

  for (unsigned int Element_pdb_pos=0;Element_pdb_pos<Vec_xrf_pdb_data.size();Element_pdb_pos++){
    // get the name of the element
    Name_element_pdb=Vec_xrf_pdb_data[Element_pdb_pos].Name;
    bool Found=false;
    for (unsigned int Element_found_pos=0;Element_found_pos<Vec_results_ka_kb.size();Element_found_pos++){
      Name_element_found=Vec_results_ka_kb[Element_found_pos].Name;
      if (Name_element_pdb==Name_element_found){
        Found=true;
        break;
      }
    }
    if (Found==false) Vec_pos_not_found.push_back(Element_pdb_pos);
  }

  // insert the data of the not found elements
  int Element_pos_pdb;
  for (unsigned int Element_pos=0;Element_pos<Vec_pos_not_found.size();Element_pos++){
    Element_pos_pdb=Vec_pos_not_found[Element_pos];
    // get the name of the element
    Name_element_pdb=Vec_xrf_pdb_data[Element_pos_pdb].Name;

    // get the Ka value in keV
    Ka=Vec_xrf_pdb_data[Element_pos_pdb].Ka;
    // get the Kb value in keV
    Kb=Vec_xrf_pdb_data[Element_pos_pdb].Kb;

    // convert the position in keV to position in the list ( the minimum value for keV is 3)
    int Pos_element_ka=int(round(Ka/Step))-int(round(3/Step));
    int Pos_element_kb=int(round(Kb/Step))-int(round(3/Step));

    _data_xrf_ns::_data_xrf_ka_kb Result;

    Result.Name=Name_element_pdb;
    Result.Position_in_pdb=Element_pos_pdb;
    Result.Selected=false;
    Result.Found=false;
    // Ka
    // Position
    Result.Ka.Position=Pos_element_ka;
    Result.Ka.Value=Vec_xrf_obs_data[Index].Vec_processed_shifted_values[Pos_element_ka];
    Result.Ka.Position_kev=Ka;

    Result.Kb.Position=Pos_element_kb;
//    Result.Kb.Value=Vec_xrf_obs_data[Index].Vec_processed_shifted_values[Pos_element_kb];
    Result.Kb.Value=0;
    Result.Kb.Position_kev=Kb;
    // applies the ratio if kb is very big
//    if (Result.Kb.Value>Result.Ka.Value){
//      Result.Kb.Value=Result.Ka.Value*Vec_xrf_pdb_data[Element_pos].Kb_Ka_ratio;
//    }

    Vec_results_ka_kb.push_back(Result);
  }

#ifdef EXPERIMENTAL
  // Experimental

  // change all the Kb of all the elements to have the ratio
  std::string Name_element;
//  float Kb_pos;

  for (unsigned int Element_pos=0;Element_pos<Vec_results_ka_kb.size();Element_pos++){
    if (Vec_results_ka_kb[Element_pos].Found==true){
      // check if the Kb has no values
      if (Vec_results_ka_kb[Element_pos].Kb.Position==-1){
        // add the data from the PDB
        Name_element=Vec_results_ka_kb[Element_pos].Name;

        // get the position in the Vec_xrf_pdb
        unsigned int Element_pdb_pos;
        for (Element_pdb_pos=0;Element_pdb_pos<Vec_xrf_pdb_data.size();Element_pdb_pos++){
          if (Vec_xrf_pdb_data[Element_pdb_pos].Name==Name_element) break;
        }

        //
        float Kb_kev_pos=Vec_xrf_pdb_data[Element_pdb_pos].Kb;
        int Position=int(round(Kb_kev_pos/Step))-int(round(3/Step));

        Vec_results_ka_kb[Element_pos].Kb.Position=Position;
        Vec_results_ka_kb[Element_pos].Kb.Position_kev=Kb_kev_pos;
        Vec_results_ka_kb[Element_pos].Kb.Value=Vec_xrf_obs_data[Index].Vec_processed_shifted_values[Position];
      }
    }
  }

  // get data for equation system
  std::vector<_gaussians_adjustment_ns::_data_gaussian_adjustment> Vec_data_gaussian_adjustment;
//  float Ratio;

  // insert the Ka
  for (unsigned int Element_pos=0;Element_pos<Vec_results_ka_kb.size();Element_pos++){
    if (Vec_results_ka_kb[Element_pos].Found==true){
      Name_element=Vec_results_ka_kb[Element_pos].Name;

      // add the Ka data
      Vec_data_gaussian_adjustment.push_back({Name_element,Vec_results_ka_kb[Element_pos].Ka.Value,Vec_results_ka_kb[Element_pos].Ka.Position_kev,0.0f });
    }
  }

  // insert the Kb
//  for (unsigned int Element_pos=0;Element_pos<Vec_results_ka_kb.size();Element_pos++){
//    if (Vec_results_ka_kb[Element_pos].Found==true){
//      Name_element=Vec_results_ka_kb[Element_pos].Name;

//      Vec_data_gaussian_adjustment.push_back({Name_element,Vec_results_ka_kb[Element_pos].Kb.Value,Vec_results_ka_kb[Element_pos].Kb.Position_kev,0.0f});
//    }
//  }

  // resolve the equation system
  if (Vec_data_gaussian_adjustment.size()>0){
    float Sigma=float(_data_xrf_ns::XRF_GAUSSIANS_SIGMA)/(1/Step);
    _gaussians_adjustment Gaussian_adjustment(Sigma);

    Gaussian_adjustment.compute_weights(Vec_data_gaussian_adjustment);
  }


  // assign the compute weight
  int Pos=0;
  for (unsigned int Element_pos=0;Element_pos<Vec_results_ka_kb.size();Element_pos++){
    if (Vec_results_ka_kb[Element_pos].Found==true){
      if (Vec_data_gaussian_adjustment.size()>0 && Vec_data_gaussian_adjustment[Pos].Weight>=0) Vec_results_ka_kb[Element_pos].Ka.Value=Vec_data_gaussian_adjustment[Pos].Weight;
      else Vec_results_ka_kb[Element_pos].Ka.Value=0;
      Pos++;
      Vec_results_ka_kb[Element_pos].Kb.Value=0;
//      if (Vec_data_gaussian_adjustment[Pos].Weight>=0) Vec_results_ka_kb[Element_pos].Kb.Value=Vec_data_gaussian_adjustment[Pos].Weight;
//      else Vec_results_ka_kb[Element_pos].Kb.Value=0;
//      Pos++;
    }
  }
#endif

  return Vec_results_ka_kb;
}

//HEA
// used the positions of the maximum in the cleaned data to search for the peaks in the original data

std::vector<_data_xrf_ns::_data_maximum> _window_interpreter::xrf_search_maximums_in_obs(std::vector<float> Values, std::vector<float> Maximums, int Window)
{
  Q_UNUSED(Window)

  std::vector<_data_xrf_ns::_data_maximum> Maximums_aux;
//  int Pos_max;
  float Max;
  unsigned int Pos_max_obs;

  for (unsigned int i=0;i<Maximums.size();i++){
    // get the pos of the maximum
    Pos_max_obs=Maximums[i];
    Max=Values[Pos_max_obs];

    // save the position and max value
    Maximums_aux.push_back({Max,int(Pos_max_obs),std::vector<_data_xrf_ns::_data_element>()});
  }

  return Maximums_aux;
}

//HEA

void _window_interpreter::xrf_search_bottom_left(int Start,int& Pos,std::vector<float>& Values,std::vector<bool>& Valids)
{
  int Start_aux=Start;
  // Pos>0 this is because we could get Pos=-1
  while (Pos>0 && Values[Start_aux]>=Values[Pos] && Valids[Pos]==true){
    Valids[Pos]=false;
    Pos=Pos-1;
    Start_aux=Start_aux-1;
  }
}

//HEA

void _window_interpreter::xrf_search_bottom_right(int Start,int& Pos,std::vector<float>& Values,std::vector<bool>& Valids)
{
  int Start_aux=Start;
  // Pos<int(Values.size()-1) this is becase Pos could reach Values.size
  while (Pos<int(Values.size()-1) &&  Values[Start_aux]>=Values[Pos] && Valids[Pos]==true){
    Valids[Pos]=false;
    Pos=Pos+1;
    Start_aux=Start_aux+1;
  }
}


//HEA

void _window_interpreter::xrf_search_top(int& Start,int& Pos,std::vector<float>& Values)
{
  while (Values[Start]<Values[Pos]){
    Pos=Pos+1;
    Start=Start+1;
  }
}

// function for comparing names
bool compare_maximums_decrease(_data_xrf_ns::_data_pos_value &A,_data_xrf_ns::_data_pos_value &B)
{
    return (A.Value > B.Value);
}

// function for comparing names
bool compare_data_peaks_decrease(_data_xrf_ns::_data_peak &A,_data_xrf_ns::_data_peak &B)
{
    return (A.Value_max > B.Value_max);
}

//HEA
// search the maximums in filtered data
// the idea is to assume that the taken value is the maximum and check that all the values to the left or to the right are less than or equal than the used value
std::vector<float> _window_interpreter::xrf_search_maximums(std::vector<float> Values)
{

  std::vector<float> Maximums;
  std::vector<_data_xrf_ns::_data_pos_value> Pos_maximums;

  // catch all the peaks -> a change from low to high to low
  for (unsigned int i=1;i<Values.size()-1;i++){
    if (Values[i]>Values[i-1] && Values[i]>Values[i+1]) Pos_maximums.push_back({int(i),Values[i]});
  }

  // sort by highness
  sort(Pos_maximums.begin(),Pos_maximums.end(),compare_maximums_decrease);

  // now take each maximum and try to span it
  std::vector<bool> Vec_valids(Values.size(),true);

  // walk trough all the maximums
  int Top;
  int Left;
  int Right;
  float Value_min;
  float Width;
  float Height;
  float Area;
  std::vector<_data_xrf_ns::_data_peak> Vec_data_peaks;

  for (unsigned int i=0;i<Pos_maximums.size();i++){
    // get the apex
    Top=Pos_maximums[i].Position;
    if (Vec_valids[Top]==true){
      // It has not been used previously
      Vec_valids[Top]=false;
      Left=Top-1;
      Right=Top+1;
      // get the left extension
      xrf_search_bottom_left(Top,Left,Values,Vec_valids);
      // get the right extension
      xrf_search_bottom_right(Top,Right,Values,Vec_valids);
    }

    if (Values[Left]<Values[Right]) Value_min=Values[Left];
    else Value_min=Values[Right];

    Width=float(Right-Left);
    Height=Values[Top];
    // compute an approximation of peak's area
    Area=Width*Height/2;
    Vec_data_peaks.push_back({Left,Top,Right,Values[Top],Value_min,Width,Height,Area});

//    if (Width>=10){
//      Height=Values[Top];
//      // compute an approximation of peak's area
//      Area=Width*Height/2;
//      Vec_data_peaks.push_back({Left,Top,Right,Values[Top],Value_min,Width,Height,Area});
//    }
  }

  // sort by area
  sort(Vec_data_peaks.begin(),Vec_data_peaks.end(),compare_data_peaks_decrease);

  // include a max number of peaks
  for (unsigned int i=0;i<_data_xrf_ns::XRF_MAX_NUM_PEAKS && i<Vec_data_peaks.size();i++)  Maximums.push_back(Vec_data_peaks[i].Pos_top);

  return Maximums;
}


//HEA
// search the maximums in filtered data
// the idea is to assume that the taken value is the maximum and check that all the values to the left or to the right are less than or equal than the used value
//vector<float> _window_interpreter::xrf_search_maximums(vector<float> Values,int Window)
//{
//  std::vector<float> Maximums;
//  float Max;
//  int Count_left;
//  int Count_right;

//  // adjust the range to look at the position-window and position+Window
//  for (unsigned int i=Window;i<Values.size()-Window-1;i++){
//    // get the value. it is considered as a max
//    Max=Values[i];
//    Count_left=0;

//    // search to the left
//    for (int j=1;j<Window;j++){
//      if (Values[i-j]<=Max){
//        // count how many postions to the left comply the condition
//        Count_left=Count_left+1;
//      }
//    }

//    // if at least there are window-1 counts at the left, it is ok
//    if (Count_left==(Window-1)){
//      // check the right part
//      Count_right=0;
//      for (int j=1;j<Window;j++){
//        if (Values[i+j]<=Max){
//          // count how many postions to the right comply the condition
//          Count_right=Count_right+1;
//        }
//      }

//      // if at least there are window-1 counts at the right, it is ok
//      if (Count_right==(Window-1)){
//        // include the position of the maximum

//        Maximums.push_back(i);
//      }
//    }
//  }

//  return Maximums;
//}


//HEA

void _window_interpreter::xrf_select_elements_using_threshold(_data_xrf_ns::_data_xrf_obs &Data_xrf_obs,float Threshold1)
{
  std::vector<_data_xrf_ns::_data_xrf_ka_kb> Result;
  std::string Name;

  for (unsigned int Element_pos=0;Element_pos<Data_xrf_obs.Vec_elements_ka_kb.size();Element_pos++){
    Name=Data_xrf_obs.Vec_elements_ka_kb[Element_pos].Name;
    if (Data_xrf_obs.Map_elements_manually_selected[Name].Manual_selection==false){
      if (Data_xrf_obs.Vec_elements_ka_kb[Element_pos].Ka.Value<Threshold1){
        // under the threshold
        Data_xrf_obs.Vec_elements_ka_kb[Element_pos].Selected=false;
//        Data_xrf_obs.Vec_elements_ka_kb[i].Selected_threshold=false;
      }
      else{
        // above the threshold
        if (Data_xrf_obs.Vec_elements_ka_kb[Element_pos].Found==true){
          Data_xrf_obs.Vec_elements_ka_kb[Element_pos].Selected=true;
        }
        else{
          Data_xrf_obs.Vec_elements_ka_kb[Element_pos].Selected=false;
        }
//        Data_xrf_obs.Vec_elements_ka_kb[i].Selected_threshold=true;
      }
    }
  }
}



//HEA
std::vector<float> _window_interpreter::xrf_create_gaussian(int Num_steps,float Sigma)
{
  std::vector<float> Gaussian(Num_steps,0);

  float Mu=float(int(Num_steps/2));
//  float Amplitude=1/(Sigma*sqrtf(2*M_PI));

  for (unsigned int i=0;i<Gaussian.size();i++){
    Gaussian[i]=expf(-0.5*pow((float(i)-Mu)/Sigma,2));
  }

  return Gaussian;
}


//HEA

void _window_interpreter::xrf_create_gaussians(_data_xrf_ns::_data_xrf_obs &Data_xrf_obs)
{
  int Pos_Ka;
  float Value_Ka;
  int Pos_Kb;
  float Value_Kb;
  int Half_position;
  float Area_Ka;

  Data_xrf_obs.Vec_values_composition_of_gaussians.resize(Data_xrf_obs.Vec_values.size());
  std::fill(Data_xrf_obs.Vec_values_composition_of_gaussians.begin(), Data_xrf_obs.Vec_values_composition_of_gaussians.end(), 0.0f);

  std::vector<float> Vec_values_single_gaussian(Data_xrf_obs.Vec_values.size());

//  Data_xrf_obs.Gaussian_sigma
  int Num_steps_gaussian=int(roundf(1.8f*2.0f*_data_xrf_ns::XRF_GAUSSIANS_SIGMAS_TO_COVER));
  if (Num_steps_gaussian%2==0) Num_steps_gaussian=Num_steps_gaussian+1;

//  std::vector<float> Gaussian=xrf_create_gaussian(Num_steps_gaussian,_data_xrf_ns::XRF_GAUSSIANS_SIGMA);

  std::vector<float> Gaussian=xrf_create_gaussian(int(_data_xrf_ns::XRF_GAUSSIANS_SIGMA*2.0f*_data_xrf_ns::XRF_GAUSSIANS_SIGMAS_TO_COVER)+1,_data_xrf_ns::XRF_GAUSSIANS_SIGMA);
  std::vector<float> Gaussian1(Gaussian.size());
  Half_position = int(Gaussian1.size()/2);

  for (unsigned int Pos_element=0;Pos_element<Data_xrf_obs.Vec_elements_ka_kb.size();Pos_element++){
    if (Data_xrf_obs.Vec_elements_ka_kb[Pos_element].Selected){
      std::string Name=Data_xrf_obs.Vec_elements_ka_kb[Pos_element].Name;

      Pos_Ka=Data_xrf_obs.Vec_elements_ka_kb[Pos_element].Ka.Position;
      Value_Ka=Data_xrf_obs.Vec_elements_ka_kb[Pos_element].Ka.Value;

      // initialice the result of the single gaussian
      std::fill(Vec_values_single_gaussian.begin(), Vec_values_single_gaussian.end(), 0.0f);

      // scale the gaussian, saving the values in Gaussian1
      for (unsigned int j=0;j<Gaussian1.size();j++) Gaussian1[j]=Gaussian[j]*Value_Ka;

      // area
      Area_Ka=accumulate(Gaussian1.begin(),Gaussian1.end(),0.0f)*Data_xrf_obs.Step;

      // add the general gaussian in the corresponding position
      for (int j=0;j<int(Gaussian1.size());j++){
        // check that the position is valid
        if (Pos_Ka+j-Half_position>=0 && Pos_Ka+j-Half_position<int(Vec_values_single_gaussian.size())){
          // save the gloabal values
          Data_xrf_obs.Vec_values_composition_of_gaussians[Pos_Ka+j-Half_position]=Data_xrf_obs.Vec_values_composition_of_gaussians[Pos_Ka+j-Half_position]+Gaussian1[j];
          // save the individual values
          Vec_values_single_gaussian[Pos_Ka+j-Half_position]=Vec_values_single_gaussian[Pos_Ka+j-Half_position]+Gaussian1[j];
        }
      }

      Pos_Kb=Data_xrf_obs.Vec_elements_ka_kb[Pos_element].Kb.Position;
      Value_Kb=Data_xrf_obs.Vec_elements_ka_kb[Pos_element].Kb.Value;

      if (Pos_Kb>=0){
        // now the same with kb

        // scale the gaussian, saving the values in Gaussian1
        for (unsigned int j=0;j<Gaussian1.size();j++) Gaussian1[j]=Gaussian[j]*Value_Kb;

        // add the general gaussian in the corresponding position
        for (int j=0;j<int(Gaussian1.size());j++){
          // check that the position is valid
          if (Pos_Kb+j-Half_position>=0 && Pos_Kb+j-Half_position<int(Vec_values_single_gaussian.size())){
            // save the gloabal values
            Data_xrf_obs.Vec_values_composition_of_gaussians[Pos_Kb+j-Half_position]=Data_xrf_obs.Vec_values_composition_of_gaussians[Pos_Kb+j-Half_position]+Gaussian1[j];
            // save the individual values
            Vec_values_single_gaussian[Pos_Kb+j-Half_position]=Vec_values_single_gaussian[Pos_Kb+j-Half_position]+Gaussian1[j];
          }
        }
      }

      // save the individual result
      Data_xrf_obs.Vec_elements_ka_kb[Pos_element].Gaussian_area_ka=Area_Ka;
      Data_xrf_obs.Vec_elements_ka_kb[Pos_element].Vec_values_gaussian=Vec_values_single_gaussian;
    }
  }
}

//HEA

std::vector<float> _window_interpreter::xrf_create_tube_gaussian(int Size1,float Max_value,float Step)
{
  std::vector<float> Vec_single_gaussian(Size1,0.0f);

//  std::vector<float> Gaussian=xrf_create_gaussian(int(_data_xrf_ns::XRF_GAUSSIANS_SIGMA*2.0f*_data_xrf_ns::XRF_GAUSSIANS_SIGMAS_TO_COVER)+1,_data_xrf_ns::XRF_GAUSSIANS_SIGMA);
  std::vector<float> Gaussian=xrf_create_gaussian(int(1*2.0f*_data_xrf_ns::XRF_GAUSSIANS_SIGMAS_TO_COVER)+1,1);
  std::vector<float> Gaussian1(Gaussian.size());
  float Half_position = int(Gaussian1.size()/2);
  int Pos_Ka;

  if (Project_data.XRD_tube_type==_data_xrd_ns::_tube_type::TUBE_TYPE_CU) Pos_Ka= int(roundf((8.05-_data_xrf_ns::XRF_START_KEV)/Step));
  else Pos_Ka= int(roundf((6.9303-_data_xrf_ns::XRF_START_KEV)/Step));

  // scale the gaussian, saving the values in Gaussian1
  for (unsigned int i=0;i<Gaussian1.size();i++) Gaussian1[i]=Gaussian[i]*Max_value;

  // add the general gaussian in the corresponding position
  for (int i=0;i<int(Gaussian1.size());i++){
    // check that the position is valid
    if (Pos_Ka+i-Half_position>=0 && Pos_Ka+i-Half_position<int(Vec_single_gaussian.size())){
      // save the individual values
      Vec_single_gaussian[Pos_Ka+i-Half_position]=Vec_single_gaussian[Pos_Ka+i-Half_position]+Gaussian1[i];
    }
  }

  return Vec_single_gaussian;
}


//HEA

std::vector<float> _window_interpreter::xrd_create_spectral_from_peaks(std::vector<float> &Vec_2theta, std::vector<float> &Vec_intensity)
{
  int Pos;

  std::vector<float> Vec_values(int((_data_xrd_ns::END_2THETA-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA),0.0f);

  float Half_width_of_gaussian=int(XRD_gaussian_parameters_width/2.0f);

  std::vector<float> Gaussian=xrf_create_gaussian(int(XRD_gaussian_parameters_width/2.0f)*2*XRD_gaussian_parameters_sd+1,Half_width_of_gaussian);
  std::vector<float> Gaussian1(Gaussian.size());
  Half_width_of_gaussian=int(float(Gaussian.size())/2.0f);

  // add all the peaks
  for (unsigned int i=0;i<Vec_2theta.size();i++){

    // scale the gaussian, saving the values in Gaussian1
    // only the more important peaks
    if (Vec_intensity[i]>_data_xrd_ns::INTENSITY_THRESHOLD){
      for (unsigned int j=0;j<Gaussian1.size();j++) Gaussian1[j]=Gaussian[j]*Vec_intensity[i];

      // add the general gaussian in the corresponding position
      Pos=int(roundf((Vec_2theta[i]-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA));

      for (int j=0;j<int(Gaussian1.size());j++){
        // check that the position is valid
        if ((Pos+j-Half_width_of_gaussian)>=0 && (Pos+j-Half_width_of_gaussian)<int(Vec_values.size())){
          Vec_values[Pos+j-Half_width_of_gaussian]=Vec_values[Pos+j-Half_width_of_gaussian]+Gaussian1[j];
        }
      }
    }
  }

  return Vec_values;
}



//HEA

void _window_interpreter::smooth_data_mean(int Num_passes,std::vector<float> &Vec_value_in,std::vector<float> &Vec_value_out)
{
  std::vector<float> Vec_value_aux=Vec_value_in;

  Vec_value_out.resize(Vec_value_in.size());

  float Mean;
  for (int i=0;i<Num_passes;i++){
    for (unsigned int j=1;j<Vec_value_aux.size()-1;j++){
      Mean=(Vec_value_aux[j-1]+Vec_value_aux[j+1])/2;
      if (Vec_value_aux[j]>=Mean){
        Vec_value_out[j]=Mean;
      }
      else Vec_value_out[j]=Vec_value_aux[j];
    }

    // first
    if (Vec_value_aux[0]>=Vec_value_aux[1]/2){
      Vec_value_out[0]=Vec_value_aux[1]/2;
    }
    else Vec_value_out[0]=Vec_value_aux[0];

    // last
    if (Vec_value_aux[Vec_value_aux.size()-1]>=Vec_value_aux[Vec_value_aux.size()-2]/2){
      Vec_value_aux[Vec_value_aux.size()-1]=Vec_value_aux[Vec_value_aux.size()-2]/2;
    }
    else Vec_value_out[Vec_value_aux.size()-1]=Vec_value_aux[Vec_value_aux.size()-1];

//    cout << "in smooth" << endl;
//    show_data(Vec_value_out,Position_show,Num_positions_show);

    if (i<Num_passes-1)
    Vec_value_aux=Vec_value_out;
  }
}

//HEA

void _window_interpreter::smooth_data_gs(int Num_passes,std::vector<float> &Vec_value_in,std::vector<float> &Vec_value_out)
{
  assert(Vec_value_in.size()==Vec_value_out.size());

  _sg_filter SG;
  std::vector<double> Values1;
  Values1.resize(Vec_value_in.size());

  for (unsigned int i=0;i<Values1.size();i++) Values1[i]=double(Vec_value_in[i]);

  // do a good smoothing
  for (int i=0;i<Num_passes;i++) Values1=SG.smooth(Values1,5,2);

  // save the smooth data
  for (unsigned int i=0;i<Vec_value_out.size();i++){
    Vec_value_out[i]=float(Values1[i]);
    if (Vec_value_out[i]<0) Vec_value_out[i]=0;
  }
}


//HEA

bool _window_interpreter::least_squares(std::vector<float> Vec_x, std::vector<float> Vec_y, float &a, float &b)
{
  float Sum_x=0;
  float Sum_x2=0;
  float Sum_y=0;
  float Sum_y2=0;
  float Sum_xy=0;
//  float Numerator=0;
  float Denominator=0;
  float n=float(Vec_x.size());

  for(unsigned int i=0;i<Vec_x.size();i++){
    Sum_x = Sum_x + Vec_x[i];
    Sum_x2 = Sum_x2 + Vec_x[i]*Vec_x[i];
    Sum_y = Sum_y + Vec_y[i];
    Sum_y2 = Sum_y2 + Vec_y[i]*Vec_y[i];
    Sum_xy = Sum_xy + Vec_x[i]*Vec_y[i];
  }

  // ax+b
  //
  // a=(nXY-X*Y)/(nX2-(X)2
  // b=(Y*X2-X*XY)/(n*X2-(X)2)

  // a
  Denominator=n*Sum_x2-(Sum_x*Sum_x);

  if (Denominator!=0){
    a=(n*Sum_xy-Sum_x*Sum_y)/Denominator;
    b=(Sum_y*Sum_x2-Sum_x*Sum_xy)/Denominator;
    return true;
  }
  else return false;
}


//HEA

void _window_interpreter::remove_background(int Num_passes,std::vector<float> &Vec_value_in,std::vector<float> &Vec_value_out)
{
  assert(Vec_value_in.size()==Vec_value_out.size());

  float a,b;
  float Mean;
  std::vector<float> Vec_x(Vec_value_in.size());
  std::iota(Vec_x.begin(), Vec_x.end(), 0.0f);

  std::vector<float> Vec_values=Vec_value_in;
  std::vector<float> Vec_values_aux(Vec_value_in.size());

//  int Size=Vec_value_in.size()/2;
//  if (Size*2==Vec_value_in.size()) Size=Size-1;

//  _sg_filter SG;
//  double Mean;
//  std::vector<double> Values1;
//  Values1.resize(Vec_value_in.size());

//  for (unsigned int i=0;i<Values1.size();i++) Values1[i]=double(Vec_value_in[i]);

  // do a good smoothing
  for (int i=0;i<Num_passes;i++){
    // computes a new linear aproximation
//    Values1=SG.smooth(Values1,Size,1);
    least_squares(Vec_x, Vec_values,a,b);

    // assign the new values
    for (unsigned int j=0;j<Vec_values_aux.size();j++){
      Vec_values_aux[j]=float(j)*a+b;
    }

    // computes the mean
    Mean=std::accumulate(Vec_values_aux.begin(),Vec_values_aux.end(),0);
    Mean=Mean/double(Vec_values_aux.size());

    // remove all the values tha are greater than the mean
    for (unsigned int j=0;j<Vec_values_aux.size();j++){
      if (Vec_values[j]>Mean) Vec_values[j]=Mean;
    }
  }

  // remove the background
  for (unsigned int i=0;i<Vec_value_out.size();i++){
    Vec_value_out[i]=Vec_value_in[i]-float(Vec_values_aux[i]);
    if (Vec_value_out[i]<0) Vec_value_out[i]=0;
  }
}

//HEA

void _window_interpreter::xrf_update_using_manual_selection()
{
  std::string Name;

  for (unsigned int Position=0;Position<Vec_xrf_obs_data.size();Position++){
    if (Vec_xrf_obs_data[Position].Position!=-1){
      for (unsigned int Element_pos=0;Element_pos<Vec_xrf_obs_data[Position].Vec_elements_ka_kb.size();Element_pos++){
        Name=Vec_xrf_obs_data[Position].Vec_elements_ka_kb[Element_pos].Name;
        if (Vec_xrf_obs_data[Position].Map_elements_manually_selected[Name].Manual_selection==true){
          // change the Selection
          Vec_xrf_obs_data[Position].Vec_elements_ka_kb[Element_pos].Selected=Vec_xrf_obs_data[Position].Map_elements_manually_selected[Name].Selected;
        }
      }
    }
  }
}


//HEA

std::vector<float> _window_interpreter::xrf_shift_obs_data(std::vector<float> &Vec_values,float Step)
{
  // search the maximums in the filtered data. Only return the positions where the maximums are
  std::vector<float> Vec_maximums=xrf_search_maximums(Vec_values);

  // the maximums of the filtered data are used to search for the maximums in the real data
  std::vector<_data_xrf_ns::_data_maximum> Vec_maximums_obs=xrf_search_maximums_in_obs(Vec_values,Vec_maximums,XRF_num_steps_search_window);

  // compute the Ka position
  int Pos_Ka;

  if (Project_data.XRD_tube_type==_data_xrd_ns::_tube_type::TUBE_TYPE_CU) Pos_Ka= int(roundf((8.05-_data_xrf_ns::XRF_START_KEV)/Step));
  else Pos_Ka= int(roundf((6.9303-_data_xrf_ns::XRF_START_KEV)/Step));

  // search the best peak
  int Distance;
  int Minimum_distance=1e6;
  int Pos;
  for (unsigned int i=0;i<Vec_maximums_obs.size();i++){
    Distance=abs(Vec_maximums_obs[i].Position_vec_data-Pos_Ka);
    if (Distance<Minimum_distance){
      Minimum_distance=Distance;
      Pos=i;
    }
  }

  int Shift_distance=Pos_Ka-Vec_maximums_obs[Pos].Position_vec_data;

  std::vector<float> Result=shift_vector(Vec_values,Shift_distance);

  return Result;
}

//HEA

void _window_interpreter::xrf_preprocess_obs_data()
{
  float Area;
  float Mean;
  float Maximum;

  // create the tube peak



  for (unsigned int Position=0;Position<Vec_xrf_obs_data.size();Position++){
    if (Vec_xrf_obs_data[Position].Position!=-1){
      // search for the max value (to get the max global value)
      // also for obtaining the range for the axis
      Maximum=*max_element(Vec_xrf_obs_data[Position].Vec_values.begin(),Vec_xrf_obs_data[Position].Vec_values.end());

      // file maximum
      Vec_XRF_maximum_values[Position]=Maximum;
      // for the global maximum
      if (Maximum>Max_global_xrf_value){
        Max_global_xrf_value=Maximum;
      }

      // smooth
      // the Vec_values_smooth must be initialized
      Vec_xrf_obs_data[Position].Vec_processed_values.resize(Vec_xrf_obs_data[Position].Vec_values.size(),0.0f);

      if (XRF_smooth_type==_data_xrf_ns::_smooth_type::SMOOTH_TYPE_MEAN) smooth_data_mean(XRF_num_steps_smooth,Vec_xrf_obs_data[Position].Vec_values,Vec_xrf_obs_data[Position].Vec_processed_values);
      else smooth_data_gs(XRF_num_steps_smooth,Vec_xrf_obs_data[Position].Vec_values,Vec_xrf_obs_data[Position].Vec_processed_values);

      //
      remove_background(XRF_num_steps_subtract_background,Vec_xrf_obs_data[Position].Vec_processed_values,Vec_xrf_obs_data[Position].Vec_processed_values);

      // shift the data
      // create the peak
      Vec_tube_peak=xrf_create_tube_gaussian(Vec_xrf_obs_data[XRF_good_file_position].Vec_values.size(), Maximum, Vec_xrf_obs_data[XRF_good_file_position].Step);
      // do the convolution to search for the best match
//      xrf_convolution(Vec_tube_peak, Vec_xrf_obs_data[Position].Vec_processed_values, Vec_xrf_obs_data[Position],20);
//      Vec_xrf_obs_data[Position].Vec_processed_shifted_values=Vec_xrf_obs_data[Position].Vec_processed_values;
      Vec_xrf_obs_data[Position].Vec_processed_shifted_values=xrf_shift_obs_data(Vec_xrf_obs_data[Position].Vec_processed_values, Vec_xrf_obs_data[XRF_good_file_position].Step);

      // compute the mean
      Area=accumulate(Vec_xrf_obs_data[Position].Vec_processed_shifted_values.begin(),Vec_xrf_obs_data[Position].Vec_processed_shifted_values.end(),0.0f);
      Mean=Area/float(Vec_xrf_obs_data[Position].Vec_processed_shifted_values.size());

      // search the maximums in the filtered data. Only return the positions where the maximums are
      std::vector<float> Vec_maximums=xrf_search_maximums(Vec_xrf_obs_data[Position].Vec_processed_shifted_values);

      // the maximums of the filtered data are used to search for the maximums in the real data
      std::vector<_data_xrf_ns::_data_maximum> Vec_maximums_obs=xrf_search_maximums_in_obs(Vec_xrf_obs_data[Position].Vec_processed_shifted_values,Vec_maximums,XRF_num_steps_search_window);

      // search the elements using the maximums
      Vec_xrf_obs_data[Position].Area=Area;
      Vec_xrf_obs_data[Position].Mean=Mean;
      Vec_xrf_obs_data[Position].Vec_elements_ka_kb=xrf_search_elements(Position,Vec_maximums_obs,XRF_num_steps_search_window);

      // assign the values
      // linear
      Vec_xrf_axis_ranges_linear[Position].X_default_range.lower=3;
      Vec_xrf_axis_ranges_linear[Position].X_default_range.upper=13;
      Vec_xrf_axis_ranges_linear[Position].Y_default_range.lower=0;
      Vec_xrf_axis_ranges_linear[Position].Y_default_range.upper=Maximum*_data_xrf_ns::XRF_ADDITIONAL_SPACE;
      Vec_xrf_axis_ranges_linear[Position].X_range=Vec_xrf_axis_ranges_linear[Position].X_default_range;
      Vec_xrf_axis_ranges_linear[Position].Y_range=Vec_xrf_axis_ranges_linear[Position].Y_default_range;

      // log
      Vec_xrf_axis_ranges_log[Position].X_default_range.lower=3;
      Vec_xrf_axis_ranges_log[Position].X_default_range.upper=13;
      Vec_xrf_axis_ranges_log[Position].Y_default_range.lower=0.01f;
      Vec_xrf_axis_ranges_log[Position].Y_default_range.upper=powf(10,ceilf(log10f(Maximum*5)));
      Vec_xrf_axis_ranges_log[Position].X_range=Vec_xrf_axis_ranges_log[Position].X_default_range;
      Vec_xrf_axis_ranges_log[Position].Y_range=Vec_xrf_axis_ranges_log[Position].Y_default_range;

      // create the Gaussians
      xrf_create_gaussians(Vec_xrf_obs_data[Position]);
    }
  }
}


//HEA

void _window_interpreter::xrf_process_obs_data()
{
  Listwidget_data_xrf_obs->clear();

  // axis ranges
  Vec_xrf_axis_ranges_linear.resize(Vec_xrf_obs_data.size());
  Vec_xrf_axis_ranges_log.resize(Vec_xrf_obs_data.size());

  // process the data of all files
  //  Vec_xrf_obs_data.resize(Vec_xrf_obs_data.size());

  // for threshod percentages
//  Vec_threshold_percentage_xrf.resize(Vec_xrf_obs_data.size(),_data_xrf_ns::XRF_THRESHOLD_PERCENTAGE);

  // for the maximums
  Vec_XRF_maximum_values.resize(Vec_xrf_obs_data.size(),0);

  for (unsigned int i=0;i<Vec_xrf_obs_data.size();i++){
    if (Vec_xrf_obs_data[i].Position!=-1){
      // create the element in the list
      QListWidgetItem *Item;
      Item=new QListWidgetItem;
      Item->setText(QString::fromStdString(Vec_xrf_obs_data[i].File_name));
      Listwidget_data_xrf_obs->addItem(Item);
      }
    else{
      // create the element in the list
      QListWidgetItem *Item;
      Item=new QListWidgetItem;
      Item->setText(QString::fromStdString("NULL"));
      Listwidget_data_xrf_obs->addItem(Item);
    }
  }

//  std::cout << __LINE__ << " 1 " << std::endl;
  // process
  xrf_preprocess_obs_data();

  // initialize the manually selected map
  std::string Name;
  for (unsigned int Position=0;Position<Vec_xrf_obs_data.size();Position++){
    if (Vec_xrf_obs_data[Position].Position!=-1){
      for (unsigned int Element_pos=0;Element_pos<Vec_xrf_obs_data[Position].Vec_elements_ka_kb.size();Element_pos++){
        Name=Vec_xrf_obs_data[Position].Vec_elements_ka_kb[Element_pos].Name;
        Vec_xrf_obs_data[Position].Map_elements_manually_selected[Name]={false,Vec_xrf_obs_data[Position].Vec_elements_ka_kb[Element_pos].Selected};
      }
    }
  }

  // order the data using the Ka value
  xrf_order_obs_data_for_all_files(int(_table_xrf_ns::_column_type::COLUMN_TYPE_KA_POSITION),_window_interpreter_ns::_order_mode::ORDER_MODE_INCREASE);

//  std::cout << __LINE__ << " 2 " << std::endl;

  // the initial selection
//  Selected_file_position=0;

  // select those elements that have a value greater than the threshold
  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

  // update tab XRF data
  xrf_set_threshold(XRF_threshold_percentage);

  xrf_create_spectral_chart(Selected_file_position);

  Listwidget_data_xrf_obs->blockSignals(true);
  Listwidget_data_xrf_obs->setCurrentRow(Selected_file_position);
  Listwidget_data_xrf_obs->blockSignals(false);

  Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
}

//HEA

void _window_interpreter::xrf_elements_obs_row_changed_slot(int Row)
{
  if (Row>=0){
    Selected_file_position=Row;

    xrf_set_threshold(XRF_threshold_percentage);

    xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);
    xrf_create_spectral_chart(Selected_file_position);
    Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);

    if (XRD_obs_data_loaded==true){
      Listwidget_data_xrd_obs->blockSignals(true);
      Listwidget_data_xrd_obs->setCurrentRow(Selected_file_position);
      Listwidget_data_xrd_obs->blockSignals(false);

      xrd_assign_data_to_table();

      if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
        xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
      else
        xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
    }
  }
}


//HEA

void _window_interpreter::xrf_change_button_state(int Element)
{
  Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[Element].Selected=!Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[Element].Selected;

  // save the current Selection value
  std::string Name=Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[Element].Name;
  Vec_xrf_obs_data[Selected_file_position].Map_elements_manually_selected[Name].Manual_selection=true;
  Vec_xrf_obs_data[Selected_file_position].Map_elements_manually_selected[Name].Selected=Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[Element].Selected;

  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

  // create the Gaussians
  xrf_create_gaussians(Vec_xrf_obs_data[Selected_file_position]);

  xrf_create_spectral_chart(Selected_file_position);

  //  Table_data_xrf->update_table(Result_elements);
  Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);

  // update XRD
  if (XRD_valid==true) xrd_update();
}


//HEA

//void _window_interpreter::slider_xrf_threshold_slot(int Value)
//{
//  float Threshold_xrf=Vec_XRF_maximum_values[Selected_file_position]*float(Value)*Threshold_percentage_xrf/_window_interpreter_ns::Slider_threshold_factor_xrf;

//  // adjust the doublespinbox
//  Doublespinbox_threshold_xrf->blockSignals(true);
//  Doublespinbox_threshold_xrf->setValue(Threshold_xrf);
//  Doublespinbox_threshold_xrf->blockSignals(false);

//  // all the elements are changed
////  for (unsigned int i=0;i<Vec_xrf_obs_data.size();i++){
////    xrf_select_elements_using_threshold(Vec_xrf_obs_data[i],Vec_XRF_maximum_values[i]*Threshold_percentage_xrf);
////  }

//  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*Threshold_percentage_xrf);

//  xrf_create_spectral_chart(Selected_file_position);

//  Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb);
//}

//HEA


void _window_interpreter::xrf_threshold_slot(int Value)
{
//  for (unsigned int i=0;i<Vec_threshold_percentage_xrf.size();i++) Vec_threshold_percentage_xrf[i]=Value;
  XRF_threshold_percentage=Value;

//  Vec_threshold_percentage_xrf[Selected_file_position]=Value; ????

  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

  xrf_create_gaussians(Vec_xrf_obs_data[Selected_file_position]);

  xrf_create_spectral_chart(Selected_file_position);

  Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
}

//HEA

void _window_interpreter::xrf_set_threshold(int Value)
{
  // adjust the doublespinbox
  Spinbox_threshold_xrf->blockSignals(true);
  Spinbox_threshold_xrf->setValue(Value);
  Spinbox_threshold_xrf->blockSignals(false);;
}


//HEA

void _window_interpreter::xrf_add_element_tool_slot(bool Checked)
{
  if (Checked){
    Toolbutton_xrf1->setIcon(Icons[int(_window_interpreter_ns::_action_type::ACTION_ADD_ELEMENT)][1]);
    Toolbutton_xrf2->setIcon(Icons[int(_window_interpreter_ns::_action_type::ACTION_REMOVE_ELEMENT)][0]);
    Toolbutton_xrf2->blockSignals(true);
    Toolbutton_xrf2->setChecked(false);
    Toolbutton_xrf2->blockSignals(false);
    Action_type=_window_interpreter_ns::_action_type::ACTION_ADD_ELEMENT;
  }
  else{
    Toolbutton_xrf1->setIcon(Icons[int(_window_interpreter_ns::_action_type::ACTION_ADD_ELEMENT)][0]);
    Action_type=_window_interpreter_ns::_action_type::ACTION_NONE;
    Element_selected.Name="";
  }

  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_delete_element_tool_slot(bool Checked)
{
  if (Checked){
    Toolbutton_xrf2->setIcon(Icons[int(_window_interpreter_ns::_action_type::ACTION_REMOVE_ELEMENT)][1]);
    Toolbutton_xrf1->setIcon(Icons[int(_window_interpreter_ns::_action_type::ACTION_ADD_ELEMENT)][0]);
    Toolbutton_xrf1->blockSignals(true);
    Toolbutton_xrf1->setChecked(false);
    Toolbutton_xrf1->blockSignals(false);
    Element_selected.Name="";
    Action_type=_window_interpreter_ns::_action_type::ACTION_REMOVE_ELEMENT;
  }
  else{
    Toolbutton_xrf2->setIcon(Icons[int(_window_interpreter_ns::_action_type::ACTION_REMOVE_ELEMENT)][0]);
    Action_type=_window_interpreter_ns::_action_type::ACTION_NONE;
  }

  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_add_element_action()
{
  if (Element_selected.Name!=""){
    Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.push_back(Element_selected);

    xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

    xrf_create_gaussians(Vec_xrf_obs_data[Selected_file_position]);

    Element_selected.Name="";

    xrf_create_spectral_chart(Selected_file_position);

    Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
  }
}

//HEA

void _window_interpreter::xrf_remove_element_action(int Element_pos)
{
  // remove
  for(unsigned int i=Element_pos;i<Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.size()-1;i++){
    Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[i]=Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[i+1];
  }
  Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.pop_back();

  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(XRF_threshold_percentage)/100.0f);

  xrf_create_gaussians(Vec_xrf_obs_data[Selected_file_position]);

  Element_selected.Name="";

  xrf_create_spectral_chart(Selected_file_position);

  Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
}


//HEA

void _window_interpreter::xrf_color_obs_raw_slot(QColor Color)
{
  XRF_color_obs_raw=Color;
  save_settings();

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_color_obs_processed_slot(QColor Color)
{
  XRF_color_obs_processed=Color;
  save_settings();

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_color_obs_processed_shifted_slot(QColor Color)
{
  XRF_color_obs_processed_shifted=Color;
  save_settings();

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_color_gaussians_slot(QColor Color)
{
  XRF_color_gaussians=Color;
  save_settings();

  xrf_create_spectral_chart(Selected_file_position);
}


// XRD -----------------
//HEA

//void _window_interpreter::load_pigments()
//{
//  std::string File_name;
//  std::string Error;

//  QDir Directory(_window_interpreter_interpreter_interpreter_ns::FOLDER_PDB+"/");
//  std::string Dir_images=Directory.absolutePath().toStdString();

//  QStringList Files_txt = Directory.entryList(QStringList() << "*.pgm.txt",QDir::Files);

//  Files_txt.sort();

//  if (Files_txt.size()>0){
//    std::vector<float> Values;
//    std::vector<_common_interpreter_ns::_peak_data> Peaks;

//    foreach(QString File_name, Files_txt) {
//      QFileInfo File_info(File_name);
//      std::string Short_name=File_info.baseName().toStdString();
//      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

//      std::vector<std::string> Vec_names;
//      std::vector<std::string> Vec_formulas;
//      std::vector<std::string> Vec_elements;
//      _vertex3f Color;

//      _file_xrd_pdb_csv File;
//      File.open(Long_name,_file_xrd_pdb_csv::_mode::MODE_READ);

//      if (File.read(Vec_names,Vec_formulas,Vec_elements,Color,Values,Error)==true){
//        File.close();

//        Vec_xrd_pdb_data.push_back({Short_name,Vec_names,Vec_formulas,Vec_elements,Color,Values,Values,0,Peaks});
//      }
//      else{
//        File.close();

//        QMessageBox::critical(this, tr("Error"),QString::fromStdString(Error));
//        QApplication::quit();
//        exit(-1);
//      }
//    }
//  }
//  else{
//    QMessageBox::critical(this, tr("Error"),tr("there are not '.txt' (xrd) files in pdb folder"));
//    QApplication::quit();
//    exit(-1);
//  }
//}


//HEA
#ifdef XRD_ACTIVE
void _window_interpreter::xrd_compute_ranges()
{
  // ranges for the XRD files
  // the data for the ranges of the charts of the files
  Vec_xrd_axis_ranges_linear.resize(Vec_xrd_obs_data.size());
  Vec_xrd_axis_ranges_log.resize(Vec_xrd_obs_data.size());

  // compute the max for the RAW data
  float Maximum;
  for (unsigned int i=0;i<Vec_xrd_obs_data.size();i++){
    if (Vec_xrd_obs_data[i].Position!=-1){
      // search for the max value (to get the max global value)
      // also for obtaining the range for the axis
      Maximum=*max_element(Vec_xrd_obs_data[i].Vec_values.begin(),Vec_xrd_obs_data[i].Vec_values.end());

      Vec_xrd_axis_ranges_linear[i].X_default_range.lower=float(_data_xrd_ns::START_2THETA);
      Vec_xrd_axis_ranges_linear[i].X_default_range.upper=float(_data_xrd_ns::END_2THETA);
      Vec_xrd_axis_ranges_linear[i].Y_default_range.lower=0.0f;
      Vec_xrd_axis_ranges_linear[i].Y_default_range.upper=Maximum*_data_xrd_ns::XRF_ADDITIONAL_SPACE;
      Vec_xrd_axis_ranges_linear[i].X_range=Vec_xrd_axis_ranges_linear[i].X_default_range;
      Vec_xrd_axis_ranges_linear[i].Y_range=Vec_xrd_axis_ranges_linear[i].Y_default_range;

      // log
      Vec_xrd_axis_ranges_log[i].X_default_range.lower=float(_data_xrd_ns::START_2THETA);
      Vec_xrd_axis_ranges_log[i].X_default_range.upper=float(_data_xrd_ns::END_2THETA);
      Vec_xrd_axis_ranges_log[i].Y_default_range.lower=0;
      Vec_xrd_axis_ranges_log[i].Y_default_range.upper=powf(10,ceilf(log10f(Maximum)));
      Vec_xrd_axis_ranges_log[i].X_range=Vec_xrd_axis_ranges_log[i].X_default_range;
      Vec_xrd_axis_ranges_log[i].Y_range=Vec_xrd_axis_ranges_log[i].Y_default_range;
    }
  }


  // ranges for matrix data
  std::vector<float> Vec_max_values_obs(Vec_xrd_obs_data.size(),-1);

  // compute the max for the NORMALIZED data
  for (unsigned int i=0;i<Vec_xrd_obs_data.size();i++){
    if (Vec_xrd_obs_data[i].Position!=-1){
      Vec_max_values_obs[i]=*max_element(Vec_xrd_obs_data[i].Vec_normalized_values.begin(),Vec_xrd_obs_data[i].Vec_normalized_values.end());
    }
    else{
      Vec_max_values_obs[i]=0;
    }
  }

  //
  std::vector<float> Vec_max_values_pdb(Vec_xrd_pdb_data.size(),-1);

  // compute the max for the PDB data
  for (unsigned int i=0;i<Vec_xrd_pdb_data.size();i++){
    Vec_max_values_pdb[i]=*max_element(Vec_xrd_pdb_data[i].Vec_normalized_values.begin(),Vec_xrd_pdb_data[i].Vec_normalized_values.end());
  }

  // the data for the ranges of the charts of the matrix of results
  Mat_xrd_spectral_axis_range_linear.resize(Mat_xrd_obs_vs_pdb_data.size());
  Mat_xrd_spectral_axis_range_log.resize(Mat_xrd_obs_vs_pdb_data.size());
  Mat_xrd_correlation_axis_range_linear.resize(Mat_xrd_obs_vs_pdb_data.size());

  for (unsigned int i=0;i<Mat_xrd_spectral_axis_range_linear.size();i++){
    Mat_xrd_spectral_axis_range_linear[i].resize(Vec_xrd_pdb_data.size());
    Mat_xrd_spectral_axis_range_log[i].resize(Vec_xrd_pdb_data.size());
    Mat_xrd_correlation_axis_range_linear[i].resize(Vec_xrd_pdb_data.size());
  }

  // set the ranges depending on the maximums
  for (unsigned int i=0;i<Vec_max_values_obs.size();i++){
    for (unsigned int j=0;j<Vec_max_values_pdb.size();j++){
      // select between the maximum of the OBS and the maximum of the PDB
      Maximum=Vec_max_values_obs[i];
      if (Vec_max_values_pdb[j]>Maximum) Maximum=Vec_max_values_pdb[j];

      // spectral
      Mat_xrd_spectral_axis_range_linear[i][j].X_default_range.lower=float(_data_xrd_ns::START_2THETA);
      Mat_xrd_spectral_axis_range_linear[i][j].X_default_range.upper=float(_data_xrd_ns::END_2THETA);
      Mat_xrd_spectral_axis_range_linear[i][j].Y_default_range.lower=0.0f;
      Mat_xrd_spectral_axis_range_linear[i][j].Y_default_range.upper=Maximum*_data_xrf_ns::XRF_ADDITIONAL_SPACE;
      Mat_xrd_spectral_axis_range_linear[i][j].X_range=Mat_xrd_spectral_axis_range_linear[i][j].X_default_range;
      Mat_xrd_spectral_axis_range_linear[i][j].Y_range=Mat_xrd_spectral_axis_range_linear[i][j].Y_default_range;

      Mat_xrd_spectral_axis_range_log[i][j].X_default_range.lower=float(_data_xrd_ns::START_2THETA);
      Mat_xrd_spectral_axis_range_log[i][j].X_default_range.upper=float(_data_xrd_ns::END_2THETA);
      Mat_xrd_spectral_axis_range_log[i][j].Y_default_range.lower=0.01f;
      Mat_xrd_spectral_axis_range_log[i][j].Y_default_range.upper=powf(10,ceilf(log10f(Maximum*1.1f)));;
      Mat_xrd_spectral_axis_range_log[i][j].X_range=Mat_xrd_spectral_axis_range_log[i][j].X_default_range;
      Mat_xrd_spectral_axis_range_log[i][j].Y_range=Mat_xrd_spectral_axis_range_log[i][j].Y_default_range;

      // correlation
//      float Max_x=-1;
//      float Max_y=-1;
//      for (unsigned int k=0;k<Mat_xrd_obs_vs_pdb_data[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].Vec_sqrt_values.size();k++){
//        if (Mat_xrd_obs_vs_pdb_data[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].Vec_sqrt_values[k]>Max_x) Max_x=Mat_xrd_obs_vs_pdb_data[Selected_file_position][Vec_xrd_selected_position[Selected_file_position]].Vec_sqrt_values[k];
//        if (Vec_xrd_pdb_data[Vec_xrd_selected_position[Selected_file_position]].Vec_normalized_values[k]>Max_y) Max_y=Vec_xrd_pdb_data[Vec_xrd_selected_position[Selected_file_position]].Vec_normalized_values[k];
//      }

      float Max_x=1;
      float Max_y=1;

      Mat_xrd_correlation_axis_range_linear[i][j].X_default_range.lower=-1.0f;
      Mat_xrd_correlation_axis_range_linear[i][j].X_default_range.upper=Max_x*1.05;
      Mat_xrd_correlation_axis_range_linear[i][j].Y_default_range.lower=-1.0f;
      Mat_xrd_correlation_axis_range_linear[i][j].Y_default_range.upper=Max_y*1.05;
      Mat_xrd_correlation_axis_range_linear[i][j].X_range=Mat_xrd_correlation_axis_range_linear[i][j].X_default_range;
      Mat_xrd_correlation_axis_range_linear[i][j].Y_range=Mat_xrd_correlation_axis_range_linear[i][j].Y_default_range;

    }
  }
}

//HEA

void _window_interpreter::xrd_process_obs_vs_pdb_data()
{
//  std::string Name;
  for (unsigned int i=0;i<Vec_xrd_obs_data.size();i++){
    if (Vec_xrd_obs_data[i].Position!=-1){
      Vec_xrd_row_names[i]=Vec_xrd_obs_data[i].File_name;
      for (unsigned int j=0;j<Vec_xrd_pdb_data.size();j++){
        compute_data_xrd_obs_pdb(i,j);
        // assign the value of peaks
        Mat_xrd_obs_vs_pdb_data[i][j].Num_peaks=Vec_xrd_pdb_data[j].Vec_peaks.size();
      }
    }
    else{
      Vec_xrd_row_names[i]="NULL";
    }
  }
}

//HEA
// compute the class of each cell. Only one time

void _window_interpreter::xrd_classify_cells_class_mat_obs_vs_pdb()
{
//  float Value;
  int Num_elements_not_found;
  bool XRF_file_exists;

  for (unsigned int Row=0;Row<Mat_xrd_obs_vs_pdb_data.size();Row++){
    for (unsigned int Col=0;Col<Mat_xrd_obs_vs_pdb_data[Row].size();Col++){
      Num_elements_not_found=Mat_xrd_obs_vs_pdb_data[Row][Col].Vec_elements_not_found.size();
      XRF_file_exists=Mat_xrd_obs_vs_pdb_data[Row][Col].XRF_used;

      if (XRF_file_exists==false)
        Mat_xrd_obs_vs_pdb_data[Row][Col].Class_type=_data_xrd_ns::_class_type::CLASS_TYPE_NO_XRF_FILE;
      else if (Num_elements_not_found>0)
        Mat_xrd_obs_vs_pdb_data[Row][Col].Class_type=_data_xrd_ns::_class_type::CLASS_TYPE_NO_ELEMENTS;
      else
        Mat_xrd_obs_vs_pdb_data[Row][Col].Class_type=_data_xrd_ns::_class_type::CLASS_TYPE_VALID;
    }
  }
}

//HEA

bool order_by_percentage_down(const _data_xrd_ns::_xrd_order_data &a, const _data_xrd_ns::_xrd_order_data &b)
{
  return a.Percentage > b.Percentage;
}

bool order_by_percentage_up(const _data_xrd_ns::_xrd_order_data &a, const _data_xrd_ns::_xrd_order_data &b)
{
  return a.Percentage < b.Percentage;
}

bool order_by_name_down(const _data_xrd_ns::_xrd_order_data &a, const _data_xrd_ns::_xrd_order_data &b)
{
  return a.Name > b.Name;
}

bool order_by_name_up(const _data_xrd_ns::_xrd_order_data &a, const _data_xrd_ns::_xrd_order_data &b)
{
  return a.Name < b.Name;
}


//HEA

void _window_interpreter::xrd_classify_cells_threshold_mat_obs_vs_pdb()
{
  float Value;

  for (unsigned int i=0;i<Vec_xrd_obs_data.size();i++){
    if (Vec_xrd_obs_data[i].Position!=-1){
      // initilize the vector with the order
      Vec_xrd_obs_data[i].Vec_order.resize(Vec_xrd_pdb_data.size());
      for (unsigned j=0;j<Vec_xrd_pdb_data.size();j++){
        Vec_xrd_obs_data[i].Vec_order[j].Name=Vec_xrd_pdb_data[j].File_name;
        Vec_xrd_obs_data[i].Vec_order[j].Position=j;
      }
    }
  }

  for (unsigned int Row=0;Row<Mat_xrd_obs_vs_pdb_data.size();Row++){
    if (Vec_xrd_obs_data[Row].Position!=-1){
      for (unsigned int Col=0;Col<Mat_xrd_obs_vs_pdb_data[Row].size();Col++){

        Value=int(roundf(Mat_xrd_obs_vs_pdb_data[Row][Col].Correlation_coefficient_squared*100.0f)); // R^2
        Vec_xrd_obs_data[Row].Vec_order[Col].Percentage=Value;

        if (Value>=XRD_correlation_good_threshold){
          Mat_xrd_obs_vs_pdb_data[Row][Col].Valid_type=_data_xrd_ns::_valid_type::VALID_TYPE_GOOD;
          Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected=true;
          Mat_xrd_obs_vs_pdb_data[Row][Col].Show=true;
        }
        else if (Value>=XRD_correlation_medium_threshold) {
          Mat_xrd_obs_vs_pdb_data[Row][Col].Valid_type=_data_xrd_ns::_valid_type::VALID_TYPE_MEDIUM;
          Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected=true;
          Mat_xrd_obs_vs_pdb_data[Row][Col].Show=true;
        }
        else if (Value>=XRD_correlation_bad_threshold){
          Mat_xrd_obs_vs_pdb_data[Row][Col].Valid_type=_data_xrd_ns::_valid_type::VALID_TYPE_BAD;
          Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected=false;
          Mat_xrd_obs_vs_pdb_data[Row][Col].Show=true;
        }
        else{
          Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected=false;
          Mat_xrd_obs_vs_pdb_data[Row][Col].Show=false;
        }
      }
      // order the vector
      std::sort(Vec_xrd_obs_data[Row].Vec_order.begin(), Vec_xrd_obs_data[Row].Vec_order.end(), order_by_percentage_down);

      // this is only for the first time, then there is a selected position that must be maintained
      if (Vec_xrd_selected_position[Row]==-1) Vec_xrd_selected_position[Row]=Vec_xrd_obs_data[Row].Vec_order[0].Position;
    }
  }
}

//HEA
// apply the manual selection

void _window_interpreter::xrd_apply_manual_selection_to_mat_obs_vs_pdb()
{
//  if (Mat_xrd_obs_vs_pdb_data_selected.size()==0){
//    Mat_xrd_obs_vs_pdb_data_selected.resize(Mat_xrd_obs_vs_pdb_data.size());
//    for (unsigned int Pos_file=0;Pos_file<Mat_xrd_obs_vs_pdb_data.size();Pos_file++){
//      Mat_xrd_obs_vs_pdb_data_selected[Pos_file].resize(Mat_xrd_obs_vs_pdb_data[Pos_file].size());
//    }

//    // assign the computed values in the start
//    for (unsigned int Pos_file=0;Pos_file<Mat_xrd_obs_vs_pdb_data.size();Pos_file++){
//      for (unsigned int Pos_pigment=0;Pos_pigment<Mat_xrd_obs_vs_pdb_data[Pos_file].size();Pos_pigment++){
//        Mat_xrd_obs_vs_pdb_data_selected[Pos_file][Pos_pigment]=Mat_xrd_obs_vs_pdb_data[Pos_file][Pos_pigment].Selected;
//      }
//    }
//  }
//  else{ // update the data with the previous values
//    for (unsigned int Pos_file=0;Pos_file<Mat_xrd_obs_vs_pdb_data.size();Pos_file++){
//      for (unsigned int Pos_pigment=0;Pos_pigment<Mat_xrd_obs_vs_pdb_data[Pos_file].size();Pos_pigment++){
//        Mat_xrd_obs_vs_pdb_data[Pos_file][Pos_pigment].Selected=Mat_xrd_obs_vs_pdb_data_selected[Pos_file][Pos_pigment];
//      }
//    }
//  }
}
#endif

//HEA
// OPTIONS

void _window_interpreter::options_parameters(QColor XRD_color_file_not_exists1, QColor XRD_color_element_not_exists1, QColor XRD_color_valid_good1, QColor Color_valid_medium1, QColor Color_valid_bad1, QColor Color_font1)
{
  Q_UNUSED(Color_valid_medium1)
  Q_UNUSED(Color_valid_bad1)
  Q_UNUSED(Color_font1)

  XRD_color_file_not_exists=XRD_color_file_not_exists1;
  XRD_color_element_not_exists=XRD_color_element_not_exists1;
  XRD_color_valid_good=XRD_color_valid_good1;
//  Color_valid_medium=Color_valid_medium1;
//  Color_valid_bad=Color_valid_bad1;
//  Color_font=Color_font1;

  save_settings();

#ifdef XRD_ACTIVE
  xrd_assign_data_to_table();
  /*
  Table_xrd_obs_vs_pdb_data->set_data(Vec_xrd_row_names,Vec_xrd_col_names,Mat_xrd_obs_vs_pdb_data,Vec_xrd_visible_columns_in_table);*/

  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
#endif
}

//HEA

void _window_interpreter::options_parameters_xrf(int XRF_title_font_size1,int XRF_legend_font_size1,int XRF_graph_line_width1)
{
  XRF_title_font_size=XRF_title_font_size1;
  XRF_legend_font_size=XRF_legend_font_size1;
  XRF_graph_line_width=XRF_graph_line_width1;

//  save_settings();
  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::options_parameters_xrd(int XRD_title_font_size1,int XRD_legend_font_size1,int XRD_graph_line_width1)
{
  XRD_title_font_size=XRD_title_font_size1;
  XRD_legend_font_size=XRD_legend_font_size1;
  XRD_graph_line_width=XRD_graph_line_width1;

//  save_settings();

#ifdef XRD_ACTIVE
  xrd_assign_data_to_table();

  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
#endif
}

//HEA

void _window_interpreter::options_slot()
{
  if (!W_options){
    W_options=new _w_options_interpreter(this);
    connect(W_options,SIGNAL(accepted()),W_options,SLOT(close()));
  }

  W_options->show();
  W_options->raise();
  W_options->activateWindow();
}


//HEA

void _window_interpreter::pdb_mode_slot()
{
  if (XRD_valid==true){
    XRD_pdb_mode=!XRD_pdb_mode;
    if (XRD_pdb_mode){
      Action_save_pdb->setEnabled(true);
      Groupbox_level_subtract_xrd->setEnabled(true);
    }
    else{
      Action_save_pdb->setEnabled(false);
      Groupbox_level_subtract_xrd->setEnabled(false);
    }

    xrd_process_data();
  }
}

//HEA

void _window_interpreter::save_pdb_slot()
{
  if (XRD_valid==true){
    // get the information of the element
    _w_xrd_pdb_data *W_xrd_pdb_data=new _w_xrd_pdb_data(this);
    W_xrd_pdb_data->raise();

    if (W_xrd_pdb_data->exec()==QDialog::Accepted){
      QStringList List=PDB_name.split(',');

      QFileDialog Dialog(this,"Save PDB file","pdb","*.pgm.csv");
      Dialog.setWindowModality(Qt::WindowModal);
      Dialog.setAcceptMode(QFileDialog::AcceptSave);
      Dialog.setDefaultSuffix("txt");
      Dialog.selectFile(List[0]+".pgm.csv");
      if (Dialog.exec()== QDialog::Accepted){
        _data_io::xrd_save_pdb_spectral(this, Dialog.selectedFiles().at(0).toStdString(), _data_xrd_ns::Vec_type_name[int(PDB_type)].toStdString(), _data_xrd_ns::Vec_tube_name[int(PDB_tube_type)].toStdString(), _data_xrd_ns::Vec_normalized_name[int(PDB_normalized)].toStdString(), PDB_name.toStdString(), PDB_formula.toStdString(), PDB_xrf_elements.toStdString(), PDB_rgb_color.toStdString(), _data_xrd_ns::START_2THETA, Vec_xrd_obs_data[Selected_file_position].Vec_normalized_values);
      }
    }
  }
}


#ifdef XRD_ACTIVE
//HEA

void _window_interpreter::xrd_pdb_options_slot()
{
  // read the folders with XRF PDB
  std::string File_name;
  std::string Error;

  QDir Directory(QString::fromStdString(_common_window_ns::FOLDER_PDB+"/"));
  std::string Dir_images=Directory.absolutePath().toStdString();
  QStringList Name_selectors;
  Name_selectors << "Cu_spectral_*" << "Co_spectral_*";
#ifdef ASTM_MODE_ACTIVE
  Name_selectors << "Cu_astm_*" << "Co_astm_*";
#endif

  QStringList Folders = Directory.entryList(Name_selectors,QDir::Dirs,QDir::Name);

  if (Folders.size()>0){
    QStringList Folders_short_names;
    foreach(QString Folder_name, Folders){
      QFileInfo Folder_info(Folder_name);
//      std::string Short_name=Folder_info.baseName().toStdString();
//      std::string Long_name=_common_window_interpreter_interpreter_interpreter_ns::FOLDER_PDB+"/"+Folder_info.fileName().toStdString();

      Folders_short_names.push_back(Folder_info.baseName());
    }

    _w_xrd_pdb_options *W_xrd_pdb_options=new _w_xrd_pdb_options(this,Folders_short_names);
    connect(W_xrd_pdb_options,SIGNAL(accepted()),W_xrd_pdb_options,SLOT(apply_slot()));

    W_xrd_pdb_options->exec();
//  W_xrd_pdb_options->raise();
//  W_xrd_pdb_options->activateWindow();
  }
  else{
    QMessageBox::critical(this, this->tr("Error"),this->tr("there are not XRD folders in pdb folder"));
    QApplication::quit();
    exit(-1);
  }
}


#endif

// function for comparing names
bool compare_names_increase(_data_xrf_ns::_data_xrf_ka_kb &A,_data_xrf_ns::_data_xrf_ka_kb &B)
{
    return (A.Name < B.Name);
}

bool compare_names_decrease(_data_xrf_ns::_data_xrf_ka_kb &A,_data_xrf_ns::_data_xrf_ka_kb &B)
{
    return (A.Name > B.Name);
}

// function for comparing ka position
bool compare_ka_positions_kev_increase(_data_xrf_ns::_data_xrf_ka_kb &A,_data_xrf_ns::_data_xrf_ka_kb &B)
{
    return (A.Ka.Position_kev < B.Ka.Position_kev);
}

bool compare_ka_positions_kev_decrease(_data_xrf_ns::_data_xrf_ka_kb &A,_data_xrf_ns::_data_xrf_ka_kb &B)
{
    return (A.Ka.Position_kev > B.Ka.Position_kev);
}


// function for comparing ka value
bool compare_ka_values_increase(_data_xrf_ns::_data_xrf_ka_kb &A,_data_xrf_ns::_data_xrf_ka_kb &B)
{
    return (A.Ka.Value < B.Ka.Value);
}

bool compare_ka_values_decrease(_data_xrf_ns::_data_xrf_ka_kb &A,_data_xrf_ns::_data_xrf_ka_kb &B)
{
    return (A.Ka.Value > B.Ka.Value);
}

//HEA

void _window_interpreter::xrf_order_obs_data(_table_xrf_ns::_column_type Column_type)
{
  switch(Column_type){
    case _table_xrf_ns::_column_type::COLUMN_TYPE_ELEMENT: //name
    XRF_data_order_element_name_increase=!XRF_data_order_element_name_increase;
    if (XRF_data_order_element_name_increase)    sort(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.end(),compare_names_increase);
    else sort(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.end(),compare_names_decrease);
    break;
  case _table_xrf_ns::_column_type::COLUMN_TYPE_KA_POSITION: //Ka position
    XRF_data_order_ka_positions_kev_increase=!XRF_data_order_ka_positions_kev_increase;
    if (XRF_data_order_ka_positions_kev_increase)
      sort(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.end(),compare_ka_positions_kev_increase);
    else sort(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.end(),compare_ka_positions_kev_decrease);
    break;
  case _table_xrf_ns::_column_type::COLUMN_TYPE_KA_VALUE: // ka value
    XRF_data_order_ka_values_increase=!XRF_data_order_ka_values_increase;
    if (XRF_data_order_ka_values_increase)
      sort(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.end(),compare_ka_values_increase);
    else sort(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb.end(),compare_ka_values_decrease);
    break;
  default:break;
  }

  Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
}

//HEA

void _window_interpreter::xrf_order_obs_data_for_all_files(int Col, _window_interpreter_ns::_order_mode Order_mode)
{

  for (unsigned int File_pos=0;File_pos<Vec_xrf_obs_data.size();File_pos++){
    switch(_table_xrf_ns::_column_type(Col)){
    case _table_xrf_ns::_column_type::COLUMN_TYPE_ELEMENT: //name
      if (Order_mode==_window_interpreter_ns::_order_mode::ORDER_MODE_INCREASE)    sort(Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.end(),compare_names_increase);
      else sort(Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.end(),compare_names_decrease);
      break;
    case _table_xrf_ns::_column_type::COLUMN_TYPE_KA_POSITION: //Ka position
      if (Order_mode==_window_interpreter_ns::_order_mode::ORDER_MODE_INCREASE)
        sort(Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.end(),compare_ka_positions_kev_increase);
      else sort(Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.end(),compare_ka_positions_kev_decrease);
      break;
    case _table_xrf_ns::_column_type::COLUMN_TYPE_KA_VALUE: // ka value
      if (Order_mode==_window_interpreter_ns::_order_mode::ORDER_MODE_INCREASE)
        sort(Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.end(),compare_ka_values_increase);
      else sort(Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.begin(),Vec_xrf_obs_data[File_pos].Vec_elements_ka_kb.end(),compare_ka_values_decrease);
      break;
    default:break;
    }
  }
}


#ifdef XRD_ACTIVE
//HEA

void _window_interpreter::xrd_color_obs_raw_slot(QColor Color)
{
  XRD_color_obs_raw=Color;
  save_settings();

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_obs_processed_slot(QColor Color)
{
  XRD_color_obs_processed=Color;
  save_settings();

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_obs_processed_shifted_slot(QColor Color)
{
  XRD_color_obs_processed_shifted=Color;
  save_settings();

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_pdb_slot(QColor Color)
{
  XRD_color_pdb=Color;
  save_settings();

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_sqrt_slot(QColor Color)
{
  XRD_color_sqrt=Color;
  save_settings();

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_file_not_exists_slot(QColor Color)
{
  XRD_color_file_not_exists=Color;
  save_settings();

  xrd_assign_data_to_table();
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_element_not_exists_slot(QColor Color)
{
  XRD_color_element_not_exists=Color;
  save_settings();

  xrd_assign_data_to_table();
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_valid_good_slot(QColor Color)
{
  XRD_color_valid_good=Color;
  save_settings();

  xrd_assign_data_to_table();
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_valid_medium_slot(QColor Color)
{
  XRD_color_valid_medium=Color;
  save_settings();

  xrd_assign_data_to_table();
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_color_valid_bad_slot(QColor Color)
{
  XRD_color_valid_bad=Color;
  save_settings();

  xrd_assign_data_to_table();
  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

//void _window_interpreter::xrd_color_font_slot(QColor Color)
//{
//  Color_font=Color;
//  save_settings();

//  xrd_assign_data_to_table();
////  Table_xrd_obs_vs_pdb_data->set_data(Vec_xrd_row_names,Vec_xrd_col_names,Mat_xrd_obs_vs_pdb_data,Vec_xrd_visible_columns_in_table);
//  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
//}

//HEA

//void _window_interpreter::xrd_compute_visible_columns_in_table(std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb> > &Mat_xrd_obs_vs_pdb_data)
//{
//  bool Valid;
//  XRD_data_to_show=false;
//  Vec_xrd_visible_columns_in_table.clear();
//  for (unsigned int Col=0;Col<Mat_xrd_obs_vs_pdb_data[0].size();Col++){
//    Valid=false;
//    for (unsigned int Row=0;Row<Mat_xrd_obs_vs_pdb_data.size();Row++){
//      if (Mat_xrd_obs_vs_pdb_data[Row][Col].Show==true){
//        Valid=true;
//        XRD_data_to_show=true;
//        break;
//      }
//    }
//    if (Valid==true) Vec_xrd_visible_columns_in_table.push_back(Col);
//  }
//}

//HEA

//void _window_interpreter::xrd_show_main_slot(bool State)
//{
//  Q_UNUSED(State)

//  XRD_show_file_not_exists=false;
//  XRD_show_element_not_exists=false;
//  XRD_show_valid=false;

//  if (Radiobutton_xrd_show_main_file_not_exists->isChecked()) XRD_show_file_not_exists=true;
//  if (Radiobutton_xrd_show_main_element_not_exists->isChecked()) XRD_show_element_not_exists=true;
//  if (Radiobutton_xrd_show_main_valid->isChecked()){
//    XRD_show_valid=true;
//    Groupbox_xrd_show_valid->show();
////    Frame_xrd_show_valid->show();
//  }
//  else{
//    XRD_show_valid=false;
//    Groupbox_xrd_show_valid->hide();
////    Frame_xrd_show_valid->hide();
//  }

//  save_settings();

//  xrd_compute_visible_columns_in_table(Mat_xrd_obs_vs_pdb_data);

//  xrd_update_info(true);

//  xrd_assign_data_to_table();
////  Table_xrd_obs_vs_pdb_data->set_data(Vec_xrd_row_names,Vec_xrd_col_names,Mat_xrd_obs_vs_pdb_data,Vec_xrd_visible_columns_in_table);
//}

//HEA

//void _window_interpreter::xrd_show_main_valid_slot(int State)
//{
////  if (State==Qt::Unchecked){
////    XRD_show_valid=false;
////    Vec_xrd_selected_row_in_table[0]=Selected_file_position;
////    Vec_xrd_selected_col_in_table[0]=XRD_selected_col_in_table;
////  }
////  else{
////    XRD_show_valid=true;
////    XRD_selected_row_in_table=Vec_xrd_selected_row_in_table[0];
////    XRD_selected_col_in_table=Vec_xrd_selected_col_in_table[0];
////    if (XRD_selected_col_in_table>=0) XRD_selected_col_in_mat=Vec_xrd_visible_columns_in_table[XRD_selected_col_in_table];
////  }

////  save_settings();

//  xrd_classify_cells_threshold_mat_obs_vs_pdb();

//  xrd_compute_visible_columns_in_table(Mat_xrd_obs_vs_pdb_data);

//  xrd_assign_data_to_table();

//  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
//  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);

////  xrd_update_info(true);

////  if (XRD_data_to_show==true) xrd_update_info_and_chart_of_selected_table_cell();
//}

//HEA

//void _window_interpreter::xrd_show_main_element_not_exists_slot(int State)
//{
////  if (State==Qt::Unchecked){
////    XRD_show_element_not_exists=false;
////    Vec_xrd_selected_row_in_table[0]=XRD_selected_row_in_table;
////    Vec_xrd_selected_col_in_table[0]=XRD_selected_col_in_table;
////  }
////  else{
////    XRD_show_element_not_exists=true;
////    XRD_selected_row_in_table=Vec_xrd_selected_row_in_table[0];
////    XRD_selected_col_in_table=Vec_xrd_selected_col_in_table[0];
////    if (XRD_selected_col_in_table>=0) XRD_selected_col_in_mat=Vec_xrd_visible_columns_in_table[XRD_selected_col_in_table];
////  }

////  save_settings();

//  xrd_classify_cells_threshold_mat_obs_vs_pdb();

//  xrd_compute_visible_columns_in_table(Mat_xrd_obs_vs_pdb_data);

//  xrd_assign_data_to_table();

//  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
//  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);

////  xrd_update_info(true);

////  if (XRD_data_to_show==true) xrd_update_info_and_chart_of_selected_table_cell();
//}

//HEA

//void _window_interpreter::xrd_show_main_file_not_exists_slot(int State)
//{
////  if (State==Qt::Unchecked){
////    XRD_show_file_not_exists=false;
////    Vec_xrd_selected_row_in_table[0]=XRD_selected_row_in_table;
////    Vec_xrd_selected_col_in_table[0]=XRD_selected_col_in_table;
////  }
////  else{
////    XRD_show_file_not_exists=true;
////    XRD_selected_row_in_table=Vec_xrd_selected_row_in_table[0];
////    XRD_selected_col_in_table=Vec_xrd_selected_col_in_table[0];
////    if (XRD_selected_col_in_table>=0) XRD_selected_col_in_mat=Vec_xrd_visible_columns_in_table[XRD_selected_col_in_table];
////  }

////  save_settings();

//  xrd_classify_cells_threshold_mat_obs_vs_pdb();

//  xrd_compute_visible_columns_in_table(Mat_xrd_obs_vs_pdb_data);

//  xrd_assign_data_to_table();

//  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
//  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);

////  xrd_update_info(true);

////  if (XRD_data_to_show==true) xrd_update_info_and_chart_of_selected_table_cell();
//}


//HEA

//void _window_interpreter::xrd_show_valid_good_slot(int State)
//{
////  if (State==Qt::Unchecked){
////    XRD_show_valid_good=false;
////    Vec_xrd_selected_row_in_table[0]=XRD_selected_row_in_table;
////    Vec_xrd_selected_col_in_table[0]=XRD_selected_col_in_table;
////  }
////  else{
////    XRD_show_valid_good=true;
////    XRD_selected_row_in_table=Vec_xrd_selected_row_in_table[0];
////    XRD_selected_col_in_table=Vec_xrd_selected_col_in_table[0];
////    if (XRD_selected_col_in_table>=0) XRD_selected_col_in_mat=Vec_xrd_visible_columns_in_table[XRD_selected_col_in_table];
////  }

////  save_settings();

//  xrd_classify_cells_threshold_mat_obs_vs_pdb();

//  xrd_compute_visible_columns_in_table(Mat_xrd_obs_vs_pdb_data);

//  xrd_assign_data_to_table();

//  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
//  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);

////  xrd_update_info(true);

////  if (XRD_data_to_show==true) xrd_update_info_and_chart_of_selected_table_cell();
//}


//HEA

//void _window_interpreter::xrd_show_valid_medium_slot(int State)
//{
////  if (State==Qt::Unchecked){
////    XRD_show_valid_medium=false;
////    Vec_xrd_selected_row_in_table[1]=XRD_selected_row_in_table;
////    Vec_xrd_selected_col_in_table[1]=XRD_selected_col_in_table;
////  }
////  else{
////    XRD_show_valid_medium=true;
////    XRD_selected_row_in_table=Vec_xrd_selected_row_in_table[1];
////    XRD_selected_col_in_table=Vec_xrd_selected_col_in_table[1];
////    if (XRD_selected_col_in_table>=0) XRD_selected_col_in_mat=Vec_xrd_visible_columns_in_table[XRD_selected_col_in_table];
////  }

////  save_settings();

//  xrd_classify_cells_threshold_mat_obs_vs_pdb();

//  xrd_compute_visible_columns_in_table(Mat_xrd_obs_vs_pdb_data);

//  xrd_assign_data_to_table();

//  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
//  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);

////  xrd_update_info(true);

////  if (XRD_data_to_show==true) xrd_update_info_and_chart_of_selected_table_cell();
//}

//HEA

//void _window_interpreter::xrd_show_valid_bad_slot(int State)
//{
////  if (State==Qt::Unchecked){
////    XRD_show_valid_bad=false;
////    Vec_xrd_selected_row_in_table[2]=XRD_selected_row_in_table;
////    Vec_xrd_selected_col_in_table[2]=XRD_selected_col_in_table;
////  }
////  else{
////    XRD_show_valid_bad=true;
////    XRD_selected_row_in_table=Vec_xrd_selected_row_in_table[2];
////    XRD_selected_col_in_table=Vec_xrd_selected_col_in_table[2];
////    if (XRD_selected_col_in_table>=0) XRD_selected_col_in_mat=Vec_xrd_visible_columns_in_table[XRD_selected_col_in_table];
////  }

////  save_settings();

//  xrd_classify_cells_threshold_mat_obs_vs_pdb();

//  xrd_compute_visible_columns_in_table(Mat_xrd_obs_vs_pdb_data);

//  xrd_assign_data_to_table();

//  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL) xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
//  else xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);

////  xrd_update_info(true);

////  if (XRD_data_to_show==true) xrd_update_info_and_chart_of_selected_table_cell();
//}

//HEA

//void _window_interpreter::xrd_selected_col_in_table(int Selected_col_xrd1)
//{
//  if (XRD_show_valid_good) Vec_xrd_selected_col_in_table[0]=Selected_col_xrd1;
//  if (XRD_show_valid_medium) Vec_xrd_selected_col_in_table[1]=Selected_col_xrd1;
//  if (XRD_show_valid_bad) Vec_xrd_selected_col_in_table[2]=Selected_col_xrd1;

//  if (Selected_col_xrd1>=0) XRD_selected_col_in_mat=Vec_xrd_visible_columns_in_table[Selected_col_xrd1];
//  XRD_selected_col_in_table=Selected_col_xrd1;
//}


//HEA

void _window_interpreter::xrd_chart_type_slot(bool State)
{
  if (State==true){
    if (Radiobutton_xrd_chart_type_spectra->isChecked()){
    XRD_chart_type=_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL;

    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
    }
    else{
    XRD_chart_type=_data_xrd_ns::_chart_type::CHART_TYPE_CORRELATION;

    xrd_create_pdb_sqrt_correlation_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
    }
  }
}
#endif

//HEA

void _window_interpreter::xrf_chart_scale_slot(bool State)
{
  Q_UNUSED(State)

  if (Radiobutton_xrf_chart_scale_linear->isChecked()){
    XRF_chart_scale=_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR;
  }
  else{
    XRF_chart_scale=_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LOGARITHMIC;
  }

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_threshold_percentage_slot(int Value)
{
  //  Threshold_percentage_xrf=float(Value)/100.0f;
//  Vec_threshold_percentage_xrf[Selected_file_position]=Value;
  XRF_threshold_percentage=Value;

  // select those elements that have a value greater than the factor
  xrf_select_elements_using_threshold(Vec_xrf_obs_data[Selected_file_position],Vec_XRF_maximum_values[Selected_file_position]*float(Value)/100.0f);

  // update tab XRF data
  xrf_set_threshold(Value);

  xrf_create_spectral_chart(Selected_file_position);

  Listwidget_data_xrf_obs->blockSignals(true);
  Listwidget_data_xrf_obs->setCurrentRow(0);
  Listwidget_data_xrf_obs->blockSignals(false);

  Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
}

//HEA

void _window_interpreter::xrf_show_obs_graph_slot(int State)
{
  if (State==Qt::Checked) XRF_show_graph_obs_values=true;
  else{
    if (XRF_show_graph_processed_values==true || XRF_show_graph_processed_shifted_values==true || XRF_show_graph_gaussians_values==true) XRF_show_graph_obs_values=false;
    else{
      Checkbox_show_graph_obs_xrf->blockSignals(true);
      Checkbox_show_graph_obs_xrf->setCheckState(Qt::Checked);
      Checkbox_show_graph_obs_xrf->blockSignals(false);
    }
  }

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_show_processed_graph_slot(int State)
{
  if (State==Qt::Checked) XRF_show_graph_processed_values=true;
  else{
    if (XRF_show_graph_obs_values==true || XRF_show_graph_processed_shifted_values || XRF_show_graph_gaussians_values==true) XRF_show_graph_processed_values=false;
    else{
      Checkbox_show_graph_processed_xrf->blockSignals(true);
      Checkbox_show_graph_processed_xrf->setCheckState(Qt::Checked);
      Checkbox_show_graph_processed_xrf->blockSignals(false);
    }
  }

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_show_processed_shifted_graph_slot(int State)
{
  if (State==Qt::Checked) XRF_show_graph_processed_shifted_values=true;
  else{
    if (XRF_show_graph_obs_values==true || XRF_show_graph_processed_values==true || XRF_show_graph_gaussians_values==true) XRF_show_graph_processed_shifted_values=false;
    else{
      Checkbox_show_graph_processed_shifted_xrf->blockSignals(true);
      Checkbox_show_graph_processed_shifted_xrf->setCheckState(Qt::Checked);
      Checkbox_show_graph_processed_shifted_xrf->blockSignals(false);
    }
  }

  xrf_create_spectral_chart(Selected_file_position);
}

//HEA

void _window_interpreter::xrf_show_gaussians_graph_slot(int State)
{
  if (State==Qt::Checked) XRF_show_graph_gaussians_values=true;
  else{
    if (XRF_show_graph_obs_values==true || XRF_show_graph_processed_values==true || XRF_show_graph_processed_shifted_values==true) XRF_show_graph_gaussians_values=false;
    else{
      Checkbox_show_graph_gaussians_xrf->blockSignals(true);
      Checkbox_show_graph_gaussians_xrf->setCheckState(Qt::Checked);
      Checkbox_show_graph_gaussians_xrf->blockSignals(false);
    }
  }

  xrf_create_spectral_chart(Selected_file_position);
}

//void _window_interpreter::xrf_smooth_type_mean_slot(bool State)
//{
//  Q_UNUSED(State)

//  if (Radiobutton_xrf_mean_smooth_type->isChecked()){
//    XRF_mean_smooth_type=true;
//    XRF_gs_smooth_type=false;
//  }
//  else{
//    XRF_mean_smooth_type=false;
//    XRF_gs_smooth_type=true;
//  }
//  xrf_process_change();
//}

//HEA

//void _window_interpreter::xrf_smooth_type_gs_slot(bool State)
//{
//  Q_UNUSED(State)

//  if (Radiobutton_xrf_gs_smooth_type->isChecked()){
//    XRF_mean_smooth_type=false;
//    XRF_gs_smooth_type=true;
//  }
//  else{
//    XRF_mean_smooth_type=true;
//    XRF_gs_smooth_type=false;
//  }
//  xrf_process_change();
//}


//HEA
#ifdef XRD_ACTIVE
//void _window_interpreter::xrd_smooth_type_mean_slot(bool State)
//{
//  Q_UNUSED(State)

//  if (Radiobutton_xrd_mean_smooth_type->isChecked()){
//    XRD_mean_smooth_type=true;
//    XRD_gs_smooth_type=false;
//  }
//  else{
//    XRD_mean_smooth_type=false;
//    XRD_gs_smooth_type=true;
//  }
//  xrd_process_data();
////  xrd_update_info(true);
//}

//HEA

//void _window_interpreter::xrd_smooth_type_gs_slot(bool State)
//{
//  Q_UNUSED(State)

//  if (Radiobutton_xrd_gs_smooth_type->isChecked()){
//    XRD_mean_smooth_type=false;
//    XRD_gs_smooth_type=true;
//  }
//  else{
//    XRD_mean_smooth_type=true;
//    XRD_gs_smooth_type=false;
//  }
//  xrd_process_data();
////  xrd_update_info(true);
//}

//HEA

void _window_interpreter::xrd_normalization_type_mean_slot(bool State)
{
  Q_UNUSED(State)

  if (Radiobutton_xrd_normalization_type_mean->isChecked()){
    XRD_normalization_type=_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_MEAN;
    xrd_process_data();
  }
}

//HEA

void _window_interpreter::xrd_normalization_type_percentage_slot(bool State)
{
  Q_UNUSED(State)

  if (Radiobutton_xrd_normalization_type_percentage->isChecked()){
    XRD_normalization_type=_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_PERCENTAGE;
    xrd_process_data();
  }
}

//HEA

void _window_interpreter::xrd_computation_type_sqrt_slot(bool State)
{
  Q_UNUSED(State)

  if (Radiobutton_xrd_computation_type_sqrt->isChecked()){
    XRD_computation_type=_data_xrd_ns::_computation_type::COMPUTATION_TYPE_SQRT;
    Label_computation_type->setText("SQRT(OBS*PDB)");
    xrd_process_data();
  }
}

//HEA

void _window_interpreter::xrd_computation_type_not_zero_slot(bool State)
{
  Q_UNUSED(State)

  if (Radiobutton_xrd_computation_type_not_zero->isChecked()){
    XRD_computation_type=_data_xrd_ns::_computation_type::COMPUTATION_TYPE_NOT_ZERO;
    Label_computation_type->setText("PDB NOT 0");
    xrd_process_data();
  }
}

//HEA

void _window_interpreter::xrd_show_graph_raw_obs_slot(int State)
{
  if (State==Qt::Checked) XRD_show_graph_obs_raw=true;
  else{
    if (XRD_show_graph_obs_processed==true || XRD_show_graph_obs_processed_shifted==true || XRD_show_graph_pdb==true || XRD_show_graph_sqrt==true) XRD_show_graph_obs_raw=false;
    else{
      Checkbox_xrd_show_raw_obs_graph->blockSignals(true);
      Checkbox_xrd_show_raw_obs_graph->setCheckState(Qt::Checked);
      Checkbox_xrd_show_raw_obs_graph->blockSignals(false);
    }
  }

  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_show_graph_obs_processed_slot(int State)
{
  if (State==Qt::Checked) XRD_show_graph_obs_processed=true;
  else{
    if (XRD_show_graph_obs_raw==true || XRD_show_graph_obs_processed_shifted==true || XRD_show_graph_pdb==true || XRD_show_graph_sqrt==true) XRD_show_graph_obs_processed=false;
    else{
      Checkbox_xrd_show_obs_graph->blockSignals(true);
      Checkbox_xrd_show_obs_graph->setCheckState(Qt::Checked);
      Checkbox_xrd_show_obs_graph->blockSignals(false);
    }
  }

  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_show_graph_obs_processed_shifted_slot(int State)
{
  if (State==Qt::Checked) XRD_show_graph_obs_processed_shifted=true;
  else{
    if (XRD_show_graph_obs_raw==true || XRD_show_graph_obs_processed==true ||  XRD_show_graph_pdb==true || XRD_show_graph_sqrt==true) XRD_show_graph_obs_processed_shifted=false;
    else{
      Checkbox_xrd_show_obs_shifted_graph->blockSignals(true);
      Checkbox_xrd_show_obs_shifted_graph->setCheckState(Qt::Checked);
      Checkbox_xrd_show_obs_shifted_graph->blockSignals(false);
    }
  }

  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_show_graph_pdb_slot(int State)
{
  if (State==Qt::Checked) XRD_show_graph_pdb=true;
  else{
    if (XRD_show_graph_obs_raw==true || XRD_show_graph_obs_processed==true || XRD_show_graph_obs_processed_shifted==true || XRD_show_graph_sqrt==true) XRD_show_graph_pdb=false;
    else{
      Checkbox_xrd_show_pdb_graph->blockSignals(true);
      Checkbox_xrd_show_pdb_graph->setCheckState(Qt::Checked);
      Checkbox_xrd_show_pdb_graph->blockSignals(false);
    }
  }

  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_show_graph_sqrt_slot(int State)
{
  if (State==Qt::Checked) XRD_show_graph_sqrt=true;
  else{
    if (XRD_show_graph_obs_raw==true || XRD_show_graph_obs_processed==true || XRD_show_graph_obs_processed_shifted==true || XRD_show_graph_pdb==true) XRD_show_graph_sqrt=false;
    else{
      Checkbox_xrd_show_sqrt_graph->blockSignals(true);
      Checkbox_xrd_show_sqrt_graph->setCheckState(Qt::Checked);
      Checkbox_xrd_show_sqrt_graph->blockSignals(false);
    }
  }

  xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}
#endif

std::vector<std::string> _window_interpreter::split(const std::string& s, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

//HEA

void _window_interpreter::xrd_change_button_state(int Position)
{
  Vec_xrd_selected_position[Selected_file_position]=Position;

  Mat_xrd_obs_vs_pdb_data_selected[Selected_file_position][Position].Hand_selection=true;
  Mat_xrd_obs_vs_pdb_data_selected[Selected_file_position][Position].Selected=!Mat_xrd_obs_vs_pdb_data_selected[Selected_file_position][Position].Selected;

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Position);
  else
    xrd_create_pdb_sqrt_correlation_chart(Selected_file_position,Position);
}

//HEA

void _window_interpreter::xrd_select_position(int Position)
{
  Vec_xrd_selected_position[Selected_file_position]=Position;

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Position);
  else
    xrd_create_pdb_sqrt_correlation_chart(Selected_file_position,Position);
}

//HEA

void _window_interpreter::xrd_chart_scale_slot(bool State)
{
  Q_UNUSED(State)

  if (Radiobutton_xrd_chart_scale_linear->isChecked()){
    XRD_chart_scale=_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR;
  }
  else{
    XRD_chart_scale=_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LOGARITHMIC;
  }

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
  else
    xrd_create_pdb_sqrt_correlation_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::xrd_pigments_obs_row_changed_slot(int Row)
{
  if (Row>=0){
    Selected_file_position=Row;

    xrd_assign_data_to_table();

    if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
      xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);
    else
      xrd_create_pdb_sqrt_correlation_chart(Selected_file_position, Vec_xrd_selected_position[Selected_file_position]);

    // now XRF update
    if (XRF_obs_data_loaded==true){
      Listwidget_data_xrf_obs->blockSignals(true);
      Listwidget_data_xrf_obs->setCurrentRow(Selected_file_position);
      Listwidget_data_xrf_obs->blockSignals(false);

      xrf_create_spectral_chart(Selected_file_position);
      Table_data_xrf->update_table(Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb, Vec_superposition);
    }
  }
}

//HEA

void _window_interpreter::xrd_order_obs_data(_table_xrd_a_ns::_column_type Column_type)
{
  switch(Column_type){
    case _table_xrd_a_ns::_column_type::COLUMN_TYPE_CORRELATION: // correlation
    XRD_data_order_correlation_increase=!XRD_data_order_correlation_increase;
    if (XRD_data_order_correlation_increase){
      for (unsigned int Row=0;Row<Mat_xrd_obs_vs_pdb_data.size();Row++){
        std::sort(Vec_xrd_obs_data[Row].Vec_order.begin(), Vec_xrd_obs_data[Row].Vec_order.end(), order_by_percentage_up);
      }
    }
    else{
      for (unsigned int Row=0;Row<Mat_xrd_obs_vs_pdb_data.size();Row++){
        std::sort(Vec_xrd_obs_data[Row].Vec_order.begin(), Vec_xrd_obs_data[Row].Vec_order.end(), order_by_percentage_down);
      }
    }
    break;
  case _table_xrd_a_ns::_column_type::COLUMN_TYPE_PIGMENT: // pigment
    XRD_data_order_pigment_name_increase=!XRD_data_order_pigment_name_increase;
    if (XRD_data_order_pigment_name_increase){
      for (unsigned int Row=0;Row<Mat_xrd_obs_vs_pdb_data.size();Row++){
        std::sort(Vec_xrd_obs_data[Row].Vec_order.begin(), Vec_xrd_obs_data[Row].Vec_order.end(), order_by_name_up);
      }
    }
    else{
      for (unsigned int Row=0;Row<Mat_xrd_obs_vs_pdb_data.size();Row++){
        std::sort(Vec_xrd_obs_data[Row].Vec_order.begin(), Vec_xrd_obs_data[Row].Vec_order.end(), order_by_name_down);
      }
    }
    break;
  default:break;
  }

  xrd_assign_data_to_table();

  if (XRD_chart_type==_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL)
    xrd_create_pdb_obs_sqrt_spectral_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
  else
    xrd_create_pdb_sqrt_correlation_chart(Selected_file_position,Vec_xrd_selected_position[Selected_file_position]);
}

//HEA

void _window_interpreter::pdb_parameters(_data_xrd_ns::_pdb_type PDB_type1, _data_xrd_ns::_tube_type PDB_tube_type1, bool PDB_normalized1, QString PDB_name1, QString PDB_formula1, QString PDB_xrf_elements1, QString PDB_rgb_color1)
{
  PDB_type=PDB_type1;
  PDB_tube_type=PDB_tube_type1;
  PDB_normalized=PDB_normalized1;
  PDB_name=PDB_name1;
  PDB_formula=PDB_formula1;
  PDB_xrf_elements=PDB_xrf_elements1;
  PDB_rgb_color=PDB_rgb_color1;

  //
  PDB_name.replace(' ','_');
  PDB_formula.replace(' ','_');

  // check the elements  ????
}

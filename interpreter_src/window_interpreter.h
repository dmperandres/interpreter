//LIC

#ifndef WINDOW_INTERPRETER_H
#define WINDOW_INTERPRETER_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QRect>
#include <QApplication>
#include <QScreen>
#include <QWizardPage>
#include <QSettings>
#include <QDateTime>
#include <QLineEdit>
#include <QDir>
#include <QLabel>
#include <QGroupBox>
#include <QFileDialog>
#include <QSpinBox>
#include <QTabWidget>
#include <QRadioButton>

#include <random>
#include <chrono>

#include <opencv2/core.hpp>

#include <vector>
#include <string>
#include <map>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QPieLegendMarker>

#include "w_tab_interpreter.h"
#include "w_xrd_pdb_data.h"

#include "splitter.h"
#include "splitter_handle.h"

#include "atomic_data.h"

#include "file_xrf_artax.h"
#include "file_xrf_xy.h"

#ifdef XRD_ACTIVE
#include "file_xrd_pdb_csv.h"
//#include "file_xrd_pdb_astm_csv.h"
#include "file_xrd_obs_uxd.h"
#include "file_xrd_obs_plv.h"
#include "file_xrd_obs_txt.h"

#include "w_xrd_pdb_options.h"
#endif

#include "file_elements_csv.h"
#include "file_info_txt.h"
#include "file_positions_txt.h"

#include "data_io.h"

#include "sg_filter.h"

#include "table_xrf.h"
#include "table_xrd_a.h"

#include "common.h"

#include "qcustomplot.h"

#include "w_options_interpreter.h"

#include "common_interpreter.h"
#include "common_qcustomplot.h"

#include "project_data.h"

#include "w_directory.h"

#include "button_color_simple.h"

#include "gaussians_adjustment.h"

//QT_CHARTS_USE_NAMESPACE

namespace _window_interpreter_ns {
  const QString Program_name="Interpreter";
  const QString Program_version="v1.0.0";
  const QDateTime Program_date_time=QDateTime::currentDateTime();
  const QString Program_date=Program_date_time.toString("dd.MM.yy");

  const QString Help_string=Program_name+" "+Program_version+" "+Program_date+"\n\nCreated by Domingo Martín (dmartin@ugr.es)\n\nThis program is part of a research project.\nAll the information is at: https://xmapslab.org\n\n";

  const float SCREEN_WIDTH_FACTOR=0.5f;
  const float SCREEN_HEIGHT_FACTOR=0.5f;

  enum class _chart_mode:unsigned char {CHART_MODE_BAR,CHART_MODE_LINE,CHART_MODE_PIE};

  const _chart_mode CHART_MODE_DEFAULT=_chart_mode::CHART_MODE_BAR;

  const int ICON_SIZE_1080=75;

//  enum class  _working_mode: unsigned char{WORKING_MODE_EDIT,WORKING_MODE_GETSAMPLES,WORKING_MODE_DISTILER};

  enum class _color_model:unsigned char {COLOR_MODEL_RGB,COLOR_MODEL_HSV,COLOR_MODEL_LAB,COLOR_MODEL_LUV};

//  enum class _update_positions:unsigned char {UPDATE_POSITIONS_IMAGE_TO_TABLE,UPDATE_POSITIONS_TABLE_TO_IMAGE};

//  const std::vector<QString> Vec_names_color_model={"RGB","HSV","LAB","LUB"};

  const int WIDTH_TAB_CHARS=20;

  const QString FOLDER_PDB="./pdb";
  const QString FILE_ELEMENTS="elements_xrf.csv";

  // for xrf slider
  const QString String_groupbox_threshold_xrf("Threshold_xrf");
  const QString String_label_threshold_xrf_min_value("Min");
  const QString String_label_threshold_xrf_max_value("Max");
  const int Slider_threshold_xrf_min_value=0;
  const int Slider_threshold_xrf_max_value=250;
  const int Slider_threshold_xrf_single_step=1;
  const int Slider_threshold_xrf_page_step=10;
  const int Slider_threshold_xrf_tick_interval=5;
  const QString String_slider_threshold_xrf_tooltip("Threshold_xrd for removing elements");
  const float Slider_threshold_factor_xrf=250.0f;

  // positions
  enum class _update_mode: unsigned char {UPDATE_MODE_ADD,UPDATE_MODE_REPLACE,UPDATE_MODE_REMOVE,UPDATE_MODE_NOTHING};

  enum class _action_type:unsigned char{ACTION_ADD_ELEMENT,ACTION_REMOVE_ELEMENT,ACTION_NONE,ACTION_LAST};

  const QString Project_name="./project_name.ini";
  //
  const int XRF_TAB_WIDTH=350;
  const int XRD_TAB_WIDTH=350;

  // for ordering
  enum class _order_mode:unsigned char {ORDER_MODE_INCREASE,ORDER_MODE_DECREASE};

  // options
  const int XRF_GRAPH_LINE_WIDTH=2;
  const int XRD_GRAPH_LINE_WIDTH=2;

  const std::vector<QColor> VEC_COLORS={ \
      QColor(255,0,0),
      QColor(0,255,0),
      QColor(0,0,255),
      QColor(0,255,255),
      QColor(255,0,255),
      QColor(255,165,0), // orange
      QColor(255,128,255), // pink
      QColor(0,255,128), // green lime
      QColor(0,128,255), // blue sky
      QColor(128,0,128), // morado
      QColor(255,215,0), // gold
      QColor(192,192,192), // silver
      QColor(0,128,0), // green grass
      QColor(128,128,128), // gray
      QColor(0,192,255) // clear blue
  };
}

  class _window_main;

class _window_interpreter : public QMainWindow
{
    Q_OBJECT

public:
  _window_main *Window_main=nullptr;

  int Initial_width;
  int Initial_height;

  int Selected_layer=-1;
  int Selected_tab=0;
  int Selected_palette=0;
  int Selected_xrf_position=0;

  bool Statistics=false;
  int Statistics_x=-1;
  int Statistics_y=-1;

  // bug
  int Num_days;

  _window_interpreter(_window_main* Window_main1);
  ~_window_interpreter();

//  int ui_font_size(){return UI_font_size;}
//  void ui_font_size(int Size);
//  void pass_ui_font_size(int UI_font_size1);

  void read_settings();
  void save_settings();

  int screen_height(){return Screen_height;}

  // Interpreter
  void xrf_select_elements_using_threshold(_data_xrf_ns::_data_xrf_obs &Data_xrf_obs, float Threshold1);

//  void xrf_create_spectral_chart(float Step, std::vector<float> &Values,vector<float> &Values_gaussians);

  void xrf_create_spectral_chart(int Selected_file_position);

  void xrf_convolution(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrf_ns::_data_xrf_obs &Data_xrf_obs1,unsigned int Half_shift);


#ifdef XRD_ACTIVE
  void xrd_create_pdb_obs_sqrt_spectral_chart(int Selected_row_in_table,int Selected_col_in_mat);
  void xrd_create_obs_spectral_chart(int Selected_row_in_table);
  void xrd_create_pdb_sqrt_correlation_chart(int Selected_row_in_table,int Selected_col_in_mat);

  void xrd_update_info_and_chart_of_selected_table_cell();

//  void remove_noise_xrd_pdb(std::vector<float> &Raw_data, std::vector<float> &Normalized_data,unsigned int Num_steps_smooth,unsigned int Num_steps_subtract_mean);

  float xrd_maximum_threshold_correlation(){return XRD_correlation_good_threshold;}
  float xrd_medium_threshold_correlation(){return XRD_correlation_medium_threshold;}
  float xrd_bad_threshold_correlation(){return XRD_correlation_bad_threshold;}

//  float max_threshold_xrd_correlation(){return XRD_correlation_good_threshold;}
//  float medium_threshold_xrd_correlation(){return XRD_correlation_medium_threshold;}

  void compute_data_xrd_obs_pdb(int OBS_pos, int PDB_pos);

  void xrd_convolution(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrd_ns::_data_xrd_obs_pdb &Result_linear_regresion1, unsigned int Half_shift);
  void linear_regression(std::vector<float>::iterator Iter_vec_x, std::vector<float>::iterator Iter_vec_y,int Num_iter, _data_xrd_ns::_data_xrd_obs_pdb &Result_linear_regresion1);

  void linear_regression(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrd_ns::_data_xrd_obs_pdb &Result_linear_regresion1);

  void linear_regression1(std::vector<float> Vec_x, std::vector<float> Vec_y, _data_xrd_ns::_data_xrd_obs_pdb &Result_linear_regresion1);

//  void xrd_selected_row_in_table(int Selected_row_xrd1){XRD_selected_row_in_table=Selected_row_xrd1;}
//  int xrd_selected_row_in_table(){return XRD_selected_row_in_table;}

//  void xrd_selected_col_in_table(int Selected_col_xrd1);
//  int selected_col_in_table(){return XRD_selected_col_in_table;}

  std::vector<float> xrd_tube_conversion(_data_xrd_ns::_tube_conversion_mode Tube_conversion_mode, std::vector<float> Values);

  bool xrd_data_to_show(){return XRD_data_to_show;}

//  void use_xrd_pdb_spectral_Cu(bool Use_xrd_pdb_spectral_Cu1){XRD_use_pdb_spectral_Cu=Use_xrd_pdb_spectral_Cu1;}
//  bool use_xrd_pdb_spectral_Cu(){return XRD_use_pdb_spectral_Cu;}

//  void use_xrd_pdb_spectral_Co(bool Use_xrd_pdb_spectral_Co1){XRD_use_pdb_spectral_Co=Use_xrd_pdb_spectral_Co1;}
//  bool use_xrd_pdb_spectral_Co(){return XRD_use_pdb_spectral_Co;}

//  void use_xrd_pdb_astm_Cu(bool Use_xrd_pdb_astm_Cu1){XRD_use_pdb_astm_Cu=Use_xrd_pdb_astm_Cu1;}
//  bool use_xrd_pdb_astm_Cu(){return XRD_use_pdb_astm_Cu;}

  void xrd_selected_pdb_folders(std::vector<std::string> Vec_xrd_selected_pdb_folders1){Vec_xrd_selected_pdb_folders=Vec_xrd_selected_pdb_folders1;}

//  void tube_type(_data_xrd_ns::_tube_type Tube_type1){XRD_tube_type=Tube_type1;}
  _data_xrd_ns::_tube_type tube_type(){return Project_data.XRD_tube_type;}

  void mat_obs_vs_pdb_flip_selected_state(int Row,int Col){
    Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Hand_selection=true;
    Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected=!Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected;
  }

  bool mat_obs_vs_pdb_data_selected(int Row,int Col){return Mat_xrd_obs_vs_pdb_data_selected[Row][Col].Selected;}

  _data_xrd_ns::_valid_type mat_obs_vs_pdb_valid_type(int Row,int Col){return Mat_xrd_obs_vs_pdb_data[Row][Col].Valid_type;}
  float mat_obs_vs_pdb_correlation_coefficient(int Row,int Col){return Mat_xrd_obs_vs_pdb_data[Row][Col].Correlation_coefficient_squared;}
  int mat_obs_vs_pdb_num_elements_not_found(int Row,int Col){return Mat_xrd_obs_vs_pdb_data[Row][Col].Vec_elements_not_found.size();}
  bool mat_obs_vs_pdb_xrf_used(int Row,int Col){return Mat_xrd_obs_vs_pdb_data[Row][Col].XRF_used;}

//  int xrd_get_true_col(int Col){
//    if (Col<int(Vec_xrd_visible_columns_in_table.size())) return Vec_xrd_visible_columns_in_table[Col];
//    else return(-1);
//  }

//  int num_visible_columns_in_table(){return Vec_xrd_visible_columns_in_table.size();}


#endif

  void smooth_data_mean(int Num_passes,std::vector<float> &Vec_value_in,std::vector<float> &Vec_value_out);
  void smooth_data_gs(int Num_passes,std::vector<float> &Vec_value_in,std::vector<float> &Vec_value_out);

  void remove_background(int Num_passes,std::vector<float> &Vec_value_in,std::vector<float> &Vec_value_out);

  void xrf_process_data();

  void xrd_compute_sqrt_values(std::vector<float> &Values1,std::vector<float> &Values2,std::vector<float> &Values3);
  void save_values(std::string File_name, std::vector<std::string> &Names, std::vector<std::vector<float> > &Values);

  void xrf_order_obs_data(_table_xrf_ns::_column_type Column_type);
  void xrf_order_obs_data_for_all_files(int Col, _window_interpreter_ns::_order_mode Order_mode);

  void xrf_change_button_state(int Element);

  int search_near_element_in_data(float X_coord,float Y_coord,float Window);
  int search_near_element_in_pdb(float Pos_ka);
  int search_near_element_in_found(int Pos_ka,int Window,float Step);
  void xrf_add_element_action();
  void xrf_remove_element_action(int Element_position);

  // for checking if there is a open project
  bool check_project();

  // colors
  QColor xrf_color_obs_raw(){return XRF_color_obs_raw;}
  QColor xrf_color_obs_processed(){return XRF_color_obs_processed;}
  QColor xrf_color_obs_processed_shifted(){return XRF_color_obs_processed_shifted;}
  QColor xrf_color_gaussians(){return XRF_color_gaussians;}


  void options_parameters(QColor XRD_color_file_not_exists1, QColor XRD_color_element_not_exists1, QColor XRD_color_valid_good1, QColor Color_valid_medium1,QColor Color_valid_bad1,QColor Color_font1);

  void project_dir(QString Project_dir1){Project_dir=Project_dir1;}
  void load_project_data();

//  bool xrd_show_valid(){return XRD_show_valid;}
//  bool xrd_show_element_not_exists(){return XRD_show_element_not_exists;}
//  bool xrd_show_file_not_exists(){return XRD_show_file_not_exists;}

//  bool xrd_show_valid_good(){return XRD_show_valid_good;}
//  bool xrd_show_valid_medium(){return XRD_show_valid_medium;}
//  bool xrd_show_valid_bad(){return XRD_show_valid_bad;}

  _data_xrd_ns::_class_type mat_xrd_obs_vs_pdb_data_class_type(int Row,int Col){return Mat_xrd_obs_vs_pdb_data[Row][Col].Class_type;}
  _data_xrd_ns::_valid_type mat_xrd_obs_vs_pdb_data_valid_type(int Row,int Col){return Mat_xrd_obs_vs_pdb_data[Row][Col].Valid_type;}
  bool mat_xrd_obs_vs_pdb_data_show(int Row,int Col){return Mat_xrd_obs_vs_pdb_data[Row][Col].Show;}

  // options
  //XRF
  void interpreter_xrf_title_font_size(int XRF_title_font_size1){XRF_title_font_size=XRF_title_font_size1;}
  int interpreter_xrf_title_font_size(){return XRF_title_font_size;}
  void interpreter_xrf_legend_font_size(int XRF_legend_font_size1){XRF_legend_font_size=XRF_legend_font_size1;}
  int interpreter_xrf_legend_font_size(){return XRF_legend_font_size;}
  void interpreter_xrf_graph_line_widht(int XRF_graph_line_width1){XRF_graph_line_width=XRF_graph_line_width1;}
  int interpreter_xrf_graph_line_widht(){return XRF_graph_line_width;}

  void options_parameters_xrf(int XRF_title_font_size1,int XRF_legend_font_size1,int XRF_graph_line_width1);

  //XRD
  void interpreter_xrd_title_font_size(int XRD_title_font_size1){XRD_title_font_size=XRD_title_font_size1;}
  int interpreter_xrd_title_font_size(){return XRD_title_font_size;}
  void interpreter_xrd_legend_font_size(int XRD_legend_font_size1){XRD_legend_font_size=XRD_legend_font_size1;}
  int interpreter_xrd_legend_font_size(){return XRD_legend_font_size;}
  void interpreter_xrd_graph_line_widht(int XRD_graph_line_width1){XRD_graph_line_width=XRD_graph_line_width1;}
  int interpreter_xrd_graph_line_widht(){return XRD_graph_line_width;}

  void options_parameters_xrd(int XRD_title_font_size1,int XRD_legend_font_size1,int XRD_graph_line_width1);

  void xrd_change_button_state(int Position);
  void xrd_select_position(int Position);

  //
  int selected_xrf_file(){return Selected_file_position;}

  // colors
  QColor xrd_color_obs_raw(){return XRD_color_obs_raw;}
  QColor xrd_color_obs_processed(){return XRD_color_obs_processed;}
  QColor xrd_color_obs_processed_shifted(){return XRD_color_obs_processed_shifted;}
  QColor xrd_color_pdb(){return XRD_color_pdb;}
  QColor xrd_color_sqrt(){return XRD_color_sqrt;}

  //
  bool least_squares(std::vector<float> Vec_x, std::vector<float> Vec_y, float &a, float &b);

  //
  void xrd_order_obs_data(_table_xrd_a_ns::_column_type Column_type);

  //
  void pdb_parameters(_data_xrd_ns::_pdb_type PDB_type1, _data_xrd_ns::_tube_type PDB_tube_type1, bool PDB_normalized1, QString PDB_name1, QString PDB_formula1, QString PDB_xrf_elements1, QString PDB_rgb_color1);

public slots:
  void load_project_data_slot();
  void save_project_data_slot();

  void load_user_selections_slot();
//  void save_user_selections_slot();

  void save_one_graph_slot();
  void save_all_graphs_slot();

  void xrf_save_process_info_csv_slot();

//  void program_positions_slot();
//  void program_maplab_slot();
#ifndef UNIFIED
  void info_slot();
#endif

  // xrf
  void xrf_elements_obs_row_changed_slot(int Row);
  bool xrf_selected(int Element){return Vec_xrf_obs_data[Selected_file_position].Vec_elements_ka_kb[Element].Selected;}
  void chart_bar_xrf_double_click_slot(QMouseEvent* Event);
  void chart_bar_xrf_before_replot_slot();

  void chart_bar_xrf_mouse_press_slot(QMouseEvent* Event);
  void chart_bar_xrf_mouse_move_slot(QMouseEvent* Event);
  void chart_bar_xrf_mouse_release_slot(QMouseEvent* Event);


  void xrf_x_axis_changed_slot(QCPRange Range);
  void xrf_y_axis_changed_slot(QCPRange Range);

  void xrf_threshold_slot(int Value);

  void xrf_add_element_tool_slot(bool Checked);
  void xrf_delete_element_tool_slot(bool Checked);

  void xrf_chart_scale_slot(bool);

  void xrf_threshold_percentage_slot(int Value);

  void xrf_show_obs_graph_slot(int State);
  void xrf_show_processed_graph_slot(int State);
  void xrf_show_processed_shifted_graph_slot(int State);
  void xrf_show_gaussians_graph_slot(int State);

//  void xrf_smooth_type_mean_slot(bool State);
//  void xrf_smooth_type_gs_slot(bool State);

  // Num steps
  void xrf_update_parameters();
  void xrf_process_change();
  void num_steps_smooth_xrf_slot(int Value);
  void num_steps_subtract_mean_xrf_slot(int Value);
  void num_steps_search_window_xrf_slot(int Value);

  void xrf_color_obs_raw_slot(QColor Color);
  void xrf_color_obs_processed_slot(QColor Color);
  void xrf_color_obs_processed_shifted_slot(QColor Color);
  void xrf_color_gaussians_slot(QColor Color);

  // xrd
#ifdef XRD_ACTIVE

#ifdef XLSX_ACTIVE
  void xrd_save_correlation_data_xlsx_slot();
  void xrd_save_process_info_xlsx_slot();
#else
  void xrd_save_correlation_data_csv_slot();
  void xrd_save_process_info_csv_slot();
#endif

//  void left_handle_slot();
//  void right_handle_slot();

  void xrd_num_steps_smooth_slot(int Value);
  void xrd_num_steps_subtract_background_slot(int Value);
  void xrd_num_steps_shift_slot(int Value);

  void xrd_pigments_obs_row_changed_slot(int Row);

//  void recompute_values_xrd_slot();
//  void xrd_recompute_all_values_slot();

  void xrd_good_threshold_slot(int Value);
  void xrd_medium_threshold_slot(int Value);
  void xrd_bad_threshold_slot(int Value);

  void xrd_level_subtract_slot(double Value);
//  void num_removed_peaks_xrd_slot(int Value);

  void chart_bar_xrd_double_click_slot(QMouseEvent *Event);
  void chart_bar_xrd_mouse_wheel_slot(QWheelEvent *Event);
  void chart_bar_xrd_mouse_press_slot(QMouseEvent* Event);
  void chart_bar_xrd_mouse_move_slot(QMouseEvent* Event);
  void chart_bar_xrd_mouse_release_slot(QMouseEvent* Event);

  void xrd_x_axis_changed_slot(QCPRange Range);
  void xrd_y_axis_changed_slot(QCPRange Range);

  // colors
  void xrd_color_obs_raw_slot(QColor Color);
  void xrd_color_obs_processed_slot(QColor Color);
  void xrd_color_obs_processed_shifted_slot(QColor Color);
  void xrd_color_pdb_slot(QColor Color);
  void xrd_color_sqrt_slot(QColor Color);

  //
  void xrd_color_file_not_exists_slot(QColor Color);
  QColor xrd_color_file_not_exists(){return XRD_color_file_not_exists;}

  void xrd_color_element_not_exists_slot(QColor Color);
  QColor xrd_color_element_not_exists(){return XRD_color_element_not_exists;}

  void xrd_color_valid_good_slot(QColor Color);
  QColor xrd_color_valid_good(){return XRD_color_valid_good;}

  void xrd_color_valid_medium_slot(QColor Color);  
  QColor xrd_color_valid_medium(){return XRD_color_valid_medium;}

  void xrd_color_valid_bad_slot(QColor Color);
  QColor xrd_color_valid_bad(){return XRD_color_valid_bad;}

//  QColor color_font(){return Color_font;}
//  void xrd_color_font_slot(QColor Color);

  // main
//  void xrd_show_valid_good_slot(int State);
//  void xrd_show_valid_medium_slot(int State);
//  void xrd_show_valid_bad_slot(int State);
//  void xrd_show_main_valid_slot(int State);
//  void xrd_show_main_element_not_exists_slot(int State);
//  void xrd_show_main_file_not_exists_slot(int State);


  void xrd_chart_type_slot(bool State);

//  void xrd_smooth_type_mean_slot(bool State);
//  void xrd_smooth_type_gs_slot(bool State);

  void xrd_normalization_type_mean_slot(bool State);
  void xrd_normalization_type_percentage_slot(bool State);

  void xrd_computation_type_sqrt_slot(bool State);
  void xrd_computation_type_not_zero_slot(bool State);

  void xrd_show_graph_raw_obs_slot(int State);
  void xrd_show_graph_obs_processed_slot(int State);
  void xrd_show_graph_obs_processed_shifted_slot(int State);
  void xrd_show_graph_pdb_slot(int State);
  void xrd_show_graph_sqrt_slot(int State);

  // options
  void xrd_pdb_options_slot();

  void xrd_chart_scale_slot(bool);

  //
  void split_screen_slot();

//  void xrd_gaussian_parameters_width_slot(int XRD_gaussian_parameters_width1){XRD_gaussian_parameters_width=XRD_gaussian_parameters_width1;}
//  void xrd_gaussian_parameters_sd_slot(int XRD_gaussian_parameters_sd1){XRD_gaussian_parameters_sd=XRD_gaussian_parameters_sd1;}

#endif

  std::vector<float> xrd_create_spectral_from_peaks(std::vector<float> &Vec_2theta, std::vector<float> &Vec_intensity);

  // options
  void options_slot();
  void pdb_mode_slot();
  void save_pdb_slot();


  //
  void tab_changed_slot(int Index);
  //
  void adjust_splitter();

protected:
//  void closeEvent(QCloseEvent *Event) override;

//  void load_data();

  // XRF
//  void load_elements();

  void xrf_search_bottom_left(int Start, int& Pos, std::vector<float>& Values, std::vector<bool> &Valids);
  void xrf_search_bottom_right(int Start, int& Pos, std::vector<float>& Values, std::vector<bool> &Valids);

  void xrf_search_top(int& Start, int& Pos, std::vector<float> &Values);


  std::vector<float> xrf_search_maximums(std::vector<float> Values);

  int search_ka(int Start_position, std::vector<_data_xrf_ns::_result> &Vec_results);
  _common_ns::_value_position search_kb(int Start_position, std::vector<_data_xrf_ns::_result> &Vec_results);

  std::vector<_data_xrf_ns::_data_xrf_ka_kb> xrf_search_elements(int Index, std::vector<_data_xrf_ns::_data_maximum> &Maximums, int Window);
  std::vector<_data_xrf_ns::_data_xrf_ka_kb> search_elements1(int Index, std::vector<_data_xrf_ns::_data_maximum> &Maximums, int Window);


  std::vector<float> xrf_search_maximums(std::vector<float> Values1,int Window);
  std::vector<_data_xrf_ns::_data_maximum> xrf_search_maximums_in_obs(std::vector<float> Values, std::vector<float> Maximums, int Window);

  void xrf_update_using_manual_selection();
  void xrf_preprocess_obs_data();
  void xrf_process_obs_data();

  std::vector<float> xrf_create_gaussian(int Num_steps,float Sigma);
  void xrf_create_gaussians(_data_xrf_ns::_data_xrf_obs &Data_xrf_obs);

  std::vector<float> xrf_create_tube_gaussian(int Size1, float Max_value, float Step);
  std::vector<float> xrf_shift_obs_data(std::vector<float> &Vec_values, float Step);

  // new
//  bool search_element_in_maximums(std::vector<_data_xrf_ns::_data_maximum> &Vec_maximums, int Window, int Pos_ka, int Pos_kb, _data_xrf_ns::_data_k& Data_ka,_data_xrf_ns::_data_k& Data_kb);
//  int search_element(std::string Element_name, map<std::string, _data_xrf_ns::_data_xrf_selected> &Map_selected);

  void xrf_remove_element_from_peaks(std::string Element_name,int Pos_peak,std::vector<_data_xrf_ns::_data_maximum>& Vec_maximums);


  void xrf_remove_element(std::string Element_name,std::map<std::string, _data_xrf_ns::_data_xrf_selected> &Map_selected, std::vector<_data_xrf_ns::_data_maximum> &Vec_maximums);

  void xrf_add_element_to_result(std::string Element_name, float Step, std::map<std::string,_data_xrf_ns::_data_xrf_selected>& Map_selected, std::vector<_data_xrf_ns::_data_maximum>& Vec_maximums, std::vector<_data_xrf_ns::_data_xrf_ka_kb>& Vec_results_ka_kb, std::vector<std::pair<int,int>>& Vec_maximums_aux);

  // XRD
#ifdef XRD_ACTIVE
  void check_xrf_xrd_file_numbers_match();

  void load_pigments();

  // process
  void xrd_assign_data_to_table();
  void xrd_preprocess_data(std::vector<float> &Raw_data, std::vector<float> &Smooth_data, std::vector<float> &Filtered_data, std::vector<float> &Normalized_data, unsigned int Num_steps_smooth, unsigned int Num_steps_subtract_mean);
  void xrd_preprocess_pdb_data();
  void xrd_preprocess_obs_data();
  void xrd_process_pdb_data();
  void xrd_process_obs_vs_pdb_data();
  void xrd_classify_cells_class_mat_obs_vs_pdb();
  void xrd_classify_cells_threshold_mat_obs_vs_pdb();
  void xrd_apply_manual_selection_to_mat_obs_vs_pdb();
  void xrd_process_data();

  void xrd_compute_ranges();

  bool xrd_load_obs_data();
//  std::vector<_window_interpreter_ns::_pigment_data_obs> load_data_xrd_ka_txt();
//  void load_data_xrd_txt();
  float compute_xrd_area(int Row,int Col);

  void xrd_update_info(bool Valid);
  void xrd_update_parameters();
  void xrd_update();

//  void xrd_compute_visible_columns_in_table(std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb> > &Mat_xrd_obs_vs_pdb_data);

  bool check_xrd_uxd_files_exist();
  bool check_xrd_plv_files_exist();
  void xrd_load_data();
  bool XRD_uxd_files_exist=false;
  bool XRD_plv_files_exist=false;

  void xrd_load_pdb_astm(std::string Folder_name);

  std::vector<float> shift_vector(std::vector<float> &Vec_data,int Shift);
#endif

  void create_widgets();

  // XRF
  bool xrf_load_obs_data();

  //
  void xrf_set_threshold(int Value);

  //
  bool check_xrf_files_exist();
  bool check_xy_files_exist();

  void xrf_load_data();

  QWizardPage* createIntroPage();

  bool XRF_artax_files_exist=false;
  bool XRF_xy_files_exist=false;

  std::vector<std::string> split(const std::string& s, char delimiter);
  //
  int Screen_width=0;
  int Screen_height=0;

  //
  int UI_font_size=_common_ns::UI_FONT_SIZE_DEFAULT;


  QMenu *Menu_view=nullptr;

  QAction *Load_project=nullptr;
  QAction *Save_project=nullptr;

//  QAction *Load_user_selections=nullptr;
  QAction *Save_user_selections=nullptr;

  QAction *Save_one_graph=nullptr;
  QAction *Save_all_graphs=nullptr;

//  QAction *QAction_xrf_save_process_info_csv=nullptr;

  QAction *Options=nullptr;

  QAction *Action_pdb_mode=nullptr;
  QAction *Action_save_pdb=nullptr;

  _splitter *Splitter_xrf_xrd=nullptr;

#ifdef XRD_ACTIVE

#ifdef XLSX_ACTIVE
  QAction *QAction_xrd_save_correlation_data_xlsx=nullptr;
  QAction *QAction_xrd_save_process_info_xlsx=nullptr;
#else
  QAction *QAction_xrd_save_correlation_data_csv=nullptr;
  QAction *QAction_xrd_save_process_info_csv=nullptr;
#endif

//  _splitter *Splitter_xrd=nullptr;
//  QSplitter *Splitter_xrd_chart_table=nullptr;

  QAction *View_split_screen=nullptr;


  QGroupBox *Groupbox_xrd_main=nullptr;

  QGroupBox *Groupbox_xrd_show_main=nullptr;
//  QFrame *Frame_xrd_show_main=nullptr;
  bool XRD_data_to_show=true;
#endif

  _w_tab_interpreter *Tab_widget_interpreter=nullptr;

  QGroupBox *Groupbox_interpreter_aux=nullptr;

  bool Left_part_full=true;
  int Left_part_size=-1;

  bool Right_part_full=true;
  int Right_part_size=-1;

  QString Project_dir;
  QString Project_name;

  bool Show_positions=false;

  _window_interpreter_ns::_chart_mode Chart_mode;

  int Selected_view;

  std::vector<QColor> Histogram_colors;

  bool Widgets_created=false;

  // XRF
  std::vector<_data_xrf_ns::_data_xrf_pdb> Vec_xrf_pdb_data;
  std::vector<std::string> Vec_xrf_pdb_names;
  std::vector<_data_xrf_ns::_data_xrf_obs> Vec_xrf_obs_data;

  QChartView *Chart_view_xrf=nullptr;
  QChart *Chart_xrf=nullptr;
  QListWidget *Listwidget_data_xrf_obs=nullptr;
  _table_xrf *Table_data_xrf=nullptr;

  int Selected_file_position=0;
  int XRF_good_file_position=0;
  int XRD_good_file_position=0;

  QCustomPlot *Customplot_xrf=nullptr;

  QSpinBox *Spinbox_threshold_xrf=nullptr;

  _data_xrf_ns::_data_xrf_ka_kb Element_selected;

  QRadioButton *Radiobutton_xrf_chart_scale_linear=nullptr;
  QRadioButton *Radiobutton_xrf_chart_scale_log=nullptr;
  _data_xrf_ns::_xrf_scale_type XRF_chart_scale=_data_xrf_ns::_xrf_scale_type::XRF_SCALE_TYPE_LINEAR;

  QSpinBox* Spinbox_threshold_percentage_xrf=nullptr;

  QSpinBox *Spinbox_xrf_num_steps_smooth=nullptr;
  QSpinBox *Spinbox_xrf_num_steps_subtract_background=nullptr;
  QSpinBox *Spinbox_xrf_num_steps_search_window=nullptr;

  QCheckBox* Checkbox_show_graph_obs_xrf=nullptr;
  QCheckBox* Checkbox_show_graph_processed_xrf=nullptr;
  QCheckBox* Checkbox_show_graph_processed_shifted_xrf=nullptr;
  QCheckBox* Checkbox_show_graph_gaussians_xrf=nullptr;

  QColor XRF_color_obs_raw=_data_xrf_ns::XRF_COLOR_OBS_RAW;
  QColor XRF_color_obs_processed=_data_xrf_ns::XRF_COLOR_OBS_PROCESSED;
  QColor XRF_color_obs_processed_shifted=_data_xrf_ns::XRF_COLOR_OBS_PROCESSED_SHIFTED;
  QColor XRF_color_gaussians=_data_xrf_ns::XRF_COLOR_GAUSSIANS;

//  QRadioButton* Radiobutton_xrf_mean_smooth_type=nullptr;
//  QRadioButton* Radiobutton_xrf_gs_smooth_type=nullptr;

  QColor XRD_color_obs_raw=_data_xrd_ns::XRD_COLOR_OBS_RAW;
  QColor XRD_color_obs_processed=_data_xrd_ns::XRD_COLOR_OBS_PROCESSED;
  QColor XRD_color_obs_processed_shifted=_data_xrd_ns::XRD_COLOR_OBS_PROCESSED_SHIFTED;
  QColor XRD_color_pdb=_data_xrd_ns::XRD_COLOR_PDB;
  QColor XRD_color_sqrt=_data_xrd_ns::XRD_COLOR_SQRT;

  QColor XRD_color_file_not_exists=_data_xrd_ns::XRD_COLOR_FILE_NOT_EXISTS;
  QColor XRD_color_element_not_exists=_data_xrd_ns::XRD_COLOR_ELEMENT_NOT_EXISTS;
  QColor XRD_color_valid_good=_data_xrd_ns::XRD_COLOR_VALID_GOOD;
  QColor XRD_color_valid_medium=_data_xrd_ns::XRD_COLOR_VALID_MEDIUM;
  QColor XRD_color_valid_bad=_data_xrd_ns::XRD_COLOR_VALID_BAD;
//  QColor XRD_color_font=_data_xrd_ns::XRD_COLOR_FONT;

  QListWidget *Listwidget_data_xrd_obs=nullptr;

  // for the ranges of the axis
  std::vector<_common_qcustomplot_ns::_ranges> Vec_xrf_axis_ranges_linear;
  std::vector<_common_qcustomplot_ns::_ranges> Vec_xrf_axis_ranges_log;

  bool XRF_data_order_element_name_increase=true;
  bool XRF_data_order_ka_positions_kev_increase=true;
  bool XRF_data_order_ka_values_increase=true;

//  std::vector<int> Vec_threshold_percentage_xrf;
  int XRF_threshold_percentage=_data_xrf_ns::XRF_THRESHOLD_PERCENTAGE;

  bool XRF_show_graph_obs_values=_data_xrf_ns::XRF_SHOW_GRAPH_OBS;
  bool XRF_show_graph_processed_values=_data_xrf_ns::XRF_SHOW_GRAPH_PROCESSED;
  bool XRF_show_graph_processed_shifted_values=_data_xrf_ns::XRF_SHOW_GRAPH_PROCESSED;
  bool XRF_show_graph_gaussians_values=_data_xrf_ns::XRF_SHOW_GRAPH_GAUSSIANS;

  _data_xrf_ns::_smooth_type XRF_smooth_type=_data_xrf_ns::_smooth_type::SMOOTH_TYPE_GS;

  // colors
  _button_color_simple *Button_color_xrf_obs_raw=nullptr;
  _button_color_simple *Button_color_xrf_obs_processed=nullptr;
  _button_color_simple *Button_color_xrf_obs_processed_shifted=nullptr;
  _button_color_simple *Button_color_xrf_gaussians=nullptr;


  // XRD
  std::vector<std::string> Vec_xrd_pdb_names; // for removing errors

  // XRD
#ifdef XRD_ACTIVE
  std::vector<_data_xrd_ns::_data_xrd_pdb> Vec_xrd_pdb_data;

  std::vector<_data_xrd_ns::_data_xrd_obs> Vec_xrd_obs_data;

  std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb>> Mat_xrd_obs_vs_pdb_data;
  std::vector<std::vector<_data_xrd_ns::_selection>> Mat_xrd_obs_vs_pdb_data_selected;
//  _table_xrd *Table_xrd_obs_vs_pdb_data=nullptr;
  _table_xrd_a *Table_data_xrd=nullptr;

  QCustomPlot *Customplot_xrd=nullptr;
  std::vector<int> Vec_xrd_match_errors;

  QRadioButton *Radiobutton_xrd_chart_type_spectra=nullptr;
  QRadioButton *Radiobutton_xrd_chart_type_correlation=nullptr;


  // colors
  _button_color_simple *Button_color_xrd_obs_raw=nullptr;
  _button_color_simple *Button_color_xrd_obs_processed=nullptr;
  _button_color_simple *Button_color_xrd_obs_processed_shifted=nullptr;
  _button_color_simple *Button_color_xrd_pdb=nullptr;
  _button_color_simple *Button_color_xrd_sqrt=nullptr;

  _button_color_simple *Button_color_xrd_file_not_exists=nullptr;
  _button_color_simple *Button_color_xrd_element_not_exists=nullptr;
  _button_color_simple *Button_color_xrd_valid_good=nullptr;
  _button_color_simple *Button_color_xrd_valid_medium=nullptr;
  _button_color_simple *Button_color_xrd_valid_bad=nullptr;
//  _button_color_simple *Button_color_xrd_font=nullptr;

//  QCheckBox *Checkbox_xrd_show_main_file_not_exists=nullptr;
//  QCheckBox *Checkbox_xrd_show_main_element_not_exists=nullptr;
//  QCheckBox *Checkbox_xrd_show_main_valid=nullptr;

//  QCheckBox *Checkbox_xrd_show_valid_good=nullptr;
//  QCheckBox *Checkbox_xrd_show_valid_medium=nullptr;
//  QCheckBox *Checkbox_xrd_show_valid_bad=nullptr;

  QLineEdit *Lineedit_xrd_file_exists=nullptr;
  QLineEdit *Lineedit_xrd_all_elements_exist=nullptr;
  QLineEdit *Lineedit_xrd_correlation=nullptr;
  QLineEdit *Lineedit_xrd_shift=nullptr;
  QLineEdit *Lineedit_xrd_num_peaks=nullptr;

  QGroupBox *Groupbox_xrd_show_valid=nullptr;
//  QFrame *Frame_xrd_show_valid=nullptr;

  QGroupBox *Groupbox_level_subtract_xrd=nullptr;

//  QRadioButton* Radiobutton_xrd_mean_smooth_type=nullptr;
//  QRadioButton* Radiobutton_xrd_gs_smooth_type=nullptr;

  QRadioButton* Radiobutton_xrd_normalization_type_mean=nullptr;
  QRadioButton* Radiobutton_xrd_normalization_type_percentage=nullptr;

  QRadioButton* Radiobutton_xrd_computation_type_sqrt=nullptr;
  QRadioButton* Radiobutton_xrd_computation_type_not_zero=nullptr;

  QCheckBox* Checkbox_xrd_show_raw_obs_graph=nullptr;
  QCheckBox* Checkbox_xrd_show_obs_graph=nullptr;
  QCheckBox* Checkbox_xrd_show_obs_shifted_graph=nullptr;
  QCheckBox* Checkbox_xrd_show_pdb_graph=nullptr;
  QCheckBox* Checkbox_xrd_show_sqrt_graph=nullptr;

  _data_xrd_ns::_chart_type XRD_chart_type=_data_xrd_ns::_chart_type::CHART_TYPE_SPECTRAL;

  QRadioButton *Radiobutton_xrd_chart_scale_linear=nullptr;
  QRadioButton *Radiobutton_xrd_char_scale_log=nullptr;
  _data_xrd_ns::_xrd_scale_type XRD_chart_scale=_data_xrd_ns::_xrd_scale_type::XRD_SCALE_TYPE_LINEAR;

//  bool XRD_show_file_not_exists=_data_xrd_ns::SHOW_FILE_NOT_EXISTS_DEFAULT;
//  bool XRD_show_element_not_exists=_data_xrd_ns::SHOW_ELEMENT_NOT_EXISTS_DEFAULT;
//  bool XRD_show_valid=_data_xrd_ns::SHOW_VALID_DEFAULT;
//  bool XRD_show_valid_good=_data_xrd_ns::SHOW_VALID_GOOD_DEFAULT;
//  bool XRD_show_valid_medium=_data_xrd_ns::SHOW_VALID_MEDIUM_DEFAULT;
//  bool XRD_show_valid_bad=_data_xrd_ns::SHOW_VALID_BAD_DEFAULT;

  _data_xrd_ns::_smooth_type XRD_smooth_type=_data_xrd_ns::SMOOTH_TYPE;

  _data_xrd_ns::_normalization_type XRD_normalization_type=_data_xrd_ns::NORMALIZATION_TYPE;

  _data_xrd_ns::_computation_type XRD_computation_type=_data_xrd_ns::COMPUTATION_TYPE;
  QLabel *Label_computation_type=nullptr;

  bool XRD_show_graph_obs_raw=_data_xrd_ns::SHOW_GRAPH_RAW_OBS_XRD;
  bool XRD_show_graph_obs_processed=_data_xrd_ns::SHOW_GRAPH_OBS_XRD;
  bool XRD_show_graph_obs_processed_shifted=_data_xrd_ns::SHOW_GRAPH_OBS_SHIFTED_XRD;
  bool XRD_show_graph_pdb=_data_xrd_ns::SHOW_GRAPH_PDB_XRD;
  bool XRD_show_graph_sqrt=_data_xrd_ns::SHOW_GRAPH_SQRT_XRD;

//  std::vector<unsigned int> Vec_xrd_visible_columns_in_table;

  unsigned int XRD_num_steps_smooth=_data_xrd_ns::NUM_STEPS_SMOOTH_XRD;
  unsigned int XRD_num_steps_subtract_background=_data_xrd_ns::XRD_NUM_STEPS_SUBTRACT_BACKGROUND;
  unsigned int XRD_num_steps_shift=_data_xrd_ns::NUM_STEPS_SHIFT_XRD;

  // for the ranges of the axis
  std::vector<_common_qcustomplot_ns::_ranges> Vec_xrd_axis_ranges_linear;
  std::vector<_common_qcustomplot_ns::_ranges> Vec_xrd_axis_ranges_log;
  std::vector<std::vector<_common_qcustomplot_ns::_ranges>> Mat_xrd_spectral_axis_range_linear;
  std::vector<std::vector<_common_qcustomplot_ns::_ranges>> Mat_xrd_spectral_axis_range_log;
  std::vector<std::vector<_common_qcustomplot_ns::_ranges>> Mat_xrd_correlation_axis_range_linear;

  std::vector<int> Vec_xrd_selected_row_in_table={0,0,0};
  std::vector<int> Vec_xrd_selected_col_in_table={-1,-1,-1};
//  int XRD_selected_row_in_table=0;
//  int XRD_selected_col_in_table=-1;
//  int XRD_selected_col_in_mat=0;


  std::vector<std::string> Vec_xrd_row_names;
  std::vector<std::string> Vec_xrd_col_names;

  QSpinBox *Spinbox_xrd_num_steps_smooth=nullptr;
  QSpinBox *Spinbox_xrd_num_steps_subtract_background=nullptr;
  QSpinBox *Spinbox_xrd_num_steps_shift=nullptr;
  QSpinBox *Spinbox_xrd_max_threshold=nullptr;
  QSpinBox *Spinbox_xrd_medium_threshold=nullptr;
  QSpinBox *Spinbox_xrd_bad_threshold=nullptr;

  QDoubleSpinBox *Doublespinbox_xrd_level_subtract=nullptr;
  float XRD_level_subtract=0;



//  QSpinBox *Spinbox_xrd_num_peaks_condition=nullptr;

  // gaussian parametes
//  QSpinBox *Spinbox_xrd_gaussian_parameters_width=nullptr;
//  QSpinBox *Spinbox_xrd_gaussian_parameters_sd=nullptr;
  int XRD_gaussian_parameters_width=_data_xrd_ns::XRD_GAUSSIAN_WIDTH_DEFAULT;
  int XRD_gaussian_parameters_sd=_data_xrd_ns::XRD_GAUSSIAN_SD_DEFAULT;


  float XRD_correlation_good_threshold=_data_xrd_ns::XRD_THRESHOLD_GOOD_CORRELATION;
  float XRD_correlation_medium_threshold=_data_xrd_ns::XRD_THRESHOLD_MEDIUM_CORRELATION;
  float XRD_correlation_bad_threshold=_data_xrd_ns::XRD_THRESHOLD_BAD_CORRELATION;

  int XRD_num_removed_peaks=0;

  bool XRD_obs_data_loaded=false;

  bool XRD_data_order_pigment_name_increase=true;
  bool XRD_data_order_correlation_increase=false;

  // PDB options
//  bool XRD_use_pdb_spectral_Cu=_data_xrd_ns::USE_XRD_PDB_SPECTRAL_CU_DEFAULT;
//  bool XRD_use_pdb_spectral_Co=_data_xrd_ns::USE_XRD_PDB_SPECTRAL_CO_DEFAULT;
//  bool XRD_use_pdb_astm_Cu=_data_xrd_ns::USE_XRD_PDB_ASTM_CU_DEFAULT;

  std::vector<std::string> Vec_xrd_selected_pdb_folders;
  _data_xrd_ns::_tube_type XRD_tube_type=_data_xrd_ns::TUBE_TYPE_DEDAULT;
#endif


  QTabWidget *Tab=nullptr;
  //
  QIcon Icons[2][2];

  QToolButton *Toolbutton_xrf1=nullptr;
  QToolButton *Toolbutton_xrf2=nullptr;

  _window_interpreter_ns::_action_type Action_type=_window_interpreter_ns::_action_type::ACTION_NONE;

  // options
  _w_options_interpreter *W_options=nullptr;

  //
  bool XRF_obs_data_loaded=false;

   //
  _project_data_ns::_project_data Project_data;

  // maximums
  std::vector<float> Vec_XRF_maximum_values;
  float Max_global_xrf_value=-1;
  int XRF_general_threshold=_data_xrf_ns::XRF_THRESHOLD_PERCENTAGE;

  // superposition. Name of the elements that have a superposition
  std::vector<std::string> Vec_superposition;

  bool Key_pressed=false;
  float X_pos=-1;
  float Y_pos=-1;
  float X_pos_ka=-1;
  float X_pos_kb=-1;

  // options
  //XRF
  int XRF_title_font_size;
  int XRF_legend_font_size;
  int XRF_graph_line_width=_window_interpreter_ns::XRF_GRAPH_LINE_WIDTH;

  //XRD
  int XRD_title_font_size;
  int XRD_legend_font_size;
  int XRD_graph_line_width=_window_interpreter_ns::XRD_GRAPH_LINE_WIDTH;

  // Num steps
  unsigned int XRF_num_steps_smooth=_data_xrf_ns::XRF_NUM_STEPS_SMOOTH;
  unsigned int XRF_num_steps_subtract_background=_data_xrf_ns::XRF_NUM_STEPS_SUBTRACT_BACKGROUND;
  unsigned int XRF_num_steps_search_window=_data_xrf_ns::NUM_STEPS_SEARCH_WINDOW_XRF;

  //
  std::vector<int> Vec_xrd_selected_position;

  //
  bool Split_screen=true;
  bool XRF_tab_active=false;

  //
  bool Left_button=false;

  std::vector<float> Vec_tube_peak;

  //
  bool XRF_valid=false;
  bool XRD_valid=false;

  //
  bool XRD_pdb_mode=false;
  _data_xrd_ns::_pdb_type PDB_type;
  _data_xrd_ns::_tube_type PDB_tube_type;
  bool PDB_normalized;
  QString PDB_name;
  QString PDB_formula;
  QString PDB_xrf_elements;
  QString PDB_rgb_color;
};

#endif

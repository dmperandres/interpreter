#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QDateTime>
#include <QDate>
//#include <QDesktopWidget>
#include <random>

#include "window_interpreter.h"

//#include "download_file.h"

QWizardPage *createIntroPage_init()
{
  QWizardPage *page = new QWizardPage;

  QFont Font=page->font();
  Font.setPointSize(20);

  page->setFont(Font);
  page->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/icons/logo_MapLab_Interpreter.png","png"));
  return page;
}

int main( int argc, char ** argv )
{
  QApplication Application( argc, argv );


#ifdef CONTROL_TIME

  QDateTime Date_time=QDateTime::currentDateTime();
  QString Date=Date_time.toString("dd.MM.yy");

//  _download_file Download;

//  Download.download();

//  if (QFile::exists("access.txt")){
//    QFile oldFile("access.txt");
//    QFileInfo fileInfo; fileInfo.setFile(oldFile);
//    QDateTime created = fileInfo.lastModified();

//    QString File_date=created.toString("dd.MM.yy");

//    if (Date!=File_date) exit(-1);

//  }
//  else{
    random_device Random_device;   // non-deterministic generator
    mt19937 Generator(Random_device());  // to seed mersenne twister.
    uniform_int_distribution<> Random(0,10);

//    QDateTime Date_time=QDateTime::currentDateTime();
//    QString Date=Date_time.toString("dd.MM.yy");

    QDateTime Init_date_time(QDate(2021,5,1));
    int Num_days=Init_date_time.daysTo(Date_time);

    if (Num_days>=30){
      if (Random(Generator)<7) exit(-1);
    }
//  }
#endif

  #ifdef REDIRECT
  #ifdef LINUX
    std::ofstream Output_stream("log.txt",std::ofstream::out);
  #else
    std::ofstream Output_stream("C:/log.txt",std::ofstream::out);
  #endif

  cout.rdbuf(Output_stream.rdbuf());
  #endif

  #ifdef DEBUG_PROGRAM
  cout << "Debugging" << endl;
  cout << "Current dir " << QDir::currentPath().toStdString() << endl;
  #endif


  QSurfaceFormat Format;
  Format.setDepthBufferSize(24);
  Format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(Format);

#ifdef LINUX
  QFont Font("Arial");
#else
  QFont Font("Microsoft Sans Serif");
#endif
  Font.setPointSize(_common_ns::UI_FONT_SIZE_DEFAULT);
  Application.setFont(Font);

//  Window.setWindowState(Qt::WindowMaximized);

//   QWizard Wizard;
// //  _wizard Wizard(&Application);
//   Wizard.setButtonText(QWizard::FinishButton, "Continue");
//   Wizard.setWizardStyle(QWizard::ClassicStyle);
//   Wizard.setWindowFlags(Qt::WindowStaysOnTopHint);
//   Wizard.setOptions(QWizard::NoCancelButton | QWizard::NoBackButtonOnLastPage);
//   Wizard.addPage(createIntroPage_init());
//   //Wizard.setWindowTitle("License");

//   // for centering the window of the wizard
////   QRect screenGeometry = Window.geometry();
////   int x = (screenGeometry.width()-Wizard.width()-300) / 2;
////   int y = (screenGeometry.height()-Wizard.height()) / 2;
////   Wizard.move(screenGeometry.x()+x,screenGeometry.y()+y);
//   Wizard.exec();

   _window_interpreter Window;
    Window.show();
//    Window.check_project();

  return Application.exec();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:




    QString to_QString(int);

    //Box:Konsole
    void gui_set_Console_field(std::string ConsoleOutput);

    //Box:Register
    void gui_set_dataSpeicher_table(int row, int column, std::string dataSpeicherOutput);
    void gui_get_dataSpeicher_table();

    //Box:Pins
    void gui_set_pin_table(int row, int column, std::string PinTableChange);
    void pin_table_checkbox(int row, int column);

    //Box:Quarzfrequenz
    void gui_set_quarzfrequenz_Label(int quarztakt);

    //Box:Laufzeit
    void gui_set_laufzeit_Label(int laufzeit);

    void gui_set_Console_field2(QString file_name);


    //Box:sichtbar
    void gui_set_wReg_Label(int wReg);
    void gui_set_fsr_Label( int fsr);
    void gui_set_pcl_Label(int pcl);
    void gui_set_pcLath_Label(int pcLath);
    void gui_set_status_Label(int status);

    //Box:unsichtbar
    void gui_set_pc_Label(int pc);
    void gui_set_stackpointer_Label(int stackpointer);
    void gui_set_vt_Label(int vt);
    void gui_set_wdt_Label(int wdt);
    void gui_check_wdt_aktiv();

    //Box 1 unten links
    void gui_set_irp_Label(int irp);
    void gui_set_rp1_Label(int rp1);
    void gui_set_rp0_Label(int rp0);
    void gui_set_t0_Label(int t0);
    void gui_set_pd_Label(int pd);
    void gui_set_z_Label(int z);
    void gui_set_dc_Label(int dc);
    void gui_set_c_Label(int c);

    void gui_set_option_Label(int option);

    // Box 2 unten links
    void gui_set_rbp_Label(int rbp);
    void gui_set_intedg_Label(int intedg);
    void gui_set_t0cs_Label(int t0cs);
    void gui_set_t0se_Label(int t0se);
    void gui_set_psa_Label(int psa);
    void gui_set_ps2_Label(int ps2);
    void gui_set_ps1_Label(int ps1);
    void gui_set_ps0_Label(int ps0);

    void gui_set_intcon_Label(int intcon);
    
    // Box 3 unten links
    void gui_set_gie_Label(int gie);
    void gui_set_pie_Label(int pie);
    void gui_set_t0ie_Label(int t0ie);
    void gui_set_inte_Label(int inte);
    void gui_set_rbie_Label(int rbie);
    void gui_set_t0if_Label(int t0if);
    void gui_set_intf_Label(int intf);
    void gui_set_rbif_Label(int rbif);

    //Menüband
    void gui_actionLaden_triggered();

    void on_go_button_clicked();

    void gui_pin_table_checkbox(int row, int column);



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

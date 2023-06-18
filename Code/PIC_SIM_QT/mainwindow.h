#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtablewidget.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QPainter>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);

public slots:



    // Umwandlung
    QString to_QString(int);
    QString string_to_QString(std::string input);

    //Box:Konsole
    void gui_set_Console_field(std::string ConsoleOutput);

    //Box:Register
    void gui_set_dataSpeicher_table(int row, int column, std::string dataSpeicherOutput);
    void gui_get_dataSpeicher_table();

    //Box:Pins
    void PIC_incTimer();
    void gui_set_pin_table(int row, int column, std::string PinTableChange);
    int gui_pin_table_checkbox_compare(int row, int column);
    int gui_get_new_pin_value(int row, int column);
    void pin_action();
    void gui_set_IO();

    //Box:Quarzfrequenz und progTime
    void gui_set_quarzfrequenz_Label();
    void gui_set_progTime_Label();

    //Box:Laufzeit
    void gui_set_laufzeit_Label();


    //Box:sichtbar
    void gui_set_wReg_Label();
    void gui_set_fsr_Label();
    void gui_set_pcl_Label();
    void gui_set_pcLath_Label();
    void gui_set_status_Label();

    //Box:unsichtbar
    void gui_set_pc_Label();
    void gui_set_stackpointer_Label();
    void gui_set_vt_Label();
    void gui_set_wdt_Label();
    void gui_check_wdt_aktiv();

    //Box 1 unten links
    void gui_set_irp_Label();
    void gui_set_rp1_Label();
    void gui_set_rp0_Label();
    void gui_set_t0_Label();
    void gui_set_pd_Label();
    void gui_set_z_Label();
    void gui_set_dc_Label();
    void gui_set_c_Label();

    void gui_set_option_Label();

    // Box 2 unten links
    void gui_set_rbp_Label();
    void gui_set_intedg_Label();
    void gui_set_t0cs_Label();
    void gui_set_t0se_Label();
    void gui_set_psa_Label();
    void gui_set_ps2_Label();
    void gui_set_ps1_Label();
    void gui_set_ps0_Label();

    void gui_set_intcon_Label();
    
    // Box 3 unten links
    void gui_set_gie_Label();
    void gui_set_pie_Label();
    void gui_set_t0ie_Label();
    void gui_set_inte_Label();
    void gui_set_rbie_Label();
    void gui_set_t0if_Label();
    void gui_set_intf_Label();
    void gui_set_rbif_Label();

    // wdt label
    void gui_set_wdt_reset_label();

    // Stack elemente
    void gui_set_stack_elements();

    //Menüband
    void on_actionLaden_triggered();

    //Footer
    void gui_set_pfad_Label();
    void gui_set_laeuft_label();


    void on_go_button_clicked();
    void on_reset_Button_clicked();

    void on_next_button_clicked();

    void on_debug_button_clicked();

    void on_reset_laufzeit_button_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_quarzfrequenz_input_textChanged(const QString &arg1);

    // RefreshGUI functions
    void refresh_GUI();
    void fillBox();
    void refreshDataSpeicher();


private slots:







    void on_pin_table_itemClicked(QTableWidgetItem *item);

    void on_pin_table_itemActivated(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    static MainWindow* mainInstance;
};
#endif // MAINWINDOW_H

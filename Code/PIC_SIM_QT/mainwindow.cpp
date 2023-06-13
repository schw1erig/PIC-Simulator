#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QFileDialog>
using namespace std;

int quarztakt;
int laufzeit;
int wReg;
int fsr;
int pcl;
int pcLath;
int status;
int pc;
int stackpointer;
int vt;
int wdt;
int irp;
int rp1;
int rp0;
int t0;
int pd;
int z;
int dc;
int c;
int option;
int rbp;
int intedg;
int t0cs;
int t0se;
int psa;
int ps2;
int ps1;
int ps0;
int intcon;
int gie;
int pie;
int t0ie;
int inte;
int rbie;
int t0if;
int intf;
int rbif;
int ConsoleOutput;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Console_Field->setReadOnly(true);
    ui->Console_Field->moveCursor (QTextCursor::End);
    ui->Console_Field->insertPlainText ("Hallo ich sollte unten sein\n");
    ui->Console_Field->moveCursor (QTextCursor::End);
    ui->Console_Field->moveCursor (QTextCursor::End);
    ui->Console_Field->insertPlainText ("Hallo ich sollte noch weiter unten sein");
    ui->Console_Field->moveCursor (QTextCursor::End);
     ui->Console_Field->insertPlainText ("\nHallo ich sollte noch weiter unten sein");
      ui->Console_Field->insertPlainText ("\nHallo ich sollte noch weiter unten sein");
    gui_set_quarzfrequenz_Label(100);
    gui_set_Console_field("hallo was geht");
    gui_set_Console_field("hallo was geht");
    gui_set_dataSpeicher_table(2,3,"hallo");
    gui_set_pin_table(2,3,"haLLO");

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::to_QString(int input){
std:string s_input = std::to_string(input);
    QString q_input = QString::fromStdString(s_input);
    return q_input;
}

void MainWindow::gui_set_Console_field(std::string ConsoleOutput)
{
    std::string str = ConsoleOutput;
    QString qstr = QString::fromStdString(str);
    ui->Console_Field->moveCursor(QTextCursor::End);
    ui->Console_Field->insertPlainText("\n");
    ui->Console_Field->insertPlainText(qstr);
}

void MainWindow::gui_set_dataSpeicher_table(int row, int column, std::string dataSpeicherOutput)
{
    std::string str = dataSpeicherOutput;
    QString qstr = QString::fromStdString(str);
    ui->dataSpeicher_table->setItem(row, column, new QTableWidgetItem(qstr));
}

void MainWindow::gui_get_dataSpeicher_table()
{

}

void MainWindow::gui_set_pin_table(int row, int column, std::string PinTableChange)
{
    std::string str = PinTableChange;
    QString qstr = QString::fromStdString(str);
    ui->pin_table->setItem(row, column, new QTableWidgetItem(qstr));
}

void MainWindow::gui_set_quarzfrequenz_Label(int quarztakt)
{
    ui->quarzfrequenz_Label->setText(to_QString(quarztakt));
}

void MainWindow::gui_set_laufzeit_Label()
{
    ui->laufzeit_Label->setText(to_QString(laufzeit));
}

void MainWindow::gui_set_wReg_Label()
{
    ui->wReg_Label->setText(to_QString(wReg));
}

void MainWindow::gui_set_fsr_Label()
{
    ui->fsr_Label->setText(to_QString(fsr));
}

void MainWindow::gui_set_pcl_Label()
{
    ui->pcl_Label->setText(to_QString(pcl));
}

void MainWindow::gui_set_pcLath_Label()
{
    ui->pcLath_Label->setText(to_QString(pcLath));
}

void MainWindow::gui_set_status_Label()
{
    ui->status_Label->setText(to_QString(status));
}

void MainWindow::gui_set_pc_Label()
{
    ui->pc_Label->setText(to_QString(pc));
}

void MainWindow::gui_set_stackpointer_Label()
{
    ui->stackpointer_Label->setText(to_QString(stackpointer));
}

void MainWindow::gui_set_vt_Label()
{
    ui->vt_Label->setText(to_QString(vt));
}

void MainWindow::gui_set_wdt_Label()
{
    ui->wdt_Label->setText(to_QString(wdt));
}

bool MainWindow::gui_check_wdt_aktiv()
{
    return 0;
}

void MainWindow::gui_set_irp_Label()
{
    ui->irp_Label->setText(to_QString(irp));
}

void MainWindow::gui_set_rp1_Label()
{
    ui->rp1_Label->setText(to_QString(rp1));
}

void MainWindow::gui_set_rp0_Label()
{
    ui->rp0_Label->setText(to_QString(rp0));
}

void MainWindow::gui_set_t0_Label()
{
    ui->t0_Label->setText(to_QString(t0));
}

void MainWindow::gui_set_pd_Label()
{
    ui->pd_Label->setText(to_QString(pd));
}

void MainWindow::gui_set_z_Label()
{
    ui->z_Label->setText(to_QString(z));
}

void MainWindow::gui_set_dc_Label()
{
    ui->dc_Label->setText(to_QString(dc));
}

void MainWindow::gui_set_c_Label()
{
    ui->c_Label->setText(to_QString(c));
}

void MainWindow::gui_set_option_Label()
{
ui->option_Label->setText(to_QString(option));
}

void MainWindow::gui_set_rbp_Label()
{
    ui->rbp_Label->setText(to_QString(rbp));
}

void MainWindow::gui_set_intedg_Label()
{
    ui->intedg_Label->setText(to_QString(intedg));
}

void MainWindow::gui_set_t0cs_Label()
{
    ui->t0cs_Label->setText(to_QString(t0cs));
}

void MainWindow::gui_set_t0se_Label()
{
    ui->t0se_Label->setText(to_QString(t0se));
}

void MainWindow::gui_set_psa_Label()
{
    ui->psa_Label->setText(to_QString(psa));
}

void MainWindow::gui_set_ps2_Label()
{
    ui->ps2_Label->setText(to_QString(ps2));
}

void MainWindow::gui_set_ps1_Label()
{
    ui->ps1_Label->setText(to_QString(ps1));
}

void MainWindow::gui_set_ps0_Label()
{
    ui->ps0_Label->setText(to_QString(ps0));
}

void MainWindow::gui_set_intcon_Label()
{
    ui->intcon_Label->setText(to_QString(intcon));
}

void MainWindow::gui_set_gie_Label()
{
    ui->gie_Label->setText(to_QString(gie));
}

void MainWindow::gui_set_pie_Label()
{
    ui->pie_Label->setText(to_QString(pie));
}

void MainWindow::gui_set_t0ie_Label()
{
    ui->t0ie_Label->setText(to_QString(t0ie));
}

void MainWindow::gui_set_inte_Label()
{
    ui->inte_Label->setText(to_QString(inte));
}

void MainWindow::gui_set_rbie_Label()
{
    ui->rbie_Label->setText(to_QString(rbie));
}

void MainWindow::gui_set_t0if_Label()
{
    ui->t0if_Label->setText(to_QString(t0if));
}

void MainWindow::gui_set_intf_Label()
{
    ui->intf_Label->setText(to_QString(intf));
}

void MainWindow::gui_set_rbif_Label()
{
    ui->rbif_Label->setText(to_QString(rbif));
}

void MainWindow::on_actionLaden_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://");
}


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QFileDialog>

#include "common.h"

using namespace std;

int quarztakt;
int laufzeit;
int fsr;
int pcl;
int pcLath;
int status;
int pc;
int stackpointer;
int vt;
//int wdt;
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

std::string ConsoleOutput;



MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Console_Field->setReadOnly(true);
    fillBox();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QImage image;
    image.load(":ressources/circle.png");

    QPainter imagePainter(this);
    imagePainter.drawImage(QPoint(1045, 60), image);
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

void MainWindow::gui_set_quarzfrequenz_Label()
{
    ui->quarzfrequenz_Label->setText(to_QString(quarzTakt));
}

void MainWindow::gui_set_progTime_Label()
{
    //ui->progTime_Label->setText(to_QString(progTime));
}

void MainWindow::gui_set_laufzeit_Label()
{
    ui->laufzeit_Label->setText(to_QString(progTime));
}

void MainWindow::gui_set_wReg_Label(int wReg)
{
    ui->wReg_Label->setText(to_QString(wReg));
}

void MainWindow::gui_set_fsr_Label(int fsr)
{
    ui->fsr_Label->setText(to_QString(fsr));
}

void MainWindow::gui_set_pcl_Label(int pcl)
{
    ui->pcl_Label->setText(to_QString(pcl));
}

void MainWindow::gui_set_pcLath_Label(int pcl)
{
    ui->pcLath_Label->setText(to_QString(pcLath));
}

void MainWindow::gui_set_status_Label(int status)
{
    ui->status_Label->setText(to_QString(status));
}

void MainWindow::gui_set_pc_Label(int pc)
{
    ui->pc_Label->setText(to_QString(pc));
}

void MainWindow::gui_set_stackpointer_Label(int stackpointer)
{
    ui->stackpointer_Label->setText(to_QString(stackpointer));
}

void MainWindow::gui_set_vt_Label(int vt)
{
    ui->vt_Label->setText(to_QString(vt));
}

void MainWindow::gui_set_wdt_Label(int wdt)
{
    ui->wdt_Label->setText(to_QString(wdt));
}

void MainWindow::gui_check_wdt_aktiv()
{
    if(ui->checkBox->isChecked())
    {
        ui->Console_Field->moveCursor(QTextCursor::End);
        ui->Console_Field->insertPlainText("\n");
        ui->Console_Field->insertPlainText("WDT is checked");
        wdtActive = 1;
    }
    else{
        ui->Console_Field->moveCursor(QTextCursor::End);
        ui->Console_Field->insertPlainText("\n");
        ui->Console_Field->insertPlainText("WDT is unchecked");
        wdtActive = 0;
    }

}

void MainWindow::gui_set_irp_Label(int irp)
{
    ui->irp_Label->setText(to_QString(irp));
}

void MainWindow::gui_set_rp1_Label(int rp1)
{
    ui->rp1_Label->setText(to_QString(rp1));
}

void MainWindow::gui_set_rp0_Label(int rp0)
{
    ui->rp0_Label->setText(to_QString(rp0));
}

void MainWindow::gui_set_t0_Label(int t0)
{
    ui->t0_Label->setText(to_QString(t0));
}

void MainWindow::gui_set_pd_Label(int pd)
{
    ui->pd_Label->setText(to_QString(pd));
}

void MainWindow::gui_set_z_Label(int z)
{
    ui->z_Label->setText(to_QString(z));
}

void MainWindow::gui_set_dc_Label(int dc)
{
    ui->dc_Label->setText(to_QString(dc));
}

void MainWindow::gui_set_c_Label(int c)
{
    ui->c_Label->setText(to_QString(c));
}

void MainWindow::gui_set_option_Label(int option)
{
ui->option_Label->setText(to_QString(option));
}

void MainWindow::gui_set_rbp_Label(int rbp)
{
    ui->rbp_Label->setText(to_QString(rbp));
}

void MainWindow::gui_set_intedg_Label(int intedg)
{
    ui->intedg_Label->setText(to_QString(intedg));
}

void MainWindow::gui_set_t0cs_Label(int t0cs)
{
    ui->t0cs_Label->setText(to_QString(t0cs));
}

void MainWindow::gui_set_t0se_Label(int t0se)
{
    ui->t0se_Label->setText(to_QString(t0se));
}

void MainWindow::gui_set_psa_Label(int psa)
{
    ui->psa_Label->setText(to_QString(psa));
}

void MainWindow::gui_set_ps2_Label(int ps2)
{
    ui->ps2_Label->setText(to_QString(ps2));
}

void MainWindow::gui_set_ps1_Label(int ps1)
{
    ui->ps1_Label->setText(to_QString(ps1));
}

void MainWindow::gui_set_ps0_Label(int ps0)
{
    ui->ps0_Label->setText(to_QString(ps0));
}

void MainWindow::gui_set_intcon_Label(int intcon)
{
    ui->intcon_Label->setText(to_QString(intcon));
}

void MainWindow::gui_set_gie_Label(int gie)
{
    ui->gie_Label->setText(to_QString(gie));
}

void MainWindow::gui_set_pie_Label(int pie)
{
    ui->pie_Label->setText(to_QString(pie));
}

void MainWindow::gui_set_t0ie_Label(int t0ie)
{
    ui->t0ie_Label->setText(to_QString(t0ie));
}

void MainWindow::gui_set_inte_Label(int inte)
{
    ui->inte_Label->setText(to_QString(inte));
}

void MainWindow::gui_set_rbie_Label(int rbie)
{
    ui->rbie_Label->setText(to_QString(rbie));
}

void MainWindow::gui_set_t0if_Label(int t0if)
{
    ui->t0if_Label->setText(to_QString(t0if));
}

void MainWindow::gui_set_intf_Label(int intf)
{
    ui->intf_Label->setText(to_QString(intf));
}

void MainWindow::gui_set_rbif_Label(int rbif)
{
    ui->rbif_Label->setText(to_QString(rbif));
}





void MainWindow::gui_set_Console_field2(QString file_name)
{

    ui->Console_Field->moveCursor(QTextCursor::End);
    ui->Console_Field->insertPlainText("\n");
    ui->Console_Field->insertPlainText(file_name);
}

void MainWindow::on_actionLaden_triggered()
{
    qDebug() << "laden triggered";
    //QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://");
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://");

    qDebug() << file_name;
    filename = file_name.toStdString();
    qDebug() << filename;

    bootPIC();
    einlesen(filename);
    fileAusgeben();
    extractBefehle();
    fillBox();

}

void MainWindow::gui_pin_table_checkbox(int row, int column)
{
    if(ui->pin_table->item(row,column)->checkState())
    {
        ui->Console_Field->moveCursor(QTextCursor::End);
        ui->Console_Field->insertPlainText("\n");
        ui->Console_Field->insertPlainText("is checked");
    }
    else
    {
        ui->Console_Field->moveCursor(QTextCursor::End);
        ui->Console_Field->insertPlainText("\n");
        ui->Console_Field->insertPlainText("is unchecked");

    }
}

//----------------------------------
//Buttons und fillGui funktionen:
void MainWindow::on_next_button_clicked()
{
    qDebug() << "go clicked" ;
    //testProgAblauf();
    //gui_set_Console_field(to_string(wReg));
    //gui_check_wdt_aktiv();
    //gui_pin_table_checkbox(2,1);
    execBefehl();
    fillBox();
    gui_set_laufzeit_Label();


}

void MainWindow::on_go_button_clicked()
{
    if (test == 1) {
        test = 0;
    } else {
        test = 1;
    }



    while (test) {
        //i++;
        //qDebug() << i;

        execBefehl();
        fillBox();
        gui_set_laufzeit_Label();

        _sleep(0);
        qApp->processEvents();

    }
}

void MainWindow::on_reset_Button_clicked()
{
    qDebug() << "Reset Button";
    test = 0;
    qDebug() << test;
    resetPIC();
    fillBox();
}


void MainWindow::on_debug_button_clicked()
{
    qDebug() << "Debug";
}




void MainWindow::on_reset_laufzeit_button_clicked()
{
    progTime = 0;
    gui_set_laufzeit_Label();
}

//-----------
//FillGUi funktionen
void MainWindow::fillBox() {
    //int gesamtzeile =106;
    ui->Console_Field->clear();

    for (int i = 0; i < 1024; i++) {
        if (prog[i] != "no") {
            if(i == matchZeile[progZeiger]) {
                gui_set_Console_field("->" + prog[i]);
            } else {
                gui_set_Console_field("   " + prog[i]);
            }
        }
    }
    for (int i = 0; i<=maxZeilen-matchZeile[progZeiger]+10; i++){
        ui->Console_Field->moveCursor(QTextCursor::Up);
    }
}






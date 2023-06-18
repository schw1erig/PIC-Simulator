#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QFileDialog>

#include "common.h"

using namespace std;


std::string ConsoleOutput;



MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Console_Field->setReadOnly(true);
    //fillBox();
    refresh_GUI();
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

QString MainWindow::string_to_QString(string input){
    QString q_input = QString::fromStdString(input);
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
    string sQuarzTakt = doubleToString(quarzTakt);
    ui->quarzfrequenz_Label->setText(string_to_QString(sQuarzTakt));
}

void MainWindow::gui_set_progTime_Label()
{
    //ui->progTime_Label->setText(to_QString(progTime));
}

void MainWindow::gui_set_laufzeit_Label()
{
    string sProgTime = doubleToString(progTime);
    ui->laufzeit_Label->setText(string_to_QString(sProgTime));
}

void MainWindow::gui_set_wReg_Label()
{
    ui->wReg_Label->setText(string_to_QString(toHexString(wReg)));
}

void MainWindow::gui_set_fsr_Label()
{
    ui->fsr_Label->setText(string_to_QString(toHexString(getFSR())));
}

void MainWindow::gui_set_pcl_Label()
{
    ui->pcl_Label->setText(string_to_QString(toHexString(getPCL())));
}

void MainWindow::gui_set_pcLath_Label()
{
    ui->pcLath_Label->setText(string_to_QString(toHexString(getPCLATH())));
}

void MainWindow::gui_set_status_Label()
{
    uint8_t status = getStatus(0xff);
    ui->status_Label->setText(string_to_QString(toHexString(status)));
}

void MainWindow::gui_set_pc_Label()
{
    ui->pc_Label->setText(string_to_QString(toHexString(progZeiger)));

}

void MainWindow::gui_set_stackpointer_Label()
{
    ui->stackpointer_Label->setText(to_QString(stackZeiger));
    ui->gui_stackZeiger->setText(to_QString(stackZeiger));
}

void MainWindow::gui_set_stack_elements()
{

    ui->gui_stack0->setText(to_QString(stack[0]));
    ui->gui_stack1->setText(to_QString(stack[1]));
    ui->gui_stack2->setText(to_QString(stack[2]));
    ui->gui_stack3->setText(to_QString(stack[3]));
    ui->gui_stack4->setText(to_QString(stack[4]));
    ui->gui_stack5->setText(to_QString(stack[5]));
    ui->gui_stack6->setText(to_QString(stack[6]));
    ui->gui_stack7->setText(to_QString(stack[7]));


}


void MainWindow::gui_set_vt_Label()
{
    ui->vt_Label->setText(string_to_QString(toHexString(pre)));
}

void MainWindow::gui_set_wdt_Label()
{
    string sWdt = doubleToString(wdt);
    ui->wdt_Label->setText(string_to_QString(sWdt));
}

void MainWindow::gui_check_wdt_aktiv()
{
    if(ui->checkBox->isChecked())
    {
        wdtActive = 1;
    }
    else{
        wdtActive = 0;
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked())
    {
        wdtActive = 1;
    }
    else{
        wdtActive = 0;
    }
}

void MainWindow::gui_set_irp_Label()
{
    ui->irp_Label->setText(to_QString(getStatus(0x80)));
}

void MainWindow::gui_set_rp1_Label()
{
    ui->rp1_Label->setText(to_QString(getStatus(0x40)));
}

void MainWindow::gui_set_rp0_Label()
{
    ui->rp0_Label->setText(to_QString(getRP0()));
}

void MainWindow::gui_set_t0_Label()
{
    ui->t0_Label->setText(to_QString(getTO()));
}

void MainWindow::gui_set_pd_Label()
{
    ui->pd_Label->setText(to_QString(getPD()));
}

void MainWindow::gui_set_z_Label()
{
    ui->z_Label->setText(to_QString(getZ()));
}

void MainWindow::gui_set_dc_Label()
{
    ui->dc_Label->setText(to_QString(getDC()));
}

void MainWindow::gui_set_c_Label()
{
    ui->c_Label->setText(to_QString(getC()));
}

void MainWindow::gui_set_option_Label()
{
    uint8_t option = getOption(0xff);
    ui->option_Label->setText(string_to_QString(toHexString(option)));
}

void MainWindow::gui_set_rbp_Label()
{
    ui->rbp_Label->setText(to_QString(getOption(0x80)));
}

void MainWindow::gui_set_intedg_Label()
{
    ui->intedg_Label->setText(to_QString(getINTEDG()));
}

void MainWindow::gui_set_t0cs_Label()
{
    ui->t0cs_Label->setText(to_QString(getT0CS()));
}
void MainWindow::gui_set_t0se_Label()
{
    ui->t0se_Label->setText(to_QString(getT0SE()));
}

void MainWindow::gui_set_psa_Label()
{
    ui->psa_Label->setText(to_QString(getPSA()));
}

void MainWindow::gui_set_ps2_Label()
{
    ui->ps2_Label->setText(to_QString(getOption(0x04)));
}

void MainWindow::gui_set_ps1_Label()
{
    ui->ps1_Label->setText(to_QString(getOption(0x02)));
}

void MainWindow::gui_set_ps0_Label()
{
    ui->ps0_Label->setText(to_QString(getOption(0x01)));
}

void MainWindow::gui_set_intcon_Label()
{
    ui->intcon_Label->setText(string_to_QString(toHexString(getINTCON(0xff))));
}

void MainWindow::gui_set_gie_Label()
{
    ui->gie_Label->setText(to_QString(getGIE()));
}

void MainWindow::gui_set_pie_Label()
{
    ui->pie_Label->setText(to_QString(getEEIE()));
}

void MainWindow::gui_set_t0ie_Label()
{
    ui->t0ie_Label->setText(to_QString(getT0IE()));
}

void MainWindow::gui_set_inte_Label()
{
    ui->inte_Label->setText(to_QString(getINTE()));
}

void MainWindow::gui_set_rbie_Label()
{
    ui->rbie_Label->setText(to_QString(getRBIE()));
}

void MainWindow::gui_set_t0if_Label()
{
    ui->t0if_Label->setText(to_QString(getT0IF()));
}

void MainWindow::gui_set_intf_Label()
{
    ui->intf_Label->setText(to_QString(getINTF()));
}

void MainWindow::gui_set_rbif_Label()
{
    ui->rbif_Label->setText(to_QString(getRBIF()));
}

void MainWindow::gui_set_wdt_reset_label()
{
    if (wdtReset) {
       ui->wdt_reset_label->setText(string_to_QString("Watchdog reset"));
    } else {
       ui->wdt_reset_label->setText(string_to_QString(""));
    }

}

void MainWindow::gui_set_pfad_Label()
{
    ui->pfad_label->setText(string_to_QString(filename));
}


void MainWindow::gui_set_laeuft_label()
{
    if(goLoop) {
       ui->laeuft_label->setText(string_to_QString("Läuft"));
    } else {
       ui->laeuft_label->setText(string_to_QString(""));
    }

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
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "G:/Ausbildung/Git/PIC-Simulator/TestProg_PicSim_20210420");

    qDebug() << file_name;
    filename = file_name.toStdString();
    qDebug() << filename;

    //dataSpeicher[1][1] = 0xff;
    resetPIC();
    einlesen(filename);
    fileAusgeben();
    extractBefehle();
    refresh_GUI();

}

int MainWindow::gui_pin_table_checkbox_compare(int row, int column)
{
    /*
    int reg;
    int oldValue;
    int newValue;

    if(row == 2) {
        reg = 0x05;
    } else {
        reg = 0x06;
    }

    oldValue = dataSpeicher[0][reg] & (1u << (7-column));


    if(ui->pin_table->item(row,column)->checkState())
    {
       newValue=1;
       qDebug() << row << " " << column << "checked";
    }
    else
    {
        newValue=0;
        qDebug() << row << " " << column << "unchecked";
    }

    if(newValue == oldValue) {
        return 0;
    } else {
        return 1;
    } */
    return 0;
}

int MainWindow::gui_get_new_pin_value(int row, int column)
{
    int newValue;

    if(ui->pin_table->item(row,column)->checkState())
    {
        newValue=1;
        qDebug() << row << " " << column << "checked";
    }
    else
    {
        newValue=0;
        qDebug() << row << " " << column << "unchecked";
    }

    qDebug() << "New get" << newValue;

    return newValue;
}


void MainWindow::on_pin_table_itemClicked(QTableWidgetItem *item)
{

    pin_action();
    refresh_GUI();
    //qDebug() << "done\n";
}

void MainWindow::pin_action() {

    int newValue;
    int oldValue;
    int reg;
    int fallFlanke;

    for (int i = 2; i < 6; i+=3) {
        for(int j = 0; j < 8; j++){

            newValue = gui_get_new_pin_value(i, j);
            oldValue = ( dataSpeicher[0][reg] & (1u << (7-j)) ) > 0 ;

            qDebug() << i << " " << j << "old: " << oldValue<< "new: " << newValue;

            if(i == 2) {
                reg = 0x05;
            } else {
                reg = 0x06;
            }

            if(newValue != oldValue) {

                fallFlanke = getFlanke(oldValue, newValue);

                // setze neuen wert im register
                if(j == 0) {
                    dataSpeicher[0][reg] = dataSpeicher[0][reg] ^ 1u; // setze bit auf gewuenschten wert
                } else {
                    dataSpeicher[0][reg] = dataSpeicher[0][reg] ^ ( 1u << (7-j) ); // setze bit auf gewuenschten wert
                }

            }


            if(i == 2 && j == 3) {
                if (getT0CS() == 1) {
                    qDebug() << "T0CS 1";
                    if(getT0SE() && fallFlanke == 1) {
                        // T0SE auf 1 definiert fallende Flanke => Timer inc.
                        qDebug() << "T0SE 1 und fallende Flanke => inc Timer";
                        incTimer();
                    } else if (!getT0SE() && fallFlanke == 0) {
                        // TOSE auf 0 und steigende Flanke => Timer inc.
                        qDebug() << "T0SE 0 und steigende Flanke => inc Timer";
                        incTimer();
                    }
                }
            }
        }
    }

    qDebug() << "done---------";
}



//----------------------------------
//Buttons, Events und fillGui funktionen:
void MainWindow::on_next_button_clicked()
{
    qDebug() << "next clicked" ;
    //testProgAblauf();
    //gui_check_wdt_aktiv();
    //gui_pin_table_checkbox(2,1);
    //wdt = 0;
    wdtReset = 0;
    execBefehl();
    refresh_GUI();
}

void MainWindow::on_go_button_clicked()
{
    if (goLoop == 1) {
        goLoop = 0;
    } else {
        goLoop = 1;
        // Watchdog zur�cksetzen
        wdt = 0;
        wdtReset = 0;
    }

    while (goLoop) {
        execBefehl();
        refresh_GUI();

        //_sleep(0);
        qApp->processEvents();

    }
}

void MainWindow::on_reset_Button_clicked()
{
    qDebug() << "Reset Button";
    resetPIC();
    refresh_GUI();
}


void MainWindow::on_debug_button_clicked()
{
    qDebug() << "Debug";
    //dataSpeicher[0][3] = 0x18;
    //dataSpeicher[1][3] = 0x18;
    //qDebug() << (int) getStatus(0xff);
    //refresh_GUI();
    //gui_set_quarzfrequenz_Label();
    //bootPIC();
    //refresh_GUI();
    //progZeiger = 0x100;
    //gui_set_pc_Label();

    dataSpeicher[0][5] = 0x01;
    dataSpeicher[0][5] = dataSpeicher[0][5] ^ ( 1u << (7-4) ); // setze bit auf gewuenschten wert
    qDebug() <<  dataSpeicher[0][5];

    //dataSpeicher[0][5] = 0x09;
    dataSpeicher[0][5] = dataSpeicher[0][5] ^ 1u; // setze bit auf gewuenschten wert
    qDebug() <<  dataSpeicher[0][5];

    refresh_GUI();

}



void MainWindow::on_reset_laufzeit_button_clicked()
{
    progTime = 0;
    takte = 0;
    gui_set_laufzeit_Label();
    refresh_GUI();
}

void MainWindow::on_quarzfrequenz_input_textChanged(const QString &arg1)
{
    double wert = arg1.toDouble();
    quarzTakt = wert;
    gui_set_quarzfrequenz_Label();
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

void MainWindow::refreshDataSpeicher() {
    //gui_set_dataSpeicher_table(i, j, dataSpeicher[][j])

    int wert;
    //string sWert;
    //stringstream stream;
    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 8; j++) {

            //stream.str("");
            //stream.clear();

            if(i < 16) {
                // berechnung der register pro zelle mit hilfe der zeile
                wert = dataSpeicher[0][(8*i) + j];
                gui_set_dataSpeicher_table(i, j, toHexString(wert));
            } else {
                // berechnung der register pro zelle mit hilfe der zeile, für bank 2 wieder zurückgesetzt auf den start = 0
                wert = dataSpeicher[1][(8*(i-16)) + j];
                gui_set_dataSpeicher_table(i, j, toHexString(wert));
            }
        }
    }
}

void MainWindow::refresh_GUI(){
    //qDebug() << "refresh GUI";
    gui_check_wdt_aktiv();
    gui_set_quarzfrequenz_Label();
    gui_set_progTime_Label();
    gui_set_laufzeit_Label();
    gui_set_wReg_Label();
    gui_set_fsr_Label();
    gui_set_pcl_Label();
    gui_set_pcLath_Label();
    gui_set_status_Label();
    gui_set_pc_Label();
    gui_set_stackpointer_Label();
    gui_set_stack_elements();
    gui_set_vt_Label();
    gui_set_wdt_Label();
    gui_set_irp_Label();
    gui_set_rp1_Label();
    gui_set_rp0_Label();
    gui_set_t0_Label();
    gui_set_pd_Label();
    gui_set_z_Label();
    gui_set_dc_Label();
    gui_set_c_Label();
    gui_set_option_Label();
    gui_set_rbp_Label();
    gui_set_intedg_Label();
    gui_set_t0cs_Label();
    gui_set_t0se_Label();
    gui_set_psa_Label();
    gui_set_ps2_Label();
    gui_set_ps1_Label();
    gui_set_ps0_Label();
    gui_set_intcon_Label();
    gui_set_gie_Label();
    gui_set_pie_Label();
    gui_set_t0ie_Label();
    gui_set_inte_Label();
    gui_set_rbie_Label();
    gui_set_t0if_Label();
    gui_set_intf_Label();
    gui_set_rbif_Label();
    gui_set_pfad_Label();
    gui_set_laeuft_label();
    fillBox();
    refreshDataSpeicher();
    gui_set_wdt_reset_label();
    string sQuarzTakt = doubleToString(quarzTakt);
    ui->quarzfrequenz_input->setText(string_to_QString(sQuarzTakt));

}





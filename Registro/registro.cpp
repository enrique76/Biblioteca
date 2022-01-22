#include "registro.h"
#include "ui_registro.h"
#include<time.h>
#include<QTimer>
#include<QDateTime>

registro::registro(QWidget *parent) :QDialog(parent),ui(new Ui::registro){
    ui->setupUi(this);

    // nacionalidades
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/mexico.png"),"MEX");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/argentina.png"),"ARG");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/alemania.png"),"DEU");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/canada.png"),"CAN");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/china.png"),"CHN");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/colombia.png"),"COL");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/espana.png"),"ESP");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/francia.png"),"FRA");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/estados-unidos-de-america.png"),"USA");
    ui->Nacionalidad->addItem(QIcon(":/new/prefix1/iconos/brazil.png"),"BRA");

    // frecha - hora

    time_t now = time(0);
    tm* time = localtime(&now);
    QString dia,mes,year,hora,min,sec;

    hora = QString::number(time->tm_hour);
    min = QString::number(time->tm_min);
    sec = QString::number(time->tm_sec);
    dia = QString::number(time->tm_mday);
    mes = QString::number(time->tm_mon+1);
    year = QString::number(1900 + time->tm_year);

    QString texto;
    texto+=dia+"/"+mes+"/"+year+" "+hora+":"+min+":"+sec;

    ui->fechahora->setText(texto);


}



registro::~registro(){
    delete ui;
}

QString registro::creacion(){
    return " ";
}

void registro::pasarDatos(){

}

void registro::on_agregar_clicked(){
    V = true;
    close();
}

void registro::on_cancelar_clicked(){
    close();
}

QString registro::getNombres(){
    return ui->nombres->text()+" "+ui->apellidos->text();
}

QString registro::getCorreo(){
    return ui->correo->text();
}

QString registro::getTelefono(){
    return ui->telefono->text();
}

QString registro::getNacionalidad(){
    return ui->Nacionalidad->currentText();
}

QString registro::getNacimiento(){
    return ui->nacimiento->text();
}

QString registro::getCURP(){
    return ui->curp->text();
}

QString registro::getFechaHora(){
    return ui->fechahora->text();
}


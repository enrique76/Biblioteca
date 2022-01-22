#include "buscar.h"
#include "ui_buscar.h"
#include<QDebug>
#include<QMessageBox>

Buscar::Buscar(QWidget *parent) :QDialog(parent),ui(new Ui::Buscar){
    ui->setupUi(this);

    for(int i=0;i<Tablas.size();++i){
        ui->tabla->addItem(Tablas.at(i));
    }

//    mDatabase = QSqlDatabase::addDatabase("QMYSQL");
//    mDatabase.setHostName("localhost");
//    mDatabase.setDatabaseName("pruebaplatzi");
//    mDatabase.setPort(3306);
//    mDatabase.setUserName("root");
//    mDatabase.setPassword("6641164177");

//    if(!mDatabase.open()){
//        QMessageBox::critical(this,"Error",mDatabase.lastError().text());
//    }

    q = new QSqlQueryModel();

}

Buscar::~Buscar(){
    delete ui;
}

void Buscar::on_ir_clicked(){
    Query = "SELECT * FROM " + ui->tabla->currentText() + " WHERE " + ui->campo->currentText() + " LIKE " + "'" + ui->dato->text() +"%';";

    q->setQuery(Query);

    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
    }
    else{
        ui->Datos->setModel(q);
    }
}

void Buscar::on_tabla_currentTextChanged(const QString &arg1){
    ui->campo->clear();

    if(arg1 == "transactions"){
        for(int i=0;i<Transacciones.size();++i){
            ui->campo->addItem(Transacciones.at(i));
        }
    }
    else if(arg1 == "clients"){
        for(int i=0;i<Clientes.size();++i){
            ui->campo->addItem(Clientes.at(i));
        }
    }
    else if(arg1 == "books"){
        for(int i=0;i<Libros.size();++i){
            ui->campo->addItem(Libros.at(i));
        }
    }
    else if(arg1 == "authors"){
        for(int i=0;i<Autores.size();++i){
            ui->campo->addItem(Autores.at(i));
        }
    }
}





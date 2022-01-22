#include "query.h"
#include "ui_query.h"
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QCompleter>

Query::Query(QWidget *parent) : QDialog(parent),ui(new Ui::Query){
    ui->setupUi(this);

    q = new QSqlQueryModel();

    ui->label->setText("MYSQL>> ");

    c = new QCompleter(historia,this);

    ui->sentencia->setCompleter(c);

}

Query::~Query(){
    delete ui;
}

void Query::on_sentencia_editingFinished(){
    query = ui->sentencia->text();
    q->setQuery(query);

    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
    }
    else{
        ui->datos->setModel(q);
        historia<<query;
        historia.removeDuplicates();
        ui->sentencia->clear();
        c = new QCompleter(historia,this);
        ui->sentencia->setCompleter(c);
    }
}



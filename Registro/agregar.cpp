#include "agregar.h"
#include "ui_agregar.h"
#include<QMessageBox>
#include<QDebug>
#include<time.h>
#include<QCompleter>
#include<QDate>

Agregar::Agregar(QWidget *parent) :QDialog(parent),ui(new Ui::Agregar){
    ui->setupUi(this);

    ui->area->setCurrentIndex(0);

    time_t now = time(0);
    tm* time = localtime(&now);
    QDate d(1900+time->tm_year,time->tm_mon+1,time->tm_mday);

    ui->birthdate->setDate(d);


    q = new QSqlQueryModel();

    q->setQuery("SELECT name FROM clients;");

    for(int i=0;i<q->rowCount();++i){
        clientes.append(q->index(i,0).data().toString());
    }



    c = new QCompleter(clientes,this);

    ui->cliente->setCompleter(c);

    q->setQuery("SELECT title FROM books;");

    for(int i=0;i<q->rowCount();++i){
        titulos.append(q->index(i,0).data().toString());
    }



    c = new QCompleter(titulos,this);


    ui->titulo->setCompleter(c);

    q->setQuery("SELECT email FROM clients;");

    for(int i=0;i<q->rowCount();++i){
        correos.append(q->index(i,0).data().toString());
    }


}

void Agregar::index(int i){
    ui->area->setCurrentIndex(i);
}

Agregar::~Agregar()
{
    delete ui;
}

bool Agregar::Accion()
{
    return cambio;
}



void Agregar::on_agregar_clicked(){
    if(ui->area->currentIndex() == 0){
        if(!titulos.contains(ui->titulo->text())){
            QMessageBox::critical(this,"Datos Incorrectos","El titulo '"+ui->titulo->text()+"' no se encuentra en nuestra base de datos");
        }
        else if(!clientes.contains(ui->cliente->text())){
            QMessageBox::critical(this,"Datos Incorrectos","El clientes '"+ui->cliente->text()+" ' aun no ha sido registrado");
        }
        else if(ui->type->currentText().isEmpty()){
             QMessageBox::critical(this,"Datos Incorrectos","Elija un tipo de Transaccion");
        }
        else{

            q->setQuery("SELECT book_id FROM books WHERE title = '"+ui->titulo->text()+"';");

            Query = "INSERT INTO transactions(book_id,client_id,type,finished) VALUES("+q->index(0,0).data().toString()+",";



            q->setQuery("select client_id from clients where name = '"+ui->cliente->text()+"';");

            Query += q->index(0,0).data().toString()+",'"+ui->type->currentText()+"',";

            if(ui->finished->isChecked()){
                Query += "1);";
            }
            else{
                Query += "0);";
            }



            q->setQuery(Query);

            if(q->lastError().isValid()){
                QMessageBox::critical(this,"Error",q->lastError().text());
            }
            else{
                cambio = true;
                close();
            }

        }
    }
    else if(ui->area->currentIndex() == 1){
        if(ui->name->text().isEmpty()){
            QMessageBox::critical(this,"Error","El nombre es obligatorio");
        }
        else if(correos.contains(ui->email->text())){
            QMessageBox::critical(this,"Error","El correo ya esta registrado");
        }
        else if(ui->email->text().isEmpty()){
            QMessageBox::critical(this,"Error","El correo es un compo obligatorio");
        }
        else{

            // INSERT INTO clients(name,email,birthdate,gender,active) VALUES('Argelia Cruz Acosta','argelia@gmail.com','1999-04-21','F',1);

            Query = "INSERT INTO clients(name,email,birthdate,gender,active) VALUES('"+ui->name->text()+"','"+ui->email->text()+"','"+ui->birthdate->text()+"','"+ui->gender->currentText()+"',";

            if(ui->active->isChecked()){
                Query += "1);";
            }
            else{
                Query += "0);";
            }

            q->setQuery(Query);

            if(q->lastError().isValid()){
                QMessageBox::critical(this,"Error",q->lastError().text());
            }
            else{
                cambio = true;
                close();
            }
        }
    }
    else if(ui->area->currentIndex() == 2){
        if(ui->author_id->text().isEmpty()){
            QMessageBox::critical(this,"Error","El campo del autor es necesario");
        }
        else if(!autores.contains(ui->author_id->text())){
            QMessageBox::critical(this,"Error","El Autor "+ui->author_id->text()+" no ha sido registrado, favor de hacerlo");
        }
        else if(ui->title->text().isEmpty()){
            QMessageBox::critical(this,"Error","El titulo es necesario");
        }
        else if(ui->language->text().isEmpty()){
            QMessageBox::critical(this,"Error","Favor de Agregar el Lenguaje del libro");
        }
        else{

            Query = "SELECT author_id FROM authors WHERE name = '"+ui->author_id->text()+"'";

            q->setQuery(Query);


            Query = "INSERT INTO books(author_id,title,year,language,cover_url,price,copies,description) VALUES("+q->index(0,0).data().toString()+",'";
            Query += ui->title->text()+"','"+ui->year->text()+"','"+ui->language->text()+"',";

            if(ui->cover_url->text().isEmpty()){
                Query += "NULL,'";
            }
            else{
                Query += "'"+ui->cover_url->text()+"',";
            }

            Query += QString::number(ui->price->value())+"','"+QString::number(ui->copias->value());

            if(ui->desciption->text().isEmpty()){
                Query += "',NULL);";
            }
            else{
                Query += "','"+ui->desciption->text()+"');";
            }




            qDebug()<<Query;

            q->setQuery(Query);

            if(q->lastError().isValid()){
                QMessageBox::critical(this,"Error",q->lastError().text());
            }
            else{
                cambio = true;
                close();
            }
        }

    }
    else{
        Query = "SELECT name FROM authors;";

        q->setQuery(Query);
        for(int i=0;i<q->rowCount();++i){
            autores.append(q->index(i,0).data().toString());
        }

        if(ui->name_2->text().isEmpty()){
            QMessageBox::critical(this,"Datos Incompletos","Hay datos ecenciales que no has ingresado");
        }
        else if(autores.contains(ui->name_2->text())){
            QMessageBox::critical(this,"Error","Este autor ya se ingreso");
        }
        else{

            Query = "INSERT INTO authors(name,nationality) VALUES('"+ui->name_2->text()+"','"+ui->nationality->currentText()+"');";

            if(q->lastError().isValid()){
                QMessageBox::critical(this,"Error",q->lastError().text());
            }
            else{
                cambio = true;
                close();
            }
        }
    }
}

void Agregar::on_cancelar_clicked(){
    close();
}

void Agregar::on_finished_stateChanged(int arg1){
    if(ui->finished->isChecked()){
        ui->finished->setText("TRUE");
    }
    else{
        ui->finished->setText("FALSE");
    }
}

void Agregar::on_active_stateChanged(int arg1){
    if(ui->active->isChecked()){
        ui->active->setText("TRUE");
    }
    else{
        ui->active->setText("FALSE");
    }
}


void Agregar::on_area_currentChanged(int arg1){
        if(arg1 == 2){
            Query = "SELECT name FROM authors";

            q->setQuery(Query);
            autores.clear();
            for(int i=0;i<q->rowCount();++i){
                autores.append(q->index(i,0).data().toString());
            }

            c = new QCompleter(autores,this);

            ui->author_id->setCompleter(c);
        }
}


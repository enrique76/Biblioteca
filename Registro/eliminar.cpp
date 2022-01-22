#include "eliminar.h"
#include "ui_eliminar.h"
#include<QSqlError>
#include<QMessageBox>
#include<QDebug>

eliminar::eliminar(QWidget *parent) : QDialog(parent), ui(new Ui::eliminar){
    ui->setupUi(this);

    q = new QSqlQueryModel();

    ui->area->setCurrentIndex(0);

}

eliminar::~eliminar(){
    delete ui;
}

void eliminar::on_e_clicked(){
    QString aux;

    for(int i=0;i<windowTitle().size()-1;++i){
        aux += windowTitle().at(i);
    }




        QMessageBox::StandardButton m = QMessageBox::question(this,"Eliminar","Deseas eliminar esta informacion?",QMessageBox::Yes | QMessageBox::No);

        if(m == QMessageBox::Yes){
            query = "DELETE FROM "+windowTitle()+" WHERE "+aux+"_id = "+ui->spinBox->text()+";";
            q->setQuery(query);

            qDebug()<<query;

            if(q->lastError().isValid()){
                QMessageBox::critical(this,"Eliminar","Los datos NO se eliminaron corestamentes");
            }
            else{
                QMessageBox::information(this,"Eliminar","Los datos se eliminaron corestamentes");
                cambio = true;
            }

            close();
        }
        else if(m == QMessageBox::No){
            QMessageBox::information(this,"Eliminar","No se elimino ningun dato");
            close();
        }

}

void eliminar::on_ed_clicked(){
    QString aux;

    for(int i=0;i<windowTitle().size()-1;++i){
        aux += windowTitle().at(i);
    }

    QMessageBox::StandardButton m = QMessageBox::question(this,"Editar","Desea cambiar "+ui->columna->currentText()+" de ID #"+ui->spinBox_2->text()+" por "+ui->lineEdit->text()+" en la tabla "+windowTitle()+"?",QMessageBox::Yes | QMessageBox::No);

    if(m == QMessageBox::Yes){
        query = "UPDATE "+windowTitle();
        query += " SET "+ui->columna->currentText();
        query += " = '"+ui->lineEdit->text();
        query += "' WHERE "+aux+"_id = "+ui->spinBox_2->text()+";";
        q->setQuery(query);

        qDebug()<<query;

        if(q->lastError().isValid()){
            QMessageBox::critical(this,"Editar","Los datos NO se Editaron corestamentes");
        }
        else{
            QMessageBox::information(this,"Editar","Los datos se Editaron corestamentes");
            cambio = true;
        }

        close();
    }
    else if(m == QMessageBox::No){
        QMessageBox::information(this,"Editar","No se Edito ningun dato");
        close();
    }


}

void eliminar::on_spinBox_editingFinished()
{


    if(windowTitle() == "transactions"){
        query = "select t.transaction_id as ID,c.name as Cliente,b.title as Titulo,"
                "a.name as Autor,t.type as Estado, t. created_at as Creacion,t. modified_at as Modificado,t.finished as Finalizado"
                " from transactions as t "
                "join books as b on t.book_id = b.book_id join clients as c on t.client_id = c.client_id "
                "join authors as a on b.author_id = a.author_id WHERE t.transaction_id = "+ui->spinBox->text()+" limit 1;";
    }
    else if(windowTitle() == "clients"){
        query = "SELECT client_id as ID,name as Nombre, email as Correo,birthdate as Cumpleaños,gender as Genero"
                ",active as Activo, created_at as Creacion FROM clients WHERE client_id = "+ui->spinBox->text()+" limit 1;";
    }
    else if(windowTitle() == "books"){
        query = "select b.book_id as ID ,b.title as Titulo,a.name as Autor,b.year as Año, b.language as Lenguaje,b.price as Precio,";
        query += "b.sellable as Vendido, b.copies as Copias, b.description as Descripccion from books as b ";
        query += "join authors as a on b.author_id = a.author_id WHERE b.book_id = "+ui->spinBox->text()+"; limit 1;";
    }
    else{
        query = "SELECT author_id as ID,name as Nombre, nationality as Nacionalidad FROM authors WHERE author_id = "+ui->spinBox->text()+" limit 1;";
    }


    //query = "DELETE FROM "+windowTitle()+" WHERE "+aux+"_id = "+ui->spinBox->text()+";";

    q->setQuery(query);

    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
        close();
    }
    else{
        ui->datos->setModel(q);
        ui->e->setEnabled(true);
    }
}

void eliminar::inicio(QString i){
    setWindowTitle(i);

        QString aux;

        for(int i=0;i<windowTitle().size()-1;++i){
            aux += windowTitle().at(i);
        }

        query = "SELECT * FROM "+windowTitle()+";";

    q->setQuery(query);

    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
        close();
    }
    else{
        ui->datos->setModel(q);
        ui->datos_2->setModel(q);
    }

    if(windowTitle() == "transactions"){
        QStringList l;

        l << "transaction_id" << "book_id" << "client_id" << "type" << "finished";

        ui->columna->addItems(l);
    }
    else if(windowTitle() == "clients"){
        QStringList l;

        l << "client_id" << "name" << "email" << "birthdate" << "gender" << "active";

        ui->columna->addItems(l);
    }
    else if(windowTitle() == "books"){
        QStringList l;

        l << "book_id" << "author_id" << "title" << "year" << "language" << "cover_url" << "price" << "sellable" << "copies" << "description";

        ui->columna->addItems(l);
    }
    else{

        QStringList l;

        l << "author_id" << "name" << "nationality";

        ui->columna->addItems(l);
    }
}

void eliminar::Cambio(){
    ui->area->setCurrentIndex(1);
}

void eliminar::setTablas(QStringList l)
{
    ui->columna->addItems(l);
}

bool eliminar::Accion()
{
    return cambio;
}



void eliminar::on_datos_2_clicked(const QModelIndex &index){
    nuevoDato = index.data().toString();



    qDebug()<<nuevoDato;
}



void eliminar::on_lineEdit_textEdited(const QString &arg1)
{
    ui->ed->setEnabled(true);
}





void eliminar::on_spinBox_2_editingFinished()
{

    QString aux;

    for(int i=0;i<windowTitle().size()-1;++i){
        aux += windowTitle().at(i);
    }

    query = "SELECT * FROM "+windowTitle()+" WHERE "+aux+"_id = "+ui->spinBox_2->text();


    //query = "DELETE FROM "+windowTitle()+" WHERE "+aux+"_id = "+ui->spinBox->text()+";";

    q->setQuery(query);

    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
        close();
    }
    else{
        ui->datos_2->setModel(q);
        //ui->ed->setEnabled(true);
    }
}


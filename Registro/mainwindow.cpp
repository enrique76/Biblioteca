#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "buscar.h"
#include "agregar.h"
#include "Query.h"
#include "eliminar.h"
#include "login.h"
#include<QMessageBox>
#include<QSqlError>
#include<QSqlTableModel>
#include<QDebug>
#include<QTimer>
#include<QDateTime>
#include<chrono>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->Datos->setAlternatingRowColors(true);



    ui->campo->addItems(Transacciones);

    time_t now = time(0);
    tm* time = localtime(&now);
    QString dia,mes,year;

    QStringList meses;
    meses<<"ENERO"<<"FEBRERO"<<"MARZO"<<"ABRIL"<<"MAYO"<<"JUNIO"<<"JULIO"<<"AGOSTO";
    meses<<"SEPTIEMBRE"<<"OCTUBRE"<<"NOVIEMBRE"<<"DICIEMBRE";

    if(time->tm_mday < 10){
        dia = "0"+QString::number(time->tm_mday);
    }
    else{
        dia = QString::number(time->tm_mday);
    }

    mes = meses.at(time->tm_mon);
    year = QString::number(1900 + time->tm_year);

    QString texto;
    texto+=dia+"/"+mes+"/"+year;

    ui->fecha->setText(texto);

   conectar();

    q = new QSqlQueryModel();

    Q = "SELECT t.transaction_id AS ID,c.name AS NOMBRE,b.title AS TITULO,a.name AS AUTOR,t.type AS ESTADO,t.created_at AS CREACION "
        "FROM transactions AS t "
        "JOIN books AS b ON t.book_id = b.book_id "
        "JOIN clients AS c ON t.client_id = c.client_id "
        "JOIN authors AS a ON b.author_id = a.author_id;";



    q->setQuery(Q);
    ui->Datos->setModel(q);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
}

void MainWindow::PasarDatos(QString Q){
    q->setQuery(Q);
    ui->Datos->setModel(q);
}

void MainWindow::showTime(){
    QTime time = QTime::currentTime();

    ui->hora->setText(time.toString(" hh : mm : ss"));
}

MainWindow::~MainWindow()
{
    mDatabase.close();
    delete ui;
}

void MainWindow::Recargar(){
    ui->actionRecargar->setIcon(QIcon(":/new/prefix1/iconos/recargarNotificacion.png"));
}

void MainWindow::setTipoUsuario(QString t)
{
    tipoUsuario = t;

    if(t == "ADMINISTRADOR"){
        ui->actionQuery->setEnabled(true);
        ui->actionQuery->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->actionAgregar->setEnabled(true);
        ui->actionEditar->setEnabled(true);
        ui->actionEliminar->setEnabled(true);
        ui->actionRecargar->setEnabled(true);
        ui->actionExcel->setEnabled(true);
        ui->actionPDF->setEnabled(true);
        ui->actionWord->setEnabled(true);
    }
    else if(t == "EMPLEADO"){
        ui->actionQuery->setEnabled(false);
    }
    else if(t == "USUARIO" || t == "INVITADO"){
        on_pushButton_2_clicked();
        ui->actionQuery->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->actionAgregar->setEnabled(false);
        ui->actionEditar->setEnabled(false);
        ui->actionEliminar->setEnabled(false);
        ui->actionRecargar->setEnabled(false);
        ui->actionExcel->setEnabled(false);
        ui->actionPDF->setEnabled(false);
        ui->actionWord->setEnabled(false);
    }

    conectar();

}

void MainWindow::conectar()
{
    mDatabase = QSqlDatabase::addDatabase("QMYSQL");
    mDatabase.setHostName("localhost");
    mDatabase.setDatabaseName("pruebaplatzi");
    mDatabase.setPort(3306);
    mDatabase.setUserName("root");
    mDatabase.setPassword("(contraseña)");

    if(!mDatabase.open()){
        QMessageBox::critical(this,"Error",mDatabase.lastError().text());
    }
}

void MainWindow::on_actionTablas_triggered(){
    ui->barra->setVisible(!ui->barra->isVisible());
}

void MainWindow::on_pushButton_clicked(){
    //Transacciones
    auto inicio = std::chrono::system_clock::now();

    ui->TituloTabla->setText("Transacciones");

    ui->campo->clear();

    ui->campo->addItems(Transacciones);
    estadoTablas = 0;

    conectar();

    Q = "SELECT t.transaction_id AS ID,c.name AS NOMBRE,b.title AS TITULO,a.name AS AUTOR,t.type AS ESTADO,t.created_at AS CREACION "
        "FROM transactions AS t "
        "JOIN books AS b ON t.book_id = b.book_id "
        "JOIN clients AS c ON t.client_id = c.client_id "
        "JOIN authors AS a ON b.author_id = a.author_id; ";

        PasarDatos(Q);


    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
    }



    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_pushButton_4_clicked(){
    //clientes
    auto inicio = std::chrono::system_clock::now();

    ui->TituloTabla->setText("Clientes");

    ui->campo->clear();

    ui->campo->addItems(Clientes);
    estadoTablas = 1;

    conectar();

        Q = "SELECT client_id as ID,name as Nombre, email as Correo,birthdate as Cumpleaños,gender as Genero"
                ",active as Activo, created_at as Creacion FROM clients";

        PasarDatos(Q);

    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
    }




    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));

}

void MainWindow::on_pushButton_2_clicked(){
    //libros

    ui->TituloTabla->setText("Libros");

    conectar();

    Q = "select b.book_id as ID ,b.title as Titulo,a.name as Autor,b.year as Año, b.language as Lenguaje,b.price as Precio,";
    Q += "b.sellable as Vendido, b.copies as Copias, b.description as Descripccion from books as b ";
    Q += "join authors as a on b.author_id = a.author_id;";

    ui->campo->clear();

    ui->campo->addItems(Libros);
    estadoTablas = 2;

    PasarDatos(Q);

    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
    }




}

void MainWindow::on_pushButton_3_clicked(){
    //autores
    ui->TituloTabla->setText("Autores");

    conectar();

    Q = "SELECT author_id as ID,name as Nombre, nationality as Nacionalidad FROM authors;";

    ui->campo->clear();

    ui->campo->addItems(Autores);
    estadoTablas = 3;

    PasarDatos(Q);

    if(q->lastError().isValid()){
        QMessageBox::critical(this,"Error",q->lastError().text());
    }



}

void MainWindow::on_actionAgregar_triggered(){
    Agregar a;

    a.index(estadoTablas);

        if(estadoTablas == 0){
            a.setWindowIcon(QIcon(":/new/prefix1/iconos/transaccion.png"));
            a.setWindowTitle("Transaccion");
        }
        else if(estadoTablas == 1){
            a.setWindowIcon(QIcon(":/new/prefix1/iconos/jefe.png"));
            a.setWindowTitle("Clientes");
        }
        else if(estadoTablas == 2){
            a.setWindowIcon(QIcon(":/new/prefix1/iconos/libro.png"));
            a.setWindowTitle("Libros");
        }
        else{
            a.setWindowIcon(QIcon(":/new/prefix1/iconos/escritor.png"));
            a.setWindowTitle("Autores");
        }

    a.exec();

    if(a.Accion()){
        ui->actionRecargar->setIcon(QIcon(":/new/prefix1/iconos/recargarNotificacion.png"));
    }
}

void MainWindow::on_actionVer_triggered(){
    Buscar b;

    b.exec();
}

void MainWindow::on_actionRecargar_triggered(){
    auto inicio = std::chrono::system_clock::now();

    ui->actionRecargar->setIcon(QIcon(":/new/prefix1/iconos/recargar.png"));


    PasarDatos(Q);

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}


void MainWindow::on_campo_currentIndexChanged(int index){

}

void MainWindow::on_az_clicked(){
    auto inicio = std::chrono::system_clock::now();

    switch (estadoTablas) {
        case 0:

        Q = "select t.transaction_id as ID,c.name as Cliente,b.title as Titulo,"
                "a.name as Autor,t.type as Estado, t. created_at as Creacion,t. modified_at as Modificado,t.finished as Finalizado"
                " from transactions as t "
                "join books as b on t.book_id = b.book_id join clients as c on t.client_id = c.client_id "
                "join authors as a on b.author_id = a.author_id order by ";

        switch(ui->campo->currentIndex()){
            case 0:
                Q += "t.transaction_id;";
            break;
            case 1:
                Q += "c.name;";
            break;
            case 2:
                Q += "b.title;";
            break;
            case 3:
                Q += "a.name;";
            break;
            case 4:
                Q += "t.type;";
            break;
            case 5:
                Q += "t.created_at;";
            break;
            case 6:
                Q += "t.modified_at;";
            break;
            case 7:
                Q += "t.finished;";
            break;
        }
        PasarDatos(Q);

        break;
        case 1:
        Q = "SELECT client_id as ID,name as Nombre, email as Correo,birthdate as Cumpleaños,gender as Genero"
                ",active as Activo, created_at as Creacion FROM clients order by "+ui->campo->currentText()+";";

        PasarDatos(Q);
        break;
        case 2:
            Q = "select b.book_id as ID ,b.title as Titulo,a.name as Autor,b.year as Año, b.language as Lenguaje,b.price as Precio,";
            Q += "b.sellable as Vendido, b.copies as Copias, b.description as Descripccion from books as b ";
            Q += "join authors as a on b.author_id = a.author_id ORDER BY "+ui->campo->currentText()+";";

            PasarDatos(Q);

        break;
        case 3:
            Q = "SELECT author_id as ID,name as Nombre, nationality as Nacionalidad FROM authors ORDER BY "+ui->campo->currentText()+";";
            PasarDatos(Q);
        break;
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}


void MainWindow::on_za_clicked(){
    auto inicio = std::chrono::system_clock::now();

    switch (estadoTablas) {
        case 0:

        Q = "select t.transaction_id as ID,c.name as Cliente,b.title as Titulo,"
                "a.name as Autor,t.type as Estado, t. created_at as Creacion,t. modified_at as Modificado,t.finished as Finalizado"
                " from transactions as t "
                "join books as b on t.book_id = b.book_id join clients as c on t.client_id = c.client_id "
                "join authors as a on b.author_id = a.author_id order by ";

        switch(ui->campo->currentIndex()){
            case 0:
                Q += "t.transaction_id desc;";
            break;
            case 1:
                Q += "c.name desc;";
            break;
            case 2:
                Q += "b.title desc;";
            break;
            case 3:
                Q += "a.name desc;";
            break;
            case 4:
                Q += "t.type desc;";
            break;
            case 5:
                Q += "t.created_at desc;";
            break;
            case 6:
                Q += "t.modified_at desc;";
            break;
            case 7:
                Q += "t.finished desc;";
            break;
        }


        PasarDatos(Q);

        break;
        case 1:
        Q = "SELECT client_id as ID,name as Nombre, email as Correo,birthdate as Cumpleaños,gender as Genero"
                ",active as Activo, created_at as Creacion FROM clients order by "+ui->campo->currentText()+" desc;";

        PasarDatos(Q);
        break;
        case 2:
            Q = "select b.book_id as ID ,b.title as Titulo,a.name as Autor,b.year as Año, b.language as Lenguaje,b.price as Precio,";
            Q += "b.sellable as Vendido, b.copies as Copias, b.description as Descripccion from books as b ";
            Q += "join authors as a on b.author_id = a.author_id ORDER BY "+ui->campo->currentText()+" desc;";

            PasarDatos(Q);
        break;
        case 3:
        Q = "SELECT author_id as ID,name as Nombre, nationality as Nacionalidad FROM authors ORDER BY "+ui->campo->currentText()+" DESC;";
        PasarDatos(Q);
        break;
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionQuery_triggered(){
    Query mq;

    mq.exec();
}

void MainWindow::on_actionEliminar_triggered(){
    eliminar e;

    e.inicio(Tablas.at(estadoTablas));



    e.exec();

    if(e.Accion()){
        ui->actionRecargar->setIcon(QIcon(":/new/prefix1/iconos/recargarNotificacion.png"));
    }
}

void MainWindow::on_actionEditar_triggered(){
    eliminar e;

    e.Cambio();
    e.inicio(Tablas.at(estadoTablas));


    e.setWindowIcon(QIcon(":/new/prefix1/iconos/servidor.png"));

    e.exec();

    if(e.Accion()){
        ui->actionRecargar->setIcon(QIcon(":/new/prefix1/iconos/recargarNotificacion.png"));
    }

}

void MainWindow::on_actionUsuario_triggered()
{
    login l;

    l.exec();

    setTipoUsuario(l.getTipoUsuario());

    setWindowTitle("Biblioteca - "+l.getTipoUsuario());
}


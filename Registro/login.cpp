#include "login.h"
#include "ui_login.h"
#include<QDebug>
#include<QMessageBox>

login::login(QWidget *parent) : QDialog(parent), ui(new Ui::login){
    ui->setupUi(this);

    ui->area->setCurrentIndex(0);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("login");
    db.setPort(3306);
    db.setPassword("(contraseña)");
    db.setUserName("root");

    if(!db.open()){
        QMessageBox::critical(this,"Error",db.lastError().text());
        close();
    }

    query = new QSqlQueryModel();

    query->setQuery("SELECT password FROM users WHERE user_id = '2';");

    ConAdmi = query->index(0,0).data().toString();

    query->setQuery("SELECT typeuser FROM users WHERE user_id = '2'");

    typeuser = query->index(0,0).data().toString();

    ui->regresar->setIcon(QIcon(":/new/prefix1/iconos/regreso.png"));
}

login::~login()
{
    delete ui;
}

QString login::getTipoUsuario()
{
    return typeuser;
}

void login::on_verCon_clicked()
{
    if(ui->con->echoMode() == 2){
        ui->con->setEchoMode(QLineEdit::Normal);
        ui->verCon->setIcon(QIcon(":/new/prefix1/iconos/visibilidad.png"));
    }
    else{
        ui->con->setEchoMode(QLineEdit::Password);
        ui->verCon->setIcon(QIcon(":/new/prefix1/iconos/ojo-abierto.png"));
    }
}

void login::on_verCon_2_clicked()
{
    if(ui->con_2->echoMode() == 2){
        ui->con_2->setEchoMode(QLineEdit::Normal);
        ui->verCon_2->setIcon(QIcon(":/new/prefix1/iconos/visibilidad.png"));
    }
    else{
        ui->con_2->setEchoMode(QLineEdit::Password);
        ui->verCon_2->setIcon(QIcon(":/new/prefix1/iconos/ojo-abierto.png"));
    }
}

void login::on_pushButton_clicked()
{
    Query = "select count(email) from users where email = '"+ui->correo->text()+"';";

    query->setQuery(Query);

    if(ui->con->text().compare(ui->con_2->text()) != 0){
        QMessageBox::critical(this,"Error","Contraseñas no coencidentes");
    }
    else if(ui->nombre->text().isEmpty() || ui->nombreUsuario->text().isEmpty() || ui->correo->text().isEmpty() || ui->con->text().isEmpty() || ui->con_2->text().isEmpty()){
        QMessageBox::critical(this,"Error","Faltan datos");

    }
    else if( query->index(0,0).data().toInt() == 1){
        QMessageBox::critical(this,"Error","Este Correo ya esta registrado");
    }
    else{


        // insert into users(name,email,username,password,typeuser,gender) values('Luis Enrique Cruz Acosta','enrique.cruz9@uabc.edu.mx','ROBILART','6641164177l','ADMINISTRADOR','M');

        Query = "INSERT INTO users(name,email,username,password,typeuser,gender) VALUES('";
        Query += E(ui->nombre->text()) + "','";
        Query += E(ui->correo->text()) + "','";
        Query += E(ui->nombreUsuario->text()) + "','";
        Query += E(ui->con->text()) + "','";
        Query += ui->tipoUsuario->currentText() + "','";
        Query += ui->gender->currentText() + "');";

        query->setQuery(Query);

        if(query->lastError().isValid()){
            QMessageBox::critical(this,"Error",query->lastError().text()+"\n\nVuelva a intentarlo");
        }
        else{
            QMessageBox::information(this,"Registro","!Listo");
            ui->area->setCurrentIndex(0);
        }

        ui->sesioncon->clear();
        ui->sesioncorreo->clear();
    }
}

QString login::E(QString e)
{
    QString en;

    for(int i=0;i<e.size();++i){
        en += char(int(e.at(i).toLatin1())+3);
    }


    return en;
}

QString login::dE(QString e)
{
    QString en;

    for(int i=0;i<e.size();++i){
        en += char(int(e.at(i).toLatin1())-3);
    }

    return en;
}

void login::on_pushButton_4_clicked()
{
    ui->area->setCurrentIndex(1);
}

void login::on_sesionvercon_clicked()
{
    if(ui->sesioncon->echoMode() == 2){
        ui->sesioncon->setEchoMode(QLineEdit::Normal);
        ui->sesionvercon->setIcon(QIcon(":/new/prefix1/iconos/visibilidad.png"));
    }
    else{
        ui->sesioncon->setEchoMode(QLineEdit::Password);
        ui->sesionvercon->setIcon(QIcon(":/new/prefix1/iconos/ojo-abierto.png"));
    }
}

void login::on_sesionEntrar_clicked()
{
    Query = "SELECT COUNT(email) FROM users WHERE email = '"+E(ui->sesioncorreo->text())+"';";

    query->setQuery(Query);

    if(query->index(0,0).data().toInt() == 0){
        QMessageBox::critical(this,"Error","El correo de "+ui->sesioncorreo->text()+" no esta registrado\nFavor de registrarse");
    }
    else{
        Query = "SELECT COUNT(password) FROM users WHERE password = '"+E(ui->sesioncon->text())+"' AND email = '"+E(ui->sesioncorreo->text())+"';";

        query->setQuery(Query);
        if(query->index(0,0).data().toInt() == 0){
            QMessageBox::critical(this,"Error","Contraseña incorrecta");
        }
        else{

            Query = "select typeuser from users where email = '"+E(ui->sesioncorreo->text())+"';";
            qDebug()<<Query;
            query->setQuery(Query);
            typeuser = query->index(0,0).data().toString();
            qDebug()<<typeuser;
            ui->sesioncon->clear();
            ui->sesioncorreo->clear();
            close();
        }
    }
}

void login::on_tipoUsuario_currentTextChanged(const QString &arg1)
{
    if(arg1 == "ADMINISTRADOR" || arg1 == "EMPLEADO"){
        ui->area->setCurrentIndex(2);
    }
}

void login::on_conAdministrador_editingFinished()
{
    if(ui->conAdministrador->text().compare(dE(ConAdmi)) == 0){
        ui->conAdministrador->clear();
        ui->area->setCurrentIndex(1);
    }
    else{
        QMessageBox::critical(this,"Tu no eres administrador","Solicita la Contraseña del Administrador");
    }
}

void login::on_nombre_textChanged(const QString &arg1)
{
    ui->nombreUsuario->clear();
    ui->nombreUsuario->setText(arg1);
}

void login::on_regresar_clicked()
{
    ui->tipoUsuario->setCurrentIndex(0);
    ui->area->setCurrentIndex(1);
}



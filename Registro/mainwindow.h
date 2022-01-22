#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QtSql>
#include<QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqlTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Recargar();
    void setTipoUsuario(QString);
    void conectar();

private slots:

    void on_actionTablas_triggered();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionAgregar_triggered();

    void on_actionVer_triggered();

    void showTime();

    void PasarDatos(QString);

    void on_actionRecargar_triggered();

    void on_campo_currentIndexChanged(int index);



    void on_az_clicked();

    void on_za_clicked();


    void on_actionQuery_triggered();

    void on_actionEliminar_triggered();

    void on_actionEditar_triggered();

    void on_actionUsuario_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mDatabase;
    QSqlQueryModel *q;
    QString Q;
    bool t = false,c = false, b = false, a = false;
    QStringList Tablas = {"transactions","clients","books","authors"};
    QStringList Transacciones = {"ID","Nombre","Titulo","Autor","Estado","Creacion"};
    QStringList Clientes = {"ID","Nombre","Correo","Cumpleaños","Genero","Activo","Creacion"};
    QStringList Libros = {"ID","Titulo","Author","Año","Lenguaje","Precio","Vendido","Copias"};
    QStringList Autores = {"ID","Nombre","Nacionalidad"};
    int estadoTablas = 0;
    QString tipoUsuario;
};
#endif // MAINWINDOW_H

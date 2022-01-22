#ifndef AGREGAR_H
#define AGREGAR_H

#include <QDialog>
#include<QSqlDatabase>
#include<QtSql>
#include<QSqlQuery>
#include<QCompleter>

namespace Ui {
class Agregar;
}

class Agregar : public QDialog
{
    Q_OBJECT

public:
    explicit Agregar(QWidget *parent = nullptr);
    void index(int);
    ~Agregar();
    bool Accion();

private slots:
    void on_agregar_clicked();

    void on_cancelar_clicked();

    void on_finished_stateChanged(int arg1);

    void on_active_stateChanged(int arg1);

    void on_area_currentChanged(int arg1);

private:
    Ui::Agregar *ui;
    QSqlDatabase mDatabase;

    QStringList clientes;
    QStringList titulos;
    QStringList correos;
    QStringList autores;
    QString Query;
    QSqlQueryModel *q;
    QCompleter *c;
    bool cambio = false;
};

#endif // AGREGAR_H

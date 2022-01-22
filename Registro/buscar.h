#ifndef BUSCAR_H
#define BUSCAR_H

#include <QDialog>
#include<QSqlDatabase>
#include<QtSql>
#include<QSqlQuery>

namespace Ui {
class Buscar;
}

class Buscar : public QDialog
{
    Q_OBJECT

public:
    explicit Buscar(QWidget *parent = nullptr);
    ~Buscar();

private slots:

    void on_ir_clicked();

    void on_tabla_currentTextChanged(const QString &arg1);




private:
    Ui::Buscar *ui;
    QStringList Tablas = {"transactions","clients","books","authors"};
    QStringList Transacciones = {"transaction_id","book_id","client_id","type","created_at","modified_at","finished"};
    QStringList Clientes = {"client_id","name","email","birthdate","gender","active","created_at"};
    QStringList Libros = {"book_id","author_id","title","year","language","cover_url","price","sellable","copies"};
    QStringList Autores = {"author_id","name","nationality"};
    QString Query;
    QSqlDatabase mDatabase;
    QSqlQueryModel *q;
};

#endif // BUSCAR_H

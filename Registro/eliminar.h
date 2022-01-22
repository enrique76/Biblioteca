#ifndef ELIMINAR_H
#define ELIMINAR_H

#include <QDialog>
#include<QSqlDatabase>
#include<QtSql>
#include<QSqlQuery>

namespace Ui {
class eliminar;
}

class eliminar : public QDialog
{
    Q_OBJECT

public:
    explicit eliminar(QWidget *parent = nullptr);
    ~eliminar();
    void inicio(QString i);
    void Cambio();
    void setTablas(QStringList);
    bool Accion();

private slots:
    void on_e_clicked();

    void on_spinBox_editingFinished();



    void on_datos_2_clicked(const QModelIndex &index);

    void on_ed_clicked();

    void on_lineEdit_textEdited(const QString &arg1);



    void on_spinBox_2_editingFinished();

private:
   Ui::eliminar *ui;
   QSqlQueryModel *q;
   QStringList Tablas = {"transactions","clients","books","authors"};
   QString query;
   QString nuevoDato;
   bool cambio = false;
};

#endif // ELIMINAR_H

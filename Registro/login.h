#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSql>
#include<QSqlQueryModel>
#include<QSqlError>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    QString getTipoUsuario();

private slots:
    void on_verCon_clicked();

    void on_verCon_2_clicked();

    void on_pushButton_clicked();

    QString E(QString e);

    QString dE(QString e);

    void on_pushButton_4_clicked();

    void on_sesionvercon_clicked();

    void on_sesionEntrar_clicked();

    void on_tipoUsuario_currentTextChanged(const QString &arg1);

    void on_conAdministrador_editingFinished();

    void on_nombre_textChanged(const QString &arg1);

    void on_regresar_clicked();

private:
    Ui::login *ui;
    QSqlDatabase db;
    QSqlQueryModel *query;
    QString Query;
    QString ConAdmi;
    QString typeuser;
};

#endif // LOGIN_H

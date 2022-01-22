#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>

namespace Ui {
class registro;
}

class registro : public QDialog
{
    Q_OBJECT

public:
    explicit registro(QWidget *parent = nullptr);
    void pasarDatos();
    QString creacion();
    QString getNombres();
    QString getCorreo();
    QString getTelefono();
    QString getNacionalidad();
    QString getNacimiento();
    QString getCURP();
    QString getFechaHora();
    ~registro();

private slots:
    void on_agregar_clicked();
    void on_cancelar_clicked();


public:
    Ui::registro *ui;
    bool V = false;
};

#endif // REGISTRO_H

#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    login l;

    l.exec();

    MainWindow w;

    w.setTipoUsuario(l.getTipoUsuario());

    w.setWindowTitle(w.windowTitle()+" - "+l.getTipoUsuario());

    w.show();
    return a.exec();
}

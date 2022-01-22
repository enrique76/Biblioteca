#ifndef QUERY_H
#define QUERY_H

#include <QDialog>
#include<QSqlDatabase>
#include<QtSql>
#include<QSqlQuery>
#include<QKeyEvent>

namespace Ui {
class Query;
}

class Query : public QDialog
{
    Q_OBJECT

public:
    explicit Query(QWidget *parent = nullptr);
    ~Query();


private slots:
    void on_sentencia_editingFinished();

private:
    Ui::Query *ui;
    QString query;
    QSqlQueryModel *q;
    QStringList historia;
    QCompleter *c;
};

#endif // QUERY_H

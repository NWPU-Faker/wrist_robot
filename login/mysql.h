#ifndef MYSQL_H
#define MYSQL_H

#endif // MYSQL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <qtsql>

class mysql{
public:
    int connect_mysql();  //数据库连接函数
    ~mysql();   //析构函数
    QSqlTableModel *m_Model;   //连接成功后进行相关操作所需的变量
    QSqlQuery *query;   //连接成功后进行相关操作所需的变量

private:

};
extern mysql *sql;

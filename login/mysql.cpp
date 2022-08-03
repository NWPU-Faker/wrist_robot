

#include"mysql.h"
#include<QDebug>
int mysql::connect_mysql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //连接的MYSQL的数据库驱动
    db.setHostName("localhost");         //主机名,可通过修改IP地址进行远程数据库连接访问
    db.setPort(3306);                    //端口
    db.setDatabaseName("rehabilitation");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("Passw0rdhzj");       //密码
    db.open();
    //执行数据库操作所需变量
    m_Model=new QSqlTableModel();
    query=new QSqlQuery(db);

    //测试连接
    if(!db.open())
    {
        return 0 ;
    }
    else
    {

         return 1 ;
    }
    //db.close();

}

mysql::~mysql()
{

}

mysql *sql=new mysql();

/**
C语言和设计模式-<行为型>-<Strategy>-<策略模式>
意图:
    定义一系列的算法,把它们一个个封装起来,并且使它们可相互替换.本模式使得算法可独立于使用它的客户而变化.
适用性:
    许多相关的类仅仅是行为有异.“策略”提供了一种用多个行为中的一个行为来配置一个类的方法.
    需要使用一个算法的不同变体.例如,你可能会定义一些反映不同的空间/时间权衡的算法.当这些变体实现为一个算法的类层次时[H087] ,可以使用策略模式.
    算法使用客户不应该知道的数据.可使用策略模式以避免暴露复杂的、与算法相关的数据结构.
    一个类定义了多种行为,并且这些行为在这个类的操作中以多个条件语句的形式出现.将相关的条件分支移入它们各自的Strategy类中以代替这些条件语句.
*/
#include <stdio.h>

/* 结构定义(行为类) */
// 回调指针结构体
typedef struct _db_cb_ptr {
    int (*db_open)(void **);
    int (*db_rollback)(void *);
    int (*db_mquery)(const char *, void *);
    int (*db_nquery)(const char *, void *);
} db_cb_ptr_t;

/* 各组件接口(各组算法) */

// 1. Oracle访问接口(第一组算法)
int db_ora_open(void **context)
{
    printf("Oracle open\n");
}

int db_ora_rollback(void *context)
{
    printf("Oracle rollback\n");
}

// 2. Informix访问接口(第二组算法)
int db_ifx_open(void **context)
{
    printf("Informix open\n");
}

int db_ifx_rollback(void *context)
{
    printf("Informix rollback\n");
}

// 3. DB2访问接口(第三组算法)
int db_db2_open(void **context)
{
    printf("DB2 open\n");
}

int db_db2_rollback(void *context)
{
    printf("DB2 rollback\n");
}

// 设置回调函数(维持和查询行为)
// 定义&声明回调对象
db_cb_ptr_t g_db_cb_ptr;

// 数据库初始化
int db_init(db_type_t dbtype)
{
    switch(dbtype)
    {
        case DB_TYPE_ORACLE:
        {
            // 设置Oracle回调
            g_db_cb_ptr.db_open     = db_ora_open;
            g_db_cb_ptr.db_close    = db_ora_close;
            g_db_cb_ptr.db_rollback = db_ora_rollback;
            g_db_cb_ptr.db_commit   = db_ora_commit;
            break;
        }
        case DB_TYPE_INFORMIX:
        {
            // 设置Inofrmix回调
            g_db_cb_ptr.db_open     = db_ifx_open;
            g_db_cb_ptr.db_close    = db_ifx_close;
            g_db_cb_ptr.db_rollback = db_ifx_rollback;
            g_db_cb_ptr.db_commit   = db_ifx_commit;
            break;
        }
        case DB_TYPE_DB2:
        {
            // 设置Db2回调
            g_db_cb_ptr.db_open     = db_db2_open;
            g_db_cb_ptr.db_close    = db_db2_close;
            g_db_cb_ptr.db_rollback = db_db2_rollback;
            g_db_cb_ptr.db_commit   = db_db2_commit;
            break;
        }
        default: break;
    }

    return 0;
}

// UDBC接口(Strategy接口)
// 连接数据库
int db_open(void **context)
{
    return g_db_cb_ptr.db_open(context);
}

//断开连接
int db_close(void *context)
{
    return g_db_cb_ptr.db_close(context);
}

//事务回滚
int db_rollback(void *context)
{
    return g_db_cb_ptr.db_rollback(context);
}

// 事务提交
int db_commit(void *context)
{
    return g_db_cb_ptr.db_commit(context);
}

// Strategy接口的使用
int main (int argc, char * argv[], char * envp[])
{
    void *context = NULL;  
    const char *sql = "INSERT INTO test_table VALUES(...)";  
   
    db_init(DB_TYPE_ORACLE);  
  
    db_open(&context);  
    db_nquery(sql, context);  
    db_close(context);

    return 0;
}

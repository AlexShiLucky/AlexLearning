/**
C���Ժ����ģʽ-<��Ϊ��>-<Strategy>-<����ģʽ>
��ͼ:
    ����һϵ�е��㷨,������һ������װ����,����ʹ���ǿ��໥�滻.��ģʽʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯.
������:
    �����ص����������Ϊ����.�����ԡ��ṩ��һ���ö����Ϊ�е�һ����Ϊ������һ����ķ���.
    ��Ҫʹ��һ���㷨�Ĳ�ͬ����.����,����ܻᶨ��һЩ��ӳ��ͬ�Ŀռ�/ʱ��Ȩ����㷨.����Щ����ʵ��Ϊһ���㷨������ʱ[H087] ,����ʹ�ò���ģʽ.
    �㷨ʹ�ÿͻ���Ӧ��֪��������.��ʹ�ò���ģʽ�Ա��Ⱪ¶���ӵġ����㷨��ص����ݽṹ.
    һ���ඨ���˶�����Ϊ,������Щ��Ϊ�������Ĳ������Զ������������ʽ����.����ص�������֧�������Ǹ��Ե�Strategy�����Դ�����Щ�������.
*/
#include <stdio.h>

/* �ṹ����(��Ϊ��) */
// �ص�ָ��ṹ��
typedef struct _db_cb_ptr {
    int (*db_open)(void **);
    int (*db_rollback)(void *);
    int (*db_mquery)(const char *, void *);
    int (*db_nquery)(const char *, void *);
} db_cb_ptr_t;

/* ������ӿ�(�����㷨) */

// 1. Oracle���ʽӿ�(��һ���㷨)
int db_ora_open(void **context)
{
    printf("Oracle open\n");
}

int db_ora_rollback(void *context)
{
    printf("Oracle rollback\n");
}

// 2. Informix���ʽӿ�(�ڶ����㷨)
int db_ifx_open(void **context)
{
    printf("Informix open\n");
}

int db_ifx_rollback(void *context)
{
    printf("Informix rollback\n");
}

// 3. DB2���ʽӿ�(�������㷨)
int db_db2_open(void **context)
{
    printf("DB2 open\n");
}

int db_db2_rollback(void *context)
{
    printf("DB2 rollback\n");
}

// ���ûص�����(ά�ֺͲ�ѯ��Ϊ)
// ����&�����ص�����
db_cb_ptr_t g_db_cb_ptr;

// ���ݿ��ʼ��
int db_init(db_type_t dbtype)
{
    switch(dbtype)
    {
        case DB_TYPE_ORACLE:
        {
            // ����Oracle�ص�
            g_db_cb_ptr.db_open     = db_ora_open;
            g_db_cb_ptr.db_close    = db_ora_close;
            g_db_cb_ptr.db_rollback = db_ora_rollback;
            g_db_cb_ptr.db_commit   = db_ora_commit;
            break;
        }
        case DB_TYPE_INFORMIX:
        {
            // ����Inofrmix�ص�
            g_db_cb_ptr.db_open     = db_ifx_open;
            g_db_cb_ptr.db_close    = db_ifx_close;
            g_db_cb_ptr.db_rollback = db_ifx_rollback;
            g_db_cb_ptr.db_commit   = db_ifx_commit;
            break;
        }
        case DB_TYPE_DB2:
        {
            // ����Db2�ص�
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

// UDBC�ӿ�(Strategy�ӿ�)
// �������ݿ�
int db_open(void **context)
{
    return g_db_cb_ptr.db_open(context);
}

//�Ͽ�����
int db_close(void *context)
{
    return g_db_cb_ptr.db_close(context);
}

//����ع�
int db_rollback(void *context)
{
    return g_db_cb_ptr.db_rollback(context);
}

// �����ύ
int db_commit(void *context)
{
    return g_db_cb_ptr.db_commit(context);
}

// Strategy�ӿڵ�ʹ��
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

#include <stdio.h>

#define DML_REPET_NUM        8
#define DML_VALUE_NUM        6

typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity */
typedef signed   short INT16S;                   /* Signed   16 bit quantity */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity */

typedef struct _mdl {
    INT8U phase[3];
} mdl_t;

static const INT32S Lx_dml_tbl[3][DML_VALUE_NUM][DML_REPET_NUM] = {
    { // 405nm laser
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 0
      {-1, -1, -1, -1, -1, -1, -1, -1 }, // 1
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 2
      { 1,  1,  1,  1,  1,  1,  1,  1 }, // 3
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 4
      { 0,  0,  0,  0,  0,  0,  0,  0 }  // 5
    },
    { // 488nm laser
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 0
      { 1,  1,  1,  1,  1,  1,  1,  1 }, // 1
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 2
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 3
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 4
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 5
    },
    { // 640nm laser
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 0
      {-1, -1, -1, -1, -1, -1, -1, -1 }, // 1
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 2
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 3
      { 0,  0,  0,  0,  0,  0,  0,  0 }, // 4
      { 1,  1,  1,  1,  1,  1,  1,  1 }, // 5
    }
};

static const mdl_t  mdl_PMTx[] = {
    { .phase = {[0] = 0, [1] = 0, [2] = 0} },
    { .phase = {[0] = 8, [1] = 1, [2] = 0} },
    { .phase = {[0] = 9, [1] = 2, [2] = 0} }
};

static void dml_tbl_config(const mdl_t *pmdl)
{
    #define WAVE_DOTS   (DML_VALUE_NUM*DML_REPET_NUM)
    INT8U  id, idx;
    INT32S value;
    INT32S *ptbl;

    for (id = 0; id < 3; id++) {
        ptbl = (INT32S *)&Lx_dml_tbl[id];
        for (idx = 0; idx < WAVE_DOTS; idx++) {
        	value = ptbl[(pmdl->phase[id]+idx)%WAVE_DOTS];
            printf("%d\t", value);
            if (!((idx+1)%DML_REPET_NUM)) printf("\n");
        }
        printf("-----------------------------------------------------------\n");
    }
}

int main(void)
{
    dml_tbl_config(&mdl_PMTx[0]);
    printf("===========================================================\n");
    dml_tbl_config(&mdl_PMTx[1]);
    printf("===========================================================\n");
    dml_tbl_config(&mdl_PMTx[2]);
    printf("===========================================================\n");
    return 0;
}

/*
********************************************************************************
* defs.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __DEFS_H
#define __DEFS_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/



/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

#ifndef DEF_False
#define DEF_False                       0u
#endif
#ifndef DEF_True
#define DEF_True                        1u
#endif

#ifndef DEF_Fail
#define DEF_Fail                        0u
#endif
#ifndef DEF_Success
#define DEF_Success                     1u
#endif

#ifndef DEF_No
#define DEF_No                          0u
#endif
#ifndef DEF_Yes
#define DEF_Yes                         1u
#endif

/*Bit Mask Macros**************************************************************/
#define DEF_BIT_NONE_MASK               0uL
#define DEF_BIT_ALL_MASK               ~0uL
#define DEF_BIT00_MASK                  0x00000001uL    // 1 << 0
#define DEF_BIT01_MASK                  0x00000002uL    // 1 << 1
#define DEF_BIT02_MASK                  0x00000004uL    // 1 << 2
#define DEF_BIT03_MASK                  0x00000008uL    // 1 << 3
#define DEF_BIT04_MASK                  0x00000010uL    // 1 << 4
#define DEF_BIT05_MASK                  0x00000020uL    // 1 << 5
#define DEF_BIT06_MASK                  0x00000040uL    // 1 << 6
#define DEF_BIT07_MASK                  0x00000080uL    // 1 << 7
#define DEF_BIT08_MASK                  0x00000100uL    // 1 << 8
#define DEF_BIT09_MASK                  0x00000200uL    // 1 << 9
#define DEF_BIT10_MASK                  0x00000400uL    // 1 << 10
#define DEF_BIT11_MASK                  0x00000800uL    // 1 << 11
#define DEF_BIT12_MASK                  0x00001000uL    // 1 << 12
#define DEF_BIT13_MASK                  0x00002000uL    // 1 << 13
#define DEF_BIT14_MASK                  0x00004000uL    // 1 << 14
#define DEF_BIT15_MASK                  0x00008000uL    // 1 << 15
#define DEF_BIT16_MASK                  0x00010000uL    // 1 << 16
#define DEF_BIT17_MASK                  0x00020000uL    // 1 << 17
#define DEF_BIT18_MASK                  0x00040000uL    // 1 << 18
#define DEF_BIT19_MASK                  0x00080000uL    // 1 << 19
#define DEF_BIT20_MASK                  0x00100000uL    // 1 << 20
#define DEF_BIT21_MASK                  0x00200000uL    // 1 << 21
#define DEF_BIT22_MASK                  0x00400000uL    // 1 << 22
#define DEF_BIT23_MASK                  0x00800000uL    // 1 << 23
#define DEF_BIT24_MASK                  0x01000000uL    // 1 << 24
#define DEF_BIT25_MASK                  0x02000000uL    // 1 << 25
#define DEF_BIT26_MASK                  0x04000000uL    // 1 << 26
#define DEF_BIT27_MASK                  0x08000000uL    // 1 << 27
#define DEF_BIT28_MASK                  0x10000000uL    // 1 << 28
#define DEF_BIT29_MASK                  0x20000000uL    // 1 << 29
#define DEF_BIT30_MASK                  0x40000000uL    // 1 << 30
#define DEF_BIT31_MASK                  0x80000000uL    // 1 << 31

#define  DEF_TIME_NBR_DAY_PER_WK        7u
#define  DEF_TIME_NBR_DAY_PER_YR        365u
#define  DEF_TIME_NBR_DAY_PER_YR_LEAP   366u

#define  DEF_TIME_NBR_HR_PER_DAY        24u
#define  DEF_TIME_NBR_HR_PER_WK        (DEF_TIME_NBR_HR_PER_DAY  * DEF_TIME_NBR_DAY_PER_WK     )
#define  DEF_TIME_NBR_HR_PER_YR        (DEF_TIME_NBR_HR_PER_DAY  * DEF_TIME_NBR_DAY_PER_YR     )
#define  DEF_TIME_NBR_HR_PER_YR_LEAP   (DEF_TIME_NBR_HR_PER_DAY  * DEF_TIME_NBR_DAY_PER_YR_LEAP)

#define  DEF_TIME_NBR_MIN_PER_HR        60u
#define  DEF_TIME_NBR_MIN_PER_DAY      (DEF_TIME_NBR_MIN_PER_HR  * DEF_TIME_NBR_HR_PER_DAY     )
#define  DEF_TIME_NBR_MIN_PER_WK       (DEF_TIME_NBR_MIN_PER_DAY * DEF_TIME_NBR_DAY_PER_WK     )
#define  DEF_TIME_NBR_MIN_PER_YR       (DEF_TIME_NBR_MIN_PER_DAY * DEF_TIME_NBR_DAY_PER_YR     )
#define  DEF_TIME_NBR_MIN_PER_YR_LEAP  (DEF_TIME_NBR_MIN_PER_DAY * DEF_TIME_NBR_DAY_PER_YR_LEAP)

#define  DEF_TIME_NBR_SEC_PER_MIN       60u
#define  DEF_TIME_NBR_SEC_PER_HR       (DEF_TIME_NBR_SEC_PER_MIN * DEF_TIME_NBR_MIN_PER_HR     )
#define  DEF_TIME_NBR_SEC_PER_DAY      (DEF_TIME_NBR_SEC_PER_HR  * DEF_TIME_NBR_HR_PER_DAY     )
#define  DEF_TIME_NBR_SEC_PER_WK       (DEF_TIME_NBR_SEC_PER_DAY * DEF_TIME_NBR_DAY_PER_WK     )
#define  DEF_TIME_NBR_SEC_PER_YR       (DEF_TIME_NBR_SEC_PER_DAY * DEF_TIME_NBR_DAY_PER_YR     )
#define  DEF_TIME_NBR_SEC_PER_YR_LEAP  (DEF_TIME_NBR_SEC_PER_DAY * DEF_TIME_NBR_DAY_PER_YR_LEAP)

#define  DEF_TIME_NBR_mS_PER_SEC        1000u
#define  DEF_TIME_NBR_uS_PER_SEC        1000000uL
#define  DEF_TIME_NBR_nS_PER_SEC        1000000000uL


/* set the termination character(s)   */
#define LINE_ENDING_CR                  "\r"    /*   use a <CR> carriage return as termination charcter */
#define LINE_ENDING_LF                  "\n"    /*   use a <LF> line feed as termination charcter */
#define LINE_ENDING_CRLF                "\r\n"  /*   use <CR><LF> carriage return + line feed as termination charcters */

#define lengthof(array)                 (sizeof(array) / sizeof(*(array)))
#define endof(array)                    (&(array)[lengthof(array) - 1])

#define OS_TICKS_PER_SEC                1
#define OS_TICKS_PER_MIN               (DEF_TIME_NBR_SEC_PER_MIN*OS_TICKS_PER_SEC)
#define OS_TICKS_PER_HOUR              (DEF_TIME_NBR_SEC_PER_HR*OS_TICKS_PER_SEC)


/*
********************************************************************************
* Shared Types
********************************************************************************
*/



/*
********************************************************************************
* Public Types
********************************************************************************
*/



/*
********************************************************************************
* Inline Functions
********************************************************************************
*/



/*
********************************************************************************
* Shared Data
********************************************************************************
*/



/*
********************************************************************************
* Public Data
********************************************************************************
*/



/*
********************************************************************************
* Public Function Prototypes
********************************************************************************
*/


#endif      /* __DEFS_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/

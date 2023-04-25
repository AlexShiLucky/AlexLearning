/*
********************************************************************************
* log.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __LOG_H
#define __LOG_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/

#include "vtansi.h"

/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

#define LOG_Print(format, ...)      printf(format, ## __VA_ARGS__)

#define LOG_ON                      0x80u
#define LOG_OFF                     0u
#define LOG_LEVEL_ALL
#define LOG_LEVEL_OFF               0u
#define LOG_LEVEL_INFO              0x01u
#define LOG_LEVEL_TRACE             0x02u
#define LOG_LEVEL_WARN              0x03u
#define LOG_LEVEL_ERROR             0x04u
#define LOG_LEVEL_FATAL             0x05u
#define LOG_LEVEL_NUMS              0x05u

#if CONFIG_LOG_COLOR_EN
#define LOG_COLOR_NONE              VTANSI_DISPLAY_RESET
#define LOG_COLOR_ASSERT            VTANSI_COLOR_LIGHT_RED
#define LOG_COLOR_WARN              VTANSI_COLOR_YELLOW
#define LOG_COLOR_ERROR             VTANSI_COLOR_RED
#define LOG_COLOR_INFO              VTANSI_COLOR_GREEN
#define LOG_COLOR_TRACE             VTANSI_COLOR_MAGENTA
#define LOG_COLOR_DELIMITER         VTANSI_COLOR_CYAN
#define LOG_COLOR_REPORT            VTANSI_COLOR_RED
#define ERR_COLOR_TRACE             VTANSI_COLOR_LIGHT_MAGENTA
#else
#define LOG_COLOR_NONE
#define LOG_COLOR_ASSERT
#define LOG_COLOR_WARN
#define LOG_COLOR_ERROR
#define LOG_COLOR_INFO
#define LOG_COLOR_TRACE
#define LOG_COLOR_DELIMITER
#define LOG_COLOR_REPORT
#define ERR_COLOR_TRACE
#endif

#define LOG_ASSERT_PREFIX          LOG_COLOR_ASSERT"[Fatal]#"LOG_COLOR_NONE
#define LOG_ASSERT_SUFFIX          "\r\n"
#if CONFIG_LOG_EN && CONFIG_LOG_ASSERT_EN
#define LOG_Assert(expr)                                                        \
do { if (!(expr)) {                                                             \
    LOG_Print(LOG_ASSERT_PREFIX"(%s) assert failed at %s:%d"LOG_ASSERT_SUFFIX,  \
              #expr, __FUNCTION__, __LINE__);                                   \
}} while (0)
#else
#define LOG_Assert(expr)
#endif

#define LOG_WARN_PREFIX            LOG_COLOR_WARN"[Warn]#"LOG_COLOR_NONE
#define LOG_WARN_SUFFIX            "\r\n"
#if CONFIG_LOG_EN && CONFIG_LOG_WARN_EN
#define LOG_Warn(message, ...)                                                  \
do {                                                                            \
    LOG_Print(LOG_WARN_PREFIX""message""LOG_WARN_SUFFIX, ## __VA_ARGS__);       \
} while (0)
#else
#define LOG_Warn(message, ...)
#endif

#define LOG_ERROR_PREFIX           LOG_COLOR_ERROR"[Error]#"LOG_COLOR_NONE
#define LOG_ERROR_SUFFIX           "\r\n"
#if CONFIG_LOG_EN && CONFIG_LOG_ERROR_EN
#define LOG_Error(expr, message, ...)                                            \
do { if (expr) {                                                                 \
    LOG_Print(LOG_ERROR_PREFIX""message""LOG_ERROR_SUFFIX, ## __VA_ARGS__);      \                                                                       \
    LOG_Print(LOG_ERROR_PREFIX"%s():%d"LOG_ERROR_SUFFIX, __FUNCTION__, __LINE__); \
    LOG_Print(LOG_ERROR_PREFIX""message""LOG_ERROR_SUFFIX, ## __VA_ARGS__);      \
    while (1);                                                                   \
}} while (0)
#else
#define LOG_Error(expr, message, ...)
#endif

// e.g: LOG_Info(LOG_XXX_EN, "Current value:%d", value);
#define LOG_INFO_PREFIX            LOG_COLOR_INFO"[Info]#"LOG_COLOR_NONE
#define LOG_INFO_SUFFIX            "\r\n"
#define LOG_FLUSH_SUFFIX           "\r"
#if CONFIG_LOG_EN && CONFIG_LOG_INFO_EN
#define LOG_Info(message, ...)                                                  \
do {                                                                            \
    LOG_Print(LOG_INFO_PREFIX""message""LOG_INFO_SUFFIX, ## __VA_ARGS__);       \
} while (0)
#define LOG_Flush(message, ...)                                                 \
do {                                                                            \
    LOG_Print(LOG_INFO_PREFIX""message""LOG_FLUSH_SUFFIX, ## __VA_ARGS__);      \
} while (0)
#define LOG_Raw(message, ...)                                                   \
do {                                                                            \
    LOG_Print(message, ## __VA_ARGS__);                                         \
} while (0)
#else
#define LOG_Info(message, ...)
#define LOG_Flush(message, ...)
#define LOG_Raw(message, ...)
#endif

// e.g: LOG_Trace(LOG_XXX_EN, "Abnormal value:%d", value);
#define LOG_TRACE_PREFIX           LOG_COLOR_TRACE"[Trace]#"LOG_COLOR_NONE
#define LOG_TRACE_SUFFIX           "\r\n"
#if CONFIG_LOG_TRACE_EN
#define LOG_Trace(message, ...)                                                 \
do {                                                                            \
    LOG_Print(LOG_TRACE_PREFIX""message""LOG_TRACE_SUFFIX, ## __VA_ARGS__);     \
} while (0)
#else
#define LOG_Trace(message, ...)
#endif

// e.g: LOG_Report("message");
#define LOG_REPORT_PREFIX          LOG_COLOR_REPORT"[Report]#"LOG_COLOR_NONE
#define LOG_REPORT_SUFFIX          "\r\n"
#define LOG_Report(message, ...)                                                \
do {                                                                            \
    LOG_Print(LOG_REPORT_PREFIX""message""LOG_REPORT_SUFFIX, ## __VA_ARGS__);   \
} while (0)

#define DEF_DELIMITER_STR          "================================================================"
#define DEF_CLEAR_SCREEN            VTANSI_ERASE_SCR""VTANSI_CURSOR_HOME

#define DELIMITER_PREFIX            LOG_COLOR_DELIMITER
#define DELIMITER_SUFFIX            LOG_COLOR_NONE""CONFIG_LINE_ENDING
#define DELIMITER_LINE()            LOG_Print(DELIMITER_PREFIX""DEF_DELIMITER_STR""DELIMITER_SUFFIX)

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

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif



#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __LOG_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/

/*
********************************************************************************
* clock.c
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

/*
********************************************************************************
* Included Files
********************************************************************************
*/

#include "common.h"

#include <sys/time.h>
#include "clock.h"

/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/



/*
********************************************************************************
* Shared Types
********************************************************************************
*/



/*
********************************************************************************
* Private Types
********************************************************************************
*/



/*
********************************************************************************
* Private Function Prototypes
********************************************************************************
*/

static cpu_bool_t is_leap(CPU_INT16U year);
static CPU_INT32S math_div(CPU_INT32S a, CPU_INT32S b);
static CPU_INT32S leaps_between(CPU_INT32S y1, CPU_INT32S y2);
static cpu_bool_t sys_time_calc(sys_time_t *nt, simple_time_t *t);

/*
********************************************************************************
* Shared Data
********************************************************************************
*/



/*
********************************************************************************
* Private Data
********************************************************************************
*/

const char wdays_str[] = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat\0";
const char months_str[] = "Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec\0";

/* How many days come before each month (0-12). */
static const unsigned short __mon_yday[2][13] = {
	/* Normal years. */
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
	/* Leap years. */
	{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
};

static sys_time_t   g_sys_time;


/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief
 *
 * @param
 *
 * @return
 *
 * @notes
 */
/*
 * Nonzero if YEAR is a leap year (every 4 years,
 * except every 100th isn't, and every 400th is).
 */
static cpu_bool_t is_leap(CPU_INT16U year)
{
    return (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
}

/* do a mathdiv for long type */
static CPU_INT32S math_div(CPU_INT32S a, CPU_INT32S b)
{
    return a / b - (a % b < 0);
}

/* How many leap years between y1 and y2, y1 must less or equal to y2 */
static CPU_INT32S leaps_between(CPU_INT32S y1, CPU_INT32S y2)
{
    CPU_INT32S leaps1 = math_div(y1 - 1, 4) - math_div(y1 - 1, 100)
        + math_div(y1 - 1, 400);
    CPU_INT32S leaps2 = math_div(y2 - 1, 4) - math_div(y2 - 1, 100)
        + math_div(y2 - 1, 400);
    return leaps2 - leaps1;
}

static cpu_bool_t sys_time_calc(sys_time_t *nt, simple_time_t *t)
{
    cpu_bool_t res = DEF_Fail;

    do {
        if (t->mon  > 11) break;
        if (t->mday > 30) break;
        if (t->hour > 23) break;
        if (t->min  > 59) break;
        if (t->sec  > 60) break;

        nt->sync_ticks = OSTimeGet();
        nt->sync_nsecs = sys_mktime(t);

        res = DEF_Success;
    } while (0);

    return res;
}

/*
********************************************************************************
* Public Functions
********************************************************************************
*/

/*
 * @brief
 *
 * @param
 *
 * @return
 *
 * @notes
 */
/* Converts Gregorian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in normal date format, i.e. 1980-12-31 23:59:59
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
 *
 * [For the Julian calendar (which was used in Russia before 1917,
 * Britain & colonies before 1752, anywhere else before 1582,
 * and is still in use by some communities) leave out the
 * -year/100+year/400 terms, and add 10.]
 *
 * This algorithm was first published by Gauss (I think).
 *
 * WARNING: this function will overflow on 2106-02-07 06:28:16 on
 * machines where long is 32-bit! (However, as time_t is signed, we
 * will already get problems at other places on 2038-01-19 03:14:08)
 */
CPU_INT64U sys_mktime(const simple_time_t *t)
{
    CPU_INT08S  mon;
    CPU_INT08U  day;
    CPU_INT16U year;

    year = t->year + BASE_YEAR;
    mon  = t->mon  + 1;
    day  = t->mday + 1;

    /* 1..12 -> 11,12,1..10 */
    if (0 >= (int) (mon -= 2)) {
        mon  += 12; /* Puts Feb last since it has leap day */
        year -= 1;
    }

    return ((((CPU_INT64U)
          (year/4 - year/100 + year/400 + 367*mon/12 + day) +
          year * DEF_TIME_NBR_DAY_PER_YR - 719499
        ) * DEF_TIME_NBR_HR_PER_DAY  + t->hour /* now have hours   */
      )   * DEF_TIME_NBR_MIN_PER_HR  + t->min  /* now have minutes */
    )     * DEF_TIME_NBR_SEC_PER_MIN + t->sec; /* finally seconds  */
}

/**
 * time_to_tm - converts the calendar time to local broken-down time
 *
 * @totalsecs	the number of seconds elapsed since 00:00:00 on January 1, 1970,
 *		Coordinated Universal Time (UTC).
 * @offset	offset seconds adding to totalsecs.
 * @result	pointer to struct tm variable to receive broken-down time
 */
void time_to_tm(CPU_INT64U totalsecs, CPU_INT64S offset, struct _tm *result)
{
    CPU_INT08S wday;
	CPU_INT64S days, rem, y;
	const CPU_INT16U *ip;

	days = totalsecs / DEF_TIME_NBR_SEC_PER_DAY;
	rem  = totalsecs % DEF_TIME_NBR_SEC_PER_DAY;
	rem += offset;
	while (rem < 0) {
		rem += DEF_TIME_NBR_SEC_PER_DAY;
		--days;
	}
	while (rem >= DEF_TIME_NBR_SEC_PER_DAY) {
		rem -= DEF_TIME_NBR_SEC_PER_DAY;
		++days;
	}

	result->hour = rem / DEF_TIME_NBR_SEC_PER_HR;
	rem %= DEF_TIME_NBR_SEC_PER_HR;
	result->min  = rem / DEF_TIME_NBR_SEC_PER_MIN;
	result->sec  = rem % DEF_TIME_NBR_SEC_PER_MIN;

	/* January 1, 1970 was a Thursday. */
	wday = (4 + days) % 7;
	if (wday < 0) wday += 7;
    result->wday = wday;

	y = 1970;

	while (days < 0 || days >= (is_leap(y) ? DEF_TIME_NBR_DAY_PER_YR_LEAP : DEF_TIME_NBR_DAY_PER_YR)) {
		/* Guess a corrected year, assuming 365 days per year. */
		CPU_INT64S yg = y + math_div(days, DEF_TIME_NBR_DAY_PER_YR);

		/* Adjust DAYS and Y to match the guessed year. */
		days -= (yg - y) * DEF_TIME_NBR_DAY_PER_YR + leaps_between(y, yg);
		y = yg;
	}

	result->year = y - BASE_YEAR;

	result->yday = days;

	ip = __mon_yday[is_leap(y)];
	for (y = 11; days < ip[y]; y--)
		continue;
	days -= ip[y];

	result->mon  = y;
	result->mday = days;
}

cpu_bool_t sys_synctime(sys_time_t *nt, simple_time_t *t, cpu_bool_t isforce)
{
    struct _tm rtc;
    cpu_bool_t res = DEF_Fail;

    /* 如果未同步 */
    if (isforce || (!(nt->flags & DEF_FLAGS_TIME_SYNC))) {
        do {
            LOG_Info("[SYNC] %u/%u/%u %02u:%02u:%02u", \
                t->year+BASE_YEAR, t->mon+1, t->mday+1, \
                t->hour, t->min, t->sec);
            res = sys_time_calc(nt, t);
            if (!res) break;
            time_to_tm(nt->sync_nsecs, 0, &rtc);
            //res = mcp7941x_rtcc_set(gd->prtcc, &rtc);
            //if (!res) break;
            nt->flags |= DEF_FLAGS_TIME_SYNC;
            LOG_Info("[SYNC-OK] %u-%02u-%02u %s %02u:%02u:%02u", \
                rtc.year+BASE_YEAR, rtc.mon+1, rtc.mday+1, \
                &wdays_str[rtc.wday*4], rtc.hour, rtc.min, rtc.sec);
        } while (0);
    } else {
        LOG_Info("[SYNC-NO] %u-%02u-%02u %02u:%02u:%02u", \
                t->year+BASE_YEAR, t->mon+1, t->mday+1, \
                t->hour, t->min, t->sec);
    }
    return res;
}

cpu_bool_t sys_inittime(sys_time_t *nt, simple_time_t *t)
{
    cpu_bool_t res = DEF_Fail;

    if (!(nt->flags & DEF_FLAGS_TIME_INIT)) {
        do {
            res = sys_time_calc(nt, t);
            if (!res) break;
            nt->flags |= DEF_FLAGS_TIME_INIT;
            LOG_Info("[INIT] %u-%02u-%02u %02u:%02u:%02u", \
                t->year+BASE_YEAR, t->mon+1, t->mday+1, \
                t->hour, t->min, t->sec);
        } while (0);
    }
    return res;
}

cpu_bool_t sys_settime(sys_time_t *nt, CPU_INT32U ticks)
{
    cpu_bool_t res = DEF_Fail;

    if (nt->flags & (DEF_FLAGS_TIME_INIT|DEF_FLAGS_TIME_SYNC)) {
        time_to_tm(nt->sync_nsecs, ((CPU_INT64S)ticks-(CPU_INT64S)nt->sync_ticks)/OS_TICKS_PER_SEC, &nt->now);
        res = DEF_Success;
    }
    return res;
}

cpu_bool_t sys_gettime(sys_time_t *nt, struct _tm *t)
{
    cpu_bool_t res = DEF_Fail;

    if (nt->flags & (DEF_FLAGS_TIME_INIT|DEF_FLAGS_TIME_SYNC)) {
        *t  = nt->now;
        res = DEF_Success;
    }
    return res;
}

sys_time_t* sys_time_get(void)
{
    sys_time_t *pnt = &g_sys_time;

    return pnt;
}

/*
********************************************************************************
* No More!
********************************************************************************
*/

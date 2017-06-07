// System Dependencies
#include <ctime>

// Local Dependencies
#include "../include/datetime.h"

/** Divisors: The number of milliseconds per item. */
#define DAY_DIVISOR		   86400000
#define HOUR_DIVISOR	   3600000
#define MINUTE_DIVISOR	   60000
#define SECOND_DIVISOR	   1000
#define MICROSECOND_FACTOR 1000

namespace native
{
	DateTime::DateTime()
	{
		struct timeval tv;
		struct timezone tz;

		::gettimeofday(&tv, &tz);

        _offset = short(-tz.tz_minuteswest);
		_value = (int64_t(tv.tv_sec) * SECOND_DIVISOR)
                 + (tv.tv_usec / MICROSECOND_FACTOR)
                 + (_offset * MINUTE_DIVISOR);
	}

	DateTime::DateTime(int year, int month, int day)
	{
        struct tm tm = { 0 };
        struct timeval tv;
        struct timezone tz;

        ::gettimeofday(&tv, &tz);

        tm.tm_year = year - 1900;
        tm.tm_mon  = month - 1;
        tm.tm_mday = day;

        _offset = short(-tz.tz_minuteswest);
        _value = (int64_t(std::mktime(&tm)) * SECOND_DIVISOR) + (_offset * MINUTE_DIVISOR);
	}

	DateTime::DateTime(const DateTime& other) : _value(other._value), _offset(other._offset)
	{
	}

	void DateTime::addDays(int days)
	{
		_value += int64_t(days) * DAY_DIVISOR;
	}

	void DateTime::addHours(int hours)
	{
		_value += int64_t(hours) * HOUR_DIVISOR;
	}

	void DateTime::addMinutes(int minutes)
	{
		_value += int64_t(minutes) * MINUTE_DIVISOR;
	}

	void DateTime::addSeconds(int seconds)
	{
		_value += int64_t(seconds) * SECOND_DIVISOR;
	}

	void DateTime::addMilliSeconds(int milliseconds)
	{
		_value += milliseconds;
	}

	short DateTime::getDay() const
	{
        struct tm tm;
        time_t t = time_t(_value / SECOND_DIVISOR);

        ::gmtime_r(&t, &tm);

		return tm.tm_mday;
	}

	WeekDay DateTime::getWeekDay() const
	{
        struct tm tm;
        time_t t = time_t(_value / SECOND_DIVISOR);

        ::gmtime_r(&t, &tm);

        return WeekDay(tm.tm_wday);
	}

	Month DateTime::getMonth() const
	{
        struct tm tm;
        time_t t = time_t(_value / SECOND_DIVISOR);

        ::gmtime_r(&t, &tm);

        return Month(tm.tm_mon + 1);
	}

	int DateTime::getYear() const
	{
        struct tm tm;
        time_t t = time_t(_value / SECOND_DIVISOR);

        ::gmtime_r(&t, &tm);

        return tm.tm_year + 1900;
	}

	short DateTime::getHour() const
	{
        struct tm tm;
        time_t t = time_t(_value / SECOND_DIVISOR);

        ::gmtime_r(&t, &tm);

        return tm.tm_hour;
	}

	short DateTime::getMinute() const
	{
        struct tm tm;
        time_t t = time_t(_value / SECOND_DIVISOR);

        ::gmtime_r(&t, &tm);

        return tm.tm_min;
	}

	short DateTime::getSecond() const
	{
        struct tm tm;
        time_t t = time_t(_value / SECOND_DIVISOR);

        ::gmtime_r(&t, &tm);

        return tm.tm_sec;
	}

	short DateTime::getMilliSecond() const
	{
		return _value % 1000;
	}

	String DateTime::toString() const
	{
		const wchar_t* format;

		if (getTimeZoneOffset() == 0)
			format = L"{0:04}-{1:02}-{2:02}T{3:02}:{4:02}:{5:02}.{6:03}Z";
		else
			format = L"{0:04}-{1:02}-{2:02}T{3:02}:{4:02}:{5:02}.{6:03}+{7:02}:{8:02}";

		return String::format(format, getYear(), getMonth(), getDay(), getHour(), getMinute(),
			getSecond(), getMilliSecond(), getTimeZoneOffset() / 60, getTimeZoneOffset() % 60);
	}
}

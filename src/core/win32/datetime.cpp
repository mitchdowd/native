// System Dependencies
#include <Windows.h>

// Local Dependencies
#include "../include/datetime.h"

/** The number of 100-nanosecond intervals in a millisecond. */
#define FILETIME_FACTOR 10000

/** The number of milliseconds from 1/1/1601 to 1/1/1970. */
#define FILETIME_OFFSET 11644473600000

/** Divisors: The number of milliseconds per item. */
#define DAY_DIVISOR		86400000
#define HOUR_DIVISOR	3600000
#define MINUTE_DIVISOR	60000
#define SECOND_DIVISOR	1000

namespace native
{
	static int64_t toInt64(FILETIME& ft)
	{
		return (int64_t(ft.dwHighDateTime) << 32 | ft.dwLowDateTime) / FILETIME_FACTOR - FILETIME_OFFSET;
	}

	static int64_t toInt64(SYSTEMTIME& st)
	{
		FILETIME ft;

		::SystemTimeToFileTime(&st, &ft);
		return toInt64(ft);
	}

	static void toFileTime(int64_t value, FILETIME& ft)
	{
		value = (value + FILETIME_OFFSET) * FILETIME_FACTOR;
		ft.dwLowDateTime = DWORD(value);
		ft.dwHighDateTime = value >> 32;
	}

	static void toSystemTime(int64_t value, SYSTEMTIME& st)
	{
		FILETIME ft;

		toFileTime(value, ft);
		::FileTimeToSystemTime(&ft, &st);
	}

	DateTime::DateTime()
	{
		TIME_ZONE_INFORMATION tz;
		SYSTEMTIME st;

		::GetLocalTime(&st);
		::GetTimeZoneInformation(&tz);

		_value = toInt64(st);
		_offset = short(-tz.Bias);
	}

	DateTime::DateTime(int year, int month, int day)
	{
		TIME_ZONE_INFORMATION tz;
		SYSTEMTIME st = {};

		st.wYear = year;
		st.wMonth = month;
		st.wDay = day;

		::GetTimeZoneInformation(&tz);

		_value = toInt64(st);
		_offset = short(-tz.Bias);
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
		SYSTEMTIME st;

		toSystemTime(_value, st);

		return st.wDay;
	}

	WeekDay DateTime::getWeekDay() const
	{
		SYSTEMTIME st;

		toSystemTime(_value, st);

		return WeekDay(st.wDayOfWeek);
	}

	Month DateTime::getMonth() const
	{
		SYSTEMTIME st;

		toSystemTime(_value, st);

		return Month(st.wMonth);
	}

	int DateTime::getYear() const
	{
		SYSTEMTIME st;

		toSystemTime(_value, st);

		return st.wYear;
	}

	short DateTime::getHour() const
	{
		SYSTEMTIME st;

		toSystemTime(_value, st);

		return st.wHour;
	}

	short DateTime::getMinute() const
	{
		SYSTEMTIME st;

		toSystemTime(_value, st);

		return st.wMinute;
	}

	short DateTime::getSecond() const
	{
		SYSTEMTIME st;

		toSystemTime(_value, st);

		return st.wSecond;
	}

	short DateTime::getMilliSecond() const
	{
		SYSTEMTIME st;

		toSystemTime(_value, st);

		return st.wMilliseconds;
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

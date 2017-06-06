// System Dependencies
#include <sys/time.h>

// Local Dependencies
#include "../include/datetime.h"
#include "../include/exception.h"

/** Divisors: The number of milliseconds per item. */
#define DAY_DIVISOR		86400000
#define HOUR_DIVISOR	3600000
#define MINUTE_DIVISOR	60000
#define SECOND_DIVISOR	1000

namespace native
{
	DateTime::DateTime()
	{
		struct timeval tv;
		struct timezone tz;

		::gettimeofday(&tv, &tz);

        _offset = short(-tz.tz_minuteswest);
		_value = (int64_t(tv.tv_sec) * 1000) + (tv.tv_usec / 1000) + (_offset * MINUTE_DIVISOR);
	}

	DateTime::DateTime(int year, int month, int day)
	{
		throw NotImplementedException();
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
		throw NotImplementedException();
	}

	WeekDay DateTime::getWeekDay() const
	{
		throw NotImplementedException();
	}

	Month DateTime::getMonth() const
	{
		throw NotImplementedException();
	}

	int DateTime::getYear() const
	{
		throw NotImplementedException();
	}

	short DateTime::getHour() const
	{
		throw NotImplementedException();
	}

	short DateTime::getMinute() const
	{
		throw NotImplementedException();
	}

	short DateTime::getSecond() const
	{
		throw NotImplementedException();
	}

	short DateTime::getMilliSecond() const
	{
		throw NotImplementedException();
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

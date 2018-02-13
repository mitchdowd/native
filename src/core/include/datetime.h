#ifndef _NATIVE_DATE_TIME_H_
#define _NATIVE_DATE_TIME_H_ 1

// Local Dependencies
#include "string.h"

namespace native
{
	/** The days of the week. */
	enum WeekDay
	{
		Sunday    = 0,
		Monday    = 1,
		Tuesday   = 2,
		Wednesday = 3,
		Thursday  = 4,
		Friday    = 5,
		Saturday  = 6
	};

	/** The months in a year. */
	enum Month
	{
		January   = 1,
		February  = 2,
		March     = 3,
		April     = 4,
		May       = 5,
		June      = 6,
		July      = 7,
		August    = 8,
		September = 9,
		October   = 10,
		November  = 11,
		December  = 12
	};

	/**
		Represents a specific point in time.
	 */
	class DateTime
	{
	public:
		/** Creates a DateTime with the current, local date and time. */
		DateTime();

		/**
			Creates a DateTime with the given date.
			\param year The year.
			\param month The month (from 1-12).
			\param day The day of the month.
		 */
		DateTime(int year, int month, int day);

		/**
			Copy constructor.
			\param other The date to copy.
		 */
		DateTime(const DateTime& other) = default;

		/** Destructor. */
		~DateTime() = default;

		/**
			Adds the given number of days to this DateTime.
			\param days The number of days to add (can be negative).
		 */
		void addDays(int days);

		/**
			Adds the given number of hours to this DateTime.
			\param hours The number of hours to add (can be negative).
		 */
		void addHours(int hours);

		/**
			Adds the given number of minutes to this DateTime.
			\param minutes The number of minutes to add (can be negative).
		 */
		void addMinutes(int minutes);

		/**
			Adds the given number of seconds to this DateTime.
			\param seconds The number of seconds to add (can be negative).
		 */
		void addSeconds(int seconds);

		/**
			Adds the given number of milliseconds to this DateTime.
			\param milliseconds The number of milliseconds to add (can be negative).
		 */
		void addMilliSeconds(int milliseconds);

		/** Gets the day of the month for this DateTime. */
		short getDay() const;

		/** Gets the day of the week for this DateTime. */
		WeekDay getWeekDay() const;

		/** Gets the month for this DateTime. */
		Month getMonth() const;

		/** Gets the year for this DateTime. */
		int getYear() const;

		/** Gets the hour for this DateTime (from 0-23). */
		short getHour() const;

		/** Gets the minute within the hour for this DateTime. */
		short getMinute() const;

		/** Gets the second within the minute for this DateTime. */
		short getSecond() const;

		/** Gets the millisecond within the second for this DateTime. */
		short getMilliSecond() const;

		/**
			Sets the time-zone offset applied to this DateTime. This does not
			change the values of any of the other fields, but will still
			ultimately result in shifting the time by the offset difference.
			\param offset The new offset value to set.
		 */
		void setTimeZoneOffset(short offset) noexcept { _offset = offset; }

		/**
			The offset of this DateTime from UTC timezone, in minutes. Subtract
			this offset from the time to achieve UTC.
			\return The time-zone offset in minutes.
		 */
		short getTimeZoneOffset() const noexcept { return _offset; }

		/**
			Returns a String representation of the DateTime.
			\return The DateTime as a String.
		 */
		String toString() const;

		/**
			Gets an integer/numeric representation of this DateTime value.
			\return The number of milli-seconds since 1970-01-01.
		 */
		int64_t toInt() const noexcept { return _value; }

	private:
		// Instance Variables
		int64_t _value;		///< Milliseconds since 1970/01/01 00:00:00.000
		short _offset;		///< Offset for time zone.
	};
}

#endif // _NATIVE_DATE_TIME_H_


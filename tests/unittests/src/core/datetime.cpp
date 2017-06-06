// External Dependencies
#include <core.h>
#include <test.h>

// Namespace Usage
using namespace native;
using namespace native::test;

TEST(DateTime_toString)
{
	DateTime date(2016, 8, 3);

	date.setTimeZoneOffset(0);	// So the test doesn't depend on current time zone.

	ASSERT_EQUAL(date.toString(), L"2016-08-03T00:00:00.000Z");
}

TEST(DateTime_addDays)
{
	DateTime date(2016, 12, 31);

	date.addDays(1);

	ASSERT(date.getDay() == 1);
	ASSERT(date.getMonth() == January);
	ASSERT(date.getYear() == 2017);
	ASSERT(date.getWeekDay() == Sunday);
	ASSERT(date.getHour() == 0);
	ASSERT(date.getMinute() == 0);
	ASSERT(date.getSecond() == 0);
	ASSERT(date.getMilliSecond() == 0);
}


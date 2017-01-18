// Standard Dependencies
#include <cstring>
#include <cwchar>

// Module Dependencies
#include "../../include/unittest.h"

namespace native
{
	namespace test
	{
		UnitTest::UnitTest(TestFunction function, const char* name) : _function(function), _name(name), _failureCount(0)
		{
			TestRegistry::registerTest(*this);
		}

		int UnitTest::run()
		{
			try
			{
				_function(this);
			}
			catch (...)
			{
				fail();
			}

			return _failureCount;
		}

		bool isEqual(const char* lhs, const char* rhs)
		{
			if (!lhs || !rhs)
				return !lhs && !rhs;

			return std::strcmp(lhs, rhs) == 0;
		}

		bool isEqual(const wchar_t* lhs, const wchar_t* rhs)
		{
			if (!lhs || !rhs)
				return !lhs && !rhs;

			return std::wcscmp(lhs, rhs) == 0;
		}
	}
}

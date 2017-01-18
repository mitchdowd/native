#ifndef _NATIVE_TEST_LOG_H_
#define _NATIVE_TEST_LOG_H_ 1

namespace native
{
	namespace test
	{
		/**
			Logs the testing output to the relevant console. Note that this
			isn't always STDOUT, as a platform such as Android would want it
			sent to the debugger console output as STDOUT is directed nowhere.
			\param format A printf() style format string, with extra arguments.
		 */
		void log(const char* format, ...);
	}
}

#endif // _NATIVE_TEST_LOG_H_

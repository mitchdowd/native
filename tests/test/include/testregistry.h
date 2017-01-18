#ifndef _NATIVE_TEST_TEST_REGISTRY_H_
#define _NATIVE_TEST_TEST_REGISTRY_H_ 1

namespace native
{
	namespace test
	{
		// Forward Declarations
		class UnitTest;

		/**
			The prototype for a test function, as created when using the TEST()
			macro.
		 */
		typedef void (*TestFunction)(UnitTest*);

		/**
			TestRegistry is a singleton class in which all unit tests declared
			by the TEST() macro are automatically registered for execution.
		 */
		class TestRegistry
		{
		public:
			/**
				Runs all registered unit tests and displays their results to
				the output console.
				\return The number of failed tests.
			 */
			static int runAllTests();

			/**
				Registers a UnitTest to be executed when runAllTests() is called.
				\param test The UnitTest to be executed.
			 */
			static void registerTest(UnitTest& test);
		};
	}
}

#endif // _NATIVE_TEST_TEST_REGISTRY_H_

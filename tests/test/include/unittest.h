#ifndef _NATIVE_TEST_UNIT_TEST_H_
#define _NATIVE_TEST_UNIT_TEST_H_ 1

// Module Dependencies
#include "testregistry.h"

namespace native
{
	namespace test
	{
		/**
			UnitTest encapsulates a test function pointer. Each test function
			is placed within a UnitTest and then registered with the TestRegistry
			when declared with the standard TEST() macro.
			Do not instantiate the UnitTest class directly, instead just declare
			test functions using the TEST() macro, which will automate the task.
		 */
		class UnitTest
		{
		public:
			/**
				Creates a UnitTest encapsulating the given test function.
				\param function The function to run to execute the test.
				\param name The name of the UnitTest.
			 */
			UnitTest(TestFunction function, const char* name);

			/**
				Default copy constructor.
				\param other The UnitTest to copy.
			 */
			UnitTest(const UnitTest& other) = default;

			/**
				Runs this UnitTest and records any failures.
				\return The number of failures encountered (0 or 1).
			 */
			int run();

			/**
				Marks this UnitTest as failed.
			 */
			void fail() { ++_failureCount; }

			/**
				Gets the name of the UnitTest, as specified in the constructor.
				\return The name of the UnitTest.
			 */
			const char* getName() const { return _name; }

		private:
			// Instance Variables
			TestFunction _function;
			const char*  _name;
			int          _failureCount;
		};

		/**
			Tests two basic values for equality.
			\param lhs The left-side value to compare.
			\param rhs The right-side value to compare.
			\return true if equal, false otherwise.
		 */
		bool isEqual(const char* lhs, const char* rhs);
		bool isEqual(const wchar_t* lhs, const wchar_t* rhs);
	}
}

/**
	Creates a UnitTest with a given name. The test is then described as a
	function, using ASSERT() macros to assess pass or failure conditions. The
	test is automatically added to the TestRegistry for execution.
	\param TestName The name of the unit test.
*/
#define TEST(TestName)													\
	void TestName(typename native::test::UnitTest*);					\
	native::test::UnitTest _unitTest_##TestName(TestName, #TestName);	\
	void TestName(native::test::UnitTest* test_)

/**
	Ensures the given condition is met before continuing. If the condition is
	not met, then the test fails and execution of the UnitTest ceases.
	\param condition The condition which must pass.
 */
#define ASSERT(condition) {		\
	if (!(condition)) {			\
		test_->fail();			\
		return;					\
	}}

/**
	Ensure that the two parameters are equal. If they are not equal, the test
	fails.
	\param lhs The left-hand parameter to check for equality.
	\param rhs The right-hand parameter to check for equality.
 */
#define ASSERT_EQUAL(lhs, rhs) {            \
	if (!native::test::isEqual(lhs, rhs)) { \
		test_->fail();						\
		return;                             \
	}}

/**
	Ensures that the given Exception type is thrown when the operation takes place.
	It is only valid if the specific Exception type is thrown.
	\param operation An operation or function call to perform.
	\param ExceptionType The type name of the Exception that should be thrown.
 */
#define ASSERT_THROWS(operation, TException) {	\
	bool thrown_ = false;						\
	try { operation; }							\
	catch (TException&) { thrown_ = true; }		\
	if (!thrown_) {								\
		test_->fail();							\
		return;									\
	}}

#if defined(_WIN32)

#define NATIVE_TEST_MAIN()									\
	int main() {											\
		return native::test::TestRegistry::runAllTests();	\
	}

#elif defined(__ANDROID__)

// Forward Declarations
class _jobject;
struct _JNIEnv;

#define NATIVE_TEST_MAIN()									\
	extern "C" void 										\
	Java_libnative_test_TestActivity_onCreate(				\
		_JNIEnv* env,										\
		_jobject* activity									\
	) {														\
		native::test::TestRegistry::runAllTests();			\
	}

#else
# error "Unknown testing platform."
#endif

#endif // _NATIVE_TEST_UNIT_TEST_H_

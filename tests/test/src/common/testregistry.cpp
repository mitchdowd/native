// Standard Dependencies
#include <list>
#include <ctime>

// Module Dependencies
#include "../../include/log.h"
#include "../../include/testregistry.h"
#include "../../include/unittest.h"

// Namespace Usage
using namespace std;

namespace native
{
	namespace test
	{
		list<UnitTest>* tests = nullptr;

		int TestRegistry::runAllTests()
		{
			int failureCount = 0;

			if (tests)
			{
				list<UnitTest> failures;
				std::clock_t start = std::clock();

				for (UnitTest& test : *tests)
				{
					int result = test.run();
					log("Executing test %-50s => %s.\n", test.getName(), result ? "Failed" : "Success");

					if (result)
						failures.push_back(test);

					failureCount += result;
				}

				double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

				log("\nTesting complete in %.4f sec. %d succeeded, %d failed.\n\n", duration, (int) (tests->size() - failureCount), failureCount);

				if (failureCount > 0)
				{
					log("Failed tests:\n");

					for (UnitTest& test : failures)
						log("  - %s\n", test.getName());

					log("\n");
				}
			}

			return failureCount;
		}

		void TestRegistry::registerTest(UnitTest& test)
		{
			if (tests == nullptr)
				tests = new std::list<UnitTest>();

			tests->push_back(test);
		}
	}
}

#ifndef _NATIVE_TEST_MOCK_COMPONENT_ADAPTER_H_
#define _NATIVE_TEST_MOCK_COMPONENT_ADAPTER_H_ 1

// External Dependencies
#include <ui.h>

namespace native
{
	namespace test
	{
		class MockComponentAdapter : public ui::IComponentAdapter
		{
		public:
			virtual void setText(const String& text) override {}
		};
	}
}

#endif // _NATIVE_TEST_MOCK_COMPONENT_ADAPTER_H_

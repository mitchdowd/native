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
			virtual void setParent(ui::IComponentAdapter* parent) override { _parent = parent; }

			ui::IComponentAdapter* getParent() const { return _parent; }

			virtual void setText(const String& text) override {}

		private:
			// Instance Variables
			ui::IComponentAdapter* _parent;
		};
	}
}

#endif // _NATIVE_TEST_MOCK_COMPONENT_ADAPTER_H_

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
			MockComponentAdapter() : _parent(nullptr), _visible(false) {}

			virtual void setParent(ui::IComponentAdapter* parent) override { _parent = parent; }

			ui::IComponentAdapter* getParent() const { return _parent; }

			virtual void setVisible(bool visible) override { _visible = visible; }

			virtual bool isVisible() const override { return _visible; }

			virtual void setText(const String& text) override {}

		private:
			// Instance Variables
			ui::IComponentAdapter* _parent;
			bool _visible;
		};
	}
}

#endif // _NATIVE_TEST_MOCK_COMPONENT_ADAPTER_H_

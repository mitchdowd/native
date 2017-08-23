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

			virtual void setEnabled(bool enable) override {}

			virtual void setArea(const ui::Rectangle& area) override { _area = area; }

			virtual ui::Rectangle getArea() const override { return _area; }

			virtual ui::Rectangle getContentArea() const override { return _area.getSize(); }

			virtual void setText(const String& text) override {}

			virtual void setFont(const ui::Font& font) override {}

			virtual handle_t getHandle() const noexcept override { return nullptr; }

			virtual void doInput(const ui::InputEvent& event) override {}

			virtual void doPaint(ui::Canvas& canvas) override {}

			virtual void invokeAsync(const Function<void>& func) override { func(); }

		private:
			// Instance Variables
			ui::IComponentAdapter* _parent;
			bool _visible;
			ui::Rectangle _area;
		};
	}
}

#endif // _NATIVE_TEST_MOCK_COMPONENT_ADAPTER_H_

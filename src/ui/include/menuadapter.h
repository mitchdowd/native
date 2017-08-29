#ifndef _NATIVE_UI_MENU_ADAPTER_H_
#define _NATIVE_UI_MENU_ADAPTER_H_ 1

// Module Dependencies
#include "imenuadapter.h"

namespace native
{
	namespace ui
	{
		class MenuAdapter : public IMenuAdapter
		{
		public:
			MenuAdapter();

			MenuAdapter(handle_t handle);

			~MenuAdapter();

			virtual void insert(size_t index, Action& action) override;
			virtual void insertSeparator(size_t index) override;
			virtual void insert(size_t index, Menu& menu) override;

			virtual void remove(Menu& menu) override;
			virtual void remove(Action& action) override;

			virtual handle_t getHandle() const override { return _handle; }

		private:
			// Instance Variables
			handle_t _handle;
		};
	}
}

#endif // _NATIVE_UI_MENU_ADAPTER_H_


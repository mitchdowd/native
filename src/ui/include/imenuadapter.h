#ifndef _NATIVE_UI_IMENU_ADAPTER_H_
#define _NATIVE_UI_IMENU_ADAPTER_H_ 1

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class Action;
		class Menu;

		class IMenuAdapter
		{
		public:
			virtual ~IMenuAdapter() = default;

			virtual void insert(size_t index, Action& action) = 0;
			virtual void insertSeparator(size_t index) = 0;
			virtual void insert(size_t index, Menu& menu) = 0;

			virtual void remove(Menu& menu) = 0;
			virtual void remove(Action& action) = 0;

			virtual void update(Action& action) = 0;
			virtual void update(Menu& menu) = 0;

			virtual handle_t getHandle() const = 0;
		};
	}
}

#endif // _NATIVE_UI_IMENU_ADAPTER_H_


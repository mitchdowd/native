#ifndef _NATIVE_UI_COMPONENT_H_
#define _NATIVE_UI_COMPONENT_H_ 1

// Module Dependencies
#include "componentadapter.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class LayoutComponent;

		/**
			The base class for user interface elements.
		 */
		class Component
		{
		public:
			/** Default constructor. */
			Component();

			/** Destructor. */
			virtual ~Component();

			/**
				Creates a Component with a particular native component adatper.
				\param adapter The adapter, giving native Component behavior.
			 */
			Component(ComponentAdapter* adapter);

			/**
				Gets this Component's adapter, if it has one.
				\return The adapter this Component was created with.
			 */
			ComponentAdapter* getAdapter() const noexcept { return _adapter; }

		private:
			// Instance Variables
			ComponentAdapter* _adapter;
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_H_


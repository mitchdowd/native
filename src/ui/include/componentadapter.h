#ifndef _NATIVE_UI_COMPONENT_ADAPTER_H_
#define _NATIVE_UI_COMPONENT_ADAPTER_H_ 1

// Module Dependencies
#include "icomponentadapter.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class Component;
		struct ComponentAdapterProperties;

		/**
			A ComponentAdapter can be set for a Component in order to provide
			native operating-system functionality to that Component. It gives
			a platform-independent wrapper around the platform-specific details
			of each native system component type.
		 */
		class ComponentAdapter : public IComponentAdapter
		{
		public:
			/**
				Creates a ComponentAdapter with the given platform-specific
				properties.
				\param properties A set of platform-specific inputs.
			 */
			ComponentAdapter(const ComponentAdapterProperties& properties);

			/**
				Sets the native parent of this native component.
				\param parent The parent component adapter.
			 */
			virtual void setParent(IComponentAdapter* parent) override;

			/**
				Sets the component's text, for those that support text.
				\param text The text to set.
			 */
			virtual void setText(const String& text) override;

		private:
			// Instance Variables
			handle_t _handle;
		};

		/**
			A subclassed adapter for Window-specific functionality.
		 */
		class WindowAdapter : public ComponentAdapter
		{
		public:
			/** Default constructor. */
			WindowAdapter();
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_ADAPTER_H_


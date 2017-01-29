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

			/** Destructor. */
			~ComponentAdapter();

			/**
				Sets the native parent of this native component.
				\param parent The parent component adapter.
			 */
			virtual void setParent(IComponentAdapter* parent) override;

			/**
				Shows or hides the Component, according to the parameter.
				\param visible Set `true` to show, `false` to hide.
			*/
			virtual void setVisible(bool visible) override;

			/**
				Determines whether the Component is currently visible or not.
				\return true if visible, false if not.
			 */
			virtual bool isVisible() const override;

			/**
				Sets the component's text, for those that support text.
				\param text The text to set.
			 */
			virtual void setText(const String& text) override;

			/**
				Gets the handle to system resources for this ComponentAdapter.
				\return The system resource handle.
			 */
			handle_t getHandle() const noexcept { return _handle; }

			/**
				Gets an adapter via its system resource handle.
				\param handle The system resource handle.
				\return The associated adapter, or nullptr if not found.
			 */
			static ComponentAdapter* fromHandle(handle_t handle);

			/**
				Base event handler for all Component-based events passed in
				by the operating system.
				\param event A platform-specific event structure.
			 */
			virtual void onEvent(ComponentEvent& event);

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


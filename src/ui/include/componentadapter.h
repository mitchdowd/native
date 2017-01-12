#ifndef _NATIVE_UI_COMPONENT_ADAPTER_H_
#define _NATIVE_UI_COMPONENT_ADAPTER_H_ 1

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
		class ComponentAdapter
		{
		public:
			/**
				Creates a ComponentAdapter with the given platform-specific
				properties.
				\param properties A set of platform-specific inputs.
			 */
			ComponentAdapter(const ComponentAdapterProperties& properties);
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_ADAPTER_H_


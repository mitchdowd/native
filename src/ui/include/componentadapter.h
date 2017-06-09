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
		class Window;
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
				Creates a ComponentAdapter from an existing native handle.
				\param handle An already-created native handle.
				\param component The Component the adapter is for.
			 */
			ComponentAdapter(handle_t handle, Component* component);

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
				Enables or disables the Component.
				\param enable true to enable, false to disable.
			 */
			virtual void setEnabled(bool enable) override;

			/**
				Sets the area occupied by this adapter, relative to its parent
				adapter (not necessarily the parent Component).
				\param area The area to set.
			 */
			virtual void setArea(const Rectangle& area) override;

			/**
				Gets the total area of the Component relative to its parent
				adapter (not necessarily the parent Component).
				\return The Component's area.
			 */
			virtual Rectangle getArea() const override;

			/**
				Gets the content area of the Component, relative to its non-content
				area.
				\return The content area.
			 */
			virtual Rectangle getContentArea() const override;

			/**
				Sets the component's text, for those that support text.
				\param text The text to set.
			 */
			virtual void setText(const String& text) override;

			/**
				Sets the Font this component will draw its text with.
				\param font The Font to draw text with.
			 */
			virtual void setFont(const Font& font) override;

			/**
				Performs default processing of an input event.
				\param event The event to process.
			 */
			virtual void doInput(const InputEvent& event) override;

			/**
				Paints the component however the system usually would.
				\param canvas The Canvas to paint with.
			 */
			virtual void doPaint(Canvas& canvas) override;

			/**
				Adds the given Function to the message queue to be called during
				the main UI event loop.
				\param func The Function to add to the message queue.
			 */
			virtual void invokeAsync(const Function<void>& func) override;

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
			handle_t   _handle;
			Component* _component;
		};

		// Forward Declarations
		class Button;
		class Checkbox;
		class InputComponent;
		class RadioButton;
		class TextComponent;
		class WebView;

		/**
			A subclassed adapter for Window-specific functionality.
		 */
		class WindowAdapter : public ComponentAdapter
		{
		public:
			/** 
				Creates a WindowAdapter.
				\param window The Window to bind to.
			 */
			WindowAdapter(Window* window);

            /**
                Sets the area of this Window.
                \param area The area to set.
             */
            virtual void setArea(const Rectangle& area) override;

			/**
				Sets the title text of the Window.
			 	\param text The text to set.
			 */
			virtual void setText(const String& text) override;
		};

		/**
			A subclassed adapter for TextComponents.
		 */
		class TextComponentAdapter : public ComponentAdapter
		{
		public:
			/** 
				Creates an adapter for a basic TextComponent.
				\param component The TextComponent for the adapter.
			 */
			TextComponentAdapter(TextComponent* component);

            /**
                Sets the component text.
                \param text The new text value.
             */
            virtual void setText(const String& text) override;

			/**
				Sets the component's Font.
				\param font The new Font.
			 */
			virtual void setFont(const Font& font) override;
		};

		/**
			A subclassed adapter for Buttons.
		 */
		class ButtonAdapter : public ComponentAdapter
		{
		public:
			/**
				Creates an adapter for the given Button.
				\param button The Button for this adapter.
			 */
			ButtonAdapter(Button* button);

			/**
				Sets the component text.
				\param text The new text value.
			 */
			virtual void setText(const String& text) override;

			/**
				Sets the component's Font.
				\param font The new Font.
			 */
			virtual void setFont(const Font& font) override;
		};

		/**
			A subclassed adapter for Checkboxes.
		 */
		class CheckboxAdapter : public ComponentAdapter
		{
		public:
			/**
				Creates an adapter for the given Checkbox.
				\param checkbox The Checkbox for this adapter.
			 */
			CheckboxAdapter(Checkbox* checkbox);

			/**
				Sets the component text.
				\param text The new text value.
			 */
			virtual void setText(const String& text) override;

			/**
				Sets the component's Font.
				\param font The new Font.
			 */
			virtual void setFont(const Font& font) override;

			/**
				Checks or unchecks the Checkbox.
				\param checked true to check, false to uncheck.
			 */
			void setChecked(bool checked);
		};

		/**
			A subclassed adapter for RadioButtons.
		 */
		class RadioButtonAdapter : public ComponentAdapter
		{
		public:
			/**
				Creates an adapter for the given RadioButton.
				\param radio The RadioButton for this adapter.
			 */
			RadioButtonAdapter(RadioButton* radio);

			/**
				Sets the component text.
				\param text The new text value.
			 */
			virtual void setText(const String& text) override;

			/**
				Sets the component's Font.
				\param font The new Font.
			 */
			virtual void setFont(const Font& font) override;

			/**
				Checks or unchecks the RadioButton. This should not affect
				the states of other RadioButtons.
				\param checked true to check, false to uncheck.
			 */
			void setChecked(bool checked);
		};

		/**
			A ComponentAdapter for InputComponents.
		 */
		class InputAdapter : public ComponentAdapter
		{
		public:
			/**
				Creates an adapter for the given InputComponent.
				\param input The component for this adapter.
			 */
			InputAdapter(InputComponent* input);

			/**
				Sets the component text.
				\param text The new text value.
			 */
			virtual void setText(const String& text) override;

			/**
				Sets the component's Font.
				\param font The new Font.
			 */
			virtual void setFont(const Font& font) override;
		};

		/**
			A ComponentAdapter for WebViews.
		*/
		class WebViewAdapter : public ComponentAdapter
		{
		public:
			/**
				Creates an adapter for the given WebView.
				\param view The component for this adapter.
			 */
			WebViewAdapter(WebView* view);

			/** Destructor. */
			~WebViewAdapter();

			/**
				Navigates the WebView to the given URL.
				\param url The url to navigate to (e.g. "http://github.com/").
			 */
			virtual void navigate(const String& url);

			/**
				Navigates back in the browser navigation.
			 */
			virtual void goBack();

			/**
				Navigates forward in the browser navigation.
			 */
			virtual void goForward();
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_ADAPTER_H_


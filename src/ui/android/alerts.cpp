// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/alerts.h"
#include "../include/app.h"

namespace native
{
	namespace ui
	{
		void Alerts::messageBox(Component*, const String& message, const String& title)
        {
            messageBox(message, title);
        }

		void Alerts::messageBox(const String& message, const String& title)
		{
			jni::Class ViewExtensions("libnative/ui/ViewExtensions");
            ViewExtensions.call<void>("messageBox(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V",
                                (jni::Object*) App::getAppHandle(), message.toArray(), title.toArray());
		}
	}
}


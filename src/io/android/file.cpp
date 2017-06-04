// Local Dependencies
#include "../include/file.h"

namespace native
{
	namespace io
	{
		File::File(const String& path, Flags<FileState> state) : _handle(nullptr)
		{
			throw NotImplementedException();
		}

		void File::close()
		{
			// TODO
		}

		size_t File::read(void* buffer, size_t maxBytes)
		{
			throw NotImplementedException();
		}

		size_t File::write(const void* data, size_t bytes)
		{
			throw NotImplementedException();
		}

		bool File::exists(const String& path)
		{
			throw NotImplementedException();
		}
	}
}


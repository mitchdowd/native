// System Dependencies
#include <unistd.h>

// Local Dependencies
#include "../include/file.h"

namespace native
{
	namespace io
	{
		File::File(const String& path, Flags<FileState> state) : _handle(nullptr)
		{
			open(path, state);
		}

        File::File(File&& other) : _handle(other._handle)
        {
            other._handle = nullptr;
		}

        void File::open(const String& path, Flags<FileState> state)
        {
            throw NotImplementedException();
        }

        void File::close()
        {
            if (_handle)
            {
                ::close(int(_handle));
                _handle = nullptr;
            }
        }

		size_t File::read(void* buffer, size_t maxBytes)
		{
			throw NotImplementedException();
		}

		size_t File::write(const void* data, size_t bytes)
		{
			throw NotImplementedException();
		}

		void File::deleteFromDisk(const String& path)
        {
            throw NotImplementedException();
        }

		bool File::exists(const String& path)
		{
			throw NotImplementedException();
		}
	}
}


// System Dependencies
#include <windows.h>

// Local Dependencies
#include "../include/file.h"

namespace native
{
	namespace io
	{
		/**
			Parses an incoming path to make sure it is valid to be passed on to
			the Win32 API functions.
			\param path The path to prepare.
			\return The prepared path.
		 */
		static String preparePath(const String& path)
		{
			return L"\\\\?\\" + path;
		}

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
				::CloseHandle(_handle);
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
			if (::DeleteFile(preparePath(path).toArray()) == 0)
			{
				switch (::GetLastError())
				{
				case ERROR_ACCESS_DENIED:
					throw IoException("Insufficient access to delete file");

				case ERROR_FILE_NOT_FOUND:
					break;	// Nobody cares...

				default:
					throw IoException("Unable to delete file");
				}
			}
		}

		bool File::exists(const String& path)
		{
			DWORD attr = ::GetFileAttributes(preparePath(path).toArray());

			// Directories do not count as Files.
			return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) == 0;
		}
	}
}


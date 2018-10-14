// System Dependencies
#include <Windows.h>

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

		File::File(File&& other) noexcept : _handle(other._handle)
		{
			other._handle = nullptr;
		}

		void File::open(const String& path, Flags<FileState> state)
		{
			if (_handle)
				throw IoException("File already open");

			DWORD dwDesiredAccess = 0;
			DWORD dwCreateDisposition = 0;

			// Check read/write access requested.
			if (state & FileState::Readable)
				dwDesiredAccess |= GENERIC_READ;
			if (state & FileState::Writable)
				dwDesiredAccess |= GENERIC_WRITE;

			// Check create/open flags.
			if (state & FileState::Truncate)
			{
				if (state & FileState::New)
					dwCreateDisposition = CREATE_NEW;
				else if (state & FileState::Existing)
					dwCreateDisposition = TRUNCATE_EXISTING;
				else
					dwCreateDisposition = CREATE_ALWAYS;
			}
			else if (state & FileState::Create)
			{
				if (state & FileState::New)
					dwCreateDisposition = CREATE_NEW;
				else if (state & FileState::Existing)
					dwCreateDisposition = OPEN_EXISTING;
				else
					dwCreateDisposition = OPEN_ALWAYS;
			}
			else
			{
				if (state & FileState::New)
					throw IoException("Invalid file state options");

				dwCreateDisposition = OPEN_EXISTING;
			}

			// Open the file.
			if ((_handle = ::CreateFile(preparePath(path).toArray(), dwDesiredAccess, FILE_SHARE_READ, NULL, dwCreateDisposition, 0, NULL)) == INVALID_HANDLE_VALUE)
			{
				switch (::GetLastError())
				{
				case ERROR_FILE_NOT_FOUND:
					throw IoException("File not found");
				case ERROR_FILE_EXISTS:
					throw IoException("File already exists");
				case ERROR_ACCESS_DENIED:
					throw IoException("File access denied");
				default:
					throw IoException("File open failed");
				}
			}
		}

		void File::close() noexcept
		{
			if (_handle)
			{
				::CloseHandle(_handle);
				_handle = nullptr;
			}
		}

		size_t File::read(void* buffer, size_t maxBytes)
		{
			// Convert the size to the required DWORD.
			DWORD dwSize = maxBytes > MAXDWORD ? MAXDWORD : DWORD(maxBytes);

			if (::ReadFile(_handle, buffer, dwSize, &dwSize, NULL) == FALSE)
				throw IoException("File read failed");

			return dwSize;
		}

		size_t File::write(const void* data, size_t bytes)
		{
			// Convert the number of bytes to a DWORD.
			DWORD dwBytes = bytes > MAXDWORD ? MAXDWORD : DWORD(bytes);

			if (::WriteFile(_handle, data, dwBytes, &dwBytes, NULL) == FALSE)
				throw IoException("File write failed");

			return dwBytes;
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


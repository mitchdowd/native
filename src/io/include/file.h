#ifndef _NATIVE_IO_FILE_H_
#define _NATIVE_IO_FILE_H_ 1

// External Dependencies
#include "../../core/include/flags.h"

// Local Dependencies
#include "istream.h"

namespace native
{
	namespace io
	{
		/** Possible flags to use when opening a FileStream. */
		ENUM_FLAGS(FileState)
		{
			Create   = 1,	///< Creates file if it doesn't exist.
			Truncate = 2,	///< Creates file if it doesn't exist. Empties existing file.
			Existing = 4,	///< File must already exist.
			New      = 8,	///< File cannot already exist.
			Readable = 16,	///< Request read access to the file.
			Writable = 32	///< Request write access to the file.
		};

		/**
			An endpoing for reading and writing on the file system.
		 */
		class File : public IStream
		{
		public:
			/**
				Opens the file at the given path with the given options.
				\param path The path of the file to open.
				\param state The opening flags.
			 */
			File(const String& path, Flags<FileState> state = FileState::Readable | FileState::Writable | FileState::Existing);

			/**
				Move constructor.
				\param other The File to move to this one.
			 */
			File(File&& other) noexcept;

			/** Ensures the File is closed. */
			~File() { close(); }

			/**
				Opens the file at the given path with the given options.
				\param path The path of the file to open.
				\param state The opening flags.
			 */
			void open(const String& path, Flags<FileState> state = FileState::Readable | FileState::Writable | FileState::Existing);

			/**
				Closes the File. No further operations can occur on it.
			 */
			void close() noexcept;

			/**
				Reads up to `maxBytes` from the file into the buffer. A partial
				read indicates the end of the file.
				\param maxBytes The maximum bytes to read.
				\param buffer The memory location to store the read data.
				\return The number of bytes read.
			 */
			virtual size_t read(void* buffer, size_t maxBytes) override;

			/**
				Writes data to the end of the file. If all bytes cannot be written,
				an Exception is thrown.
				\param data The data to write.
				\param bytes The number of bytes to write.
				\return The number of bytes written.
			 */
			virtual size_t write(const void* data, size_t bytes) override;

			/**
				Deletes the file at the given path from the file system.
				\param path The path of the file to delete.
			 */
			static void deleteFromDisk(const String& path);

			/**
				Checks whether a File exists at the given path.
				\param path The file path.
				\return true if there is a file at that path, false otherwise.
			 */
			static bool exists(const String& path);

			/**
				Gets the file handle.
				\return The underlying system-dependent file handle.
			 */
			handle_t getHandle() const noexcept { return _handle; }

		private:
			// Instance Variables
			handle_t _handle;
		};
	}
}

#endif // _NATIVE_IO_FILE_H_


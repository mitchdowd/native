#ifndef _NATIVE_IO_TEXT_STREAM_H_
#define _NATIVE_IO_TEXT_STREAM_H_ 1

// External Dependencies
#include "../../core/include/stringcodec.h"

// Local Dependencies
#include "istream.h"

namespace native
{
	namespace io
	{
		/**
			A class for reading and writing text to/from a IStream. The difference
			between this and basic streams is that basic streams read and write pure
			binary data, while a TextStream deals specifically with text.
		 */
		class TextStream
		{
		public:
			/**
				Creates a TextStream for reading/writing using the given underlying
				binary stream.
				\param stream The stream to read/write to.
			 */
			TextStream(IStream& stream);

			/**
				Writes a string of text to the output buffer.
				\param text The text to write.
			 */
			void write(const String& text);

			/**
				Flushes all buffered output to the underlying stream.
			 */
			void flush();

			/**
				Returns the length (in bytes) of buffered, unsent output.
				\return The number of unsent output bytes.
			 */
			size_t getOutputLength() const noexcept { return _outputLength; }

		private:
			// Instance Variables
			IStream* _stream;
			StringCodec* _codec;
			ByteArray _output;
			size_t _outputLength;
		};
	}
}

#endif // _NATIVE_IO_TEXT_STREAM_H_

